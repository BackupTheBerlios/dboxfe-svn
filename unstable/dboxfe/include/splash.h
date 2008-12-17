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

#ifndef DBoxFE_SPLASH_H
#define DBoxFE_SPLASH_H

// QtGui
#include <QtGui>
#include <QtCore>
#include <Qt>

namespace asaal {

  class Splash : public QSplashScreen {
    Q_OBJECT

  public:
    Splash( const QPixmap& pixmap, Qt::WFlags f = 0 );
    virtual ~Splash();

  protected:
    void drawContents( QPainter * painter );

    public slots:
      void animate();
      void showMessage( const QString &str, int flags = Qt::AlignLeft, const QColor &color = Qt::white );

  private:
    int state;
    int progress_bar_size;
    QString m_string;

  };
}

#endif // DBoxFE_SPLASH_H
