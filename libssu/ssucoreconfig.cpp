/**
 * @file ssucoreconfig.cpp
 * @copyright 2013 Jolla Ltd.
 * @author Bernd Wachter <bwachter@lart.info>
 * @date 2013
 */

#include <QFile>
#include <QTextStream>
#include <QDBusConnection>

#include <getdef.h>

#include "ssucoreconfig.h"
#include "ssulog.h"

SsuCoreConfig *SsuCoreConfig::ssuCoreConfig = 0;

SsuCoreConfig *SsuCoreConfig::instance(){
  if (!ssuCoreConfig)
    ssuCoreConfig = new SsuCoreConfig();

  return ssuCoreConfig;
}

QPair<QString, QString> SsuCoreConfig::credentials(QString scope){
  QPair<QString, QString> ret;
  beginGroup("credentials-" + scope);
  ret.first = value("username").toString();
  ret.second = value("password").toString();
  endGroup();
  return ret;
}

QString SsuCoreConfig::credentialsScope(QString repoName, bool rndRepo){
  if (contains("credentials-scope"))
    return value("credentials-scope").toString();
  else
    return "your-configuration-is-broken-and-does-not-contain-credentials-scope";
}

QString SsuCoreConfig::credentialsUrl(QString scope){
  if (contains("credentials-url-" + scope))
    return value("credentials-url-" + scope).toString();
  else
    return "your-configuration-is-broken-and-does-not-contain-credentials-url-for-" + scope;
}

QString SsuCoreConfig::flavour(){
  if (contains("flavour"))
    return value("flavour").toString();
  else
    return "release";
}

int SsuCoreConfig::deviceMode(){
  if (!contains("deviceMode"))
    return Ssu::ReleaseMode;
  else
    return value("deviceMode").toInt();
}

QString SsuCoreConfig::domain(bool pretty){
  if (contains("domain")){
    // this is a workaround for upgrading existing devices to
    // Jolla sales setup. it should be removed in a few weeks
    // this should keep devices with old default domain in rnd
    // mode using the proper domain
    if (contains("default-rnd-domain") &&
        isRegistered() &&
        value("domain").toString() == "sales" &&
        (deviceMode() & Ssu::RndMode) == Ssu::RndMode)
      setValue("domain", value("default-rnd-domain"));
    //

    if (pretty)
      return value("domain").toString().replace(":", "-");
    else
      return value("domain").toString();
  } else
    return "";
}

QString SsuCoreConfig::releaseDomain() {
    if (contains("releaseDomain")) {
        return value("releaseDomain").toString();
    }

    return "";
}

bool SsuCoreConfig::isRegistered(){
  if (!contains("privateKey"))
    return false;
  if (!contains("certificate"))
    return false;
  return value("registered").toBool();
}

QDateTime SsuCoreConfig::lastCredentialsUpdate(){
  return value("lastCredentialsUpdate").toDateTime();
}

QString SsuCoreConfig::release(bool rnd){
  if (rnd)
    return value("rndRelease").toString();
  else
    return value("release").toString();
}

void SsuCoreConfig::setDeviceMode(int mode, int editMode){
  int oldMode = value("deviceMode").toInt();

  if ((editMode & Ssu::Add) == Ssu::Add){
    oldMode |= mode;
  } else if ((editMode & Ssu::Remove) == Ssu::Remove){
    oldMode &= ~mode;
  } else
    oldMode = mode;

  setValue("deviceMode", oldMode);
  sync();
}

void SsuCoreConfig::setFlavour(QString flavour){
  setValue("flavour", flavour);
  // flavour is RnD only, so enable RnD mode
  setDeviceMode(Ssu::RndMode, Ssu::Add);
  sync();
}

void SsuCoreConfig::setRelease(QString release, bool rnd){
  if (rnd) {
    setValue("rndRelease", release);
    // switch rndMode on/off when setting releases
    setDeviceMode(Ssu::RndMode, Ssu::Add);
  } else {
    setValue("release", release);
    setDeviceMode(Ssu::RndMode, Ssu::Remove);
  }
  sync();
}

void SsuCoreConfig::setDomain(QString domain){
  // - in domain messes with default section autodetection,
  // so change it to :
  setValue("domain", domain.replace("-", ":"));
  sync();
}

void SsuCoreConfig::setReleaseDomain(QString releaseDomain) {
  // Same logic as with setDomain() applies
  setValue("releaseDomain", releaseDomain.replace("-", ":"));
  sync();
}

bool SsuCoreConfig::useSslVerify(){
  if (contains("ssl-verify"))
    return value("ssl-verify").toBool();
  else
    return true;
}

QDBusConnection SsuCoreConfig::userSessionBus(){
  int uid_min = getdef_num("UID_MIN", -1);

  // For calls from valid UID we assume that they are properly logged in users.
  // If they are not the call will fail, but it's their fault.
  if (getuid() >= uid_min){
    return QDBusConnection::sessionBus();
  } else {
    // DBus security policy will prevent this beeing used by callers other
    // than root at the moment. Still do it generic in case DBus policy will
    // be extended later, and just use the usual 'DBus: THOU SHALL NOT PASS!'
    // @TODO the uid to be used should be determined using the logind API from
    //       systemd package to support multiuser systems in the future
    QString sessionBusAddress=QString("unix:path=/run/user/%1/dbus/user_bus_socket")
      .arg(uid_min);
    return QDBusConnection::connectToBus(sessionBusAddress, "userSessionBus");
  }
}
