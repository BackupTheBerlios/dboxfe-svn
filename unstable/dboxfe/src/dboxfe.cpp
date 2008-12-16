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
#include <dboxfe.h>
#include <messagebox.h>

#include <preference.h>

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
    connect( btnPreferences, SIGNAL( clicked() ), this, SLOT( preferences() ) );

    connect( listWidgetGames, SIGNAL( itemClicked( QListWidgetItem * ) ), this, SLOT( listWidgetItemClicked( QListWidgetItem * ) ) );
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
    prefrences = 0;
    configBase = 0;
    dboxfe = 0;
    profile = 0;
    profSettings = 0;

  }

  void DBoxFE::closeEvent( QCloseEvent *event ) {

    QStringList profiles;

    for ( int a = 0; a < listWidgetGames->count(); a++ ) {

      profiles.append( listWidgetGames->item( a )->text() );
    }

    configBase->xmlPreferences().setStringList( "Name", profiles, "Profile" );

    configBase->xmlPreferences().save( configBase->settingFile() );

    event->accept();
  }

  /*
   * Initial profiles and load this into a internal QListWidget
   */
  void DBoxFE::initialProfiles() {

    QString profile = QDir::homePath();
    profile.append( "/.dboxfe/profile/profile.xml" );
    
    if( QFile::exists( profile ) ) {
      if( configBase->isOldProfile( profile ) ) {

        if ( !configBase->convertProfile( profile ) ) {
  
          QMessageBox::information( this, tr( "DBoxFE" ), tr( "Can not convert old file %1" ).arg( profile ) );
          return;
        }
      }
    }

    QStringList profiles = configBase->readProfiles();
    listWidgetGames->addItems( profiles );
  }

  /*
   * Open description for selected game profile
   */
  void DBoxFE::openDescription() {

    QString description = QFileDialog::getOpenFileName( this, tr( "Open game screen capture" ), QDir::homePath(), tr( "All files (*.*)" ) );

    if ( !description.isNull() || !description.isEmpty() ) {

      QFile descFile( description );

      if ( !descFile.open( QIODevice::Text | QIODevice::ReadOnly ) ) {

        QMessageBox::information( this, tr( "DBoxFE" ), tr( "Can not read file %1" ).arg( descFile.fileName() ) );
        description = QString( "" );
        return;
      }

      QTextStream in( &descFile );

      textEditGameDescription->setHtml( in.readAll() );

      descFile.close();
      description = QString( "" );
    }
  }

  /*
   * Apply description for selected game profile
   */
  void DBoxFE::applyDescription() {

    QListWidgetItem *currentItem = listWidgetGames->currentItem();

    if ( currentItem == NULL ) {

      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No game profile was selected!" ) );
      return;
    }

    configBase->xmlPreferences().setString( "description", textEditGameDescription->toHtml(), currentItem->text() );

    configBase->xmlPreferences().setString( "image", imageFile, currentItem->text() );
    configBase->xmlPreferences().save( configBase->settingFile() );
  }

  /*
   * Clear description for selected game profile
   */
  void DBoxFE::clearDescription() {

    textEditGameDescription->clear();
    textEditGameDescription->setHtml( QString( "" ) );
    textEditGameDescription->setPlainText( QString( "" ) );
  }

  /*
   * Open screen capture for selected game profile
   */
  void DBoxFE::openScreenCapture() {

    imageFile = QFileDialog::getOpenFileName( this, tr( "caption" ), QDir::homePath(), tr( "All image files (*.bmp *.jpeg *.jpg *.png *.gif *.xpm)" ) );

    if ( !imageFile.isNull() || !imageFile.isEmpty() ) {

      QPixmap pixmap( imageFile );
      labelGameScreenshot->setPixmap( pixmap );
    }
  }

  /*
   * Apply screen capture for selected game profile
   */
  void DBoxFE::applyScreenCapture() {

    applyDescription();
  }

  /*
   * Clear screen capture for selected game profile
   */
  void DBoxFE::clearScreenCapture() {

    imageFile = QString( "" );
    labelGameScreenshot->clear();
  }

  /*
   * Start game with this configuration if this exist
   */
  void DBoxFE::startGame() {

    QListWidgetItem *currentItem = listWidgetGames->currentItem();

    if ( currentItem == NULL ) {

      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No game profile was selected!" ) );
      return;
    }

    if ( currentItem->text().isNull() || currentItem->text().isEmpty() ) {

      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No game profile was selected!" ) );
      return;
    }

    QString dosboxBinary = configBase->xmlPreferences( configBase->settingFile() ).getString( "binary", "DOSBox" );

    QString dosboxVersion = configBase->xmlPreferences( configBase->settingFile() ).getString( "version", "DOSBox" );

    if ( dosboxBinary.isNull() || dosboxBinary.isEmpty() ) {

      QMessageBox::information( this, tr( "DBoxFE" ), tr( "DOSBox binary not found." ) );
      return;
    }

    if ( dosboxVersion != "0.72" ) {

      QMessageBox::information( this, tr( "DBoxFE" ), tr( "Wrong dosbox version. Only dosbox 0.72 or higher is supported." ) );
      return;
    }

    QString profile = QDir::homePath();

    profile.append( "/.dboxfe/" + currentItem->text() + ".conf" );

    if ( !QFile::exists( profile ) ) {

      QMessageBox::information( this, tr( "DBoxFE" ), tr( "Gameconfiguration '%1' dosn't exist!" ).arg( currentItem->text() ) );
      return;
    }

    processStart( dosboxBinary, "-conf", """" + profile + """" );

    profile = QString( "" );
    dosboxBinary = QString( "" );
    dosboxVersion = QString( "" );
  }

  /*
   * Create new game profile
   */
  void DBoxFE::newGame() {

    profile->LEProfile->setText( "" );

    if ( profile->exec() == QDialog::Accepted ) {

      QString profileName = profile->LEProfile->text();

      if ( !profileName.isNull() || !profileName.isEmpty() ) {

        bool found = false;

        for ( int a = 0; a < listWidgetGames->count(); a++ ) {

          qApp->processEvents();

          QListWidgetItem *foundItem = listWidgetGames->item( a );

          if ( foundItem ) {

            if ( foundItem->text() == profileName ) {

              found = true;
              break;
            }
          }
        }

        if ( found ) {

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

  /*
   * Edit selected game profile
   */
  void DBoxFE::editGame() {

    QListWidgetItem *currentItem = listWidgetGames->currentItem();

    if ( currentItem == NULL ) {

      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No game profile was selected!" ) );
      return;
    }

    if ( currentItem->text().isNull() || currentItem->text().isEmpty() ) {

      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No game profile was selected!" ) );
      return;
    }

    QString profile = QDir::homePath();

    profile.append( "/.dboxfe/" + currentItem->text() + ".conf" );

    profSettings = new ProfileSettings();
    profSettings->setProfileName( currentItem->text() );
    profSettings->initialConfiguration( profile );

    if ( profSettings->exec() == QDialog::Accepted ) {

      delete profSettings;
      profSettings = 0;
    }
  }

  /*
   * Delete selected game profile
   */
  void DBoxFE::deleteGame() {

    QListWidgetItem *currentItem = listWidgetGames->currentItem();

    if ( currentItem == NULL ) {

      QMessageBox::information( this, tr( "DBoxFE" ), tr( "No game profile was selected!" ) );
      return;
    } else {

      messageBox->setMessageBoxTitle( tr( "Remove [ %1 ]" ).arg( currentItem->text() ) );
      messageBox->exec();
    }
  }

  /*
   * Open preference widget
   */
  void DBoxFE::preferences() {

    prefrences = 0;
    prefrences = new Preference();
    prefrences->exec();
  }

  /*
  * This signal is emitted with the specified item when a mouse button is clicked on an item in the widget.
  */
  void DBoxFE::listWidgetItemClicked( QListWidgetItem *item ) {

    labelGameScreenshot->clear();
    textEditGameDescription->clear();

    QPixmap pixmap( configBase->xmlPreferences( configBase->settingFile() ).getString( "image", item->text() ) );
    QString description = configBase->xmlPreferences( configBase->settingFile() ).getString( "description", item->text() );

    labelGameScreenshot->setPixmap( pixmap );
    textEditGameDescription->setHtml( description );

    description = QString( "" );
  }

  /*
   * This signal is emitted with the specified item when a mouse button is double clicked on an item in the QListWidget.
   */
  void DBoxFE::listWidgetItemDoubleClicked( QListWidgetItem *item ) {

    startGame();
  }

  /*
   * This signal is emitted when the command button on MessageBox is clicked.
   */
  void DBoxFE::deleteProfile( const QCommandLinkButton *commandLinkButton ) {

    if ( commandLinkButton ) {

      QListWidgetItem *currentItem = listWidgetGames->currentItem();

      if ( currentItem ) {

        if ( commandLinkButton->objectName() == "DPFL" ) {

          delete currentItem;
        } else if ( commandLinkButton->objectName() == "DPFLAF" ) {

          QString profile = QDir::homePath();
          profile.append( "/.dboxfe/" + currentItem->text() + ".conf" );

          if ( QFile::exists( profile ) ) {

            bool removed = QFile::remove( profile );

            if ( removed ) {

              delete currentItem;
            }
          }
        }
      }
    }
  }

  /*
   * Open the new game assistant dialog. It is a QProcess to start dboxfeassistant.
   */
  void DBoxFE::newGameWithAssistant() {

    QString dbfeAssistant = QString( "" );

#ifdef Q_OS_WIN32
    dbfeAssistant = QCoreApplication::applicationDirPath() + "/dboxfeassistant.exe";
#else
    dbfeAssistant = QCoreApplication::applicationDirPath() + "/dboxfeassistant";
#endif

    if ( !QFile::exists( dbfeAssistant ) ) {
      QMessageBox::information( this, tr( "DBoxFE" ), tr( "Can not start dboxfe game assistant! Binary not available." ) );
      return;
    }

    bool winHide = configBase->xmlPreferences( configBase->settingFile() ).getBool( "winHide", "DBoxFE" );

    if ( winHide ) {

      hide();
    }

    processStart( dbfeAssistant, "", "" );
  }

  /*
   * Start process
   */
  void DBoxFE::processStart( const QString& bin, const QString &param, const QString &conf ) {

    processParameter.clear();

    qApp->processEvents();

    dosbox = 0;
    dosbox = new QProcess( this );

    if ( !param.isEmpty() && !conf.isEmpty() ) {

#ifdef Q_OS_WIN32

      processParameter.append( "-noconsole" );
#endif

      processParameter.append( param );
      processParameter.append( conf );

      bool startKeyMapper = configBase->xmlPreferences( configBase->settingFile() ).getBool( "keyMapper", "DBoxFE" );

      if ( startKeyMapper ) {

        processParameter.append( "-startmapper" );
      }

#ifdef Q_OS_WIN32

      QFileInfo dboxBin( conf );

      dosbox->setWorkingDirectory( dboxBin.absolutePath() );

#endif
    }

    dosbox->start( bin, processParameter );

    connect( dosbox, SIGNAL( readyReadStandardOutput() ), this, SLOT( processOutput() ) );
    connect( dosbox, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( processFinish( int, QProcess::ExitStatus ) ) );
    connect( dosbox, SIGNAL( error( QProcess::ProcessError ) ), this, SLOT( processError( QProcess::ProcessError ) ) );
  }

  /*
   * Get output from process
   */
  void DBoxFE::processOutput() {

    while ( dosbox->canReadLine() ) {
      qDebug() << dosbox->readLine();
    }
  }

  /*
   * Process was finished and read the result from file on windows systems
   */
  void DBoxFE::processFinish( int exitCode, QProcess::ExitStatus exitStatus ) {

    show();

#ifdef Q_OS_WIN32

    QString path, outLine;
    path = QDir::homePath();
    path.append( "/.dboxfe/stdout.txt" );

    QFile outFile( path );

    if ( !outFile.open( QFile::ReadOnly | QFile::Text ) ) {
      QMessageBox::information( this, tr( "DBoxFE" ), tr( "Can not read file " ) + path );
      outFile.close();
      return;
    }

    QTextStream t( &outFile );

    while ( !t.atEnd() ) {
      qDebug() << t.readLine();
    }

    outFile.close();

#endif

    switch ( exitStatus ) {

      case QProcess::NormalExit:
        qDebug() << "Process exit normal with code: " << exitCode;
        break;

      case QProcess::CrashExit:
        qDebug() << "Process exit with crash code: " << exitCode;
        break;
    }
  }

  /*
   * A error has occured after process was finished. Display the error output.
   */
  void DBoxFE::processError( QProcess::ProcessError error ) {

    switch ( error ) {

      case QProcess::FailedToStart:
        qDebug() << tr( "dboxfe: the dosbox process failed to start" );
        break;

      case QProcess::Crashed:
        qDebug() << tr( "dboxfe: dosbox process crashed some time after starting successfully" );
        break;

      case QProcess::Timedout:
        qDebug() << tr( "dboxfe: last waitFor...() function timed out" );
        break;

      case QProcess::WriteError:
        qDebug() << tr( "dboxfe: an error occurred when attempting to write to the dosbox process" );
        break;

      case QProcess::ReadError:
        qDebug() << tr( "dboxfe: an error occurred when attempting to read from the dosbox process" );
        break;

      case QProcess::UnknownError:
        qDebug() << tr( "dboxfe: An unknown error occurred" );
        break;
    }
  }
}
