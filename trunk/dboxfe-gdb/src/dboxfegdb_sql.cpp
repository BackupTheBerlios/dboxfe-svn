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

	sqlFile = QString( "" );
	sqlDatabase = QString( "" );

	_template_name = QString( "" );

	_version = QString( "" );
	_title = QString( "" );
	_year = QString( "" );
	_sw_house = QString( "" );
	_link = QString( "" );
	_comp_percent = QString( "" );
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

bool GameDatabaseSql::importDosBoxGameList( const QMap< QString, QMap< QString, QString> > &list, QProgressBar *pBar, QLabel *lbl )
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

	// TODO Delete all entities in the database ...
	query.exec( "DELETE FROM DOSBOXVERSION;" );
	if( !query.isActive() )
		qWarning() << "Failed to delete entities from dosbox table:\t>> " << query.lastError().text() << " <<";

	query.exec( "DELETE FROM DOSBOXINFO;" );
	if( !query.isActive() )
		qWarning() << "Failed to delete entities from dosboxinformation table:\t>> " << query.lastError().text() << " <<";

	// TODO Insert dosbox versions into database
	QString gameXML =  QDir::homePath() + "/.dboxfe-gdb/game_database.xml";

	GameDatabaseXml *gd_xml = new GameDatabaseXml( this );
	QStringList gameVersionsList = gd_xml->getDosBoxVersion( gameXML );

	pBar->setMaximum( gameVersionsList.size() );

	for( int i = 0; i < gameVersionsList.size(); i++ ) {
		qApp->processEvents();

		_id = QUuid::createUuid().toString();

		sqlQuery.clear();
		sqlQuery = "";
		sqlQuery += "INSERT INTO DOSBOXVERSION\n";
		sqlQuery += "(\n";
		sqlQuery += "\tID,\n";
		sqlQuery += "\tVERSION\n";
		sqlQuery += ")\n";
		sqlQuery += "VALUES\n";
		sqlQuery += "(\n";
		sqlQuery += "\t'" + _id + "',\n";
		sqlQuery += "\t'" + gameVersionsList.value( i ).replace( "'", "''" ) + "'\n";
		sqlQuery += ");";

		query.exec( "SELECT VERSION FROM DOSBOXVERSION WHERE VERSION = '" + gameVersionsList.value( i ) + "';" );
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

	lbl->setText( "Status: " );
	lbl->repaint();
	lbl->update();

	pBar->setValue( 0 );

	x = 0;
	gd_xml = 0;

	delete gd_xml;

	// TODO Insert dosboxgames into the database
	QMap< QString, QMap< QString, QString> >::const_iterator gameIt = gameDosBoxList.begin();
	while( gameIt != gameDosBoxList.end() ) {
		qApp->processEvents();

		_id = QUuid::createUuid().toString();
		_title = gameIt.key();

		QMap< QString, QString>::const_iterator valueIt = gameIt.value().begin();
		while( valueIt != gameIt.value().end() )
		{
			if( valueIt.key() == "link" )
				_link = valueIt.value();
			else if( valueIt.key() == "sw_house" )
				_sw_house = valueIt.value();
			else if( valueIt.key() == "year" )
				_year = valueIt.value();
			else if( valueIt.key() == "version" )
				_version = valueIt.value();
			else if( valueIt.key() == "comp_percent" )
				_comp_percent = valueIt.value();

			++valueIt;
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

		// TODO create reference to dosboxid table ...
		QString dosboxVersion = QString( "" );
		query.exec( "SELECT ID FROM DOSBOXVERSION WHERE VERSION = '" + _version.replace( "'", "''" ) + "';" );
		if( query.isActive() )
			while( query.next() )
				dosboxVersion = query.value( 0 ).toString();

		sqlQuery.clear();
		sqlQuery = "";
		sqlQuery += "INSERT INTO DOSBOXID\n";
		sqlQuery += "(\n";
		sqlQuery += "\tD_ID,\n";
		sqlQuery += "\tDI_ID\n";
		sqlQuery += ")\n";
		sqlQuery += "VALUES\n";
		sqlQuery += "(\n";
		sqlQuery += "\t'" + dosboxVersion + "',\n";
		sqlQuery += "\t'" + _id + "'\n";
		sqlQuery += ");";

		query.exec( sqlQuery );
		if( !query.isActive() )
			qWarning() << "Failed to create reference on dosboxid:\t>> " << query.lastError().text() << " <<";

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

	pBar->setValue( 0 );
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
	query.exec( "SELECT G.NAME, D.VERSION, G.EXEC FROM GAME G JOIN DOSBOXVERSION D ON G.DB_ID = D.ID;" );
	if( query.isActive() )
	{
		while( !query.next() )
		{
			exportGameList.append( query.value( 0 ).toString() + ";" + query.value( 1 ).toString() + ";" + query.value( 2 ).toString() );
		}
	}

	QString sqlQuery;
	sqlQuery.clear();
	sqlQuery = "";
	sqlQuery += "SELECT G.NAME,GT.TEMPLATE\n";
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

bool GameDatabaseSql::updateTemplates( const QString &name, QMap< QString, QMap< QString, QString > > &settings )
{
	if( name.isNull() || name.isEmpty() )
		return false;

	if( dir.isNull() || dir.isEmpty() )
		return false;

	_template_name = name;

	sett.clear();
	sett = settings;

	QSqlQuery query( gamedb );

	return true;
}

bool GameDatabaseSql::insertTemplates( const QString &name, QMap< QString, QMap< QString, QString > > &settings )
{
	if( name.isNull() || name.isEmpty() )
		return false;

	if( dir.isNull() || dir.isEmpty() )
		return false;

	_template_name = name;

	sett.clear();
	sett = settings;

	QSqlQuery query( gamedb );

	QString _id = QUuid::createUuid().toString();

	QString sqlQuery;

	sqlQuery = "";
	sqlQuery += "INSERT INTO GAMETEMPLATE\n";
	sqlQuery += "(\n";
	sqlQuery += "\tID,\n";
	sqlQuery += "\tNAME,\n";
	sqlQuery += "\tDIR\n";
	sqlQuery += ")\n";
	sqlQuery += "VALUES\n";
	sqlQuery += "(\n";
	sqlQuery += "\t'" + _id + "',\n";
	sqlQuery += "\t'" + _template_name + "'\n";
	sqlQuery += ");";

	query.exec( sqlQuery );
	if( !query.isActive() )
			qWarning() << "Failed to insert templates into database:\t" + query.lastError().text();


	QMap< QString, QString>::const_iterator conSettIt;
	QMap< QString, QMap< QString, QString> >::const_iterator confIt = sett.begin();

	while( confIt != sett.end() )
	{
		qApp->processEvents();

		if( confIt.key().toUpper() == "SDL" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "fullscreen" )
					_fullscreen = conSettIt.value();
				else if( conSettIt.key().toLower() == "fulldouble" )
					_fulldouble = conSettIt.value();
				else if( conSettIt.key().toLower() == "fullresolution" )
					_fullresolution = conSettIt.value();
				else if( conSettIt.key().toLower() == "windowresolution" )
					_windowresolution = conSettIt.value();
				else if( conSettIt.key().toLower() == "output" )
					_output = conSettIt.value();
				else if( conSettIt.key().toLower() == "autolock" )
					_autolock = conSettIt.value();
				else if( conSettIt.key().toLower() == "sensitivity" )
					_sensitivity = conSettIt.value();
				else if( conSettIt.key().toLower() == "waitonerror" )
					_waitonerror = conSettIt.value();
				else if( conSettIt.key().toLower() == "priority" )
					_priority = conSettIt.value();
				else if( conSettIt.key().toLower() == "mapperfile" )
					_mapperfile = conSettIt.value();
				else if( conSettIt.key().toLower() == "usescancodes" )
					_usescancodes = conSettIt.value();

				++conSettIt;
			}

			sqlSdl = "";
			sqlSdl += "INSERT INTO SDL\n";
			sqlSdl += "(\n";
			sqlSdl += "\tID,\n";
			sqlSdl += "\tFULLSCREEN,\n";
			sqlSdl += "\tFULLDOUBLE,\n";
			sqlSdl += "\tFULLRESOLUTION,\n";
			sqlSdl += "\tWINDOWRESOLUTION,\n";
			sqlSdl += "\tOUTPUT,\n";
			sqlSdl += "\tAUTOLOCK,\n";
			sqlSdl += "\tSENSITIVITY,\n";
			sqlSdl += "\tWAITONERROR,\n";
			sqlSdl += "\tPRIORITY,\n";
			sqlSdl += "\tMAPPERFILE,\n";
			sqlSdl += "\tUSESCANCODES\n";
			sqlSdl += ")\n";
			sqlSdl += "VALUES\n";
			sqlSdl += "(\n";
			sqlSdl += "\t'" + _id + "',\n";
			sqlSdl += "\t'" + _fullscreen + "',\n";
			sqlSdl += "\t'" + _fulldouble + "',\n";
			sqlSdl += "\t'" + _fullresolution + "',\n";
			sqlSdl += "\t'" + _windowresolution + "',\n";
			sqlSdl += "\t'" + _output + "',\n";
			sqlSdl += "\t'" + _autolock + "',\n";
			sqlSdl += "\t'" + _sensitivity + "',\n";
			sqlSdl += "\t'" + _waitonerror + "',\n";
			sqlSdl += "\t'" + _priority + "',\n";
			sqlSdl += "\t'" + _mapperfile + "',\n";
			sqlSdl += "\t'" + _usescancodes + "'\n";
			sqlSdl += ");";
		}
		else if( confIt.key().toUpper() == "DOSBOX" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "language" )
					_language = conSettIt.value();
				else if( conSettIt.key().toLower() == "machine" )
					_machine = conSettIt.value();
				else if( conSettIt.key().toLower() == "captures" )
					_captures = conSettIt.value();
				else if( conSettIt.key().toLower() == "memsize" )
					_memsize = conSettIt.value();

				++conSettIt;
			}

			sqlDosBox = "";
			sqlSdl += "INSERT INTO DOSBOX\n";
			sqlSdl += "(\n";
			sqlSdl += "\tID,\n";
			sqlSdl += "\tLANGUAGE,\n";
			sqlSdl += "\tMACHINE,\n";
			sqlSdl += "\tCAPTURES,\n";
			sqlSdl += "\tMEMSIZE\n";
			sqlSdl += ")\n";
			sqlSdl += "VALUES\n";
			sqlSdl += "(\n";
			sqlSdl += "\t'" + _id + "',\n";
			sqlSdl += "\t'" + _language + "',\n";
			sqlSdl += "\t'" + _machine + "',\n";
			sqlSdl += "\t'" + _captures + "',\n";
			sqlSdl += "\t'" + _memsize + "'\n";
			sqlSdl += ");";
		}
		else if( confIt.key().toUpper() == "RENDER" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "language" )
					_language = conSettIt.value();
				else if( conSettIt.key().toLower() == "machine" )
					_machine = conSettIt.value();
				else if( conSettIt.key().toLower() == "captures" )
					_captures = conSettIt.value();
				else if( conSettIt.key().toLower() == "memsize" )
					_memsize = conSettIt.value();

				++conSettIt;
			}
		}
		else if( confIt.key().toUpper() == "CPU" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "core" )
					_core = conSettIt.value();
				else if( conSettIt.key().toLower() == "cycles" )
					_cycles = conSettIt.value();
				else if( conSettIt.key().toLower() == "cycleup" )
					_cycleup = conSettIt.value();
				else if( conSettIt.key().toLower() == "cycledown" )
					_cycledown = conSettIt.value();

				++conSettIt;
			}
		}
		else if( confIt.key().toUpper() == "MIXER" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "nosound" )
					_nosound = conSettIt.value();
				else if( conSettIt.key().toLower() == "rate" )
					_rate = conSettIt.value();
				else if( conSettIt.key().toLower() == "blocksize" )
					_blocksize = conSettIt.value();
				else if( conSettIt.key().toLower() == "prebuffer" )
					_prebuffer = conSettIt.value();

				++conSettIt;
			}
		}
		else if( confIt.key().toUpper() == "MIDI" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "device" )
					_device = conSettIt.value();
				else if( conSettIt.key().toLower() == "config" )
					_config = conSettIt.value();

				++conSettIt;
			}
		}
		else if( confIt.key().toUpper() == "SBLASTER" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "sbtype" )
					_sbtype = conSettIt.value();
				else if( conSettIt.key().toLower() == "sbbase" )
					_sbbase = conSettIt.value();
				else if( conSettIt.key().toLower() == "irq" )
					_irq = conSettIt.value();
				else if( conSettIt.key().toLower() == "dma" )
					_dma = conSettIt.value();
				else if( conSettIt.key().toLower() == "hdma" )
					_hdma = conSettIt.value();
				else if( conSettIt.key().toLower() == "mixer" )
					_mixer = conSettIt.value();
				else if( conSettIt.key().toLower() == "oplmode" )
					_oplmode = conSettIt.value();
				else if( conSettIt.key().toLower() == "oplrate" )
					_oplrate = conSettIt.value();

				++conSettIt;
			}
		}
		else if( confIt.key().toUpper() == "GUS" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "gus" )
					_gus = conSettIt.value();
				else if( conSettIt.key().toLower() == "gusrate" )
					_gusrate = conSettIt.value();
				else if( conSettIt.key().toLower() == "gusbase" )
					_gusbase = conSettIt.value();
				else if( conSettIt.key().toLower() == "irq1" )
					_irq1 = conSettIt.value();
				else if( conSettIt.key().toLower() == "irq2" )
					_irq2 = conSettIt.value();
				else if( conSettIt.key().toLower() == "dma1" )
					_dma1 = conSettIt.value();
				else if( conSettIt.key().toLower() == "dma2" )
					_dma2 = conSettIt.value();
				else if( conSettIt.key().toLower() == "ultradir" )
					_ultradir = conSettIt.value();

				++conSettIt;
			}
		}
		else if( confIt.key().toUpper() == "SPEAKER" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "pcspeaker" )
					_pcspeaker = conSettIt.value();
				else if( conSettIt.key().toLower() == "pcrate" )
					_pcrate = conSettIt.value();
				else if( conSettIt.key().toLower() == "tandy" )
					_tandy = conSettIt.value();
				else if( conSettIt.key().toLower() == "tandyrate" )
					_tandyrate = conSettIt.value();
				else if( conSettIt.key().toLower() == "disney" )
					_disney = conSettIt.value();

				++conSettIt;
			}
		}
		else if( confIt.key().toUpper() == "JOYSTICK" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "joysticktype" )
					_joysticktype = conSettIt.value();
				else if( conSettIt.key().toLower() == "timed" )
					_timed = conSettIt.value();
				else if( conSettIt.key().toLower() == "autofire" )
					_autofire = conSettIt.value();
				else if( conSettIt.key().toLower() == "swap34" )
					_swap34 = conSettIt.value();
				else if( conSettIt.key().toLower() == "buttonwrap" )
					_buttonwrap = conSettIt.value();

				++conSettIt;
			}
		}
		else if( confIt.key().toUpper() == "SERIAL" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "serial1" )
					_serial1 = conSettIt.value();
				else if( conSettIt.key().toLower() == "serial2" )
					_serial2 = conSettIt.value();
				else if( conSettIt.key().toLower() == "serial3" )
					_serial3 = conSettIt.value();
				else if( conSettIt.key().toLower() == "serial4" )
					_serial4 = conSettIt.value();

				++conSettIt;
			}
		}
		else if( confIt.key().toUpper() == "DOS" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "xms" )
					_xms = conSettIt.value();
				else if( conSettIt.key().toLower() == "ems" )
					_ems = conSettIt.value();
				else if( conSettIt.key().toLower() == "umb" )
					_umb = conSettIt.value();
				else if( conSettIt.key().toLower() == "keyboardlayout" )
					_keyboardlayout = conSettIt.value();

				++conSettIt;
			}
		}
		else if( confIt.key().toUpper() == "IPX" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "ipx" )
					_ipx = conSettIt.value();

				++conSettIt;
			}
		}

		++confIt;
	}



	query.exec( sqlQuery );
	if( !query.isActive() )
		qWarning() << "Failed to insert settings into database:\t" + query.lastError().text();

	return true;
}

