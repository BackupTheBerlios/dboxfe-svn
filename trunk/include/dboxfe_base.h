/*
*   Copyright (C) 2004/05/06 by Alexander Saal <alex.saal@gmx.de>
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
#ifndef DBOXFE_BASE_H
#define DBOXFE_BASE_H

#include "dboxfe.h"
#include "XMLPreferences.h"

#include <QtCore>
#include <QtGui>

/**
 * Class for DBoxFE
 *
 * @class DB_BASE dboxfe_base.h "DB_BASE"
 * @author Alexander Saal <alex.saal@gmx.de>
 * @date 2006/03/03
 * @version 0.1.0
 * @since 0.1.0
*/

class DB_BASE {

    private:
        QStringList gameList, gamesList;
        QString m_file, m_gameName;
        QFileInfo fi;
        int state;

    public:
        DB_BASE();
        inline virtual ~DB_BASE() {}

        DBoxFE *_dbfe_;

        /**
         * Return the absolut path of executable
         * @since 0.1.0
         */
        static QString applicationDir();

        /**
         * Read dosbox configuration file
         *
         * @param dbconf  Read the dosbox configuration file
         * @param dbfe    QWidget (include all labels etc.)
         * @since 0.1.0
         */
        void readConf( const QString &dbconf, DBoxFE* dbfe );

        /**
         * Save dosbox configuration file
         *
         * @param dbconf  Save the dosbox configuration file
         * @param dbfe    QWidget (include all labels etc.)
         * @since 0.1.0
         */
        void saveConf( const QString &dbconf, DBoxFE* dbfe );

        /**
         * Set default setting
         *
         * @param dbfe    QWidget (include all labels etc.)
         * @since 0.1.0
         */
        void defaultSettings( DBoxFE *dbfe );

        /**
         * Search game executable
         *
         * @param dirName    Directory for search
         * @param qlw        QListWidget for list information
         * @since 0.1.0
         */
        void findGames( const QString &dirName, QTreeWidget* qlw );

        /**
         * Search dosbox executable
         *
         * @param dirName    Directory for search
         * @param pBar       for Progressinformation
         * @since 0.1.0
         */
        void findDosbox( const QString &dirName, QProgressBar *pBar, QStringList &lstBinary );

        /**
         * Create game profiles
         *
         * @param file        configuraton file for store information about profile names
         * @param gamesList   QListWidget for list information
         * @since 0.1.0
         */
        void createGameProfiles( const QString &file, const QStringList &gamesList );

        /**
         * Insert game in to database (xml file)
         *
         * @param name        Game name
         * @param executable  Executabel of game
         * @param QTreeWidget QTreeWidget for list information
         * @since 0.1.0
         */
        void insertGameInToDb( const QString &name, const QString &executable, QTreeWidget* qtw );

        /**
         * Remove game from database (xml file) and return the current count
         *
         * @param QTreeWidget QTreeWidget for select an item to remove it
         * @since 0.1.0
         */
        int removeGameFromDb( QTreeWidget* qtw );

        /**
         * Save game database (xml file)
         *
         * @param file      file to save
         * @param qtw       QTreeWidget for information
         * @param col1      QTreeWidgetColumn 1 for information
         * @param col2      QTreeWidgetColumn 2 for information
         * @since 0.1.0
         */
        void saveGameDb( const QString &file, QTreeWidget* qtw, int col1, int col2 );

        /**
         * Load game database file
         *
         * @param file      file to read
         * @param qtw       QTreeWidget to insert the readed fileinformation
         * @since 0.1.0
         */
        void readGameDb( const QString &file, QTreeWidget* qtw );
};

#endif // DBOXFE_BASE_H
