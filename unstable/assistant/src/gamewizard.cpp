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
#include <finishpage.h>
#include <gamewizard.h>
#include <graphicpage.h>
#include <installpage.h>
#include <importexportpage.h>
#include <installprocesspage.h>
#include <miscpage.h>
#include <settingpage.h>
#include <soundpage.h>
#include <welcomepage.h>

#include <QtGui>

namespace asaal {

  GameWizard *gameWizard = 0;
  ConfigBase *configBase = 0;
  GameWizard::GameWizard( QWidget *parent ) : QWizard( parent ) {

    setWindowTitle( tr( "Game Wizard" ) );

    ie = new ImportExportPage();
    ip = new InstallPage();
    ipp = new InstallProcessPage();
    gp = new GraphicPage();
    settp = new SettingPage();
    sp = new SoundPage();
    mp = new MiscPage();

    setPage( PAGE_WELCOME, new WelcomePage );
    setPage( PAGE_SETTING, settp );
    setPage( PAGE_IMPORTEXPORT, ie );
    setPage( PAGE_INSTALL, ip );
    setPage( PAGE_INSTALLPROCESS, ipp );
    setPage( PAGE_GRAPHIC, gp );
    setPage( PAGE_SOUND, sp );
    setPage( PAGE_MISC, mp );
    setPage( PAGE_FINSH, new FinishPage );

    setStartId( PAGE_WELCOME );
    setPixmap( QWizard::LogoPixmap, QPixmap( ":/logo_wizard_image" ) );

    gameWizard = this;
    configBase = new ConfigBase( gameWizard );
  }

  void GameWizard::accept() {

    QString profile = field( "gameName" ).toString();
    QString profileDirectory = QDir::homePath();
    profileDirectory.append( "/.dboxfe/" + profile + ".conf" );

    if ( createGameProfile( profileDirectory ) ) {
      
      qApp->quit();
    }
    else
    {
      return;
    }
    
  }

