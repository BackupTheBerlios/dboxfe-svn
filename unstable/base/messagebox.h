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

#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <ui_messagebox.h>

#include <QtCore>
#include <QtGui>

/**
 * \brief Namespace asaal
 */ 
namespace asaal {

  /**
   * \brief MessageBox to handles messages from dboxfe
   * 
   * @author Alexander Saal <alex.saal@gmx.de>
   * @sa http://dboxfe.belios.de/index
   * @date  2008/08/12
   * @version 0.2.5
   * @since 0.2.5
   */ 
  class MessageBox : public QDialog, public Ui::UiMessageBox {

     Q_OBJECT

    public:
      /**
       * \brief Constructor of MessageBox
       * 
       * @param parent Optional parent widget
       * @param cmdBtn1Id The optional id for first command link button
       * @param cmdBtn2Id The optional id for second command link button
       */ 
      MessageBox( QWidget *parent = 0, const QString &cmdBtn1Id = QString( "cmdButtonOne" ), const QString &cmdBtn2Id = QString( "cmdButtonTwo" ));

      /**
       * \brief De-Constructor of MessageBox
       */ 
      ~MessageBox();

      public slots:
        /**
         * \brief Set window title
         * 
         * @param title The title.
         */ 
        void setMessageBoxTitle( const QString &title = QString ( "" ) );

        /**
         * \brief Set instruction (message)
         * 
         * @param instruction The instruction
         */ 
        void setMessageBoxInstruction( const QString &instruction = QString( "" ) );

        /**
         * \brief Set text for the first command link button
         * 
         * @param text The text
         */ 
        void setCommandButton1Text( const QString &text = QString( "" ) );

        /**
         * \brief Set description for the first command link button
         * 
         * @param description The description
         */ 
        void setCommandButton1Description( const QString &description = QString( "" ) );

        /**
         * \brief Set text for the second command link button
         * 
         * @param text The text
         */ 
        void setCommandButton2Text( const QString &text = QString( "" ) );

        /**
         * \brief Set description for the second command link button
         * 
         * @param description The description
         */
        void setCommandButton2Description( const QString &description = QString( "" ) );

     private slots:
          /**
           * \brief This event is called if you clicked on a QCommandLinkButton
           */ 
          void commandButtonClicked();

Q_SIGNALS:
          /**
           * \brief This signal is emitted when the command button on MessageBox is clicked.
           */ 
          void commandLinkButtonClicked( const QCommandLinkButton *commandButton );

    protected:
      /**
       * \brief 
       * @param e 
       */ 
      void closeEvent( QCloseEvent *e );
  };
}

#endif // MESSAGEBOX_H
