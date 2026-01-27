#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

typedef enum udayofweek_t {
	UTZ_MONDAY = 1,
	UTZ_TUESDAY,
	UTZ_WEDNESDAY,
	UTZ_THURSDAY,
	UTZ_FRIDAY,
	UTZ_SATURDAY,
	UTZ_SUNDAY,
} udayofweek_t;

/**************************************************************************/
/*                          struct definitions                            */
/**************************************************************************/

// reverse for big endian comparisons via raw?
/** @struct utime_t
 *  @brief time type
 *
 *  @var utime_t::second 0-59
 *  @var utime_t::minute 0-59
 *  @var utime_t::hour 0-23
 *  @var utime_t::padding unused space to pad to 4 bytes
 *  @var utime_t::raw for comparisons and conversions
 */
typedef struct utime_t {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
} utime_t;

// reverse for big endian comparisons via raw?
/** @struct udate_t
 *  @brief date type
 *
 *  @var udate_t::dayofweek day of week (monday = 1, sunday = 7)
 *  @var udate_t::dayofmonth 01-31
 *  @var udate_t::month 01-12
 *  @var udate_t::year 2000-2255
 *  @var udate_t::padding unused space to pad to 4 bytes
 *  @var udate_t::raw for comparisons and conversions
 */
typedef struct udate_t {
  uint16_t year;       // 2000-2255
  uint8_t month;      // 01-12
  uint8_t dayofmonth; // 01-31
  uint8_t dayofweek;
} udate_t;


/** @brief datetime type */
typedef struct udatetime_t {
  union {
    udate_t date;
    struct {
      uint16_t year;
      uint8_t month;
      uint8_t dayofmonth;
      uint8_t dayofweek;
    };
  };
  union {
    utime_t time;
    struct {
      uint8_t hour;
      uint8_t minute;
      uint8_t second;
    };
  };
} udatetime_t;

static_assert(offsetof(udatetime_t, year) == offsetof(udatetime_t, date.year));
static_assert(offsetof(udatetime_t, month) == offsetof(udatetime_t, date.month));
static_assert(offsetof(udatetime_t, dayofmonth) == offsetof(udatetime_t, date.dayofmonth));
static_assert(offsetof(udatetime_t, dayofweek) == offsetof(udatetime_t, date.dayofweek));
static_assert(offsetof(udatetime_t, hour) == offsetof(udatetime_t, time.hour));
static_assert(offsetof(udatetime_t, minute) == offsetof(udatetime_t, time.minute));
static_assert(offsetof(udatetime_t, second) == offsetof(udatetime_t, time.second));

/** @brief timezone offset type */
typedef struct uoffset_t {
  uint8_t minutes; // 0 to 59
  int8_t hours; // -12 to +12
} uoffset_t;

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

/** @struct urule_packed_t
 *  @brief packed rule type, rules for daylight savings time
 *
 * There are 3 possible formats for on - the specifier for the day when the rule takes effect:
 * 1) the default format is "dayOfWeek >= dayOfMonth"
 * 2) unless on_dayofweek is 0, in which case the format is "dayOfMonth"
 * 3) unless on_dayofmonth is 0, in which case the format is "last dayOfWeek"
 *
 *  @var urule_packed_t::from_year years since 2000
 *  @var urule_packed_t::to_year years since 2000
 *  @var urule_packed_t::on_dayofweek day of week (monday = 1, sunday = 7)
 *  @var urule_packed_t::on_dayofmonth day of month
 *  @var urule_packed_t::at_is_local_time is time of day in local time, if not utc
 *  @var urule_packed_t::at_hours time of day, hours
 *  @var urule_packed_t::at_inc_minutes time of day, minutes, in OFFSET_INCREMENT minute increments
 *  @var urule_packed_t::letter (-,S,D) sorry Troll, Antarctica
 *  @var urule_packed_t::in_month month (1-12)
 *  @var urule_packed_t::offset_hours (0-3)
 */
typedef struct urule_packed_t {
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
} urule_packed_t;

/** @brief unpacked zone type */
typedef struct uzone_t {
  const char* name;
  uoffset_t offset;
  const urule_packed_t* rules;
  uint8_t rules_len;
  const char* abrev_formatter;
  const uzone_packed_t* src;
} uzone_t;

/** @brief unpacked rule type, rules for daylight savings time */
typedef struct urule_t {
  udatetime_t datetime;
  bool is_local_time;
  char letter;
  uint8_t offset_hours;
} urule_t;
