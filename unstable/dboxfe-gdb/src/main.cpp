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
#include "dboxfegdb.h"
#include "dboxfegdb_assistant.h"

#include <XMLPreferences.h>

#include <QtCore>
#include <QtGui>

int main( int argc, char **argv )
{
	QApplication app ( argc, argv );

	XMLPreferences xmlPreferences( "DBoxFE - GDB", "Alexander Saal" );
	xmlPreferences.load( QDir::homePath() + "/.dboxfe-gdb/dboxfegdb.xml" );

	QString database = xmlPreferences.getString( "Database", "DatabaseFile" );

	bool startAgain = true;
	startAgain = xmlPreferences.getBool( "Assistant", "StartAgain" );
	
	if( startAgain )
	{
		GameDatabaseAssistant *gd_a = new GameDatabaseAssistant( 0 );
		if( gd_a->exec() == QDialog::Accepted )
		{
			GameDatabaseDialog gd_dialog;
			app.processEvents();

			gd_dialog.exec();
			app.connect ( &app, SIGNAL ( lastWindowClosed() ), &app, SLOT ( quit() ) );
			return app.exec();
		}
		else
			return -1;
	}
	else
	{
		if( database.isNull() || database.isEmpty() )
		{
			GameDatabaseAssistant *gd_a = new GameDatabaseAssistant( 0 );
			if( gd_a->exec() == QDialog::Accepted )
			{
				GameDatabaseDialog gd_dialog;
				app.processEvents();

				gd_dialog.exec();
				app.connect ( &app, SIGNAL ( lastWindowClosed() ), &app, SLOT ( quit() ) );
				return app.exec();
			}
			else
				return -1;
		}
		else
		{
			GameDatabaseDialog gd_dialog;
			app.processEvents();
			gd_dialog.exec();

			return 0;
		}

		return 0;
	}


	app.connect ( &app, SIGNAL ( lastWindowClosed() ), &app, SLOT ( quit() ) );
	return app.exec();
}
