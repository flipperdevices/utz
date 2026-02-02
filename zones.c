#include "utz.h"

const utz_rule_packed_t utz_zone_rules[55] = {
{{  8}, {255}, 7,  1,  1,  2, 0, 1,  4, 0}, // 	AN	2008	max	-	Apr	Sun>=1	2:00s	0	S
{{  8}, {255}, 7,  1,  1,  2, 0, 2, 10, 1}, // 	AN	2008	max	-	Oct	Sun>=1	2:00s	1:00	D
{{  8}, {255}, 7,  1,  1,  2, 0, 1,  4, 0}, // 	AS	2008	max	-	Apr	Sun>=1	2:00s	0	S
{{  8}, {255}, 7,  1,  1,  2, 0, 2, 10, 1}, // 	AS	2008	max	-	Oct	Sun>=1	2:00s	1:00	D
{{  8}, {255}, 7,  1,  1,  2, 0, 1,  4, 0}, // 	AT	2008	max	-	Apr	Sun>=1	2:00s	0	S
{{  1}, {255}, 7,  1,  1,  2, 0, 2, 10, 1}, // 	AT	2001	max	-	Oct	Sun>=1	2:00s	1:00	D
{{ 26}, { 26}, 6, 21,  1, 23, 0, 0,  2, 0}, // 	Brazil	2026	only	-	Feb	Sun>=22	0:00	0	-
{{ 27}, { 33}, 6, 14,  1, 23, 0, 0,  2, 0}, // 	Brazil	2027	2033	-	Feb	Sun>=15	0:00	0	-
{{ 34}, { 34}, 6, 21,  1, 23, 0, 0,  2, 0}, // 	Brazil	2034	only	-	Feb	Sun>=22	0:00	0	-
{{ 35}, { 36}, 6, 14,  1, 23, 0, 0,  2, 0}, // 	Brazil	2035	2036	-	Feb	Sun>=15	0:00	0	-
{{ 37}, { 37}, 6, 21,  1, 23, 0, 0,  2, 0}, // 	Brazil	2037	only	-	Feb	Sun>=22	0:00	0	-
{{ 38}, {255}, 6, 14,  1, 23, 0, 0,  2, 0}, // 	Brazil	2038	max	-	Feb	Sun>=15	0:00	0	-
{{  8}, {255}, 7, 15,  1,  0, 0, 1, 10, 1}, // 	Brazil	2008	max	-	Oct	Sun>=15	0:00	1:00	S
{{  7}, {255}, 7,  8,  1,  2, 0, 2,  3, 1}, // 	Canada	2007	max	-	Mar	Sun>=8	2:00	1:00	D
{{  7}, {255}, 7,  1,  1,  1, 0, 1, 11, 0}, // 	Canada	2007	max	-	Nov	Sun>=1	2:00	0	S
{{ 16}, {255}, 7,  9,  0,  3, 0, 0,  5, 0}, // 	Chile	2016	max	-	May	Sun>=9	3:00u	0	-
{{ 16}, {255}, 7,  9,  0,  4, 0, 1,  8, 1}, // 	Chile	2016	max	-	Aug	Sun>=9	4:00u	1:00	S
{{  0}, {255}, 7,  0,  0,  1, 0, 1,  3, 1}, // 	EU	1981	max	-	Mar	lastSun	 1:00u	1:00	S
{{  0}, {255}, 7,  0,  0,  1, 0, 0, 10, 0}, // 	EU	1996	max	-	Oct	lastSun	 1:00u	0	-
{{ 15}, {255}, 7, 15,  1,  2, 0, 0,  1, 0}, // 	Fiji	2015	max	-	Jan	Sun>=15	3:00	0	-
{{ 14}, {255}, 7,  1,  1,  2, 0, 1, 11, 1}, // 	Fiji	2014	max	-	Nov	Sun>=1	2:00	1:00	S
{{ 25}, { 27}, 0, 22,  1,  0, 0, 2,  3, 1}, // 	Iran	2025	2027	-	Mar	22	0:00	1:00	D
{{ 28}, { 29}, 0, 21,  1,  0, 0, 2,  3, 1}, // 	Iran	2028	2029	-	Mar	21	0:00	1:00	D
{{ 30}, { 31}, 0, 22,  1,  0, 0, 2,  3, 1}, // 	Iran	2030	2031	-	Mar	22	0:00	1:00	D
{{ 32}, { 33}, 0, 21,  1,  0, 0, 2,  3, 1}, // 	Iran	2032	2033	-	Mar	21	0:00	1:00	D
{{ 34}, { 35}, 0, 22,  1,  0, 0, 2,  3, 1}, // 	Iran	2034	2035	-	Mar	22	0:00	1:00	D
{{ 36}, {255}, 0, 21,  1,  0, 0, 2,  3, 1}, // 	Iran	2036	max	-	Mar	21	0:00	1:00	D
{{ 25}, { 27}, 0, 21,  1, 23, 0, 1,  9, 0}, // 	Iran	2025	2027	-	Sep	22	0:00	0	S
{{ 28}, { 29}, 0, 20,  1, 23, 0, 1,  9, 0}, // 	Iran	2028	2029	-	Sep	21	0:00	0	S
{{ 30}, { 31}, 0, 21,  1, 23, 0, 1,  9, 0}, // 	Iran	2030	2031	-	Sep	22	0:00	0	S
{{ 32}, { 33}, 0, 20,  1, 23, 0, 1,  9, 0}, // 	Iran	2032	2033	-	Sep	21	0:00	0	S
{{ 34}, { 35}, 0, 21,  1, 23, 0, 1,  9, 0}, // 	Iran	2034	2035	-	Sep	22	0:00	0	S
{{ 36}, {255}, 0, 20,  1, 23, 0, 1,  9, 0}, // 	Iran	2036	max	-	Sep	21	0:00	0	S
{{ 14}, {255}, 4,  0,  1, 24, 0, 1,  3, 1}, // 	Jordan	2014	max	-	Mar	lastThu	24:00	1:00	S
{{ 14}, {255}, 5,  0,  1,  0, 0, 0, 10, 0}, // 	Jordan	2014	max	-	Oct	lastFri	0:00s	0	-
{{  0}, {255}, 7,  0,  1,  0, 0, 1,  3, 1}, // 	Lebanon	1993	max	-	Mar	lastSun	0:00	1:00	S
{{  0}, {255}, 7,  0,  1,  0, 0, 0, 10, 0}, // 	Lebanon	1999	max	-	Oct	lastSun	0:00	0	-
{{  2}, {255}, 7,  1,  1,  2, 0, 2,  4, 1}, // 	Mexico	2002	max	-	Apr	Sun>=1	2:00	1:00	D
{{  2}, {255}, 7,  0,  1,  1, 0, 1, 10, 0}, // 	Mexico	2002	max	-	Oct	lastSun	2:00	0	S
{{ 15}, {255}, 6,  0,  1,  2, 0, 1,  3, 1}, // 	Mongol	2015	max	-	Mar	lastSat	2:00	1:00	S
{{ 15}, {255}, 6,  0,  1,  0, 0, 0,  9, 0}, // 	Mongol	2015	max	-	Sep	lastSat	0:00	0	-
{{ 26}, {255}, 7,  0,  1,  2, 0, 1,  3, 1}, // 	Morocco	2026	max	-	Mar	lastSun	 2:00	1:00	S
{{ 13}, {255}, 7,  0,  1,  2, 0, 0, 10, 0}, // 	Morocco	2013	max	-	Oct	lastSun	 3:00	0	-
{{ 36}, { 36}, 0, 19,  1,  2, 0, 0, 10, 0}, // 	Morocco	2036	only	-	Oct	19	 3:00	0	-
{{ 37}, { 37}, 0,  4,  1,  2, 0, 0, 10, 0}, // 	Morocco	2037	only	-	Oct	 4	 3:00	0	-
{{  8}, {255}, 7,  1,  1,  2, 0, 1,  4, 0}, // 	NZ	2008	max	-	Apr	Sun>=1	2:00s	0	S
{{  7}, {255}, 7,  0,  1,  2, 0, 2,  9, 1}, // 	NZ	2007	max	-	Sep	lastSun	2:00s	1:00	D
{{  0}, {255}, 7,  1,  1,  1, 0, 0,  4, 0}, // 	Namibia	1995	max	-	Apr	Sun>=1	2:00	0	-
{{  0}, {255}, 7,  1,  1,  2, 0, 1,  9, 1}, // 	Namibia	1994	max	-	Sep	Sun>=1	2:00	1:00	S
{{ 17}, {255}, 7, 15,  1,  2, 0, 0,  1, 0}, // 	Tonga	2017	max	-	Jan	Sun>=15	3:00	0	-
{{ 16}, {255}, 7,  1,  1,  2, 0, 1, 11, 1}, // 	Tonga	2016	max	-	Nov	Sun>=1	2:00	1:00	S
{{  7}, {255}, 7,  8,  1,  2, 0, 2,  3, 1}, // 	US	2007	max	-	Mar	Sun>=8	2:00	1:00	D
{{  7}, {255}, 7,  1,  1,  1, 0, 1, 11, 0}, // 	US	2007	max	-	Nov	Sun>=1	2:00	0	S
{{ 13}, {255}, 5, 23,  1,  2, 0, 2,  3, 1}, // 	Zion	2013	max	-	Mar	Fri>=23	2:00	1:00	D
{{ 13}, {255}, 7,  0,  1,  1, 0, 1, 10, 0}, // 	Zion	2013	max	-	Oct	lastSun	2:00	0	S
};

