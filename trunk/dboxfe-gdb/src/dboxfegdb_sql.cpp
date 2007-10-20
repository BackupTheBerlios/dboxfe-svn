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
			qWarning() << "Failed to create tables on " + sqlDatabase + ":\t" + query.lastError().text();
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

bool GameDatabaseSql::updateTemplates( const QString &name, QMap< QString, QMap< QString, QVariant > > &settings )
{
	if( name.isNull() || name.isEmpty() )
		return false;

	if( settings.size() <= 0 )
		return false;

	_template_name = name;

	sett.clear();
	sett = settings;

	QSqlQuery query( gamedb );

	return true;
}

bool GameDatabaseSql::insertTemplates( const QString &name, QComboBox *cbx )
{	
	if( name.isNull() || name.isEmpty() )
		return false;
	
	if( !isOpen() )
		return false;

	cbx->clear();

	QSqlQuery query( gamedb );

	QString _id = QUuid::createUuid().toString();

	QString sqlQuery;
	sqlQuery = "";
	sqlQuery += "INSERT INTO GAMETEMPLATES\n";
	sqlQuery += "(\n";
	sqlQuery += "\tID,\n";
	sqlQuery += "\tNAME\n";
	sqlQuery += ")\n";
	sqlQuery += "VALUES\n";
	sqlQuery += "(\n";
	sqlQuery += "\t'" + _id + "',\n";
	sqlQuery += "\t'" + name + "'\n";
	sqlQuery += ");";

	query.exec( sqlQuery );
	if( !query.isActive() )
			qWarning() << "Failed to insert templates into database:\t" + query.lastError().text();

	sqlQuery.clear();
	sqlQuery = "";
	sqlQuery += "SELECT NAME\n";
	sqlQuery += "FROM GAMETEMPLATES;";
	
	query.exec( sqlQuery );	
	if( query.isActive() )
		while( query.next() )
			cbx->addItem( query.value( 0 ).toString() );
}

