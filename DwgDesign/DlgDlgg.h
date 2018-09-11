#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "excel9.h"
#include "rwExcel.h"

// CDlgDlgg 对话框

class CDlgDlgg : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgDlgg)

public:
	CDlgDlgg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDlgg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DLGG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	CString m_sDlmc;
	CAcUiComboBox m_cmb_Dlgg;
	CListCtrl m_list_Result;

	CString m_sXlcl;//线缆材料
	CString m_sXlwzdm;//线缆物资代码

	vector<struct_DLGG> m_vecDlgg;

	void FindExcelInfo();
	void FillList();

	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCmbDlgg();
};