  bool GameWizard::createGameProfile( const QString &profile ) {

    Configuration m_Config;

    // Installation page
    QString dosBoxBinary = field( "dosBoxBinary" ).toString();
    QString installSetupFile = field( "installSetupFile" ).toString();
    QString installFolder = field( "installFolder" ).toString();
    QString gameFile = field( "gameFile" ).toString();
    QString gameFolder = field( "gameFolder" ).toString();

    // Graphic page: SDL settings
    m_Config.sdl.insert( "fullscreen", field( "sdlFullScreen" ) );
    m_Config.sdl.insert( "fulldouble", field( "sdlFullDouble" ) );
    m_Config.sdl.insert( "fullwighthigh", gp->fieldWidgetValue( "sdlFullWightHigh" ) );
    m_Config.sdl.insert( "windowresolution", gp->fieldWidgetValue( "sdlWindowWightHigh" ) );
    m_Config.sdl.insert( "priority", gp->fieldWidgetValue( "sdlFocusUnfocus" ) );
    m_Config.sdl.insert( "outout", gp->fieldWidgetValue( "sdlOutout" ) );
    m_Config.sdl.insert( "autolock", field( "sdlAutolock" ) );
    m_Config.sdl.insert( "waitonerror", field( "sdlWaitOnError" ) );
    m_Config.sdl.insert( "usescancode", field( "sdlUseScanCode" ) );
    m_Config.sdl.insert( "sensitivity", gp->fieldWidgetValue( "sdlSensitivity" ) );
    m_Config.sdl.insert( "mapperfile", QVariant( "mapperfile" ) );

    // Graphic page: Render settings
    m_Config.render.insert( "renderaspect", field( "renderAspect" ) );
    m_Config.render.insert( "renderscaler", gp->fieldWidgetValue( "renderScaler" ) );
    m_Config.render.insert( "framescip", gp->fieldWidgetValue( "frameScip" ) );

    // Graphic page: CPU settings
    m_Config.cpu.insert( "cpucore", gp->fieldWidgetValue( "cpuCore" ) );
    m_Config.cpu.insert( "cpucycleup", gp->fieldWidgetValue( "cpuCycleUp" ) );
    m_Config.cpu.insert( "cpucycles", gp->fieldWidgetValue( "cpuCycles" ) );
    m_Config.cpu.insert( "cpucycledown", gp->fieldWidgetValue( "cpuCycleDown" ) );

    // Sound page: Mixer settings
    m_Config.mixer.insert( "nosound", field( "mixerNoSound" ) );
    m_Config.mixer.insert( "rate", sp->fieldWidgetValue( "mixerRate" ) );
    m_Config.mixer.insert( "blocksize", sp->fieldWidgetValue( "mixerBlockSize" ) );
    m_Config.mixer.insert( "prebuffer", sp->fieldWidgetValue( "prebuffer" ) );

    // Sound page: S-Blaster settings
    m_Config.sblaster.insert( "sbtype", sp->fieldWidgetValue( "soundBlasterType" ) );
    m_Config.sblaster.insert( "sbbase", sp->fieldWidgetValue( "soundBlasterBase" ) );
    m_Config.sblaster.insert( "irq", sp->fieldWidgetValue( "soundBlasterIRQ" ) );
    m_Config.sblaster.insert( "dma", sp->fieldWidgetValue( "soundBlasterDMA" ) );
    m_Config.sblaster.insert( "oplmode", sp->fieldWidgetValue( "soundBlasterOplMode" ) );
    m_Config.sblaster.insert( "hdma", sp->fieldWidgetValue( "soundBlasterHDMA" ) );
    m_Config.sblaster.insert( "oplrate", sp->fieldWidgetValue( "soundBlasterOPLRate" ) );
    m_Config.sblaster.insert( "mixer", field( "soundBlasterMixer" ) );

    // Sound page: GUS settings
    m_Config.gus.insert( "gus", field( "gus" ) );
    m_Config.gus.insert( "gusrate", sp->fieldWidgetValue( "gusRate" ) );
    m_Config.gus.insert( "gusase", sp->fieldWidgetValue( "gusBase" ) );
    m_Config.gus.insert( "ultradir", field( "gusUltraDir" ) );
    m_Config.gus.insert( "irq1", sp->fieldWidgetValue( "gusIrq_1" ) );
    m_Config.gus.insert( "irq2", sp->fieldWidgetValue( "gusIrq_2" ) );
    m_Config.gus.insert( "dma1", sp->fieldWidgetValue( "gusDMA_1" ) );
    m_Config.sblaster.insert( "dma2", sp->fieldWidgetValue( "gusDMA_2" ) );

    // Sound page: Speacker settings
    m_Config.speaker.insert( "disney", field( "disney" ) );
    m_Config.speaker.insert( "pcspeaker", sp->fieldWidgetValue( "speaker" ) );
    m_Config.speaker.insert( "pcrate", sp->fieldWidgetValue( "speakerRate" ) );
    m_Config.speaker.insert( "tandy", sp->fieldWidgetValue( "speakerTandy" ) );
    m_Config.speaker.insert( "tandyrate", sp->fieldWidgetValue( "speakerTandyRate" ) );

    // Sound page: MDI settings
    m_Config.mdi.insert( "config", field( "mdiConfig" ) );
    m_Config.mdi.insert( "mpu401", sp->fieldWidgetValue( "mdiMPU" ) );
    m_Config.mdi.insert( "device", sp->fieldWidgetValue( "mdiDevice" ) );
    
    // Misc page: DOS
    m_Config.dos.insert( "xms", "" );
    m_Config.dos.insert( "ems", "" );
    m_Config.dos.insert( "umb", "" );
    m_Config.dos.insert( "keyboardlayout", "" );

    // Mis Page: DOSBox
    m_Config.dosbox.insert( "language", "" );
    m_Config.dosbox.insert( "machine", "" );
    m_Config.dosbox.insert( "memsize", "" );
    m_Config.dosbox.insert( "captures", "" );
    
    // Misc page: Joystick
    m_Config.joystick.insert( "joysticktype", "" );
    m_Config.joystick.insert( "timed", "" );
    m_Config.joystick.insert( "autofire", "" );
    m_Config.joystick.insert( "swap34", "" );
    m_Config.joystick.insert( "buttonwrap", "" );
    
    // Save configuration
    configBase->writeConfiguration( profile, m_Config );

    m_Config.clear();
    return true;
  }
}
