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
#include "dboxfegdb_assistant.h"
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

	XMLPreferences xmlPreferences( "DBoxFE - GDB", "Alexander Saal" );
	xmlPreferences.load( QDir::homePath() + "/.dboxfe-gdb/dboxfegdb.xml" );

	QString database = xmlPreferences.getString( "Database", "DatabaseFile" );	

	gd_sql->createConnection( database );

	connect( btnAdd, SIGNAL ( clicked() ), this, SLOT ( addGame() ) );
	connect( btnUpdate, SIGNAL ( clicked() ), this, SLOT ( updateGame() ) );
	connect( btnDelete, SIGNAL ( clicked() ), this, SLOT ( deleteGame() ) );
	connect( btnGame, SIGNAL ( clicked() ), this, SLOT ( chooseGame() ) );
	connect( btnExecutable, SIGNAL ( clicked() ), this, SLOT ( chooseExec() ) );
	connect( btnTemplate, SIGNAL ( clicked() ), this, SLOT ( chooseTempl() ) );
	connect( btnClose, SIGNAL ( clicked() ), this, SLOT ( cancel() ) );

	connect( treeWidgetGames, SIGNAL ( itemClicked( QTreeWidgetItem *, int ) ), this, SLOT ( treeWidgetGameItemClicked( QTreeWidgetItem *, int ) ) );

	QDesktopWidget *desktop = qApp->desktop();
	const QRect rect = desktop->availableGeometry ( desktop->primaryScreen() );
	int left = ( rect.width() - width() ) / 2;
	int top = ( rect.height() - height() ) / 2;
	setGeometry ( left, top, width(), height() );

	gameName = QString( "" );

	gd_sql->selectGames( treeWidgetGames );

	comboBoxDosboxVersion->clear();

	QStringList dosboxVersionList = gd_sql->selectDosBoxVersion();
	if( dosboxVersionList.isEmpty() || dosboxVersionList.size() <= 0 )
		return;

	for( int i = 0; i < dosboxVersionList.size(); i++ )
	{
		comboBoxDosboxVersion->addItem( dosboxVersionList.value( i ) );
	}
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

void GameDatabaseDialog::treeWidgetGameItemClicked( QTreeWidgetItem *item, int column )
{
	int col = column;
	gameName = item->text( 0 );
}

void GameDatabaseDialog::addGame()
{
	if( checkStatus() )
	{
		QString gName = lineEditGame->text();
		QString gVersion = comboBoxDosboxVersion->currentText();
		QString gExec = lineEditExecutable->text();
		QString gTemplate = lineEditTemplate->text();

		gd_sql->insertGames( gName, gVersion, gExec, gTemplate );
	}
}

void GameDatabaseDialog::updateGame()
{
	if( checkStatus() )
	{
		QString gName = lineEditGame->text();
		QString gVersion = comboBoxDosboxVersion->currentText();
		QString gExec = lineEditExecutable->text();
		QString gTemplate = lineEditTemplate->text();

		gd_sql->updateGames( gName, gVersion, gExec, gTemplate );
	}
}

void GameDatabaseDialog::deleteGame()
{
	if( !gameName.isNull() || !gameName.isEmpty() )
	{		
		QMessageBox::critical( this, tr( "Gamedatabase" ), tr( "Please select a game from list." ) );
		return;
	}

	gd_sql->deleteGames( gameName, false );
}

void GameDatabaseDialog::chooseGame()
{	
	gd_dosbox = new GameDosBoxDialog();
	if( gd_dosbox->exec() == QDialog::Accepted )
	{
		QString gName = gd_dosbox->lineEditGames->text();
		lineEditGame->setText( gName );

	}
}

void GameDatabaseDialog::chooseExec()
{
}

void GameDatabaseDialog::chooseTempl()
{
	gd_template = new GameTemplateDialog( 0 );
	if( gd_template->exec() == QDialog::Accepted )
	{
	}
}

void GameDatabaseDialog::cancel()
{
	qApp->quit();
}

bool GameDatabaseDialog::checkStatus()
{
	if( lineEditGame->text().isEmpty() )
	{
		QMessageBox::critical( this, tr( "Gamedatabase" ), tr( "Please enter a name for this game." ) );		
		return false;
	}

	if( comboBoxDosboxVersion->currentText().isNull() || comboBoxDosboxVersion->currentText().isEmpty() )
	{
		QMessageBox::critical( this, tr( "Gamedatabase" ), tr( "You must select a dosbox version for this game." ) );
		return false;
	}

	if( lineEditExecutable->text().isEmpty() )
	{
		QMessageBox::critical( this, tr( "Gamedatabase" ), tr( "You must select a executable for this game." ) );
		return false;
	}

	return true;
}