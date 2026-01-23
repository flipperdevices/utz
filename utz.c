/** @file utz.c
 *  @brief micro timezone library
 *
 *  @author eV
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "utz.h"
#include "zones.h"

#define RULE_IS_VALID(r) ((r).letter != 0)
#define OFFSET_INCREMENT 15 // Minutes

#define MAX_CURRENT_RULES 4 + 1 // Fuck Morocco

#define DAYS_IN_LEAP_YEAR 366

#ifdef UTZ_GLOBAL_COUNTERS
static uint8_t utz_i, utz_j;
static uint16_t utz_k;
#endif

#if 0
/** @brief lookup table name of the days of week */
static const char days_of_week[] = {
'M','o','n','d','a','y','\0',
'T','u','e','s','d','a','y','\0',
'W','e','d','n','e','s','d','a','y','\0',
'T','h','u','r','s','d','a','y','\0',
'F','r','i','d','a','y','\0',
'S','a','t','u','r','d','a','y','\0',
'S','u','n','d','a','y','\0',
};

/** @brief lookup table name of the months of year */
static const char months_of_year[] = {
'J','a','n','u','a','r','y','\0',
'F','e','b','r','u','a','r','y','\0',
'M','a','r','c','h','\0',
'A','p','r','i','l','\0',
'M','a','y','\0',
'J','u','n','e','\0',
'J','u','l','y','\0',
'A','u','g','u','s','t','\0',
'S','e','p','t','e','m','b','e','r','\0',
'N','o','v','e','m','b','e','r','\0',
'D','e','c','e','m','b','e','r','\0',
};
#endif

/** @brief unpack rule
 *
 *  @param rule_in pointer to packed rule
 *  @param cur_year year: 1 <= y <= 255 (2001 - 2255)
 *  @param rule_out pointer for the output unpacked rule
 *  @return void
 */
static void unpack_rule(const urule_packed_t* rule_in, uint8_t cur_year, urule_t* rule_out);

/** @brief unpack rules that are active in the current year
 *
 *  Note this assumes no two rules are active on the same day
 *
 *  @param rules_in pointer to packed rules
 *  @param num_rules the number of rules in the array
 *  @param cur_year year: 1 <= y <= 255 (2001 - 2255)
 *  @param rules_out pointer for the output unpacked rules
 *  @return void
 */
static void unpack_rules(const urule_packed_t* rules_in, uint8_t num_rules, uint8_t cur_year, urule_t* rules_out);

/** @brief get the rule that applies at datetime
 *
 *  @param zone timezone which rules apply to
 *  @param rules pointer to rules
 *  @param datetime the datetime to check rules for
 *  @return a pointer the the rule that applies
 */
static const urule_t* get_active_rule(const uzone_t *zone, const urule_t* rules, const udatetime_t* datetime);

/** @brief unpack timezone
 *
 *  @param name the name of the timezone
 *  @param zone_in pointer to input packed zone
 *  @param zone_in pointer to output unpacked zone
 *  @return void
 */
static void unpack_zone(const uzone_packed_t* zone_in, const char* name, uzone_t* zone_out);

static const uzone_packed_t* last_zone;
static uint8_t last_year;

/** @brief cached rules for the zone and year from the last call of utz_get_current_offset */
static urule_t cached_rules[MAX_CURRENT_RULES];

static bool ustrneq(const char* string1, const char* string2, uint8_t n) {
#ifndef UTZ_GLOBAL_COUNTERS
  uint8_t utz_i;
#endif
  for (utz_i = 0; utz_i < n && string1[utz_i] != '\0' && string2[utz_i] != '\0'; utz_i++) {
    if (string1[utz_i] != string2[utz_i]) {
      return false;
    }
  }
  return true;
}

