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
 * @file ssusettings.h
 * @copyright 2013 Jolla Ltd.
 * @author Bernd Wachter <bwachter@lart.info>
 * @date 2013
 */

#ifndef _SSUSETTINGS_H
#define _SSUSETTINGS_H

#include <QSettings>

class SsuSettings: public QSettings {
    Q_OBJECT

    friend class SettingsTest;

  public:
    SsuSettings();
    SsuSettings(const QString &fileName, Format format, QObject *parent=0);
    /**
     * Initialize the settings object with a defaults settings file, resulting in
     * update to the configuration file if needed
     */
    SsuSettings(const QString &fileName, Format format, const QString &defaultFileName, QObject *parent=0);
    /**
     * Initialize the settings object from a settings.d structure, if needed. Only INI
     * style settings are supported in this mode.
     */
    SsuSettings(const QString &fileName, const QString &settingsDirectory, QObject *parent=0);

  private:
    QString defaultSettingsFile, settingsd;
    void merge(bool keepOld=false);
    static void merge(QSettings *masterSettings, const QStringList &settingsFiles);
    void upgrade();

};

#endif
