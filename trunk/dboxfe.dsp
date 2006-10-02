# Microsoft Developer Studio Project File - Name="dboxfe" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=dboxfe - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dboxfe.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dboxfe.mak" CFG="dboxfe - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dboxfe - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dboxfe - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl
MTL=midl
RSC=rc
BSC32=bscmake.exe

!IF  "$(CFG)" == "dboxfe - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "bin"
# PROP BASE Intermediate_Dir "win\obj"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "bin"
# PROP Intermediate_Dir "win\obj"
# PROP Target_Dir ""
# ADD CPP /I"$(QTDIR)/include/QtCore" /I"$(QTDIR)/include/QtNetwork" /I"$(QTDIR)/include/QtGui" /I"$(QTDIR)/include/QtXml" /I"$(QTDIR)/include" /I"include" /I"3rdparty" /I"$(QTDIR)/include/ActiveQt" /I"win\moc" /I"win\ui" /I"..\..\..\Lib\qt4\mkspecs\win32-msvc" /c /FD -nologo -Zm200 -O1 -MD -O1 -MD -W3 -GR -GX  /D "_WINDOWS"  /D UNICODE /D QT_LARGEFILE_SUPPORT /D QT_DLL /D QT_NO_DEBUG /D QT_XML_LIB /D QT_GUI_LIB /D QT_NETWORK_LIB /D QT_CORE_LIB /D QT_THREAD_SUPPORT  /D "WIN32"   /D "QT_THREAD_SUPPORT" 
# ADD MTL /nologo /mktyplib203 /win32 /D "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
# ADD BSC32 /nologo
LINK32=link
# ADD LINK32 /NOLOGO /INCREMENTAL:NO /INCREMENTAL:NO /SUBSYSTEM:windows /LIBPATH:"$(QTDIR)\lib" "$(QTDIR)\lib\qtmain.lib" "$(QTDIR)\lib\QtXml4.lib" "$(QTDIR)\lib\QtGui4.lib" "$(QTDIR)\lib\QtNetwork4.lib" "$(QTDIR)\lib\QtCore4.lib" /out:"bin\dboxfe.exe" 

!ELSEIF  "$(CFG)" == "dboxfe - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "bin"
# PROP BASE Intermediate_Dir "win\obj"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "bin"
# PROP Intermediate_Dir "win\obj"
# PROP Target_Dir ""
# ADD CPP /I"$(QTDIR)/include/QtCore" /I"$(QTDIR)/include/QtNetwork" /I"$(QTDIR)/include/QtGui" /I"$(QTDIR)/include/QtXml" /I"$(QTDIR)/include" /I"include" /I"3rdparty" /I"$(QTDIR)/include/ActiveQt" /I"win\moc" /I"win\ui" /I"..\..\..\Lib\qt4\mkspecs\win32-msvc" /c /FD -nologo -Zm200 -Zi -MDd -Zi -MDd -W3 -GR -GX  /D "_WINDOWS"  /D UNICODE /D QT_LARGEFILE_SUPPORT /D QT_DLL /D QT_XML_LIB /D QT_GUI_LIB /D QT_NETWORK_LIB /D QT_CORE_LIB /D QT_THREAD_SUPPORT  /D "WIN32"   /D "QT_THREAD_SUPPORT" 
# ADD MTL /nologo /mktyplib203 /win32 /D "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
# ADD BSC32 /nologo
LINK32=link
# ADD LINK32 /NOLOGO /DEBUG /DEBUG /SUBSYSTEM:windows /LIBPATH:"$(QTDIR)\lib" "$(QTDIR)\lib\qtmaind.lib" "$(QTDIR)\lib\QtXmld4.lib" "$(QTDIR)\lib\QtGuid4.lib" "$(QTDIR)\lib\QtNetworkd4.lib" "$(QTDIR)\lib\QtCored4.lib" /out:"bin\dboxfe.exe" 

!ENDIF 

# Begin Target

