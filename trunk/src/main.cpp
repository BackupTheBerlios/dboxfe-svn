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

// Qt 4 Header
#include <QtCore>
#include <QtGui>

int main(int argc, char **argv )
{
    QApplication app(argc, argv);
    
    DBoxFE w;
    
    QTranslator translator;
    QString m_file, m_profile_dir, m_tmpl_dir, lng;
    
    DBoxFE_Splash *splash;
    splash = new DBoxFE_Splash( QPixmap(":/pics/images/logo.png") );
    app.processEvents();
    
    if (splash) splash->showMessage( QApplication::translate( "DBoxFE", "Create/Search application Directory ..." ) );
    if (splash) splash->show();
    
    // TODO Create application directory if dosn't exists    
    m_file = QDir::homePath();
    m_file.append( "/.dboxfe" );
    QDir appDir(m_file);
    
    if( !appDir.exists( m_file ) ){ appDir.mkdir( m_file ); }
    if (splash) splash->showMessage( QApplication::translate( "DBoxFE", "Create Directory " ) + m_file +  "..." );
    
    // TODO Create profile directory if dosn't exists
    m_profile_dir = QDir::homePath();
    m_profile_dir.append( "/.dboxfe/profile" );
    QDir proDir(m_profile_dir);
    
    if( !proDir.exists( m_profile_dir ) ){ proDir.mkdir( m_profile_dir ); }
    if (splash) splash->showMessage( QApplication::translate( "DBoxFE", "Create Directory " ) + m_profile_dir +  "..." );
    
    // TODO Create Template directory if dosn't exists
    m_tmpl_dir = QDir::homePath();
    m_tmpl_dir.append( "/.dboxfe/tmpl" );
    QDir tmplDir(m_tmpl_dir);
    
    if( !tmplDir.exists( m_tmpl_dir ) ){ tmplDir.mkdir( m_tmpl_dir ); }
    if (splash) splash->showMessage( QApplication::translate( "DBoxFE", "Create Directory " ) + m_tmpl_dir +  "..." );
    
    if (splash) splash->showMessage( QApplication::translate( "DBoxFE", "Read Language settings ...") );
    
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
	lng = ":/lng/dboxfe_en.qm";
	translator.load( lng );
	app.installTranslator(&translator);	
    }
    
    if (splash) splash->showMessage( QApplication::translate( "DBoxFE", "Loading Profiles ..." ) );

    w.init();
    
    if (splash) splash->showMessage( QApplication::translate( "DBoxFE", "Starting GUI ..." ) );
    
    w.show();

    if (splash) delete splash;
    
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    

    return app.exec();
}
