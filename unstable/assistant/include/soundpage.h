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

#ifndef SOUNDPAGE_H
#define SOUNDPAGE_H

#include <ui_soundpage.h>

#include <QtGui>

namespace asaal {

  /**
  * @brief $(CLASSNAME)
  */

  class SoundPage : public QWizardPage, public Ui::UiSoundPage {
      Q_OBJECT

    public:
      /**
      * @brief $(CONSTRUCTORNAME)
      *
      * @param parent the optional parent widget
      */
      SoundPage( QWidget *parent = 0 );

      int nextId() const;

      /**
       * Get field value from widget
       *
       * @parame fieldName The name of registered field
       * @return QVariant value with the assocciated field name
       */
      QVariant fieldWidgetValue( const QString &fieldName ) const;
  };
}

#endif // SOUNDPAGE_H
