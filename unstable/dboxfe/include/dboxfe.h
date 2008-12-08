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

#ifndef DBOXFE_H
#define DBOXFE_H

#include <base.h>
#include <messagebox.h>
#include <profile.h>
#include <profilesettings.h>

#include "ui_dboxfe.h"

#include <QtGui>


/**
 * \brief Namespace asaal
 */

namespace asaal {

  /**
   * Initial variable for ConfigBase
   * @see ConfigBase
   */
  extern ConfigBase *configBase;

  class DBoxFE;
  extern DBoxFE *dboxfe;

  /**
   * \brief DBoxFE
   *
   * @author Alexander Saal <alex.saal@gmx.de>
   * @sa http://dboxfe.berlios.de/index
   * @date 2008/5/10
   * @version 0.2.5
   * @since 0.2.5
   */

  class DBoxFE : public QWidget, public Ui::UiDBoxFE {
      Q_OBJECT

    public:
      /**
       * \brief Constructor of DBoxFE
       *
       * @param parent The optional parent widget
       * @param flags The optional window flag
       */
      DBoxFE( QWidget *parent = 0, Qt::WFlags flags = 0 );

      /**
       * \brief De-Constructor
       */
      ~DBoxFE();

      /**
       * \brief Return the instance of ConfigBase
       */
      inline static ConfigBase *configBaseInstance() {

        return configBase;
      }

      /**
       * \brief Return the instance of ConfigBase
       */
      inline static DBoxFE *instance() {

        return dboxfe;
      }

    public slots:
      /**
       * \brief Initial profiles. It means, get all profiles and store it into QListWidget
       */
      void initialProfiles();

    protected:
      /**
       * This event handler is called with the given event when Qt receives
       * a window close request for a top-level widget from the window system.
       *
       * @param e The QCloseEvent
       */
      void closeEvent( QCloseEvent *event );

    private slots:
      /*
       * Open/Apply/Clear description
       */
      void openDescription();
      void applyDescription();
      void clearDescription();

      /*
       * Open/Apply/Clear screen capture
       */
      void openScreenCapture();
      void applyScreenCapture();
      void clearScreenCapture();

      /*
       * Start/New/Edit/Delete/ game
       */
      void startGame();
      void newGame();
      void editGame();
      void deleteGame();

      /*
       * This signal is emitted when the text edit contextMenuPolicy is Qt::CustomContextMenu,
       * and the user has requested a context menu on the text edit. The position "pos" is the
       * position of the context menu event that the text edit receives.
       */
      void textEditCustomContextMenuRequested( const QPoint & );

      /*
       * This signal is emitted with the specified item when a mouse button is double clicked on an item in the widget.
       */
      void listWidgetItemDoubleClicked( QListWidgetItem * );

      /*
       * Create new game with Assistant
       */
      void newGameWithAssistant();

      /**
       * \brief This signal is emitted when the command button on MessageBox is clicked.
       * 
       * @param commandLinkButton The command link button from MessageBox 
       * 
       * @see MessageBox
       */ 
      void deleteProfile( const QCommandLinkButton * );

      /**
       * \brief Start dosbox
       *
       * @param bin The dosbox binary
       * @param param The parameter for dosbox
       * @param conf The profile configuration
       */
      void processStart( const QString& bin, const QString &param, const QString &conf );

      /**
       * \brief Read Std. output from console
       */
      void processOutput();

      /**
       * \brief Process finish
       *
       * @param exitCode Result of process state
       * @param exitStatus Result of exit status
       */
      void processFinish( int, QProcess::ExitStatus );

      /**
       * \brief Process was exited and have an error occured
       *
       * @param error The error information
       */
      void processError( QProcess::ProcessError );
      
    private:
      Profile *profile;
      ProfileSettings *profSettings;     
      MessageBox *messageBox;
  };
}

#endif // DBOXFE_H
