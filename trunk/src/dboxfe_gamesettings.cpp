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

#include "dboxfe_gamesettings.h"

// 3rdparty library
#include "XMLPreferences.h"

// Qt 4 Header
#include <QtCore>
#include <QtGui>

DBoxFE_GameSettings::DBoxFE_GameSettings( QWidget *parent, Qt::WFlags flags ) : QWidget( parent, flags )
{
    ui.setupUi( this );

    // connection
    connect( ui.btnAdd, SIGNAL( clicked() ), this, SLOT( slotAdd() ) );
    connect( ui.btnRemove, SIGNAL( clicked() ), this, SLOT( slotRemove() ) );
    connect( ui.btnChange, SIGNAL( clicked() ), this, SLOT( slotChange() ) );
    connect( ui.btnPreview, SIGNAL( clicked() ), this, SLOT( slotPreview() ) );
    connect( ui.btnSave, SIGNAL( clicked() ), this, SLOT( slotSave() ) );
    connect( ui.btnImage, SIGNAL( clicked() ), this, SLOT( slotImage() ) );

    // center the application on desktop screen
    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );
}

DBoxFE_GameSettings::~DBoxFE_GameSettings()
{}

void DBoxFE_GameSettings::closeEvent( QCloseEvent *e )
{
    e->accept();
}

void DBoxFE_GameSettings::slotAdd()
{}

void DBoxFE_GameSettings::slotRemove()
{}

void DBoxFE_GameSettings::slotChange()
{}

void DBoxFE_GameSettings::slotPreview()
{}

void DBoxFE_GameSettings::slotSave()
{}

void DBoxFE_GameSettings::slotImage()
{}
