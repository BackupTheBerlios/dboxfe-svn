/***************************************************************************
 *   Copyright (C) 2006 by Alexander Saal                                  *
 *   alex.saal@gmx.de                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef DBOXFE_BASE_H
#define DBOXFE_BASE_H

#include "dboxfe.h"
#include "XMLPreferences.h"

#include <QtGui/QWidget>
#include <QtGui/QListWidget>
#include <QtGui/QProgressBar>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDir>

/**
 * Klasse für DBoxFE
 *
 * @class DB_BASE dboxfe_base.h "DB_BASE"
 * @author Alexander Saal <alex.saal@gmx.de>
 * @date 2006/03/03
 * @version 0.1.0
 * @since 0.1.0
*/
class DB_BASE
{

public:
    DB_BASE();
    inline virtual ~DB_BASE(){}

    /**
     * Read dosbox configuration file
     *
     * @param dbconf  read the dosbox configuration file
     * @param qw      the QWidget
     * @since 0.1.0
     */
    void readDBConf( const QString &dbconf, const DBoxFE &dbfe );

    /**
     * Save dosbox configuration file
     *
     * @param dbconf  save the dosbox configuration file
     * @param qw      the QWidget
     * @since 0.1.0
     */
    void saveDBConf( const QString &dbconf, const DBoxFE &dbfe );
    
    /**
     * Search game executable
     *
     * @param dir        the directory for search
     * @param files      the QStringList &files (include all files from QDir &dir)
     * @param wildCards  the wild cards for searching executable (like: *.exe)
     * @since 0.1.0
     */
    QStringList findFiles( const QDir &dir, const QStringList &files, const QString &wildCards, QProgressBar *pBar );
    
    /**
     * Show found games
     *
     * @param dir        the directory
     * @param files      the QStringList &files (include all files from QDir &dir)
     * @param qlw        the QListWidget for show found file
     * @since 0.1.0
     */
    void showFiles( const QDir &dir, const QStringList &files, QListWidget* qlw );
};

#endif // DBOXFE_BASE_H
