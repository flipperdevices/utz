#!/usr/bin/env python3
""" Create tz database links for major metropolian areas that don't exist in the IANA db

eV Quirk
"""

import unicodedata
import argparse

from bs4 import BeautifulSoup
import geopy
import sys


def main():
    parser = argparse.ArgumentParser(prog="compile_tzlinks.py", description="Create tz database links for major metropolian areas that don't exist in the IANA db")
    parser.add_argument('-u', '--user', required=True, help="GeoNames username (register on https://www.geonames.org/ and enable free web service)")
    parser.add_argument('-t', '--timeout', required=False, default=30, type=int, help="network timeout (seconds)")
    args = parser.parse_args()
    geopy.geocoders.options.default_timeout = args.timeout
    geocoder = geopy.geocoders.GeoNames(username=args.user)
    links = []

    with open('vendor/wikipedia/majormetros.html') as f:
        soup = BeautifulSoup(f, features="html.parser")
        table = soup.find('table', {'class': "sortable wikitable"})
        for row in table.find_all('tr'):
            columns = row.find_all('td')
            if columns:
                metro = columns[1].find('a').text
                country = columns[2].find('a').text
                print(f"{metro}, {country}")
                try:
                    location = geocoder.geocode('%s, %s' % (metro, country))
                    if not location:  # try just searching for just the metro
                        location = geocoder.geocode('%s' % metro)
                    if location:
                        zone = geocoder.reverse_timezone((location.latitude, location.longitude)).pytz_timezone.zone
                        if zone:
                            metro = unicodedata.normalize('NFD', metro).encode('ascii', 'ignore').decode('ascii')
                            metro = metro.replace(' ', '_')
                            if zone.split('/')[-1] not in metro:
                                alias = zone.split('/')[:-1]
                                alias.append(metro)
                                links.append(('Link', zone, '/'.join(alias)))
                            else:
                                print("%s, %s already present as %s" % (metro, country, zone))
                        else:
                            print("couldn't find zone for: %s, %s" % (metro, country))
                    else:
                        print("couldn't find location for: %s, %s" % (metro, country))
                except geopy.exc.GeopyError as e:
                    print(f"geopy error: {e}")
                    return 1

    with open('majormetros', 'w') as f:
        f.write('\n'.join(['\t'.join(entry) for entry in links]))

    return 0

if __name__ == '__main__':
    ret = main()
    sys.exit(ret)
