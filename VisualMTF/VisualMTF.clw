; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VisualMTF.h"
LastPage=0

ClassCount=22
Class1=CVisualMTFApp
Class2=CVisualMTFDoc
Class3=CVisualMTFView
Class4=CMainFrame

ResourceCount=14
Resource1=IDD_DIALOG4
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class6=CParaSet
Class7=CFreqSet
Resource4=IDD_DIALOG2
Resource5=IDD_DIALOG1
Class8=LeftFormView
Class9=RightTextView
Class10=RightListView
Resource6=IDD_DIALOG9
Class11=RightMTFView
Resource7=IDD_DIALOG3
Class12=RightLSFView
Class13=CBackgroundWnd
Resource8=IDD_DIALOG8
Resource9=IDR_MENU1
Class14=CStageSet
Resource10=IDD_DIALOG7
Class15=CScanImage
Resource11=IDD_DIALOG10
Class16=CRealTimeFrame
Class17=CRealTimeUp
Class18=CRealTimeDown
Resource12=IDD_DIALOG5
Class19=CThroughFocusFrame
Class20=CThroughFocusLeft
Class21=CThroughFocusRight
Resource13=IDD_DIALOG6
Class22=CFOI
Resource14=IDD_DIALOG11

[CLS:CVisualMTFApp]
Type=0
HeaderFile=VisualMTF.h
ImplementationFile=VisualMTF.cpp
Filter=N
LastObject=CVisualMTFApp

[CLS:CVisualMTFDoc]
Type=0
HeaderFile=VisualMTFDoc.h
ImplementationFile=VisualMTFDoc.cpp
Filter=N
LastObject=CVisualMTFDoc

[CLS:CVisualMTFView]
Type=0
HeaderFile=VisualMTFView.h
ImplementationFile=VisualMTFView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_MENUITEM_PRINT


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_CONF_PARASET
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=VisualMTF.cpp
ImplementationFile=VisualMTF.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN_MENU
Command2=ID_FILE_SAVE_MENU
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_APP_EXIT
Command6=ID_CONF_PARASET
Command7=ID_CONF_FREQSET
Command8=ID_CONF_STAGE
Command9=IDD_OPER_REALTIME
Command10=ID_OPER_THROUGH
Command11=ID_OPER_STARIMAGE
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_DIALOG1]
Type=1
Class=CParaSet
ControlCount=22
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350639744
Control6=IDC_STATIC,button,1342177287
Control7=IDC_EDIT2,edit,1350639744
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT3,edit,1350639744
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT4,edit,1350639744
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EDIT5,edit,1350639744
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT6,edit,1350639744
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT7,edit,1350631552
Control22=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOG2]
Type=1
Class=CFreqSet
ControlCount=23
Control1=IDCANCEL,button,1342242816
Control2=IDC_FreqEDIT1,edit,1350631552
Control3=IDC_FreqEDIT2,edit,1350631552
Control4=IDC_FreqEDIT3,edit,1350631552
Control5=IDC_FreqEDIT4,edit,1350631552
Control6=IDC_FreqEDIT5,edit,1350631552
Control7=IDC_FreqEDIT6,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308353
Control10=IDC_STATIC,static,1342308353
Control11=IDC_MTFtEDIT1,edit,1350641792
Control12=IDC_MTFtEDIT2,edit,1350641792
Control13=IDC_MTFtEDIT3,edit,1350641792
Control14=IDC_MTFtEDIT4,edit,1350641792
Control15=IDC_MTFtEDIT5,edit,1350641792
Control16=IDC_MTFtEDIT6,edit,1350641792
Control17=IDC_MTFsEDIT1,edit,1350641792
Control18=IDC_MTFsEDIT2,edit,1350641792
Control19=IDC_MTFsEDIT3,edit,1350641792
Control20=IDC_MTFsEDIT4,edit,1350641792
Control21=IDC_MTFsEDIT5,edit,1350641792
Control22=IDC_MTFsEDIT6,edit,1350641792
Control23=IDC_BUTTONUpdate,button,1342242816

[CLS:CParaSet]
Type=0
HeaderFile=ParaSet.h
ImplementationFile=ParaSet.cpp
BaseClass=CDialog
Filter=D
LastObject=CParaSet
VirtualFilter=dWC

[CLS:CFreqSet]
Type=0
HeaderFile=FreqSet.h
ImplementationFile=FreqSet.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTONUpdate
VirtualFilter=dWC

