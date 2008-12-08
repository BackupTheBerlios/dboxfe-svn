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

#include <base.h>
#include <messagebox.h>
#include <dboxfe.h>

#include <QtGui>
#include <QtCore>

namespace asaal {

  ConfigBase *configBase;
  DBoxFE *dboxfe;
  DBoxFE::DBoxFE( QWidget *parent, Qt::WFlags flags ) : QWidget( parent, flags ) {

    setupUi( this );

    dboxfe = this;
    configBase = new ConfigBase( dboxfe );

    connect( btnOpenDescriptionText, SIGNAL( clicked() ), this, SLOT( openDescription() ) );
    connect( btnApplyDescriptionText, SIGNAL( clicked() ), this, SLOT( applyDescription() ) );
    connect( btnClearDescriptionText, SIGNAL( clicked() ), this, SLOT( clearDescription() ) );
    connect( btnOpenScreenCapture, SIGNAL( clicked() ), this, SLOT( openScreenCapture() ) );
    connect( btnApplyScreenCapture, SIGNAL( clicked() ), this, SLOT( applyScreenCapture() ) );
    connect( btnClearScreenCapture, SIGNAL( clicked() ), this, SLOT( clearScreenCapture() ) );
    connect( btnStartGame, SIGNAL( clicked() ), this, SLOT( startGame() ) );
    connect( btnNewProfile, SIGNAL( clicked() ), this, SLOT( newGame() ) );
    connect( btnEditProfile, SIGNAL( clicked() ), this, SLOT( editGame() ) );
    connect( btnDeleteProfile, SIGNAL( clicked() ), this, SLOT( deleteGame() ) );
    connect( btnAssistant, SIGNAL( clicked() ), this, SLOT( newGameWithAssistant() ) );

    connect( textEditGameDescription, SIGNAL( customContextMenuRequested( const QPoint & ) ), this, SLOT( textEditCustomContextMenuRequested( const QPoint & ) ) );
    connect( listWidgetGames, SIGNAL( itemDoubleClicked( QListWidgetItem * ) ), this, SLOT( listWidgetItemDoubleClicked( QListWidgetItem * ) ) );

    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );

    messageBox = new MessageBox( this, "DPFL", "DPFLAF" );
    connect( messageBox, SIGNAL( commandLinkButtonClicked( const QCommandLinkButton * ) ), this, SLOT( deleteProfile( const QCommandLinkButton * ) ) );

