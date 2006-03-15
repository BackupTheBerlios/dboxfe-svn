/***************************************************************************
 *   Copyright (C) 2006 by Alexander Saal                                  *
 *   alex.saal@gmx.de                                                      *
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

#include "dboxfe_gamedatabase.h"

// Qt 4 Header
#include <QtCore>
#include <QtGui>

DBoxFE_GameDatabase::DBoxFE_GameDatabase(QWidget *parent, Qt::WFlags flags)
        : QWidget(parent, flags)
{
    // setup grafical user interface (gui)
    ui.setupUi( this );

    // connection
    connect( ui.btnAdd, SIGNAL( clicked() ), this, SLOT( slotAdd() ) );
    connect( ui.btnRemove, SIGNAL( clicked() ), this, SLOT( slotRemove() ) );
    connect( ui.btnChange, SIGNAL( clicked() ), this, SLOT( slotChange() ) );
    
    connect( ui.btnClose, SIGNAL( clicked() ), this, SLOT( slotClose() ) );
    connect( ui.btnSelectBin, SIGNAL( clicked() ), this, SLOT( slotSelectBinary() ) );
    
    // center the wiget on desktop screen
    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );
}

DBoxFE_GameDatabase::~DBoxFE_GameDatabase()
{}

void DBoxFE_GameDatabase::slotAdd()
{
}

void DBoxFE_GameDatabase::slotRemove()
{
}

void DBoxFE_GameDatabase::slotChange()
{
}

void DBoxFE_GameDatabase::slotSelectBinary()
{
    /*QString strDir = QFileDialog::getExistingDirectory( this, tr("Open search directory"), QDir::homePath() );
    if ( strDir.isEmpty() )
        return;

    ui.LEDirectory->setText( strDir );*/
}

void DBoxFE_GameDatabase::slotClose()
{ 
}
