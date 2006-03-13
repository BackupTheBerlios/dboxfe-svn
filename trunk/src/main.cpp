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
#include "dboxfe_splash.h"
#include "XMLPreferences.h"

#include <QtGui/QApplication>
#include <QtGui/QPixmap>

#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QTranslator>
#include <QtCore/QLocale>
#include <QtGui/QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
 
    QTranslator translator;
    QString local = QLocale::system().name();
    QString m_file;
    QString lng;
    
    m_file = QDir::homePath();
    m_file.append( "/.dboxfe/profile/profile.xml" );
    
    DBoxFE w;
    
    XMLPreferences settGP( "DBoxFE", "Alexander Saal" );
    settGP.setVersion( w.getAppVersion() );
    settGP.load( m_file );
    
    int lngIndex = settGP.getInt( "DBoxFE", "Lng" );

    if( lngIndex == 0 )
    {
	lng = ":/lng/dboxfe_en.qm";
	translator.load( lng );
	app.installTranslator(&translator);
    }
    else if( lngIndex == 1 )
    {
	lng = ":/lng/dboxfe_de.qm";
	translator.load( lng );
	app.installTranslator(&translator);
    }
    else
    {
	// TODO add code for disable message
	if( lngIndex == -1 ) QMessageBox::information( 0, w.winTitle(), "No Language was choosed, use default language english ...");
    }

    DBoxFE_Splash *splash;
    splash = new DBoxFE_Splash( QPixmap(":/pics/images/logo.png") );
    app.processEvents();
    
    if (splash) splash->showMessage( "Loading Profiles" );
    if (splash) splash->show();

    w.init();

    if (splash) splash->showMessage( "Starting GUI");
    
    w.show();

    if (splash) delete splash;
    
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    

    return app.exec();
}
