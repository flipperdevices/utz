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

static void test_berlin(void) {
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

static void test_st_johns(void) {
	// Timezone with negative fractional offset
	uzone_t zone;
	TEST(utz_get_zone_by_name("St Johns", &zone));
	TEST(strcmp(zone.name, "St Johns") == 0);
	// Offset -3:30, represented as {-4, 30}
	TEST(zone.offset.hours == -4);
	TEST(zone.offset.minutes == 30);
}

static void test_new_york(void) {
	uzone_t zone;
	// Look up by name
	TEST(utz_get_zone_by_name("New York", &zone));
	TEST(strcmp(zone.name, "New York") == 0);
	TEST(zone.rules_len == 2);
	TEST(strcmp(zone.abrev_formatter, "E%cT") == 0);

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
	TEST(c == 'S');
	TEST(offset.hours == -5);
	TEST(offset.minutes == 0);

	// Winter time, right before switching to summer time
	// Switch at 2:00 local time - 7:00 UTC
	dt.date = utz_date_init(UYEAR_FROM_YEAR(2026), 3, 8);
	dt.time.hour = 6;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == 'S');
	TEST(offset.hours == -5);
	TEST(offset.minutes == 0);

	// Summer time, right after switching from winter time
	dt.time.hour = 7;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == 'D');
	TEST(offset.hours == -4);
	TEST(offset.minutes == 0);

	// Summer time, right before switching to winter time
	// Switch at 2:00 local time - 6:00 UTC
	dt.date = utz_date_init(UYEAR_FROM_YEAR(2026), 11, 1);
	dt.time.hour = 5;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == 'D');
	TEST(offset.hours == -4);
	TEST(offset.minutes == 0);

	// Winter time, right after switching from summer time
	dt.time.hour = 6;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == 'S');
	TEST(offset.hours == -5);
	TEST(offset.minutes == 0);
}

static void test_auckland(void) {
	uzone_t zone;
	// Look up by name
	TEST(utz_get_zone_by_name("Auckland", &zone));
	TEST(strcmp(zone.name, "Auckland") == 0);
	TEST(zone.rules_len == 2);
	TEST(strcmp(zone.abrev_formatter, "NZ%cT") == 0);

	// Summer time
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
	TEST(c == 'D');
	TEST(offset.hours == 13);
	TEST(offset.minutes == 0);

	// Summer time, right before switching to winter time
	// Switch at 3:00 local time - 14:00 UTC previous day
	dt.date = utz_date_init(UYEAR_FROM_YEAR(2026), 4, 4);
	dt.time.hour = 13;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == 'D');
	TEST(offset.hours == 13);
	TEST(offset.minutes == 0);

	// Winter time, right after switching from summer time
	dt.time.hour = 14;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == 'S');
	TEST(offset.hours == 12);
	TEST(offset.minutes == 0);

	// Winter time, right before switching to summer time
	// Switch at 2:00 local time - 14:00 UTC previous day
	dt.date = utz_date_init(UYEAR_FROM_YEAR(2026), 9, 26);
	dt.time.hour = 13;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == 'S');
	TEST(offset.hours == 12);
	TEST(offset.minutes == 0);

	// Summer time, right after switching from winter time
	dt.time.hour = 14;
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == 'D');
	TEST(offset.hours == 13);
	TEST(offset.minutes == 0);
}

