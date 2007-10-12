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

#include "dboxfegdb_sql.h"
#include "dboxfegdb_xml.h"

#include "XMLPreferences.h"

#include <QtCore>
#include <QtGui>
#include <QtSql>

GameDatabaseSql::GameDatabaseSql( QObject *parent ) : QObject( parent )
{
	object = parent;	
}

GameDatabaseSql::~GameDatabaseSql()
{}


bool GameDatabaseSql::createConnection( const QString &db )
{
	sqlDatabase = db;
	if( sqlDatabase.isNull() || sqlDatabase.isEmpty() )
		return false;

	gamedb = QSqlDatabase::addDatabase( "QSQLITE" );
	gamedb.setDatabaseName( sqlDatabase );
	gamedb.setUserName( "" );
	gamedb.setPassword( "" );
	gamedb.setHostName( "" );

	if ( !gamedb.open() )
	{
		qWarning() << "Failed to open game database: " + gamedb.lastError().text();
		return false;
	}

	return true;
}

bool GameDatabaseSql::closeConnection()
{
	if( isOpen() )
	{
		if( sqlDatabase.isNull() || sqlDatabase.isEmpty() )
			return false;

		gamedb.close();
	}

	return true;
}

bool GameDatabaseSql::createDatabase( const QString &name )
{
	if ( name.isNull() || name.isEmpty() || name == QString( "" ) )
		return false;

	sqlDatabase = name;

	sqlFile = QString( ":/misc/game_database.sql" );

	QFile f( sqlFile );

	if ( !f.open( QIODevice::ReadOnly | QIODevice::Text ) )
		return false;

	gamedb = QSqlDatabase::addDatabase( "QSQLITE" );
	gamedb.setDatabaseName( sqlDatabase );
	gamedb.setUserName( "" );
	gamedb.setPassword( "" );
	gamedb.setHostName( "" );

	if ( !gamedb.open() )
	{
		qWarning() << "Failed to open game database: " + gamedb.lastError().text();
		return false;
	}

	QSqlQuery query( gamedb );

	while( !f.atEnd() )
	{
		QString sql = f.readLine();
		query.exec( sql );

		if( !query.isActive() )
		{
			qWarning() << "Failed to create tables on " + sqlDatabase + " (exists?): " + query.lastError().text();
			return false;
		}
	}

	return true;
}

