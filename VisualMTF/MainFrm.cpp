// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VisualMTF.h"

#include "MainFrm.h"

#include "BackgroundWnd.h"//��ʾ�ļ�����

#include "ParaSet.h"//��������
#include "FreqSet.h"//Ƶ������
#include "StageSet.h"//���
#include "ScanImage.h"//�ǵ�ͼ
#include "RealTimeFrame.h"//ʵʱ����
#include "ThroughFocusFrame.h"//�뽹����

#include<string>
#include<fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define STEP_DISTANCE 0.25

#define LINDEX 0
#define LRGBFORM FORM_GRAY8
#define CAMERA_WIDTH 640 
#define CAMERA_HEIGHT 480
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_CONF_PARASET, OnParaSetDialog)
	ON_COMMAND(ID_CONF_FREQSET, OnFreqSetDialog)
	ON_COMMAND(ID_FILE_OPEN_MENU, OnFileOpenMenu)
	ON_COMMAND(ID_FILE_SAVE_MENU, OnFileSaveMenu)
	ON_COMMAND(ID_CONF_STAGE, OnStageSetDialog)
	ON_COMMAND(ID_OPER_STARIMAGE, OnStarImage)
	ON_COMMAND(IDD_OPER_REALTIME, OnRealTime)
	ON_COMMAND(ID_OPER_THROUGH, OnThroughFocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

	//���еı�����������ΪĬ�ϵĳ�ʼֵ
	dPinDiameter=10;
	dAmplify=20;
	dFocusLength=50;
	dFNumber=8;
	dWaveLength=550;
	dLength=2000;
	sLensName="Unknown Name1";
	dPixel=0.0098;
	arraylength=6;
	dFreq=new double[arraylength];
	dLSFt=new double[arraylength];
	dLSFs=new double[arraylength];
	dMTFt=new double[arraylength];
	dMTFs=new double[arraylength];
	dPOSt=new double[arraylength];
	dPOSs=new double[arraylength];
	ExtendedMTFs=NULL;
	ExtendedMTFt=NULL;
	extendedMTFlength=0;
	dF=0.0;
	dMTFxmax=0.0;
	nStarHeight=16;
	nStarWidth=32;
	for(int i=0;i<arraylength;i++)
	{
		dFreq[i]=i+i;
		dLSFt[i]=100+5*i;
		dLSFs[i]=80+6*i;
		dMTFt[i]=0.5+1.0*i/arraylength*0.5;
		dMTFs[i]=0.3+1.0*i/arraylength*0.7;
		dPOSt[i]=0;
		dPOSs[i]=0;
	}
	SavedTime=new CTime(CTime::GetCurrentTime());
	typedpage=0;

	rc=DMCOpen(1,0,&hDmc);//�򿪵��������
	if(rc)
	{
		sprintf(cItemText,"Could not open stage controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		bStageInit=TRUE;
	}
	else
		bStageInit=FALSE;


	long lIndex=LINDEX;
	if ( hBoard=okOpenBoard(&lIndex) ) //��ָ�����е�ͼ��ɼ���
	{
		//Sleep(500);
		okSetVideoParam(hBoard, VIDEO_SOURCECHAN, 0x0 ); //������Ƶ�źŲ�����Դ·ѡ�񣬸��������һ·��
        
		okSetVideoParam(hBoard, VIDEO_RGBFORMAT, LRGBFORM ); //����8λ�ڰ���Ƶ��ʽ
		okSetCaptureParam(hBoard, CAPTURE_BUFRGBFORMAT, LRGBFORM ); //����֡�����8λ�ڰ׸�ʽ

		//������ɶ�ȡͼ��������BUFFER������
		rcVideo.left=rcVideo.top=0;
		rcVideo.right=CAMERA_WIDTH;
		rcVideo.bottom=CAMERA_HEIGHT;

		rcBuffer.left=rcBuffer.top=0;
		rcBuffer.right=CAMERA_WIDTH;
		rcBuffer.bottom=CAMERA_HEIGHT;

		okSetTargetRect(hBoard, VIDEO, &rcVideo); //����Դ��
		okSetTargetRect(hBoard, BUFFER, &rcBuffer); //����Ŀ��Ŀ����BUFFER

		okSetCaptureParam(hBoard, CAPTURE_SEQCAPWAIT, 1); //���òɼ���ʽ�´��ɼ�ȫ�������ٷ���

		lNum=okGetBufferSize(hBoard, (void **)&lpLinear, &dwSize); //��ñ�����Ϊͼ������ʹ�õľ�̬����BUFFER�ڵ�ǰ�����¿ɴ��ͼ��ķ���
			
		okSetTargetRect(hBoard, VIDEO, &rcVideo); //����ԴĿ����Ŀ���崰�ڴ�С
		bCameraInit=TRUE;
	}
	else
	{
		sprintf(cItemText,"Could not open the OK board.");
		MessageBox(cItemText);
		bCameraInit=FALSE;
	}
	pStarHeight=&nStarHeight;
	pStarWidth=&nStarWidth;
}

CMainFrame::~CMainFrame()
{
	mydelete();
	if(SavedTime!=NULL)
	{
		delete SavedTime;
		SavedTime=NULL;
	}
}

void CMainFrame::mydelete()
{
	if(dFreq!=NULL)
	{
		delete[] dFreq;
		dFreq=NULL;
	}
	if(dLSFt!=NULL)
	{
		delete[] dLSFt;
		dLSFt=NULL;
	}
	if(dLSFs!=NULL)
	{
		delete[] dLSFs;
		dLSFs=NULL;
	}
	if(dMTFt!=NULL)
	{
		delete[] dMTFt;
		dMTFt=NULL;
	}
	if(dMTFs!=NULL)
	{
		delete[] dMTFs;
		dMTFs=NULL;
	}
	if(dPOSt!=NULL)
	{
		delete[] dPOSt;
		dPOSt=NULL;
	}
	if(dPOSs!=NULL)
	{
		delete[] dPOSs;
		dPOSs=NULL;
	}
	if(ExtendedMTFt!=NULL)
	{
		delete[] ExtendedMTFt;
		ExtendedMTFt=NULL;
	}
	if(ExtendedMTFs!=NULL)
	{
		delete[] ExtendedMTFs;
		ExtendedMTFs=NULL;
	}
	arraylength=0;
	extendedMTFlength=0;
	dF=0.0;
	dMTFxmax=0.0;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	EnableDocking(CBRS_ALIGN_ANY);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

	cs.cx=800;
	cs.cy=650;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnFileOpenMenu() 
{
	// TODO: Add your command handler code here
	int i,time_Year,time_Month,time_Day,time_Hour,time_Minute,time_Second;
	CFileDialog filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY 
		|OFN_OVERWRITEPROMPT, "VMF�ļ� (*.vmf)|*.vmf|�����ļ� (*.*)|*.*||", NULL);//���ļ��Ի���
	char *filepath;
	const lenofcameraname=100;
	char cameraname[lenofcameraname];
	if(filedlg.DoModal()==IDOK)
	{
		string sfpath=filedlg.GetPathName();//��ȡ�ļ�·��
		filepath=new char[sfpath.length()+1];
		strcpy(filepath,sfpath.c_str());
		FILE *filepoint=fopen(filepath,"r");//���ļ�
		delete[] filepath;
		filepath=NULL;
		if(filepoint==NULL)
		{
			MessageBox("Could not open file!","Error");
			return;
		}
		fscanf(filepoint,"Saved time:%d-%d-%d-%d-%d-%d\n",&time_Year,&time_Month,&time_Day,&time_Hour,&time_Minute,&time_Second);//��ȡ����ʱ�����ɢ���ͱ���
		if(SavedTime!=NULL)
			delete SavedTime;
		SavedTime=new CTime(time_Year,time_Month,time_Day,time_Hour,time_Minute,time_Second);//������ʱ�丳��ʱ�����͵ı���
		fscanf(filepoint,"Pin Diameter:%lf\n",&dPinDiameter);//��ȡ�׾�
		fscanf(filepoint,"Amplification Ratio:%lf\n",&dAmplify);//��ȡ�м̷Ŵ���
		fscanf(filepoint,"Camera Name:");
		fgets(cameraname,lenofcameraname,filepoint);
		cameraname[strlen(cameraname)-1]='\0';
		sLensName=cameraname;//��ȡ��ͷ����
		fscanf(filepoint,"Focus:%lf\n",&dFocusLength);//��ȡ��ͷ����
		fscanf(filepoint,"F Number:%lf\n",&dFNumber);//��ȡ��ͷF��
		fscanf(filepoint,"WaveLength:%lf\n",&dWaveLength);//��ȡ��Դ����
		fscanf(filepoint,"Collimated Focus:%lf\n",&dLength);//��ȡƽ�й�ܽ���
		if(arraylength>0)
			mydelete();
		fscanf(filepoint,"Array Length:%d\n",&arraylength);//��ȡ�������鳤��
		
		
		dPOSt=new double[arraylength];//��ȡT����λ������
		fscanf(filepoint,"position(T):");
		for(i=0;i<arraylength;i++)
		{
			fscanf(filepoint,"%lf",&dPOSt[i]);
		}
		fscanf(filepoint,"\n");
		
		
		dLSFt=new double[arraylength];//��ȡT����LSF����
		fscanf(filepoint,"LSF(T):");
		for(i=0;i<arraylength;i++)
		{
			fscanf(filepoint,"%lf",&dLSFt[i]);
		}
		fscanf(filepoint,"\n");
		
		
		dPOSs=new double[arraylength];//��ȡS����λ������
		fscanf(filepoint,"position(S):");
		for(i=0;i<arraylength;i++)
		{
			fscanf(filepoint,"%lf",&dPOSs[i]);
		}
		fscanf(filepoint,"\n");
		
		dLSFs=new double[arraylength];//��ȡT����LSF����
		fscanf(filepoint,"LSF(S):");
		for(i=0;i<arraylength;i++)
		{
			fscanf(filepoint,"%lf",&dLSFs[i]);
		}
		fscanf(filepoint,"\n");
		
		
		dFreq=new double[arraylength];//��ȡƵ������
		fscanf(filepoint,"Frequence(lp/mm):");
		for(i=0;i<arraylength;i++)
		{
			fscanf(filepoint,"%lf",&dFreq[i]);
		}
		fscanf(filepoint,"\n");

		//ԭ������LSF����MTF�˴��ƺ������������ԭʼMTFֵ��û�ж���
		dMTFt=new double[arraylength];
		fscanf(filepoint,"MTF(T):");
		for(i=0;i<arraylength;i++)
		{
			fscanf(filepoint,"%lf",&dMTFt[i]);
		}
		fscanf(filepoint,"\n");

		dMTFs=new double[arraylength];
		fscanf(filepoint,"MTF(S):");
		for(i=0;i<arraylength;i++)
		{
			fscanf(filepoint,"%lf",&dMTFs[i]);
		}
		//�ڱ���ʱ��ÿ�еĻ��з�д�������ײ���ע����󱣴��MTFS֮��û�л��з�
		
		fclose(filepoint);//�ر��ļ�
		
		//SolveMTF();//Ҳ���Բ���ȡMTF��ֵ�����ɶ�ȡ��ϵ�LSF��ֵ��ͨ���ú�������õ�MTFֵ

		//������ģ̬�Ի���
		CBackgroundWnd* pBackgroundWnd;
		pBackgroundWnd=new CBackgroundWnd();
		if(pBackgroundWnd!=NULL)
		{
			pBackgroundWnd->getDataFromMainFrm(this);
			CRect rect;
			GetWindowRect(rect);//λ�ü���С�趨
			rect.top+=75;
			rect.left+=75;
			rect.right=rect.left+660;
			rect.bottom=rect.top+520;
			BOOL ret=pBackgroundWnd->Create(NULL,sLensName,WS_OVERLAPPEDWINDOW,rect,this);
			if(!ret)
				AfxMessageBox("Error Creating Dialog!");
			pBackgroundWnd->ShowWindow(SW_SHOW);//��ʾ�Ի���
		}
		else
		{
			AfxMessageBox("Error Creating Dialog Object!");
		}
	}
}

void CMainFrame::getDataFromWnd(void *pfrm/* =NULL */)
{
	CBackgroundWnd* pBackgroundWnd=NULL;
	if(pfrm==NULL)
		return;
	else
		pBackgroundWnd=(CBackgroundWnd*)pfrm;
	mydelete();
	dPinDiameter=pBackgroundWnd->getdPinDiameter();
	dAmplify=pBackgroundWnd->getdAmplify();
	dFocusLength=pBackgroundWnd->getdFocusLength();
	dFNumber=pBackgroundWnd->getdFNumber();
	dWaveLength=pBackgroundWnd->getdWaveLength();
	dLength=pBackgroundWnd->getdLength();
	sLensName=pBackgroundWnd->getsLensName();
	arraylength=pBackgroundWnd->getarraylength();
	
	dF=pBackgroundWnd->getCurrentF();
	dMTFxmax=pBackgroundWnd->getMTFmax();
	extendedMTFlength=pBackgroundWnd->getExtendedlength();

	dFreq=new double[arraylength];
	dMTFt=new double[arraylength];
	dMTFs=new double[arraylength];
	dLSFt=new double[arraylength];
	dLSFs=new double[arraylength];
	dPOSt=new double[arraylength];
	dPOSs=new double[arraylength];
	ExtendedMTFt=new double[extendedMTFlength];
	ExtendedMTFs=new double[extendedMTFlength];
	setdFreq(pBackgroundWnd->getdFreq());
	setdMTFt(pBackgroundWnd->getdMTFt());
	setdMTFs(pBackgroundWnd->getdMTFs());
	setdLSFt(pBackgroundWnd->getdLSFt());
	setdLSFs(pBackgroundWnd->getdLSFs());
	setdPOSt(pBackgroundWnd->getdPOSt());
	setdPOSs(pBackgroundWnd->getdPOSs());
	setExtendedMTFt(pBackgroundWnd->getExtendedMTFt());
	setExtendedMTFs(pBackgroundWnd->getExtendedMTFs());
	setSavedTime(pBackgroundWnd->getSavedTime());
}

void CMainFrame::OnFileSaveMenu() 
{
	// TODO: Add your command handler code here
	int i;
	CFileDialog filedlg(FALSE, NULL, NULL, OFN_HIDEREADONLY 
		|OFN_OVERWRITEPROMPT, "VMF�ļ� (*.vmf)|*.vmf|�����ļ� (*.*)|*.*||", NULL);//�����ļ�����Ի���
	char *filepath;
	if(filedlg.DoModal()==IDOK)
	{
		string sfpath=filedlg.GetPathName();//����ļ�����·��
		i=sfpath.length();
		filepath=new char[i+5];
		strcpy(filepath,sfpath.c_str());//�����ļ�·��
		if(strcmp(filepath+i-4,".vmf")!=0)//�ļ���׺���б�
		{
			filepath[i++]='.';//��׺�����
			filepath[i++]='v';
			filepath[i++]='m';
			filepath[i++]='f';
			filepath[i]='\0';
		}
		FILE *filepoint=fopen(filepath,"w");//���ļ�
		delete[] filepath;
		filepath=NULL;
		if(filepoint==NULL)
		{
			MessageBox("Could not save file!","Error");//���ļ�ʧ��
			return;
		}
		CTime temptime;
		temptime=CTime::GetCurrentTime();//��ȡ��ǰʱ��
		CString temptimestring=temptime.Format("%Y-%m-%d-%H-%M-%S");//��ʱ�����ת�����ַ�������ʽΪ��-��-��-ʱ-��-��
		fprintf(filepoint,"Saved time:%s\n",temptimestring);//д�뱣��ʱ��
		fprintf(filepoint,"Pin Diameter:%.2lf\n",dPinDiameter);//д��׾�
		fprintf(filepoint,"Amplification Ratio:%.2lf\n",dAmplify);//д���м�ϵͳ�Ŵ���
		fprintf(filepoint,"Camera Name:%s\n",sLensName);//д�뾵ͷ����
		fprintf(filepoint,"Focus:%.2lf\n",dFocusLength);//д��ƽ�й�ܽ���
		fprintf(filepoint,"F Number:%.2lf\n",dFNumber);//д�뾵ͷF��
		fprintf(filepoint,"WaveLength:%.2lf\n",dWaveLength);//д���Դ����
		fprintf(filepoint,"Collimated Focus:%.2lf\n",dLength);//д��ƽ�й�ܽ���
		fprintf(filepoint,"Array Length:%d\n",arraylength);//д����������ߴ�
		
		
		fprintf(filepoint,"position(T):");//д��T����λ������
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",dPOSt[i]);
		}
	

		fprintf(filepoint,"\nLSF(T):");//д��T����LSF����
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",dLSFt[i]);
		}

		
		fprintf(filepoint,"\nposition(S):");//д��S����λ������
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",dPOSs[i]);
		}
		


		fprintf(filepoint,"\nLSF(S):");//д��S����LSF����
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",dLSFs[i]);
		}
		

		fprintf(filepoint,"\nFrequence(lp/mm):");//д��Ƶ������
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",dFreq[i]);
		}
		
		fprintf(filepoint,"\nMTF(T):");//д��T����MTF����
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",dMTFt[i]);
		}
		
		
		fprintf(filepoint,"\nMTF(S):");//д��S����MTF����
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",dMTFs[i]);
		}
		
		
		fclose(filepoint);//�ر��ļ�
	}
}

