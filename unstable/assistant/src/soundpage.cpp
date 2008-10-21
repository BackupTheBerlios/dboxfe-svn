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
#include <soundpage.h>

#include <QtCore>
#include <QtGui>

namespace asaal {

  SoundPage::SoundPage( QWidget *parent ) : QWizardPage( parent ) {

    setupUi( this );
    setTitle( tr( "Grapihc option" ) );
    setSubTitle( tr( "Specify basic information about the sound for selected game." ) );

    registerField( "mixerRate", comboBoxMixerRate );
    registerField( "mixerBlockSize", comboBoxMixerBlockSize );
    registerField( "prebuffer", spinnBoxPrebuffer );
    registerField( "mixerNoSound", checkBoxMixerNoSound );
    registerField( "soundBlasterType", comboBoxSBType );
    registerField( "soundBlasterBase", comboBoxSBBase );
    registerField( "soundBlasterIRQ", comboBoxSBIRQ );
    registerField( "soundBlasterDMA", comboBoxSBDMA );
    registerField( "soundBlasterOplMode", comboBoxSBOplMode );
    registerField( "soundBlasterHDMA", comboBoxSBHDMA );
    registerField( "soundBlasterOPLRate", comboBoxSBOPLRate );
    registerField( "soundBlasterMixer", checkBoxSBMixer );
    registerField( "gusRate", comboBoxGUSRate );
    registerField( "gusBase", comboBoxGUSBase );
    registerField( "gusIrq_1", comboBoxGUSIrq_1 );
    registerField( "gusIrq_2", comboBoxGUSIrq_2 );
    registerField( "gusDMA_1", comboBoxGUSDMA_1 );
    registerField( "gusDMA_2", comboBoxGUSDMA_2 );
    registerField( "gusUltraDir", lineEditGUSUltraDir );
    registerField( "gus", checkBoxGUS );
    registerField( "speaker", comboBoxSpeaker );
    registerField( "speakerRate", comboBoxSpeakerRate );
    registerField( "speakerTandy", comboBoxSpeakerTandy );
    registerField( "speakerTandyRate", comboBoxSpeakerTandyRate );
    registerField( "disney", checkBoxDisney );
    registerField( "mdiMPU", comboBoxMDIMPU );
    registerField( "mdiDevice", comboBoxMDIDevice );
    registerField( "mdiConfig", lineEditMDIConfig );
  }

  int SoundPage::nextId() const {

    return GameWizard::PAGE_MISC;
  }

  QVariant SoundPage::fieldWidgetValue( const QString &fieldName ) const {

    if ( fieldName.isNull() || fieldName.isEmpty() ) {

      return QVariant();
    }

    if ( fieldName == "mixerRate" ) {
      return QVariant( comboBoxMixerRate->currentText() );

    } else if ( fieldName == "mixerBlockSize" ) {
      return QVariant( comboBoxMixerBlockSize->currentText() );

    } else if ( fieldName == "prebuffer" ) {
      return QVariant( spinnBoxPrebuffer->value() );

    } else if ( fieldName == "soundBlasterType" ) {
      return QVariant( comboBoxSBType->currentText() );

    } else if ( fieldName == "soundBlasterBase" ) {
      return QVariant( comboBoxSBBase->currentText() );

    } else if ( fieldName == "soundBlasterIRQ" ) {
      return QVariant( comboBoxSBIRQ->currentText() );

    } else if ( fieldName == "soundBlasterDMA" ) {
      return QVariant( comboBoxSBDMA->currentText() );

    } else if ( fieldName == "soundBlasterOplMode" ) {
      return QVariant( comboBoxSBOplMode->currentText() );

    } else if ( fieldName == "soundBlasterHDMA" ) {
      return QVariant( comboBoxSBHDMA->currentText() );

    } else if ( fieldName == "soundBlasterOPLRate" ) {
      return QVariant( comboBoxSBOPLRate->currentText() );

    } else if ( fieldName == "gusRate" ) {
      return QVariant( comboBoxGUSRate->currentText() );

    } else if ( fieldName == "gusBase" ) {
      return QVariant( comboBoxGUSBase->currentText() );

    } else if ( fieldName == "gusIrq_1" ) {
      return QVariant( comboBoxGUSIrq_1->currentText() );

    } else if ( fieldName == "gusIrq_2" ) {
      return QVariant( comboBoxGUSIrq_2->currentText() );

    } else if ( fieldName == "gusDMA_1" ) {
      return QVariant( comboBoxGUSDMA_1->currentText() );

    } else if ( fieldName == "gusDMA_2" ) {
      return QVariant( comboBoxGUSDMA_2->currentText() );

    } else if ( fieldName == "speaker" ) {
      return QVariant( comboBoxSpeaker->currentText() );

    } else if ( fieldName == "speakerRate" ) {
      return QVariant( comboBoxSpeakerRate->currentText() );

    } else if ( fieldName == "speakerTandy" ) {
      return QVariant( comboBoxSpeakerTandy->currentText() );

    } else if ( fieldName == "speakerTandyRate" ) {
      return QVariant( comboBoxSpeakerTandyRate->currentText() );

    } else if ( fieldName == "mdiMPU" ) {
      return QVariant( comboBoxMDIMPU->currentText() );

    } else if ( fieldName == "mdiDevice" ) {
      return QVariant( comboBoxMDIDevice->currentText() );
    }
    
    return QVariant();
  }
}
