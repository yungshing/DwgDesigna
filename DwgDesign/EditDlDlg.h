#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"

// CEditDlDlg 对话框

class CEditDlDlg : public CAcUiDialog
{
	DECLARE_DYNAMIC(CEditDlDlg)

public:
	CEditDlDlg(AcDbObjectId idEnt,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditDlDlg();

// 对话框数据
	enum { IDD = IDD_DLG_EDITDL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	AcDbObjectId m_idEnt;
	CAcUiComboBox m_cmbDlgg;
	CAcUiComboBox m_cmbDydj;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