const char utz_zone_abrevs[361] = {
'E','E','S','T','\0',
'W','E','%','s','T','\0',
'W','A','T','\0',
'C','A','T','\0',
'E','A','T','\0',
'W','A','%','s','T','\0',
'A','K','%','s','T','\0',
'A','R','S','T','\0',
'A','S','T','\0',
'C','O','S','T','\0',
'V','E','T','\0',
'C','%','s','T','\0',
'M','%','s','T','\0',
'C','S','T','\0',
'W','G','%','s','T','\0',
'A','%','s','T','\0',
'P','%','s','T','\0',
'A','M','T','\0',
'U','Y','S','T','\0',
'E','%','s','T','\0',
'M','S','T','\0',
'C','L','%','s','T','\0',
'B','R','%','s','T','\0',
'N','%','s','T','\0',
'K','Z','T','\0',
'E','E','%','s','T','\0',
'T','M','T','\0',
'A','Z','T','\0',
'I','C','T','\0',
'K','G','T','\0',
'S','L','S','T','\0',
'G','S','T','\0',
'T','J','T','\0',
'H','K','S','T','\0',
'I','R','K','T','\0',
'W','I','B','\0',
'I','%','s','T','\0',
'A','F','T','\0',
'P','K','S','T','\0',
'N','P','T','\0',
'I','S','T','\0',
'K','R','A','T','\0',
'M','Y','T','\0',
'M','A','G','T','\0',
'O','M','S','T','\0',
'K','S','T','\0',
'G','E','T','\0',
'I','R','%','s','T','\0',
'J','S','T','\0',
'U','L','A','%','s','T','\0',
'V','L','A','T','\0',
'Y','A','K','T','\0',
'M','M','T','\0',
'Y','E','K','T','\0',
'A','Z','O','%','s','T','\0',
'C','V','T','\0',
'A','C','%','s','T','\0',
'A','E','S','T','\0',
'A','C','S','T','\0',
'A','E','%','s','T','\0',
'A','W','S','T','\0',
'U','T','C','\0',
'C','E','%','s','T','\0',
'T','R','T','\0',
'K','A','L','T','\0',
'G','M','T','\0',
'M','S','K','\0',
'S','A','M','T','\0',
'N','Z','%','s','T','\0',
'F','J','%','s','T','\0',
'C','h','S','T','\0',
'H','S','T','\0',
'M','H','T','\0',
'S','S','T','\0',
'T','O','%','s','T','\0',
};

