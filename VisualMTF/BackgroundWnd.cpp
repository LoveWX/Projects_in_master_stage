// BackgroundWnd.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "BackgroundWnd.h"
#include "LeftFormView.h"
#include "RightMTFView.h"
#include "RightLSFView.h"
#include "RightListView.h"
#include "RightTextView.h"
#include "MainFrm.h"
#include "ParaSet.h"
#include "FreqSet.h"
#include "RealTimeUp.h"

#include<string>
#include<fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackgroundWnd

IMPLEMENT_DYNCREATE(CBackgroundWnd, CFrameWnd)

CBackgroundWnd::CBackgroundWnd()
{
	// TODO: add member initialization code here
	
	//���еı�����������ΪĬ�ϵĳ�ʼֵ
	dPinDiameter=10;
	dAmplify=20;
	dFocusLength=50;
	dFNumber=8;
	dWaveLength=550;
	dLength=2000;
	sLensName="Unknown Name";
	arraylength=6;
	dFreq=new double[arraylength];
	dLSFt=new double[arraylength];
	dLSFs=new double[arraylength];
	dMTFt=new double[arraylength];
	dMTFs=new double[arraylength];
	dPOSt=new double[arraylength];
	dPOSs=new double[arraylength];
	tempslopet=new double[arraylength];	
	tempslopes=new double[arraylength];	
	ExtendedMTFt=NULL;
	ExtendedMTFs=NULL;


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
}

CBackgroundWnd::~CBackgroundWnd()
{
	mydelete();
	if(SavedTime!=NULL)
	{
		delete SavedTime;
		SavedTime=NULL;
	}
}

void CBackgroundWnd::mydelete()//����ʾ��������������
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
	if(tempslopet!=NULL)
	{
		delete[] tempslopet;
		tempslopet=NULL;
	}
	if(tempslopes!=NULL)
	{
		delete[] tempslopes;
		tempslopes=NULL;
	}
	arraylength=0;
	extendedMTFlength=0;
}

void CBackgroundWnd::Calc_f()
{
	const double d=0.0098;//̽������Ԫ�ߴ磨mm��
	if(arraylength==0)
	{
		return;
	}
	dOriginalF=dAmplify/arraylength/d;//ԭʼƵ�ʼ��
	int temp=(int)(dOriginalF/5);//ԭʼƵ�ʼ�������Ĳ�ֵ������ֵԭ��Ϊ��ֵ�������Ƶ�ʲ�Ϊ������5��������ֵ��
	extendedMTFlength=(temp-1)*(arraylength-1)+arraylength;//��ֵ��Ƶ�ʵ���
	dCurrentF=dOriginalF*(arraylength-1)/(extendedMTFlength-1);
}

void CBackgroundWnd::Calc_Frequence()//�ú������Լ���MTF��ֵǰ��Ƶ���ƶ���
{
	int i;
	dFreq[0]=0.0;
	for(i=1;i<arraylength;i++)
	{
		dFreq[i]=dFreq[i-1]+dOriginalF;
	}
}