void CMainFrame::OnParaSetDialog() 
{
	// TODO: Add your command handler code here
	CParaSet ParaSetDialog;
	ParaSetDialog.m_dPinDiameter=dPinDiameter;
	ParaSetDialog.m_dAmplify=dAmplify;
	ParaSetDialog.m_dFocusLength=dFocusLength;
	ParaSetDialog.m_dFNumber=dFNumber;
	ParaSetDialog.m_dWaveLength=dWaveLength;
	ParaSetDialog.m_dLength=dLength;
	ParaSetDialog.m_sLensName=sLensName;
	




	if(ParaSetDialog.DoModal()==IDOK)
	{
		dPinDiameter=ParaSetDialog.m_dPinDiameter;
		dAmplify=ParaSetDialog.m_dAmplify;
		dFocusLength=ParaSetDialog.m_dFocusLength;
		dFNumber=ParaSetDialog.m_dFNumber;
		dWaveLength=ParaSetDialog.m_dWaveLength;
		dLength=ParaSetDialog.m_dLength;
		sLensName=ParaSetDialog.m_sLensName;
	}
}

void CMainFrame::OnFreqSetDialog() 
{
	// TODO: Add your command handler code here
	CFreqSet FreqSetDialog;
	if(FreqSetDialog.DoModal()==IDOK)
	{
		dFreq[0]=FreqSetDialog.m_dFreq1;
		dFreq[1]=FreqSetDialog.m_dFreq2;
		dFreq[2]=FreqSetDialog.m_dFreq3;
		dFreq[3]=FreqSetDialog.m_dFreq4;
		dFreq[4]=FreqSetDialog.m_dFreq5;
		dFreq[5]=FreqSetDialog.m_dFreq6;
		dMTFt[0]=FreqSetDialog.m_dMTFt1;
		dMTFt[1]=FreqSetDialog.m_dMTFt2;
		dMTFt[2]=FreqSetDialog.m_dMTFt3;
		dMTFt[3]=FreqSetDialog.m_dMTFt4;
		dMTFt[4]=FreqSetDialog.m_dMTFt5;
		dMTFt[5]=FreqSetDialog.m_dMTFt6;
		dMTFs[0]=FreqSetDialog.m_dMTFs1;
		dMTFs[1]=FreqSetDialog.m_dMTFs2;
		dMTFs[2]=FreqSetDialog.m_dMTFs3;
		dMTFs[3]=FreqSetDialog.m_dMTFs4;
		dMTFs[4]=FreqSetDialog.m_dMTFs5;
		dMTFs[5]=FreqSetDialog.m_dMTFs6;
	}
}

