/***************************************************************************
*   Copyright (C) 2007-2008 by Alexander Saal                             *
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

#include <about.h>

#include <QtCore>
#include <QtGui>

namespace asaal {

  TrayIconAbout::TrayIconAbout( QWidget * parent, const QString &license ) : QWidget( parent ), m_License( license ) {

    setupUi( this );

    connect( btnAboutQt, SIGNAL( clicked() ), qApp, SLOT( aboutQt() ) );

    if( !m_License.isEmpty() || !m_License.isNull() ) {
      textEditTrayAboutLicense->setPlainText( m_License );

    } else {
      QString lic = QString( ":/license" );

      QFile licFile( lic );
      if( !licFile.open( QIODevice::ReadOnly | QIODevice::Text) ) {

        return;
      }

      QTextStream licStream( &licFile );
      lic = licStream.readAll();
      licFile.close();

      textEditTrayAboutLicense->setPlainText( lic );
    }

    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );
  }
  
  void TrayIconAbout::closeEvent( QCloseEvent *e ) {

    e->accept();
  }
}
