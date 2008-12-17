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
 *   the Free Software Foundation; either version 3 of the License, or     *
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

#include <base.h>
#include <dboxfe.h>
#include <splash.h>

#include <xmlpreferences.h>

#include <QtCore>
#include <QtXml>


using namespace asaal;

int main( int argc, char *argv[] ) {

  QApplication app( argc, argv );

  DBoxFE *dboxfe = new DBoxFE();

  QString m_file, m_profile_dir, m_tmpl_dir, lng;

  Splash *splash;
  splash = new Splash( QPixmap( ":/pics/images/logo.png" ) );
  app.processEvents();

  if ( splash )
    splash->show();

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Create/Search application Directory ..." ) );

  m_file = QDir::homePath();

  m_file.append( "/.dboxfe" );

  QDir appDir( m_file );

  if ( !appDir.exists( m_file ) ) {
    appDir.mkdir( m_file );
  }

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Create profile directory " ) + m_file + "..." );

  m_profile_dir = QDir::homePath();

  m_profile_dir.append( "/.dboxfe/profile" );

  QDir proDir( m_profile_dir );

  if ( !proDir.exists( m_profile_dir ) ) {
    proDir.mkdir( m_profile_dir );
  }

  DBoxFE_Configuration dboxfeConfig = DBoxFE::configBaseInstance()->readSettings();
  {
    if( dboxfeConfig.profiles.count() <= 0 ) {
      dboxfeConfig.profiles = DBoxFE::configBaseInstance()->readProfiles();
    }

    if( dboxfeConfig.dosboxBinary.isNull() || dboxfeConfig.dosboxBinary.isEmpty() ) {
      dboxfeConfig.dosboxBinary = "";
    }

    if( dboxfeConfig.dosboxVersion.isNull() || dboxfeConfig.dosboxVersion.isEmpty() ) {
      dboxfeConfig.dosboxVersion = "0.72";
    }

    if( dboxfeConfig.profileCount <= 0 )  {
      dboxfeConfig.profileCount = 0;
    }

    dboxfeConfig.winHide = true;
    dboxfeConfig.keyMapper = false;
  }
  DBoxFE::configBaseInstance()->writeSettings( dboxfeConfig );

#ifdef Q_OS_LINUX

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Create template directory " ) + m_profile_dir + "..." );

  m_tmpl_dir = QDir::homePath();
  m_tmpl_dir.append( "/.dboxfe/templates" );

  QDir tmplDir( m_tmpl_dir );

  if ( !tmplDir.exists( m_tmpl_dir ) ) {
    tmplDir.mkdir( m_tmpl_dir );
  }

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Load resource stream" ) );

  QStringList entryList = tmplDir.entryList( QDir::Files );
  if ( entryList.count() != dboxfeConfig.profileCount || dboxfeConfig.profileCount <= 0 ) {


    QString templateResource = QString::fromUtf8( ":/files/templates.qrc" );
    QFile templateFile( templateResource );
    templateFile.open( QIODevice::ReadOnly | QIODevice::Text );

    QDomDocument doc;
    doc.setContent( &templateFile );

    templateFile.close();
    templateResource = QString( "" );

    QDomNode node = doc.documentElement().firstChild();

    if ( splash )  {
      splash->showMessage( QApplication::translate( "DBoxFE", "Initial resource stream ..." ) );
    }

    while ( !node.isNull() ) {
      qApp->processEvents();

      QString tagName = node.toElement().tagName();

      if ( tagName == "qresource" ) {

        QDomNode qresource = node.firstChild();

        while ( !qresource.isNull() ) {
          qApp->processEvents();

          tagName = qresource.toElement().tagName();

          if ( tagName == "file" ) {
            QString dfendProf = ":/" + QString( qresource.toElement().attribute( "alias" ) );

            QFile profIn( dfendProf );

            if ( !profIn.open( QIODevice::ReadOnly ) ) {
              qDebug() << QString( "ERROR: Can't open the resource stream: %1" ).arg( dfendProf );

              qresource = qresource.nextSibling();
              continue;
            }

            QTextStream in( &profIn );

            QString profEntry = in.readAll();

            QFile profOut( m_file + "/" + qresource.toElement().text() );

            if ( profOut.exists() ) {

              if ( splash ) {

                splash->showMessage( QApplication::translate( "DBoxFE", "Ignore template: " ) + qresource.toElement().attribute( "alias" ) + ".prof ..." );
              }

              profIn.close();

              qresource = qresource.nextSibling();
              continue;
            }

            if ( !profOut.open( QIODevice::WriteOnly | QIODevice::Text ) ) {
              qDebug() << QString( "ERROR: Can't write the resource stream %1 to %2" ).arg( dfendProf ).arg( profOut.fileName() );

              qresource = qresource.nextSibling();
              continue;
            }

            QTextStream out( &profOut );

            out << profEntry;

            out.flush();
            profOut.flush();
            profOut.close();
            profIn.close();
            profEntry = QString( "" );

            if ( splash ) {

              splash->showMessage( QApplication::translate( "DBoxFE", "Initial template: " ) + qresource.toElement().attribute( "alias" ) + ".prof ..." );
            }
          }

          qresource = qresource.nextSibling();
        }
      }

      node = node.nextSibling();
    }

    entryList.clear();

    entryList = tmplDir.entryList( QDir::Files );

    DBoxFE_Configuration dboxfeConfig = DBoxFE::configBaseInstance()->readSettings();
    dboxfeConfig.profileCount = entryList.count();

    DBoxFE::configBaseInstance()->writeSettings( dboxfeConfig );
  }

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Closing resource stream ..." ) );

#endif

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Loading Profiles ..." ) );

  dboxfe->initialProfiles();

  if ( splash )
    splash->showMessage( QApplication::translate( "DBoxFE", "Starting GUI ..." ) );

  dboxfe->show();

  if ( splash )
    delete splash;

  app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );

  return app.exec();
}
