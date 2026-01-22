/** @file utz.h
 *  @brief micro timezone library header
 *
 *  @author eV
 */

#ifndef _UTZ_H
#define _UTZ_H

#include <stdint.h>
#include <stdbool.h>

#include "types.h"

/**************************************************************************/
/*                              constants                                 */
/**************************************************************************/

#define UYEAR_OFFSET 2000
#define UYEAR_OFFSET_SEC 946684800
#define UYEAR_FROM_YEAR(y) (y - UYEAR_OFFSET)
#define UYEAR_TO_YEAR(y) (y + UYEAR_OFFSET)


/**************************************************************************/
/*                         datetime functions                             */
/**************************************************************************/

/** @brief populates udate_t structure, sets day of the week.
 *  @param y year: 1 <= y <= 255 (see UYEAR_FROM_YEAR)
 *  @param m month: 1 <= m <= 12
 *  @param d day: 1 <= d <= 31
 */
udate_t utz_date_init(uint8_t year, uint8_t month, uint8_t day);

/** @brief returns the day of the week for the given year/month/day
 *
 *  @param y year: 1 <= y <= 255 (see UYEAR_FROM_YEAR)
 *  @param m month: 1 <= m <= 12
 *  @param d day: 1 <= d <= 31
 *  @return day of week (Monday = 1, Sunday = 7)
 */
udayofweek_t utz_dayofweek(uint8_t y, uint8_t m, uint8_t d);

/** @brief returns true if the year is a leap year
 *
 *  @param y year: 1 <= y <= 255 (see UYEAR_FROM_YEAR)
 *  @brief true if the year is a leap year
 */
bool utz_is_leap_year(uint8_t y);

/** @brief returns days needed to get from the "current" day to the desired day of the week.
 *
 *  @param dayofweek_of_cur the "current" day of the week: 1 <= dayofweek_of_cur <= 7 (Monday = 1, Sunday = 7)
 *  @param dayofweek the desired day of the week: 1 <= dayofweek <= 7 (Monday = 1, Sunday = 7)
 *  @return number of days
 */
uint8_t utz_next_dayofweek_offset(udayofweek_t dayofweek_of_cur, udayofweek_t dayofweek);

/** @brief returns *dt1 == *dt2
 *
 *  @param dt1 pointer to the first datetime
 *  @param dt1 pointer to the second datetime
 *  @return *dt1 == *dt2
 */
bool utz_udatetime_eq(const udatetime_t* dt1, const udatetime_t* dt2);

/** @brief returns *dt1 < *dt2
 *
 *  @param dt1 pointer to the first datetime
 *  @param dt1 pointer to the second datetime
 *  @return *dt1 < *dt2
 */
bool utz_udatetime_lt(const udatetime_t* dt1, const udatetime_t* dt2);

/** @brief returns *dt1 <= *dt2
 *
 *  @param dt1 pointer to the first datetime
 *  @param dt1 pointer to the second datetime
 *  @return *dt1 <= *dt2
 */
bool utz_udatetime_le(const udatetime_t* dt1, const udatetime_t* dt2);

/** @brief returns *dt1 > *dt2
 *
 *  @param dt1 pointer to the first datetime
 *  @param dt1 pointer to the second datetime
 *  @return *dt1 > *dt2
 */
bool utz_udatetime_gt(const udatetime_t* dt1, const udatetime_t* dt2);

/** @brief returns *dt1 >= *dt2
 *
 *  @param dt1 pointer to the first datetime
 *  @param dt1 pointer to the second datetime
 *  @return *dt1 >= *dt2
 */
bool utz_udatetime_ge(const udatetime_t* dt1, const udatetime_t* dt2);

/**************************************************************************/
/*                         zone rule functions                            */
/**************************************************************************/

/** @brief unpack rule
 *
 *  @param rule_in pointer to packed rule
 *  @param cur_year year: 1 <= y <= 255 (2001 - 2255)
 *  @param rule_out pointer for the output unpacked rule
 *  @return void
 */
void utz_unpack_rule(const urule_packed_t* rule_in, uint8_t cur_year, urule_t* rule_out);

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
void utz_unpack_rules(const urule_packed_t* rules_in, uint8_t num_rules, uint8_t cur_year, urule_t* rules_out);

/** @brief get the rule that applies at datetime
 *
 *  @param rules pointer to rules
 *  @param datetime the datetime to check rules for
 *  @return a pointer the the rule that applies
 */
const urule_t* utz_get_active_rule(const urule_t* rules, const udatetime_t* datetime);

/** @brief get the offset for zone at datetime, taking into account daylight savings time rules
 *
 *  @param zone pointer to zone
 *  @param datetime the datetime (UTC) to check rules for
 *  @param offset offset for zone at datetime
 *  @return abbreviation letter
 */
char utz_get_current_offset(const uzone_t* zone, const udatetime_t* datetime, uoffset_t* offset);

/** @brief unpack timezone
 *
 *  @param name the name of the timezone
 *  @param zone_in pointer to input packed zone
 *  @param zone_in pointer to output unpacked zone
 *  @return void
 */
void utz_unpack_zone(const uzone_packed_t* zone_in, const char* name, uzone_t* zone_out);

/** @brief lookup a zone via zone_names
 *
 *  @param name the name of the zone to find
 *  @param zone_out pointer for zone found
 *  @return true if zone was found, false otherwise
 */
bool utz_get_zone_by_name(const char* name, uzone_t* zone_out);

int utz_udatetime_cmp(const udatetime_t* dt1, const udatetime_t* dt2);

#ifdef UTZ_MKTIME
uint32_t utz_mktime(const udatetime_t* dt);
#endif
/**************************************************************************/
/*                                 zones                                  */
/**************************************************************************/

extern const urule_packed_t utz_zone_rules[];
extern const uzone_packed_t utz_zone_defns[];
extern const char utz_zone_abrevs[];
extern const char utz_zone_names[];

#endif /* _UTZ_H */
