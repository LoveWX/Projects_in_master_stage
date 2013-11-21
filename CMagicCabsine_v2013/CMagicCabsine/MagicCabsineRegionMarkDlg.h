#pragma once
#include "CMagicCabsineSplitData.h"
#include "afxwin.h"
#include <cv.h>

// CMagicCabsineRegionMarkDlg �Ի���

class CMagicCabsineRegionMarkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMagicCabsineRegionMarkDlg)

public:
	CMagicCabsineRegionMarkDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMagicCabsineRegionMarkDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_REGION_MARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void setSplitData(CMagicCabsineSplitData* temp){splitData = temp;}
	void setPoint(int tempX, int tempY){x=tempX,y=tempY;}

protected:
	CMagicCabsineSplitData* splitData;
	int x;
	int y;
	int tempRegionID;
	IplImage* showRegionImg;	//Ҫ��ʾ������ͼ��
	set<int> frontIDs;		//ǰ����ID��
	set<int> backIDs;		//������ID��
	BOOL isFront;			//��ʶ��ǰ�����Ƿ���ǰ��

	int color_R;
	int color_G;
	int color_B;

public:
	// ��Ǹ�������ǰ�����Ǳ���
	CComboBox m_selFrontBack;
	// ��ʾ��ɫ��
//	CStatic m_showMainColor;
//	CStatic m_showRegion;
	CSliderCtrl m_changeColorG;
	CSliderCtrl m_changeColorB;
	CSliderCtrl m_changeColorR;
	CEdit m_showSize_G;
	CEdit m_showSize_B;
	CEdit m_showSize_R;

	virtual INT_PTR DoModal();
	afx_msg void OnPaint();


	//��ʾ��ǰѡ�е�����
	void showSelectedRegion();
	//��ʾ��ɫ��
	void showMainColor();
	void initialShowData();
	afx_msg void OnCustomdrawSliderMarkregionColorR(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderMarkregionColorG(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderMarkregionColorB(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
