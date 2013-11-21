// FreqSet.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "FreqSet.h"
#include "BackgroundWnd.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFreqSet dialog


CFreqSet::CFreqSet(CWnd* pParent /*=NULL*/)
	: CDialog(CFreqSet::IDD, pParent)
{
	pBackgroundWnd=NULL;
	m_dFreq1=0.0;
	m_dFreq2=0.0;
	m_dFreq3=0.0;
	m_dFreq4=0.0;
	m_dFreq5=0.0;
	m_dFreq6=0.0;
	m_dMTFt1=0.0;
	m_dMTFt2=0.0;
	m_dMTFt3=0.0;
	m_dMTFt4=0.0;
	m_dMTFt5=0.0;
	m_dMTFt6=0.0;
	m_dMTFs1=0.0;
	m_dMTFs2=0.0;
	m_dMTFs3=0.0;
	m_dMTFs4=0.0;
	m_dMTFs5=0.0;
	m_dMTFs6=0.0;
}

void CFreqSet::setAimPoint(void *pfrm/* =NULL */)
{
	pBackgroundWnd=pfrm;
}

void CFreqSet::get6data(void *pfrm/* =NULL */)
{
	double tdFreq[6],tdMTFt[6],tdMTFs[6];
	((CBackgroundWnd*)pfrm)->send6data(tdFreq,tdMTFt,tdMTFs);
	m_dFreq1=tdFreq[0];
	m_dFreq2=tdFreq[1];
	m_dFreq3=tdFreq[2];
	m_dFreq4=tdFreq[3];
	m_dFreq5=tdFreq[4];
	m_dFreq6=tdFreq[5];
	m_dMTFt1=tdMTFt[0];
	m_dMTFt2=tdMTFt[1];
	m_dMTFt3=tdMTFt[2];
	m_dMTFt4=tdMTFt[3];
	m_dMTFt5=tdMTFt[4];
	m_dMTFt6=tdMTFt[5];
	m_dMTFs1=tdMTFs[0];
	m_dMTFs2=tdMTFs[1];
	m_dMTFs3=tdMTFs[2];
	m_dMTFs4=tdMTFs[3];
	m_dMTFs5=tdMTFs[4];
	m_dMTFs6=tdMTFs[5];
}

void CFreqSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFreqSet)
	DDX_Text(pDX, IDC_FreqEDIT1, m_dFreq1);
	DDX_Text(pDX, IDC_FreqEDIT2, m_dFreq2);
	DDX_Text(pDX, IDC_FreqEDIT3, m_dFreq3);
	DDX_Text(pDX, IDC_FreqEDIT4, m_dFreq4);
	DDX_Text(pDX, IDC_FreqEDIT6, m_dFreq6);
	DDX_Text(pDX, IDC_FreqEDIT5, m_dFreq5);
	DDX_Text(pDX, IDC_MTFtEDIT1, m_dMTFt1);
	DDX_Text(pDX, IDC_MTFtEDIT2, m_dMTFt2);
	DDX_Text(pDX, IDC_MTFtEDIT3, m_dMTFt3);
	DDX_Text(pDX, IDC_MTFtEDIT4, m_dMTFt4);
	DDX_Text(pDX, IDC_MTFtEDIT5, m_dMTFt5);
	DDX_Text(pDX, IDC_MTFtEDIT6, m_dMTFt6);
	DDX_Text(pDX, IDC_MTFsEDIT1, m_dMTFs1);
	DDX_Text(pDX, IDC_MTFsEDIT2, m_dMTFs2);
	DDX_Text(pDX, IDC_MTFsEDIT3, m_dMTFs3);
	DDX_Text(pDX, IDC_MTFsEDIT4, m_dMTFs4);
	DDX_Text(pDX, IDC_MTFsEDIT5, m_dMTFs5);
	DDX_Text(pDX, IDC_MTFsEDIT6, m_dMTFs6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFreqSet, CDialog)
	//{{AFX_MSG_MAP(CFreqSet)
	ON_BN_CLICKED(IDC_BUTTONUpdate, OnBUTTONUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFreqSet message handlers

void CFreqSet::OnBUTTONUpdate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	double tempx[6],anst[6],anss[6];//»ñµÃ
	tempx[0]=m_dFreq1;
	tempx[1]=m_dFreq2;
	tempx[2]=m_dFreq3;
	tempx[3]=m_dFreq4;
	tempx[4]=m_dFreq5;
	tempx[5]=m_dFreq6;

	if(pBackgroundWnd==NULL)
		return;
	((CBackgroundWnd*)pBackgroundWnd)->CalcMTF(tempx,anst,anss);

	m_dMTFt1=anst[0];
	m_dMTFt2=anst[1];
	m_dMTFt3=anst[2];
	m_dMTFt4=anst[3];
	m_dMTFt5=anst[4];
	m_dMTFt6=anst[5];
	m_dMTFs1=anss[0];
	m_dMTFs2=anss[1];
	m_dMTFs3=anss[2];
	m_dMTFs4=anss[3];
	m_dMTFs5=anss[4];
	m_dMTFs6=anss[5];

	UpdateData(FALSE);
}
