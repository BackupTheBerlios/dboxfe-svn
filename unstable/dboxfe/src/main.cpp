/***************************************************************************
 *   Copyright (C) 2004-2008 by Alexander Saal                             *
 *   alex.saal@gmx.de                                                      *
 *                                                                         *
 *   File: ${filename}.${extension}                                        *
 *   Desc: ${description}                                                  *
 *                                                                         *
 *   This file is part of DBoxFE - DOSBox Front End                        *
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

#include <dboxfe.h>
#include <splash.h>

#include <QApplication>
#include <QDir>
#include <QString>


using namespace asaal;

int main( int argc, char *argv[] ) {

  QApplication app( argc, argv );

  DBoxFE dboxfe;

  QString m_file, m_profile_dir, m_tmpl_dir, lng;

  Splash *splash;
  splash = new Splash( QPixmap( ":/pics/images/logo.png" ) );
  app.processEvents();

  if ( splash )
    splash->show();

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Create/Search application Directory ..." ) );

  // TODO Create application directory if dosn't exists
  m_file = QDir::homePath();
  m_file.append( "/.dboxfe" );

  QDir appDir( m_file );
  if ( !appDir.exists( m_file ) ) {
    appDir.mkdir( m_file );
  }

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Create Directory " ) + m_file + "..." );

  m_profile_dir = QDir::homePath();
  m_profile_dir.append( "/.dboxfe/profile" );

  QDir proDir( m_profile_dir );
  if ( !proDir.exists( m_profile_dir ) ) {
    proDir.mkdir( m_profile_dir );
  }

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Create Directory " ) + m_profile_dir + "..." );

  m_tmpl_dir = QDir::homePath();
  m_tmpl_dir.append( "/.dboxfe/templates" );

  QDir tmplDir( m_tmpl_dir );

  if ( !tmplDir.exists( m_tmpl_dir ) ) {
    tmplDir.mkdir( m_tmpl_dir );
  }

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Create Directory " ) + m_tmpl_dir + "..." );


  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Loading Profiles ..." ) );

  dboxfe.initialProfiles();

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Starting GUI ..." ) );

  dboxfe.show();

  if ( splash )
    delete splash;

  app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );

  return app.exec();
}