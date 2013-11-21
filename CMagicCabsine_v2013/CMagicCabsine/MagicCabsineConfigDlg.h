#pragma once

#include "CMagicCabsineConfig.h"

#include <vector>
using namespace std;

// CMagicCabsineConfigDlg 对话框

class CMagicCabsineConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMagicCabsineConfigDlg)

public:
	CMagicCabsineConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMagicCabsineConfigDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CONF };

protected:
	BOOL m_bHit;
	int currentClickedItem;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CComboBox m_selectImageType;
	CListCtrl m_portionProp;
	CListCtrl m_splitMethod;
	CListCtrl m_universalProp;



	CMagicCabsineConfig *theConfig;//配置类的指针
	vector<bool> universalSelected;//全局变量的选择
	vector<bool> portionSelected;//局部变量的选择
	SPLIT_METHOD_NAME tempSplitMethodName;	//分割方法名称

	virtual BOOL OnInitDialog();
	afx_msg void OnClickListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeComboSelectImagetype();
	afx_msg void OnBnClickedOk();
//	afx_msg void OnItemclickListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemchangedListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult);
};

