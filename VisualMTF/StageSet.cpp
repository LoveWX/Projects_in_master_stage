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
	//���öԻ����ʼʱ����������λ�������Ӧ���ĸ�����λ�ü�¼��
	dXAbs=m_dXPos;
	dYAbs=m_dYPos;
	dZAbs=m_dZPos;
	dTAbs=m_dTPos;
	
	//�б������ʾ�ı��ĳ�ʼ��
	pLB=(CListBox*)GetDlgItem(IDC_LIST1);
	pLB->InsertString(-1,"X��");
	pLB->InsertString(-1,"Y��");
	pLB->InsertString(-1,"Z��");
	pLB->InsertString(-1,"T��");
	//�趨��ʼĬ�ϵ��б��λ�ö�Ӧ�����Z��λ��
	nListBoxPos=2;
	pLB->SetCurSel(nListBoxPos);
	
	//��ʼ���������Ĺ�����Χ
	pSB=(CScrollBar*)GetDlgItem(IDC_SCROLLBAR1);
	int nScrollRange=SCROLL_RANGE;
	pSB->SetScrollRange(0,nScrollRange);
	pSB->EnableScrollBar(ESB_ENABLE_BOTH);

    
	//���ù������ĳ�ʼλ��
	int nScrollPos=GetScrollPos(dZAbs);
	pSB->SetScrollPos(nScrollPos);

	//�ĵ���ĳ�ʼ״̬ȫ������Ϊ����
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
	UpdateData(TRUE);//ˢ�¶Ի���
	double dMoveDis=m_dRelDis;//������λ���� 
	double dCurrentPos;
	switch(nListBoxPos)//��þ���λ��
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
	//�����������������������λ����
	double dLeftExtDis=MIN_DISTANCE-dCurrentPos;
	double dRightExtDis=MAX_DISTANCE-dCurrentPos;
	//�����û�����ľ���λ����
	if(dMoveDis<dLeftExtDis)
		dMoveDis=dLeftExtDis;
	if(dMoveDis>dRightExtDis)
		dMoveDis=dRightExtDis;
	
	rc=MoveDistance(nListBoxPos,dMoveDis);//�ƶ����Ծ���
	if(!rc)
	{
			ChangeAbsPos(nListBoxPos,dMoveDis);//�ı����λ��	
			ChangeRelPos(nListBoxPos,dMoveDis);//�ı����λ��
	}
}



void CStageSet::ChangeAbsPos(int nStageNum, double nMoveDistance)
{
	int nNewScrollPos;
	switch(nStageNum)//���Ķ�Ӧ��ŵ���ľ���λ��
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
	
	pSB->SetScrollPos(nNewScrollPos);//���ö�Ӧ��ŵ���ľ���λ��
}

void CStageSet::ChangeRelPos(int nStageNum, double nMoveDistance)
{
	switch(nStageNum)//��ö�Ӧ��ŵ�������λ�ã��������λ������������
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
	UpdateData(FALSE);//ˢ�¶Ի���
}

