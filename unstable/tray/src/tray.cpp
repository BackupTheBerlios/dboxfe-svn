/***************************************************************************
*   Copyright (C) 2007-2008 by Alexander Saal                             *
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

#include <tray.h>
#include <XMLPreferences.h>

#include <QtGui>
#include <QtCore>

namespace asaal {

  TrayIcon::TrayIcon() {

    trayIconMenu = new QMenu( this );	
    trayIcon = new QSystemTrayIcon( this );

    createMenu();

    trayIcon->setContextMenu( trayIconMenu );
    trayIcon->setIcon( QIcon( QString::fromUtf8( ":/dboxfe_image" ) ) );
    trayIcon->setToolTip( "DBoxFE - TrayIcon " + getAppVersion() );
    trayIcon->show();

    setWindowIcon( QIcon( QString::fromUtf8( ":/dboxfe_image" ) ) );
    setWindowTitle( getAppTitel() );

    update = new QTimer( this );
    connect( update, SIGNAL( timeout() ), this, SLOT( reloadMenu() ) );
    update->thread()->setPriority( QThread::NormalPriority );
    update->start( 15000 );
  }


  void TrayIcon::setVisible( bool visible ) {

    visible = false;
    QWidget::setVisible( visible );
  }

  void TrayIcon::closeEvent( QCloseEvent *e ) {

    hide();
    e->ignore();
  }

  void TrayIcon::createMenu() {

    QAction *infoAction = new QAction( getAppTitel(), this );
    infoAction->setEnabled( false );

    trayIconMenu->addAction( infoAction );
    trayIconMenu->addSeparator();

    m_file = QDir::homePath();
    m_file.append( "/.dboxfe/profile/profile.xml" );

    XMLPreferences settGP( "DBoxFE", "Alexander Saal" );
    settGP.setVersion( getAppVersion() );
    settGP.load( m_file );

    /* Get the preferences from dboxfe profile */
    QStringList sList = settGP.getStringList( "Profile", "Name" );
    dosbox = settGP.getString( "DOSBox", "binary" );

    /* Add dynamical menu entries of gameprofiles */
    for ( int i = 0; i < sList.size(); i++ ) {
      qApp->processEvents();

      trayAction = new QAction( sList.value( i ), this );
      connect( trayAction, SIGNAL( triggered() ), this, SLOT( startGame() ) );
      trayIconMenu->addAction( trayAction );
    }

    /* Create action after profile menus */
    trayIconMenu->addSeparator();

    QAction *dboxfeAction = new QAction( "&DBoxFE", this );
    connect( dboxfeAction, SIGNAL( triggered() ), this, SLOT( startdboxfe() ) );

    QAction *quitAction = new QAction( tr( "&Quit" ), this );
    connect( quitAction, SIGNAL( triggered() ), qApp, SLOT( quit() ) );

    /* Create trayicon now and set the context menu */
    trayIconMenu->addAction( dboxfeAction );
    trayIconMenu->addAction( quitAction );
  }

  void TrayIcon::reloadMenu() {
    update->stop();

    trayIconMenu->clear();
    createMenu();

    update->start( 10000 );
  }

  void TrayIcon::startGame() {

    QAction *action = qobject_cast< QAction* >( sender() );
    QString gProfile = QDir::homePath() + "/.dboxfe/" + action->text() + ".conf";

    if ( dosbox.isEmpty() || dosbox.isNull() ) {
      QMessageBox::information( this, getAppTitel(), tr( "Can not start dosbox, no dosbox binary was selected.\nPlease choose dosbox binary." ) );
      return;
    }

    start( dosbox, "-conf", """" + gProfile + """" );
  }

  void TrayIcon::start( const QString& bin, const QString &param, const QString &conf ) {

    m_DosBoxProcess = new QProcess( this );

#ifdef Q_OS_WIN32
    m_param.append( "-noconsole" );
#endif

    m_param.append( param );
    m_param.append( conf );

#ifdef Q_OS_WIN32
    QFileInfo dboxBin( conf );
    m_DosBoxProcess->setWorkingDirectory( dboxBin.absolutePath() );
#endif

    m_DosBoxProcess->start( bin, m_param );

    m_param.clear();
  }

  void TrayIcon::startdboxfe() {

    QString dbfeBin;
    m_ProcessDboxfe = new QProcess( this );

#ifdef Q_OS_WIN32
    dbfeBin = QCoreApplication::applicationDirPath() + "/dboxfe.exe";
#else
    dbfeBin = QCoreApplication::applicationDirPath() + "/dboxfe";
#endif

    m_ProcessDboxfe->start( dbfeBin, QStringList() );
  }
}
