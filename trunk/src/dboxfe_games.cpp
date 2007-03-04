/*
*   Copyright (C) 2004 - 2007 by Alexander Saal <alex.saal@gmx.de>
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

#include "dboxfe_games.h"
#include "dboxfe_base.h"

// Qt 4 Header
#include <QtCore>
#include <QtGui>

DBoxFE_Game::DBoxFE_Game( QDialog *parent, Qt::WFlags flags )
        : QDialog( parent, flags )
{
    // setup grafical user interface (gui)
    setupUi( this );

    // center the wiget on desktop screen
    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );

    DB_BASE gpIni;
    QString m_file;
    m_file = QDir::homePath();
    m_file.append( "/.dboxfe/profile/games.xml" );

    //gpIni.readGameDb( m_file, twGame );
}

DBoxFE_Game::~DBoxFE_Game() {}
