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
		bool importDosBoxGameList( const QMap<QString, QMap< QString, QString> > &list, QProgressBar *pBar = 0, QLabel *lbl = 0 );		

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
		 * Insert template into database
		 * @param name the Game name
		 * @return true if insert successfull
		 */
		bool updateTemplates( const QString &name, QMap< QString, QMap< QString, QVariant > > &settings );		

		/**
		 * Insert template into database
		 * @param name the template name
		 * @param cbx the QComboBox for insert template names
		 * @return true if insert successfull
		 */
		bool insertTemplates( const QString &name, QComboBox *cbx );

		/**
		 * Insert template into database
		 * @param name the template name
		 * @param settings the QMap with all settings
		 * @return true if insert successfull
		 */
		bool insertTemplates( const QString &name, QMap< QString, QMap< QString, QVariant > > &settings );
		
		/**
		 * Delete template from database
		 * @param name the Template name
		 * @return true if delete successfull
		 */
		bool deleteTemplates( const QString &name );

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

		/**
		 * Select template settings from database
		 * @return QMap with all settings
		 */
		QMap< QString, QMap< QString, QVariant > > selectTemplateSettings( const QString &name );

	public slots:
		void selectDosBoxGames( const QString &version, QTreeWidget *qtw );		
		void selectGames( QTreeWidget *qtw );
		void selectTemplates( QComboBox *cbx );

	private:
		bool isOpen();

		QMap< QString, QMap< QString, QString > > gameDosBoxList;
		QMap< QString, QMap< QString, QVariant > > sett;

		QMap< QString, QMap< QString, QVariant > > templateSettings;
		QMap< QString, QVariant > subTemplateSettings;

		QStringList dosboxVersionList;
		QStringList gameList;
		QStringList exportGameList;
		QStringList gameTemplateList;
		QStringList exportGameTemplateList;

		QString sqlFile;
		QString sqlDatabase;

		QString _template_name;

		QString _version;
		QString _title;
		QString _year;
		QString _sw_house;
		QString _link;
		QString _comp_percent;

				
		QString // SDL Strings
				_fullscreen, _fulldouble, _fullresolution, _windowresolution, _output, _autolock, _sensitivity, _waitonerror, _priority, _mapperfile, _usescancodes,

				// DOSBOX Strings
				_language, _machine, _captures, _memsize,

				// RENDER Settings
				_frameskip, _aspect, _scaler,

				// CPU Settings
				_core, _cycles, _cycleup, _cycledown,
				
				// MIXER Settings
				_nosound, _rate, _blocksize, _prebuffer,

				// MIDI Settings
				_device, _config,

				// SBLASTER Settings
				_sbtype, _sbbase, _irq, _dma, _hdma, _mixer, _oplmode, _oplrate,

				// GUS Settings
				_gus, _gusrate, _gusbase, _irq1, _irq2, _dma1, _dma2, _ultradir,

				// SPEAKER Settings
				_pcspeaker, _pcrate, _tandy, _tandyrate, _disney,

				// JOYSTICK Settings
				_joysticktype, _timed, _autofire, _swap34, _buttonwrap,

				// SERIAL Settings
				_serial1, _serial2, _serial3, _serial4,

				// DOS Settings
				_xms, _ems, _umb, _keyboardlayout,

				// IPX
				_ipx;

		QString sqlSdl,
				sqlDosBox,
				sqlRender,
				sqlCpu,
				sqlMixer,
				sqlMidi,
				sqlSbBlaster,
				sqlGus,
				sqlSpeaker,
				sqlJoystick,
				sqlSerial,
				sqlDos,
				sqlIpx;

		QSqlDatabase gamedb;

		QObject *object;
};

#endif // DBOXFEGDB_SQL_H