[DLG:IDD_DIALOG3]
Type=1
Class=LeftFormView
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_COMBO1,combobox,1344339971
Control3=IDC_STATIC,button,1342177287
Control4=IDC_CHECK1,button,1342242819
Control5=IDC_CHECK2,button,1342242819
Control6=IDC_CHECK3,button,1342242819
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT1,edit,1350639746
Control9=IDC_BUTTON1,button,1342242816

[DLG:IDD_DIALOG4]
Type=1
Class=RightTextView
ControlCount=15
Control1=IDC_STATIC,static,1342308865
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1342244992
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT2,edit,1342244992
Control11=IDC_EDIT3,edit,1342244992
Control12=IDC_EDIT4,edit,1342244992
Control13=IDC_EDIT5,edit,1342244992
Control14=IDC_EDIT6,edit,1342244992
Control15=IDC_EDIT7,edit,1342244992

[CLS:LeftFormView]
Type=0
HeaderFile=LeftFormView.h
ImplementationFile=LeftFormView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=IDC_CHECK3

[CLS:RightTextView]
Type=0
HeaderFile=RightTextView.h
ImplementationFile=RightTextView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC

[CLS:RightListView]
Type=0
HeaderFile=RightListView.h
ImplementationFile=RightListView.cpp
BaseClass=CListView
Filter=C
LastObject=ID_APP_ABOUT

[DLG:IDD_DIALOG5]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308865

[CLS:RightMTFView]
Type=0
HeaderFile=RightMTFView.h
ImplementationFile=RightMTFView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC

[DLG:IDD_DIALOG6]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308865

[CLS:RightLSFView]
Type=0
HeaderFile=RightLSFView.h
ImplementationFile=RightLSFView.cpp
BaseClass=CView
Filter=C
LastObject=ID_APP_ABOUT

[CLS:CBackgroundWnd]
Type=0
HeaderFile=BackgroundWnd.h
ImplementationFile=BackgroundWnd.cpp
BaseClass=CFrameWnd
Filter=T
VirtualFilter=fWC
LastObject=CBackgroundWnd

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_MENUITEM_SAVE
Command2=ID_MENUITEM_PRINT
Command3=ID_MENUITEM_PRINTPREVIEW
Command4=ID_MENU_CONF_PARASET
Command5=ID_MENU_FREQ_PARASET
CommandCount=5

[DLG:IDD_DIALOG7]
Type=1
Class=CStageSet
ControlCount=21
Control1=IDC_STATIC,button,1342177287
Control2=IDC_LIST1,listbox,1352728835
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_EDIT3,edit,1350631552
Control6=IDC_EDIT4,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT5,edit,1350631552
Control14=IDC_BUTTON1,button,1342242816
Control15=IDC_BUTTON2,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_SCROLLBAR1,scrollbar,1342177280
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_CHECK1,button,1342242819
Control21=IDC_BUTTON3,button,1342242816

[CLS:CStageSet]
Type=0
HeaderFile=StageSet.h
ImplementationFile=StageSet.cpp
BaseClass=CDialog
Filter=D
LastObject=CStageSet
VirtualFilter=dWC

[DLG:IDD_DIALOG8]
Type=1
Class=CScanImage
ControlCount=18
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308353
Control3=IDC_STATIC,static,1342308353
Control4=IDC_COMBO1,combobox,1344339971
Control5=IDC_COMBO2,combobox,1344339971
Control6=IDC_STATIC,static,1342308353
Control7=IDC_STATIC,static,1342308353
Control8=IDC_STATIC,button,1342177287
Control9=IDC_EDIT1,edit,1350631552
Control10=IDC_EDIT2,edit,1350631552
Control11=IDC_STATIC,static,1342308353
Control12=IDC_STATIC,static,1342308353
Control13=IDC_STATIC,static,1342308353
Control14=IDC_STATIC,static,1342308353
Control15=IDC_BUTTON1,button,1342242816
Control16=IDC_BUTTON2,button,1342242816
Control17=IDC_IMAGE,static,1342177284
Control18=IDC_BUTTON3,button,1073807360

[CLS:CScanImage]
Type=0
HeaderFile=ScanImage.h
ImplementationFile=ScanImage.cpp
BaseClass=CDialog
Filter=D
LastObject=CScanImage
VirtualFilter=dWC