bool GameDatabaseSql::insertTemplates( const QString &name, QMap< QString, QMap< QString, QVariant > > &settings )
{
	if( name.isNull() || name.isEmpty() )
		return false;

	if( settings.size() <= 0 )
		return false;

	_template_name = name;

	sett.clear();
	sett = settings;

	QSqlQuery query( gamedb );

	QString _id;

	QString sqlQuery;
	sqlQuery = "";
	sqlQuery += "SELECT ID\n";
	sqlQuery += "FROM GAMETEMPLATES\n";
	sqlQuery += "WHERE NAME = '" + name + "';";

	query.exec( sqlQuery );
	if( query.isActive() )
	{
		while( query.next() )
			_id = query.value( 0 ).toString();
	}
	else
	{
		qWarning() << "Failed to insert templates into database:\t" + query.lastError().text();
	}

	if( _id.isNull() || _id.isEmpty() )
		return false;

	QMap< QString, QVariant>::const_iterator conSettIt;
	QMap< QString, QMap< QString, QVariant> >::const_iterator confIt = sett.begin();

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
					_fullscreen = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "fulldouble" )
					_fulldouble = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "fullresolution" )
					_fullresolution = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "windowresolution" )
					_windowresolution = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "output" )
					_output = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "autolock" )
					_autolock = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "sensitivity" )
					_sensitivity = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "waitonerror" )
					_waitonerror = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "priority" )
					_priority = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "mapperfile" )
					_mapperfile = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "usescancodes" )
					_usescancodes = conSettIt.value().toString();

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
					_language = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "machine" )
					_machine = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "captures" )
					_captures = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "memsize" )
					_memsize = conSettIt.value().toString();

				++conSettIt;
			}

			sqlDosBox = "";
			sqlDosBox += "INSERT INTO DOSBOX\n";
			sqlDosBox += "(\n";
			sqlDosBox += "\tID,\n";
			sqlDosBox += "\tLANGUAGE,\n";
			sqlDosBox += "\tMACHINE,\n";
			sqlDosBox += "\tCAPTURES,\n";
			sqlDosBox += "\tMEMSIZE\n";
			sqlDosBox += ")\n";
			sqlDosBox += "VALUES\n";
			sqlDosBox += "(\n";
			sqlDosBox += "\t'" + _id + "',\n";
			sqlDosBox += "\t'" + _language + "',\n";
			sqlDosBox += "\t'" + _machine + "',\n";
			sqlDosBox += "\t'" + _captures + "',\n";
			sqlDosBox += "\t'" + _memsize + "'\n";
			sqlDosBox += ");";
		}
		else if( confIt.key().toUpper() == "RENDER" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "frameskip" )
					_frameskip = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "aspect" )
					_aspect = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "scaler" )
					_scaler = conSettIt.value().toString();

				++conSettIt;
			}

			sqlRender = "";
			sqlRender += "INSERT INTO RENDER\n";
			sqlRender += "(\n";
			sqlRender += "\tID,\n";
			sqlRender += "\tFRAMESKIP,\n";
			sqlRender += "\tASPECT,\n";
			sqlRender += "\tSCALER\n";
			sqlRender += ")\n";
			sqlRender += "VALUES\n";
			sqlRender += "(\n";
			sqlRender += "\t'" + _id + "',\n";
			sqlRender += "\t'" + _frameskip + "',\n";
			sqlRender += "\t'" + _aspect + "',\n";
			sqlRender += "\t'" + _scaler + "'\n";
			sqlRender += ");";
		}
		else if( confIt.key().toUpper() == "CPU" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "core" )
					_core = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "cycles" )
					_cycles = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "cycleup" )
					_cycleup = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "cycledown" )
					_cycledown = conSettIt.value().toString();

				++conSettIt;
			}

			sqlCpu = "";
			sqlCpu += "INSERT INTO CPU\n";
			sqlCpu += "(\n";
			sqlCpu += "\tID,\n";
			sqlCpu += "\tCORE,\n";
			sqlCpu += "\tCYCLES,\n";
			sqlCpu += "\tCYCLEUP,\n";
			sqlCpu += "\tCYCLEDOWN\n";
			sqlCpu += ")\n";
			sqlCpu += "VALUES\n";
			sqlCpu += "(\n";
			sqlCpu += "\t'" + _id + "',\n";
			sqlCpu += "\t'" + _core + "',\n";
			sqlCpu += "\t'" + _cycles + "',\n";
			sqlCpu += "\t'" + _cycleup + "',\n";
			sqlCpu += "\t'" + _cycledown + "'\n";
			sqlCpu += ");";
		}
		else if( confIt.key().toUpper() == "MIXER" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "nosound" )
					_nosound = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "rate" )
					_rate = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "blocksize" )
					_blocksize = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "prebuffer" )
					_prebuffer = conSettIt.value().toString();

				++conSettIt;
			}

			sqlMixer = "";
			sqlMixer += "INSERT INTO MIXER\n";
			sqlMixer += "(\n";
			sqlMixer += "\tID,\n";
			sqlMixer += "\tNOSOUND,\n";
			sqlMixer += "\tRATE,\n";
			sqlMixer += "\tBLOCKSIZE,\n";
			sqlMixer += "\tPREBUFFER\n";
			sqlMixer += ")\n";
			sqlMixer += "VALUES\n";
			sqlMixer += "(\n";
			sqlMixer += "\t'" + _id + "',\n";
			sqlMixer += "\t'" + _nosound + "',\n";
			sqlMixer += "\t'" + _rate + "',\n";
			sqlMixer += "\t'" + _blocksize + "',\n";
			sqlMixer += "\t'" + _prebuffer + "'\n";
			sqlMixer += ");";
		}
		else if( confIt.key().toUpper() == "MIDI" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "device" )
					_device = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "config" )
					_config = conSettIt.value().toString();

				++conSettIt;
			}

			sqlMidi = "";
			sqlMidi += "INSERT INTO MIDI\n";
			sqlMidi += "(\n";
			sqlMidi += "\tID,\n";
			sqlMidi += "\tDEVICE,\n";
			sqlMidi += "\tCONFIG\n";
			sqlMidi += ")\n";
			sqlMidi += "VALUES\n";
			sqlMidi += "(\n";
			sqlMidi += "\t'" + _id + "',\n";
			sqlMidi += "\t'" + _device + "',\n";
			sqlMidi += "\t'" + _config + "'\n";
			sqlMidi += ");";
		}
		else if( confIt.key().toUpper() == "SBLASTER" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "sbtype" )
					_sbtype = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "sbbase" )
					_sbbase = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "irq" )
					_irq = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "dma" )
					_dma = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "hdma" )
					_hdma = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "mixer" )
					_mixer = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "oplmode" )
					_oplmode = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "oplrate" )
					_oplrate = conSettIt.value().toString();

				++conSettIt;
			}

			sqlSbBlaster = "";
			sqlSbBlaster += "INSERT INTO SBLASTER\n";
			sqlSbBlaster += "(\n";
			sqlSbBlaster += "\tID,\n";
			sqlSbBlaster += "\tSBTYPE,\n";
			sqlSbBlaster += "\tSBBASE,\n";
			sqlSbBlaster += "\tIRQ,\n";
			sqlSbBlaster += "\tDMA,\n";
			sqlSbBlaster += "\tHDMA,\n";
			sqlSbBlaster += "\tMIXER,\n";
			sqlSbBlaster += "\tOPLMODE,\n";
			sqlSbBlaster += "\tOPLRATE\n";
			sqlSbBlaster += ")\n";
			sqlSbBlaster += "VALUES\n";
			sqlSbBlaster += "(\n";
			sqlSbBlaster += "\t'" + _id + "',\n";
			sqlSbBlaster += "\t'" + _sbtype + "',\n";
			sqlSbBlaster += "\t'" + _sbbase + "',\n";
			sqlSbBlaster += "\t'" + _irq + "',\n";
			sqlSbBlaster += "\t'" + _dma + "',\n";
			sqlSbBlaster += "\t'" + _hdma + "',\n";
			sqlSbBlaster += "\t'" + _mixer + "',\n";
			sqlSbBlaster += "\t'" + _oplmode + "',\n";
			sqlSbBlaster += "\t'" + _oplrate + "'\n";
			sqlSbBlaster += ");";
		}
		else if( confIt.key().toUpper() == "GUS" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "gus" )
					_gus = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "gusrate" )
					_gusrate = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "gusbase" )
					_gusbase = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "irq1" )
					_irq1 = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "irq2" )
					_irq2 = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "dma1" )
					_dma1 = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "dma2" )
					_dma2 = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "ultradir" )
					_ultradir = conSettIt.value().toString();

				++conSettIt;
			}

			sqlGus = "";
			sqlGus += "INSERT INTO GUS\n";
			sqlGus += "(\n";
			sqlGus += "\tID,\n";
			sqlGus += "\tGUS,\n";
			sqlGus += "\tGUSRATE,\n";
			sqlGus += "\tGUSBASE,\n";
			sqlGus += "\tIRQ1,\n";
			sqlGus += "\tIRQ1,\n";
			sqlGus += "\tDMA1,\n";
			sqlGus += "\tDMA2,\n";
			sqlGus += "\tULTRADIR\n";
			sqlGus += ")\n";
			sqlGus += "VALUES\n";
			sqlGus += "(\n";
			sqlGus += "\t'" + _id + "',\n";
			sqlGus += "\t'" + _gus + "',\n";
			sqlGus += "\t'" + _gusrate + "',\n";
			sqlGus += "\t'" + _gusbase + "',\n";
			sqlGus += "\t'" + _irq1 + "',\n";
			sqlGus += "\t'" + _irq2 + "',\n";
			sqlGus += "\t'" + _dma1 + "',\n";
			sqlGus += "\t'" + _dma2 + "',\n";
			sqlGus += "\t'" + _ultradir + "'\n";
			sqlGus += ");";
		}
		else if( confIt.key().toUpper() == "SPEAKER" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "pcspeaker" )
					_pcspeaker = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "pcrate" )
					_pcrate = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "tandy" )
					_tandy = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "tandyrate" )
					_tandyrate = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "disney" )
					_disney = conSettIt.value().toString();

				++conSettIt;
			}

			sqlSpeaker = "";
			sqlSpeaker += "INSERT INTO SPEAKER\n";
			sqlSpeaker += "(\n";
			sqlSpeaker += "\tID,\n";
			sqlSpeaker += "\tPCSPEAKER,\n";
			sqlSpeaker += "\tPCRATE,\n";
			sqlSpeaker += "\tTANDY,\n";
			sqlSpeaker += "\tTANDYRATE,\n";
			sqlSpeaker += "\tDISNEY\n";
			sqlSpeaker += ")\n";
			sqlSpeaker += "VALUES\n";
			sqlSpeaker += "(\n";
			sqlSpeaker += "\t'" + _id + "',\n";
			sqlSpeaker += "\t'" + _pcspeaker + "',\n";
			sqlSpeaker += "\t'" + _pcrate + "',\n";
			sqlSpeaker += "\t'" + _tandy + "',\n";
			sqlSpeaker += "\t'" + _tandyrate + "',\n";
			sqlSpeaker += "\t'" + _disney + "'\n";
			sqlSpeaker += ");";
		}
		else if( confIt.key().toUpper() == "JOYSTICK" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "joysticktype" )
					_joysticktype = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "timed" )
					_timed = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "autofire" )
					_autofire = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "swap34" )
					_swap34 = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "buttonwrap" )
					_buttonwrap = conSettIt.value().toString();

				++conSettIt;
			}

			sqlJoystick = "";
			sqlJoystick += "INSERT INTO JOYSTICK\n";
			sqlJoystick += "(\n";
			sqlJoystick += "\tID,\n";
			sqlJoystick += "\tJOYSTICKTYPE,\n";
			sqlJoystick += "\tTIMED,\n";
			sqlJoystick += "\tAUTOFIRE,\n";
			sqlJoystick += "\tSWAP34,\n";
			sqlJoystick += "\tBUTTONWRAP\n";
			sqlJoystick += ")\n";
			sqlJoystick += "VALUES\n";
			sqlJoystick += "(\n";
			sqlJoystick += "\t'" + _id + "',\n";
			sqlJoystick += "\t'" + _joysticktype + "',\n";
			sqlJoystick += "\t'" + _timed + "',\n";
			sqlJoystick += "\t'" + _autofire + "',\n";
			sqlJoystick += "\t'" + _swap34 + "',\n";
			sqlJoystick += "\t'" + _buttonwrap + "'\n";
			sqlJoystick += ");";
		}
		else if( confIt.key().toUpper() == "SERIAL" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "serial1" )
					_serial1 = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "serial2" )
					_serial2 = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "serial3" )
					_serial3 = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "serial4" )
					_serial4 = conSettIt.value().toString();

				++conSettIt;
			}

			sqlSerial = "";
			sqlSerial += "INSERT INTO SERIAL\n";
			sqlSerial += "(\n";
			sqlSerial += "\tID,\n";
			sqlSerial += "\tSERIAL1,\n";
			sqlSerial += "\tSERIAL2,\n";
			sqlSerial += "\tSERIAL3,\n";
			sqlSerial += "\tSERIAL4\n";
			sqlSerial += ")\n";
			sqlSerial += "VALUES\n";
			sqlSerial += "(\n";
			sqlSerial += "\t'" + _id + "',\n";
			sqlSerial += "\t'" + _serial1 + "',\n";
			sqlSerial += "\t'" + _serial2 + "',\n";
			sqlSerial += "\t'" + _serial3 + "',\n";
			sqlSerial += "\t'" + _swap34 + "'\n";
			sqlSerial += ");";
		}
		else if( confIt.key().toUpper() == "DOS" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "xms" )
					_xms = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "ems" )
					_ems = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "umb" )
					_umb = conSettIt.value().toString();
				else if( conSettIt.key().toLower() == "keyboardlayout" )
					_keyboardlayout = conSettIt.value().toString();

				++conSettIt;
			}

			sqlDos = "";
			sqlDos += "INSERT INTO DOS\n";
			sqlDos += "(\n";
			sqlDos += "\tID,\n";
			sqlDos += "\tXMS,\n";
			sqlDos += "\tEMS,\n";
			sqlDos += "\tUMB,\n";
			sqlDos += "\tKEYBOARDLAYOUT\n";
			sqlDos += ")\n";
			sqlDos += "VALUES\n";
			sqlDos += "(\n";
			sqlDos += "\t'" + _id + "',\n";
			sqlDos += "\t'" + _xms + "',\n";
			sqlDos += "\t'" + _ems + "',\n";
			sqlDos += "\t'" + _umb + "',\n";
			sqlDos += "\t'" + _keyboardlayout + "'\n";
			sqlDos += ");";
		}
		else if( confIt.key().toUpper() == "IPX" )
		{
			conSettIt = confIt.value().begin();
			while( conSettIt != confIt.value().end() )
			{
				qApp->processEvents();

				if( conSettIt.key().toLower() == "ipx" )
					_ipx = conSettIt.value().toString();

				++conSettIt;
			}

			sqlIpx = "";
			sqlIpx += "INSERT INTO IPX\n";
			sqlIpx += "(\n";
			sqlIpx += "\tID,\n";
			sqlIpx += "\tIPX\n";
			sqlIpx += ")\n";
			sqlIpx += "VALUES\n";
			sqlIpx += "(\n";
			sqlIpx += "\t'" + _id + "',\n";
			sqlIpx += "\t'" + _ipx + "'\n";
			sqlIpx += ");";
		}

		++confIt;
	}

	query.exec( sqlSdl );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlDosBox );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlRender );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlCpu );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlMixer );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlMidi );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlSbBlaster );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlGus );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlSpeaker );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlJoystick );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlSerial );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlDos );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

	query.exec( sqlIpx );
	if( !query.isActive() )
		qWarning() << "Failed to insert entities into database:\t" + query.lastError().text();

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
	query.exec( "SELECT ID FROM GAMETEMPLATES WHERE NAME = '" + templates + "';" );
	if( query.isActive() )
	{
		while( query.next() )
			_id_template = query.value( 0 ).toString();
	}

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

		if( _id_template.isNull() || _id_template.isEmpty() )
			sqlQuery += "\tEXEC\n";
		else
		{
			sqlQuery += "\tEXEC,\n";
			sqlQuery += "\tTEMPLATE\n";
		}		

		sqlQuery += ")\n";
		sqlQuery += "VALUES\n";
		sqlQuery += "(\n";
		sqlQuery += "\t'" + _id + "',\n";
		sqlQuery += "\t'" + name + "',\n";
		sqlQuery += "\t'" + _id_dosbox + "',\n";

		if( _id_template.isNull() || _id_template.isEmpty() )
			sqlQuery += "\t'" + executable + "'\n";
		else
		{
			sqlQuery += "\t'" + executable + "',\n";
			sqlQuery += "\t'" + _id_template + "'\n";
		}
		
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