double CMainFrame::getdPinDiameter()
{
	return dPinDiameter;
}

double CMainFrame::getdAmplify()
{
	return dAmplify;
}

double CMainFrame::getdFocusLength()
{
	return dFocusLength;
}

double CMainFrame::getdFNumber()
{
	return dFNumber;
}

double CMainFrame::getdWaveLength()
{
	return dWaveLength;
}

double CMainFrame::getdLength()
{
	return dLength;
}

CString CMainFrame::getsLensName()
{
	return sLensName;
}

int CMainFrame::getarraylength()
{
	return arraylength;
}

double* CMainFrame::getdFreq()
{
	return dFreq;
}

double* CMainFrame::getdLSFt()
{
	return dLSFt;
}

double* CMainFrame::getdLSFs()
{
	return dLSFs;
}

double* CMainFrame::getdMTFt()
{
	return dMTFt;
}

double* CMainFrame::getdMTFs()
{
	return dMTFs;
}

double* CMainFrame::getdPOSt()
{
	return dPOSt;
}

double* CMainFrame::getdPOSs()
{
	return dPOSs;
}

int CMainFrame::getExtendedlength()
{
	return extendedMTFlength;
}

double* CMainFrame::getExtendedMTFt()
{
	return ExtendedMTFt;
}

double* CMainFrame::getExtendedMTFs()
{
	return ExtendedMTFs;
}

