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
#include "dboxfegdb_sql.h"
#include "dboxfegdb_template.h"
#include "dboxfegdb_xml.h"

#include <XMLPreferences.h>

#include <QtGui>
#include <QtCore>

GameDatabaseDialog::GameDatabaseDialog( QDialog *parent, Qt::WFlags flags ) : QDialog( parent, flags )
{
	setupUi( this );
	
	gd_sql = new GameDatabaseSql( this );
	gd_xml = new GameDatabaseXml( this );
}

GameDatabaseDialog::~GameDatabaseDialog()
{
}

void GameDatabaseDialog::closeEvent ( QCloseEvent *e )
{
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

void GameDatabaseDialog::save()
{
}

void GameDatabaseDialog::cancel()
{
}
