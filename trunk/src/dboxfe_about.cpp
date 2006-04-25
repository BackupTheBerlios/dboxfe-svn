/*
*   Copyright (C) 2004/05/06 by Alexander Saal <alex.saal@gmx.de>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <QtGui>
#include <QtCore>

#include "daboxfe_about.h"

DBoxFE_About::DBoxFE_About( QWidget *parent, Qt::WFlags flags )
        : QWidget( parent, flags ) {
    
    ui.setupUi( this );
    
    connect( ui.btnAboutQt, SIGNAL( clicked() ), qApp, SLOT( aboutQt() ) );
    
    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );

}

DBoxFE_About::~DBoxFE_About() {}

void DBoxFE_About::readThxFile( const QString &thxFile ) {
}

void DBoxFE_About::readLicFile( const QString &licFile ) {
}
