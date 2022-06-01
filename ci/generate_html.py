#!/usr/bin/env python3

from bs4 import BeautifulSoup as bs
import csv
import os
import sys

def write_html(data, last_data):

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

    th = soup.new_tag('th', width='40%')
    tr.append(th)
    th.append('Test name')

    th = soup.new_tag('th', width='15%')
    tr.append(th)
    th.append('Time/s')

    th = soup.new_tag('th', width='15%')
    tr.append(th)
    th.append('Change')

    th = soup.new_tag('th', width='15%')
    tr.append(th)
    th.append('LogLikelihood')

    th = soup.new_tag('th', width='15%')
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
        th.append("{:.3f}".format(data[test][0]))

        th = soup.new_tag('th')
        tr.append(th)
        if test in last_data:
            th.append("{:.3f}".format(data[test][0] - last_data[test][0]))
        else:
            th.append('N/A')

        th = soup.new_tag('th')
        tr.append(th)
        th.append("{:.3f}".format(data[test][1]))

        th = soup.new_tag('th')
        tr.append(th)
        if test in last_data:
            th.append("{:.3f}".format(data[test][1] - last_data[test][1]))
        else:
            th.append('N/A')

    html_file = open('benchmark.html', 'w')
    html_file.write(soup.prettify(formatter=None))


def write_csv(data):

    timing_file = open('last_data.csv', mode='w')
    writer = csv.writer(timing_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    for k, v in data.items():
       writer.writerow([k, v[0], v[1]])


def read_csv(filename):

    data = dict()
    if not os.path.exists(filename):
        return data

    timing_file = open(filename, mode='r')
    reader = csv.reader(timing_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    for row in reader:
        data[row[0]] = [float(row[1]), float(row[2])]
    return data


def main():

    try:
        location = sys.argv[1]
    except IndexError:
        raise SystemExit(f"Usage: {sys.argv[0]} <location>")

    current_data = dict()

    for dirname in os.listdir(location):
        filename = os.path.join(location, dirname, 'test.raxml.log')
        if os.path.exists(filename):
            f  = open(filename, "r")
            line = f.readline()
            found = 0
            likelihood = 0
            time = 0
            while line:
                if 'Final LogLikelihood:' in line:
                    likelihood = float(line.split()[2])
                    found += 1
                if 'Elapsed time:' in line:
                    time = float(line.split()[2])
                    found += 1
                if found == 2:
                    break
                line = f.readline()
            current_data[dirname] = [time, likelihood]

    last_data = read_csv('last_data.csv')
    write_html(current_data, last_data)
    write_csv(current_data)


if __name__ == "__main__":
    main()
