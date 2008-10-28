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

#include <gamewizard.h>
#include <settingpage.h>

#include <QtCore>
#include <QtGui>

namespace asaal {

  SettingPage::SettingPage( QWidget *parent ) : QWizardPage( parent ) {

    setupUi( this );

    setTitle( tr( "Seting option" ) );
    setSubTitle( tr( "Select a option above and click 'Next' to continue." ) );
  }

  int SettingPage::nextId() const {

    if ( rbtnInstallAddGame->isChecked() ) {
      return GameWizard::PAGE_INSTALL;

    } else if ( rbtnImportDFendProfile->isCheckable() ) {
      return GameWizard::PAGE_IMPORTPROFILE;

    } else if ( rbtnExportDboxFeProfile->isCheckable() ) {
      return GameWizard::PAGE_EXPORTPROFILEPAGE_SETTING;

    }

    return GameWizard::PAGE_SETTING;
  }
}
