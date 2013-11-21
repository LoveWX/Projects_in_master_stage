// StageSet.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "StageSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SCROLL_RANGE 500
#define SCROLL_STEP 100
#define STEP_DISTANCE 0.25
#define MIN_DISTANCE 0
#define MAX_DISTANCE 50000
#define CENTER_DISTANCE 25000
/////////////////////////////////////////////////////////////////////////////
// CStageSet dialog


CStageSet::CStageSet(CWnd* pParent /*=NULL*/)
	: CDialog(CStageSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStageSet)
	m_bLocked = FALSE;
	m_dXPos = 0.0;
	m_dYPos = 0.0;
	m_dZPos = 0.0;
	m_dTPos = 0.0;
	m_dRelDis = 0.0;
	//}}AFX_DATA_INIT
}


void CStageSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStageSet)
	DDX_Check(pDX, IDC_CHECK1, m_bLocked);
	DDX_Text(pDX, IDC_EDIT1, m_dXPos);
	DDX_Text(pDX, IDC_EDIT2, m_dYPos);
	DDX_Text(pDX, IDC_EDIT3, m_dZPos);
	DDX_Text(pDX, IDC_EDIT4, m_dTPos);
	DDX_Text(pDX, IDC_EDIT5, m_dRelDis);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStageSet, CDialog)
	//{{AFX_MSG_MAP(CStageSet)
	ON_BN_CLICKED(IDC_BUTTON1, OnMove)
	ON_BN_CLICKED(IDC_BUTTON2, OnSetZero)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_BUTTON3, OnCenter)
	ON_WM_HSCROLL()
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageSet message handlers

BOOL CStageSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//将该对话框初始时获得四轴绝对位置输给对应的四个绝对位置记录量
	dXAbs=m_dXPos;
	dYAbs=m_dYPos;
	dZAbs=m_dZPos;
	dTAbs=m_dTPos;
	
	//列表框内显示文本的初始化
	pLB=(CListBox*)GetDlgItem(IDC_LIST1);
	pLB->InsertString(-1,"X轴");
	pLB->InsertString(-1,"Y轴");
	pLB->InsertString(-1,"Z轴");
	pLB->InsertString(-1,"T轴");
	//设定初始默认的列表框位置对应第三项即Z轴位置
	nListBoxPos=2;
	pLB->SetCurSel(nListBoxPos);
	
	//初始化滚动条的滚动范围
	pSB=(CScrollBar*)GetDlgItem(IDC_SCROLLBAR1);
	int nScrollRange=SCROLL_RANGE;
	pSB->SetScrollRange(0,nScrollRange);
	pSB->EnableScrollBar(ESB_ENABLE_BOTH);

    
	//设置滚动条的初始位置
	int nScrollPos=GetScrollPos(dZAbs);
	pSB->SetScrollPos(nScrollPos);

	//四电机的初始状态全部设置为锁定
	for(int i=0;i<4;i++)
		bStageLocked[i]=1;

	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CStageSet::GetScrollPos(double dPos)
{
	return (int)dPos/SCROLL_STEP;
}

void CStageSet::OnMove() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//刷新对话框
	double dMoveDis=m_dRelDis;//获得相对位移量 
	double dCurrentPos;
	switch(nListBoxPos)//获得绝对位置
	{
		case 0:
			dCurrentPos=dXAbs;
			break;
		case 1:
			dCurrentPos=dYAbs;
			break;
		case 2:
			dCurrentPos=dZAbs;
			break;
		case 3:
			dCurrentPos=dTAbs;
			break;
	}
	//获得左右两个方向容许的最大位移量
	double dLeftExtDis=MIN_DISTANCE-dCurrentPos;
	double dRightExtDis=MAX_DISTANCE-dCurrentPos;
	//修正用户输入的绝对位移量
	if(dMoveDis<dLeftExtDis)
		dMoveDis=dLeftExtDis;
	if(dMoveDis>dRightExtDis)
		dMoveDis=dRightExtDis;
	
	rc=MoveDistance(nListBoxPos,dMoveDis);//移动绝对距离
	if(!rc)
	{
			ChangeAbsPos(nListBoxPos,dMoveDis);//改变相对位置	
			ChangeRelPos(nListBoxPos,dMoveDis);//改变绝对位置
	}
}



void CStageSet::ChangeAbsPos(int nStageNum, double nMoveDistance)
{
	int nNewScrollPos;
	switch(nStageNum)//更改对应序号电机的绝对位置
	{
		case 0:
			dXAbs+=nMoveDistance;
			nNewScrollPos=GetScrollPos(dXAbs);
			break;
		case 1:
			dYAbs+=nMoveDistance;
			nNewScrollPos=GetScrollPos(dYAbs);
			break;
		case 2:
			dZAbs+=nMoveDistance;
			nNewScrollPos=GetScrollPos(dZAbs);
			break;
		case 3:
			dTAbs+=nMoveDistance;
			nNewScrollPos=GetScrollPos(dTAbs);
			break;
	}
	
	pSB->SetScrollPos(nNewScrollPos);//设置对应序号电机的绝对位置
}

