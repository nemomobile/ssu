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
 * @file repomanagertest.cpp
 * @copyright 2013 Jolla Ltd.
 * @author Martin Kampas <martin.kampas@tieto.com>
 * @date 2013
 */

#include "repomanagertest.h"

#include <QtTest/QtTest>

#include "libssu/ssucoreconfig.h"
#include "libssu/ssurepomanager.h"

void RepoManagerTest::testSettings(){
  SsuCoreConfig *const coreConfig = SsuCoreConfig::instance();
  SsuRepoManager repoManager;

  repoManager.add("repo1", "http://repo1");
  QCOMPARE(coreConfig->value("repository-urls/repo1").toString(), QString("http://repo1"));
  QVERIFY(!coreConfig->value("enabled-repos").toStringList().contains("repo1"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo1"));

  repoManager.enable("repo1");
  QCOMPARE(coreConfig->value("repository-urls/repo1").toString(), QString("http://repo1"));
  QVERIFY(!coreConfig->value("enabled-repos").toStringList().contains("repo1"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo1"));

  repoManager.add("repo1");
  QCOMPARE(coreConfig->value("repository-urls/repo1").toString(), QString("http://repo1"));
  QVERIFY(coreConfig->value("enabled-repos").toStringList().contains("repo1"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo1"));

  repoManager.disable("repo1");
  QCOMPARE(coreConfig->value("repository-urls/repo1").toString(), QString("http://repo1"));
  QVERIFY(coreConfig->value("enabled-repos").toStringList().contains("repo1"));
  QVERIFY(coreConfig->value("disabled-repos").toStringList().contains("repo1"));

  repoManager.enable("repo1");
  QCOMPARE(coreConfig->value("repository-urls/repo1").toString(), QString("http://repo1"));
  QVERIFY(coreConfig->value("enabled-repos").toStringList().contains("repo1"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo1"));

  repoManager.add("repo2", "http://repo2");
  QCOMPARE(coreConfig->value("repository-urls/repo1").toString(), QString("http://repo1"));
  QVERIFY(coreConfig->value("enabled-repos").toStringList().contains("repo1"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo1"));
  QCOMPARE(coreConfig->value("repository-urls/repo2").toString(), QString("http://repo2"));
  QVERIFY(!coreConfig->value("enabled-repos").toStringList().contains("repo2"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo2"));

  repoManager.disable("repo2");
  QCOMPARE(coreConfig->value("repository-urls/repo1").toString(), QString("http://repo1"));
  QVERIFY(coreConfig->value("enabled-repos").toStringList().contains("repo1"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo1"));
  QCOMPARE(coreConfig->value("repository-urls/repo2").toString(), QString("http://repo2"));
  QVERIFY(!coreConfig->value("enabled-repos").toStringList().contains("repo2"));
  QVERIFY(coreConfig->value("disabled-repos").toStringList().contains("repo2"));

  repoManager.enable("repo2");
  QCOMPARE(coreConfig->value("repository-urls/repo1").toString(), QString("http://repo1"));
  QVERIFY(coreConfig->value("enabled-repos").toStringList().contains("repo1"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo1"));
  QCOMPARE(coreConfig->value("repository-urls/repo2").toString(), QString("http://repo2"));
  QVERIFY(!coreConfig->value("enabled-repos").toStringList().contains("repo2"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo2"));

  repoManager.add("repo2");
  QCOMPARE(coreConfig->value("repository-urls/repo1").toString(), QString("http://repo1"));
  QVERIFY(coreConfig->value("enabled-repos").toStringList().contains("repo1"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo1"));
  QCOMPARE(coreConfig->value("repository-urls/repo2").toString(), QString("http://repo2"));
  QVERIFY(coreConfig->value("enabled-repos").toStringList().contains("repo2"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo2"));

  repoManager.remove("repo1");
  QVERIFY(!coreConfig->contains("repository-urls/repo1"));
  QVERIFY(!coreConfig->value("enabled-repos").toStringList().contains("repo1"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo1"));
  QCOMPARE(coreConfig->value("repository-urls/repo2").toString(), QString("http://repo2"));
  QVERIFY(coreConfig->value("enabled-repos").toStringList().contains("repo2"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo2"));

  repoManager.remove("repo2");
  QVERIFY(!coreConfig->contains("repository-urls/repo1"));
  QVERIFY(!coreConfig->value("enabled-repos").toStringList().contains("repo1"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo1"));
  QVERIFY(!coreConfig->contains("repository-urls/repo2"));
  QVERIFY(!coreConfig->value("enabled-repos").toStringList().contains("repo2"));
  QVERIFY(!coreConfig->value("disabled-repos").toStringList().contains("repo2"));
}
