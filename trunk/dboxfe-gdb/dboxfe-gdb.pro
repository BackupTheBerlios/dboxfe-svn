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
DEPENDPATH += include res src ui 3rdparty
INCLUDEPATH += include 3rdparty
RESOURCES += res/dboxfe-gdb.qrc
#CONFIG += release thread warn_on qt
CONFIG += debug thread warn_on qt
QT += sql xml network

# Project Ui files
FORMS += ui/dboxfegdb.ui
FORMS += ui/dboxfegdb_assistant.ui
FORMS += ui/dboxfegdb_dosbox.ui
FORMS += ui/dboxfegdb_template.ui
FORMS += ui/dboxfegdb_template_new.ui

# Project Translation
TRANSLATIONS += lng/dboxfe-gdb_de.ts

# Project Misc files
DISTFILES += LICENSE.GPL

# Project Header
HEADERS += include/dboxfegdb.h
HEADERS += include/dboxfegdb_assistant.h
HEADERS += include/dboxfegdb_dosbox.h
HEADERS += include/dboxfegdb_sql.h
HEADERS += include/dboxfegdb_template.h
HEADERS += include/dboxfegdb_template_new.h
HEADERS += include/dboxfegdb_xml.h

# Project Source

SOURCES += src/main.cpp
SOURCES += src/dboxfegdb_assistant.cpp
SOURCES += src/dboxfegdb.cpp
SOURCES += src/dboxfegdb_dosbox.cpp
SOURCES += src/dboxfegdb_sql.cpp
SOURCES += src/dboxfegdb_template.cpp
SOURCES += src/dboxfegdb_template_new.cpp
SOURCES += src/dboxfegdb_xml.cpp

# 3rdparty Header
HEADERS += 3rdparty/Base64.h
HEADERS += 3rdparty/XMLWriter.h
HEADERS += 3rdparty/XMLPreferences.h 

# 3rdparty Source
SOURCES += 3rdparty/Base64.cpp
SOURCES += 3rdparty/XMLPreferences.cpp
SOURCES += 3rdparty/XMLWriter.cpp 

# Unix/Linux settings
unix{
  #CONFIG += release thread warn_on qt
  CONFIG += debug thread warn_on qt
  TARGET = dboxfe-gdb
  #QMAKE_POST_LINK = strip -s bin/dboxfe-gdb
  RCC_DIR = .unix/rcc
  MOC_DIR += .unix/moc
  OBJECTS_DIR += .unix/obj
  UI_DIR += .unix/ui
}

# Windows settings
win32{
  #CONFIG += release thread warn_on qt embed_manifest_exe
  CONFIG += debug thread warn_on qt embed_manifest_exe

  RC_FILE = dboxfe-gdb.rc
  TARGET = dboxfe-gdb
  RCC_DIR = win/rcc
  MOC_DIR += win/moc
  OBJECTS_DIR += win/obj
  UI_DIR += win/ui
}
