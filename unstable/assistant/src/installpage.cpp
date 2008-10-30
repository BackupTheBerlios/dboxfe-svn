/***************************************************************************
*   Copyright (c) 2008 by Alexander Saal                                  *
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

#include <gamewizard.h>
#include <installpage.h>

#include <QtCore>
#include <QtGui>

namespace asaal {

  InstallPage::InstallPage( QWidget *parent ) : QWizardPage( parent ) {

    setupUi( this );

    setTitle( tr( "Installation option" ) );
    setSubTitle( tr( "Specify basic information about the installation for which game option are you interested." ) );

    connect( btnDosBoxFile, SIGNAL( clicked() ), this, SLOT( chooseDosBoxBinary() ) );
    connect( btnSetupFile, SIGNAL( clicked() ), this, SLOT( chooseGameSetupFile() ) );
    connect( btnInstallFolder, SIGNAL( clicked() ), this, SLOT( chooseGameInstallFolder() ) );
    connect( btnGameFile, SIGNAL( clicked() ), this, SLOT( chooseGameExecutable() ) );
    connect( btnGameFolder, SIGNAL( clicked() ), this, SLOT( choosGameFolder() ) );
    connect( groupBoxInstallSettings, SIGNAL( toggled( bool ) ), this, SLOT( gameInstallOptionChanged( bool ) ) );
    connect( groupBoxGameSettings, SIGNAL( toggled( bool ) ), this, SLOT( gameSettingOptionChanged( bool ) ) );

    registerField( "dosBoxBinary*", lineEditDosBoxBinary );
    registerField( "gameName*", lineEditGameName );
    registerField( "installSetupFile", lineEditInstallSetupFile );
    registerField( "installFolder", lineEditInstallFolder );
    registerField( "gameFile", lineEditGameFile );
    registerField( "gameFolder", lineEditGameFolder );
  }

  int InstallPage::nextId() const {

    if ( groupBoxInstallSettings->isChecked() ) {

      if ( lineEditInstallSetupFile->text() == "" ) {
        showMessage( tr( "Game Wizard" ), tr( "You must select a game setup file!" ) );
        return GameWizard::PAGE_INSTALL;
      }

      if ( lineEditInstallFolder->text() == "" ) {
        showMessage( tr( "Game Wizard" ), tr( "You must select a game installation folder!" ) );
        return GameWizard::PAGE_INSTALL;
      }

      return GameWizard::PAGE_INSTALLPROCESS;

    } else if ( groupBoxGameSettings->isChecked() ) {

      if ( lineEditGameFile->text() == "" ) {
        showMessage( tr( "Game Wizard" ), tr( "You must select a game file!" ) );
        return GameWizard::PAGE_INSTALL;
      }

      if ( lineEditGameFolder->text() == "" ) {
        showMessage( tr( "Game Wizard" ), tr( "You must select a game folder!" ) );
        return GameWizard::PAGE_INSTALL;
      }

      return GameWizard::PAGE_GRAPHIC;
    }

    return GameWizard::PAGE_INSTALL;
  }

  void InstallPage::chooseDosBoxBinary() {

    QString dosboxBinary = QFileDialog::getOpenFileName( this, tr( "Open DOSBOx binary" ), QDir::homePath(), tr( "Setup file (dosbox.exe dosbox)" ) );

    if ( !dosboxBinary.isEmpty() ) {

      QString version = checkDosBoxVersion( dosboxBinary );
      if ( version >= "0.70" && version != "UKNOWN" ) {
        lineEditDosBoxBinary->setText( dosboxBinary );

      } else {
        QMessageBox::information( 0, tr( "Game Wizard" ), tr( "Wrong dosbox version: " ) + QString( version.simplified() ).trimmed() + tr( ", i need 0.7x or higher." ) );
        return;
      }
    }
  }

  void InstallPage::chooseGameSetupFile() {

    QString gameSetupFile = QFileDialog::getOpenFileName( this, tr( "Open Gamesetup File" ), QDir::homePath(), tr( "Setup file (*.bat *.com *.exe)" ) );

    if ( !gameSetupFile.isEmpty() ) {
      lineEditInstallSetupFile->setText( gameSetupFile );
    }
  }

  void InstallPage::chooseGameInstallFolder() {

    QString gameInstallFolder = QFileDialog::getExistingDirectory( this, tr( "Open Game installation folder" ), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    if ( !gameInstallFolder.isEmpty() ) {
      lineEditInstallFolder->setText( gameInstallFolder );
    }
  }

  void InstallPage::chooseGameExecutable() {

    QString gameFile = QFileDialog::getOpenFileName( this, tr( "Open game executable" ), QDir::homePath(), tr( "Executable (*.bat *.com *.exe)" ) );

    if ( !gameFile.isEmpty() ) {
      lineEditGameFile->setText( gameFile );
    }
  }

  void InstallPage::choosGameFolder() {

    QString gameFolder = QFileDialog::getExistingDirectory( this, tr( "Open Game folder" ), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    if ( !gameFolder.isEmpty() ) {
      lineEditGameFolder->setText( gameFolder );
    }
  }

  void InstallPage::gameInstallOptionChanged( bool install ) {

    Q_UNUSED( install );
    groupBoxGameSettings->setChecked( false );
  }

  void InstallPage::gameSettingOptionChanged( bool settings ) {

    Q_UNUSED( settings );
    groupBoxInstallSettings->setChecked( false );
  }

  void InstallPage::showMessage( const QString &title, const QString &message ) const {

    QMessageBox::information( 0, title, message, QMessageBox::Ok );
  }

  QString InstallPage::checkDosBoxVersion( const QString &dosbox ) {

    qApp->processEvents();

    if ( dosbox.isNull() || dosbox.isEmpty() ) {
      return "UNKNOWN";
    }

    QFileInfo dosboxBinary( dosbox );
    QStringList m_param;

#ifdef Q_OS_WIN32

    QProcess *p = new QProcess( this );
    m_param.append( "-noconsole" );
    m_param.append( "-version" );

    p->setWorkingDirectory( dosboxBinary.absolutePath() );
    p->start( dosbox, m_param );

    while ( p->waitForFinished() ) {
      QFile dboxOutFile( dosboxBinary.absolutePath() + "/stdout.txt" );

      if ( !dboxOutFile.open( QFile::ReadOnly | QFile::Text ) ) {
        QMessageBox::information( 0, tr( "Game Wizard" ), tr( "Can not read " ) + dboxOutFile.fileName() );
        delete p;
        return "UNKOWN";
      }

      QTextStream t( &dboxOutFile );

      QString dboxVersion = t.readAll();
      QStringList version = dboxVersion.split( " " );
      QString dVersion = version.value( 2 ).replace( ",", "" );

      if ( QString( dVersion.simplified() ).trimmed().isEmpty() ) {
        QMessageBox::information( 0, tr( "Game Wizard" ), tr( "This is not a valid dosbox binary." ) );
        delete p;
        return "UNKOWN";
      }

      if ( QString( dVersion.simplified() ).trimmed() >= "0.70" ) {
        return dVersion;

      } else {
        QMessageBox::information( 0, tr( "Game Wizard" ), tr( "Wrong dosbox version: " ) + QString( dVersion.simplified() ).trimmed() + tr( ", i need 0.7x or higher." ) );
        delete p;
        return "UNKOWN";
      }
    }

    m_param.clear();

    delete p;
#else

    QProcess *p = new QProcess( this );
    p->start( dosbox, QStringList() << "-version" );

    while ( p->waitForFinished() ) {

      QString dboxVersion = p->readAll();
      QStringList version = dboxVersion.split( " " );
      QString dVersion = version.value( 2 ).replace( ",", "" );

      if ( QString( dboxVersion.simplified() ).trimmed().isEmpty() ) {
        QMessageBox::information( 0, tr( "Game Wizard" ), tr( "This is not a valid dosbox binary." ) );
        delete p;
        return "UNKOWN";
      }

      if ( QString( dboxVersion.simplified() ).trimmed() >= "0.70" ) {
        return dVersion;

      } else {
        QMessageBox::information( 0, tr( "Game Wizard" ), tr( "Wrong dosbox version: " ) + QString( dboxVersion.simplified() ).trimmed() + tr( ", i need 0.7x or higher." ) );
        delete p;
        return "UNKOWN";
      }
    }

    delete p;

#endif

    return "UNKOWN";
  }

  bool InstallPage::checkGameExectuable( const QString &executable ){

    QStringList templates;
    QString exec, execMD5, setup, setupMD5, applicationDirPath;

#ifdef Q_OS_WIN32
    applicationDirPath = QApplication::applicationDirPath() + "/templates";
#else
    applicationDirPath = "/usr/share/dboxfe/templates";
#endif

    QDir templateFolder( applicationDirPath );

    QFileInfo fi;
    const QFileInfoList fil = templateFolder.entryInfoList( QDir::Files, QDir::Name );
    QListIterator< QFileInfo > it( fil );
    QStringList lst;

    while ( it.hasNext() ) {
      fi = it.next();

      if ( fi.fileName() == "." || fi.fileName() == ".." ) {
        ;
      } else {
        if( fi.isFile() && fi.isReadable() && fi.fileName().endsWith( ".exe" ) ) {
          templates.append( fi.absoluteFilePath );
        }
      }
    }

    QProgressDialog progressDialog( tr( "Game search" ), tr( "&Cancel" ), 0, templates.size(), this );
    progressDialog.setWindowTitle( tr( "Searching game, please wait ..." ) );
    progressDialog.setWindowModality( Qt::WindowModal );

    for( int i = 0; i < templates.size(); i++ ) {
      progressDialog.setValue(i);

      if ( progressDialog.wasCanceled() ) {
        break;
      }

      QFile gameFile( templates.value( i ) );
      if( !gameFile.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        continue;
      }

      QSettings gameFileSetting( templates.value( i ), QSettings::IniFormat );
      gameFileSetting.beginGroup( "Extra" );
      exec = gameFileSetting.value( "Exe" ).toString();
      execMD5 = gameFileSetting.value( "ExeMD5" ).toString();
      setup = gameFileSetting.value( "Setup" ).toString();
      setupMD5 = gameFileSetting.value( "SetupMD5" ).toString();
      gameFileSetting.endGroup();

    }
    progress.setValue( templates.size() );
    templates.clear();
  }
}
