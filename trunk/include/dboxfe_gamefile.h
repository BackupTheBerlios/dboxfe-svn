/*
*   Copyright (C) 2004 - 06 by Alexander Saal <alex.saal@gmx.de>
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
#ifndef DBOXFE_GAMEFILE_H
#define DBOXFE_GAMEFILE_H

#include "ui_gamefile.h"
#include "dboxfe_gamesettings.h"

#include <QtGui>
#include <QtCore>
#include <QtNetwork>

class DBoxFE_GameFile : public QWidget
{
        Q_OBJECT

    public:
        DBoxFE_GameFile( QWidget *parent = 0, Qt::WFlags flags = 0 );
        ~DBoxFE_GameFile();

        Ui::DBoxFE_GameFile ui;
                
    protected:
        void closeEvent( QCloseEvent *e );

    private:
        QHttp *m_http;
        QFile *m_file;

        int httpGetId;
        bool httpRequestAborted;
				
    public slots:
        void loadGameFile( const QString &url );
        void parseGameFile( const QString &file, DBoxFE_GameSettings *dbfe_gs );

    private slots:
				void httpDataReadProgress( int done, int total  );
        void httpRequestFinished( int requestId, bool error );
        void readResponseHeader( const QHttpResponseHeader &responseHeader );
};

#endif // DBOXFE_GAMEFILE_H