static void test_datetime_adjust(void) {
	uoffset_t off;
	udatetime_t dt, res;

	// Positive offset (same day)
	dt = (udatetime_t){
		.date = utz_date_init(UYEAR_FROM_YEAR(2026), 1, 22),
		.time = { .hour = 10, .minute = 30, .second = 0 }
	};
	off = (uoffset_t){ .hours = 2, .minutes = 15 };

	res = utz_udatetime_add(&dt, &off);
	TEST(res.time.hour == 12);
	TEST(res.time.minute == 45);
	TEST(res.date.dayofmonth == 22);

	// Negative offset (same day)
	off = (uoffset_t){ .hours = -4, .minutes = 50 };

	res = utz_udatetime_add(&dt, &off);
	TEST(res.time.hour == 7);
	TEST(res.time.minute == 20);
	TEST(res.date.dayofmonth == 22);


	// Minute overflow -> next hour
	off = (uoffset_t){ .hours = 0, .minutes = 45 };

	res = utz_udatetime_add(&dt, &off);
	TEST(res.time.hour == 11);
	TEST(res.time.minute == 15);

	// Day increment (cross midnight)
	dt.time.hour = 23;
	dt.time.minute = 50;
	off = (uoffset_t){ .hours = 0, .minutes = 15 };

	res = utz_udatetime_add(&dt, &off);
	TEST(res.time.hour == 0);
	TEST(res.time.minute == 5);
	TEST(res.date.dayofmonth == 23);

	// Day decrement (negative offset)
	dt = (udatetime_t){
		.date = utz_date_init(UYEAR_FROM_YEAR(2026), 1, 22),
		.time = { .hour = 0, .minute = 10, .second = 0 }
	};
	off = (uoffset_t){ .hours = -1, .minutes = 30 };

	res = utz_udatetime_add(&dt, &off);
	TEST(res.time.hour == 23);
	TEST(res.time.minute == 40);
	TEST(res.date.dayofmonth == 21);

	// Month rollover (Jan -> Feb)
	dt = (udatetime_t){
		.date = utz_date_init(UYEAR_FROM_YEAR(2026), 1, 31),
		.time = { .hour = 23, .minute = 0, .second = 0 }
	};
	off = (uoffset_t){ .hours = 2, .minutes = 0 };

	res = utz_udatetime_add(&dt, &off);
	TEST(res.time.hour == 1);
	TEST(res.date.month == 2);
	TEST(res.date.dayofmonth == 1);

	// Year rollover (Dec -> Jan)
	dt = (udatetime_t){
		.date = utz_date_init(UYEAR_FROM_YEAR(2026), 12, 31),
		.time = { .hour = 23, .minute = 30, .second = 0 }
	};
	off = (uoffset_t){ .hours = 1, .minutes = 0 };

	res = utz_udatetime_add(&dt, &off);
	TEST(res.date.year == UYEAR_FROM_YEAR(2027));
	TEST(res.date.month == 1);
	TEST(res.date.dayofmonth == 1);
	TEST(res.time.hour == 0);
	TEST(res.time.minute == 30);

	// Leap year: Feb 28 -> Feb 29
	dt = (udatetime_t){
		.date = utz_date_init(UYEAR_FROM_YEAR(2028), 2, 28),
		.time = { .hour = 23, .minute = 30, .second = 0 }
	};
	off = (uoffset_t){ .hours = 1, .minutes = 0 };

	res = utz_udatetime_add(&dt, &off);
	TEST(res.date.month == 2);
	TEST(res.date.dayofmonth == 29);
	TEST(res.time.hour == 0);

	// Leap year: Feb 29 -> Mar 1
	dt.date = utz_date_init(UYEAR_FROM_YEAR(2028), 2, 29);
	dt.time.hour = 23;
	dt.time.minute = 0;

	off = (uoffset_t){ .hours = 2, .minutes = 0 };
	res = utz_udatetime_add(&dt, &off);

	TEST(res.date.month == 3);
	TEST(res.date.dayofmonth == 1);
	TEST(res.time.hour == 1);

	// Leap year: Mar 1 -> Feb 29
	dt.date = utz_date_init(UYEAR_FROM_YEAR(2028), 3, 1);
	dt.time.hour = 1;
	dt.time.minute = 0;

	off = (uoffset_t){ .hours = -2, .minutes = 0 };
	res = utz_udatetime_add(&dt, &off);

	TEST(res.date.month == 2);
	TEST(res.date.dayofmonth == 29);
	TEST(res.time.hour == 23);

	// Normal year: Mar 1 -> Feb 28
	dt.date = utz_date_init(UYEAR_FROM_YEAR(2027), 3, 1);
	dt.time.hour = 1;
	dt.time.minute = 0;

	off = (uoffset_t){ .hours = -2, .minutes = 0 };
	res = utz_udatetime_add(&dt, &off);

	TEST(res.date.month == 2);
	TEST(res.date.dayofmonth == 28);
	TEST(res.time.hour == 23);
}

// No daylight saving time
static void test_brazzaville(void) {
	uzone_t zone;
	// Look up by name
	TEST(utz_get_zone_by_name("Brazzaville", &zone));
	TEST(strcmp(zone.name, "Brazzaville") == 0);
	TEST(zone.rules_len == 0);
	TEST(strcmp(zone.abrev_formatter, "WAT") == 0);

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
}

static void test_default(void) {
	udatetime_t dt = {
		.date = utz_date_init(UYEAR_FROM_YEAR(2026), 6, 22),
		.time = {
			.hour = 12,
			.minute = 22,
			.second = 19
		}
	};
	uoffset_t offset;
	char c = utz_get_current_offset(&utz_zone_default, &dt, &offset);
	TEST(c == '-');
	TEST(offset.hours == 0);
	TEST(offset.minutes == 0);

	uzone_t zone;
	TEST(utz_get_zone_by_name("Helsinki", &zone));
	c = utz_get_current_offset(&zone, &dt, &offset);
	TEST(c == 'S');
	TEST(offset.hours == 3);
	TEST(offset.minutes == 0);
}

int main(void) {
	test_leap();
	test_dayofweek();
	test_cmp();
	test_offset();
	test_datetime_adjust();
	test_berlin();
	test_st_johns();
	test_new_york();
	test_auckland();
	test_brazzaville();
	test_default();
	return 0;
}