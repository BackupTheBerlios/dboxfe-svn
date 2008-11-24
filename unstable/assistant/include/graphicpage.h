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

#ifndef GRAPHICPAGE_H
#define GRAPHICPAGE_H

#include <ui_graphicpage.h>

#include <QtGui>

namespace asaal {

  /**
  * @brief $(CLASSNAME)
  */

  class GraphicPage : public QWizardPage, public Ui::UiGraphicPage {
      Q_OBJECT

    public:
      /**
      * @brief $(CONSTRUCTORNAME)
      *
      * @param parent the optional parent widget
      */
      GraphicPage( QWidget *parent = 0 );

      /**
       * The next id
       */
      int nextId() const;

      /**
       * Get field as widget
       *
       * @parame fieldName The name of registered field
       * @return QVariant valze with the assocciated field name
       */
      QVariant fieldWidgetValue( const QString &fieldName ) const;
  };
}

#endif // GRAPHICPAGE_H
