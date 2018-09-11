#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "fcGsPreviewCtrl.h"

// CDlDwg 对话框

class CDlDwg : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlDwg)

public:
	CDlDwg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlDwg();

// 对话框数据
	enum { IDD = IDD_DLG_DL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnMouseUpListPhoto();
	DECLARE_MESSAGE_MAP()

public:
	CAcUiComboBox m_cmbL1;
	CAcUiComboBox m_cmbL2;
	CAcUiComboBox m_cmbL3;

	fcGsPreviewCtrl m_fc;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCmbL3();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnDblclkCmbL1();
};
