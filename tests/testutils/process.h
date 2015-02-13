/**
 * ssu: Seamless Software Update
 * Copyright (c) 2013 Martin Kampas <martin.kampas@tieto.com>
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
 **/

/**
 * @file process.h
 * @copyright 2013 Jolla Ltd.
 * @author Martin Kampas <martin.kampas@tieto.com>
 * @date 2013
 */

#ifndef _PROCESS_H
#define _PROCESS_H

#include <QtCore/QProcess>

class Process {
  public:
    enum ExpectedResult {
      ExpectSuccess,
      ExpectFail
    };

  public:
    Process();

    QString execute(const QString &program, const QStringList &arguments,
        bool expectedResult = ExpectSuccess);
    bool hasError();
    QString fmtErrorMessage();

  private:
    QProcess m_process;
    QString m_program;
    QStringList m_arguments;
    bool m_expectFail;
    bool m_timedOut;
};

#endif
