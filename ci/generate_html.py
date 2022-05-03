#!/usr/bin/env python3

from bs4 import BeautifulSoup as bs
import os

def write_html(data):
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

    tbody = soup.new_tag('tbody')
    table.append(tbody)

    line_type = 'odd'
    for name, time in data:

        tr = soup.new_tag('tr', **{'class':line_type})
        tbody.append(tr)

        line_type = 'even' if line_type == 'odd' else 'odd'

        th = soup.new_tag('th')
        tr.append(th)
        th.append(name)

        th = soup.new_tag('th')
        tr.append(th)
        th.append(time)

    html_file = open('benchmark.html', 'w')
    html_file.write(soup.prettify(formatter=None))


def main():

    data = []
    location = '../ngtest/out/1.1.0-master/T1W1'

    for dirname in os.listdir(location):
        filename = os.path.join(location, dirname, 'test.raxml.log')
        if os.path.exists(filename):
            f  = open(filename, "r")
            line = f.readline()
            while line:
                if 'Elapsed time:' in line:
                    time = line.split()[2]
                    data.append([dirname, time])
                    break
                line = f.readline()

    write_html(data)


if __name__ == "__main__":
    main()
