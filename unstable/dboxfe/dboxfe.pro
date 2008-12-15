#/*
#*   Copyright (C) 2004 - 2008 by Alexander Saal <alex.saal@gmx.de>
#*
#*   This program is free software; you can redistribute it and/or modify
#*   it under the terms of the GNU General Public License as published by
#*   the Free Software Foundation; either version 3 of the License, or (at
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
DESTDIR	= ../bin
TARGET = dboxfe
DEPENDPATH += include src ui ../3rdparty ../3rdparty/Zip ../base
INCLUDEPATH += include ui ../3rdparty ../3rdparty/Zip ../base
RESOURCES += ../resource/dboxfe.qrc
RESOURCES += ../resource/templates.qrc
CONFIG += debug thread warn_on qt
QT += xml network

# Project Ui files
FORMS += ui/about.ui
FORMS += ui/dboxfe.ui
FORMS += ui/preference.ui
FORMS += ui/profile.ui
FORMS += ui/profilesettings.ui

# Project Misc files
DISTFILES += ../resource/thanks
DISTFILES += ../resource/LICENSE.GPL

# Project Header
HEADERS += include/about.h
HEADERS	+= include/dboxfe.h
HEADERS += include/preference.h
HEADERS	+= include/profile.h
HEADERS	+= include/profilesettings.h
HEADERS	+= include/splash.h

# Project Source
SOURCES += src/about.cpp
SOURCES	+= src/dboxfe.cpp
SOURCES	+= src/main.cpp
SOURCES += src/preference.cpp
SOURCES	+= src/profile.cpp
SOURCES	+= src/profilesettings.cpp
SOURCES	+= src/splash.cpp

# 3rdparty Forms
FORMS += ../base/messagebox.ui

# 3rdparty Header
HEADERS += ../base/base.h
HEADERS	+= ../base/messagebox.h
HEADERS	+= ../3rdparty/base64.h
HEADERS += ../3rdparty/md5hash.h
HEADERS	+= ../3rdparty/xmlpreferences.h
HEADERS	+= ../3rdparty/xmlpreferences_p.h
HEADERS	+= ../3rdparty/xmlwriter.h
HEADERS	+= ../3rdparty/xmlwriter_p.h
HEADERS += ../3rdparty/unzip.h
HEADERS += ../3rdparty/unzip_p.h
HEADERS += ../3rdparty/zipentry_p.h
HEADERS += ../3rdparty/zip.h
HEADERS += ../3rdparty/zip_p.h

# 3rdparty Source
SOURCES += ../base/base.cpp
SOURCES	+= ../base/messagebox.cpp
SOURCES	+= ../3rdparty/base64.cpp
SOURCES += ../3rdparty/md5hash.cpp
SOURCES	+= ../3rdparty/xmlpreferences.cpp
SOURCES	+= ../3rdparty/xmlwriter.cpp
SOURCES += ../3rdparty/unzip.cpp
SOURCES += ../3rdparty/zip.cpp

# Unix/Linux settings
unix {
  DEPENDPATH += /usr/include/libxml2
  INCLUDEPATH += /usr/include/libxml2

	RCC_DIR	= ../build/dboxfe/unix/rcc
	MOC_DIR	+= ../build/dboxfe/unix/moc
	OBJECTS_DIR += ../build/dboxfe/unix/obj
	UI_DIR += ../build/dboxfe/unix/ui
	LIBS += -lxml2
	LIBS += -lz
}

# Windows settings
win32 {
	CONFIG += embed_manifest_exe
	RC_FILE = ../resource/dboxfe.rc
	RCC_DIR	= ../build/dboxfe/win/rcc
	MOC_DIR	+= ../build/dboxfe/win/moc
	OBJECTS_DIR += ../build/dboxfe/win/obj
	UI_DIR += ../build/dboxfe/win/ui
	LIBS += -llibxml2
	LIBS += -lzlib
}
