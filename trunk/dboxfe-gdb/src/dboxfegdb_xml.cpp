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

#include "dboxfegdb_xml.h"

#include <XMLPreferences.h>

#include <QtCore>
#include <QtXml>

GameDatabaseXml::GameDatabaseXml( QObject *parent ) : QObject( parent )
{
	object = parent;
}

GameDatabaseXml::~GameDatabaseXml()
{}

QMap< QString, QMap<QString, QString> > GameDatabaseXml::parseDosBoxGameXml( const QString &xml )
{
	QFile file( xml );

	if ( !file.open( QIODevice::ReadOnly ) )
		return gameDosBoxList;

	xmlFile = xml;

	QDomDocument doc;

	doc.setContent( &file );
	file.close();
	QDomNode item = doc.documentElement().firstChild();

	gameDosBoxList.clear();
	attributes.clear();

	while ( !item.isNull() )
	{
		if ( item.isElement() && item.nodeName() == "game" )
		{
			QDomNode subitem = item.toElement().firstChild();
			while ( !subitem.isNull() )
			{
				if ( subitem.toElement().tagName() == "title" )
				{
					title = subitem.toElement().text();
				}
				else if ( subitem.toElement().tagName() == "year" )
				{
					attributes.insert( "year", subitem.toElement().text() );
				}
				else if ( subitem.toElement().tagName() == "sw_house" )
				{
					attributes.insert( "sw_house", subitem.toElement().text() );
				}
				else if ( subitem.toElement().tagName() == "link" )
				{
					attributes.insert( "link", subitem.toElement().text() );
				}
				else if ( subitem.toElement().tagName() == "dosbox" )
				{
					QDomNode attrib = subitem.toElement().firstChild();
					while ( !attrib.isNull() )
					{
						if ( attrib.toElement().tagName() == "info" )
						{
							attributes.insert( "version", attrib.toElement().attribute( "version" ) );
							attributes.insert( "comp_percent", attrib.toElement().attribute( "comp_percent" ) );
						}
						attrib = attrib.nextSibling();	
					}				
				}
				subitem = subitem.nextSibling();
			}
			gameDosBoxList.insert( title, attributes );
		}

		item = item.nextSibling();
	}

	return gameDosBoxList;
}

QStringList GameDatabaseXml::parseGameXml( const QString &xml )
{
	if( xml.isNull() || xml.isEmpty() )
		return QStringList();
	
	xmlFile = xml;
	
	getPreferenceInstance().load( xml );
	gameList = getPreferenceInstance().getStringList( "Games", "Name" );

	return gameList;
}

QStringList GameDatabaseXml::parseGameTemplates( const QString &xml )
{
	if( xml.isNull() || xml.isEmpty() )
		return QStringList();
	
	getPreferenceInstance().load( xml );
	gameTemplateList = getPreferenceInstance().getStringList( "ConfigTemplate", "Name" );

	return gameTemplateList;
}

QStringList GameDatabaseXml::insert( const QString &name, const QString &templateName )
{
	if ( name.isNull() || name.isEmpty() || name == "" )
		return gameList;

	for ( int i = 0; i < gameList.size(); i++ )
	{
		QStringList _gameList = gameList.value( i ).split( ";" );

		if ( QString( _gameList.value( 0 ) ).toLower() != name.toLower() )
			gameList.append( name + ";" + "" );
	}

	return gameList;
}

QStringList GameDatabaseXml::insert( const QString &name, const QString &executable, const QString &templateName )
{
	if ( name.isNull() || name.isEmpty() || name == "" )
		return gameList;

	for ( int i = 0; i < gameList.size(); i++ )
	{
		QStringList _gameList = gameList.value( i ).split( ";" );

		if ( QString( _gameList.value( 0 ) ).toLower() != name.toLower() )
			gameList.append( name + ";" + executable );
	}

	return gameList;
}

QStringList GameDatabaseXml::update( const QString &name, const QString &templateName )
{
	if ( name.isNull() || name.isEmpty() || name == "" )
		return gameList;

	for ( int i = 0; i < gameList.size(); i++ )
	{
		QStringList _gameList = gameList.value( i ).split( ";" );

		if ( QString( _gameList.value( 0 ) ).toLower() == name.toLower() )
			if( templateName.isNull() || templateName.isEmpty() )
				gameList.replace( i, name + ";" + "" );
			else
				gameList.replace( i, name + ";" + templateName );
			
	}

	return gameList;
}

QStringList GameDatabaseXml::update( const QString &name, const QString &executable, const QString &templateName )
{
	if ( name.isNull() || name.isEmpty() || name == "" )
		return gameList;

	for ( int i = 0; i < gameList.size(); i++ )
	{
		QStringList _gameList = gameList.value( i ).split( ";" );

		if ( QString( _gameList.value( 0 ) ).toLower() == name.toLower() )
			gameList.replace( i, name + ";" + executable );
	}

	return gameList;
}

QStringList GameDatabaseXml::remove( const QString &name )
{
	if ( name.isNull() || name.isEmpty() || name == "" )
		return gameList;

	for ( int i = 0; i < gameList.size(); i++ )
	{
		QStringList _gameList = gameList.value( i ).split( ";" );

		if ( QString( _gameList.value( 0 ) ).toLower() == name.toLower() )
			gameList.removeAt( i );
	}

	return gameList;
}

void GameDatabaseXml::save( const QString &xml )
{
	getPreferenceInstance().setStringList( "Games", "Name", gameList );
	getPreferenceInstance().setStringList( "ConfigTemplate", "Name", gameTemplateList );

	if ( !xml.isNull() || !xml.isEmpty() || xml != "" )
		getPreferenceInstance().save( xmlFile );
	else
	{
		xmlFile = xml;
		getPreferenceInstance().save( xml );
	}
	
}

XMLPreferences GameDatabaseXml::getPreferenceInstance()
{
	XMLPreferences xmlPreferences( "DBoxFE", "Alexander Saal" );
	xmlPreferences.setVersion( "v0.1.3" );
	return xmlPreferences;
}
