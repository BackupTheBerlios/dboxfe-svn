/*
*   Copyright (C) 2007 by Alexander Saal <alex.saal@gmx.de>
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

#include <QtGui>
#include <QtCore>

#include "dboxfetray.h"

#include "XMLPreferences.h"

DBoxFE_TrayIcon::DBoxFE_TrayIcon()
{
	dbfe_trayIconMenu = new QMenu( this );	
	dbfe_trayIcon = new QSystemTrayIcon( this );

	createMenu();

	dbfe_trayIcon->setContextMenu( dbfe_trayIconMenu );
	dbfe_trayIcon->setIcon( QIcon( QString::fromUtf8( ":/dboxfetray.png" ) ) );
	dbfe_trayIcon->setToolTip( "DBoxFE - TrayIcon v0.1.3 (SVN)" );
	dbfe_trayIcon->show();

	setWindowIcon( QIcon( QString::fromUtf8( ":/dboxfetray.png" ) ) );
	setWindowTitle( getAppTitel() );

	update = new QTimer( this );
	connect( update, SIGNAL( timeout() ), this, SLOT( reloadMenu() ) );
	update->thread()->setPriority( QThread::NormalPriority );
	update->start( 15000 );
}

void DBoxFE_TrayIcon::setVisible( bool visible )
{
	visible = false;
	QWidget::setVisible( visible );
}

void DBoxFE_TrayIcon::closeEvent( QCloseEvent *e )
{
	hide();
	e->ignore();
}

void DBoxFE_TrayIcon::createMenu()
{
	
	QAction *infoAction = new QAction( getAppTitel(), this );
	infoAction->setEnabled( FALSE );

	dbfe_trayIconMenu->addAction( infoAction );
	dbfe_trayIconMenu->addSeparator();

	m_file = QDir::homePath();
	m_file.append( "/.dboxfe/profile/profile.xml" );

	XMLPreferences settGP( "DBoxFE", "Alexander Saal" );
	settGP.setVersion( getAppVersion() );
	settGP.load( m_file );

	/* Get the preferences from dboxfe profile */
	QStringList sList = settGP.getStringList( "Profile", "Name" );
	dbox_bin = settGP.getString( "DOSBox", "binary" );

	/* Add dynamical menu entries of gameprofiles */
	for ( int i = 0; i < sList.size(); i++ ) {
		qApp->processEvents();
		dbfe_trayAction = new QAction( sList.value( i ), this );
		connect( dbfe_trayAction, SIGNAL( triggered() ), this, SLOT( startGame() ) );
		dbfe_trayIconMenu->addAction( dbfe_trayAction );
	}

	/* Create action after profile menus */
	dbfe_trayIconMenu->addSeparator();

	QAction *dboxfeAction = new QAction( "&DBoxFE", this );

	connect( dboxfeAction, SIGNAL( triggered() ), this, SLOT( startdboxfe() ) );

	QAction *quitAction = new QAction( tr( "&Quit" ), this );

	connect( quitAction, SIGNAL( triggered() ), qApp, SLOT( quit() ) );

	/* Create trayicon now and set the context menu */
	dbfe_trayIconMenu->addAction( dboxfeAction );
	dbfe_trayIconMenu->addAction( quitAction );
}

void DBoxFE_TrayIcon::reloadMenu()
{
	update->stop();

	dbfe_trayIconMenu->clear();
	createMenu();

	update->start( 10000 );
}

void DBoxFE_TrayIcon::startGame()
{
	QAction *action = qobject_cast<QAction *>( sender() );
	QString gProfile = QDir::homePath() + "/.dboxfe/" + action->text() + ".conf";

	if ( dbox_bin.isEmpty() || dbox_bin.isNull() ) {
		QMessageBox::information( this, getAppTitel(), tr( "Can not start dosbox, no dosbox binary was selected.\nPlease choose dosbox binary." ) );
		return;
	}

	start( dbox_bin, "-conf", """" + gProfile + """" );
}

void DBoxFE_TrayIcon::start( const QString& bin, const QString &param, const QString &conf )
{
	dBox = new QProcess( this );

#ifdef Q_OS_WIN32
	m_param.append( "-noconsole" );
#endif

	m_param.append( param );
	m_param.append( conf );

#ifdef Q_OS_WIN32
	QFileInfo dboxBin( conf );
	dBox->setWorkingDirectory( dboxBin.absolutePath() );
#endif

	dBox->start( bin, m_param );

	m_param.clear();
}

void DBoxFE_TrayIcon::startdboxfe()

{
	QString dbfeBin;
	dboxfe = new QProcess( this );

#ifdef Q_OS_WIN32
	dbfeBin = QCoreApplication::applicationDirPath() + "/dboxfe.exe";
#else
	dbfeBin = QCoreApplication::applicationDirPath() + "/dboxfe";
#endif

	dboxfe->start( dbfeBin, QStringList() );
}
