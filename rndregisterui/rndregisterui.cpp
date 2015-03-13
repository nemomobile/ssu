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
 * @file rndregisterui.cpp
 * @copyright 2012 Jolla Ltd.
 * @author Bernd Wachter <bernd.wachter@jollamobile.com>
 * @date 2012
 */

#include <QDeclarativeContext>
#include <QDir>
#include <QGraphicsObject>
#include <QApplication>

#include "rndregisterui.h"

RndRegisterUi::RndRegisterUi(QWidget *parent): QMainWindow(parent){
  ui = new QDeclarativeView;

  ui->rootContext()->setContextProperty("ssu", &ssu);

  QDir dir;
  if (dir.exists("/home/nemo/rndregisterui.qml"))
    ui->setSource(QUrl("file:///home/nemo/rndregisterui.qml"));
  else
    ui->setSource(QUrl("qrc:/resources/qml/rndregisterui.qml"));

  setCentralWidget(ui);

  QObject *item=dynamic_cast<QObject*>(ui->rootObject());
  connect(item, SIGNAL(quit()), QApplication::instance(), SLOT(quit()));
}

RndRegisterUi::~RndRegisterUi(){
  delete ui;
}
