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

#include <QtCore/QString>
#include <QtCore/QProcess>
#include <QtGui/QListWidget>
#include <QtCore/QStringList>
#include <QtGui/QWidget>

/**
 * Klasse für DBoxFE
 *
 * @class GP_BASE dboxfe_base.h "GP_BASE"
 * @author Alexander Saal <alex.saal@gmx.de>
 * @date 2006/03/03
 * @version 0.1.0
 * @since 0.1.0
*/
class DB_BASE
{

private:
    DBoxFE dbfe;

public:
    DB_BASE();
    inline virtual ~DB_BASE(){}

    /**
     * Read gameprofile file
     *
     * @param gpIni   read gameprofile
     * @param lw      the QListWidget
     * @since 0.1.0
     */
    void readGPIni( const QString &gpIni, QListWidget* lw );

    /**
     * Save gameprofile file
     *
     * @param gpIni   save gameprofile
     * @param lw      the QListWidget
     * @since 0.1.0
     */
    void saveGPIni( const QString &gpIni, QListWidget* lw );


    /**
     * Read dosbox configuration file
     *
     * @param dbconf  read the dosbox configuration file
     * @param qw      the QWidget
     * @since 0.1.0
     */
    void readDBConf( const QString &dbconf, QWidget* qw );

    /**
     * Save dosbox configuration file
     *
     * @param dbconf  save the dosbox configuration file
     * @param qw      the QWidget
     * @since 0.1.0
     */
    void saveDBConf( const QString &dbconf, QWidget* qw );
};

#endif // DBOXFE_BASE_H