const uzone_packed_t utz_zone_defns[84] = {
// Africa/Cairo	2:00	Egypt	EE%sT
{  8,   0,   0,   0},
// Africa/Casablanca	0:00	Morocco	WE%sT
{  0,  41,   4,   5},
// Africa/Lagos	1:00	-	WAT
{  4,   0,   0,  11},
// Africa/Maputo	2:00	-	CAT
{  8,   0,   0,  15},
// Africa/Nairobi	3:00	-	EAT
{ 12,   0,   0,  19},
// Africa/Windhoek	1:00	Namibia	WA%sT
{  4,  47,   2,  23},
// America/Anchorage	-9:00	US	AK%sT
{-36,  51,   2,  29},
// America/Argentina/Buenos_Aires	-3:00	Arg	AR%sT
{-12,   0,   0,  35},
// America/Barbados	-4:00	Barb	A%sT
{-16,   0,   0,  40},
// America/Bogota	-5:00	CO	CO%sT
{-20,   0,   0,  44},
// America/Caracas	-4:00	-	VET
{-16,   0,   0,  49},
// America/Chicago	-6:00	US	C%sT
{-24,  51,   2,  53},
// America/Chihuahua	-7:00	Mexico	M%sT
{-28,  37,   2,  58},
// America/Costa_Rica	-6:00	CR	C%sT
// America/Regina	-6:00	-	CST
{-24,   0,   0,  63},
// America/Denver	-7:00	US	M%sT
{-28,  51,   2,  58},
// America/Godthab	-3:00	EU	WG%sT
{-12,  17,   2,  67},
// America/Halifax	-4:00	Canada	A%sT
{-16,  13,   2,  73},
// America/Los_Angeles	-8:00	US	P%sT
// America/Tijuana	-8:00	US	P%sT
{-32,  51,   2,  78},
// America/Manaus	-4:00	-	AMT
{-16,   0,   0,  83},
// America/Mexico_City	-6:00	Mexico	C%sT
{-24,  37,   2,  53},
// America/Montevideo	-3:00	Uruguay	UY%sT
{-12,   0,   0,  87},
// America/New_York	-5:00	US	E%sT
{-20,  51,   2,  92},
// America/Phoenix	-7:00	-	MST
{-28,   0,   0,  97},
// America/Santiago	-4:00	Chile	CL%sT
{-16,  15,   2, 101},
// America/Sao_Paulo	-3:00	Brazil	BR%sT
{-12,   6,   7, 107},
// America/St_Johns	-3:30	Canada	N%sT
{-14,  13,   2, 113},
// Asia/Almaty	5:00	-	KZT
{ 20,   0,   0, 118},
// Asia/Amman	2:00	Jordan	EE%sT
{  8,  33,   2, 122},
// Asia/Ashgabat	5:00	-	TMT
{ 20,   0,   0, 128},
// Asia/Baghdad	3:00	Iraq	A%sT
// Asia/Riyadh	3:00	-	AST
{ 12,   0,   0,  40},
// Asia/Baku	4:00	Azer	AZT
{ 16,   0,   0, 132},
// Asia/Bangkok	7:00	-	ICT
{ 28,   0,   0, 136},
// Asia/Beirut	2:00	Lebanon	EE%sT
{  8,  35,   2, 122},
// Asia/Bishkek	6:00	-	KGT
{ 24,   0,   0, 140},
// Asia/Colombo	5:30	-	SLST
{ 22,   0,   0, 144},
// Asia/Dubai	4:00	-	GST
{ 16,   0,   0, 149},
// Asia/Dushanbe	5:00	-	TJT
{ 20,   0,   0, 153},
// Asia/Hong_Kong	8:00	HK	HK%sT
{ 32,   0,   0, 157},
// Asia/Irkutsk	8:00	-	IRKT
{ 32,   0,   0, 162},
// Asia/Jakarta	7:00	-	WIB
{ 28,   0,   0, 167},
// Asia/Jerusalem	2:00	Zion	I%sT
{  8,  53,   2, 171},
// Asia/Kabul	4:30	-	AFT
{ 18,   0,   0, 176},
// Asia/Karachi	5:00	Pakistan	PK%sT
{ 20,   0,   0, 180},
// Asia/Kathmandu	5:45	-	NPT
{ 23,   0,   0, 185},
// Asia/Kolkata	5:30	-	IST
{ 22,   0,   0, 189},
// Asia/Krasnoyarsk	7:00	-	KRAT
// Asia/Novosibirsk	7:00	-	KRAT
{ 28,   0,   0, 193},
// Asia/Kuala_Lumpur	8:00	-	MYT
{ 32,   0,   0, 198},
// Asia/Magadan	11:00	-	MAGT
{ 44,   0,   0, 202},
// Asia/Omsk	6:00	-	OMST
{ 24,   0,   0, 207},
// Asia/Seoul	9:00	ROK	K%sT
{ 36,   0,   0, 212},
// Asia/Shanghai	8:00	PRC	C%sT
// Asia/Taipei	8:00	Taiwan	C%sT
{ 32,   0,   0,  63},
// Asia/Tbilisi	4:00	-	GET
{ 16,   0,   0, 216},
// Asia/Tehran	3:30	Iran	IR%sT
{ 14,  21,  12, 220},
// Asia/Tokyo	9:00	Japan	J%sT
{ 36,   0,   0, 226},
// Asia/Ulaanbaatar	8:00	Mongol	ULA%sT
{ 32,  39,   2, 230},
// Asia/Vladivostok	10:00	-	VLAT
{ 40,   0,   0, 237},
// Asia/Yakutsk	9:00	-	YAKT
{ 36,   0,   0, 242},
// Asia/Yangon	6:30	-	MMT
{ 26,   0,   0, 247},
// Asia/Yekaterinburg	5:00	-	YEKT
{ 20,   0,   0, 251},
// Asia/Yerevan	4:00	RussiaAsia	AMT
{ 16,   0,   0,  83},
// Atlantic/Azores	-1:00	EU	AZO%sT
{ -4,  17,   2, 256},
// Atlantic/Cape_Verde	-1:00	-	CVT
{ -4,   0,   0, 263},
// Atlantic/South_Georgia	-2:00	-	GST
{ -8,   0,   0, 149},
// Australia/Adelaide	9:30	AS	AC%sT
{ 38,   2,   2, 267},
// Australia/Brisbane	10:00	AQ	AE%sT
{ 40,   0,   0, 273},
// Australia/Darwin	9:30	Aus	AC%sT
{ 38,   0,   0, 278},
// Australia/Hobart	10:00	AT	AE%sT
{ 40,   4,   2, 283},
// Australia/Perth	8:00	AW	AW%sT
{ 32,   0,   0, 289},
// Australia/Sydney	10:00	AN	AE%sT
{ 40,   0,   2, 283},
// 	Etc/UTC		0	-	UTC
{  0,   0,   0, 294},
// Europe/Amsterdam	1:00	EU	CE%sT
// Europe/Belgrade	1:00	EU	CE%sT
// Europe/Berlin	1:00	EU	CE%sT
// Europe/Brussels	1:00	EU	CE%sT
// Europe/Madrid	1:00	EU	CE%sT
// Europe/Rome	1:00	EU	CE%sT
{  4,  17,   2, 298},
// Europe/Athens	2:00	EU	EE%sT
// Europe/Helsinki	2:00	EU	EE%sT
// Europe/Kiev	2:00	EU	EE%sT
{  8,  17,   2, 122},
// Europe/Istanbul	3:00	-	TRT
{ 12,   0,   0, 304},
// Europe/Kaliningrad	2:00	-	KALT
{  8,   0,   0, 308},
// Europe/London	0:00	EU	GMT
{  0,  17,   2, 313},
// Europe/Minsk	3:00	-	MSK
// Europe/Moscow	3:00	-	MSK
{ 12,   0,   0, 317},
// Europe/Samara	4:00	-	SAMT
{ 16,   0,   0, 321},
// Pacific/Auckland	12:00	NZ	NZ%sT
{ 48,  45,   2, 326},
// Pacific/Fiji	12:00	Fiji	FJ%sT
{ 48,  19,   2, 332},
// Pacific/Guam	10:00	-	ChST
{ 40,   0,   0, 338},
// Pacific/Honolulu	-10:00	-	HST
{-40,   0,   0, 343},
// Pacific/Majuro	12:00	-	MHT
{ 48,   0,   0, 347},
// Pacific/Pago_Pago	-11:00	-	SST
{-44,   0,   0, 351},
// Pacific/Tongatapu	13:00	Tonga	TO%sT
{ 52,  49,   2, 355},
};

