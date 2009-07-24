# Microsoft Developer Studio Project File - Name="auriga_sql" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=auriga_sql - Win32 Debug
!MESSAGE これは有効なメイクファイルではありません。 このプロジェクトをビルドするためには NMAKE を使用してください。
!MESSAGE [メイクファイルのエクスポート] コマンドを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "auriga_sql.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE コマンド ライン上でマクロの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "auriga_sql.mak" CFG="auriga_sql - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なビルド モード:
!MESSAGE 
!MESSAGE "auriga_sql - Win32 Release" ("Win32 (x86) Console Application" 用)
!MESSAGE "auriga_sql - Win32 Debug" ("Win32 (x86) Console Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "auriga_sql - Win32 Release"

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
# ADD CPP /nologo /W3 /Gi /GX /O2 /D PACKETVER=15 /D "NEW_006b" /D FD_SETSIZE=4096 /D "_CRT_SECURE_NO_DEPRECATE" /D "WINDOWS" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "NO_HTTPD_CGI" /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib /nologo /subsystem:console /incremental:yes /map:"../../auriga_sql.map" /machine:I386

!ELSEIF  "$(CFG)" == "auriga_sql - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /Gi /GX /ZI /Od /D PACKETVER=15 /D "NEW_006b" /D FD_SETSIZE=4096 /D "_CRT_SECURE_NO_DEPRECATE" /D "WINDOWS" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "NO_HTTPD_CGI" /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib /nologo /subsystem:console /map:"../../auriga_sql.map" /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "auriga_sql - Win32 Release"
# Name "auriga_sql - Win32 Debug"
# End Target
# End Project
