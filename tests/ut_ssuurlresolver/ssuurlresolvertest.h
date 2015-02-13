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
 * @file ssuurlresolvertest.h
 * @copyright 2013 Jolla Ltd.
 * @author Martin Kampas <martin.kampas@tieto.com>
 * @date 2013
 */

#ifndef _SSUURLRESOLVERTEST_H
#define _SSUURLRESOLVERTEST_H

#include <QObject>

class Sandbox;

class SsuUrlResolverTest: public QObject {
    Q_OBJECT

  public:
    SsuUrlResolverTest(): m_sandbox(0) {}

  private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_data();
    void test();

  private:
    Sandbox *m_sandbox;
};

#endif
