/**
 * ssu: Seamless Software Update
 * Copyright (c) 2013, 2014, 2015 Jolla Ltd.
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
 * @file ssufeaturemanager.cpp
 * @copyright 2013 Jolla Ltd.
 * @author Bernd Wachter <bwachter@lart.info>
 * @date 2013
 */

#include <QStringList>
#include <QRegExp>
#include <QDirIterator>

#include "ssudeviceinfo.h"
#include "ssufeaturemanager.h"
#include "ssucoreconfig.h"
#include "ssulog.h"
#include "ssuvariables.h"
#include "ssu.h"

#include "../constants.h"

#ifndef SSU_FEATURE_CONFIGURATION
/// Path to the main ssu configuration file
#define SSU_FEATURE_CONFIGURATION "/var/cache/ssu/features.ini"
#endif

#ifndef SSU_FEATURE_CONFIGURATION_DIR
/// Path to the main ssu configuration file
#define SSU_FEATURE_CONFIGURATION_DIR "/usr/share/ssu/features.d"
#endif

SsuFeatureManager::SsuFeatureManager(): QObject() {
  featureSettings = new SsuSettings(SSU_FEATURE_CONFIGURATION, SSU_FEATURE_CONFIGURATION_DIR);
}


// @TODO - allow enabling/disabling features
//       - export feature file for mic through ssu-ks
//       - add feature header in ssu-ks
//
//    all features have a list of repositories in the repos key
//    if there are enabled/disabled features, check the repos keys from all enabled features
//    and only enable the repositories from those
QStringList SsuFeatureManager::repos(bool rndRepo, int filter){
  QStringList r;
  QStringList keys;
  SsuCoreConfig *settings = SsuCoreConfig::instance();

  // @TODO features currently can't be blacklisted, but just ignoring user filter
  // is still the best way atm
  if (filter == Ssu::UserFilter)
    return r;

  QString repoHeader = QString("repositories-%1/")
    .arg(rndRepo ? "rnd" : "release");

  // take the global groups
  featureSettings->beginGroup("repositories");
  r.append(featureSettings->allKeys());
  featureSettings->endGroup();

  // and override with rnd/release specific groups
  featureSettings->beginGroup(repoHeader);
  r.append(featureSettings->allKeys());
  featureSettings->endGroup();

  r.removeDuplicates();
  return r;
}

QString SsuFeatureManager::url(QString repo, bool rndRepo){
  QString repoHeader = QString("repositories-%1/")
    .arg(rndRepo ? "rnd" : "release");

  if (featureSettings->contains(repoHeader + repo))
    return featureSettings->value(repoHeader + repo).toString();
  else if (featureSettings->contains("repositories/" + repo))
    return featureSettings->value("repositories/" + repo).toString();

  return "";
}
