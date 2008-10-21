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

#include <finishpage.h>
#include <gamewizard.h>
#include <graphicpage.h>
#include <installpage.h>
#include <installprocesspage.h>
#include <miscpage.h>
#include <soundpage.h>
#include <welcomepage.h>

#include <QtGui>

namespace asaal {

  GameWizard *gameWizard = 0;
  GameWizard::GameWizard( QWidget *parent ) : QWizard( parent ) {

    setWindowTitle( tr( "Game Wizard" ) );
    gameWizard = this;

    ip = new InstallPage();
    ipp = new InstallProcessPage();
    gp = new GraphicPage();
    sp = new SoundPage();
    mp = new MiscPage();

    setPage( PAGE_WELCOME, new WelcomePage );
    setPage( PAGE_INSTALL, ip );
    setPage( PAGE_INSTALLPROCESS, ipp );
    setPage( PAGE_GRAPHIC, gp );
    setPage( PAGE_SOUND, sp );
    setPage( PAGE_MISC, mp );
    setPage( PAGE_FINSH, new FinishPage );

    setStartId( PAGE_WELCOME );
    setPixmap( QWizard::LogoPixmap, QPixmap( ":/logo_wizard_image" ) );
  }

  void GameWizard::accept() {

    QString profile = field( "gameName" ).toString();
    if( createGameProfile( profile ) ) {
    }
  }

  bool GameWizard::createGameProfile( const QString &profile ) {

    // Installation page
    QString dosBoxBinary = field( "dosBoxBinary" ).toString();
    QString installSetupFile = field( "installSetupFile" ).toString();
    QString installFolder = field( "installFolder" ).toString();
    QString gameFile = field( "gameFile" ).toString();
    QString gameFolder = field( "gameFolder" ).toString();

    // Graphic page
    bool sdlFullScreen = field( "sdlFullScreen" ).toBool();
    bool sdlFullDouble = field( "sdlFullDouble" ).toBool();
    bool sdlWaitOnError = field( "sdlWaitOnError" ).toBool();
    bool sdlAutolock = field( "sdlAutolock" ).toBool();
    bool sdlUseScanCode = field( "sdlUseScanCode" ).toBool();
    bool renderAspect = field( "renderAspect" ).toBool();
    int renderScaler = gp->fieldWidgetValue( "renderScaler" ).toInt();
    int frameScip = gp->fieldWidgetValue( "frameScip" ).toInt();
    QString sdlOutout = gp->fieldWidgetValue( "sdlOutout" ).toString();
    QString sdlFocusUnfocus = gp->fieldWidgetValue( "sdlFocusUnfocus" ).toString();
    QString sdlWindowWightHigh = gp->fieldWidgetValue( "sdlWindowWightHigh" ).toString();
    QString sdlFullWightHigh = gp->fieldWidgetValue( "sdlFullWightHigh" ).toString();
    QString sdlSensitivity = gp->fieldWidgetValue( "sdlSensitivity" ).toString();
    QString cpuCore = gp->fieldWidgetValue( "cpuCore" ).toString();
    QString cpuCycleUp = gp->fieldWidgetValue( "cpuCycleUp" ).toString();
    QString cpuCycles = gp->fieldWidgetValue( "cpuCycles" ).toString();
    QString cpuCycleDown = gp->fieldWidgetValue( "cpuCycleDown" ).toString();

    // Sound page
    bool mixerNoSound = field( "mixerNoSound" ).toBool();
    bool soundBlasterMixer = field( "soundBlasterMixer" ).toBool();
    bool gus = field( "gus" ).toBool();
    bool disney = field( "disney" ).toBool();
    int prebuffer = sp->fieldWidgetValue( "prebuffer" ).toInt();
    QString gusUltraDir = field( "gusUltraDir" ).toString();
    QString mdiConfig = field( "mdiConfig" ).toString();
    QString mixerRate = sp->fieldWidgetValue( "mixerRate" ).toString();
    QString mixerBlockSize = sp->fieldWidgetValue( "mixerBlockSize" ).toString();
    QString soundBlasterType = sp->fieldWidgetValue( "soundBlasterType" ).toString();
    QString soundBlasterBase = sp->fieldWidgetValue( "soundBlasterBase" ).toString();
    QString soundBlasterIRQ = sp->fieldWidgetValue( "soundBlasterIRQ" ).toString();
    QString soundBlasterDMA = sp->fieldWidgetValue( "soundBlasterDMA" ).toString();
    QString soundBlasterOplMode = sp->fieldWidgetValue( "soundBlasterOplMode" ).toString();
    QString soundBlasterHDMA = sp->fieldWidgetValue( "soundBlasterHDMA" ).toString();
    QString soundBlasterOPLRate = sp->fieldWidgetValue( "soundBlasterOPLRate" ).toString();
    QString gusRate = sp->fieldWidgetValue( "gusRate" ).toString();
    QString gusBase = sp->fieldWidgetValue( "gusBase" ).toString();
    QString gusIrq_1 = sp->fieldWidgetValue( "gusIrq_1" ).toString();
    QString gusIrq_2 = sp->fieldWidgetValue( "gusIrq_2" ).toString();
    QString gusDMA_1 = sp->fieldWidgetValue( "gusDMA_1" ).toString();
    QString gusDMA_2 = sp->fieldWidgetValue( "gusDMA_2" ).toString();
    QString speaker = sp->fieldWidgetValue( "speaker" ).toString();
    QString speakerRate = sp->fieldWidgetValue( "speakerRate" ).toString();
    QString speakerTandy = sp->fieldWidgetValue( "speakerTandy" ).toString();
    QString speakerTandyRate = sp->fieldWidgetValue( "speakerTandyRate" ).toString();
    QString mdiMPU = sp->fieldWidgetValue( "mdiMPU" ).toString();
    QString mdiDevice = sp->fieldWidgetValue( "mdiDevice" ).toString();
    
    return false;
  }
}
