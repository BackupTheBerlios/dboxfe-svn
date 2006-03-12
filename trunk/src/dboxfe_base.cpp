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

#include "dboxfe.h"
#include "dboxfe_base.h"
#include "XMLPreferences.h"

#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QIODevice>
#include <QtCore/QList>
#include <QtCore/QFileInfo>
#include <QtCore/QListIterator>
#include <QtCore/QtDebug>

#include <QtGui/QProgressBar>
#include <QtGui/QWidget>
#include <QtGui/QListWidgetItem>

DB_BASE::DB_BASE()
{}

void DB_BASE::readDBConf( const QString &dbconf, const DBoxFE &dbfe )
{
    QSettings settGP( dbconf, QSettings::IniFormat );
    QStringList sList;

}

void DB_BASE::saveDBConf( const QString &dbcon, const DBoxFE &dbfe )
{
    QSettings settGP( dbcon, QSettings::IniFormat );

    settGP.setValue( "", "" );

}

void DB_BASE::findFiles( const QString &dirName, QListWidget* qlw, QProgressBar *pBar )
{
    QDir dir( dirName );
    
    m_file = QDir::homePath();
    m_file.append( "/.dboxfe/profile/games.xml" );
    
    XMLPreferences games( "DBoxFE", "Alexander Saal" );
    games.setVersion( "v0.1.0" );
    games.load( m_file );
    
    gameList= games.getStringList( "Games", "Name");
    
    int x = 0;
    
    const QFileInfoList fil = dir.entryInfoList(QDir::Files | QDir::Dirs, QDir::Name);
    QListIterator<QFileInfo> it( fil );

    while ( it.hasNext() )
    {
        fi = it.next();
        x += 1;

        if ( fi.fileName() == "." || fi.fileName() == ".." )
            ;
        else
        {
            if ( fi.isDir() && fi.isReadable() )
                findFiles( fi.absoluteFilePath(), qlw, pBar );
            else
            {
                QFile f( dirName );

                if ( f.exists() )
                {
		    /*for( int i = 0; i < gameList.size(); ++i )
		    {
			m_gameName = gameList.join(";");
			qDebug() << m_gameName;
		    }*/
		    
                    qlw->addItem( fi.fileName() ) ;
                    //qDebug() << dirName << fi.fileName();
                    pBar->setValue( x );
                }
            }
        }
    }
}