void CBackgroundWnd::extendMTF()//�ĺ������MTFԭʼ���ݵĲ�ֵ
{
	if(ExtendedMTFs!=NULL)
	{
		delete[] ExtendedMTFs;
	}
	if(ExtendedMTFt!=NULL)
	{
		delete[] ExtendedMTFt;
	}
	if(tempslopet!=NULL)
	{
		delete[] tempslopet;
	}
	if(tempslopes!=NULL)
	{
		delete[] tempslopes;
	}
	ExtendedMTFt=new double[extendedMTFlength];//����Ϊ��ֵ��MTFֵ
	ExtendedMTFs=new double[extendedMTFlength];
	tempslopet=new double[arraylength];//����Ϊ��ֵǰб��
	tempslopes=new double[arraylength];
	double* tempf=new double[arraylength];//����Ϊ��ֵǰ��Ƶ������	
	double* tempx=new double[extendedMTFlength];	
	int i;
	tempf[0]=0.0;
	tempx[0]=0.0;
	for(i=1;i<arraylength;i++)
	{
		tempf[i]=tempf[i-1]+dOriginalF;//����ֵǰƵ������ֵ
	}
	for(i=1;i<extendedMTFlength;i++)
	{
		tempx[i]=tempx[i-1]+dCurrentF;//����ֵ��Ƶ������ֵ
	}
	spline(tempf,dMTFt,getLeftSlope(),getRightSlope(),tempslopet,arraylength);//��ò�ֵǰ����б��
	for(i=0;i<extendedMTFlength;i++)
	{
		splint(tempf,dMTFt,tempslopet,tempx[i],ExtendedMTFt[i],arraylength);//��ò�ֵ�����ֵ
	}
	spline(tempf,dMTFs,getLeftSlope(),getRightSlope(),tempslopes,arraylength);//��ò�ֵǰ����б��
	for(i=0;i<extendedMTFlength;i++)
	{
		splint(tempf,dMTFs,tempslopes,tempx[i],ExtendedMTFs[i],arraylength);//��ò�ֵ�����ֵ
	}

	delete[] tempf;
	delete[] tempx;
}

double CBackgroundWnd::getLeftSlope()
{
	return 1.0e31;
}

double CBackgroundWnd::getRightSlope()
{
	return 1.0e31;
}

void CBackgroundWnd::spline(double* x,double* y,double yp1,double ypn,double* y2,int lena)
{
	int i,k;
	double p,qn,sig,un;
	
	int n=lena;
	double * u=new double[n-1];
	if(yp1>0.99e30)
		y2[0]=u[0]=0.0;
	else
	{
		y2[0]=-0.5;
		u[0]=(3.0/(x[1]-x[0]))*((y[1]-y[0])/(x[1]-x[0])-yp1);
		
	}
	for(i=1;i<n-1;i++)
	{
		sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
		p=sig*y2[i-1]+2.0;
		y2[i]=(sig-1.0)/p;
		u[i]=(y[i+1]-y[i])/(x[i+1]-x[i])-(y[i]-y[i-1])/(x[i]-x[i-1]);
		u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1]/p);
	}
	if(ypn>0.99e30)
	{
		qn=un=0.0;
	}
	else
	{
		qn=0.5;
		un=(3.0/(x[n-1]-x[n-2]))*(ypn-(y[n-1]-y[n-2])/(x[n-1]-x[n-2]));
	}
	y2[n-1]=(un-qn*u[n-2])/(qn*y2[n-2]+1.0);
	for (k=n-2;k>=0;k--)
		y2[k]=y2[k]*y2[k+1]+u[k];
	delete[] u;
}

void CBackgroundWnd::splint(double* xa,double* ya,double* y2a,double x,double &y,int lena)
{
	int k;
	double h,b,a;
	
	int n=lena;
	int klo=0;
	int khi=n-1;
	while (khi-klo>1)
	{
		k=(khi+klo)>>1;
		if(xa[k]>x)
			khi=k;
		else
			klo=k;
	}
	h=xa[khi]-xa[klo];
	if(h==0.0)
	{
		MessageBox("Bad xa input!");
		return;
	}
	a=(xa[khi]-x)/h;
	b=(x-xa[klo])/h;
	y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]
		+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
}

void CBackgroundWnd::ChangeView(int CurrentGet)
{
    CRect rc;
    GetClientRect(&rc);
    CSize paneSize(rc.Width()/4,rc.Height());
	m_wndSplitter.DeleteView(0,1);
	switch(CurrentGet)
	{
	case 0:
		m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(RightMTFView),paneSize,NULL);
		break;
	case 1:
		m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(RightLSFView),paneSize,NULL);
		break;
	case 2:
		m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(RightTextView),paneSize,NULL);
		break;
	case 3:
		m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(RightListView),paneSize,NULL);
		break;
	default:
		break;
	}
	m_wndSplitter.RecalcLayout();
}

