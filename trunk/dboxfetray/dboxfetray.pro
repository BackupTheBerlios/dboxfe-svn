#/*
#*   Copyright (C) 2007 by Alexander Saal <alex.saal@gmx.de>
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
DEPENDPATH += include res ui src ../3rdparty
INCLUDEPATH += include ../3rdparty
RESOURCES += res/dboxfetray.qrc
CONFIG += debug thread warn_on qt
QT += xml

# Project Ui files
FORMS += ui/dboxfetrayabout.ui

# Project Translation
# TRANSLATIONS += res/dboxfetray_de.ts
# TRANSLATIONS += res/dboxfetray_en.ts 

# Project Misc files
DISTFILES += ChangeLog
DISTFILES += LICENSE.GPL

# Project Header
HEADERS += include/dboxfetray.h

# Project Source
SOURCES += src/main.cpp
SOURCES += src/dboxfetray.cpp

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
  RCC_DIR = .unix/rcc
  MOC_DIR += .unix/moc
  OBJECTS_DIR += .unix/obj
  UI_DIR += .unix/ui
}

# Windows settings
win32{
  RC_FILE = res/dboxfetray.rc
  TARGET = dboxfetray
  RCC_DIR = win/rcc
  MOC_DIR += win/moc
  OBJECTS_DIR += win/obj
  UI_DIR += win/ui
}
