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

#include "dboxfe_base.h"
#include "dboxfe_profilewizard.h"

#include <QtGui/QDialog>
#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QDesktopWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>

#include <QtCore/QRect>

DBoxFE_ProfileWizard::DBoxFE_ProfileWizard(QDialog *parent, Qt::WFlags flags)
        : QDialog(parent, flags)
{
    // setup grafical user interface (gui)
    ui.setupUi( this );

    // connection
    connect( ui.btnBack, SIGNAL( clicked() ), this, SLOT( slotBack() ) );
    connect( ui.btnNext, SIGNAL( clicked() ), this, SLOT( slotNext() ) );
    connect( ui.btnHelp, SIGNAL( clicked() ), this, SLOT( slotHelp() ) );
    connect( ui.btnAbort, SIGNAL( clicked() ), this, SLOT( slotAbort() ) );
    connect( ui.btnSelectDir, SIGNAL( clicked() ), this, SLOT( slotSelectDir() ) );
    connect( ui.btnSearch, SIGNAL( clicked() ), this, SLOT( slotSearch() ) );

    // center the wiget on desktop screen
    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );
}

DBoxFE_ProfileWizard::~DBoxFE_ProfileWizard()
{}

/*void DBoxFE_ProfileWizard::slotAdd()
{
    if ( ui.LEProfile->text().isEmpty() )
    {
        QMessageBox::information( this, "DOSBox Front End", "Please enter a profile name." );
    }
    else
    {
        QDialog::accept();
    }
}*/

void DBoxFE_ProfileWizard::slotBack()
{
}

void DBoxFE_ProfileWizard::slotNext()
{
}

void DBoxFE_ProfileWizard::slotHelp()
{
}

void DBoxFE_ProfileWizard::slotAbort()
{
}

void DBoxFE_ProfileWizard::slotSelectDir()
{
    QString strDir = QFileDialog::getExistingDirectory( this, tr("Open search directory"), QDir::homePath() );
    if ( strDir.isEmpty() )
        return;

    ui.LEDirectory->setText( strDir );
}

void DBoxFE_ProfileWizard::slotSearch()
{
    DB_BASE base;

    QString path = ui.LEDirectory->text();
    QStringList files;

    if ( path.isEmpty() )
        return;

    base.findFiles( path, ui.lwGames, ui.pBarSearch );
    //base.showFiles( files, ui.lwGames);
}
