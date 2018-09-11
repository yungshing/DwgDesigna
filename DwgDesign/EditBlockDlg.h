#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "fcGsPreviewCtrl.h"

// CEditBlockDlg 对话框

class CEditBlockDlg : public CAcUiDialog
{
	DECLARE_DYNAMIC(CEditBlockDlg)

public:
	CEditBlockDlg(AcDbObjectId entId,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditBlockDlg();

// 对话框数据
	enum { IDD = IDD_DLG_EDITBLOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	AcDbObjectId m_entId;//用于删除处理块
	CAcUiComboBox m_cmbTh;//替换掉的图块选择
	fcGsPreviewCtrl m_fc;
	BOOL m_bJx;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCmbTh();
	afx_msg void OnBnClickedOk();

};
