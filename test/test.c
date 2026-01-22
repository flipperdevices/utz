#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <utz.h>

#define TEST(v) do { if (!(v)) {\
				fprintf(stderr, "test failed at line %d\n", __LINE__);\
				exit(1);\
				} } while(false)

static void test_leap(void) {
	TEST(utz_is_leap_year(UYEAR_FROM_YEAR(2000)));
	TEST(utz_is_leap_year(UYEAR_FROM_YEAR(2004)));
	TEST(utz_is_leap_year(UYEAR_FROM_YEAR(2008)));
	TEST(!utz_is_leap_year(UYEAR_FROM_YEAR(2025)));
	TEST(!utz_is_leap_year(UYEAR_FROM_YEAR(2026)));
	TEST(!utz_is_leap_year(UYEAR_FROM_YEAR(2100)));
	TEST(utz_is_leap_year(UYEAR_FROM_YEAR(2104)));
	TEST(utz_is_leap_year(UYEAR_FROM_YEAR(2204)));
	TEST(!utz_is_leap_year(UYEAR_FROM_YEAR(2200)));
}

static void test_dayofweek(void) {
	TEST(utz_dayofweek(UYEAR_FROM_YEAR(2026), 1, 22) == UTZ_THURSDAY);
	TEST(utz_dayofweek(UYEAR_FROM_YEAR(2101), 4, 26) == UTZ_TUESDAY);
	TEST(utz_dayofweek(UYEAR_FROM_YEAR(2054), 5, 17) == UTZ_SUNDAY);
	TEST(utz_dayofweek(UYEAR_FROM_YEAR(2053), 12, 12) == UTZ_FRIDAY);
}

static void test_cmp(void) {
	udatetime_t dt1 = {
		.date = utz_date_init(UYEAR_FROM_YEAR(2026), 1, 22),
		.time = {
			.hour = 12,
			.minute = 22,
			.second = 18
		}
	};
	udatetime_t dt2 = {
		.date = utz_date_init(UYEAR_FROM_YEAR(2026), 1, 22),
		.time = {
			.hour = 12,
			.minute = 22,
			.second = 19
		}
	};
	TEST(utz_udatetime_cmp(&dt1, &dt1) == 0);
	TEST(utz_udatetime_cmp(&dt1, &dt2) < 0);
	dt2 = dt1;
	dt2.time.minute -= 1;
	TEST(utz_udatetime_cmp(&dt1, &dt2) > 0);

	dt2 = dt1;
	dt2.time.hour += 1;
	TEST(utz_udatetime_cmp(&dt1, &dt2) < 0);

	dt2 = dt1;
	dt2.time.hour -= 1;
	TEST(utz_udatetime_cmp(&dt1, &dt2) > 0);

	dt2 = dt1;
	dt2.date = utz_date_init(UYEAR_FROM_YEAR(2026), 1, 23);
	TEST(utz_udatetime_cmp(&dt1, &dt2) < 0);

	dt2.date = utz_date_init(UYEAR_FROM_YEAR(2026), 1, 21);
	TEST(utz_udatetime_cmp(&dt1, &dt2) > 0);

	dt2 = dt1;
	dt2.date = utz_date_init(UYEAR_FROM_YEAR(2026), 2, 22);
	TEST(utz_udatetime_cmp(&dt1, &dt2) < 0);

	dt2.date = utz_date_init(UYEAR_FROM_YEAR(2026), 0, 22);
	TEST(utz_udatetime_cmp(&dt1, &dt2) > 0);

	dt2 = dt1;
	dt2.date = utz_date_init(UYEAR_FROM_YEAR(2027), 1, 22);
	TEST(utz_udatetime_cmp(&dt1, &dt2) < 0);

	dt2.date = utz_date_init(UYEAR_FROM_YEAR(2025), 1, 22);
	TEST(utz_udatetime_cmp(&dt1, &dt2) > 0);
}

static void test_offset(void) {
	TEST(utz_next_dayofweek_offset(UTZ_WEDNESDAY, UTZ_FRIDAY) == 2);
	TEST(utz_next_dayofweek_offset(UTZ_TUESDAY, UTZ_TUESDAY) == 0);
	TEST(utz_next_dayofweek_offset(UTZ_WEDNESDAY, UTZ_TUESDAY) == 6);
}

static void test_rule(void) {
	uzone_t zone;
	// Error handling
	TEST(!utz_get_zone_by_name("Unknown", &zone));

	// Look up by name
	TEST(utz_get_zone_by_name("Berlin", &zone));
	TEST(strcmp(zone.name, "Berlin") == 0);
	TEST(zone.rules_len == 2);
	TEST(strcmp(zone.abrev_formatter, "CE%cT") == 0);

	// Winter time
	udatetime_t dt = {
		.date = utz_date_init(UYEAR_FROM_YEAR(2026), 1, 22),
		.time = {
			.hour = 12,
			.minute = 22,
			.second = 19
		}
	};
	uoffset_t offset;
	char c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == '-');
	TEST(offset.hours == 1);
	TEST(offset.minutes == 0);

	// Winter time, right before switching to summer time
	dt.date = utz_date_init(UYEAR_FROM_YEAR(2026), 3, 29);
	dt.time.hour = 0;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == '-');
	TEST(offset.hours == 1);
	TEST(offset.minutes == 0);

	// Summer time, right after switching from winter time
	dt.date = utz_date_init(UYEAR_FROM_YEAR(2026), 3, 29);
	dt.time.hour = 1;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == 'S');
	TEST(offset.hours == 2);
	TEST(offset.minutes == 0);

	// Summer time, right before switching to winter time
	dt.date = utz_date_init(UYEAR_FROM_YEAR(2026), 10, 25);
	dt.time.hour = 0;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == 'S');
	TEST(offset.hours == 2);
	TEST(offset.minutes == 0);

	// Winter time, right after switching from summer time
	dt.time.hour = 1;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == '-');
	TEST(offset.hours == 1);
	TEST(offset.minutes == 0);
}

int main(void) {
	test_leap();
	test_dayofweek();
	test_cmp();
	test_offset();
	test_rule();
	return 0;
}