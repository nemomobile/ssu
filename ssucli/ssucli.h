/**
 * ssu: Seamless Software Update
 * Copyright (c) 2012, 2013, 2014, 2015 Jolla Ltd.
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
 * @file ssucli.h
 * @copyright 2012 Jolla Ltd.
 * @author Bernd Wachter <bernd.wachter@jollamobile.com>
 * @date 2012
 */

#ifndef _SsuCli_H
#define _SsuCli_H

#include <QObject>
#include <QSettings>
#include <QStringList>
#include <QDebug>

#include "libssu/ssu.h"
#include "ssuproxy.h"

class SsuCli: public QObject {
    Q_OBJECT

  public:
    SsuCli();
    ~SsuCli();

  public slots:
    void run();

  private:
    Ssu ssu;
    SsuProxy *ssuProxy;
    QSettings settings;
    int state;
    void usage(QString message="");
    void uidWarning(QString message="");
    void optDomain(QStringList opt);
    void optFlavour(QStringList opt);
    void optMode(QStringList opt);
    void optModel(QStringList opt);
    void optRegister(QStringList opt);
    void optRelease(QStringList opt);
    void optRepos(QStringList opt);
    void optSet(QStringList opt);
    void optStatus(QStringList opt);
    void optUpdateCredentials(QStringList opt);
    void optUpdateRepos(QStringList opt);

    enum Actions {
      Remove  = 0,
      Add     = 1,
      Disable = 2,
      Enable  = 3,
    };

    void optModifyRepo(enum Actions action, QStringList opt);

    void optAddRepo(QStringList opt) { optModifyRepo(Add, opt); }
    void optRemoveRepo(QStringList opt) { optModifyRepo(Remove, opt); }
    void optEnableRepo(QStringList opt) { optModifyRepo(Enable, opt); }
    void optDisableRepo(QStringList opt) { optModifyRepo(Disable, opt); }

    enum State {
      Idle,
      Busy,
      UserError
    };

  private slots:
    void handleResponse();
    void handleDBusResponse();

  signals:
    void done();

};

#endif
