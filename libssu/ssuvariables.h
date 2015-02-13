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
 * @file ssuvariables.h
 * @copyright 2013 Jolla Ltd.
 * @author Bernd Wachter <bwachter@lart.info>
 * @date 2013
 */

#ifndef _SSUVARIABLES_H
#define _SSUVARIABLES_H

#include <QObject>
#include <QHash>

#include "ssusettings.h"

class SsuVariables: public QObject {
    Q_OBJECT

  public:
    SsuVariables();
    /**
     * Return a default variable section, if exists, or an empty string.
     *
     * To identify the default section the section name gets split at '-', and
     * the first token (or second token for "var-" sections) replaced with
     * "default". You should therefore avoid "-" in section names.
     */
    static QString defaultSection(SsuSettings *settings, QString section);
    /**
     * Resolve a whole string, containing several variables. Variables inside variables are allowed
     */
    static QString resolveString(QString pattern, QHash<QString, QString> *variables, int recursionDepth=0);
    /**
     * Resolve variables; variable can be passed as %(var) or var
     */
    static QString resolveVariable(QString variable, QHash<QString, QString> *variables);
    /**
     * Set the settings object to use
     */
    void setSettings(SsuSettings *settings);
    /*
     * Return the settings object used
     */
    SsuSettings *settings();
    /**
     * Return a variable from the given variable section. 'var'- is automatically
     * prepended to the section name if not specified already. Recursive search
     * through several variable sections (specified in the section) is supported,
     * returned will be the last occurence of the variable.
     */
    QVariant variable(QString section, const QString &key);
    static QVariant variable(SsuSettings *settings, QString section, const QString &key);
    /**
     * Return the requested variable section, recursively looking up all variable
     * sections referenced inside with the 'variable' keyword. 'var-' is automatically
     * prepended to the section names of included variable sections, but not for
     * the parent section.
     *
     * Variables starting with _ are treated as local variables and are ignored.
     * The special key 'local' may contain a section-specific stringlist with
     * additional keys which should be treated local.
     *
     * This function tries to identify a default configuration section, and merges
     * the default section with the requested section.
     */
    void variableSection(QString section, QHash<QString, QString> *storageHash);
    static void variableSection(SsuSettings *settings, QString section,
                                QHash<QString, QString> *storageHash);

  private:
    static void readSection(SsuSettings *settings, QString section,
                            QHash<QString, QString> *storageHash, int recursionDepth,
                            bool logOverride=true);
    static QVariant readVariable(SsuSettings *settings, QString section, const QString &key,
                                int recursionDepth, bool logOverride=true);
    SsuSettings *m_settings;
};

#endif
