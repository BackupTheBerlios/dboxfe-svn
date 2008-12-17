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

#ifndef GAMES_H
#define GAMES_H

#include <ui_games.h>

#include <QtGui>

/**
 * \brief Namespace asaal
 */

namespace asaal {

  /**
   * \brief Games handles games in the resource stream
   *
   * @author Alexander Saal <alex.saal@gmx.de>
   * @sa http://dboxfe.belios.de/index
   * @date 2008/17/12
   * @version 0.2.5
   * @since 0.2.5
   */

  class Games : public QDialog, public Ui::UiGames {

      Q_OBJECT

    public:
      /**
       * \brief Constructor
       *
       * @param parent The optional parent widget
       * @param flags The optional window flags
       */
      Games( QWidget *parent = 0, Qt::WFlags flags = 0 );

      /**
       * \brief Destructor
       */
      ~Games();

      /**
       * \brief Get the game executable
       *
       * @return String with game executable (incl. the path)
       */
      QString executable() {

        return mExecutable;
      }

    public slots:
      /**
       * \brief Initial games from stream
       */
      void initalGames();

    private slots:
      /**
       * \brief Game was accepted
       */
      void gameAccept();

      /**
       * \brief Select game executable from filesystem
       */
      void gameExecutable();

    protected:
      /**
       * \brief This event slot is called if you close the current widget; overide from QWidget
       *
       * @param e The QCloseEvent fired from QWidget
       */
      void closeEvent( QCloseEvent *e );

    private:
      /* Private members and variables */
      QString mExecutable;
  };
}

#endif // GAMES_H