double CMainFrame::getMTFxmax()
{
	return dMTFxmax;
}

double CMainFrame::getdF()
{
	return dF;
}

CTime* CMainFrame::getSavedTime()
{
	return SavedTime;
}

double CMainFrame::GetTypedmax()
{
	const double thexmax=400.0;//�˴�ΪMTF������ʾƵ����������ޣ�����RightMTFView::GetXmax()�µĸ�ֵһ��ı�
    double f=Calc_f();
	double Max=f;
	while(Max<=thexmax)
	{
		Max+=f;
	}
	Max-=f;
	
	return Max;
}

double CMainFrame::Calc_f()
{
	const double d=0.0098;
	if(arraylength==0)
	{
		return 0.0;
	}
	return dAmplify/arraylength/d;
}

void CMainFrame::setdPinDiameter(double dt)
{
	dPinDiameter=dt;
}

void CMainFrame::setdAmplify(double dt)
{
	dAmplify=dt;
}

void CMainFrame::setdFocusLength(double dt)
{
	dFocusLength=dt;
}

void CMainFrame::setdFNumber(double dt)
{
	dFNumber=dt;
}

void CMainFrame::setdWaveLength(double dt)
{
	dWaveLength=dt;
}

void CMainFrame::setdLength(double dt)
{
	dLength=dt;
}

