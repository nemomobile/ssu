/**
 * ssu: Seamless Software Update
 * Copyright (c) 2012 Jolla Ltd.
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
 * @file rndregisterui.h
 * @copyright 2012 Jolla Ltd.
 * @author Bernd Wachter <bernd.wachter@jollamobile.com>
 * @date 2012
 */

#ifndef RndRegisterUi_H
#define RndRegisterUi_H

#include <QMainWindow>
#include <QtDeclarative/QDeclarativeView>

#include "libssu/ssu.h"

namespace Ui {
  class RndRegisterUi;
}

class RndRegisterUi: public QMainWindow{
    Q_OBJECT

  public:
    explicit RndRegisterUi(QWidget *parent = 0);
    ~RndRegisterUi();

  private:
    Ssu ssu;
    QDeclarativeView *ui;
};

#endif