bool GameDatabaseSql::importDosBoxGameList( const QMap< QString, QMap< QString, QStringList> > &list, QProgressBar *pBar, QLabel *lbl )
{
	if( !isOpen() )
		return false;

	gameDosBoxList = list;
	gameDosBoxList.setInsertInOrder( false );

	QSqlQuery query( gamedb );
	QString sqlQuery;
	QString _id;
	int x = 0;

	pBar->setMaximum( list.size() );

	query.exec( "DELETE FROM DOSBOX;" );
	if( !query.isActive() )
		qWarning() << "Failed to delete entities from dosbox table:\t>> " << query.lastError().text() << " <<";

	query.exec( "DELETE FROM DOSBOXINFO;" );
	if( !query.isActive() )
		qWarning() << "Failed to delete entities from dosboxinformation table:\t>> " << query.lastError().text() << " <<";

	// TODO Insert dosbox versions into database - START
	QString gameXML =  QDir::homePath() + "/.dboxfe-gdb/game_database.xml";

	GameDatabaseXml *gd_xml = new GameDatabaseXml( this );
	QStringList gameVersionsList = gd_xml->getDosBoxVersion( gameXML );

	pBar->setMaximum( gameVersionsList.size() );

	for( int i = 0; i < gameVersionsList.size(); i++ ) {
		qApp->processEvents();

		_id = QUuid::createUuid().toString();

		sqlQuery.clear();
		sqlQuery = "";
		sqlQuery += "INSERT INTO DOSBOX\n";
		sqlQuery += "(\n";
		sqlQuery += "\tID,\n";
		sqlQuery += "\tVERSION\n";
		sqlQuery += ")\n";
		sqlQuery += "VALUES\n";
		sqlQuery += "(\n";
		sqlQuery += "\t'" + _id + "',\n";
		sqlQuery += "\t'" + gameVersionsList.value( i ).replace( "'", "''" ) + "'\n";
		sqlQuery += ");";

		query.exec( "SELECT VERSION FROM DOSBOX WHERE VERSION = '" + gameVersionsList.value( i ) + "';" );
		if( query.isActive() )
		{
			while( query.next() )
			{
				qApp->processEvents();

				if( !query.value( 0 ).toString().isEmpty() )
				{
					goto next;
				}
				else
				{
					query.exec( sqlQuery );
					if( !query.isActive() )
						qWarning() << "Failed to import dosbox version into dosbox table:\t>> " << query.lastError().text() << " <<";
				}
			}
		}
		query.exec( sqlQuery );
		if( !query.isActive() )
			qWarning() << "Failed to import dosbox information into dosbox table:\t>> " << query.lastError().text() << " <<";
		

		lbl->setText( "" );
		lbl->setText( "Status: " + gameVersionsList.value( i ).replace( "'", "''" ) );
		lbl->repaint();
		lbl->update();

		pBar->setValue( x );
		pBar->repaint();
		pBar->update();

		x = x + 1;

		continue;
next:
		;
	}

	lbl->setText( "" );
	lbl->setText( "Status:" );
	pBar->setValue( 0 );
	x = 0;

	gd_xml = 0;
	delete gd_xml;

	// TODO Insert dosboxgames into the database
	bool first = true;
	QMap< QString, QMap< QString, QStringList> >::const_iterator gameIt = gameDosBoxList.begin();
	while( gameIt != gameDosBoxList.end() ) {
		qApp->processEvents();

		_id = QUuid::createUuid().toString();
		_title = gameIt.key();

		QMap< QString, QStringList>::const_iterator valueIt = gameIt.value().begin();
		while( valueIt != gameIt.value().end() )
		{
			qDebug() << valueIt.key();
			if( valueIt.key() == "link" )
				_link = valueIt.value().value(0);
			else if( valueIt.key() == "sw_house" )
				_sw_house = valueIt.value().value(0);
			else if( valueIt.key() == "year" )
				_year = valueIt.value().value(0);
			else if( valueIt.key() == "version" )
			{
				if( valueIt.value().size() >= 1 )
				{
					for( int i = 0; i < valueIt.value().size(); i++ )
					{
						_version = valueIt.value().value( i ).split( ";" ).value( 0 );
						_comp_percent = valueIt.value().value( i ).split( ";" ).value( 1 );

						if( _year.isNull() || _year.isEmpty() )
						{
							++valueIt;
							_year = valueIt.value().value(0);
							--valueIt;
						}

						sqlQuery.clear();
						sqlQuery = "";
						sqlQuery += "INSERT INTO DOSBOXINFO\n";
						sqlQuery += "(\n";
						sqlQuery += "\tID,\n";
						sqlQuery += "\tVERSION,\n";
						sqlQuery += "\tTITLE,\n";
						sqlQuery += "\tYEAR,\n";
						sqlQuery += "\tSW_HOUSE,\n";
						sqlQuery += "\tLINK,\n";
						sqlQuery += "\tCOMP_PERSENT\n";
						sqlQuery += ")\n";
						sqlQuery += "VALUES\n";
						sqlQuery += "(\n";
						sqlQuery += "\t'" + _id + "',\n";
						sqlQuery += "\t'" + _version.replace( "'", "''" ) + "',\n";
						sqlQuery += "\t'" + _title.replace( "'", "''" ) + "',\n";
						sqlQuery += "\t'" + _year.replace( "'", "''" ) + "',\n";
						sqlQuery += "\t'" + _sw_house.replace( "'", "''" ) + "',\n";
						sqlQuery += "\t'" + _link.replace( "'", "''" ) + "',\n";
						sqlQuery += "\t'" + _comp_percent.replace( "'", "''" ) + "'\n";
						sqlQuery += ");";

						query.exec( sqlQuery );
						if( !query.isActive() )
							qWarning() << "Failed to import dosbox information into dosboxinformation table:\t>> " << query.lastError().text() << " <<";
					}
				}
			}

			++valueIt;
		}

		lbl->setText( "" );
		lbl->setText( "Status: " + _title );
		lbl->repaint();
		lbl->update();

		pBar->setValue( x );
		pBar->repaint();
		pBar->update();

		x = x + 1;
		++gameIt;
	}

	lbl->setText( "Status: finish" );
	lbl->repaint();
	lbl->update();

	pBar->setValue( 100 );
	pBar->repaint();
	pBar->update();

	return true;
}

bool GameDatabaseSql::importGameList( const QStringList &list )
{
	if( list.isEmpty() )
		return false;

	if( !isOpen() )
		return false;

	gameList = list;
	for( int i = 0; i < gameList.size(); i++ )
	{
		QStringList games = gameList.value( i ).split( ";" );
		QString gameId = QUuid::createUuid().toString();
		QString name = games.value( 0 ); // Game name
		QString exec = games.value( 1 ); // Game executable

		QSqlQuery query( gamedb );

		QString sqlQuery;
		sqlQuery.clear();
		sqlQuery = "";
		sqlQuery += "INSERT INTO GAME\n";
		sqlQuery += "(\n";
		sqlQuery += "\tID,\n";
		sqlQuery += "\tNAME,\n";
		sqlQuery += "\tEXEC\n";
		sqlQuery += ")\n";
		sqlQuery += "VALUES\n";
		sqlQuery += "(\n";
		sqlQuery += "\t'" + gameId + "',\n";
		sqlQuery += "\t'" + name + "',\n";
		sqlQuery += "\t'" + exec + "'\n";
		sqlQuery += ");";

		query.exec( sqlQuery );

		if( query.isActive() )
			qWarning() << "Failed to insert game into database:\t" + query.lastError().text();
	}

	return true;
}

