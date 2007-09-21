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

#include "XMLPreferences.h"

#include <QtCore>
#include <QtSql>

GameDatabaseSql::GameDatabaseSql( QObject *parent ) : QObject( parent )
{
	object = parent;	
}

GameDatabaseSql::~GameDatabaseSql()
{}

void GameDatabaseSql::init()
{
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

	QString sql = f.readAll();

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

	query.exec( sql );

	if( !query.isActive() )
	{
		qWarning() << "Failed to create tables on " + sqlDatabase + " (exists?): " + query.lastError().text();
		return false;
	}

	return true;
}

bool GameDatabaseSql::importDosBoxGameList( const QMap< QString, QMap< QString, QString> > &list )
{
	if( !isOpen() )
		return false;

	gameDosBoxList = list;

	QMap< QString, QMap< QString, QString> >::const_iterator gameIt = gameDosBoxList.begin();
	while( gameIt != gameDosBoxList.end() ) {
		QSqlQuery query( gamedb );
		query.exec( "SELECT TITLE FROM DOSBOXINFO WHERE TITLE = '" + gameIt.key() + "';" );
		if( query.isActive() )
		{
			_title = query.value( 0 ).toString();
			if( !_title.isNull() || !_title.isEmpty() )
			{
				if( (_title.toLower() == gameIt.key().toLower()) )
				{
					QMap< QString, QString>::const_iterator valueIt = gameIt.value().begin();
					while( valueIt != gameIt.value().end() )
					{
						if( valueIt.key() == "year" )
							_year = valueIt.value();
						if( valueIt.key() == "sw_house" )
							_sw_house = valueIt.value();
						if( valueIt.key() == "link" )
							_link = valueIt.value();
						if( valueIt.key() == "comp_percent" )
							_comp_percent = valueIt.value();
						if( valueIt.key() == "version" )
							_version = valueIt.value();						 
					}

					bool up = updateDosBoxGames( _version, _title, _year, _sw_house, _link, _comp_percent );

					if( !up )
						qWarning() << "Failed to update a query  to game database:\t" + query.lastError().text();
				}
				else
				{
					QMap< QString, QString>::const_iterator valueIt = gameIt.value().begin();
					while( valueIt != gameIt.value().end() )
					{
						if( valueIt.key() == "year" )
							_year = valueIt.value();
						if( valueIt.key() == "sw_house" )
							_sw_house = valueIt.value();
						if( valueIt.key() == "link" )
							_link = valueIt.value();
						if( valueIt.key() == "comp_percent" )
							_comp_percent = valueIt.value();
						if( valueIt.key() == "version" )
							_version = valueIt.value();						 
					}

					bool in = insertDosBoxGames( _version, _title, _year, _sw_house, _link, _comp_percent );

					if( !in )
						qWarning() << "Failed to insert a query to game database:\t" + query.lastError().text();
				}
			}
		}
		else
			qWarning() << "Failed to query game database:\t" + query.lastError().text();

		++gameIt;
	}

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
			qWarning() << "Failed to insert game into database:\t" + query.lastError().text();
			return false;
		}		
	}
	return true;
}

bool GameDatabaseSql::updateDosBoxGames( const QString &version, const QString &title, const QString &year, const QString &sw_house, const QString &link, const QString &comp_percent )
{
	return false;
}

bool GameDatabaseSql::insertDosBoxGames( const QString &version, const QString &title, const QString &year, const QString &sw_house, const QString &link, const QString &comp_percent )
{
	return false;
}


bool GameDatabaseSql::updateGames( const QString &name, const QString &version, const QString &executable, const QString &templates )
{
	return false;
}

bool GameDatabaseSql::insertGames( const QString &name, const QString &version, const QString &executable, const QString &templates )
{
	if( name.isNull() || name.isEmpty() )
		return false;

	if( executable.isNull() || executable.isEmpty() )
		return false;

	if( !isOpen() )
		return false;

	QSqlQuery query( gamedb );

	if( !templates.isNull() || !templates.isEmpty() )
	{
		QString sqlQuery;
		sqlQuery = "";
		sqlQuery += "INSERT INTO GAME\n";
		sqlQuery += "(\n";
		sqlQuery += "\tNAME\n";
		sqlQuery += "\tDB_ID\n";
		sqlQuery += "\n";

		query.exec( "" );		
	}

	return false;
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
		QString gameId = query.value( 0 ).toString();
		QString gameName = query.value( 1 ).toString();

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

bool GameDatabaseSql::isOpen()
{
	if( gamedb.isOpen() )
		return true;

	return false;
}
