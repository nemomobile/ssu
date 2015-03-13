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
 * @file main.cpp
 * @copyright 2012 Jolla Ltd.
 * @author Martin Kampas <martin.kampas@tieto.com>
 * @date 2012
 */

#include <QtTest/QtTest>

#include "libssu/sandbox_p.h"
#include "repomanagertest.h"

int main(int argc, char **argv){
  Sandbox sandbox(QString("%1/configroot").arg(TESTS_DATA_PATH),
      Sandbox::UseAsSkeleton, Sandbox::ThisProcess);
  if (!sandbox.activate()){
    qFatal("Failed to activate sandbox");
  }

  RepoManagerTest repomanagerTest;

  if (QTest::qExec(&repomanagerTest, argc, argv))
    return 1;

  return 0;
}