bool GameDatabaseSql::exportGamesList( const QString &xml )
{
	if( xml.isNull() || xml.isEmpty() )
		return false;

	if( !isOpen() )
		return false;

	exportGameList.clear();
	exportGameTemplateList.clear();

	QSqlQuery query( gamedb );
	query.exec( "SELECT NAME, EXEC FROM GAME;" );
	if( query.isActive() )
	{
		while( !query.next() )
		{
			exportGameList.append( query.value( 0 ).toString() + ";" + query.value( 1 ).toString() );
		}
	}

	QString sqlQuery;
	sqlQuery.clear();
	sqlQuery = "";
	sqlQuery += "SELECT G.NAME, GT.TEMPLATE\n";
	sqlQuery += "FROM GAMETEMPLATE GT\n";
	sqlQuery += "JOIN GAME G ON GT.ID = G.ID;";

	query.exec( sqlQuery );
	if( query.isActive() )
	{
		while( !query.next() )
		{
			exportGameTemplateList.append( query.value( 0 ).toString() + ";" + query.value( 1 ).toString() );
		}
	}

	XMLPreferences xmlPreferences( "DBoxFE", "Alexander Saal" );
	xmlPreferences.setVersion( "v0.1.3" );
	xmlPreferences.setStringList( "Games", "Name", exportGameList );
	xmlPreferences.setStringList( "ConfigTemplate", "Name", exportGameTemplateList );

	return xmlPreferences.save( xml );
}

bool GameDatabaseSql::importGameTemplateList( const QStringList &list )
{
	if( list.isEmpty() )
		return false;

	if( !isOpen() )
		return false;

	gameTemplateList = list;
	QSqlQuery query( gamedb );

	for( int i = 0; i < gameList.size(); i++ )
	{
		QStringList games = gameList.value( i ).split( ";" );

		query.exec( "SELECT ID FROM GAME WHERE NAME = '" +  games.value( 0 ) + "';" );
		QString gameId = query.value( 0 ).toString();
		QString templates = games.value( 1 ); // Game executable

		QString sqlQuery;
		sqlQuery = "";
		sqlQuery += "INSERT INTO GAMETEMPLATE\n";
		sqlQuery += "(\n";
		sqlQuery += "\tID,\n";
		sqlQuery += "\tTEMPLATE\n";
		sqlQuery += ")\n";
		sqlQuery += "VALUES\n";
		sqlQuery += "(\n";
		sqlQuery += "\t'" + gameId + "',\n";
		sqlQuery += "\t'" + templates + "'\n";
		sqlQuery += ");";

		query.exec( sqlQuery );

		if( !query.isActive() )
		{
			qWarning() << "Failed to import templates into database:\t" + query.lastError().text();
			return false;
		}		
	}
	return true;
}

bool GameDatabaseSql::updateGames( const QString &name, const QString &version, const QString &executable, const QString &templates )
{
	qWarning() << "Not yet implementet ==> updateGames( ... ); ==> TODO: FIX THIS";
	return false;
}

bool GameDatabaseSql::insertGames( const QString &name, const QString &version, const QString &executable, const QString &templates )
{
	if( name.isNull() || name.isEmpty() )
		return false;

	if( executable.isNull() || executable.isEmpty() )
		return false;

	if( !isOpen() )
	{
		createConnection( sqlDatabase );
	}

	if( !isOpen() )
		return false;

	QString _id_dosbox = QString( "" );

	QSqlQuery query( gamedb );

	// Select dosbox id form dosbox
	query.exec( "SELECT ID FROM DOSBOX WHERE VERSION = '" + version + "';" );

	if( query.isActive() )
	{
		while( query.next() )
			_id_dosbox = query.value( 0 ).toString();
	}

	if( _id_dosbox.isNull() || _id_dosbox.isEmpty() )
		return false;


	QString _id_template = QString( "" );

	// Select id from game template
	query.exec( "SELECT ID FROM GAME WHERE ID = '" + templates + "';" );
	if( query.isActive() )
	{
		while( query.next() )
			_id_template = query.value( 0 ).toString();
	}

	if( _id_template.isNull() || _id_template.isEmpty() )
		return false;	

	if( !templates.isNull() || !templates.isEmpty() )
	{
		QString sqlQuery;
		sqlQuery = "";
		sqlQuery += "INSERT INTO GAME\n";
		sqlQuery += "(\n";
		sqlQuery += "\tNAME\n";
		sqlQuery += "\tDB_ID\n";
		sqlQuery += "\tNAME\n";
		sqlQuery += "\tEXEC\n";
		sqlQuery += "\tTEMPLATE\n";
		sqlQuery += ")\n";
		sqlQuery += "VALUES\n";
		sqlQuery += "(\n";
		sqlQuery += "\t" + name + "\n";
		sqlQuery += "\t" + _id_dosbox + "\n";
		sqlQuery += "\t" + executable + "\n";
		sqlQuery += "\t" + _id_template + "\n";
		sqlQuery += ");\n";

		query.exec( sqlQuery );
		if( !query.isActive() )
		{
			qWarning() << "Failed to insert game into database:\t" + query.lastError().text();
			return false;			
		}
	}

	return true;
}