QMap< QString, QMap< QString, QVariant > > GameDatabaseSql::selectTemplateSettings( const QString &name )
{
	if( !isOpen() )
		return templateSettings;

	if( name.isNull() || name.isEmpty() )
		return templateSettings;

	QString templateId = QString( "" );

	QSqlQuery query( gamedb );
	query.exec( "SELECT ID FROM GAMETEMPLATES WHERE NAME = '" + name + "';" );
	if( query.isActive() )
		while( query.next() )
			templateId = query.value( 0 ).toString();

	sqlSdl = "";
	sqlSdl += "SELECT\tFULLSCREEN,\n";
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
	sqlSdl += "FROM\tSDL\n";
	sqlSdl += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlSdl );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "fullscreen", query.value( 0 ) );
			subTemplateSettings.insert( "fulldouble", query.value( 1 ) );
			subTemplateSettings.insert( "fullresolution", query.value( 2 ) );
			subTemplateSettings.insert( "windowresolution", query.value( 3 ) );
			subTemplateSettings.insert( "output", query.value( 4 ) );
			subTemplateSettings.insert( "autolock", query.value( 5 ) );
			subTemplateSettings.insert( "sensitivity", query.value( 6 ) );
			subTemplateSettings.insert( "waitonerror", query.value( 7 ) );			
			subTemplateSettings.insert( "priority", query.value( 8 ) );
			subTemplateSettings.insert( "mapperfile", query.value( 9 ) );
			subTemplateSettings.insert( "usescancodes", query.value( 10 ) );
		}
		templateSettings.insert( "SDL", subTemplateSettings );
	}

	sqlDosBox = "";
	sqlDosBox += "SELECT\n";
	sqlDosBox += "\tLANGUAGE,\n";
	sqlDosBox += "\tMACHINE,\n";
	sqlDosBox += "\tCAPTURES,\n";
	sqlDosBox += "\tMEMSIZE\n";
	sqlDosBox += "FROM\tDOSBOX\n";
	sqlDosBox += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlDosBox );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "language", query.value( 0 ) );
			subTemplateSettings.insert( "machine", query.value( 1 ) );
			subTemplateSettings.insert( "captures", query.value( 2 ) );
			subTemplateSettings.insert( "memsize", query.value( 3 ) );
		}
		templateSettings.insert( "DOSBOX", subTemplateSettings );
	}

	sqlRender = "";
	sqlRender += "SELECT\n";
	sqlRender += "\tFRAMESKIP,\n";
	sqlRender += "\tASPECT,\n";
	sqlRender += "\tSCALER\n";
	sqlRender += "FROM\tRENDER\n";
	sqlRender += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlRender );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "frameskip", query.value( 0 ) );
			subTemplateSettings.insert( "aspect", query.value( 1 ) );
			subTemplateSettings.insert( "scaler", query.value( 2 ) );
		}
		templateSettings.insert( "RENDER", subTemplateSettings );
	}

	sqlCpu = "";
	sqlCpu += "SELECT\n";
	sqlCpu += "\tCORE,\n";
	sqlCpu += "\tCYCLES,\n";
	sqlCpu += "\tCYCLEUP,\n";
	sqlCpu += "\tCYCLEDOWN\n";
	sqlCpu += "FROM\tCPU\n";
	sqlCpu += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlCpu );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "core", query.value( 0 ) );
			subTemplateSettings.insert( "cycles", query.value( 1 ) );
			subTemplateSettings.insert( "cycleup", query.value( 2 ) );
			subTemplateSettings.insert( "cycledown", query.value( 3 ) );
		}
		templateSettings.insert( "CPU", subTemplateSettings );
	}

	sqlMixer = "";
	sqlMixer += "SELECT\n";
	sqlMixer += "\tNOSOUND,\n";
	sqlMixer += "\tRATE,\n";
	sqlMixer += "\tBLOCKSIZE,\n";
	sqlMixer += "\tPREBUFFER\n";
	sqlMixer += "FROM\tMIXER\n";
	sqlMixer += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlMixer );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "nosound", query.value( 0 ) );
			subTemplateSettings.insert( "rate", query.value( 1 ) );
			subTemplateSettings.insert( "blocksize", query.value( 2 ) );
			subTemplateSettings.insert( "prebuffer", query.value( 3 ) );
		}
		templateSettings.insert( "MIXER", subTemplateSettings );
	}

	sqlMidi = "";
	sqlMidi += "SELECT\n";
	sqlMidi += "\tDEVICE,\n";
	sqlMidi += "\tCONFIG\n";
	sqlMidi += "FROM\tMIDI\n";
	sqlMidi += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlMidi );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "device", query.value( 0 ) );
			subTemplateSettings.insert( "config", query.value( 1 ) );
		}
		templateSettings.insert( "MIDI", subTemplateSettings );
	}

	sqlSbBlaster = "";
	sqlSbBlaster += "SELECT\n";
	sqlSbBlaster += "\tSBTYPE,\n";
	sqlSbBlaster += "\tSBBASE,\n";
	sqlSbBlaster += "\tIRQ,\n";
	sqlSbBlaster += "\tDMA,\n";
	sqlSbBlaster += "\tHDMA,\n";
	sqlSbBlaster += "\tMIXER,\n";
	sqlSbBlaster += "\tOPLMODE,\n";
	sqlSbBlaster += "\tOPLRATE\n";
	sqlSbBlaster += "FROM\tSBLASTER\n";
	sqlSbBlaster += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlSbBlaster );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "sbtype", query.value( 0 ) );
			subTemplateSettings.insert( "sbbase", query.value( 1 ) );
			subTemplateSettings.insert( "irq", query.value( 2 ) );
			subTemplateSettings.insert( "dma", query.value( 3 ) );
			subTemplateSettings.insert( "hdma", query.value( 4 ) );
			subTemplateSettings.insert( "mixer", query.value( 5 ) );
			subTemplateSettings.insert( "oplmode", query.value( 6 ) );
			subTemplateSettings.insert( "oplrate", query.value( 7 ) );
		}
		templateSettings.insert( "SBLASTER", subTemplateSettings );
	}

	sqlGus = "";
	sqlGus += "SELECT\n";
	sqlGus += "\tGUS,\n";
	sqlGus += "\tGUSRATE,\n";
	sqlGus += "\tGUSBASE,\n";
	sqlGus += "\tIRQ1,\n";
	sqlGus += "\tIRQ1,\n";
	sqlGus += "\tDMA1,\n";
	sqlGus += "\tDMA2,\n";
	sqlGus += "\tULTRADIR\n";
	sqlGus += "FROM\tGUS\n";
	sqlGus += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlGus );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "gus", query.value( 0 ) );
			subTemplateSettings.insert( "gusrate", query.value( 1 ) );
			subTemplateSettings.insert( "gusbase", query.value( 2 ) );
			subTemplateSettings.insert( "irq1", query.value( 3 ) );
			subTemplateSettings.insert( "irq2", query.value( 4 ) );
			subTemplateSettings.insert( "dma1", query.value( 5 ) );
			subTemplateSettings.insert( "dma2", query.value( 6 ) );
			subTemplateSettings.insert( "ultradir", query.value( 7 ) );
		}
		templateSettings.insert( "GUS", subTemplateSettings );
	}

	sqlSpeaker = "";
	sqlSpeaker += "SELECT\n";
	sqlSpeaker += "\tPCSPEAKER,\n";
	sqlSpeaker += "\tPCRATE,\n";
	sqlSpeaker += "\tTANDY,\n";
	sqlSpeaker += "\tTANDYRATE,\n";
	sqlSpeaker += "\tDISNEY\n";
	sqlSpeaker += "FROM\tSPEAKER\n";
	sqlSpeaker += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlSpeaker );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "pcspeaker", query.value( 0 ) );
			subTemplateSettings.insert( "pcrate", query.value( 1 ) );
			subTemplateSettings.insert( "tandy", query.value( 2 ) );
			subTemplateSettings.insert( "tandyrate", query.value( 3 ) );
			subTemplateSettings.insert( "disney", query.value( 4 ) );
		}
		templateSettings.insert( "SPEAKER", subTemplateSettings );
	}

	sqlJoystick = "";
	sqlJoystick += "SELECT\n";
	sqlJoystick += "\tJOYSTICKTYPE,\n";
	sqlJoystick += "\tTIMED,\n";
	sqlJoystick += "\tAUTOFIRE,\n";
	sqlJoystick += "\tSWAP34,\n";
	sqlJoystick += "\tBUTTONWRAP\n";
	sqlJoystick += "FROM\tJOYSTICK\n";
	sqlJoystick += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlJoystick );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "joysticktype", query.value( 0 ) );
			subTemplateSettings.insert( "timed", query.value( 1 ) );
			subTemplateSettings.insert( "autofire", query.value( 2 ) );
			subTemplateSettings.insert( "swap34", query.value( 3 ) );
			subTemplateSettings.insert( "buttonwrap", query.value( 4 ) );
		}
		templateSettings.insert( "JOYSTICK", subTemplateSettings );
	}

	sqlSerial = "";
	sqlSerial += "SELECT\n";
	sqlSerial += "\tSERIAL1,\n";
	sqlSerial += "\tSERIAL2,\n";
	sqlSerial += "\tSERIAL3,\n";
	sqlSerial += "\tSERIAL4\n";
	sqlSerial += "FROM\tSERIAL\n";
	sqlSerial += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlSerial );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "serial1", query.value( 0 ) );
			subTemplateSettings.insert( "serial2", query.value( 1 ) );
			subTemplateSettings.insert( "serial3", query.value( 2 ) );
			subTemplateSettings.insert( "serial4", query.value( 3 ) );
		}
		templateSettings.insert( "SERIAL", subTemplateSettings );
	}

	sqlDos = "";
	sqlDos += "SELECT\n";
	sqlDos += "\tXMS,\n";
	sqlDos += "\tEMS,\n";
	sqlDos += "\tUMB,\n";
	sqlDos += "\tKEYBOARDLAYOUT\n";
	sqlDos += "FROM\tDOS\n";
	sqlDos += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlDos );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "xms", query.value( 0 ) );
			subTemplateSettings.insert( "ems", query.value( 1 ) );
			subTemplateSettings.insert( "umb", query.value( 2 ) );
			subTemplateSettings.insert( "keyboardlayout", query.value( 3 ) );
		}
		templateSettings.insert( "DOS", subTemplateSettings );
	}

	sqlIpx = "";
	sqlIpx += "SELECT\n";
	sqlIpx += "\tIPX\n";
	sqlIpx += "FROM\tIPX\n";
	sqlIpx += "WHERE\tID = '" + templateId + "';";

	query.exec( sqlSerial );
	if( query.isActive() )
	{
		subTemplateSettings.clear();
		while( query.next() )
		{
			subTemplateSettings.insert( "ipx", query.value( 0 ) );
		}
		templateSettings.insert( "IPX", subTemplateSettings );
	}

	return templateSettings;
}

void GameDatabaseSql::selectTemplates( QComboBox *cbx )
{
	if( !isOpen() )
		return;

	cbx->clear();	
	
	QSqlQuery query( gamedb );

	QString sqlQuery;
	sqlQuery.clear();
	sqlQuery = "";
	sqlQuery += "SELECT NAME\n";
	sqlQuery += "FROM GAMETEMPLATES;";
	
	query.exec( sqlQuery );	
	if( query.isActive() )
		while( query.next() )
			cbx->addItem( query.value( 0 ).toString() );
}

bool GameDatabaseSql::isOpen()
{
	if( gamedb.isOpen() )
		return true;

	return false;
}

