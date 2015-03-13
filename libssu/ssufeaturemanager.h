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
 * @file ssufeaturemanager.h
 * @copyright 2013 Jolla Ltd.
 * @author Bernd Wachter <bwachter@lart.info>
 * @date 2013
 */

#ifndef _SSUFEATUREMANAGER_H
#define _SSUFEATUREMANAGER_H

#include <QObject>
#include <QHash>
#include <QStringList>

#include "ssu.h"
#include "ssusettings.h"

class SsuFeatureManager: public QObject {
    Q_OBJECT

  public:
    SsuFeatureManager();
    QStringList repos(bool rndRepo, int filter=Ssu::NoFilter);
    QString url(QString repo, bool rndRepo);

  private:
    SsuSettings *featureSettings;
};

#endif