bool GameDatabaseSql::deleteTemplates( const QString &name )
{
	
	if( name.isNull() || name.isEmpty() )
		return false;

	_template_name = name;

	QSqlQuery query( gamedb );

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

	QSqlQuery query( gamedb );

	QString _id_dosbox = QString( "" );

	// Select dosbox id form dosbox
	query.exec( "SELECT ID FROM DOSBOXVERSION WHERE VERSION = '" + version + "';" );

	if( query.isActive() )
	{
		while( query.next() )
			_id_dosbox = query.value( 0 ).toString();
	}

	if( _id_dosbox.isNull() || _id_dosbox.isEmpty() )
		return false;

	QString _id_template = QString( "" );

	// Select id from game template
	query.exec( "SELECT ID FROM GAMETEMPLATES WHERE TEMPLATE = '" + templates + "';" );
	if( query.isActive() )
	{
		while( query.next() )
			_id_template = query.value( 0 ).toString();
	}

	if( _id_template.isNull() || _id_template.isEmpty() )
		_id_template = QUuid::createUuid().toString();

	QString _id = QString( "" );
	_id = QUuid::createUuid().toString();

	if( !templates.isNull() || !templates.isEmpty() )
	{
		QString sqlQuery;
		sqlQuery = "";
		sqlQuery += "INSERT INTO GAME\n";
		sqlQuery += "(\n";
		sqlQuery += "(\tID,";
		sqlQuery += "\tNAME,\n";
		sqlQuery += "\tDB_ID,\n";
		sqlQuery += "\tEXEC,\n";
		sqlQuery += "\tTEMPLATE\n";
		sqlQuery += ")\n";
		sqlQuery += "VALUES\n";
		sqlQuery += "(\n";
		sqlQuery += "(\t" + _id + ",\n";
		sqlQuery += "\t" + name + ",\n";
		sqlQuery += "\t" + _id_dosbox + ",\n";
		sqlQuery += "\t" + executable + ",\n";
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
	query.exec( "SELECT DISTINCT VERSION FROM DOSBOXVERSION ORDER BY VERSION;" );
	if( query.isActive() )
		while( query.next() )
		{
			dosboxVersionList.append( query.value( 0 ).toString() );
		}
	else
		qWarning() << "Can't get dosbox version from table 'DOSBOXVERSION':\t" + query.lastError().text();

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
	sqlQuery += "WHERE DI.VERSION = '" + version + "';";

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
	sqlQuery += "JOIN DOSBOXVERSION D ON G.DB_ID = D.ID";

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

