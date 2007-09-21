;/*
; *   Copyright (C) ©'2004-2007 by Alexander Saal <alex.saal@gmx.de>
; *
; *   This program is free software; you can redistribute it and/or modify
; *   it under the terms of the GNU General Public License as published by
; *   the Free Software Foundation; either version 2 of the License, or (at
; *   your option) any later version.
; *
; *   This program is distributed in the hope that it will be useful, but
; *   WITHOUT ANY WARRANTY; without even the implied warranty of
; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; *   GNU General Public License for more details.
; *
; *   You should have received a copy of the GNU General Public License
; *   along with this program; if not, write to the Free Software Foundation,
; *   Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
; */

#define MyAppName "DBoxFE - DOSBox Frontend"
#define MyAppNameTray "DBoxFE - DOSBox Frontend (TrayIcon)"
#define MyAppVerName "DBoxFE - DOSBox Frontend v0.1.3.0"
#define MyAppVersion "0.1.3.0"
#define MyAppPublisher "Privat - Alexander Saal"
#define MyAppURL "http://chmaster.freeforge.net"
#define MyAppCopyright "(C)opyright ©'2004-2007 by Alexander Saal"
#define MyAppExeName "dboxfe.exe"
#define MyAppExeNameTray "dboxfetray.exe"
#define MyAppUrlName "dboxfe.url"

[Setup]
AppName={#MyAppName}
AppVerName={#MyAppVerName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}

DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}

VersionInfoVersion={#MyAppVersion}
VersionInfoCopyright={#MyAppCopyright}
VersionInfoCompany={#MyAppPublisher}

AllowNoIcons=true
LicenseFile=res\LICENSE.GPL
OutputDir=.
OutputBaseFilename=dboxfe-{#MyAppVersion}-setup-win32
SetupIconFile=res\dboxfe.ico
Compression=lzma
SolidCompression=true
InternalCompressLevel=max
MinVersion=4.1.2222,5.0.2195sp3
AppID={{0F40AF50-E524-4B61-9772-CFAA42C0672A}
UninstallDisplayIcon={app}\dboxfe.exe
DisableFinishedPage=false
UninstallDisplayName={#MyAppVersion}-{#MyAppName}
AllowRootDirectory=true
UninstallLogMode=new
DisableStartupPrompt=true
WizardImageFile=compiler:WizModernImage-IS.bmp
WizardSmallImageFile=compiler:WizModernSmallImage-IS.bmp
ShowLanguageDialog=yes

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}; MinVersion: 4.1.2222,4.0.1381sp6
Name: quicklaunchicon; Description: {cm:CreateQuickLaunchIcon}; GroupDescription: {cm:AdditionalIcons}; MinVersion: 4.1.2222,4.0.1381sp6

[Files]
;Source: bin\dboxfe-debug.exe; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
;Source: bin\dboxfe-tray-debug.exe; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6

Source: bin\dboxfe.exe; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
Source: bin\dboxfetray.exe; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
Source: res\dboxfe.ico; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
Source: res\LICENSE.GPL; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6

; Needed library (Qt4 Release):
Source: ..\..\..\Lib\qt43\bin\QtGui4.dll; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
Source: ..\..\..\Lib\qt43\bin\QtCore4.dll; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
Source: ..\..\..\Lib\qt43\bin\QtNetwork4.dll; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
Source: ..\..\..\Lib\qt43\bin\QtXml4.dll; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6

; Needed library (Qt4 Debug):
;Source: ..\..\..\Lib\qt43\bin\QtGuid4.dll; DestDir: {app}\library; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
;Source: ..\..\..\Lib\qt43\bin\QtCored4.dll; DestDir: {app}\library; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
;Source: ..\..\..\Lib\qt43\bin\QtNetworkd4.dll; DestDir: {app}\library; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
;Source: ..\..\..\Lib\qt43\bin\QtXmld4.dll; DestDir: {app}\library; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6

; Needed library (MS VC++ 2005 Release)
Source: ..\..\msvc\msvcm80.dll; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
Source: ..\..\msvc\msvcr80.dll; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
Source: ..\..\msvc\msvcp80.dll; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
Source: ..\..\msvc\Microsoft.VC80.CRT.manifest; DestDir: {app}; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6

; Needed library (MS VC++ 2005 Debug)
;Source: ..\..\msvc\msvcm80d.dll; DestDir: {app}\library; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
;Source: ..\..\msvc\msvcr80d.dll; DestDir: {app}\library; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
;Source: ..\..\msvc\msvcp80d.dll; DestDir: {app}\library; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
;Source: ..\..\msvc\msvcm80d.i386.pdb; DestDir: {app}\library; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
;Source: ..\..\msvc\msvcr80d.i386.pdb; DestDir: {app}\library; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6
;Source: ..\..\msvc\msvcp80d.i386.pdb; DestDir: {app}\library; Flags: ignoreversion uninsremovereadonly 32bit overwritereadonly replacesameversion; MinVersion: 4.1.2222,4.0.1381sp6

[INI]
Filename: {app}\{#MyAppUrlName}; Section: InternetShortcut; Key: URL; String: {#MyAppURL}; Flags: createkeyifdoesntexist; MinVersion: 4.1.2222,4.0.1381sp6

[Icons]
Name: {group}\{#MyAppName}; Filename: {app}\{#MyAppExeName}
Name: {group}\{#MyAppNameTray}; Filename: {app}\{#MyAppExeNameTray}
Name: {group}\{cm:ProgramOnTheWeb,{#MyAppName}}; Filename: {app}\{#MyAppUrlName}
Name: {group}\{cm:UninstallProgram,{#MyAppName}}; Filename: {uninstallexe}
Name: {userdesktop}\{#MyAppName}; Filename: {app}\{#MyAppExeName}; Tasks: desktopicon
Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}; Filename: {app}\{#MyAppExeName}; Tasks: quicklaunchicon

[Run]
Filename: {app}\{#MyAppExeName}; Description: {cm:LaunchProgram,{#MyAppName}}; Flags: postinstall skipifsilent; MinVersion: 4.1.2222,4.0.1381sp6; WorkingDir: {app}

[UninstallDelete]
Type: files; Name: {app}\{#MyAppUrlName}

[Messages]
BeveledLabel={#MyAppCopyright}
