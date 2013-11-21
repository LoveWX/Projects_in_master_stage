#pragma once
#include "CMagicCabsineSplitData.h"
#include "afxwin.h"
#include <cv.h>

// CMagicCabsineRegionMarkDlg 对话框

class CMagicCabsineRegionMarkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMagicCabsineRegionMarkDlg)

public:
	CMagicCabsineRegionMarkDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMagicCabsineRegionMarkDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_REGION_MARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	IplImage* showRegionImg;	//要显示的区域图像
	set<int> frontIDs;		//前景的ID号
	set<int> backIDs;		//背景的ID号
	BOOL isFront;			//标识当前区域是否是前景

	int color_R;
	int color_G;
	int color_B;

public:
	// 标记该区域是前景还是背景
	CComboBox m_selFrontBack;
	// 显示主色调
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


	//显示当前选中的区域
	void showSelectedRegion();
	//显示主色调
	void showMainColor();
	void initialShowData();
	afx_msg void OnCustomdrawSliderMarkregionColorR(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderMarkregionColorG(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderMarkregionColorB(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
