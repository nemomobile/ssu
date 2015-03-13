/**
 * ssu: Seamless Software Update
 * Copyright (c) 2013 Jolla Ltd.
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
 * @file ssukickstarter.h
 * @copyright 2013 Jolla Ltd.
 * @author Bernd Wachter <bwachter@lart.info>
 * @date 2013
 */

#ifndef _SSUKICKSTARTER_H
#define _SSUKICKSTARTER_H

#include <QObject>
#include <QSettings>
#include <QHash>

#include "libssu/ssudeviceinfo.h"
#include "libssu/ssu.h"

class SsuKickstarter {
  public:
    SsuKickstarter();
    void setRepoParameters(QHash<QString, QString> parameters);
    bool write(QString kickstart="");

    enum ScriptletFlags {
      /// Chroot is not useful, but helps in making the code more readable
      Chroot         = 0,
      NoChroot       = 0x1,
      DeviceSpecific = 0x2,
    };

  private:
    QHash<QString, QString> repoOverride;
    Ssu ssu;
    bool rndMode;
    QString deviceModel;
    QStringList commands();
    /// read a command section from file system
    QStringList commandSection(const QString &section, const QString &description="");
    QStringList packagesSection(QString name);
    QString replaceSpaces(const QString &value);
    QStringList repos();
    QStringList scriptletSection(QString name, int flags=Chroot);
};

#endif
