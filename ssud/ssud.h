/**
 * ssu: Seamless Software Update
 * Copyright (c) 2013 Jolla Ltd.
 * Contact: Bernd Wachter <bernd.wachter@jolla.com>
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
 * @file ssud.h
 * @copyright 2013 Jolla Ltd.
 * @author Bernd Wachter <bwachter@lart.info>
 * @date 2013
 */

#ifndef _SSUD_H
#define _SSUD_H

#include <QObject>
#include <QString>
#include <QTimer>

#include "libssu/ssu.h"

class Ssud: public QObject {
    Q_OBJECT

  public:
    Ssud(QObject *parent=NULL);
    virtual ~Ssud();

  public slots:
    /* device info */
    QString deviceModel();
    QString deviceFamily();
    QString deviceUid();
    QString deviceVariant();
    QString displayName(int type);
    /* credential management */
    bool isRegistered();
    void registerDevice(const QString &username, const QString &password);
    void unregisterDevice();
    /* repository management */
    int deviceMode();
    void setDeviceMode(int mode);
    QString flavour();
    void setFlavour(const QString &release);
    QString release(bool rnd);
    void setRelease(const QString &release, bool rnd);
    void modifyRepo(int action, const QString &repo);
    void addRepo(const QString &repo, const QString &url);
    void updateRepos();

    bool error();
    QString lastError();

    void quit();


  signals:
    void done();
    void credentialsChanged();
    void registrationStatusChanged();

  private:
    Ssu ssu;
    static const char *SERVICE_NAME;
    static const char *OBJECT_PATH;
    QTimer autoclose;

    enum Actions {
      Remove  = 0,
      Add     = 1,
      Disable = 2,
      Enable  = 3,
    };
};

#endif