# Name "dboxfe - Win32 Release"
# Name "dboxfe - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE=3rdparty\Base64.cpp
# End Source File

# Begin Source File
SOURCE=3rdparty\XMLPreferences.cpp
# End Source File

# Begin Source File
SOURCE=3rdparty\XMLWriter.cpp
# End Source File

# Begin Source File
SOURCE=src\dboxfe.cpp
# End Source File

# Begin Source File
SOURCE=src\dboxfe_about.cpp
# End Source File

# Begin Source File
SOURCE=src\dboxfe_base.cpp
# End Source File

# Begin Source File
SOURCE=src\dboxfe_gamefile.cpp
# End Source File

# Begin Source File
SOURCE=src\dboxfe_games.cpp
# End Source File

# Begin Source File
SOURCE=src\dboxfe_gamesettings.cpp
# End Source File

# Begin Source File
SOURCE=src\dboxfe_images.cpp
# End Source File

# Begin Source File
SOURCE=src\dboxfe_profile.cpp
# End Source File

# Begin Source File
SOURCE=src\dboxfe_profilewizard.cpp
# End Source File

# Begin Source File
SOURCE=src\dboxfe_splash.cpp
# End Source File

# Begin Source File
SOURCE=src\main.cpp
# End Source File

# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File
SOURCE=3rdparty\Base64.h
# End Source File

# Begin Source File
SOURCE=3rdparty\XMLPreferences.h
# End Source File

# Begin Source File
SOURCE=3rdparty\XMLWriter.h
# End Source File

# Begin Source File
SOURCE=include\dboxfe.h
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_include\dboxfe.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe.h
InputPath=include\dboxfe.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe.cpp
"win\moc\moc_dboxfe.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_include\dboxfe.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe.h
InputPath=include\dboxfe.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe.cpp
"win\moc\moc_dboxfe.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=include\dboxfe_about.h
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_include\dboxfe_about.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_about.h
InputPath=include\dboxfe_about.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_about.cpp
"win\moc\moc_dboxfe_about.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_include\dboxfe_about.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_about.h
InputPath=include\dboxfe_about.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_about.cpp
"win\moc\moc_dboxfe_about.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=include\dboxfe_base.h
# End Source File

# Begin Source File
SOURCE=include\dboxfe_gamefile.h
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_include\dboxfe_gamefile.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_gamefile.h
InputPath=include\dboxfe_gamefile.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_gamefile.cpp
"win\moc\moc_dboxfe_gamefile.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_include\dboxfe_gamefile.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_gamefile.h
InputPath=include\dboxfe_gamefile.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_gamefile.cpp
"win\moc\moc_dboxfe_gamefile.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=include\dboxfe_games.h
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_include\dboxfe_games.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_games.h
InputPath=include\dboxfe_games.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_games.cpp
"win\moc\moc_dboxfe_games.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_include\dboxfe_games.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_games.h
InputPath=include\dboxfe_games.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_games.cpp
"win\moc\moc_dboxfe_games.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=include\dboxfe_gamesettings.h
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_include\dboxfe_gamesettings.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_gamesettings.h
InputPath=include\dboxfe_gamesettings.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_gamesettings.cpp
"win\moc\moc_dboxfe_gamesettings.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_include\dboxfe_gamesettings.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_gamesettings.h
InputPath=include\dboxfe_gamesettings.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_gamesettings.cpp
"win\moc\moc_dboxfe_gamesettings.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=include\dboxfe_images.h
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_include\dboxfe_images.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_images.h
InputPath=include\dboxfe_images.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_images.cpp
"win\moc\moc_dboxfe_images.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_include\dboxfe_images.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_images.h
InputPath=include\dboxfe_images.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_images.cpp
"win\moc\moc_dboxfe_images.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=include\dboxfe_profile.h
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_include\dboxfe_profile.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_profile.h
InputPath=include\dboxfe_profile.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_profile.cpp
"win\moc\moc_dboxfe_profile.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_include\dboxfe_profile.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_profile.h
InputPath=include\dboxfe_profile.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_profile.cpp
"win\moc\moc_dboxfe_profile.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=include\dboxfe_profilewizard.h
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_include\dboxfe_profilewizard.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_profilewizard.h
InputPath=include\dboxfe_profilewizard.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_profilewizard.cpp
"win\moc\moc_dboxfe_profilewizard.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_include\dboxfe_profilewizard.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_profilewizard.h
InputPath=include\dboxfe_profilewizard.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_profilewizard.cpp
"win\moc\moc_dboxfe_profilewizard.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=include\dboxfe_splash.h
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_include\dboxfe_splash.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_splash.h
InputPath=include\dboxfe_splash.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_splash.cpp
"win\moc\moc_dboxfe_splash.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_include\dboxfe_splash.h=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MOC on include\dboxfe_splash.h
InputPath=include\dboxfe_splash.h
BuildCmds=  \
	$(QTDIR)\bin\moc.exe  -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I"$(QTDIR)/include/QtCore" -I"$(QTDIR)/include/QtNetwork" -I"$(QTDIR)/include/QtGui" -I"$(QTDIR)/include/QtXml" -I"$(QTDIR)/include" -I"include" -I"3rdparty" -I"$(QTDIR)/include/ActiveQt" -I"win\moc" -I"win\ui" -I"..\..\..\Lib\qt4\mkspecs\win32-msvc" -D_MSC_VER=1200 -DWIN32 $(InputPath) -o win\moc\moc_dboxfe_splash.cpp
