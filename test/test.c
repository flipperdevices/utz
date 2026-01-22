#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <utz.h>

#define TEST(v) do { if (!(v)) {\
				fprintf(stderr, "test failed at line %d\n", __LINE__);\
				exit(1);\
				} } while(false)

static void test_leap(void) {
	TEST(is_leap_year(UYEAR_FROM_YEAR(2000)));
	TEST(is_leap_year(UYEAR_FROM_YEAR(2004)));
	TEST(is_leap_year(UYEAR_FROM_YEAR(2008)));
	TEST(!is_leap_year(UYEAR_FROM_YEAR(2025)));
	TEST(!is_leap_year(UYEAR_FROM_YEAR(2026)));
	TEST(!is_leap_year(UYEAR_FROM_YEAR(2100)));
	TEST(is_leap_year(UYEAR_FROM_YEAR(2104)));
	TEST(is_leap_year(UYEAR_FROM_YEAR(2204)));
	TEST(!is_leap_year(UYEAR_FROM_YEAR(2200)));
}

int main(void) {
	test_leap();
	return 0;
}