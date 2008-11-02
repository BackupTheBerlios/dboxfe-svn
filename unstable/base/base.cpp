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
    m_Sdl.insert( "mapperfile", readConf.value( "mapperfile" ) );
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
    dbfe->chkBoxGUS->setChecked( readConf.value( "gus" ) );
    int gusrate = dbfe->cbxGUSRate->findText( readConf.value( "gusrate" ) );
    dbfe->cbxGUSRate->setCurrentIndex( gusrate );
    int gusbase = dbfe->cbxGUSBase->findText( readConf.value( "gusbase" ) );
    dbfe->cbxGUSBase->setCurrentIndex( gusbase );
    int irq1 = dbfe->cbxGUSIrq_1->findText( readConf.value( "irq1" ) );
    dbfe->cbxGUSIrq_1->setCurrentIndex( irq1 );
    int irq2 = dbfe->cbxGUSIrq_2->findText( readConf.value( "irq2" ) );
    dbfe->cbxGUSIrq_2->setCurrentIndex( irq2 );
    int dma1 = dbfe->cbxGUSDMA_1->findText( readConf.value( "dma1" ) );
    dbfe->cbxGUSDMA_1->setCurrentIndex( dma1 );
    int dma2 = dbfe->cbxGUSDMA_2->findText( readConf.value( "dma2" ) );
    dbfe->cbxGUSDMA_2->setCurrentIndex( dma2 );
    dbfe->LEGUSUltraDir->setText( readConf.value( "ultradir" ) );
    readConf.endGroup();

    // PC Speaker settings
    readConf.beginGroup( "speaker" );

    if ( readConf.value( "pcspeaker" ) == "true" )
      dbfe->cbxSpeaker->setCurrentIndex( 0 );
    else
      dbfe->cbxSpeaker->setCurrentIndex( 1 );

    int pcrate = dbfe->cbxSpeakerRate->findText( readConf.value( "pcrate" ) );

    dbfe->cbxSpeakerRate->setCurrentIndex( pcrate );

    int tandy = dbfe->cbxSpeakerTandy->findText( readConf.value( "tandy" ) );

    dbfe->cbxSpeakerTandy->setCurrentIndex( tandy );

    int tandyrate = dbfe->cbxSpeakerTandyRate->findText( readConf.value( "tandyrate" ) );

    dbfe->cbxSpeakerTandyRate->setCurrentIndex( tandyrate );

    dbfe->chkBoxDisney->setChecked( readConf.value( "disney" ) );

    readConf.endGroup();

    // joystick settings
    readConf.beginGroup( "joystick" );

    int joysticktype = dbfe->cbxJoystickType->findText( readConf.value( "joysticktype" ) );

    dbfe->cbxJoystickType->setCurrentIndex( joysticktype );

    dbfe->chkBoxTimed->setChecked( readConf.value( "timed" ) );

    dbfe->chkBoxAutofire->setChecked( readConf.value( "autofire" ) );

    dbfe->chkBoxSwap34->setChecked( readConf.value( "swap34" ) );

    dbfe->chkBoxButtonWrap->setChecked( readConf.value( "buttonwrap" ) );

    readConf.endGroup();

    // Serial settings
    readConf.beginGroup( "serial" );

    dbfe->twSerial->clear();

    QTreeWidgetItem *serial1 = new QTreeWidgetItem( dbfe->twSerial );

    serial1->setText( 0, "serial1" );

    serial1->setText( 1, readConf.value( "serial1" ) );

    QTreeWidgetItem *serial2 = new QTreeWidgetItem( dbfe->twSerial );

    serial2->setText( 0, "serial2" );

    serial2->setText( 1, readConf.value( "serial2" ) );

    QTreeWidgetItem *serial3 = new QTreeWidgetItem( dbfe->twSerial );

    serial3->setText( 0, "serial3" );

    serial3->setText( 1, readConf.value( "serial3" ) );

    QTreeWidgetItem *serial4 = new QTreeWidgetItem( dbfe->twSerial );

    serial4->setText( 0, "serial4" );

    serial4->setText( 1, readConf.value( "serial4" ) );

    readConf.endGroup();

    // DOS settings
    readConf.beginGroup( "dos" );

    dbfe->chkBoxXMS->setChecked( readConf.value( "xms" ) );

    dbfe->chkBoxEMS->setChecked( readConf.value( "ems" ) );

    dbfe->chkBoxUMB->setChecked( readConf.value( "umb" ) );

    int kbdl = dbfe->cbxKeyboardLayout->findText( readConf.value( "keyboardlayout" ) );

    dbfe->cbxKeyboardLayout->setCurrentIndex( kbdl );

    readConf.endGroup();

    // IPX settings
    readConf.beginGroup( "ipx" );

    dbfe->chkBoxIPX->setChecked( readConf.value( "ipx" ) );

    readConf.endGroup();

    // Autoexec settings
    QFile f( profile );

    if ( !f.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
      delete getConf;
      return ;
    }

    QTextStream in( &f );

    QString line;

    dbfe->lwAutoexec->clear();

    while ( !in.atEnd() ) {
      line = in.readLine();

      if ( line == "[autoexec]" ) {
        while ( !in.atEnd() ) {
          line = in.readLine();
          QListWidgetItem *autoexec = new QListWidgetItem( dbfe->lwAutoexec );
          autoexec->setText( line );

          if ( line.startsWith( "[" ) && line.endsWith( "]" ) )
            break;
        }
      }
    }

    f.close();

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
