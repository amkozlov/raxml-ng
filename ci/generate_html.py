#!/usr/bin/env python3

from bs4 import BeautifulSoup as bs
import csv
import os

def write_html(data, last_timing):

    header = '<h1>Benchmark</h1>'
    parser = 'lxml'
    soup = bs(header, parser)
    head = soup.new_tag('head')
    soup.html.insert(0, head)

    style = soup.new_tag('link', **{'href':'style.css', 'rel':'stylesheet', 'type':'text/css'})
    head.insert(0, style)

    table = soup.new_tag('table', **{'class':'list', 'id':'regression_tests'})
    soup.html.body.append(table)

    thead = soup.new_tag('thead')
    table.append(thead)

    tr = soup.new_tag('tr')
    thead.append(tr)

    th = soup.new_tag('th', width='70%')
    tr.append(th)
    th.append('Test name')

    th = soup.new_tag('th')
    tr.append(th)
    th.append('Time/s')

    th = soup.new_tag('th')
    tr.append(th)
    th.append('Change')

    tbody = soup.new_tag('tbody')
    table.append(tbody)

    line_type = 'odd'
    for test in data:

        tr = soup.new_tag('tr', **{'class':line_type})
        tbody.append(tr)

        line_type = 'even' if line_type == 'odd' else 'odd'

        th = soup.new_tag('th')
        tr.append(th)
        th.append(test)

        th = soup.new_tag('th')
        tr.append(th)
        th.append(data[test])

        th = soup.new_tag('th')
        tr.append(th)
        if test in last_timing:
            th.append(str(float(data[test]) - float(last_timing[test])))
        else:
            th.append('N/A')

    html_file = open('benchmark.html', 'w')
    html_file.write(soup.prettify(formatter=None))


def write_csv(data):

    timing_file = open('last_timing.csv', mode='w')
    writer = csv.writer(timing_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    writer.writerows(data.items())


def read_csv(filename):

    data = dict()
    if not os.path.exists(filename):
        return data

    timing_file = open(filename, mode='r')
    reader = csv.reader(timing_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    for row in reader:
        data[row[0]] = row[1]
    return data


def main():

    location = '../ngtest/out/1.1.0-master/T1W1'
    current_timing = dict()

    for dirname in os.listdir(location):
        filename = os.path.join(location, dirname, 'test.raxml.log')
        if os.path.exists(filename):
            f  = open(filename, "r")
            line = f.readline()
            while line:
                if 'Elapsed time:' in line:
                    time = line.split()[2]
                    current_timing[dirname] = time
                    break
                line = f.readline()

    last_timing = read_csv('last_timing.csv')
    write_html(current_timing, last_timing)
    write_csv(current_timing)


if __name__ == "__main__":
    main()