void CStageSet::ChangeRelPos(int nStageNum, double nMoveDistance)
{
	switch(nStageNum)//获得对应序号电机的相对位置，并将相对位移量计算入内
	{
		case 0:
			m_dXPos+=nMoveDistance;
			break;
		case 1:
			m_dYPos+=nMoveDistance;
			break;
		case 2:
			m_dZPos+=nMoveDistance;
			break;
		case 3:
			m_dTPos+=nMoveDistance;
			break;
	}
	UpdateData(FALSE);//刷新对话框
}

long CStageSet::MoveDistance(int nStageNum, double dMoveDistance)
{
	CString cMes,cMes1,cMes2;
	int nMoveStep=GetMoveStep(dMoveDistance);//将距离转化成步数
	cMes1="SP 500,500,500,500\r\n";//设置速度
	switch(nStageNum)//依据电机序号编写电机位移代码
	{
		case(0):
			cMes2.Format("PR %d,0,0,0\r\nEN",nMoveStep);
			break;
		case(1):
			cMes2.Format("PR 0,%d,0,0\r\nEN",nMoveStep);
			break;
		case(2):
			cMes2.Format("PR 0,0,%d,0\r\nEN",nMoveStep);
			break;
		case(3):
			cMes2.Format("PR 0,0,%d,0\r\nEN",nMoveStep);
			break;
	}
	cMes=cMes1+cMes2;//电机指令合并
	
	for(int i=0;i<cMes.GetLength();i++)
		szBuffer[i]=cMes.GetAt(i);//字符串转变成字符数组

	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	hDmc=MainFramePoint->getHANDLEDMC();//获取电机控制器句柄

    rc=DMCDownloadFromBuffer(hDmc,szBuffer,NULL);//指令发送
	if(rc)
	{
		sprintf(cItemText,"Could not download a program to the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}
	
	rc=DMCCommand(hDmc,"XQ/r",szBuffer,NULL);//指令执行
	
	if(rc)
	{
		sprintf(cItemText,"Could not execute a program in the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}

	
		return 0;
}

int CStageSet::GetMoveStep(double dMoveDis)
{
	int nMoveStep=int(dMoveDis/STEP_DISTANCE);
	return nMoveStep;
}

void CStageSet::OnSetZero() 
{
	// TODO: Add your control notification handler code here
	nListBoxPos=pLB->GetCurSel();//获得当前电机序号
	switch (nListBoxPos)//相对位置清零
	{
		case 0:
			m_dXPos=0.0;
			break;
		case 1:
			m_dYPos=0.0;
			break;
		case 2:
			m_dZPos=0.0;
			break;
		case 3:
			m_dTPos=0.0;
			break;
		default:
			break;
	}
	UpdateData(FALSE);//刷新对话框
}

void CStageSet::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int nCurrentPos=pScrollBar->GetScrollPos();//获得滚动条当前位置
	double dMoveDis=SCROLL_STEP;//100
	switch(nSBCode)//分析消息
	{
		case SB_LINELEFT://左触击
			if(nCurrentPos==0)//当前已经在最左端
				return;
			else
			{
				rc=MoveDistance(nListBoxPos,(-1)*dMoveDis);//向左位移绝对量
				if(!rc)//若无错误
				{
					ChangeAbsPos(nListBoxPos,(-1)*dMoveDis);//修改位置绝对值	
					ChangeRelPos(nListBoxPos,(-1)*dMoveDis);//修改位置相对值
				}
			}
				
			break;
		case SB_LINERIGHT://右触击
			if(nCurrentPos==SCROLL_RANGE)//当前已经在最右端
				return;
			else
			{
				rc=MoveDistance(nListBoxPos,dMoveDis);//向右位移绝对量
				if(!rc)//若无错误
				{
					ChangeAbsPos(nListBoxPos,dMoveDis);//修改位置绝对值
					ChangeRelPos(nListBoxPos,dMoveDis);//修改位置相对值	
				}
			}
		
			break;

	}


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CStageSet::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//刷新对话框
	int nCheck=m_bLocked;//获得复选框状态
	switch(nCheck)
	{
		case 0://解锁
			rc=UnlockStage(nListBoxPos);//对应序号的电机进行解锁操作
			if(!rc)//若无错误	
				bStageLocked[nListBoxPos]=0;//记录当前对应序号电机的新状态
			else//若有错误
			{
				m_bLocked=!nCheck;//恢复原状态
				UpdateData(FALSE);//刷新对话框
			}
						
		case 1://锁定
			rc=LockStage(nListBoxPos);//对应序号的电机进行解锁操作
			if(!rc)//若无错误
				bStageLocked[nListBoxPos]=1;//记录当前对应序号电机的新状态
			else//若有错误
			{
				m_bLocked=!nCheck;//恢复原状态
				UpdateData(FALSE);//刷新对话框
			}
	}
}

long CStageSet::LockStage(int nStageNum)//用以对序号为nStageNum的电机进行锁定操作
{
	CString cMes;
	switch(nStageNum)//依据电机序号编写电机位移代码
	{
		case(0):
			cMes.Format("MOX\r\nEN");//X轴代码为X
			break;
		case(1):
			cMes.Format("MOY\r\nEN");//Y轴代码为Y
			break;
		case(2):
			cMes.Format("MOZ\r\nEN");//Z轴代码为Z
			break;
		case(3):
			cMes.Format("MOT\r\nEN");//转轴代码为T（待确认实现）
			break;
	}
		
	for(int i=0;i<cMes.GetLength();i++)
		szBuffer[i]=cMes.GetAt(i);//字符串转变成字符数组

	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	hDmc=MainFramePoint->getHANDLEDMC();//获取电机控制器句柄

    rc=DMCDownloadFromBuffer(hDmc,szBuffer,NULL);//指令发送
	if(rc)//指令发送失败
	{
		sprintf(cItemText,"Could not download a program to the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}
	
	rc=DMCCommand(hDmc,"XQ/r",szBuffer,NULL);//指令执行
	
	if(rc)//指令执行失败
	{
		sprintf(cItemText,"Could not execute a program in the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}

	
	return 0;//均顺利则返回0
}

long CStageSet::UnlockStage(int nStageNum)//用以对序号为nStageNum的电机进行解锁操作
{
	CString cMes;
	switch(nStageNum)//依据电机序号编写电机位移代码
	{
		case(0):
			cMes.Format("SHX\r\nEN");//X轴代码为X
			break;
		case(1):
			cMes.Format("SHY\r\nEN");//Y轴代码为Y
			break;
		case(2):
			cMes.Format("SHZ\r\nEN");//Z轴代码为Z
			break;
		case(3):
			cMes.Format("SHT\r\nEN");//转轴代码为T（待确认实现）
			break;
	}
		
	for(int i=0;i<cMes.GetLength();i++)
		szBuffer[i]=cMes.GetAt(i);//字符串转变成字符数组

	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	hDmc=MainFramePoint->getHANDLEDMC();//获取电机控制器句柄

    rc=DMCDownloadFromBuffer(hDmc,szBuffer,NULL);//指令发送
	if(rc)//指令发送失败
	{
		sprintf(cItemText,"Could not download a program to the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}
	
	rc=DMCCommand(hDmc,"XQ/r",szBuffer,NULL);//指令执行
	
	if(rc)//指令执行失败
	{
		sprintf(cItemText,"Could not execute a program in the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}

	
	return 0;//均顺利则返回0
	
	
	
}

void CStageSet::OnCenter() 
{
	// TODO: Add your control notification handler code here
	double dCurrentPos,dMoveDis;
	switch(nListBoxPos)//获当前序号电机绝对位置
	{
		case 0:
			dCurrentPos=dXAbs;
			break;
		case 1:
			dCurrentPos=dYAbs;
			break;
		case 2:
			dCurrentPos=dZAbs;
			break;
		case 3:
			dCurrentPos=dTAbs;
			break;
	}
	
	dMoveDis=CENTER_DISTANCE-dCurrentPos;//获得电机居中所需位移量

	rc=MoveDistance(nListBoxPos,dMoveDis);//移动相应距离
	if(!rc)
	{
			ChangeAbsPos(nListBoxPos,dMoveDis);//修改绝对位移值
			ChangeRelPos(nListBoxPos,dMoveDis);//修改相对位移值
	}
}

void CStageSet::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	nListBoxPos=pLB->GetCurSel();//获得当前新选择项
	int nNewScrollPos;
	switch (nListBoxPos)//获当前选项对应的绝对位置
	{
		
		case 0:
			nNewScrollPos=GetScrollPos(dXAbs);
			break;
		case 1:
			nNewScrollPos=GetScrollPos(dYAbs);
			break;
		case 2:
			nNewScrollPos=GetScrollPos(dZAbs);
			break;
		case 3:
			nNewScrollPos=GetScrollPos(dTAbs);
			break;
		default:
			break;
	}

	pSB->SetScrollPos(nNewScrollPos);//设置滚动条位置至当前选项的绝对位置
	m_bLocked=bStageLocked[nListBoxPos];//设置选择框的状态
	UpdateData(FALSE);//刷新对话框
}