bool GameDatabaseSql::deleteGames( const QString &name, bool withTemplate )
{
	if( name.isNull() || name.isEmpty() )
		return false;

	if( !isOpen() )
		return false;

	QSqlQuery query( gamedb );
	query.exec( "SELECT ID, NAME FROM GAME WHERE NAME = '" + name + "';" );
	if( query.isActive() )
	{
		QString gameId = "";
		QString gameName = "";
		while( query.next() )
		{
			gameId = query.value( 0 ).toString();
			gameName = query.value( 1 ).toString();
		}

		query.exec( "DELETE FROM GAME WHERE NAME = '" + gameName + "';" );
		if( !query.isActive() )
		{
			qWarning() << "Can't delete game from table 'GAME': " + query.lastError().text();
			return false;
		}

		if( withTemplate )
		{
			query.exec( "DELETE FROM GAMETEMPLATE WHERE ID = '" + gameId + "';" );
			if( !query.isActive() )
			{
				qWarning() << "Can't delete game template from table 'GAMETEMPLATE': " + query.lastError().text();
				return false;
			}
		}
	}

	return true;
}

QStringList GameDatabaseSql::selectDosBoxVersion()
{
	if( !isOpen() )
		return dosboxVersionList;

	QSqlQuery query( gamedb );
	query.exec( "SELECT DISTINCT VERSION FROM DOSBOX ORDER BY VERSION;" );
	if( query.isActive() )
		while( query.next() )
		{
			dosboxVersionList.append( query.value( 0 ).toString() );
		}
	else
		qWarning() << "Can't get dosbox version from table 'DOSBOX':\t" + query.lastError().text();

	return dosboxVersionList;
}

void GameDatabaseSql::selectDosBoxGames( const QString &version, QTreeWidget *qtw )
{
	if( version.isNull() || version.isEmpty() )
		return;

	if( !isOpen() )
		return;

	qtw->clear();

	QSqlQuery query( gamedb );

	QString sqlQuery;
	sqlQuery.clear();
	sqlQuery = "";
	sqlQuery += "SELECT DI.TITLE, DI.YEAR, DI.SW_HOUSE, DI.LINK, DI.COMP_PERSENT\n";
	sqlQuery += "FROM DOSBOXINFO DI\n";
	sqlQuery += "JOIN DOSBOX D ON DI.ID = D.ID\n";
	sqlQuery += "WHERE D.VERSION = '" + version + "';";

	query.exec( sqlQuery );
	if( query.isActive() )
	{
		while( query.next() )
		{
			QTreeWidgetItem *item = new QTreeWidgetItem( qtw );
			item->setText( 0, query.value( 0 ).toString() );
			item->setText( 1, query.value( 1 ).toString() );
			item->setText( 2, query.value( 2 ).toString() );
			item->setText( 3, query.value( 3 ).toString() );
			item->setText( 4, query.value( 4 ).toString() );
		} 
	}
}

void GameDatabaseSql::selectGames( QTreeWidget *qtw )
{
	if( !isOpen() )
		return;

	qtw->clear();

	QSqlQuery query( gamedb );

	QString sqlQuery;
	sqlQuery.clear();
	sqlQuery = "";
	sqlQuery += "SELECT G.NAME , D.VERSION, G.EXEC, G.TEMPLATE\n";
	sqlQuery += "FROM GAME G\n";
	sqlQuery += "JOIN DOSBOX D ON G.DB_ID = D.ID";

	query.exec( sqlQuery );
	if( query.isActive() )
	{
		while( query.next() )
		{
			QTreeWidgetItem *item = new QTreeWidgetItem( qtw );
			item->setText( 0, query.value( 0 ).toString() );
			item->setText( 1, query.value( 1 ).toString() );
			item->setText( 2, query.value( 2 ).toString() );
			item->setText( 3, query.value( 3 ).toString() );
		} 
	}

}

bool GameDatabaseSql::isOpen()
{
	if( gamedb.isOpen() )
		return true;

	return false;
}

