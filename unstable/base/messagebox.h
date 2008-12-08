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

namespace asaal {

	class MessageBox : public QDialog, public Ui::UiMessageBox {

		Q_OBJECT
		
		public:
			MessageBox( QWidget *parent = 0 );
			~MessageBox()

		public slots:
			void setMessageBoxTitle( const QString &title = QString ( "" ) );

			void setMessageBoxInstruction( const QString &instruction = QString( "" ) );

			void setCommandButton1Text( const QString &text = QString( "" ) );

			void setCommandButton1Description( const QString &description = QString( "" ) );

			void setCommandButton2Text( const QString &text = QString( "" ) );

			void setCommandButton2Description( const QString &description = QString( "" ) );

		private slots:
			void cmdButtonClicked();
			
		Q_SIGNALS:
			void commandButton1Clicked();
			void commandButton2Clicked();
			
		protected:
			void closeEvent( QCloseEvent *e );

		private:
			QString m_Title;
			QString m_Instruction;
			QString m_CmdBtn1Text;
			QString m_CmdBtn1Description;
			QString m_CmdBtn2Text;
			QString m_CmdBtn2Description;
	};
}

#endif // MESSAGEBOX_H
