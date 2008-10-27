#/*
#*   Copyright (C) 2007 - 2008 by Alexander Saal <alex.saal@gmx.de>
#*
#*   This program is free software; you can redistribute it and/or modify
#*   it under the terms of the GNU General Public License as published by
#*   the Free Software Foundation; either version 2 of the License, or (at
#*   your option) any later version.
#*
#*   This program is distributed in the hope that it will be useful, but
#*   WITHOUT ANY WARRANTY; without even the implied warranty of
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#*   GNU General Public License for more details.
#*
#*   You should have received a copy of the GNU General Public License
#*   along with this program; if not, write to the Free Software Foundation,
#*   Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#*/

# Qt 4 Settings
TEMPLATE = app
DESTDIR = ../bin
DEPENDPATH += include src resource ../3rdparty
INCLUDEPATH += include ../3rdparty
RESOURCES += resource/tray.qrc
CONFIG += debug thread warn_on qt
QT += xml

# Project Ui files
FORMS += ui/about.ui

# Project Header
HEADERS += include/tray.h

# Project Source
SOURCES += src/main.cpp
SOURCES += src/tray.cpp

# 3rdparty Header
HEADERS += ../3rdparty/Base64.h
HEADERS += ../3rdparty/XMLWriter.h
HEADERS += ../3rdparty/XMLPreferences.h 

# 3rdparty Source
SOURCES += ../3rdparty/Base64.cpp
SOURCES += ../3rdparty/XMLPreferences.cpp
SOURCES += ../3rdparty/XMLWriter.cpp 

# Unix/Linux settings
unix{
  TARGET = dboxfetray
  #QMAKE_POST_LINK = strip -s bin/dboxfetray
  RCC_DIR = ../build/dboxfetray/unix/rcc
  MOC_DIR += ../build/dboxfetray/unix/moc
  OBJECTS_DIR += ../build/dboxfetray/unix/obj
  UI_DIR += ../build/dboxfetray/unix/ui
}

# Windows settings
win32{
  CONFIG += embed_manifest_exe

  TARGET = dboxfetray
  RC_FILE = resource/tray.rc
  RCC_DIR = ../build/dboxfetray/win/rcc
  MOC_DIR += ../build/dboxfetray/win/moc
  OBJECTS_DIR += ../build/dboxfetray/win/obj
  UI_DIR += ../build/dboxfetray/win/ui
}
