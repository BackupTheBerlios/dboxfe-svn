#/*
#*   Copyright (C) 2004/05/06 by Alexander Saal <alex.saal@gmx.de>
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
 
TEMPLATE = app
DESTDIR = bin
DEPENDPATH += include res src ui 3rdparty
INCLUDEPATH += include 3rdparty
RESOURCES += res/dboxfe.qrc
CONFIG += debug thread warn_on qt
QT += xml network

FORMS += ui/dboxfe.ui
FORMS += ui/about.ui
FORMS += ui/profile.ui
FORMS += ui/profilewizard.ui
FORMS += ui/gamepreview.ui
FORMS += ui/gamesettings.ui

FORMS += ui/games.ui

TRANSLATIONS += lng/dboxfe_de.ts
TRANSLATIONS += lng/dboxfe_en.ts 
		
DISTFILES += ChangeLog
DISTFILES += LICENSE.GPL
	     
HEADERS += include/dboxfe.h
HEADERS += include/dboxfe_about.h
HEADERS += include/dboxfe_profile.h
HEADERS += include/dboxfe_profilewizard.h
HEADERS += include/dboxfe_games.h
HEADERS += include/dboxfe_gamesettings.h
HEADERS += include/dboxfe_base.h
HEADERS += include/dboxfe_splash.h
HEADERS += 3rdparty/Base64.h
HEADERS += 3rdparty/XMLWriter.h
HEADERS += 3rdparty/XMLPreferences.h 

SOURCES += src/dboxfe.cpp
SOURCES += src/dboxfe_about.cpp
SOURCES += src/dboxfe_profile.cpp
SOURCES += src/dboxfe_profilewizard.cpp
SOURCES += src/dboxfe_games.cpp
SOURCES += src/dboxfe_gamesettings.cpp
SOURCES += src/dboxfe_base.cpp
SOURCES += src/dboxfe_splash.cpp
SOURCES += src/main.cpp
SOURCES += 3rdparty/Base64.cpp
SOURCES += 3rdparty/XMLPreferences.cpp
SOURCES += 3rdparty/XMLWriter.cpp 
	   
unix{
  TARGET = dboxfe
  #QMAKE_POST_LINK = strip -s bin/dboxfe
  RCC_DIR = .unix/rcc
  MOC_DIR += .unix/moc
  OBJECTS_DIR += .unix/obj
  UI_DIR += .unix/ui
}

win32{
  RC_FILE = dboxfe.rc
  TARGET = dboxfe
  RCC_DIR = win/rcc
  MOC_DIR += win/moc
  OBJECTS_DIR += win/obj
  UI_DIR += win/ui
}
