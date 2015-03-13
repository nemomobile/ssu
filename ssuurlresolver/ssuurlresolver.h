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
 * @file ssuurlresolver.h
 * @copyright 2012 Jolla Ltd.
 * @author Bernd Wachter <bernd.wachter@jollamobile.com>
 * @date 2012
 */

#ifndef _SsuUrlResolver_H
#define _SsuUrlResolver_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QEventLoop>
#include <QFile>

#include <iostream>
#include <zypp/PluginFrame.h>

#include "libssu/ssu.h"

// quick hack for waiting for a signal
class SignalWait: public QObject {
    Q_OBJECT
  public:
    SignalWait(){
      needRunning=1;
    }

  public slots:
    void sleep(){
      if (needRunning==1)
        loop.exec();
    }

    virtual void finished(){
      needRunning=0;
      loop.exit();
    }

  private:
    QEventLoop loop;
    int needRunning;
};

using namespace zypp;

class SsuUrlResolver: public QObject {
    Q_OBJECT

  public:
    SsuUrlResolver();

  private:
    Ssu ssu;
    void error(QString message);
    void printJournal(int priority, QString message);
    bool writeZyppCredentialsIfNeeded(QString credentialsScope);

  public slots:
    void run();

  signals:
    void done();

};

#endif