void CMainFrame::setsLensName(CString ds)
{
	sLensName=ds;
}

void CMainFrame::setarraylength(int di)
{
	arraylength=di;
}

void CMainFrame::setdFreq(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dFreq[i]=pdt[i];
}

void CMainFrame::setdLSFt(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dLSFt[i]=pdt[i];
}

void CMainFrame::setdLSFs(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dLSFs[i]=pdt[i];
}

void CMainFrame::setdMTFt(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dMTFt[i]=pdt[i];
}

void CMainFrame::setdMTFs(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dMTFs[i]=pdt[i];
}

void CMainFrame::setdPOSt(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dPOSt[i]=pdt[i];
}

void CMainFrame::setdPOSs(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dPOSs[i]=pdt[i];
}

void CMainFrame::setExtendedMTFt(double* pdt)
{
	int i;
	for(i=0;i<extendedMTFlength;i++)
		ExtendedMTFt[i]=pdt[i];
}

void CMainFrame::setExtendedMTFs(double* pdt)
{
	int i;
	for(i=0;i<extendedMTFlength;i++)
		ExtendedMTFs[i]=pdt[i];
}

void CMainFrame::setSavedTime(CTime *LastSavedTime/* =NULL */)
{
	if(SavedTime!=NULL)
	{
		delete(SavedTime);
	}
	if(LastSavedTime==NULL)
	{
		CTime currenttime;
		currenttime=CTime::GetCurrentTime();
		SavedTime=new CTime(currenttime);
	}
	else
	{
		SavedTime=new CTime(*LastSavedTime);
	}
}

