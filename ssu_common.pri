CONFIG -= gui
QT -= gui

INCLUDEPATH *= $$PWD
DEPENDPATH *= $$PWD

CONFIG += link_pkgconfig
PKGCONFIG += libsailfishkeyprovider accounts-qt5 libsignon-qt5

# TODO: determine build dir automatically
SSU_BUILD_DIR = $$PWD/build

DESTDIR_BIN = $$SSU_BUILD_DIR/bin
DESTDIR_LIB = $$SSU_BUILD_DIR/lib

LIBS += -L$$DESTDIR_LIB