udayofweek_t utz_dayofweek(uint8_t y, uint8_t m, uint8_t d) {
    static const uint8_t dayofweek_table[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    d = ((UYEAR_TO_YEAR(y) + (UYEAR_TO_YEAR(y)/4) - (UYEAR_TO_YEAR(y)/100) + UYEAR_OFFSET/400 + dayofweek_table[m-1] + d) % 7);
    if (d == 0) { return 7; } else { return d; }
}

bool utz_is_leap_year(uint8_t y) {
#if UYEAR_OFFSET == 2000
  if (y % 4 == 0 && y != 100 && y != 200) {
#else
  if ((((UYEAR_TO_YEAR(y) % 4) == 0) && ((UYEAR_TO_YEAR(y) % 100) != 0)) || ((UYEAR_TO_YEAR(y) % 400) == 0)) {
#endif
    return true;
  }
  return false;
}

static uint8_t days_in_month(uint8_t y, uint8_t m) {
  static const uint8_t days_in_month_nonleap[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (m == 2 && utz_is_leap_year(y)) {
    return days_in_month_nonleap[m] + 1;
  } else {
    return days_in_month_nonleap[m];
  }
}

uint8_t utz_next_dayofweek_offset(udayofweek_t dayofweek_of_cur, udayofweek_t dayofweek) {
  return (7 + dayofweek - dayofweek_of_cur) % 7;
}

int utz_udatetime_cmp(const udatetime_t* dt1, const udatetime_t* dt2) {
  int ret;
  ret = dt1->date.year - dt2->date.year; if(ret != 0) { return ret; }
  ret = dt1->date.month - dt2->date.month; if(ret != 0) { return ret; }
  ret = dt1->date.dayofmonth - dt2->date.dayofmonth; if(ret != 0) { return ret; }
  ret = dt1->time.hour - dt2->time.hour; if(ret != 0) { return ret; }
  ret = dt1->time.minute - dt2->time.minute; if(ret != 0) { return ret; }
  ret = dt1->time.second - dt2->time.second; if(ret != 0) { return ret; }
  return 0;
}

static void udate_dec(udate_t *date) {
  date->dayofweek -= 1;
  if (date->dayofweek == 0) {
    date->dayofweek = 7;
  }
  date->dayofmonth -= 1;
  if (date->dayofmonth == 0) {
    if (date->month == 1) {
      date->year -= 1;
      date->month = 12;
      date->dayofmonth = 31;
    } else {
      date->month -= 1;
      date->dayofmonth = days_in_month(date->year, date->month);
    }
  }
}

static void udate_inc(udate_t *date) {
  date->dayofweek += 1;
  if (date->dayofweek == 8) {
    date->dayofweek = 1;
  }
  date->dayofmonth += 1;
  if (date->dayofmonth == days_in_month(date->year, date->month) + 1) {
    date->dayofmonth = 1;
    date->month += 1;
    if (date->month == 13) {
      date->month = 1;
      date->year += 1;
    }
  }
}

udatetime_t utz_udatetime_add(const udatetime_t* dt, const uoffset_t *offset) {
  udatetime_t r = *dt;

  int8_t h = dt->time.hour; // 0..23
  uint8_t m = dt->time.minute; // 0..59

  m += offset->minutes; // can't overflow, offset->minutes is guaranteed to be 0..59
  if (m >= 60) {
    m -= 60;
    h += 1;
  }
  h += offset->hours; // can't overflow, offset->hours is guaranteed to be -12..12
  if (h >= 24) {
    h -= 24;
    udate_inc(&r.date);
  } else if (h < 0) {
    h += 24;
    udate_dec(&r.date);
  }
  r.time.hour = (uint8_t)h;
  r.time.minute = m;
  return r;
}

static void unpack_rule(const urule_packed_t* rule_in, uint8_t cur_year, urule_t* rule_out) {
  static const char letter_lut[3] = {'-', 'S', 'D'};

  udayofweek_t dayofweek_of_first_dayofmonth;
  udayofweek_t first_dayofweek;
  udayofweek_t dayofweek_of_dayofmonth;

  rule_out->datetime.date.year = cur_year;
  rule_out->datetime.date.month = 0;
  rule_out->datetime.date.month += rule_in->in_month;

  if (rule_in->on_dayofweek == 0) { // format is DOM e.g. 22
    rule_out->datetime.date.dayofmonth = rule_in->on_dayofmonth;
  } else if (rule_in->on_dayofmonth == 0) { // format is lastDOW e.g. lastSun
    dayofweek_of_first_dayofmonth = utz_dayofweek(cur_year, rule_in->in_month, 1);
    first_dayofweek = utz_next_dayofweek_offset(dayofweek_of_first_dayofmonth, rule_in->on_dayofweek);
    rule_out->datetime.date.dayofmonth = 1 + (7*3) + first_dayofweek;
    if (rule_out->datetime.date.dayofmonth + 7 <= days_in_month(cur_year, rule_in->in_month)) {
      rule_out->datetime.date.dayofmonth += 7;
    }
  } else { // format is DOW >= DOM e.g. Sun>=22
    dayofweek_of_dayofmonth = utz_dayofweek(cur_year, rule_in->in_month, rule_in->on_dayofmonth);
    rule_out->datetime.date.dayofmonth = rule_in->on_dayofmonth + utz_next_dayofweek_offset(
      dayofweek_of_dayofmonth, 
      rule_in->on_dayofweek
    );
  }

  rule_out->datetime.time.hour = 0;
  rule_out->datetime.time.hour += rule_in->at_hours;
  rule_out->datetime.time.minute = 0;
  rule_out->datetime.time.minute += rule_in->at_inc_minutes * OFFSET_INCREMENT;
  rule_out->is_local_time = rule_in->at_is_local_time != 0;

  rule_out->letter = letter_lut[rule_in->letter];

  rule_out->offset_hours = 0;
  rule_out->offset_hours += rule_in->offset_hours;
}

static void unpack_rules(const urule_packed_t* rules_in, uint8_t num_rules, uint8_t cur_year, urule_t* rules_out) {
#ifndef UTZ_GLOBAL_COUNTERS
  uint8_t utz_i;
#endif
  uint8_t l = 0;
  uint8_t current_rule_count = 1;

  for (utz_i = 0; utz_i < num_rules && current_rule_count < MAX_CURRENT_RULES; utz_i++) {
    // First lets find the "last" rule of the previous year, for simplification 
    // this assumes that multiple rules don't apply to the same month and
    // that the offset would not change between years (just the day of effect)
    if (cur_year >= rules_in[utz_i].from_year && cur_year <= rules_in[utz_i].to_year) {
      if (rules_in[utz_i].in_month > rules_in[l].in_month) {
        l = utz_i;
      }
      unpack_rule(&rules_in[utz_i], cur_year, &rules_out[current_rule_count++]);
    }
  }

  unpack_rule(&rules_in[l], cur_year, rules_out);
  // We override the "last" rule time of effect to be the start of the current year
  rules_out->datetime.date.year = cur_year;
  rules_out->datetime.date.month = 1;
  rules_out->datetime.date.dayofmonth = 1;
  memset(&rules_out->datetime.time, 0, sizeof(utime_t));
}

static const urule_t* get_active_rule(const uzone_t* zone, const urule_t* rules, const udatetime_t* datetime) {
#ifndef UTZ_GLOBAL_COUNTERS
  int8_t utz_i = 0;
#endif
  // Rules are guaranteed to have year set to be equal to datetime's year (done in unpack_rule).
  for (utz_i = 1; utz_i < MAX_CURRENT_RULES; utz_i++) {
    const urule_t *rule = rules + utz_i;
    if (!RULE_IS_VALID(*rule)) {
      return rule - 1;
    }
    if (!rule->is_local_time) {
      // Rule start is UTC time, simply comprare
      if (utz_udatetime_cmp(datetime, &rule->datetime) < 0) {
        return rule - 1;
      }
    } else {
      // Rule start is local time of the zone, regardless of the rule
      uoffset_t offset = zone->offset;
      udatetime_t local = utz_udatetime_add(datetime, &offset);
      if (utz_udatetime_cmp(&local, &rule->datetime) < 0) {
        return rule - 1;
      }
    }
  }
  return &rules[MAX_CURRENT_RULES-1];
}

char utz_get_current_offset(const uzone_t* zone, const udatetime_t* datetime, uoffset_t* offset) {
  if (last_zone != zone->src || last_year != datetime->date.year) {
    unpack_rules(zone->rules, zone->rules_len, datetime->date.year, cached_rules);
    last_zone = zone->src;
    last_year = datetime->date.year;
  }

  offset->minutes = zone->offset.minutes;
  offset->hours = zone->offset.hours;
  const urule_t *rule = get_active_rule(zone, cached_rules, datetime);
  offset->hours += rule->offset_hours;
  return rule->letter;
}

static void unpack_zone(const uzone_packed_t* zone_in, const char* name, uzone_t* zone_out) {
  zone_out->src = zone_in;
  zone_out->name = name;

  int8_t minutes = (zone_in->offset_inc_minutes % (60 / OFFSET_INCREMENT)) * OFFSET_INCREMENT;
  zone_out->offset.hours = zone_in->offset_inc_minutes / (60 / OFFSET_INCREMENT);
  if (minutes < 0) {
    minutes += 60;
    zone_out->offset.hours -= 1;
  }
  zone_out->offset.minutes = minutes;
  zone_out->rules = &(utz_zone_rules[zone_in->rules_idx]);
  zone_out->rules_len = zone_in->rules_len;

  zone_out->abrev_formatter = &utz_zone_abrevs[zone_in->abrev_formatter];
}

/** @brief advance to the next item in utz_zone_names and return
 *
 *  @param list pointer
 *  @return index into the utz_zone_defns array for the item before advancement
 */
static uint8_t advance_and_get_defn_idx(const char** list) {
  do {
    (*list)++;
  } while (**list);
  ++(*list);
  return **list;
}

const char *utz_next_zone_name(const char *prev) {
  do {
    ++prev;
  } while (*prev);
  prev += 2;
  if (*prev) {
    return prev;
  } else {
    return NULL;
  }
}

bool utz_get_zone_by_name(const char* name, uzone_t* zone_out) {
#ifndef UTZ_GLOBAL_COUNTERS
  uint16_t utz_k;
#endif
  const char* zone = utz_zone_names;
  for (utz_k = 0; utz_k < UTZ_NUM_ZONE_NAMES; utz_k++) {
    if (ustrneq(zone, name, UTZ_MAX_ZONE_NAME_LEN)) {
      unpack_zone(&utz_zone_defns[advance_and_get_defn_idx(&zone)], name, zone_out);
      return true;
    } else {
      advance_and_get_defn_idx(&zone);
    }
    zone++;
  }
  return false;
}

bool utz_udatetime_eq(const udatetime_t* dt1, const udatetime_t* dt2) {
  return utz_udatetime_cmp(dt1, dt2) == 0;
}

bool utz_udatetime_lt(const udatetime_t* dt1, const udatetime_t* dt2) {
  return utz_udatetime_cmp(dt1, dt2) < 0;
}

bool utz_udatetime_le(const udatetime_t* dt1, const udatetime_t* dt2) {
  return utz_udatetime_cmp(dt1, dt2) <= 0;
}

bool utz_udatetime_gt(const udatetime_t* dt1, const udatetime_t* dt2) {
  return utz_udatetime_cmp(dt1, dt2) > 0;
}

bool utz_udatetime_ge(const udatetime_t* dt1, const udatetime_t* dt2) {
  return utz_udatetime_cmp(dt1, dt2) >= 0;
}

udate_t utz_date_init(uint8_t year, uint8_t month, uint8_t day) {
  udayofweek_t day_of_week = utz_dayofweek(year, month, day);
  return (udate_t){
    .year = year,
    .month = month,
    .dayofmonth = day,
    .dayofweek = day_of_week
  };
}