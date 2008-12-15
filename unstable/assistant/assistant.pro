#/*
#*   Copyright (C) 2008 by Alexander Saal <alex.saal@gmx.de>
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
TARGET = dboxfeassistant
DEPENDPATH += include src ui resource ../3rdparty ../3rdparty/Zip ../base
INCLUDEPATH += include ui ../3rdparty ../3rdparty/Zip  ../base
RESOURCES += resource/dboxfeassistant.qrc
RESOURCES += ../resource/templates.qrc
CONFIG += debug thread warn_on qt
QT += xml

# Project Ui files
FORMS += ui/finishpage.ui
FORMS += ui/graphicpage.ui
FORMS += ui/installpage.ui
FORMS += ui/installprocesspage.ui
FORMS += ui/importexportpage.ui
FORMS += ui/miscpage.ui
FORMS += ui/settingpage.ui
FORMS += ui/soundpage.ui
FORMS += ui/welcomepage.ui

# Project Header
HEADERS += include/finishpage.h
HEADERS += include/gamewizard.h
HEADERS += include/graphicpage.h
HEADERS += include/importexportpage.h
HEADERS += include/installpage.h
HEADERS += include/installprocesspage.h
HEADERS += include/miscpage.h
HEADERS += include/settingpage.h
HEADERS += include/soundpage.h
HEADERS += include/welcomepage.h

# Project Source
SOURCES	+= src/main.cpp
SOURCES += src/finishpage.cpp
SOURCES += src/gamewizard.cpp
SOURCES += src/graphicpage.cpp
SOURCES += src/importexportpage.cpp
SOURCES += src/installpage.cpp
SOURCES += src/installprocesspage.cpp
SOURCES += src/miscpage.cpp
SOURCES += src/settingpage.cpp
SOURCES += src/soundpage.cpp
SOURCES += src/welcomepage.cpp

# 3rdparty Header
HEADERS += ../base/base.h
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

	RCC_DIR	= ../build/dboxfeassistant/unix/rcc
	MOC_DIR	+= ../build/dboxfeassistant/unix/moc
	OBJECTS_DIR += ../build/dboxfeassistant/unix/obj
	UI_DIR += ../build/dboxfeassistant/unix/ui

	LIBS += -lxml2
  LIBS += -lz 
}

# Windows settings
win32 {
	CONFIG += embed_manifest_exe
	
	RC_FILE = resource/dboxfeassistant.rc
	RCC_DIR	= ../build/dboxfeassistant/win/rcc
	MOC_DIR	+= ../build/dboxfeassistant/win/moc
	OBJECTS_DIR += ../build/dboxfeassistant/win/obj
	UI_DIR += ../build/dboxfeassistant/win/ui

	LIBS += -llibxml2
  LIBS += -lzlib
}
