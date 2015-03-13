import subprocess
import sys
import re
import collections

# Rules for rewriting/combining authorship information
COPYRIGHT = [
    lambda author: 'Jolla Ltd.' if ('@jollamobile.com' in author or '@jolla.com' in author) else None,
]

# Rules for adding contact information (useful for grouped authors)
CONTACTS = {
    lambda author: 'Bernd Wachter <bernd.wachter@jolla.com>' if author == 'Jolla Ltd.' else None,
}

LICENSE_BLOCK_RE = r'/[*].*?This program is free software.*?\*/'

HEADER_TEMPLATE = """/**
 * ssu: Seamless Software Update
 * <<COPYRIGHT>>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 **/"""


def update(filename):
    d = subprocess.check_output(['git', 'log', '--format=%an <%ae>|%ad', '--follow', filename])

    dd = collections.defaultdict(list)
    for author, date in map(lambda x: x.split('|'), d.decode('utf-8').splitlines()):
        key = next(iter(filter(None, (c(author) for c in COPYRIGHT))), author)
        dd[key].append(date)

    def combine(s, date):
        # "Sat Feb 18 12:58:00 2012 -0800"
        s.add(date.split()[4])
        return s

    for k in dd:
        dd[k] = sorted(reduce(combine, dd[k], set()))

    def year_sort(item):
        _, years = item
        return tuple(map(int, years))

    def inject():
        for line in HEADER_TEMPLATE.splitlines():
            line = line.rstrip('\n')
            if '<<COPYRIGHT>>' in line:
                for author, years in sorted(dd.items(), key=year_sort):
                    copyright = 'Copyright (c) {years} {author}'.format(years=', '.join(years), author=author)
                    yield line.replace('<<COPYRIGHT>>', copyright)
                    for check in CONTACTS:
                        contact = check(author)
                        if contact:
                            yield ' * Contact: {}'.format(contact)
                continue
            yield line

    license = '\n'.join(inject())

    d = open(filename).read()
    if re.search(LICENSE_BLOCK_RE, d, re.DOTALL) is None:
        d = license + '\n\n' + d
    else:
        d = re.sub(LICENSE_BLOCK_RE, license, d, 0, re.DOTALL)
    open(filename, 'w').write(d)


if __name__ == '__main__':
    for filename in sys.argv[1:]:
        print 'Updating:', filename
        update(filename)
