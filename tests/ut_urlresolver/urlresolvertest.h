/**
 * ssu: Seamless Software Update
 * Copyright (c) 2012, 2013 Jolla Ltd.
 * Contact: Bernd Wachter <bernd.wachter@jolla.com>
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
 * @file urlresolvertest.h
 * @copyright 2012 Jolla Ltd.
 * @author Bernd Wachter <bwachter@lart.info>
 * @date 2012
 */

#ifndef _URLRESOLVERTEST_H
#define _URLRESOLVERTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QHash>

#include "libssu/ssu.h"

class UrlResolverTest: public QObject {
    Q_OBJECT

  private slots:
    void initTestCase();
    void cleanupTestCase();
    void checkFlavour();
    void checkRelease();
    void checkDomain();
    void checkCleanUrl();
    void simpleRepoUrlLookup();
    void checkReleaseRepoUrls();
    void checkRegisterDevice();
    void checkSetCredentials();
    void checkStoreAuthorizedKeys();
    void checkVerifyResponse();

  private:
    Ssu ssu;
    QHash<QString, QString> rndRepos, releaseRepos;
};

#endif
