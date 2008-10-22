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

#include <gamewizard.h>
#include <installprocesspage.h>

#include <QtCore>
#include <QtGui>

namespace asaal {

  InstallProcessPage::InstallProcessPage( QWidget *parent ) : QWizardPage( parent ) {

    setupUi( this );

    setTitle( tr( "Installprocess" ) );
    setSubTitle( tr( "Are you ready to install then click the 'Installation' button." ) );

    connect( btnInstallGame, SIGNAL( clicked() ), this, SLOT( prepareInstallation() ) );
  }

  int InstallProcessPage::nextId() const {

    return GameWizard::PAGE_GRAPHIC;
  }

  void InstallProcessPage::prepareInstallation() {

    // Make a application thread
    qApp->processEvents();

    // Get the wizard next-button
    QAbstractButton *buttonNext = GameWizard::instance()->button( QWizard::NextButton );

    if ( buttonNext ) {

      buttonNext->setEnabled( false );
    }

    // Get dosbox binary and setup settings
    dosBoxBinary = field( "dosBoxBinary" ).toString();
    installSetupFile = field( "installSetupFile" ).toString();
    installFolder = field( "installFolder" ).toString();

    // Get installation config
    QString m_installConf = ":/install_conf";

    QFile installConf( m_installConf );

    // Open installation config
    if ( !installConf.open( QFile::ReadOnly | QFile::Text ) ) {
      QMessageBox::information( 0, tr( "Game Wizard" ), tr( "Can not read " ) + installConf.fileName() );
      return;
    }

    // Read installation config
    QTextStream installTextStream( &installConf );
    QString m_conf = installTextStream.readAll();

    QString keyboardLayout = QLocale::languageToString( QLocale::system().language() );
    if( keyboardLayout == "German" ) {
      keyboardLayout = "GR";

    } else {
      keyboardLayout = "none";
    }

    QFileInfo dvdDirectory( installSetupFile );

    m_conf.replace( "$(KEYBOARD_LAYOUT)", keyboardLayout );
    m_conf.replace( "$(DVD_CD_DIRECTORY)", dvdDirectory.absolutePath() );
    m_conf.replace( "$(INSTALLATION_DIRECTORY)", installFolder );
    m_conf.replace( "$(SETUP_EXECUTABLE)", dvdDirectory.fileName() );

    // Close install config
    installConf.flush();
    installConf.close();

    // Set real installation config for save on hard disc
    m_installConf = "";
    m_installConf = QDir::homePath();
    m_installConf.append( "/.dboxfe" );

    // create profile directory if this not exists
    QDir profileDir( m_installConf );

    if ( !profileDir.exists() ) {
      profileDir.mkpath( m_installConf );
    }

    // Append the installation config file
    m_installConf.append( "/installation.conf" );

    QFile realInstallConf( m_installConf );

    // Open real installation config
    if ( !realInstallConf.open( QFile::WriteOnly | QFile::Text ) ) {
      QMessageBox::information( 0, tr( "Game Wizard" ), tr( "Can not read " ) + realInstallConf.fileName() );
      return;
    }

    // Read real installation config
    QTextStream realInstallTextStream( &realInstallConf );

    realInstallTextStream << m_conf;

    // Close and write real install config
    realInstallTextStream.flush();
    installConf.flush();
    installConf.close();
    
    install( dosBoxBinary, "-conf", """" + realInstallConf.fileName() + """", buttonNext );
  }

  void InstallProcessPage::install( const QString& bin, const QString &param, const QString &conf, QAbstractButton *button ) {

    qApp->processEvents();

    m_installProcess = new QProcess( this );

#ifdef Q_OS_WIN32

    m_param.append( "-noconsole" );
#endif

    m_param.append( param );
    m_param.append( conf );

#ifdef Q_OS_WIN32

    QFileInfo dosboxBinary( conf );
    m_installProcess->setWorkingDirectory( dosboxBinary.absolutePath() );
#endif

    m_installProcess->start( bin, m_param );

    connect( m_installProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( processReadOutput() ) );
    connect( m_installProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( processFinish( int, QProcess::ExitStatus ) ) );
    connect( m_installProcess, SIGNAL( error( QProcess::ProcessError ) ), this, SLOT( processError( QProcess::ProcessError ) ) );

    while ( m_installProcess->waitForFinished() ) {

      if ( button ) {

        button->setEnabled( true );
      }
    }

    m_param.clear();
  }

  void InstallProcessPage::processReadOutput() {

    while ( m_installProcess->canReadLine() ) {

      m_OutputResult = m_installProcess->readLine();
      listWidgetDosBoxProcessStatus->addItem( tr( "dosbox cmd output -> " ) + m_OutputResult.mid( m_OutputResult.indexOf( ":" ) + 1 ) );
      listWidgetDosBoxProcessStatus->update();
    }
  }

  void InstallProcessPage::processFinish( int exitCode, QProcess::ExitStatus exitStatus ) {

#ifdef Q_OS_WIN32
    QString path, outLine;
    path = QDir::homePath();
    path.append( "/.dboxfe/stdout.txt" );

    QFile outFile( path );

    if ( !outFile.open( QFile::ReadOnly | QFile::Text ) ) {

      QMessageBox::information( this, tr( "Game Wizard" ), tr( "Can not read file %1" ).arg( path ) );
      outFile.close();
      return ;
    }

    QTextStream t( &outFile );

    while ( !t.atEnd() ) {

      outLine = t.readLine();
      listWidgetDosBoxProcessStatus->addItem( tr( "dosbox cmd output -> " ) + outLine.mid( outLine.indexOf( ":" ) + 1 ) );
      listWidgetDosBoxProcessStatus->update();
    }

    outFile.close();
#endif

    switch ( exitStatus ) {

      case QProcess::NormalExit:
        listWidgetDosBoxProcessStatus->addItem( tr( "dosbox: dosbox process exited normally" ) );
        break;

      case QProcess::CrashExit:
        listWidgetDosBoxProcessStatus->addItem( tr( "dosbox: dosbox process crashed on exit" ) );
        break;
    }
    
    // Now we check installation folder for correct game installation
    listWidgetDosBoxProcessStatus->addItem( tr( "dosbox: check for installation folder ..." ) );

    // code here ...
    QDir folder( installFolder );
    QFileInfo fi;
    const QFileInfoList fil = folder.entryInfoList( QDir::Files, QDir::Name );
    QListIterator< QFileInfo > it( fil );
    QStringList lst;

    while ( it.hasNext() ) {
      fi = it.next();
    
      if ( fi.fileName() == "." || fi.fileName() == ".." ) {
        ;
      } else {
        if( fi.isFile() && fi.isReadable() && fi.fileName().endsWith( ".exe" ) ) {
        }
      }
    }

    listWidgetDosBoxProcessStatus->addItem( tr( "dosbox: check for installation folder ... finish" ) );
  }

  void InstallProcessPage::processError( QProcess::ProcessError processError ) {

    switch ( processError ) {

      case QProcess::Crashed:
        listWidgetDosBoxProcessStatus->addItem( tr( "dosbox: dosbox process crashed" ) );
        break;

      case QProcess::FailedToStart:
        listWidgetDosBoxProcessStatus->addItem( tr( "dosbox: dosbox process faild to start" ) );
        break;

      case QProcess::ReadError:
        listWidgetDosBoxProcessStatus->addItem( tr( "dosbox: dosbox process read error" ) );
        break;

      case QProcess::Timedout:
        listWidgetDosBoxProcessStatus->addItem( tr( "dosbox: dosbox process timeout" ) );
        break;

      case QProcess::UnknownError:
        listWidgetDosBoxProcessStatus->addItem( tr( "dosbox: dosbox process unkown error" ) );
        break;

      case QProcess::WriteError:
        listWidgetDosBoxProcessStatus->addItem( tr( "dosbox: dosbox process write error" ) );
        break;

    }
  }
}
