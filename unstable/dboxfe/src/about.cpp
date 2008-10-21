/***************************************************************************
*   Copyright (C) 2004-2008 by Alexander Saal                             *
*   alex.saal@gmx.de                                                      *
*                                                                         *
*   File: ${filename}.${extension}                                        *
*   Desc: ${description}                                                  *
*                                                                         *
*   This file is part of DBoxFE - DOSBox Front End                        *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include <QtGui>
#include <QtCore>

#include <about.h>

namespace asaal {

  About::About( QWidget *parent, Qt::WFlags flags ) : QWidget( parent, flags ) {

    setupUi( this );

    connect( btnAboutQt, SIGNAL( clicked() ), qApp, SLOT( aboutQt() ) );

    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );

    QFile thx( QString::fromUtf8( ":/files/thanks" ) );

    if ( !thx.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
      return ;
    }

    QTextStream thxIn( &thx );

    QString lineThx = thxIn.readAll();
    readThxFile( lineThx );
    thx.close();

    QFile lic( QString::fromUtf8( ":/files/LICENSE.GPL" ) );

    if ( !lic.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
      return ;
    }

    QTextStream LicIn( &lic );

    QString lineLic = LicIn.readAll();
    readLicFile( lineLic );
    lic.close();
  }

  About::~About() {}

  void About::readThxFile( const QString &thxFile ) {
    TEThanks->setPlainText( thxFile );
  }

  void About::readLicFile( const QString &licFile ) {
    TELicense->setPlainText( licFile );
  }
}
