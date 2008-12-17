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
 *   the Free Software Foundation; either version 3 of the License, or     *
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

#include "splash.h"

#include <QtCore>
#include <QtGui>
#include <Qt>


namespace asaal {

  Splash::Splash( const QPixmap& pixmap, Qt::WFlags f ) : QSplashScreen( pixmap, f ) {

    QTimer * timer = new QTimer( this );
    QObject::connect( timer, SIGNAL( timeout() ), this, SLOT( animate() ) );
    timer->start( 150 );

    state = 0;
    progress_bar_size = 3;
  }


  Splash::~Splash() {}


  void Splash::animate() {

    state = (( state + 1 ) % ( 2 * progress_bar_size - 1 ) );
    repaint();
  }


  void Splash::showMessage( const QString &str, int flags, const QColor &color ) {

    QSplashScreen::showMessage( str, flags, color );
    animate();
    m_string = str;
  }


  void Splash::drawContents( QPainter* painter ) {

    int position;
    QColor base_color( 255, 255, 255 );

    painter->setPen( Qt::NoPen );
    painter->setBrush( QColor( 255, 255, 255 ) );
    painter->drawEllipse( 11, 7, 9, 9 );
    painter->drawEllipse( 22, 7, 9, 9 );
    painter->drawEllipse( 33, 7, 9, 9 );

    for ( int i = 0; i < progress_bar_size; i++ ) {
      position = ( state + i ) % ( 2 * progress_bar_size - 1 );
      painter->setBrush( QColor( base_color.red() - 18 * i, base_color.green() - 10 * i, base_color.blue() - 28 * i ) );

      if ( position < 3 )
        painter->drawEllipse( 11 + position * 11, 7, 9, 9 );
    }

    painter->setPen( QColor( 255, 255, 255 ) );

    QFont fnt( "Monospace" );
    fnt.setPointSize( 9 );
    painter->setFont( fnt );

    if ( m_string.length() > 40 ) {
      m_string.truncate( 39 );
      m_string += "...";
    }

    painter->drawText( 50, 16, m_string );
  }
}
