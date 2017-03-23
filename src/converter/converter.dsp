# Microsoft Developer Studio Project File - Name="converter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=converter - Win32 Debug
!MESSAGE これは有効なメイクファイルではありません。 このプロジェクトをビルドするためには NMAKE を使用してください。
!MESSAGE [メイクファイルのエクスポート] コマンドを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "converter.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE コマンド ライン上でマクロの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "converter.mak" CFG="converter - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なビルド モード:
!MESSAGE 
!MESSAGE "converter - Win32 Release" ("Win32 (x86) Console Application" 用)
!MESSAGE "converter - Win32 Debug" ("Win32 (x86) Console Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "converter - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WINDOWS" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gi /GX /O2 /I "../common/" /D PACKETVER=20120925 /D "NEW_006b" /D FD_SETSIZE=4096 /D "_CRT_SECURE_NO_DEPRECATE" /D "WINDOWS" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "NO_HTTPD" /D "NO_HTTPD_CGI" /D "PRE_RENEWAL" /D "DYNAMIC_SC_DATA" /FD /c /wd4819
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib /nologo /subsystem:console /incremental:yes /map:"../../txt-converter.map" /machine:I386 /out:"../../txt-converter.exe"

!ELSEIF  "$(CFG)" == "converter - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WINDOWS" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /Gi /GX /ZI /Od /I "../common/" /D PACKETVER=20120925 /D "NEW_006b" /D FD_SETSIZE=4096 /D "_CRT_SECURE_NO_DEPRECATE" /D "WINDOWS" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "NO_HTTPD" /D "NO_HTTPD_CGI" /D "PRE_RENEWAL" /D "DYNAMIC_SC_DATA" /FD /GZ /c /wd4819
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib /nologo /subsystem:console /map:"../../txt-converter.map" /debug /machine:I386 /out:"../../txt-converter.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "converter - Win32 Release"
# Name "converter - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\char-converter.c"
# End Source File
# Begin Source File

SOURCE=.\converter.c
# End Source File
# Begin Source File

SOURCE=..\common\core.c
# End Source File
# Begin Source File

SOURCE=..\common\db.c
# End Source File
# Begin Source File

SOURCE=..\common\httpd.c
# End Source File
# Begin Source File

SOURCE=".\inter-converter.c"
# End Source File
# Begin Source File

SOURCE="..\common\lock.c"
# End Source File
# Begin Source File

SOURCE=".\login-converter.c"
# End Source File
# Begin Source File

SOURCE=..\common\malloc.c
# End Source File
# Begin Source File

SOURCE=..\common\md5calc.c
# End Source File
# Begin Source File

SOURCE=.\map-converter.c
# End Source File
# Begin Source File

SOURCE=..\common\socket.c
# End Source File
# Begin Source File

SOURCE=..\common\timer.c
# End Source File
# Begin Source File

SOURCE=..\common\version.c
# End Source File
# Begin Source File

SOURCE=..\common\utils.c
# End Source File
# Begin Source File

SOURCE=..\common\sqldbs.c
# End Source File
# Begin Source File

SOURCE=..\common\winservice.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=".\char-converter.h"
# End Source File
# Begin Source File

SOURCE=.\converter.h
# End Source File
# Begin Source File

SOURCE=..\common\core.h
# End Source File
# Begin Source File

SOURCE=..\common\db.h
# End Source File
# Begin Source File

SOURCE=".\inter-converter.h"
# End Source File
# Begin Source File

SOURCE="..\common\lock.h"
# End Source File
# Begin Source File

SOURCE=".\login-converter.h"
# End Source File
# Begin Source File

SOURCE=..\common\malloc.h
# End Source File
# Begin Source File

SOURCE=".\map-converter.h"
# End Source File
# Begin Source File

SOURCE=..\common\md5calc.h
# End Source File
# Begin Source File

SOURCE=..\common\mmo.h
# End Source File
# Begin Source File

SOURCE=..\common\socket.h
# End Source File
# Begin Source File

SOURCE="..\common\timer.h"
# End Source File
# Begin Source File

SOURCE="..\common\utils.h"
# End Source File
# Begin Source File

SOURCE="..\common\sqldbs.h"
# End Source File
# Begin Source File

SOURCE="..\common\winservice.h"
# End Source File
# End Group
# End Target
# End Project
