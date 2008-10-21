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

#ifndef INSTALLPAGE_H
#define INSTALLPAGE_H

#include <ui_installpage.h>

#include <QtGui>

namespace asaal {

  /**
   * @brief $(CLASSNAME)
   */

  class InstallPage : public QWizardPage, public Ui::UiInstallPage {
      Q_OBJECT

    public:
      /**
       * @brief $(CONSTRUCTORNAME)
       *
       * @param parent the optional parent widget
       */
      InstallPage( QWidget *parent = 0 );

      int nextId() const;

    private slots:
      /**
       * Choose game setup file from local drive or from CD/DVD
       */
      void chooseDosBoxBinary();

      /**
       * Choose game setup file from local drive or from CD/DVD
       */
      void chooseGameSetupFile();

      /**
       * Choose game installation folder
       */
      void chooseGameInstallFolder();

      /**
       * Choose game executable
       */
      void chooseGameExecutable();

      /**
       * Choose game folder
       */
      void choosGameFolder();

      /**
       * Installation type was changed
       *
       * @param install
       */
      void gameInstallOptionChanged( bool );
      void gameSettingOptionChanged( bool );

      /**
       * Show information message
       *
       * @param title the title of message
       * @param message the message to display
       */
      void showMessage( const QString &title, const QString &message ) const;

    private:
      /**
       * Check dosbox version
       *
       * @param dosbox
       */
      QString checkDosBoxVersion( const QString &dosbox );
  };
}

#endif // INSTALLPAGE_H
