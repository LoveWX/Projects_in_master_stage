
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include <string>
using namespace std;

//����ͼƬ����
enum IMAGE_TYPE {	IMAGE_HUMAN,
					IMAGE_SCENERY,
					IMAGE_ANIMAL,
					IMAGE_CUSTOM};

//���廭������
enum CLOTH_TYPE {	CLOTH_TYPE1,
					CLOTH_TYPE2		};

//������������
enum THREAD_TYPE {	THREAD_TYPE1,
					THREAD_TYPE2	};

//�������̲���
//�������̲���
enum PROCESS_TYPE {	PROCESS_START,
					PROCESS_UNIVERSALCALCED,
					PROCESS_SPLIT_MARKDOWN = 10,
					PROCESS_SPLITED,
					PROCESS_LEFTDONE,
					PROCESS_SIMULATED,
					PROCESS_SIMULATEDONE,
					PROCESS_DONE	};

//�����ǩ����
enum TABVIEW_TYPE { TABTYPE_SRCIMAGE,
					TABTYPE_UNIVERSAL,
					TABTYPE_SPLIT,
					TABTYPE_SPLIT_RES,
					TABTYPE_PORTION,
					TABTYPE_SIMU_ALL,
					TABTYPE_SIMU_LEVEL};

//����ָ������
enum SPLIT_METHOD_TYPE{ SPLIT_MARK_NONE,
						SPLIT_MARK_GROUND,
						SPLIT_MARK_SURROUND};

//����ָ������
enum SPLIT_METHOD_NAME{	SPLIT_MEANSHIFT = 1,
						SPLIT_GRAPHBASE = 2};

//�����뷨����
enum STITCH_TYPE {	STITCH_ChaosVerticalCross,		//������������
					STITCH_ChaosHorizontalCross,	//������ύ��
					STITCH_ChaosVectorFieldCross,	//������ʸ��������
					STITCH_OrderlessCross,			//С����
					STITCH_Other};					//�����뷨

//������ͼ��ʾ����
enum SHOW_VIEW_TYPE{LEFT_SHOW,
					RIGHT_SHOW,
					BOTH_SHOW};

const double pi=3.1415926535897932384626433832795;

//static string theApp.GetDefaultPath();//Ĭ��·��,Ϊ��ǰ���������ļ���,��CMagicCabsineDoc�Ĺ��캯���г�ʼ��


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

