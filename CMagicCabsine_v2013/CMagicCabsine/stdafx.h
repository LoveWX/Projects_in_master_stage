
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

#include <string>
using namespace std;

//定义图片类型
enum IMAGE_TYPE {	IMAGE_HUMAN,
					IMAGE_SCENERY,
					IMAGE_ANIMAL,
					IMAGE_CUSTOM};

//定义画布类型
enum CLOTH_TYPE {	CLOTH_TYPE1,
					CLOTH_TYPE2		};

//定义绣线类型
enum THREAD_TYPE {	THREAD_TYPE1,
					THREAD_TYPE2	};

//定义流程步骤
//定义流程步骤
enum PROCESS_TYPE {	PROCESS_START,
					PROCESS_UNIVERSALCALCED,
					PROCESS_SPLIT_MARKDOWN = 10,
					PROCESS_SPLITED,
					PROCESS_LEFTDONE,
					PROCESS_SIMULATED,
					PROCESS_SIMULATEDONE,
					PROCESS_DONE	};

//定义标签类型
enum TABVIEW_TYPE { TABTYPE_SRCIMAGE,
					TABTYPE_UNIVERSAL,
					TABTYPE_SPLIT,
					TABTYPE_SPLIT_RES,
					TABTYPE_PORTION,
					TABTYPE_SIMU_ALL,
					TABTYPE_SIMU_LEVEL};

//定义分割方法类型
enum SPLIT_METHOD_TYPE{ SPLIT_MARK_NONE,
						SPLIT_MARK_GROUND,
						SPLIT_MARK_SURROUND};

//定义分割方法名称
enum SPLIT_METHOD_NAME{	SPLIT_MEANSHIFT = 1,
						SPLIT_GRAPHBASE = 2};

//定义针法类型
enum STITCH_TYPE {	STITCH_ChaosVerticalCross,		//大乱针竖交叉
					STITCH_ChaosHorizontalCross,	//大乱针横交叉
					STITCH_ChaosVectorFieldCross,	//大乱针矢量场交叉
					STITCH_OrderlessCross,			//小乱针
					STITCH_Other};					//其它针法

//定义视图显示类型
enum SHOW_VIEW_TYPE{LEFT_SHOW,
					RIGHT_SHOW,
					BOTH_SHOW};

const double pi=3.1415926535897932384626433832795;

//static string theApp.GetDefaultPath();//默认路径,为当前工程所在文件夹,在CMagicCabsineDoc的构造函数中初始化


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include "CMagicCabsine.h"