void* CBackgroundWnd::GetLeftView()
{
	return (void*)m_wndSplitter.GetPane(0,0);
}

void* CBackgroundWnd::GetRightView()
{
	return (void*)m_wndSplitter.GetPane(0,1);
}

BEGIN_MESSAGE_MAP(CBackgroundWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CBackgroundWnd)
	ON_COMMAND(ID_MENUITEM_SAVE, OnMenuitemSave)
	ON_COMMAND(ID_MENUITEM_PRINT, OnMenuitemPrint)
	ON_COMMAND(ID_MENUITEM_PRINTPREVIEW, OnMenuitemPrintpreview)
	ON_COMMAND(ID_MENU_CONF_PARASET, OnMenuConfParaset)
	ON_COMMAND(ID_MENU_FREQ_PARASET, OnMenuFreqParaset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackgroundWnd message handlers

BOOL CBackgroundWnd::PreCreateWindow(CREATESTRUCT& cs)
{
//	cs.style &= ~WS_MAXIMIZEBOX;
//	cs.style &= ~WS_MINIMIZEBOX;
//	return CFrameWnd::PreCreateWindow(cs);

	
    // Size the window to 1/3 screen size and center it 
    cs.cy = ::GetSystemMetrics(SM_CYSCREEN) / 1.4; 
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN) / 1.3; 
    cs.y = ((cs.cy * 1.4) - cs.cy) / 2; 
    cs.x = ((cs.cx * 1.3) - cs.cx) / 2;
	
    // Call the base-class version
    return CFrameWnd::PreCreateWindow(cs); 

}

BOOL CBackgroundWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
    CRect rc;
    GetClientRect(&rc);
    //CSize paneSize(rc.Width()/4,rc.Height());
    CSize paneSize(228,rc.Height());
    m_wndSplitter.CreateStatic(this,1,2);
    m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(LeftFormView),paneSize,pContext);
    m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(RightTextView),paneSize,pContext);

	m_myMenu.LoadMenu(IDR_MENU1);
	SetMenu(&m_myMenu);
    return TRUE;
}

void CBackgroundWnd::getDataFromMainFrm(void *mainfrm/* =NULL */)
{
	mydelete();
	CMainFrame* MainFramePoint=NULL;
	if(mainfrm==NULL)
		MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	else
		MainFramePoint=(CMainFrame*)mainfrm;
	dPinDiameter=MainFramePoint->getdPinDiameter();
	dAmplify=MainFramePoint->getdAmplify();
	dFocusLength=MainFramePoint->getdFocusLength();
	dFNumber=MainFramePoint->getdFNumber();
	dWaveLength=MainFramePoint->getdWaveLength();
	dLength=MainFramePoint->getdLength();
	sLensName=MainFramePoint->getsLensName();
	arraylength=MainFramePoint->getarraylength();

	dFreq=new double[arraylength];
	dMTFt=new double[arraylength];
	dMTFs=new double[arraylength];
	dLSFt=new double[arraylength];
	dLSFs=new double[arraylength];
	dPOSt=new double[arraylength];
	dPOSs=new double[arraylength];
	//ExtendedMTFt=new double[extendedMTFlength];
	//ExtendedMTFs=new double[extendedMTFlength];
	setdFreq(MainFramePoint->getdFreq());
	setdMTFt(MainFramePoint->getdMTFt());
	setdMTFs(MainFramePoint->getdMTFs());
	setdLSFt(MainFramePoint->getdLSFt());
	setdLSFs(MainFramePoint->getdLSFs());
	setdPOSt(MainFramePoint->getdPOSt());
	setdPOSs(MainFramePoint->getdPOSs());
	//setExtendedMTFt(MainFramePoint->getExtendedMTFt());
	//setExtendedMTFs(MainFramePoint->getExtendedMTFs());
	//setSavedTime(MainFramePoint->getSavedTime());
	Calc_f();//�����ֵǰ��Ƶ�Լ���ֵ���Ƶ�����鳤��
	//Calc_Frequence();//�ú����ƺ����࣬ԭʼƵ������ֵ����setdFreq���趨
	extendMTF();
}

