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

#include <QtGui>

#include "ui_dboxfe.h"

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
  };
}

#endif // DBOXFE_H