void CMainFrame::setTypedPage(int nPage)
{
	typedpage=nPage;
}

int CMainFrame::getTypedPage()
{
	return typedpage;
}

void CMainFrame::SolveMTF()//�ú��������dLSFt��dLSFs���һ�����dMTFt��dMTFs���ȵ�����
{
	int i=arraylength,thepower=0;
	if(dMTFt==NULL)
		dMTFt=new double[arraylength];
	if(dMTFs==NULL)
		dMTFs=new double[arraylength];
	double *temparray=new double[arraylength];//�鲿�ݴ�����
	while(i>1)//ȷ����Ҫ���ݼ���
	{
		thepower++;
		i>>=1;
	}
	myfft(dLSFt,dMTFt,temparray,thepower);
	dMTFt[0]=sqrt(dMTFt[0]*dMTFt[0]+temparray[0]*temparray[0]);//�׵�ַ��ȡģ
	myfft(dLSFs,dMTFs,temparray,thepower);
	dMTFs[0]=sqrt(dMTFs[0]*dMTFs[0]+temparray[0]*temparray[0]);//�׵�ַ��ȡģ
	for(i=1;i<arraylength;i++)
	{
		dMTFt[i]=sqrt(dMTFt[i]*dMTFt[i]+temparray[i]*temparray[i])/dMTFt[0];//���׵�ַ��ȡģ�����׵�ֵַ��һ��
		dMTFs[i]=sqrt(dMTFs[i]*dMTFs[i]+temparray[i]*temparray[i])/dMTFs[0];//���׵�ַ��ȡģ�����׵�ֵַ��һ��
	}
	dMTFt[0]=1.0;
	dMTFs[0]=1.0;
	delete[] temparray;
}