const char utz_zone_names[1098] = {
                                            'A','d','e','l','a','i','d','e','\0',  63, // Adelaide
                                                    'A','l','m','a','t','y','\0',  26, // Almaty
                                                        'A','m','m','a','n','\0',  27, // Amman
                                        'A','m','s','t','e','r','d','a','m','\0',  70, // Amsterdam
                                        'A','n','c','h','o','r','a','g','e','\0',   6, // Anchorage
                                                    'A','n','k','a','r','a','\0',  72, // Ankara
                                            'A','s','h','g','a','b','a','t','\0',  28, // Ashgabat
                                                    'A','t','h','e','n','s','\0',  71, // Athens
                                                'A','t','l','a','n','t','a','\0',  21, // Atlanta
                                            'A','u','c','k','l','a','n','d','\0',  77, // Auckland
                                                    'A','z','o','r','e','s','\0',  60, // Azores
                                                'B','a','g','h','d','a','d','\0',  29, // Baghdad
                                                            'B','a','k','u','\0',  30, // Baku
                                                'B','a','n','g','k','o','k','\0',  31, // Bangkok
                                            'B','a','r','b','a','d','o','s','\0',   8, // Barbados
                                                'B','e','i','j','i','n','g','\0',  50, // Beijing
                                                    'B','e','i','r','u','t','\0',  32, // Beirut
                                            'B','e','l','g','r','a','d','e','\0',  70, // Belgrade
                    'B','e','l','o',' ','H','o','r','i','z','o','n','t','e','\0',  24, // Belo Horizonte
                                                    'B','e','r','l','i','n','\0',  70, // Berlin
                                                'B','i','s','h','k','e','k','\0',  33, // Bishkek
                                                    'B','o','g','o','t','a','\0',   9, // Bogota
                                                    'B','o','s','t','o','n','\0',  21, // Boston
                                'B','r','a','z','z','a','v','i','l','l','e','\0',   2, // Brazzaville
                                            'B','r','i','s','b','a','n','e','\0',  64, // Brisbane
                                            'B','r','u','s','s','e','l','s','\0',  70, // Brussels
                            'B','u','e','n','o','s',' ','A','i','r','e','s','\0',   7, // Buenos Aires
                                                        'C','a','i','r','o','\0',   0, // Cairo
                                    'C','a','p','e',' ','V','e','r','d','e','\0',  61, // Cape Verde
                                                'C','a','r','a','c','a','s','\0',  10, // Caracas
                                    'C','a','s','a','b','l','a','n','c','a','\0',   1, // Casablanca
                                                'C','h','i','c','a','g','o','\0',  11, // Chicago
                                        'C','h','i','h','u','a','h','u','a','\0',  12, // Chihuahua
                                                'C','o','l','o','m','b','o','\0',  34, // Colombo
                                    'C','o','s','t','a',' ','R','i','c','a','\0',  13, // Costa Rica
                                                    'D','a','r','w','i','n','\0',  65, // Darwin
                                                        'D','e','l','h','i','\0',  44, // Delhi
                                                    'D','e','n','v','e','r','\0',  14, // Denver
                                                        'D','u','b','a','i','\0',  35, // Dubai
                                            'D','u','s','h','a','n','b','e','\0',  36, // Dushanbe
                                                            'F','i','j','i','\0',  78, // Fiji
                                                'G','o','d','t','h','a','b','\0',  15, // Godthab
                                'G','u','a','d','a','l','a','j','a','r','a','\0',  19, // Guadalajara
                                                            'G','u','a','m','\0',  79, // Guam
                                                'H','a','l','i','f','a','x','\0',  16, // Halifax
                                                    'H','a','r','a','r','e','\0',   3, // Harare
                                            'H','e','l','s','i','n','k','i','\0',  71, // Helsinki
                                                    'H','o','b','a','r','t','\0',  66, // Hobart
                                        'H','o','n','g',' ','K','o','n','g','\0',  37, // Hong Kong
                                            'H','o','n','o','l','u','l','u','\0',  80, // Honolulu
                                                'H','o','u','s','t','o','n','\0',  11, // Houston
                        'I','n','l','a','n','d',' ','E','m','p','i','r','e','\0',  17, // Inland Empire
                                                'I','r','k','u','t','s','k','\0',  38, // Irkutsk
                                            'I','s','t','a','n','b','u','l','\0',  72, // Istanbul
                                                'J','a','k','a','r','t','a','\0',  39, // Jakarta
                                        'J','e','r','u','s','a','l','e','m','\0',  40, // Jerusalem
                                                        'K','a','b','u','l','\0',  41, // Kabul
                                'K','a','l','i','n','i','n','g','r','a','d','\0',  73, // Kaliningrad
                                                'K','a','r','a','c','h','i','\0',  42, // Karachi
                                            'K','a','t','m','a','n','d','u','\0',  43, // Katmandu
                                                            'K','i','e','v','\0',  71, // Kiev
                                'K','r','a','s','n','o','y','a','r','s','k','\0',  45, // Krasnoyarsk
                            'K','u','a','l','a',' ','L','u','m','p','u','r','\0',  46, // Kuala Lumpur
                                                    'K','u','w','a','i','t','\0',  29, // Kuwait
                                                    'L','a','h','o','r','e','\0',  42, // Lahore
                                                    'L','o','n','d','o','n','\0',  74, // London
                                'L','o','s',' ','A','n','g','e','l','e','s','\0',  17, // Los Angeles
                                                    'M','a','d','r','i','d','\0',  70, // Madrid
                                                'M','a','g','a','d','a','n','\0',  47, // Magadan
                                                    'M','a','j','u','r','o','\0',  81, // Majuro
                                                    'M','a','n','a','u','s','\0',  18, // Manaus
                                'M','e','x','i','c','o',' ','C','i','t','y','\0',  19, // Mexico City
                                                        'M','i','a','m','i','\0',  21, // Miami
                                                    'M','i','d','w','a','y','\0',  82, // Midway
                                                        'M','i','l','a','n','\0',  70, // Milan
                                                        'M','i','n','s','k','\0',  75, // Minsk
                                    'M','o','n','t','e','v','i','d','e','o','\0',  20, // Montevideo
                                                    'M','o','s','c','o','w','\0',  75, // Moscow
                                                'N','a','i','r','o','b','i','\0',   4, // Nairobi
                                            'N','e','w',' ','Y','o','r','k','\0',  21, // New York
                                'N','o','v','o','s','i','b','i','r','s','k','\0',  45, // Novosibirsk
                                                            'O','m','s','k','\0',  48, // Omsk
                                                        'P','e','r','t','h','\0',  67, // Perth
                            'P','h','i','l','a','d','e','l','p','h','i','a','\0',  21, // Philadelphia
                                                'P','h','o','e','n','i','x','\0',  22, // Phoenix
                                                'R','a','n','g','o','o','n','\0',  57, // Rangoon
                                                    'R','e','g','i','n','a','\0',  13, // Regina
                    'R','i','o',' ','d','e',' ','J','a','n','e','i','r','o','\0',  24, // Rio de Janeiro
                                                            'R','o','m','e','\0',  70, // Rome
                                                    'S','a','m','a','r','a','\0',  76, // Samara
                        'S','a','n',' ','F','r','a','n','c','i','s','c','o','\0',  17, // San Francisco
                                            'S','a','n','t','i','a','g','o','\0',  23, // Santiago
                                        'S','a','o',' ','P','a','u','l','o','\0',  24, // Sao Paulo
                                            'S','a','r','a','j','e','v','o','\0',  70, // Sarajevo
                                                        'S','e','o','u','l','\0',  49, // Seoul
                        'S','o','u','t','h',' ','G','e','o','r','g','i','a','\0',  62, // South Georgia
                                            'S','t',' ','J','o','h','n','s','\0',  25, // St Johns
                                                    'S','y','d','n','e','y','\0',  68, // Sydney
                                                    'T','a','i','p','e','i','\0',  50, // Taipei
                                                'T','b','i','l','i','s','i','\0',  51, // Tbilisi
                                                    'T','e','h','r','a','n','\0',  52, // Tehran
                                                'T','i','j','u','a','n','a','\0',  17, // Tijuana
                                                        'T','o','k','y','o','\0',  53, // Tokyo
                                        'T','o','n','g','a','t','a','p','u','\0',  83, // Tongatapu
                                'U','l','a','a','n','b','a','a','t','a','r','\0',  54, // Ulaanbaatar
                                        'U','n','i','v','e','r','s','a','l','\0',  69, // Universal
                                'V','l','a','d','i','v','o','s','t','o','k','\0',  55, // Vladivostok
            'W','a','s','h','i','n','g','t','o','n',',',' ','D','.','C','.','\0',  21, // Washington, D.C.
                                            'W','i','n','d','h','o','e','k','\0',   5, // Windhoek
                                                'Y','a','k','u','t','s','k','\0',  56, // Yakutsk
                        'Y','e','k','a','t','e','r','i','n','b','u','r','g','\0',  58, // Yekaterinburg
                                                'Y','e','r','e','v','a','n','\0',  59, // Yerevan
                                        'Z','h','e','n','g','z','h','o','u','\0',  50, // Zhengzhou
                                                                                    0
};
