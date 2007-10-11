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

#ifndef DBOXFEGDB_XML_H
#define DBOXFEGDB_XML_H

#include <QtCore>
#include <QtXml>

#include <XMLPreferences.h>

/**
 * Class for DBoxFE-GDB
 *
 * @class GameDatabaseXml dboxfegdb_xml.h "GameDatabaseXml"
 * @author Alexander Saal <alex.saal@gmx.de>
 * @date 2007/09/17
 * @version 0.1.3
 * @since 0.1.3
 */
class GameDatabaseXml : public QObject
{
	Q_OBJECT

	public:
		/**
	 	 * Default constructor
		 */
		GameDatabaseXml( QObject *parent = 0 );
		~GameDatabaseXml();
		
		/**
		 * Parse dosbox game xml file
		 * @param xml the DOSBox game xml file
		 * @return a QMap<QString, QMap<QString, QString>> with all games from dosbox xml file<br>
		 *         QString = name of dosbox game<br>
		 *         QMap<QString, QString> = attributes of dosbox game
		 */
		QMap< QString, QMap<QString, QString> > parseDosBoxGameXml( const QString &xml );

		/**
		 * Parse dboxfe game xml file and return dosbox version in a QStringList
		 * @param xml the DOSBox game xml file
		 * @return a QStringList with all version of dosbox
		 */
		QStringList getDosBoxVersion( const QString &xml );

		/**
		 * Parse dboxfe game xml file
		 * @param xml the DBoxFE game xml file
		 * @return a QStringList with all games
		 */
		QStringList parseGameXml( const QString &xml );
		
		/**
		 * Parse dboxfe game xml file
		 * @param xml the DBoxFE game xml file
		 * @return a QStringList with all games
		 */
		QStringList parseGameTemplates( const QString & xml );
		
		/**
		 * Insert a game into xml database
		 * @param name the Gamename
		 * @return a QStringList with all games
		 */
		QStringList insert( const QString &name, const QString &templateName );
		
		/**
		 * Insert a game into xml database
		 * @param name the Gamename
		 * @param executable the Gameexecutable
		 * @return a QStringList with all games
		 */
		QStringList insert( const QString &name, const QString &executable, const QString &templateName );
		
		/**
		 * Update a game on xml database
		 * @param name the Gamename
		 * @return a QStringList with all games
		 */
		QStringList update( const QString &name, const QString &templateName );
		
		/**
		 * Update a game on xml database
		 * @param name the Gamename
		 * @param executable the Gameexecutable
		 * @return a QStringList with all games
		 */
		QStringList update( const QString &name, const QString &executable, const QString &templateName );
		
		/**
		 * Delete a game from xml database
		 * @param name the Gamename
		 * @return a QStringList with all games
		 */
		QStringList remove( const QString &name );

		/**
		 * Check a consistence of the game xml database from dosbox
		 * @param xml the DOSBox Game Xml file
		 * @return true, if the xml a dosbox game xml
		 */
		bool checkDosBoxGameXml( const QString &xml );

	public slots:
		
		/**
	 	 * Save the dboxfe game xml
	 	 * @param xml the DBoxFE game xml file
		 */
		void save( const QString &xml = QString() );
		
	private:
		XMLPreferences getPreferenceInstance();
		QDomNode getDocument( const QString &xml );

		QMap<QString, QMap<QString, QString> > gameDosBoxList;
		QMap<QString, QString> attributes;

		QStringList dosboxVersionList;
		QStringList gameList;
		QStringList gameTemplateList;
		QStringList attribute;

		QString title;
		QString year;
		QString sw_house;
		QString link;
		QString xmlFile;

		QObject *object;
};

#endif // DBOXFEGDB_XML_H