[DLG:IDD_DIALOG9]
Type=1
Class=CRealTimeUp
ControlCount=10
Control1=IDC_EDIT1,edit,1350631553
Control2=IDC_STATIC,button,1342177287
Control3=IDC_SCROLLBAR1,scrollbar,1342177280
Control4=IDC_STATIC,button,1342177287
Control5=IDC_BUTTON1,button,1342242816
Control6=IDC_BUTTON2,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_CHECK1,button,1342242819
Control9=IDC_BUTTON3,button,1342242816
Control10=IDC_BUTTON4,button,1342242816

[CLS:CRealTimeFrame]
Type=0
HeaderFile=RealTimeFrame.h
ImplementationFile=RealTimeFrame.cpp
BaseClass=CFrameWnd
Filter=T
LastObject=CRealTimeFrame
VirtualFilter=fWC

[CLS:CRealTimeUp]
Type=0
HeaderFile=RealTimeUp.h
ImplementationFile=RealTimeUp.cpp
BaseClass=CFormView
Filter=D
LastObject=IDC_BUTTON4
VirtualFilter=VWC

[CLS:CRealTimeDown]
Type=0
HeaderFile=RealTimeDown.h
ImplementationFile=RealTimeDown.cpp
BaseClass=CView
Filter=C
LastObject=CRealTimeDown
VirtualFilter=VWC

[DLG:IDD_DIALOG10]
Type=1
Class=CThroughFocusLeft
ControlCount=15
Control1=IDC_STATIC,button,1342177287
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308353
Control6=IDC_STATIC,static,1342308353
Control7=IDC_STATIC,static,1342308353
Control8=IDC_STATIC,static,1342308353
Control9=IDC_STATIC,static,1342308353
Control10=IDC_STATIC,static,1342308353
Control11=IDC_EDIT1,edit,1350631553
Control12=IDC_EDIT2,edit,1350631553
Control13=IDC_COMBO1,combobox,1344339971
Control14=IDC_CHECK1,button,1342242819
Control15=IDC_BUTTON3,button,1342242816

[CLS:CThroughFocusFrame]
Type=0
HeaderFile=ThroughFocusFrame.h
ImplementationFile=ThroughFocusFrame.cpp
BaseClass=CFrameWnd
Filter=T
VirtualFilter=fWC
LastObject=CThroughFocusFrame

[CLS:CThroughFocusLeft]
Type=0
HeaderFile=ThroughFocusLeft.h
ImplementationFile=ThroughFocusLeft.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=CThroughFocusLeft

[CLS:CThroughFocusRight]
Type=0
HeaderFile=ThroughFocusRight.h
ImplementationFile=ThroughFocusRight.cpp
BaseClass=CView
Filter=C
LastObject=CThroughFocusRight
VirtualFilter=VWC

[DLG:IDD_DIALOG11]
Type=1
Class=CFOI
ControlCount=23
Control1=IDCANCEL,button,1342242816
Control2=IDC_FreqEDIT1,edit,1350631552
Control3=IDC_FreqEDIT2,edit,1350631552
Control4=IDC_FreqEDIT3,edit,1350631552
Control5=IDC_FreqEDIT4,edit,1350631552
Control6=IDC_FreqEDIT5,edit,1350631552
Control7=IDC_FreqEDIT6,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308353
Control10=IDC_STATIC,static,1342308353
Control11=IDC_MTFtEDIT1,edit,1350641792
Control12=IDC_MTFtEDIT2,edit,1350641792
Control13=IDC_MTFtEDIT3,edit,1350641792
Control14=IDC_MTFtEDIT4,edit,1350641792
Control15=IDC_MTFtEDIT5,edit,1350641792
Control16=IDC_MTFtEDIT6,edit,1350641792
Control17=IDC_MTFsEDIT1,edit,1350641792
Control18=IDC_MTFsEDIT2,edit,1350641792
Control19=IDC_MTFsEDIT3,edit,1350641792
Control20=IDC_MTFsEDIT4,edit,1350641792
Control21=IDC_MTFsEDIT5,edit,1350641792
Control22=IDC_MTFsEDIT6,edit,1350641792
Control23=IDC_REFRESH,button,1342242816

[CLS:CFOI]
Type=0
HeaderFile=FOI.h
ImplementationFile=FOI.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_REFRESH
VirtualFilter=dWC