"win\moc\moc_dboxfe_splash.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# End Group

# Begin Group "Form Files"
# PROP Default_Filter "ui"
# Begin Source File
SOURCE=ui\about.ui
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_ui\about.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\about.ui
InputPath=ui\about.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_about.h
"win\ui\ui_about.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_ui\about.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\about.ui
InputPath=ui\about.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_about.h
"win\ui\ui_about.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=ui\dboxfe.ui
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_ui\dboxfe.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\dboxfe.ui
InputPath=ui\dboxfe.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_dboxfe.h
"win\ui\ui_dboxfe.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_ui\dboxfe.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\dboxfe.ui
InputPath=ui\dboxfe.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_dboxfe.h
"win\ui\ui_dboxfe.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=ui\gamefile.ui
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_ui\gamefile.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\gamefile.ui
InputPath=ui\gamefile.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_gamefile.h
"win\ui\ui_gamefile.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_ui\gamefile.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\gamefile.ui
InputPath=ui\gamefile.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_gamefile.h
"win\ui\ui_gamefile.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=ui\gamepreview.ui
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_ui\gamepreview.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\gamepreview.ui
InputPath=ui\gamepreview.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_gamepreview.h
"win\ui\ui_gamepreview.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_ui\gamepreview.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\gamepreview.ui
InputPath=ui\gamepreview.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_gamepreview.h
"win\ui\ui_gamepreview.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=ui\games.ui
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_ui\games.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\games.ui
InputPath=ui\games.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_games.h
"win\ui\ui_games.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_ui\games.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\games.ui
InputPath=ui\games.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_games.h
"win\ui\ui_games.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=ui\gamesettings.ui
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_ui\gamesettings.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\gamesettings.ui
InputPath=ui\gamesettings.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_gamesettings.h
"win\ui\ui_gamesettings.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_ui\gamesettings.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\gamesettings.ui
InputPath=ui\gamesettings.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_gamesettings.h
"win\ui\ui_gamesettings.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=ui\images.ui
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_ui\images.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\images.ui
InputPath=ui\images.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_images.h
"win\ui\ui_images.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_ui\images.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\images.ui
InputPath=ui\images.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_images.h
"win\ui\ui_images.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=ui\profile.ui
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_ui\profile.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\profile.ui
InputPath=ui\profile.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_profile.h
"win\ui\ui_profile.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_ui\profile.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\profile.ui
InputPath=ui\profile.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_profile.h
"win\ui\ui_profile.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# Begin Source File
SOURCE=ui\profilewizard.ui
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_ui\profilewizard.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\profilewizard.ui
InputPath=ui\profilewizard.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_profilewizard.h
"win\ui\ui_profilewizard.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_ui\profilewizard.ui=
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running UIC on ui\profilewizard.ui
InputPath=ui\profilewizard.ui
BuildCmds=  \
	$(QTDIR)\bin\uic.exe $(InputPath) -o win\ui\ui_profilewizard.h
