#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "excel9.h"
#include "rwExcel.h"

// CDlgLjq 对话框


class CDlgLjq : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgLjq)

public:
	CDlgLjq(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLjq();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_LJQ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString m_sLjqmc;//连接器名称
	CAcUiComboBox m_cmb_Ljqlx;//类型
	CListCtrl m_list_Result;//list容器

	CString m_sLjqxh;//连接器型号
	CString m_sWzdm;//物资代码

	vector<struct_LJQ> m_vecLjq;
	void FindExcelInfo();
	void FillList();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCmbLjqlx();
};
