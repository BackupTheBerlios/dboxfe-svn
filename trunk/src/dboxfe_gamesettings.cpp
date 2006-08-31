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

#include "dboxfe_base.h"
#include "dboxfe_images.h"
#include "dboxfe_gamefile.h"
#include "dboxfe_gamesettings.h"
#include "dboxfe_gamepreview.h"

// 3rdparty library
#include "XMLPreferences.h"

// Qt 4 Header
#include <QtGui>
#include <QtCore>

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
    connect( ui.twGameSettings, SIGNAL( itemClicked( QTreeWidgetItem*, int ) ), this, SLOT( slotItemClicked( QTreeWidgetItem*, int ) ) );

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
{
    QTreeWidgetItem * qwtItem = new QTreeWidgetItem( ui.twGameSettings );
    if ( !ui.LEGame->text().isEmpty() ) {
        qwtItem->setText( 0, ui.LEGame->text() );
    } else {
        QMessageBox::information( this, "DBox Front End", "Enter a valid game name." );
        return ;
    }

    if ( !ui.cbxGameCategory->currentText().isEmpty() ) {
        qwtItem->setText( 1, ui.cbxGameCategory->currentText() );
    } else {
        QMessageBox::information( this, "DBox Front End", "Choose a category for the game." );
        return ;
    }

    if ( !ui.LEGameDeveloper->text().isEmpty() )
        qwtItem->setText( 2, ui.LEGameDeveloper->text() );
    else
        qwtItem->setText( 2, "" );

    if ( !ui.LEGameCompatibility->text().isEmpty() )
        qwtItem->setText( 4, ui.LEGameCompatibility->text() );
    else
        qwtItem->setText( 4, "" );

	if ( ui.LEGamYear->isEnabled() ) {
		if ( !ui.LEGamYear->text().isEmpty() ){
			qwtItem->setText( 3, ui.LEGamYear->text() );
		} else {
			qwtItem->setText( 3, "" );
		}
	}        
}

void DBoxFE_GameSettings::slotRemove()
{
    QTreeWidgetItem * qwtItem = ui.twGameSettings->currentItem();
    if ( qwtItem != NULL )
        delete qwtItem;
    else
        QMessageBox::information( this, "DBox Front End", "No item was selected." );
}

void DBoxFE_GameSettings::slotChange()
{
    QTreeWidgetItem * selectedItem = ui.twGameSettings->currentItem();
    if ( selectedItem != NULL ) {
    }
}

void DBoxFE_GameSettings::slotPreview()
{
	DBoxFE_GameFile *dbfe_gf = new DBoxFE_GameFile();
	dbfe_gf->dbfe_gs = this;
	dbfe_gf->show();
	dbfe_gf->loadGameFile( "http://dosbox.sourceforge.net/game_database.xml?begaming_website_session=c715af45518f8e4dea01bd4900d5d14e" );

	//DB_BASE gbBase;
	//gbBase.readGameDb("D:\\Projekte\\cplusplus\\dboxfe\\bin\\game_database.xml", NULL, this->ui.twGameSettings );
}

void DBoxFE_GameSettings::slotSave()
{
    /*
                m_file = QDir::homePath();
        m_file.append( "/.dboxfe/images/gamesettings.xml" );
     
        XMLPreferences gamesettings( "DBoxFE", "Alexander Saal" );
        gamesettings.setVersion( "v0.1.2" );
                        QListWidgetItem * qlwItem = new QListWidgetItem( qlw );
                        qlwItem->setText( fi.baseName() );
        gamesettings.setStringList( "Gamesettings", "imagefiles", lstTmp );
        gamesettings.save( m_file );
    */
    DB_BASE gbBase;
    QString imageDir;
    QStringList imageList;

    imageDir = QDir::homePath();
    imageDir.append( "/.dboxfe/images" );

    DBoxFE_Image * dbfe_image = new DBoxFE_Image();

    if ( dbfe_image->exec() == QDialog::Accepted ) {
        //	QListWidgetItem *qlwItem = dbfe_image->ui.lwImage->currentItem();
    }
}

void DBoxFE_GameSettings::slotImage()
{
    QTreeWidgetItem * item = ui.twGameSettings->currentItem();
    if ( item != NULL ) {
        QString imageDir;
        QStringList imageList, lstTmp;

        DB_BASE gbBase;

        imageDir = QDir::homePath();
        imageDir.append( "/.dboxfe/images" );

        imageList = gbBase.loadImage( imageDir );

        DBoxFE_Image * dbfe_image = new DBoxFE_Image();

        for ( int x = 0; x < imageList.size(); x++ ) {
            lstTmp = imageList.value( x ).split( ";" );

            QListWidgetItem *qlwItem = new QListWidgetItem( dbfe_image->ui.lwImage );
            qlwItem->setText( lstTmp.value( 0 ) );

            lstTmp.clear();
        }

        if ( dbfe_image->exec() == QDialog::Accepted ) {
			// TODO .... DBoxFE_Image ....
		}
	}
    else {
        QMessageBox::information( this, "DBox Front End", "No item was selected." );
    }
}

void DBoxFE_GameSettings::slotItemClicked( QTreeWidgetItem* item, int column )
{
    if ( item != NULL ) {
        ui.LEGame->setText( item->text( 0 ) );
        ui.cbxGameCategory->setCurrentIndex( ui.cbxGameCategory->findText( item->text( 1 ), Qt::MatchExactly | Qt::MatchCaseSensitive ) );
        ui.LEGameDeveloper->setText( item->text( 2 ) );
        ui.LEGameCompatibility->setText( item->text( 4 ) );
        ui.LEGamYear->setText( item->text( 3 ) );
    } else {
        return;
    }
}
