/** @file example.c
 *  @brief FIXME
 *
 *  @author eV Quirk
 */

#include "utz.h"
#include "zones.h"

#include <stdio.h>
int main() {
  printf("Total library db size: %d B\n", sizeof(utz_zone_rules) + sizeof(utz_zone_abrevs) + sizeof(utz_zone_defns) + sizeof(utz_zone_names));

  utz_datetime_t dt = {0};
  dt.date.year = 2017;
  dt.date.month = 9;
  dt.date.dayofmonth = 26;
  dt.time.hour = 1;
  dt.time.minute = 0;
  dt.time.second = 0;

  utz_zone_t active_zone;
  utz_get_zone_by_name("San Francisco", &active_zone);
  utz_offset_t offset;
  char c = utz_get_current_offset(&active_zone, &dt, &offset);
  printf("%s, current offset: %d.%d\n", active_zone.name, offset.hours, offset.minutes / 60);
  printf(active_zone.abrev_formatter, c);
  printf("\n");
  return 0;
}