long CStageSet::MoveDistance(int nStageNum, double dMoveDistance)
{
	CString cMes,cMes1,cMes2;
	int nMoveStep=GetMoveStep(dMoveDistance);//������ת���ɲ���
	cMes1="SP 500,500,500,500\r\n";//�����ٶ�
	switch(nStageNum)//���ݵ����ű�д���λ�ƴ���
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
	cMes=cMes1+cMes2;//���ָ��ϲ�
	
	for(int i=0;i<cMes.GetLength();i++)
		szBuffer[i]=cMes.GetAt(i);//�ַ���ת����ַ�����

	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	hDmc=MainFramePoint->getHANDLEDMC();//��ȡ������������

    rc=DMCDownloadFromBuffer(hDmc,szBuffer,NULL);//ָ���
	if(rc)
	{
		sprintf(cItemText,"Could not download a program to the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}
	
	rc=DMCCommand(hDmc,"XQ/r",szBuffer,NULL);//ָ��ִ��
	
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
	nListBoxPos=pLB->GetCurSel();//��õ�ǰ������
	switch (nListBoxPos)//���λ������
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
	UpdateData(FALSE);//ˢ�¶Ի���
}

void CStageSet::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int nCurrentPos=pScrollBar->GetScrollPos();//��ù�������ǰλ��
	double dMoveDis=SCROLL_STEP;//100
	switch(nSBCode)//������Ϣ
	{
		case SB_LINELEFT://�󴥻�
			if(nCurrentPos==0)//��ǰ�Ѿ��������
				return;
			else
			{
				rc=MoveDistance(nListBoxPos,(-1)*dMoveDis);//����λ�ƾ�����
				if(!rc)//���޴���
				{
					ChangeAbsPos(nListBoxPos,(-1)*dMoveDis);//�޸�λ�þ���ֵ	
					ChangeRelPos(nListBoxPos,(-1)*dMoveDis);//�޸�λ�����ֵ
				}
			}
				
			break;
		case SB_LINERIGHT://�Ҵ���
			if(nCurrentPos==SCROLL_RANGE)//��ǰ�Ѿ������Ҷ�
				return;
			else
			{
				rc=MoveDistance(nListBoxPos,dMoveDis);//����λ�ƾ�����
				if(!rc)//���޴���
				{
					ChangeAbsPos(nListBoxPos,dMoveDis);//�޸�λ�þ���ֵ
					ChangeRelPos(nListBoxPos,dMoveDis);//�޸�λ�����ֵ	
				}
			}
		
			break;

	}


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CStageSet::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//ˢ�¶Ի���
	int nCheck=m_bLocked;//��ø�ѡ��״̬
	switch(nCheck)
	{
		case 0://����
			rc=UnlockStage(nListBoxPos);//��Ӧ��ŵĵ�����н�������
			if(!rc)//���޴���	
				bStageLocked[nListBoxPos]=0;//��¼��ǰ��Ӧ��ŵ������״̬
			else//���д���
			{
				m_bLocked=!nCheck;//�ָ�ԭ״̬
				UpdateData(FALSE);//ˢ�¶Ի���
			}
						
		case 1://����
			rc=LockStage(nListBoxPos);//��Ӧ��ŵĵ�����н�������
			if(!rc)//���޴���
				bStageLocked[nListBoxPos]=1;//��¼��ǰ��Ӧ��ŵ������״̬
			else//���д���
			{
				m_bLocked=!nCheck;//�ָ�ԭ״̬
				UpdateData(FALSE);//ˢ�¶Ի���
			}
	}
}

long CStageSet::LockStage(int nStageNum)//���Զ����ΪnStageNum�ĵ��������������
{
	CString cMes;
	switch(nStageNum)//���ݵ����ű�д���λ�ƴ���
	{
		case(0):
			cMes.Format("MOX\r\nEN");//X�����ΪX
			break;
		case(1):
			cMes.Format("MOY\r\nEN");//Y�����ΪY
			break;
		case(2):
			cMes.Format("MOZ\r\nEN");//Z�����ΪZ
			break;
		case(3):
			cMes.Format("MOT\r\nEN");//ת�����ΪT����ȷ��ʵ�֣�
			break;
	}
		
	for(int i=0;i<cMes.GetLength();i++)
		szBuffer[i]=cMes.GetAt(i);//�ַ���ת����ַ�����

	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	hDmc=MainFramePoint->getHANDLEDMC();//��ȡ������������

    rc=DMCDownloadFromBuffer(hDmc,szBuffer,NULL);//ָ���
	if(rc)//ָ���ʧ��
	{
		sprintf(cItemText,"Could not download a program to the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}
	
	rc=DMCCommand(hDmc,"XQ/r",szBuffer,NULL);//ָ��ִ��
	
	if(rc)//ָ��ִ��ʧ��
	{
		sprintf(cItemText,"Could not execute a program in the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}

	
	return 0;//��˳���򷵻�0
}

long CStageSet::UnlockStage(int nStageNum)//���Զ����ΪnStageNum�ĵ�����н�������
{
	CString cMes;
	switch(nStageNum)//���ݵ����ű�д���λ�ƴ���
	{
		case(0):
			cMes.Format("SHX\r\nEN");//X�����ΪX
			break;
		case(1):
			cMes.Format("SHY\r\nEN");//Y�����ΪY
			break;
		case(2):
			cMes.Format("SHZ\r\nEN");//Z�����ΪZ
			break;
		case(3):
			cMes.Format("SHT\r\nEN");//ת�����ΪT����ȷ��ʵ�֣�
			break;
	}
		
	for(int i=0;i<cMes.GetLength();i++)
		szBuffer[i]=cMes.GetAt(i);//�ַ���ת����ַ�����

	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	hDmc=MainFramePoint->getHANDLEDMC();//��ȡ������������

    rc=DMCDownloadFromBuffer(hDmc,szBuffer,NULL);//ָ���
	if(rc)//ָ���ʧ��
	{
		sprintf(cItemText,"Could not download a program to the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}
	
	rc=DMCCommand(hDmc,"XQ/r",szBuffer,NULL);//ָ��ִ��
	
	if(rc)//ָ��ִ��ʧ��
	{
		sprintf(cItemText,"Could not execute a program in the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}

	
	return 0;//��˳���򷵻�0
	
	
	
}

void CStageSet::OnCenter() 
{
	// TODO: Add your control notification handler code here
	double dCurrentPos,dMoveDis;
	switch(nListBoxPos)//��ǰ��ŵ������λ��
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
	
	dMoveDis=CENTER_DISTANCE-dCurrentPos;//��õ����������λ����

	rc=MoveDistance(nListBoxPos,dMoveDis);//�ƶ���Ӧ����
	if(!rc)
	{
			ChangeAbsPos(nListBoxPos,dMoveDis);//�޸ľ���λ��ֵ
			ChangeRelPos(nListBoxPos,dMoveDis);//�޸����λ��ֵ
	}
}

void CStageSet::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	nListBoxPos=pLB->GetCurSel();//��õ�ǰ��ѡ����
	int nNewScrollPos;
	switch (nListBoxPos)//��ǰѡ���Ӧ�ľ���λ��
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

	pSB->SetScrollPos(nNewScrollPos);//���ù�����λ������ǰѡ��ľ���λ��
	m_bLocked=bStageLocked[nListBoxPos];//����ѡ����״̬
	UpdateData(FALSE);//ˢ�¶Ի���
}
