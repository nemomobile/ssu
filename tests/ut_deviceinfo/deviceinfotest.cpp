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
 * @file deviceinfotest.cpp
 * @copyright 2013 Jolla Ltd.
 * @author Martin Kampas <martin.kampas@tieto.com>
 * @date 2013
 */

#include "deviceinfotest.h"

#include <QtTest/QtTest>

#include "libssu/ssudeviceinfo.h"

void DeviceInfoTest::testAdaptationVariables(){
  SsuDeviceInfo deviceInfo("N950");
  QHash<QString, QString> variables;
  QHash<QString, QString> variablesExpected;
  variablesExpected["adaptation"] = "n950-n9";
  variablesExpected["foo-n9"] = "foo-n9-val";
  variablesExpected["foo-n950-n9"] = "foo-n950-n9-val";

  QString repoName = deviceInfo.adaptationVariables("adaptation1", &variables);

  QCOMPARE(variables, variablesExpected);
  QCOMPARE(repoName, QString("adaptation"));
}

void DeviceInfoTest::testDeviceUid(){
  QVERIFY2(!SsuDeviceInfo().deviceUid().isEmpty(), "No method to get device UID on this platform");
}

void DeviceInfoTest::testVariableSection(){
  SsuDeviceInfo deviceInfo;

  QHash<QString, QString> fooVars;
  QHash<QString, QString> fooVarsExpected;
  fooVarsExpected["foo1"] = "foo1Val";
  fooVarsExpected["foo2"] = "foo2Val";

  deviceInfo.variableSection("foo", &fooVars);

  QCOMPARE(fooVars, fooVarsExpected);

  QHash<QString, QString> barVars;
  QHash<QString, QString> barVarsExpected;
  barVarsExpected["bar1"] = "bar1Val";
  barVarsExpected["bar2"] = "bar2Val";

  deviceInfo.variableSection("bar", &barVars);

  QCOMPARE(barVars, barVarsExpected);

  QHash<QString, QString> bazVars;
  QHash<QString, QString> bazVarsExpected;
  bazVarsExpected["foo1"] = "foo1Val";
  bazVarsExpected["foo2"] = "foo2Val";
  bazVarsExpected["bar1"] = "bar1Val";
  bazVarsExpected["bar2"] = "bar2Val";

  deviceInfo.variableSection("baz", &bazVars);

  QCOMPARE(bazVars, bazVarsExpected);
}

void DeviceInfoTest::testValue(){
  SsuDeviceInfo deviceInfo("N950");
  QCOMPARE(deviceInfo.value("family").toString(), QString("n950-n9"));
  QCOMPARE(deviceInfo.value("adaptation-repos").toStringList(),
      QString("n9xx-common,n950-n9").split(','));
  QCOMPARE(deviceInfo.value("foo").toString(), QString("n950-foo"));
}
