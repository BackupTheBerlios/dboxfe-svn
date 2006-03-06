/***************************************************************************
 *   Copyright (C) 2006 by Alexander Saal                                  *
 *   alex.saal@gmx.de                                                      *
 *                                                                         *
 *   Original code provide by KDevelop3 SplashSreen                        *
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

#include "dboxfe_splash.h"

// QtGui
#include <QtGui/QFont>
#include <QtGui/QColor>
#include <QtGui/QPixmap>

// QtCore
#include <QtCore/QTimer>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <Qt>


DBoxFE_Splash::DBoxFE_Splash(const QPixmap& pixmap, Qt::WFlags f) : QSplashScreen(pixmap, f)
{
    QTimer *timer = new QTimer( this );
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(150);

    state = 0;
    progress_bar_size = 3;
}


DBoxFE_Splash::~DBoxFE_Splash()
{}


void DBoxFE_Splash::animate()
{
    state = ((state + 1) % (2*progress_bar_size-1));
    repaint();
}


void DBoxFE_Splash::showMessage( const QString &str, int flags, const QColor &color)
{
    QSplashScreen::showMessage(str,flags,color);
    animate();
    m_string = str;
}


void DBoxFE_Splash::drawContents (QPainter* painter)
{
    int position;
    QColor base_color (255,255,255);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255,255,255));
    painter->drawEllipse(51,7,9,9);
    painter->drawEllipse(62,7,9,9);
    painter->drawEllipse(73,7,9,9);
    
    for (int i=0; i < progress_bar_size; i++)
    {
        position = (state+i)%(2*progress_bar_size-1);
        painter->setBrush(QColor(base_color.red()-18*i, base_color.green()-10*i, base_color.blue()-28*i));
        if (position < 3)
            painter->drawEllipse(51+position*11,7,9,9);
    }

    painter->setPen(QColor(255,255,255));
    QFont fnt("Verdena");
    fnt.setPointSize(12);
    painter->setFont(fnt);

    if (m_string.length() > 40)
    {
        m_string.truncate(39);
        m_string += "...";
    }
    painter->drawText(90, 16, m_string);

}
