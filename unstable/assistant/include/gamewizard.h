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

#ifndef GAMEWIZARD_H
#define GAMEWIZARD_H

#include <base.h>
#include <finishpage.h>
#include <graphicpage.h>
#include <importexportpage.h>
#include <installpage.h>
#include <installprocesspage.h>
#include <miscpage.h>
#include <settingpage.h>
#include <soundpage.h>
#include <welcomepage.h>

#include <QWizard>
#include <QWidget>

namespace asaal {

  class GameWizard;
  extern GameWizard *gameWizard;
  extern ConfigBase *configBase;

  /**
   * \brief GameWizard is the main class of the DBoxFE - Assistant
   * 
   * @author Alexander Saal <laex.saal@gmx.de>
   * @sa http://dboxfe.belios.de/index
   * @date 2008/09/11
   * @version 0.2.5
   * @since 0.2.5
   */ 
  class GameWizard : public QWizard {
      Q_OBJECT

    public:

      /**
       * Enumeration for @see GameWizard
       */ 
      enum {
        /**
        * Welcome page
        */
        PAGE_WELCOME,
        /**
         * Setting config page
         */
        PAGE_SETTING,

        /**
        * Installation page
         */ 
        PAGE_INSTALL,
        /**
        * Installation process page
        */
        PAGE_INSTALLPROCESS,
        /**
         * Export page
         */
        PAGE_IMPORTEXPORT,
        /**
        * Graphic config page
        */
        PAGE_GRAPHIC,
        /**
         * Sound config page
         */
        PAGE_SOUND,
        /**
        * Misc. config page
        */
        PAGE_MISC,
        /**
        * Finsh page
        */
        PAGE_FINSH
      };

      /**
      * @brief GameWizard
      *
      * @param parent the optional parent widget
      */
      GameWizard( QWidget *parent = 0 );

      /**
      * Get the instance of GameWizard
      *
      * @return The instance of GameWizard
      */
      inline static GameWizard *instance() {

        return gameWizard;
      }

      /**
       * \brief Get the ConfigBase instance
       * 
       * @return The new instance of ConfigBase
       */ 
      inline static ConfigBase *configBaseInstance() {

        return configBase;
      }

      /**
       * \brief Hides the modal dialog and sets the result code to Accepted. This function is reimplemented from QWizard
       */ 
      void accept();

    private:

      /**
       * \brief Create game profile
       * 
       * @param profile The profile name (complete path with filename)
       * @return True was profile created, othwerwise false
       */ 
      bool createGameProfile( const QString &profile );

      WelcomePage *wp;
      ImportExportPage *ie;
      InstallPage *ip;
      InstallProcessPage *ipp;
      GraphicPage *gp;
      SettingPage *settp;      
      SoundPage *sp;
      MiscPage *mp;
      FinishPage *fp;

  };
}

#endif // GAMEWIZARD_H