void CMainFrame::myfft(double *TD,double *FDre,double *FDim,int r)
{
	long count;		//����Ҷ�任����
	int i,j,k;		//ѭ������
	int bfsize,p;
	double angle,tempre,tempim;	//�Ƕ�
	double *Wre,*Wim,*Xre1,*Xim1,*Xre2,*Xim2,*X;
	
	count=1<<r;		//���㸵��Ҷ�任����
	
	//������������洢��
	Wre=new double[count/2];
	Wim=new double[count/2];
	Xre1=new double[count];
	Xre2=new double[count];
	Xim1=new double[count];
	Xim2=new double[count];
	
	//�����Ȩϵ��
	for(i=0;i<count/2;i++)
	{
		angle=-i*PI*2/count;
		Wre[i]=cos(angle);
		Wim[i]=sin(angle);
	}
	
	//��ʱ���д��X1
	for (i=0;i<count;i++)
	{
		Xre1[i]=TD[i];
		Xim1[i]=0;
	}
	
	//���õ����㷨���п��ٸ���Ҷ�任
	for (k=0;k<r;k++)//����r�ε���
	{
		for (j=0;j<1<<k;j++)//ÿ�ε����ֳ�(1<<k)�����ּ���
		{
			bfsize=1<<(r-k);//ÿ�ε����������ֵĳ���
			for (i=0;i<bfsize/2;i++)
			{
				p=j*bfsize;//��λ��������
				Xre2[i+p]=Xre1[i+p]+Xre1[i+p+bfsize/2];
				Xim2[i+p]=Xim1[i+p]+Xim1[i+p+bfsize/2];
				//X2[i+p+bfsize/2]=(X1[i+p]-X1[i+p+bfsize/2])*W[i*(1<<k)];
				tempre=Xre1[i+p]-Xre1[i+p+bfsize/2];
				tempim=Xim1[i+p]-Xim1[i+p+bfsize/2];
				Xre2[i+p+bfsize/2]=tempre*Wre[i*(1<<k)]-tempim*Wim[i*(1<<k)];
				Xim2[i+p+bfsize/2]=tempre*Wim[i*(1<<k)]+tempim*Wre[i*(1<<k)];
			}
		}
		X=Xre1;			//����X1��X2
		Xre1=Xre2;		//Ŀ���ǽ�X2�е�Ԫ���Ƶ�X1�������ý���ָ��ķ���ʵ��
		Xre2=X;
		X=Xim1;
		Xim1=Xim2;
		Xim2=X;
	}
	
	//��������
	for (j=0;j<count;j++)
	{
		p=0;
		for (i=0;i<r;i++)//�������빲rλ����ѭ��ʹpΪj�ĵ�����
		{
			if(j&(1<<i))
			{
				p+=1<<(r-i-1);
			}
		}
		FDre[j]=Xre1[p];
		FDim[j]=Xim1[p];
	}
	
	delete[] Wre;
	delete[] Wim;
	delete[] Xre1;
	delete[] Xre2;
	delete[] Xim1;
	delete[] Xim2;
}

void CMainFrame::OnStageSetDialog() 
{
	// TODO: Add your command handler code here
	CStageSet dlg;
	//���»���ĵ���ĵ�ǰ����λ��
	rc=DMCCommand(hDmc,"TPA\r",szBuffer,sizeof(szBuffer));
	dlg.m_dXPos=ResSteptoDis(szBuffer);
	rc=DMCCommand(hDmc,"TPB\r",szBuffer,sizeof(szBuffer));
	dlg.m_dYPos=ResSteptoDis(szBuffer);
	rc=DMCCommand(hDmc,"TPC\r",szBuffer,sizeof(szBuffer));
	dlg.m_dZPos=ResSteptoDis(szBuffer);
	rc=DMCCommand(hDmc,"TPD\r",szBuffer,sizeof(szBuffer));
	dlg.m_dTPos=ResSteptoDis(szBuffer);
	dlg.m_bLocked=1;//�������õ����z�ᣩΪ����״̬
	

	int result=dlg.DoModal();
}

