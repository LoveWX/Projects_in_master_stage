#pragma once

#include "CMagicCabsineConfig.h"

#include <vector>
using namespace std;

// CMagicCabsineConfigDlg �Ի���

class CMagicCabsineConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMagicCabsineConfigDlg)

public:
	CMagicCabsineConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMagicCabsineConfigDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONF };

protected:
	BOOL m_bHit;
	int currentClickedItem;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CComboBox m_selectImageType;
	CListCtrl m_portionProp;
	CListCtrl m_splitMethod;
	CListCtrl m_universalProp;



	CMagicCabsineConfig *theConfig;//�������ָ��
	vector<bool> universalSelected;//ȫ�ֱ�����ѡ��
	vector<bool> portionSelected;//�ֲ�������ѡ��
	SPLIT_METHOD_NAME tempSplitMethodName;	//�ָ������

	virtual BOOL OnInitDialog();
	afx_msg void OnClickListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeComboSelectImagetype();
	afx_msg void OnBnClickedOk();
//	afx_msg void OnItemclickListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemchangedListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult);
};

