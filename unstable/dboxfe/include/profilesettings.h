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

#ifndef PROFILESETTINGS_H
#define PROFILESETTINGS_H

#include <ui_profilesettings.h>

#include <base.h>

#include <QtGui>

/**
* \brief Namespace asaal
*/

namespace asaal {

  /**
   * \brief ProfileSettings
   *
   * @author Alexander Saal <alex.saal@gmx.de>
   * @sa http://dboxfe.belios.de/index
   * @date 2008/09/11
   * @version 0.2.5
   * @since 0.2.5
   */

  class ProfileSettings : public QDialog, public Ui::UiProfileSettings {

      Q_OBJECT

    public:
      /**
       * \brief Constructor of ProfileSettings
       *
       * @param parent The optional parent widget
       * @param flags The optional window flags
       */
      ProfileSettings( QWidget *parent = 0, Qt::WFlags flags = 0 );

      /**
       * \brief De-Constructor of ProfileSettings
       */
      ~ProfileSettings();

    public slots:
      /**
       * \brief Set profile name
       *
       * @param name The profile name
       */
      inline void setProfileName( const QString &name ) {

        profName = name;
        setWindowTitle( tr( "Settings for [ %1 ]" ).arg( profName ) );
      }

      inline void initialConfiguration( const QString &configFile ) {

        profFile = configFile;
        loadConfiguration();
      }

    private slots:
      /**
       * \brief This event slot is called if you change index in the serial combobox
       *
       * @param index the current index from QComboBox
       */
      void comboBoxSerialIndexChanged( int );

      /**
       * \brief This event slot is called if you change index in the autoexec combobox
       *
       * @param index the current index from QComboBox
       */
      void comboBoxAutoexecIndexChanged( int );

      /**
       * \brief
       *
       * @param index The current index from QComboBox
       */
      void comboBoxAutoexecImageFormatIndexChanged( int );

      /**
       * \brief This event slot is called if you change keyboard layout for DOSBox
       *
       * @param index the current index from QComboBox
       */
      void comboBoxKeyboardLayoutIndexChanged( int );

      /**
       * \brief Select autexec drive
       */
      void autoexecDrive();

      /**
       * \brief Update autoecex entry in the list
       */
      void autoexecUpdate();

      /**
       * \brief Remove autoecex entry to the list
       */
      void autoexecRemove();

      /**
       * \brief Add autoecex entry to the list
       */
      void autoexecAdd();

      /**
       * \brief Move entry in autoexec list up
       */
      void autoexecMoveUp();

      /**
       * \brief Move entry in autoexec list down
       */
      void autoexecMoveDown();
      
      /**
       * \brief Add game executable to this profile
       */
      void addGame();

      /**
       * \brief Remove serial interface to the list
       */
      void serialRemove();

      /**
       * \brief Add serial interface to the list
       */
      void serialAdd();

      /**
       * \brief Open language file from file system.
       */
      void openLanguageFile();

      /**
       * \brief Save configuration for selected profile
       *
       * @see Configuration
       */
      void saveConfiguration();

      /**
       * \brief Set default configuration
       *
       * @see Configuration
       */
      void setDefaultConfiguration();


      /**
       * \brief Load configuration
       */
      void loadConfiguration();

      /**
       * \brief Close widget
       */
      void closeWidget();

    protected:
      /**
       * \brief This event slot is called if you close the current widget; overide from QWidget
       *
       * @param e The QCloseEvent fired from QWidget
       */
      void closeEvent( QCloseEvent *e );

    private:
      /**
       * Internal, private variables
       */
      QString profFile;
      QString profName;
      Configuration profileConfiguration;
  };
}

#endif // PROFILESETTINGS_H
