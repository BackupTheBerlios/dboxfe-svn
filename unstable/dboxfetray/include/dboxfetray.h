/*
*   Copyright (C) 2007 by Alexander Saal <alex.saal@gmx.de>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef DBOXFE_TRAY_H
#define DBOXFE_TRAY_H

#include <QtGui>
#include <QtCore>

class DBoxFE_TrayIcon : public QWidget {
        Q_OBJECT

    public:
        DBoxFE_TrayIcon();
		void setVisible(bool visible);

    private:
		QString getAppVersion() { return tr( "v0.1.3 (SVN)" ); }
		QString getAppTitel() { return tr( "DBoxFE - TrayIcon" ); }

		QSystemTrayIcon *dbfe_trayIcon;
		QMenu *dbfe_trayIconMenu;
		QAction *dbfe_trayAction;
		QString m_file;
		QString dbox_bin;
		QProcess *dBox;
		QProcess *dboxfe;
		QStringList m_param;
		QTimer *update;

    protected:
        void closeEvent( QCloseEvent *e );

    private slots:
		void createMenu();
		void reloadMenu();
		void startGame();
		void startdboxfe();

		void start( const QString& bin, const QString &param, const QString &conf );
};

#endif // DBOXFE_TRAY_H
