/***************************************************************************
 *   Copyright (C) 2004-2008 by Alexander Saal                             *
 *   alex.saal@gmx.de                                                      *
 *                                                                          *
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

#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <base.h>

#include "ui_preference.h"

#include <QtGui>

/**
 * \brief Namespace asaal
 */
namespace asaal {

  /**
   * \brief Preference
   *
   * @author Alexander Saal <alex.saal@gmx.de>
   * @sa http://dboxfe.berlios.de/index
   * @date 2008/10/12
   * @version 0.2.5
   * @since 0.2.5
   */
  class Preference : public QDialog, public Ui::UiPreferences {

      Q_OBJECT

    public:
      /**
       * \brief Constructor of Preference
       *
       * @param parent The optional widget
       */
      Preference( QWidget *parent = 0 );

      /**
       * \brief De-Constructor of Preference
       */
      ~Preference();

    private slots:

      /**
       * Save preferences
       */
      void save();

      /**
       * Choose dosbox binary from file system
       */
      void chooseDosbox();

      /**
       * Load DBoxFE settings
       *
       * @param dboxfeConfig The DBoxFE configuration
       *
       * @see DBoxFE_Configuration
       */
      void loadSettings( const DBoxFE_Configuration &dboxfeConfig );

    protected:
      /**
       * This event handler is called with the given event when Qt receives
       * a window close request for a top-level widget from the window system.
       *
       * @param event The QCloseEvent
       */
      void closeEvent( QCloseEvent *event );

    private:
      /*
       * Private member and variables
       */
      QProcess *dosbox;
      QStringList parameters;
      QString dosboxBinary;
      QString dosboxVersion;

      ConfigBase *configBase;
      DBoxFE_Configuration dboxfeConfig;
  };
}

#endif // PREFERENCE_H
