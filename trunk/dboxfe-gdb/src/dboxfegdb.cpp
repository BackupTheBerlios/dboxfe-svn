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

#include "dboxfegdb.h"
#include "dboxfegdb_dosbox.h"
#include "dboxfegdb_template.h"
#include "dboxfegdb_sql.h"

#include <XMLPreferences.h>

#include <QtGui>
#include <QtCore>

GameDatabaseDialog::GameDatabaseDialog( QDialog *parent, Qt::WFlags flags ) : QDialog( parent, flags )
{
	setupUi( this );
	
	gd_sql = new GameDatabaseSql( this );

	connect( btnAdd, SIGNAL ( clicked() ), this, SLOT ( addGame() ) );
	connect( btnUpdate, SIGNAL ( clicked() ), this, SLOT ( updateGame() ) );
	connect( btnDelete, SIGNAL ( clicked() ), this, SLOT ( deleteGame() ) );
	connect( btnGame, SIGNAL ( clicked() ), this, SLOT ( chooseGame() ) );
	connect( btnExecutable, SIGNAL ( clicked() ), this, SLOT ( chooseExec() ) );
	connect( btnTemplate, SIGNAL ( clicked() ), this, SLOT ( chooseTempl() ) );
	connect( btnClose, SIGNAL ( clicked() ), this, SLOT ( cancel() ) );

#ifdef Q_OS_MACX
	QApplication::setStyle ( "plastique" );
#endif

#ifdef Q_OS_MAC9
	QApplication::setStyle ( "plastique" );
#endif

#ifdef Q_OS_UNIX
	QApplication::setStyle ( "plastique" );
#endif

	QDesktopWidget *desktop = qApp->desktop();
	const QRect rect = desktop->availableGeometry ( desktop->primaryScreen() );
	int left = ( rect.width() - width() ) / 2;
	int top = ( rect.height() - height() ) / 2;
	setGeometry ( left, top, width(), height() );
}

GameDatabaseDialog::~GameDatabaseDialog()
{
	gd_sql = NULL;
	gd_template = NULL;
}

void GameDatabaseDialog::closeEvent ( QCloseEvent *e )
{
	gd_sql = NULL;
	gd_template = NULL;
}

void GameDatabaseDialog::addGame()
{
}

void GameDatabaseDialog::updateGame()
{
}

void GameDatabaseDialog::deleteGame()
{
}

void GameDatabaseDialog::chooseGame()
{
}

void GameDatabaseDialog::chooseExec()
{
}

void GameDatabaseDialog::chooseTempl()
{
}

void GameDatabaseDialog::cancel()
{
}
