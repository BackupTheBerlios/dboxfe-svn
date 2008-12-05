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

#include <xmlpreferences.h>

#include <QtCore>

/**
 * \brief Namespace asaal
 */ 
namespace asaal {


  /**
   * \brief DFend_Configuration handles read, write and convert of dfend configuration files
   *
   * @author Alexander Saal <alex.saal@gmx.de>
   * @sa http://dboxfe.belios.de/index
   * @date 2008/09/11
   * @version 0.2.5
   * @since 0.2.5
   */
   class DFend_Configuration {

    public:
      /** Set/Get extra settings */
      QMap< QString, QVariant > extra;

      /** Set/Get extrainfo settings */
      QMap< QString, QVariant > extrainfo;

      /** Set/Get extra settings */
      QMap< QString, QVariant > vga;

      /** Set/Get printer settings */
      QMap< QString, QVariant > printer;

      /** Set/Get glide settings */
      QString glide;

      /**
       * \brief Returns true if other points the same item of other; otherwise returns false.
       */
      bool operator == ( const DFend_Configuration &other ) const {
        return  extra == other.extra &&
                extrainfo == other.extrainfo &&
                vga == other.vga &&
                printer == other.printer &&
                glide == other.glide;
      }

      /**
       * \brief Returns true if other points to a different item than this other; otherwise returns false.
       */
      bool operator != ( const DFend_Configuration &other ) const {
        return  extra != other.extra ||
                extrainfo != other.extrainfo ||
                vga != other.vga ||
                printer != other.printer ||
                glide != other.glide;
      }

      /**
       * \brief Returns true if the cache contains no objects; otherwise returns false.
       */
      bool isEmpty() const {
        return  extra.isEmpty() &&
                extrainfo.isEmpty() &&
                vga.isEmpty() &&
                printer.isEmpty() &&
                glide.isEmpty();
      }

      /**
       * \brief Deletes all the objects in the cache.
       */
      void clear() {
        extra.clear();
        extrainfo.clear();
        vga.clear();
        printer.clear();
        glide = QString( "" );
      }
  };

  /**
   * \brief Configuration handles all objects from dosbox configuration file
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

      /** DFend - Realoded Configuraion */
      DFend_Configuration dfendConfig;

      /**
       * \brief Returns true if other points the same item of other; otherwise returns false.
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
                dfendConfig == other.dfendConfig &&
                autoexec == other.autoexec;
      }

      /**
       * \brief Returns true if other points to a different item than this other; otherwise returns false.
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
                dfendConfig != other.dfendConfig ||
                autoexec != other.autoexec;
      }

      /**
       * \brief Returns true if the cache contains no objects; otherwise returns false.
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
                dfendConfig.isEmpty() &&
                ( ipx.isEmpty() || ipx.isNull() ) &&
                ( autoexec.isEmpty() || autoexec.isNull() );
      }

      /**
       * \brief Deletes all the objects in the cache.
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
        dfendConfig.clear();
        autoexec = QString( "" );
      }
  };

  /**
   * \brief ConfigBase handles read, write and convert of dosbox configuration files
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
       * \brief Constructor
       * 
       * @param parent The optional QObject object
       */ 
      ConfigBase( QObject *parent = 0 );

      /**
       * \brief Destructor
       */ 
      ~ConfigBase();

      /**
       * \brief Returns the profiles for dboxfe in a QStringList
       */ 
      QStringList readProfiles();

      /**
       * \brief Returns the instance of XmlPreferences
       * @see XmlPreferences
       */ 
      XmlPreferences xmlPreferences();

      /**
       * \brief Read configuration
       *
       * @param profile The DBoxFE profile
       * @return The configuration @see Configuration for readed profile
       */
      Configuration readConfiguration( const QString &profile );

      /**
       * \brief Convert D-Fend Reloaded profile to DBoxFE.<br>
       *
       * @param profile The D-Fend Reloaded profile
       * @return The configuration @see Configuration from given profile
       */
      Configuration convertConfiguration( const QString &profile );

      /**
       * \brief Import D-Fend Reloaded  profiles from ZIP file.
       *
       * @param zipFile The ZIP file with DFend Reloaded configuration
       * @return The dosbox default configuration with all objects inclusive the dfend configuration.
       * @see Configuration and @see DFend_Configuration
       */
      Configuration importConfiguration( const QString &zipFile );

      /**
       * \brief Export DBoxFE profile to D-Fend Reloaded
       *
       * @param name The name of profile
       * @param config The config @see Configuration
       * @return true was write ok; otherwise false
       */
      bool exportConfiguration( const QString &name, const Configuration &config );

    public slots:
      /**
       * \brief Write configuration
       *
       * @param profile The DBoxFE profile
       * @param config The config @see Configuration
       */
      void writeConfiguration( const QString &profile, const Configuration &config );

    private:
      /**
       * \brief Get files/directories for D-Fend Reloaded exported ziparchiv.
       *
       * @param directory The directory with all files/directories for export to zip
       * @return QMap< QString, QString > with all files
       */
      QMap< QString, QString> exportDatas( const QString &directory );

      /**
       * Internal variables
       */ 
      Configuration m_Configuration;
      QStringList profiles;
  };
}

#endif // BASE_H
