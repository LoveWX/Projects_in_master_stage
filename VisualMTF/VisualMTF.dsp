# Microsoft Developer Studio Project File - Name="VisualMTF" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VisualMTF - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VisualMTF.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VisualMTF.mak" CFG="VisualMTF - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VisualMTF - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VisualMTF - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VisualMTF - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "VisualMTF - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "VisualMTF - Win32 Release"
# Name "VisualMTF - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BackgroundWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\FOI.cpp
# End Source File
# Begin Source File

SOURCE=.\FreqSet.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ParaSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RealTimeDown.cpp
# End Source File
# Begin Source File

SOURCE=.\RealTimeFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\RealTimeUp.cpp
# End Source File
# Begin Source File

SOURCE=.\RightListView.cpp
# End Source File
# Begin Source File

SOURCE=.\RightLSFView.cpp
# End Source File
# Begin Source File

SOURCE=.\RightMTFView.cpp
# End Source File
# Begin Source File

SOURCE=.\RightTextView.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanImage.cpp
# End Source File
# Begin Source File

SOURCE=.\StageSet.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ThroughFocusFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ThroughFocusLeft.cpp
# End Source File
# Begin Source File

SOURCE=.\ThroughFocusRight.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualMTF.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualMTF.rc
# End Source File
# Begin Source File

SOURCE=.\VisualMTFDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualMTFView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BackgroundWnd.h
# End Source File
# Begin Source File

SOURCE=.\FOI.h
# End Source File
# Begin Source File

SOURCE=.\FreqSet.h
# End Source File
# Begin Source File

SOURCE=.\LeftFormView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ParaSet.h
# End Source File
# Begin Source File

SOURCE=.\RealTimeDown.h
# End Source File
# Begin Source File

SOURCE=.\RealTimeFrame.h
# End Source File
# Begin Source File

SOURCE=.\RealTimeUp.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RightListView.h
# End Source File
# Begin Source File

SOURCE=.\RightLSFView.h
# End Source File
# Begin Source File

SOURCE=.\RightMTFView.h
# End Source File
# Begin Source File

SOURCE=.\RightTextView.h
# End Source File
# Begin Source File

SOURCE=.\ScanImage.h
# End Source File
# Begin Source File

SOURCE=.\StageSet.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ThroughFocusFrame.h
# End Source File
# Begin Source File

SOURCE=.\ThroughFocusLeft.h
# End Source File
# Begin Source File

SOURCE=.\ThroughFocusRight.h
# End Source File
# Begin Source File

SOURCE=.\VisualMTF.h
# End Source File
# Begin Source File

SOURCE=.\VisualMTFDoc.h
# End Source File
# Begin Source File

SOURCE=.\VisualMTFView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\VisualMTF.ico
# End Source File
# Begin Source File

SOURCE=.\res\VisualMTF.rc2
# End Source File
# Begin Source File

SOURCE=.\res\VisualMTFDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\DMCMLIB.dll
# End Source File
# Begin Source File

SOURCE=.\okacap.dll
# End Source File
# Begin Source File

SOURCE=.\OKAPI32.dll
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\OKAPI32.lib
# End Source File
# Begin Source File

SOURCE=.\DMC32M.LIB
# End Source File
# End Target
# End Project
