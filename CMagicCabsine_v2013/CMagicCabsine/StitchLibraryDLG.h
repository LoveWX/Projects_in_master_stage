#pragma once

#include "CMagicCabsineStitchLibrary.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "CGenerateSmallImage.h"
// SitchLibraryDLG 对话框


class StitchLibraryDLG : public CDialogEx
{
	DECLARE_DYNAMIC(StitchLibraryDLG)
public:
	CMagicCabsineStitchLibrary m_stitchlib;
	CGenerateSmallImage		   m_gsi;
	IplImage*	m_showImage;
public:
	StitchLibraryDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~StitchLibraryDLG();

	virtual BOOL OnInitDialog();
public:
	void CreateList();
	void UpdateList();
	void InitSliderAndEdit();
	int GetParaFromList(int nItem,TempParaVal& tpv);
	void UpdateSlider(TempParaVal tpv);
	void UpdateEdit(TempParaVal tpv);
	void UpdateImage(TempParaVal tpv);
	void ShowImage(IplImage* img);
	void GetParaFromSlider(TempParaVal& tpv);

	// 对话框数据
	enum { IDD = IDD_DIALOG_STITCH_LIBRARY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	static const int SLD_UP_DSY = 20;
	static const int SLD_UP_LEN = 20;
	static const int SLD_UP_CHA = 10;
	static const int SLD_UP_THETA = 20;
	static const int SLD_UP_BETA = 20;
	CListCtrl m_listStitch;
	CSliderCtrl m_sliderDensity;
	CSliderCtrl m_sliderLength;
	CSliderCtrl m_sliderChaos;
	CSliderCtrl m_sliderTheta;
	CSliderCtrl m_sliderBeta;
	STITCH_TYPE m_type;
	CEdit m_editName;
	CEdit m_editDensity;
	CEdit m_editLength;
	CEdit m_editChaos;
	CEdit m_editTheta;
	CEdit m_editBeta;
	CButton m_btnAddStitch;
	CButton m_btnDeleteStitch;
	CButton m_btnModifyStitch;
	afx_msg void OnNMClickListStitch(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderStitchdensity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderStitchlength(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderStitchchaos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderStitchtheta(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderStitchbeta(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAddstitch();
	afx_msg void OnBnClickedButtonDeletestitch();
	
	afx_msg void OnBnClickedButtonModifystitch();
};