void CBackgroundWnd::sendDataToMainFrm(void *mainfrm/* =NULL */)
{
	CMainFrame* MainFramePoint=NULL;
	if(mainfrm==NULL)
		MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	else
		MainFramePoint=(CMainFrame*)mainfrm;
	MainFramePoint->getDataFromWnd(this);
}

double CBackgroundWnd::getdPinDiameter()
{
	return dPinDiameter;
}

double CBackgroundWnd::getdAmplify()
{
	return dAmplify;
}

double CBackgroundWnd::getdFocusLength()
{
	return dFocusLength;
}

double CBackgroundWnd::getdFNumber()
{
	return dFNumber;
}

double CBackgroundWnd::getdWaveLength()
{
	return dWaveLength;
}

double CBackgroundWnd::getdLength()
{
	return dLength;
}

CString CBackgroundWnd::getsLensName()
{
	return sLensName;
}

int CBackgroundWnd::getarraylength()
{
	return arraylength;
}

int CBackgroundWnd::getExtendedlength()
{
	return extendedMTFlength;
}

double* CBackgroundWnd::getdFreq()
{
	return dFreq;
}

double* CBackgroundWnd::getdLSFt()
{
	return dLSFt;
}

double* CBackgroundWnd::getdLSFs()
{
	return dLSFs;
}

double* CBackgroundWnd::getdMTFt()
{
	return dMTFt;
}

double* CBackgroundWnd::getdMTFs()
{
	return dMTFs;
}

double* CBackgroundWnd::getdPOSt()
{
	return dPOSt;
}

double* CBackgroundWnd::getdPOSs()
{
	return dPOSs;
}

double CBackgroundWnd::getMTFmax()
{
	RightMTFView* RightMTFViewPoint=(RightMTFView*)(this->GetRightView());
	return RightMTFViewPoint->getMTFmax();	
}

double* CBackgroundWnd::getExtendedMTFt()
{
	return ExtendedMTFt;
}

double* CBackgroundWnd::getExtendedMTFs()
{
	return ExtendedMTFs;
}

double CBackgroundWnd::getCurrentF()
{
	return dCurrentF;
}

double CBackgroundWnd::getOriginalF()
{
	return dOriginalF;
}

CTime* CBackgroundWnd::getSavedTime()
{
	return SavedTime;
}

void CBackgroundWnd::setdPinDiameter(double dt)
{
	dPinDiameter=dt;
}

void CBackgroundWnd::setdAmplify(double dt)
{
	dAmplify=dt;
}

void CBackgroundWnd::setdFocusLength(double dt)
{
	dFocusLength=dt;
}

void CBackgroundWnd::setdFNumber(double dt)
{
	dFNumber=dt;
}

void CBackgroundWnd::setdWaveLength(double dt)
{
	dWaveLength=dt;
}

void CBackgroundWnd::setdLength(double dt)
{
	dLength=dt;
}

void CBackgroundWnd::setsLensName(CString ds)
{
	sLensName=ds;
}

void CBackgroundWnd::setarraylength(int di)
{
	arraylength=di;
}

void CBackgroundWnd::setExtendedlength(int di)
{
	extendedMTFlength=di;
}

void CBackgroundWnd::setdFreq(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dFreq[i]=pdt[i];
}

void CBackgroundWnd::setdLSFt(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dLSFt[i]=pdt[i];
}

void CBackgroundWnd::setdLSFs(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dLSFs[i]=pdt[i];
}

void CBackgroundWnd::setdMTFt(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dMTFt[i]=pdt[i];
}

void CBackgroundWnd::setdMTFs(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dMTFs[i]=pdt[i];
}

void CBackgroundWnd::setdPOSt(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dPOSt[i]=pdt[i];
}