    profile = new Profile();
  }

  DBoxFE::~DBoxFE() {

    messageBox = 0;
    configBase = 0;
    dboxfe = 0;
    profile = 0;
    profSettings = 0;
    
  }

  void DBoxFE::closeEvent( QCloseEvent *event ) {

    event->accept();
  }

  void DBoxFE::initialProfiles() {

    QStringList profiles = configBase->readProfiles();
    listWidgetGames->addItems( profiles );
  }

  void DBoxFE::openDescription() {
  }

  void DBoxFE::applyDescription() {
  }

  void DBoxFE::clearDescription() {
  }

  void DBoxFE::openScreenCapture() {
  }

  void DBoxFE::applyScreenCapture() {
  }

  void DBoxFE::clearScreenCapture() {
  }

  void DBoxFE::startGame() {
  }

  void DBoxFE::newGame() {

    profile->LEProfile->setText( "" );

    if( profile->exec() == QDialog::Accepted ) {

      QString profileName = profile->LEProfile->text();
      if( !profileName.isNull() || !profileName.isEmpty() ) {

        bool found = false;

        for( int a = 0; a < listWidgetGames->count(); a++ ) {

          qApp->processEvents();

          QListWidgetItem *foundItem = listWidgetGames->item( a );
          if( foundItem ) {

            if( foundItem->text() == profileName ) {

              found = true;
              break;
            }
          }
        }

        if( found ) {

          QMessageBox::information( this, tr( "DBoxFE" ), tr( "You can't add the same game name!" ) );
          return;
        }

        QString profile = QDir::homePath();
        profile.append( "/.dboxfe/" + profileName + ".conf" );

        profSettings = new ProfileSettings();
        profSettings->setProfileName( profileName );
        profSettings->initialConfiguration( profile );

        if ( profSettings->exec() == QDialog::Accepted ) {

          QListWidgetItem *item = 0;
          item = new QListWidgetItem( listWidgetGames );
          item->setText( profileName );

          listWidgetGames->setCurrentItem( item, QItemSelectionModel::Select );
        }

        delete profSettings;
        profSettings = 0;
      }
    }
  }

  void DBoxFE::editGame() {
    
    QListWidgetItem *currentItem = listWidgetGames->currentItem();
    if( currentItem == NULL ) {
      
      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No game profile was selected!" ) );
      return;
    }

    if( currentItem->text().isNull() || currentItem->text().isEmpty() ) {
      
      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No game profile was selected!" ) );
      return;
    }
    
    QString profile = QDir::homePath();
    profile.append( "/.dboxfe/" + currentItem->text() + ".conf" );

    profSettings = new ProfileSettings();
    profSettings->setProfileName( currentItem->text() );
    profSettings->initialConfiguration( profile );

    if ( profSettings->exec() == QDialog::Accepted ) {
    }

    delete profSettings;
    profSettings = 0;
  }

  void DBoxFE::deleteGame() {

    QListWidgetItem *currentItem = listWidgetGames->currentItem();
    if( currentItem == NULL ) {
      
      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No game profile was selected!" ) );
      return;
    } else {

      messageBox->setMessageBoxTitle( tr( "Remove [ %1 ]" ).arg( currentItem->text() ) );
      messageBox->exec();
    }
  }

  void DBoxFE::textEditCustomContextMenuRequested( const QPoint &pos ) {
  }

  void DBoxFE::listWidgetItemDoubleClicked( QListWidgetItem *item ) {

    QString profile = QDir::homePath();
    profile.append( "/.dboxfe/" + item->text() + ".conf" );
    
    profSettings = new ProfileSettings();
    profSettings->setProfileName( item->text() );
    profSettings->initialConfiguration( profile );

    if ( profSettings->exec() == QDialog::Accepted ) {
    }

    delete profSettings;
    profSettings = 0;
  }

  void DBoxFE::deleteProfile( const QCommandLinkButton *commandLinkButton ) {

    if( commandLinkButton ) {

      QListWidgetItem *currentItem = listWidgetGames->currentItem();
      if( currentItem ) {

        if( commandLinkButton->objectName() == "DPFL" ) {

          delete currentItem;
        } else if( commandLinkButton->objectName() == "DPFLAF" ) {

          QString profile = QDir::homePath();
          profile.append( "/.dboxfe/" + currentItem->text() + ".conf" );
          if( QFile::exists( profile ) ) {

            bool removed = QFile::remove( profile );
            if( removed ) {

              delete currentItem;
            }
          }
        }
      }
    }
  }

  void DBoxFE::newGameWithAssistant() {

    QString dbfeAssistant = QString( "" );
    
#ifdef Q_OS_WIN32
    dbfeAssistant = QCoreApplication::applicationDirPath() + "/dboxfeassistant.exe";
#else
    dbfeAssistant = QCoreApplication::applicationDirPath() + "/dboxfeassistant";
#endif

    if( !QFile::exists( dbfeAssistant ) ) {
      QMessageBox::information( this, tr( "DBoxFE" ), tr( "Can not start dboxfe game assistant! Binary not available." ) );
      return;
    }

    // code here to start dboxfe game assistant
  } 

  void DBoxFE::processStart( const QString& bin, const QString &param, const QString &conf ) {
  }

  void DBoxFE::processOutput() {
  }

  void DBoxFE::processFinish( int exitCode, QProcess::ExitStatus exitStatus ) {
  }

  void DBoxFE::processError( QProcess::ProcessError error ) {
  }
}
