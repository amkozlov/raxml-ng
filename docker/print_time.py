#! /usr/bin/env python3

import csv
import os

def main():

    location = 'ngtest/out/1.1.0-master/T1W1'
    with open('test_timings.csv', mode='w') as test_timings_file:
        writer = csv.writer(test_timings_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

        for dirname in os.listdir(location):
            filename = os.path.join(location, dirname, 'test.raxml.log')
            if os.path.exists(filename):
                f  = open(filename, "r")
                line = f.readline()
                while line:
                    if 'Elapsed time:' in line:
                        time = line.split()[2]
                        writer.writerow([dirname, time])
                        break
                    line = f.readline()

if __name__ == "__main__":
    main()