void CBackgroundWnd::setdPOSs(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		dPOSs[i]=pdt[i];
}

void CBackgroundWnd::setExtendedMTFt(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		ExtendedMTFt[i]=pdt[i];
}

void CBackgroundWnd::setExtendedMTFs(double* pdt)
{
	int i;
	for(i=0;i<arraylength;i++)
		ExtendedMTFs[i]=pdt[i];
}

void CBackgroundWnd::setSavedTime(CTime *LastSavedTime/* =NULL */)
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

void CBackgroundWnd::CalcMTF(double* x,double* y1,double* y2)
{
	double tempxmax=dOriginalF*(arraylength-1);
	int i;
	for(i=0;i<6;i++)
	{
		if(x[i]>=0.0&&x[i]<=tempxmax)
		{
			splint(dFreq,dMTFt,tempslopet,x[i],y1[i],arraylength);
			splint(dFreq,dMTFs,tempslopes,x[i],y2[i],arraylength);
		}
	}
}

void CBackgroundWnd::send6data(double* a,double* b,double* c)
{
	int i;
	for(i=0;i<6;i++)
	{
		a[i]=dFreq[i];
		b[i]=dMTFt[i];
		c[i]=dMTFs[i];
	}
}

void CBackgroundWnd::OnMenuitemSave() 
{
	// TODO: Add your command handler code here
	int i;
	CFileDialog filedlg(FALSE, NULL, NULL, OFN_HIDEREADONLY 
		|OFN_OVERWRITEPROMPT, "VMF�ļ� (*.vmf)|*.vmf|�����ļ� (*.*)|*.*||", NULL);
	char *filepath;
	if(filedlg.DoModal()==IDOK)
	{
		string sfpath=filedlg.GetPathName();
		i=sfpath.length();
		filepath=new char[i+5];
		strcpy(filepath,sfpath.c_str());
		if(strcmp(filepath+i-4,".vmf")!=0)
		{
			filepath[i++]='.';
			filepath[i++]='v';
			filepath[i++]='m';
			filepath[i++]='f';
			filepath[i]='\0';
		}
		FILE *filepoint=fopen(filepath,"w");
		delete[] filepath;
		filepath=NULL;
		if(filepoint==NULL)
		{
			MessageBox("Could not save file!","Error");
			return;
		}
		CTime temptime;
		temptime=CTime::GetCurrentTime();
		CString temptimestring=temptime.Format("%Y-%m-%d-%H-%M-%S");
		fprintf(filepoint,"Saved time:%s\n",temptimestring);
		fprintf(filepoint,"Pin Diameter:%.2lf\n",dPinDiameter);
		fprintf(filepoint,"Amplification Ratio:%.2lf\n",dAmplify);
		fprintf(filepoint,"Camera Name:%s\n",sLensName);
		fprintf(filepoint,"Focus:%.2lf\n",dFocusLength);
		fprintf(filepoint,"F Number:%.2lf\n",dFNumber);
		fprintf(filepoint,"WaveLength:%.2lf\n",dWaveLength);
		fprintf(filepoint,"Collimated Focus:%.2lf\n",dLength);
		fprintf(filepoint,"Array Length:%d\n",arraylength);	
		
		fprintf(filepoint,"position(T):");
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",dPOSt[i]);
		}
	

		fprintf(filepoint,"\nLSF(T):");
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",dLSFt[i]);
		}

		
		fprintf(filepoint,"\nposition(S):");
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",dPOSs[i]);
		}
		


		fprintf(filepoint,"\nLSF(S):");
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",dLSFs[i]);
		}
		
		
		fprintf(filepoint,"\nFrequence(lp/mm):");
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",dFreq[i]);
		}
		
		fprintf(filepoint,"\nMTF(T):");
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",dMTFt[i]);
		}
		
		
		fprintf(filepoint,"\nMTF(S):");
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",dMTFs[i]);
		}
		
		fprintf(filepoint,"\n");
		
		fclose(filepoint);
	}
}

