/***************************************************************************
 *   Copyright (C) 2008 by Alexander Saal                                  *
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

#include <base.h>
#include <xmlpreferences.h>

#include <QtCore>

namespace asaal {

  ConfigBase::ConfigBase( QObject *parent ) : QObject( parent ) {

    m_Parent = parent;
  }

  ConfigBase::~ConfigBase() {
  }

  Configuration ConfigBase::readConfiguration( const QString &profile ) {

    m_Configuration.clear();
    QFile configFile( profile );

    if ( !configFile.exists() ) {
      m_Configuration.clear();
      return m_Configuration;
    }

    QSettings readConf( profile, QSettings::IniFormat );

    // SDL settings
    readConf.beginGroup( "sdl" );
    m_Configuration.sdl.insert( "fullscreen", readConf.value( "fullscreen" ) );
    m_Configuration.sdl.insert( "fulldouble", readConf.value( "fulldouble" ) );
    m_Configuration.sdl.insert( "fullresolution", readConf.value( "fullresolution" ) );
    m_Configuration.sdl.insert( "windowresolution", readConf.value( "windowresolution" ) );
    m_Configuration.sdl.insert( "priority", readConf.value( "priority" ) );
    m_Configuration.sdl.insert( "output", readConf.value( "output" ) );
    m_Configuration.sdl.insert( "autolock", readConf.value( "autolock" ) );
    m_Configuration.sdl.insert( "waitonerror", readConf.value( "waitonerror" ) );
    m_Configuration.sdl.insert( "usescancodes", readConf.value( "usescancodes" ) );
    m_Configuration.sdl.insert( "sensitivity", readConf.value( "sensitivity" ) );
    m_Configuration.sdl.insert( "sensitivity", readConf.value( "sensitivity" ) );
    m_Configuration.sdl.insert( "mapperfile", readConf.value( "mapperfile" ) );
    readConf.endGroup();

    // DOSBox settings
    readConf.beginGroup( "dosbox" );
    m_Configuration.dosbox.insert( "language", readConf.value( "language" ) );
    m_Configuration.dosbox.insert( "machine", readConf.value( "machine" ) );
    m_Configuration.dosbox.insert( "memsize", readConf.value( "memsize" ) );
    m_Configuration.dosbox.insert( "captures", readConf.value( "captures" ) );
    readConf.endGroup();

    // Render settings
    readConf.beginGroup( "render" );
    m_Configuration.render.insert( "frameskip", readConf.value( "frameskip" ) );
    m_Configuration.render.insert( "scaler", readConf.value( "scaler" ) );
    m_Configuration.render.insert( "aspect", readConf.value( "aspect" ) );
    readConf.endGroup();

    // CPU settings
    readConf.beginGroup( "cpu" );
    m_Configuration.cpu.insert( "core", readConf.value( "core" ) );
    m_Configuration.cpu.insert( "cycles", readConf.value( "cycles" ) );
    m_Configuration.cpu.insert( "cycleup", readConf.value( "cycleup" ) );
    m_Configuration.cpu.insert( "cycledown", readConf.value( "cycledown" ) );
    readConf.endGroup();

    // Mixer settings
    readConf.beginGroup( "mixer" );
    m_Configuration.mixer.insert( "nosound", readConf.value( "nosound" ) );
    m_Configuration.mixer.insert( "rate", readConf.value( "rate" ) );
    m_Configuration.mixer.insert( "blocksize", readConf.value( "blocksize" ) );
    m_Configuration.mixer.insert( "prebuffer", readConf.value( "prebuffer" ) );
    readConf.endGroup();

    // Mdi settings
    readConf.beginGroup( "midi" );
    m_Configuration.mdi.insert( "mpu401", readConf.value( "mpu401" ) );
    m_Configuration.mdi.insert( "device", readConf.value( "device" ) );
    m_Configuration.mdi.insert( "config", readConf.value( "config" ) );
    readConf.endGroup();

    // Soundblaster settings
    readConf.beginGroup( "sblaster" );
    m_Configuration.sblaster.insert( "sbtype", readConf.value( "sbtype" ) );
    m_Configuration.sblaster.insert( "sbbase", readConf.value( "sbbase" ) );
    m_Configuration.sblaster.insert( "irq", readConf.value( "irq" ) );
    m_Configuration.sblaster.insert( "dma", readConf.value( "dma" ) );
    m_Configuration.sblaster.insert( "hdma", readConf.value( "hdma" ) );
    m_Configuration.sblaster.insert( "oplrate", readConf.value( "oplrate" ) );
    m_Configuration.sblaster.insert( "oplmode", readConf.value( "oplmode" ) );
    m_Configuration.sblaster.insert( "mixer", readConf.value( "mixer" ) );
    readConf.endGroup();

    // GUS settings
    readConf.beginGroup( "gus" );
    m_Configuration.gus.insert( "gus", readConf.value( "gus" ) );
    m_Configuration.gus.insert( "gusrate", readConf.value( "gusrate" ) );
    m_Configuration.gus.insert( "gusbase", readConf.value( "gusbase" ) );
    m_Configuration.gus.insert( "irq1", readConf.value( "irq1" ) );
    m_Configuration.gus.insert( "irq2", readConf.value( "irq2" ) );
    m_Configuration.gus.insert( "dma1", readConf.value( "dma1" ) );
    m_Configuration.gus.insert( "dma2", readConf.value( "dma2" ) );
    m_Configuration.gus.insert( "ultradir", readConf.value( "ultradir" ) );
    readConf.endGroup();

    // PC Speaker settings
    readConf.beginGroup( "speaker" );
    m_Configuration.speaker.insert( "pcspeaker", readConf.value( "pcspeaker" ) );
    m_Configuration.speaker.insert( "pcrate", readConf.value( "pcrate" ) );
    m_Configuration.speaker.insert( "tandy", readConf.value( "tandy" ) );
    m_Configuration.speaker.insert( "tandyrate", readConf.value( "tandyrate" ) );
    m_Configuration.speaker.insert( "disney", readConf.value( "disney" ) );
    readConf.endGroup();

    // joystick settings
    readConf.beginGroup( "joystick" );
    m_Configuration.joystick.insert( "joysticktype", readConf.value( "joysticktype" ) );
    m_Configuration.joystick.insert( "timed", readConf.value( "timed" ) );
    m_Configuration.joystick.insert( "autofire", readConf.value( "autofire" ) );
    m_Configuration.joystick.insert( "swap34", readConf.value( "swap34" ) );
    m_Configuration.joystick.insert( "buttonwrap", readConf.value( "buttonwrap" ) );
    readConf.endGroup();

    // Serial settings
    readConf.beginGroup( "serial" );
    m_Configuration.serial.insert( "serial1", readConf.value( "serial1" ) );
    m_Configuration.serial.insert( "serial2", readConf.value( "serial2" ) );
    m_Configuration.serial.insert( "serial3", readConf.value( "serial3" ) );
    m_Configuration.serial.insert( "serial4", readConf.value( "serial4" ) );
    readConf.endGroup();

    // DOS settings
    readConf.beginGroup( "dos" );
    m_Configuration.dos.insert( "xms", readConf.value( "xms" ) );
    m_Configuration.dos.insert( "ems", readConf.value( "ems" ) );
    m_Configuration.dos.insert( "umb", readConf.value( "umb" ) );
    m_Configuration.dos.insert( "keyboardlayout", readConf.value( "keyboardlayout" ) );
    readConf.endGroup();

    // IPX settings
    readConf.beginGroup( "ipx" );
    m_Configuration.ipx = readConf.value( "ipx" ).toString();
    readConf.endGroup();

    // Autoexec settings
    if ( !configFile.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
      return m_Configuration;
    }

    QTextStream in( &configFile );
    QString line;

    while ( !in.atEnd() ) {
      line = in.readLine();

      if ( line == "[autoexec]" ) {
        while ( !in.atEnd() ) {
          m_Configuration.autoexec += in.readLine() + "\n";

          if ( line.startsWith( "[" ) && line.endsWith( "]" ) )
            break;
        }
      }
    }

    configFile.close();

    return m_Configuration;
  }

  Configuration ConfigBase::convertConfiguration( const QString &profile ) {

    QFile configFile( profile );

    if ( !configFile.exists() ) {
      m_Configuration.clear();
      return m_Configuration;
    }

    QSettings readConf( profile, QSettings::IniFormat );

    return m_Configuration;
  }

  void ConfigBase::writeConfiguration( const QString &profile, const Configuration &config ) {

    if ( config.isEmpty() ) {
      return;
    }
  }

}
