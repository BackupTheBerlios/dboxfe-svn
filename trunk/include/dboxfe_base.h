/*
*   Copyright (C) 2004 - 2007 by Alexander Saal <alex.saal@gmx.de>
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
#include "dboxfe_profilewizard.h"
#include "dboxfe_gamesettings.h"
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
    QFile *createFile;

  public:
    DB_BASE();
    inline virtual ~DB_BASE() {}

    /**
     * Return the absolut path of executable
     * @since 0.1.0
     */
    static QString applicationDir();

    /**
     * Save dosbox configuration file
     *
     * @param dbconf Save the dosbox configuration file
     * @param dbfe  QWidget (include all labels etc.)
     * @since 0.1.0
     */
    void saveConf( const QString &dbconf, DBoxFE* dbfe );

    /**
     * Read dosbox configuration file
     *
     * @param dbconf Read the dosbox configuration file
     * @param dbfe  QWidget (include all labels etc.)
     * @since 0.1.0
     */
    void readConf( const QString &dbconf, DBoxFE* dbfe );

    /**
     * Search game executable
     *
     * @param dirName Directory for search
    * @param qlw  QListWidget for list information
     * @since 0.1.0
     */
    void findGames( const QString &dirName, QTreeWidget* qlw );

    /**
     * Create game profiles
     *
     * @param file  configuraton file for store information about profile names
     * @param gamesList QStrinList with all selected games
     * @since 0.1.0
     */
    void createGameProfiles( const QString &file, QStringList &gamesList, DBoxFE* dbfe, DBoxFE_ProfileWizard* dbfe_pw );

    /**
     * Load image from directory
     *
     * @parm imageDirectory Imagedirectory
     * @param imageDirectory QListWidget for list information
     * @since 0.1.2
     */
    QStringList loadImage( const QString &imageDirectory );

    /**
     * Insert game in to database (xml file)
     *
     * @param name   Game name
     * @param executable Executabel of game
     * @param qtw   QTreeWidget for list information
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
     * @param file  file to save
     * @param qtw  QTreeWidget for information
     * @param col1  QTreeWidgetColumn 1 for information
     * @param col2  QTreeWidgetColumn 2 for information
     * @since 0.1.0
     */
    void saveGameDb( const QString &file, QTreeWidget* qtw, int col1, int col2 );

    /**
           * Read game xml
           *
           * @param file   Game name
           * @param qtw   QTreeWidget for list information
           * @since 0.1.2
           */
    void readGameDb( const QString &file, QProgressBar *pBar, QTreeWidget* qtw );

    /**
           * Import DFend - Profile :)
           *
           * @param file   DFEnd - Profil file
           * @since 0.1.2
           */
    void importDFendProfile( const QString &file, DBoxFE *dbfe );

    /**
           * Check for double entryies in profillist
           *
           * @param dbfe   ...
     * @param name   Name of profile
           * @since 0.1.2
           */
    bool isDoubleEntry( const QString &name, DBoxFE* dbfe );
};

#endif // DBOXFE_BASE_H
