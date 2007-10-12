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

#ifndef DBOXFEGDB_SQL_H
#define DBOXFEGDB_SQL_H

#include <QtCore>
#include <QtGui>
#include <QtSql>

/**
 * Class for DBoxFE-GDB
 *
 * @class GameDatabaseSql dboxfegdb_sql.h "GameDatabaseSql"
 * @author Alexander Saal <alex.saal@gmx.de>
 * @date 2007/09/17
 * @version 0.1.3
 * @since 0.1.3
 */
class GameDatabaseSql : public QObject
{
	Q_OBJECT

	public:
		/**
		  * Default constructor
		  * @param parent the parent QObject
		 */
		GameDatabaseSql( QObject *parent = 0 );
		~GameDatabaseSql();

		bool createConnection( const QString &db );
		bool closeConnection();

		/**
		 * Create database
		 * @param name the Database name
		 * @return true is database created
		 */
		bool createDatabase( const QString &name );

		/**
		 * Import dosbox games into database
		 * @param list the DOSBox games to import
		 * @return true if import successfull
		 */
		bool importDosBoxGameList( const QMap<QString, QMap< QString, QStringList> > &list, QProgressBar *pBar = 0, QLabel *lbl = 0 );		
		bool checkReferencesOnDosBoxGames( const QMap<QString, QMap< QString, QString> > &list );

		/**
		 * Import games into database
		 * @param list the Games to import
		 * @return true if import successfull
		 */
		bool importGameList( const QStringList &list );

		/**
		 * Import game templates into database<br>
		 * You must first call importGameList
		 * @param list the Gametemplates to import
		 * @return true if import successfull
		 */
		bool importGameTemplateList( const QStringList &list );

		/**
		 * Store the games from database into a xml file
		 * @param xml the xml
		 * @return true if export successfull
		 */
		bool exportGamesList( const QString & xml );

		/**
		 * Update game
		 * @param name the Game name
		 * @param executable the Executable of game (can be empty)
		 * @param templates the Template of game (can be empty)
		 * @return true if update successfull
		 */
		bool updateGames( const QString &name,
						  const QString &version,
						  const QString &executable = QString(),
						  const QString &templates = QString()
						);

		/**
		 * Insert game into database
		 * @param name the Game name
		 * @param executable the Executable of game (can be empty)
		 * @param templates the Template of game (can be empty)
		 * @return true if insert successfull
		 */
		bool insertGames( const QString &name,
						  const QString &version,
						  const QString &executable = QString(),
						  const QString &templates = QString()
						);

		/**
		 * Delete game from database
		 *
		 * @param name the Game name
		 * @param withTemplate delete game with gametemplate?
		 * @return true if delete successfull
		 */
		bool deleteGames( const QString &name, bool withTemplate );

		/**
		 * Select dosbox version from database
		 * @return QStringList with all dosbox version
		 */
		QStringList selectDosBoxVersion();

	public slots:
		void selectDosBoxGames( const QString &version, QTreeWidget *qtw );		
		void selectGames( QTreeWidget *qtw );

	private:
		bool isOpen();

		QMap< QString, QMap< QString, QStringList> > gameDosBoxList;
		QStringList dosboxVersionList;
		QStringList gameList;
		QStringList exportGameList;
		QStringList gameTemplateList;
		QStringList exportGameTemplateList;
		QString sqlFile;
		QString sqlDatabase;

		QString _version;
		QString _title;
		QString _year;
		QString _sw_house;
		QString _link;
		QString _comp_percent;

		QSqlDatabase gamedb;

		QObject *object;
};

#endif // DBOXFEGDB_SQL_H