double CMainFrame::ResSteptoDis(char *cInputChar)
{
	return STEP_DISTANCE*atoi(cInputChar);
}

HANDLEDMC CMainFrame::getHANDLEDMC()
{
	return hDmc;
}

void CMainFrame::OnStarImage() 
{
	// TODO: Add your command handler code here
	CScanImage *dlg=new CScanImage;
	
	nStarHeight=16;
	nStarWidth=64;
	
	dlg->m_nXPos=64;
	dlg->m_nYPos=64;
	
	dlg->m_nBoxHeight=16;
	dlg->m_nBoxWidth=32;
	
	dlg->m_sCombo1="16";
	dlg->m_sCombo2="32";
	dlg->Create(IDD_DIALOG8);

	dlg->UpdateWindow();
	dlg->ShowWindow(SW_SHOW);

}

HANDLE CMainFrame::getHANDLEOK()
{
	return hBoard;
}

LPBYTE CMainFrame::getLPBYTEOK()
{
	return lpLinear;
}



int* CMainFrame::getpStarHeight()
{
	return pStarHeight;
}

int* CMainFrame::getpStarWidth()
{
	return pStarWidth;
}

void CMainFrame::OnRealTime() 
{
	// TODO: Add your command handler code here
	CRealTimeFrame* pRealTimeFrame;
	pRealTimeFrame=new CRealTimeFrame();
		
	if(pRealTimeFrame!=NULL)
	{
		CRect rect;
		GetWindowRect(rect);//���µ����޶��Ի���λ���ߴ�
		rect.top+=75;
		rect.left+=75;
		rect.right=rect.left+1000;
		rect.bottom=rect.top+700;
		CString sTiTle="ʵʱ����";
		BOOL ret=pRealTimeFrame->Create(NULL,sTiTle,WS_OVERLAPPEDWINDOW,rect,this);//CWnd::Create(Null���Ի������ƣ��Ի����񣬶Ի���ߴ磬this��??��ȷ�ϴ˴�this�ĺ���
		if(!ret)
		{	
			AfxMessageBox("Error Creating Dialog!");
			return;
		}
		else
		{
			
			pRealTimeFrame->ShowWindow(SW_SHOW);//��ģʽ�Ի������ʾ
		}
	}
}

int CMainFrame::getnStarHeight()
{
	return nStarHeight;
}

int CMainFrame::getnStarWidth()
{
	return nStarWidth;
}

BOOL CMainFrame::getbCamInit()
{
	return bCameraInit;
}

BOOL CMainFrame::getbStageInit()
{
	return bStageInit;
}

HANDLE CMainFrame::getCameraHandle()
{
	return hBoard;
}

HANDLEDMC CMainFrame::getStageHandle()
{
	return hDmc;
}

LPBYTE CMainFrame::getCameraBuffer()
{
	return lpLinear;
}

double CMainFrame::getdPixel()
{
	return dPixel;
}

void CMainFrame::OnThroughFocus() 
{
	// TODO: Add your command handler code here
	CThroughFocusFrame* pThroughFocusFrame;
	pThroughFocusFrame=new CThroughFocusFrame();
		
	if(pThroughFocusFrame!=NULL)
	{
		CRect rect;
		GetWindowRect(rect);//���µ����޶��Ի���λ���ߴ�
		rect.top+=75;
		rect.left+=75;
		rect.right=rect.left+1000;
		rect.bottom=rect.top+700;
		CString sTiTle="�뽹����";
		BOOL ret=pThroughFocusFrame->Create(NULL,sTiTle,WS_OVERLAPPEDWINDOW,rect,this);//CWnd::Create(Null���Ի������ƣ��Ի����񣬶Ի���ߴ磬this��??��ȷ�ϴ˴�this�ĺ���
		if(!ret)
		{	
			AfxMessageBox("Error Creating Dialog!");
			return;
		}
		else
		{
			
			pThroughFocusFrame->ShowWindow(SW_SHOW);//��ģʽ�Ի������ʾ
		}
	}
}




