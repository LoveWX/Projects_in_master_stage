#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "CMagicCabsineSimuLineSet.h"
#include "CMagicCabsineStitchLibrary.h"
#include "CGenerateSmallImage.h"


// RegionModifyDLG 对话框

class RegionModifyDLG : public CDialogEx
{
	DECLARE_DYNAMIC(RegionModifyDLG)

public:
	RegionModifyDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RegionModifyDLG();

	void InitCombox();
	void InitSlider();
	void InitTPV();
	void UpdateFromTPV(TempParaVal tpv);
	void UpdateSlider(TempParaVal tpv);
	void UpdateEdit(TempParaVal tpv);
	void GetParaFromSlider(TempParaVal& tpv);

	void ShowMaskImage();

	void ShowStitchImage(TempParaVal tpv);

// 对话框数据
	enum { IDD = IDD_DIALOG_REGION_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMagicCabsineStitchLibrary		m_stitchlib;
	CGenerateSmallImage				m_gsi;
	IplImage*	m_showImageMask;
	IplImage*	m_showImageStitch;
	TempParaVal m_tpv;
	STITCH_TYPE m_type;
	int m_regID;
	int m_levelID;
	SimuLineSet* m_SlsPtr;

	int RM_SLD_UP_DSY;
	int RM_SLD_UP_LEN;
	int RM_SLD_UP_CHA;

	CEdit m_editLevelID;
	CEdit m_editRegionID;
	CEdit m_editRegionColor;
	CComboBox m_comboType;
	CEdit m_editDensity;
	CEdit m_editLength;
	CEdit m_editChaos;
	CSliderCtrl m_sliderDensity;
	CSliderCtrl m_sliderLength;
	CSliderCtrl m_sliderChaos;

	virtual BOOL OnInitDialog();
	afx_msg void OnNMReleasedcaptureSliderRegiondensity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderRegionlength(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderRegionchaos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboStitchtype();
};
