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
 * @file ssuurlresolvertest.cpp
 * @copyright 2013 Jolla Ltd.
 * @author Martin Kampas <martin.kampas@tieto.com>
 * @date 2013
 */

#include "ssuurlresolvertest.h"

#include <stdlib.h>
#include <zypp/media/UrlResolverPlugin.h>

#include <QtTest/QtTest>

#include "libssu/sandbox_p.h"

/**
 * @class SsuUrlResolverTest
 * @brief Tests libzypp UrlResolverPlugin plugin compatibility
 *
 * This test verifies the UrlResolverPlugin works well with installed version of libzypp.
 */

void SsuUrlResolverTest::initTestCase(){
  m_sandbox = new Sandbox(QString("%1/configroot").arg(TESTS_DATA_PATH),
      Sandbox::UseDirectly, Sandbox::ChildProcesses);
  if (!m_sandbox->activate()){
    QFAIL("Failed to activate sandbox");
  }
  setenv("LD_PRELOAD", qPrintable(QString("%1/libsandboxhook.so").arg(TESTS_PATH)), 1);
}

void SsuUrlResolverTest::cleanupTestCase(){
  delete m_sandbox;
  m_sandbox = 0;
}

void SsuUrlResolverTest::test_data(){
  QTest::addColumn<QString>("input");
  QTest::addColumn<QString>("expected");

  QTest::newRow("basic")
    << "plugin:ssu?repo=mer-core&debug&arch=i586"
    << "https://packages.testing.com//mer/i586/debug/";
}

void SsuUrlResolverTest::test(){
  QFETCH(QString, input);
  QFETCH(QString, expected);

  zypp::media::UrlResolverPlugin::HeaderList customHeaders;
  const QString resolved = QString::fromStdString(
      zypp::media::UrlResolverPlugin::resolveUrl(input.toStdString(), customHeaders).asString());

  QCOMPARE(resolved, expected);
}
