/***************************************************************************
*   Copyright (C) 2007-2008 by Alexander Saal                             *
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

#ifndef TRAY_H
#define TRAY_H

#include <QtGui>
#include <QtCore>

namespace asaal {

  class TrayIcon : public QWidget {
      Q_OBJECT

    public:
      TrayIcon();

      void setVisible( bool visible );

    private:
      QString getAppVersion() {
        return tr( "v0.2.5" );
      }

      QString getAppTitel() {
        return tr( "DBoxFE - TrayIcon" );
      }

      QSystemTrayIcon *trayIcon;
      QMenu *trayIconMenu;
      QAction *trayAction;
      QString m_file;
      QString dosbox;
      QProcess *m_DosBoxProcess;
      QProcess *m_ProcessDboxfe;
      QStringList m_param;
      QTimer *update;

    protected:
      void closeEvent( QCloseEvent *e );

    private slots:
      void aboutTrayIcon();
      void createMenu();
      void reloadMenu();
      void startGame();
      void startdboxfe();
      void start( const QString& bin, const QString &param, const QString &conf );
  };
}

#endif // TRAY_H
