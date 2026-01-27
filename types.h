#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

typedef enum utz_dayofweek_t {
	UTZ_MONDAY = 1,
	UTZ_TUESDAY,
	UTZ_WEDNESDAY,
	UTZ_THURSDAY,
	UTZ_FRIDAY,
	UTZ_SATURDAY,
	UTZ_SUNDAY,
} utz_dayofweek_t;

/**************************************************************************/
/*                          struct definitions                            */
/**************************************************************************/

// reverse for big endian comparisons via raw?
/** @struct utz_time_t
 *  @brief time type
 *
 *  @var utz_time_t::second 0-59
 *  @var utz_time_t::minute 0-59
 *  @var utz_time_t::hour 0-23
 *  @var utz_time_t::padding unused space to pad to 4 bytes
 *  @var utz_time_t::raw for comparisons and conversions
 */
typedef struct utz_time_t {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
} utz_time_t;

// reverse for big endian comparisons via raw?
/** @struct utz_date_t
 *  @brief date type
 *
 *  @var utz_date_t::dayofweek day of week (monday = 1, sunday = 7)
 *  @var utz_date_t::dayofmonth 01-31
 *  @var utz_date_t::month 01-12
 *  @var utz_date_t::year 2000-2255
 *  @var utz_date_t::padding unused space to pad to 4 bytes
 *  @var utz_date_t::raw for comparisons and conversions
 */
typedef struct utz_date_t {
  uint16_t year;       // 2000-2255
  uint8_t month;      // 01-12
  uint8_t dayofmonth; // 01-31
  uint8_t dayofweek;
} utz_date_t;


/** @brief datetime type */
typedef struct utz_datetime_t {
  union {
    utz_date_t date;
    struct {
      uint16_t year;
      uint8_t month;
      uint8_t dayofmonth;
      uint8_t dayofweek;
    };
  };
  union {
    utz_time_t time;
    struct {
      uint8_t hour;
      uint8_t minute;
      uint8_t second;
    };
  };
} utz_datetime_t;

static_assert(offsetof(utz_datetime_t, year) == offsetof(utz_datetime_t, date.year));
static_assert(offsetof(utz_datetime_t, month) == offsetof(utz_datetime_t, date.month));
static_assert(offsetof(utz_datetime_t, dayofmonth) == offsetof(utz_datetime_t, date.dayofmonth));
static_assert(offsetof(utz_datetime_t, dayofweek) == offsetof(utz_datetime_t, date.dayofweek));
static_assert(offsetof(utz_datetime_t, hour) == offsetof(utz_datetime_t, time.hour));
static_assert(offsetof(utz_datetime_t, minute) == offsetof(utz_datetime_t, time.minute));
static_assert(offsetof(utz_datetime_t, second) == offsetof(utz_datetime_t, time.second));

/** @brief timezone offset type */
typedef struct utz_offset_t {
  uint8_t minutes; // 0 to 59
  int8_t hours; // -12 to +12
} utz_offset_t;

/** @struct uzone_packed_t
 *  @brief packed timezone type
 *
 *  @var uzone_packed_t::offset_inc_minutes signed minutes in increments of OFFSET_INCREMENT
 *  @var uzone_packed_t::rules_idx index into rules array for start of corresponding rules
 *  @var uzone_packed_t::rules_len number of rule entries
 *  @var uzone_packed_t::abrev_formatter abreviation formatter
 */
typedef struct uzone_packed_t {
  int8_t offset_inc_minutes;
  uint8_t rules_idx;
  uint8_t rules_len;
  uint16_t abrev_formatter;
} uzone_packed_t;

/** @struct utz_short_year_t
 *  @brief type-safe short year.
 *
 *  @var utz_short_year_t::y years since 2000
 */
typedef struct utz_short_year_t {
  uint8_t y;
} utz_short_year_t;

static_assert(sizeof(utz_short_year_t) == 1);

/** @struct utz_rule_packed_t
 *  @brief packed rule type, rules for daylight savings time
 *
 * There are 3 possible formats for on - the specifier for the day when the rule takes effect:
 * 1) the default format is "dayOfWeek >= dayOfMonth"
 * 2) unless on_dayofweek is 0, in which case the format is "dayOfMonth"
 * 3) unless on_dayofmonth is 0, in which case the format is "last dayOfWeek"
 *
 *  @var utz_rule_packed_t::from_year years since 2000
 *  @var utz_rule_packed_t::to_year years since 2000
 *  @var utz_rule_packed_t::on_dayofweek day of week (monday = 1, sunday = 7)
 *  @var utz_rule_packed_t::on_dayofmonth day of month
 *  @var utz_rule_packed_t::at_is_local_time is time of day in local time, if not utc
 *  @var utz_rule_packed_t::at_hours time of day, hours
 *  @var utz_rule_packed_t::at_inc_minutes time of day, minutes, in OFFSET_INCREMENT minute increments
 *  @var utz_rule_packed_t::letter (-,S,D) sorry Troll, Antarctica
 *  @var utz_rule_packed_t::in_month month (1-12)
 *  @var utz_rule_packed_t::offset_hours (0-3)
 */
typedef struct utz_rule_packed_t {
  utz_short_year_t from_year;
  utz_short_year_t to_year;
  uint8_t on_dayofweek:3;
  uint8_t on_dayofmonth:5;
  uint8_t at_is_local_time:1;
  uint8_t at_hours:5;
  uint8_t at_inc_minutes:2;
  uint8_t letter:2;
  uint8_t in_month:4;
  uint8_t offset_hours:2;
} utz_rule_packed_t;

/** @brief unpacked zone type */
typedef struct utz_zone_t {
  const char* name;
  utz_offset_t offset;
  const utz_rule_packed_t* rules;
  uint8_t rules_len;
  const char* abrev_formatter;
  const uzone_packed_t* src;
} utz_zone_t;

/** @brief unpacked rule type, rules for daylight savings time */
typedef struct utz_rule_t {
  utz_datetime_t datetime;
  bool is_local_time;
  char letter;
  uint8_t offset_hours;
} utz_rule_t;
