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

#ifndef BASE_H
#define BASE_H

#include <QtCore>

namespace asaal {

  /**
  * Configuration handles all objects from dosbox configuration file
  *
  * @author Alexander Saal <alex.saal@gmx.de>
  * @sa http://dboxfe.belios.de/index
  * @date 2008/31/10
  * @version 0.2.5
  * @since 0.2.5
  */

  class Configuration {

    public:
      /** Set/Get sdl settings */
      QMap< QString, QVariant > sdl;

      /** Set/Get dosbox settings */
      QMap< QString, QVariant > dosbox;

      /** Set/Get render settings */
      QMap< QString, QVariant > render;

      /** Set/Get ipx settings */
      QMap< QString, QVariant > cpu;

      /** Set/Get mixer settings */
      QMap< QString, QVariant > mixer;

      /** Set/Get mdi settings */
      QMap< QString, QVariant > mdi;

      /** Set/Get sblaster settings */
      QMap< QString, QVariant > sblaster;

      /** Set/Get gus settings */
      QMap< QString, QVariant > gus;

      /** Set/Get speaker settings */
      QMap< QString, QVariant > speaker;

      /** Set/Get joystick settings */
      QMap< QString, QVariant > joystick;

      /** Set/Get serial settings */
      QMap< QString, QVariant > serial;

      /** Set/Get dos settings */
      QMap< QString, QVariant > dos;

      /** Set/Get ipx settings */
      QString ipx;

      /** Set/Get autoexec settings */
      QString autoexec;

      /**
      * Returns true if other points the same item of other; otherwise returns false.
      */
      bool operator == ( const Configuration &other ) const {
        return  sdl == other.sdl &&
                dosbox == other.dosbox &&
                render == other.render &&
                cpu == other.cpu &&
                mixer == other.mixer &&
                mdi == other.mdi &&
                sblaster == other.sblaster &&
                gus == other.gus &&
                speaker == other.speaker &&
                joystick == other.joystick &&
                serial == other.serial &&
                dos == other.dos &&
                ipx == other.ipx &&
                autoexec == other.autoexec;
      }

      /**
      * Returns true if other points to a different item than this other; otherwise returns false.
      */
      bool operator != ( const Configuration &other ) const {
        return  sdl != other.sdl ||
                dosbox != other.dosbox ||
                render != other.render ||
                cpu != other.cpu ||
                mixer != other.mixer ||
                mdi != other.mdi ||
                sblaster != other.sblaster ||
                gus != other.gus ||
                speaker != other.speaker ||
                joystick != other.joystick ||
                serial != other.serial ||
                dos != other.dos ||
                ipx != other.ipx ||
                autoexec != other.autoexec;
      }

      /**
      * Returns true if the cache contains no objects; otherwise returns false.
      */
      bool isEmpty() const {
        return  sdl.isEmpty() &&
                dosbox.isEmpty() &&
                render.isEmpty() &&
                cpu.isEmpty() &&
                mixer.isEmpty() &&
                mdi.isEmpty() &&
                sblaster.isEmpty() &&
                gus.isEmpty() &&
                speaker.isEmpty() &&
                joystick.isEmpty() &&
                serial.isEmpty() &&
                dos.isEmpty() &&
                ( ipx.isEmpty() || ipx.isNull() ) &&
                ( autoexec.isEmpty() || autoexec.isNull() );
      }

      /**
      * Deletes all the objects in the cache.
      */
      void clear() {
        sdl.clear();
        dosbox.clear();
        render.clear();
        cpu.clear();
        mixer.clear();
        mdi.clear();
        sblaster.clear();
        gus.clear();
        speaker.clear();
        joystick.clear();
        serial.clear();
        dos.clear();
        ipx.clear();
        autoexec = QString( "" );
      }
  };

  /**
  * ConfigBase handles read, write and convert of dosbox configuration files
  *
  * @author Alexander Saal <alex.saal@gmx.de>
  * @sa http://dboxfe.belios.de/index
  * @date 2008/31/10
  * @version 0.2.5
  * @since 0.2.5
  */

  class ConfigBase : public QObject {

      Q_OBJECT

    public:
      /**
       * Profile type
       */
      enum profileType {
        /** D-Fend Reloaded to DBoxFE */
        DFEND = 0
      };
      Q_DECLARE_FLAGS( ProfileType, profileType )

      /**
      * @brief Constructor
      *
      * @param parent The optional QObject object
      */
      ConfigBase( QObject *parent = 0 );

      /**
      * @brief Destructor
      */
      ~ConfigBase();

      /**
      * Get instance of @link ConfigBase
      */
      inline static ConfigBase* innstance() {

        if ( !m_Instance ) {
          m_Instance = new ConfigBase();
        }

        return m_Instance;
      }

      /**
       * Get @link Configuration for the given profile
       *
       * @param profile The DBoxFE profile
       */
      Configuration readConfiguration( const QString &profile );

      /**
       * Convert D-Fend Reloaded profiles to DBoxFE profiles or DBoxFE to D-Fend Reloaded
       *
       * @param profile The D-Fend Reloaded profile or DBoxFE profile
       * @param type The @link ProfileType
       *
       * @return @link Configuration
       */
      Configuration convertConfiguration( const QString &profile, ProfileType type = ConfigBase::DFEND );

      /**
       * Export DBoxFE profile to D-Fend Reloaded
       *
       * @param name The name of profile
       * @param config The @link Configuration
       */
      bool exportConfiguration( const QString &name, const Configuration &config );

    public slots:
      /**
       * Write @link Configuration
       *
       * @param profile The DBoxFE profile
       * @param config The @link Configuration
       */
      void writeConfiguration( const QString &profile, const Configuration &config );

    private:
      /**
       * Get files/directories for D-Fend Reloaded exported ziparchiv.
       *
       * @param directory The directory with all datas for export to zip
       * @return QStringList with all files
       */
      QMap< QString, QString> exportData( const QString &directory );

      static ConfigBase* m_Instance;
      Configuration m_Configuration;
  };

  Q_DECLARE_OPERATORS_FOR_FLAGS( ConfigBase::ProfileType )
}

#endif // BASE_H
