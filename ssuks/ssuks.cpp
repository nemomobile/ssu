/**
 * ssu: Seamless Software Update
 * Copyright (c) 2013 Martin Kampas <martin.kampas@tieto.com>
 * Copyright (c) 2013, 2014 Jolla Ltd.
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
 * @file ssuks.cpp
 * @copyright 2013 Jolla Ltd.
 * @author Bernd Wachter <bernd.wachter@jollamobile.com>
 * @date 2013
 */

#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QTimer>
#include <QStringList>
#include <QDirIterator>

#include "ssukickstarter.h"
#include "constants.h"
#include "libssu/sandbox_p.h"

#include "ssuks.h"

void SsuKs::run(){
  QStringList arguments = QCoreApplication::arguments();
  // get rid of the binary name
  arguments.removeFirst();

  QTextStream qout(stdout);
  QTextStream qerr(stderr);
  QHash<QString, QString> repoParameters;

  if (arguments.count() == 1 &&
          (arguments.at(0) == "help" ||
           arguments.at(0) == "--help" ||
           arguments.at(0) == "-h")) {
    usage();
    return;
  }

  QString fileName;
  if (arguments.count() >= 1 && !arguments.at(0).contains("=")){
    fileName = arguments.at(0);
    arguments.removeFirst();
  }

  for (int i=0; i<arguments.count(); i++){
    if (arguments.at(i).count("=") != 1){
      qout << "Invalid flag: " << arguments.at(i) << endl;
      QCoreApplication::exit(1);
      return;
    }
    QStringList split = arguments.at(i).split("=");
    repoParameters.insert(split.at(0), split.at(1));
  }

  QString sandbox;
  Sandbox *sb;
  if (repoParameters.contains("sandbox")){
    sandbox = repoParameters.value("sandbox");
    repoParameters.remove("sandbox");

    sb = new Sandbox(sandbox, Sandbox::UseDirectly, Sandbox::ThisProcess);

    if (!sb->addWorldFiles(SSU_DATA_DIR)){
      qerr << "Failed to copy files into sandbox, using empty sandbox" << endl;
    }

    if (sb->activate())
      qerr << "Using sandbox at " << sandbox << endl;
    else {
      qerr << "Failed to activate sandbox" << endl;
      QCoreApplication::exit(1);
      return;
    }

    // force re-merge of settings
    QFile::remove(Sandbox::map(SSU_BOARD_MAPPING_CONFIGURATION));
    SsuSettings(SSU_BOARD_MAPPING_CONFIGURATION, SSU_BOARD_MAPPING_CONFIGURATION_DIR);
  }

  SsuKickstarter kickstarter;
  kickstarter.setRepoParameters(repoParameters);
  QCoreApplication::exit(!kickstarter.write(fileName));
  return;


  QCoreApplication::exit(0);
}

void SsuKs::usage(){
  QTextStream qout(stdout);
  qout << "\nUsage: ssuks <filename> <flags>" << endl
       << endl
       << "Flags are in the form key=value. 'model', 'force', 'rnd' and 'sandbox' keys have special meanings." << endl
       << "To do a kickstart for N9 do 'ssuks model=N9'" << endl
       << "To force generating a kickstart for a non-existant device add force=true" << endl
       << endl;
  qout.flush();
  QCoreApplication::exit(1);
}

int main(int argc, char** argv){
  QCoreApplication app(argc, argv);
  QCoreApplication::setOrganizationName("Jolla");
  QCoreApplication::setOrganizationDomain("http://www.jollamobile.com");
  QCoreApplication::setApplicationName("ssuks");

  QTranslator qtTranslator;
  qtTranslator.load("qt_" + QLocale::system().name(),
                    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
  app.installTranslator(&qtTranslator);

  SsuKs mw;
  QTimer::singleShot(0, &mw, SLOT(run()));

  return app.exec();
}
