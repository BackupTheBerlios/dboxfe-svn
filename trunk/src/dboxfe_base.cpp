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
    // qw->ui.
    settGP.setValue( "", "" );

}

QStringList DB_BASE::findFiles( const QDir &dir, const QStringList &files, const QString &wildCards, QProgressBar *pBar )
{
    QStringList foundFiles;
    pBar->setMaximum( files.size() );

    for( int i = 0; i < files.size(); ++i )
    {
        QFile file( dir.absoluteFilePath( files[i] ) );

        if ( file.open( QIODevice::ReadOnly ) )
        {
            QString line;
            QTextStream in( &file );
	    
            while (!in.atEnd())
            {
                line = in.readLine();
                if ( line.contains( wildCards ) )
                {
                    foundFiles << files[i];
                    break;
                }
            }
        }
	pBar->setValue( i );
    }
    pBar->reset();
    return foundFiles;
}

void DB_BASE::showFiles(const QDir &dir, const QStringList &files, QListWidget* qlw)
{
    for( int i = 0; i < files.size(); ++i )
    {
	// for future requests
        // QFile file( dir.absoluteFilePath( files[i] ) );
	
	QListWidgetItem *fileNameItem = new QListWidgetItem( files[i] );
	fileNameItem->setFlags(Qt::ItemIsEnabled);
	
	qlw->addItem( fileNameItem );
    }
}
