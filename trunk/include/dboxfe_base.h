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

#include <QtCore/QFileInfo>
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
    
private:
    QStringList gameList;
    QString m_file, m_gameName;
    QFileInfo fi;
        
public:
    DB_BASE();
    inline virtual ~DB_BASE(){}

    /**
     * Read dosbox configuration file
     *
     * @param dbconf  Read the dosbox configuration file
     * @param dbfe    QWidget (include all labels etc.)
     * @since 0.1.0
     */
    void readDBConf( const QString &dbconf, const DBoxFE &dbfe );

    /**
     * Save dosbox configuration file
     *
     * @param dbconf  Save the dosbox configuration file
     * @param dbfe    QWidget (include all labels etc.)
     * @since 0.1.0
     */
    void saveDBConf( const QString &dbconf, const DBoxFE &dbfe );
    
    /**
     * Search game executable
     *
     * @param dir        Directory for search
     * @param qlw        QListWidget for information
     * @param pBar       QProgressBar for search status
     * @since 0.1.0
     */
    void findFiles( const QString &dirName, QListWidget* qlw, QProgressBar *pBar );
};

#endif // DBOXFE_BASE_H
