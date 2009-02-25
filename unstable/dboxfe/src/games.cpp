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

#include <games.h>

#include <QtGui>
#include <QtCore>
#include <QtXml>

/**
 * \brief Namespace asaal
 */

namespace asaal {

  Games::Games( QWidget *parent, Qt::WFlags flags ) : QDialog( parent, flags ) {

    setupUi( this );

    mExecutable = QString( "" );

    connect( btnGameExecutable, SIGNAL( clicked() ), this, SLOT( gameExecutable() ) );
    connect( btnOk, SIGNAL( clicked() ), this, SLOT( gameAccept() ) );

    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );
  }

  Games::~Games() {
  }

  void Games::closeEvent( QCloseEvent *e ) {

    e->accept();
  }
  
  void Games::initalGames() {

    treeWidgetGames->clear();

#ifdef Q_OS_WIN32
    QDir templateDir( QApplication::applicationDirPath() + "/templates" );
#else
    QDir templateDir( QDir::homePath() + "/.dboxfe/templates" );
#endif


    QStringList entryList = templateDir.entryList( QDir::Files );
    
    if( entryList.isEmpty() || entryList.count() <= 0 ) {

      return;
    }
    
    foreach( QString entry, entryList ) {
      
      qApp->processEvents();
      
      QFile profFile( templateDir.path() + "/" + entry );
      if( !profFile.open( QIODevice::ReadOnly | QIODevice::Text ) ) {

        return;
      }
      
      QSettings *profSettings = new QSettings( templateDir.path() + "/" + entry, QSettings::IniFormat );
      
          
      profSettings->beginGroup( "Extra" );
      QString executable = profSettings->value( "Exe" ).toString();
      profSettings->endGroup();

      profSettings->beginGroup( "ExtraInfo" );
      QString name = profSettings->value( "Name" ).toString();
      QString genre = profSettings->value( "Genre" ).toString();
      QString publisher = profSettings->value( "Publisher" ).toString();
      profSettings->endGroup();

      QTreeWidgetItem *item = new QTreeWidgetItem( treeWidgetGames );
      item->setText( 0, executable );
      item->setText( 1, name );
      item->setText( 2, genre );
      item->setText( 3, publisher );

      profSettings = 0;
      delete profSettings;
    }
  }

  void Games::gameAccept() {

    QTreeWidgetItem *item = treeWidgetGames->currentItem();

    if ( item ) {

      mExecutable = item->text( 0 );
    } else if ( !lineEditExecutable->text().isNull() || !lineEditExecutable->text().isEmpty() ) {

      mExecutable = lineEditExecutable->text();
    } else {

      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No game executable was selected!" ) );
      return;
    }

    QDialog::accept();
  }

  void Games::gameExecutable() {

    mExecutable = QFileDialog::getOpenFileName( this, tr( "Open game executable" ), QDir::homePath(),  "All (*.exe *.com *.bat);;Exe (*.exe);;COM (*.com);;BIN (*.bat)" );

    if ( mExecutable.isEmpty() || mExecutable.isNull() ) {
      return;
    }

    lineEditExecutable->setText( mExecutable );
  }
}