void CBackgroundWnd::OnMenuitemPrint() 
{
	// TODO: Add your command handler code here
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);//������
	sendDataToMainFrm(MainFramePoint);//������ͼ������ȫ�����͸�����
	LeftFormView* LeftFormViewPoint=(LeftFormView*)GetLeftView();//�����ӿ�
	MainFramePoint->setTypedPage(LeftFormViewPoint->m_selmode.GetCurSel());//��ǰ��ͼ��ʾ�����ͱ��
	MainFramePoint->SendMessage(WM_COMMAND,ID_FILE_PRINT);//���ʹ�ӡ��Ϣ
}

void CBackgroundWnd::OnMenuitemPrintpreview() 
{
	// TODO: Add your command handler code here
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);//������
//	HWND hWnd=MainFramePoint->GetSafeHwnd(); 
	sendDataToMainFrm(MainFramePoint);//������ͼ������ȫ�����͸�����
	LeftFormView* LeftFormViewPoint=(LeftFormView*)GetLeftView();//�����ӿ�
	MainFramePoint->setTypedPage(LeftFormViewPoint->m_selmode.GetCurSel());//��ǰ��ͼ��ʾ�����ͱ��
	//MainFramePoint->SetForegroundWindow();
	MainFramePoint->SendMessage(WM_COMMAND,ID_FILE_PRINT_PREVIEW);//���ʹ�ӡԤ����Ϣ
}

void CBackgroundWnd::OnMenuConfParaset() 
{
	// TODO: Add your command handler code here
	CParaSet ParaSetDialog;
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

void CBackgroundWnd::OnMenuFreqParaset()
{
	// TODO: Add your command handler code here
	CFreqSet FreqSetDialog;
	FreqSetDialog.setAimPoint(this);
	FreqSetDialog.get6data(this);
	FreqSetDialog.DoModal();
}

void CBackgroundWnd::getDataFromRealTimeFrm(void *tempfrm)//�ú�������������RT��������������ʾ���������ݵ����⣬����ָ�����ɻ�ã����ݵĲ���ָ��ΪRT������ָ��
{
	mydelete();//�����ʾ������
	//�����������ò���
	//�����߸�������������
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	
	dPinDiameter=MainFramePoint->getdPinDiameter();
	dAmplify=MainFramePoint->getdAmplify();
	dFocusLength=MainFramePoint->getdFocusLength();
	dFNumber=MainFramePoint->getdFNumber();
	dWaveLength=MainFramePoint->getdWaveLength();
	dLength=MainFramePoint->getdLength();
	sLensName=MainFramePoint->getsLensName();
	
	//���²�����RT��������
	CRealTimeUp* RealTimeUpPoint=NULL;
	RealTimeUpPoint=(CRealTimeUp*)tempfrm;
	arraylength=RealTimeUpPoint->getarraylength();

	dFreq=new double[arraylength];
	dMTFt=new double[arraylength];
	dMTFs=new double[arraylength];
	dLSFt=new double[arraylength];
	dLSFs=new double[arraylength];
	dPOSt=new double[arraylength];
	dPOSs=new double[arraylength];
	
	setdFreq(RealTimeUpPoint->getdFreq());
	setdMTFt(RealTimeUpPoint->getdMTFt());
	setdMTFs(RealTimeUpPoint->getdMTFs());
	setdLSFt(RealTimeUpPoint->getdLSFt());
	setdLSFs(RealTimeUpPoint->getdLSFs());
	setdPOSt(RealTimeUpPoint->getdPOSt());
	setdPOSs(RealTimeUpPoint->getdPOSs());
	
	

	Calc_f();//�����ֵǰ��Ƶ�Լ���ֵ���Ƶ�����鳤��
	//Calc_Frequence();//�ú����ƺ����࣬ԭʼƵ������ֵ����setdFreq���趨
	extendMTF();//��ԭʼMTF�������ɲ�ֵMTF����
}
