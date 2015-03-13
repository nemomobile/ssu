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
 * @file sandboxtest.cpp
 * @copyright 2013 Jolla Ltd.
 * @author Martin Kampas <martin.kampas@tieto.com>
 * @date 2013
 */

#include "sandboxtest.h"

#include <QtTest/QtTest>

#include "libssu/sandbox_p.h"

void SandboxTest::test(){

  const QDir::Filters noHidden = QDir::AllEntries | QDir::NoDotAndDotDot;

  QCOMPARE(QDir(Sandbox::map(TESTS_DATA_PATH "/world")).entryList(noHidden, QDir::Name),
      QStringList()
      << "world-and-sandbox"
      << "world-only"
      << "world-only-to-be-copied-into-sandbox");

  QVERIFY(!QFileInfo(Sandbox::map(TESTS_DATA_PATH "/world/world-only")).isWritable());
  QCOMPARE(readAll(Sandbox::map(TESTS_DATA_PATH "/world/world-only")).trimmed(),
      QString("world/world-only"));

  QVERIFY(!QFileInfo(Sandbox::map(TESTS_DATA_PATH "/world/world-and-sandbox")).isWritable());
  QCOMPARE(readAll(Sandbox::map(TESTS_DATA_PATH "/world/world-and-sandbox")).trimmed(),
      QString("world/world-and-sandbox"));

  QVERIFY(!QFileInfo(Sandbox::map(TESTS_DATA_PATH "/world/world-only-to-be-copied-into-sandbox"))
      .isWritable());
  QCOMPARE(readAll(Sandbox::map(TESTS_DATA_PATH "/world/world-only-to-be-copied-into-sandbox"))
      .trimmed(), QString("world/world-only-to-be-copied-into-sandbox"));

  QVERIFY(!QFileInfo(Sandbox::map(TESTS_DATA_PATH "/world/sandbox-only")).exists());


  Sandbox sandbox(Sandbox::map(TESTS_DATA_PATH "/sandbox"),
      Sandbox::UseAsSkeleton, Sandbox::ThisProcess | Sandbox::ChildProcesses);
  sandbox.addWorldFiles(Sandbox::map(TESTS_DATA_PATH "/world"), QDir::AllEntries,
      QStringList() << "*-to-be-copied-into-sandbox");
  QVERIFY(sandbox.activate());


  QCOMPARE(QDir(Sandbox::map(TESTS_DATA_PATH "/world")).entryList(noHidden, QDir::Name),
      QStringList()
      << "sandbox-only"
      << "world-and-sandbox"
      << "world-only-to-be-copied-into-sandbox");

  QVERIFY(!QFileInfo(Sandbox::map(TESTS_DATA_PATH "/world/world-only")).exists());

  QVERIFY(QFileInfo(Sandbox::map(TESTS_DATA_PATH "/world/world-and-sandbox")).isWritable());
  QCOMPARE(readAll(Sandbox::map(TESTS_DATA_PATH "/world/world-and-sandbox")).trimmed(),
      QString("sandbox/world-and-sandbox"));

  QVERIFY(QFileInfo(Sandbox::map(TESTS_DATA_PATH "/world/world-only-to-be-copied-into-sandbox"))
      .isWritable());
  QCOMPARE(readAll(Sandbox::map(TESTS_DATA_PATH "/world/world-only-to-be-copied-into-sandbox"))
      .trimmed(), QString("world/world-only-to-be-copied-into-sandbox"));

  QVERIFY(QFileInfo(Sandbox::map(TESTS_DATA_PATH "/world/sandbox-only")).exists());
  QVERIFY(QFileInfo(Sandbox::map(TESTS_DATA_PATH "/world/sandbox-only")).isWritable());
  QCOMPARE(readAll(Sandbox::map(TESTS_DATA_PATH "/world/sandbox-only")).trimmed(),
      QString("sandbox/sandbox-only"));
}

QString SandboxTest::readAll(const QString &fileName){
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly)){
    qWarning("%s: Failed to open file for reading: '%s': %s", Q_FUNC_INFO, qPrintable(fileName),
        qPrintable(file.errorString()));
    return QString();
  }

  return file.readAll();
}