"win\ui\ui_profilewizard.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# End Group

# Begin Group "Resources"
# PROP Default_Filter "rc;qrc"
# Begin Source File
SOURCE=res\dboxfe.qrc
!IF "$(CFG)" == "dboxfe - Win32 Release"

USERDEP_res\dboxfe.qrc="$(QTDIR)\bin\rcc.exe"
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running RCC on res\dboxfe.qrc
InputPath=res\dboxfe.qrc
BuildCmds=  \
	$(QTDIR)\bin\rcc.exe -name dboxfe $(InputPath) -o win\rcc\qrc_dboxfe.cpp
"win\rcc\qrc_dboxfe.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ELSEIF "$(CFG)" == "dboxfe - Win32 Debug"

USERDEP_res\dboxfe.qrc="$(QTDIR)\bin\rcc.exe"
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running RCC on res\dboxfe.qrc
InputPath=res\dboxfe.qrc
BuildCmds=  \
	$(QTDIR)\bin\rcc.exe -name dboxfe $(InputPath) -o win\rcc\qrc_dboxfe.cpp
"win\rcc\qrc_dboxfe.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(BuildCmds)

# End Custom Build

!ENDIF
# End Source File

# End Group

# Begin Group "Translations"
# PROP Default_Filter "ts"
# Begin Source File
SOURCE=lng\dboxfe_de.ts
# End Source File

# Begin Source File
SOURCE=lng\dboxfe_en.ts
# End Source File

# End Group

# Begin Group "Generated"
# PROP Default_Filter ""
# Begin Source File
SOURCE=win\moc\moc_dboxfe.cpp
# End Source File

# Begin Source File
SOURCE=win\moc\moc_dboxfe_about.cpp
# End Source File

# Begin Source File
SOURCE=win\moc\moc_dboxfe_gamefile.cpp
# End Source File

# Begin Source File
SOURCE=win\moc\moc_dboxfe_games.cpp
# End Source File

# Begin Source File
SOURCE=win\moc\moc_dboxfe_gamesettings.cpp
# End Source File

# Begin Source File
SOURCE=win\moc\moc_dboxfe_images.cpp
# End Source File

# Begin Source File
SOURCE=win\moc\moc_dboxfe_profile.cpp
# End Source File

# Begin Source File
SOURCE=win\moc\moc_dboxfe_profilewizard.cpp
# End Source File

# Begin Source File
SOURCE=win\moc\moc_dboxfe_splash.cpp
# End Source File

# Begin Source File
SOURCE=win\rcc\qrc_dboxfe.cpp
# End Source File

# Begin Source File
SOURCE=win\ui\ui_about.h
# End Source File

# Begin Source File
SOURCE=win\ui\ui_dboxfe.h
# End Source File

# Begin Source File
SOURCE=win\ui\ui_gamefile.h
# End Source File

# Begin Source File
SOURCE=win\ui\ui_gamepreview.h
# End Source File

# Begin Source File
SOURCE=win\ui\ui_games.h
# End Source File

# Begin Source File
SOURCE=win\ui\ui_gamesettings.h
# End Source File

# Begin Source File
SOURCE=win\ui\ui_images.h
# End Source File

# Begin Source File
SOURCE=win\ui\ui_profile.h
# End Source File

# Begin Source File
SOURCE=win\ui\ui_profilewizard.h
# End Source File

# End Group


# End Target
# End Project
