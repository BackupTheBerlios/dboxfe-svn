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

#include <gamewizard.h>
#include <graphicpage.h>

#include <QtCore>
#include <QtGui>

namespace asaal {

  GraphicPage::GraphicPage( QWidget *parent ) : QWizardPage( parent ) {

    setupUi( this );
    setTitle( tr( "Grapihc option" ) );
    setSubTitle( tr( "Specify basic information about the graphic for selected game." ) );

    registerField( "sdlFullScreen", checkBoxSDLFullScreen );
    registerField( "sdlFullDouble", checkBoxSDLFullDouble );
    registerField( "sdlWaitOnError", checkBoxSDLWaitOnError );
    registerField( "sdlAutolock", checkBoxSDLAutolock );
    registerField( "sdlUseScanCode", checkBoxSDLUseScanCode );
    registerField( "sdlOutout", comboBoxSDLOutout );
    registerField( "sdlFocusUnfocus", comboBoxSDLFocusUnfocus );
    registerField( "sdlWindowWightHigh", comboBoxSDLWindowWightHigh );
    registerField( "sdlFullWightHigh", comboBoxSDLFullWightHigh );
    registerField( "sdlSensitivity", lcdSDLSensitivity );
    registerField( "renderScaler", comboBoxRenderScaler );
    registerField( "frameScip", lcdRenderFrameScip );
    registerField( "renderAspect", checkBoxRenderAspect );
    registerField( "cpuCore", comboBoxCPUCore );
    registerField( "cpuCycleUp", comboBoxCPUCycleUp );
    registerField( "cpuCycles", comboBoxCPUCycles );
    registerField( "cpuCycleDown", comboBoxCPUCycleDown );
  }

  int GraphicPage::nextId() const {

    return GameWizard::PAGE_SOUND;
  }

  QVariant GraphicPage::fieldWidgetValue( const QString &fieldName ) const {

    if ( fieldName.isNull() || fieldName.isEmpty() ) {

      return QVariant();
    }

    if ( fieldName == "sdlOutout" ) {

      return QVariant( comboBoxSDLOutout->currentText() );
    }

    if ( fieldName == "sdlFocusUnfocus" ) {

      return QVariant( comboBoxSDLFocusUnfocus->currentText() );
    }

    if ( fieldName == "sdlWindowWightHigh" ) {

      return QVariant( comboBoxSDLWindowWightHigh->currentText() );
    }

    if ( fieldName == "sdlFullWightHigh" ) {

      return QVariant( comboBoxSDLFullWightHigh->currentText() );
    }

    if ( fieldName == "renderScaler" ) {

      return QVariant( comboBoxRenderScaler->currentText() );
    }

    if ( fieldName == "cpuCore" ) {

      return QVariant( comboBoxCPUCore->currentText() );
    }

    if ( fieldName == "cpuCycleUp" ) {

      return QVariant( comboBoxCPUCycleUp->currentText() );
    }

    if ( fieldName == "cpuCycles" ) {

      return QVariant( comboBoxCPUCycles->currentText() );
    }

    if ( fieldName == "cpuCycleDown" ) {

      return QVariant( comboBoxCPUCycleDown->currentText() );
    }

    if ( fieldName == "sdlSensitivity" ) {

      return QVariant( lcdSDLSensitivity->intValue() );
    }

    if ( fieldName == "frameScip" ) {

      return QVariant( lcdRenderFrameScip->intValue() );
    }

    return 0;
  }
}
