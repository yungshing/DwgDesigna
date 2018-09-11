#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"

// CDlgAutoCreat 对话框

class CDlgAutoCreat : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgAutoCreat)

public:
	CDlgAutoCreat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAutoCreat();

// 对话框数据
	enum { IDD = IDD_DLG_AUTOCREAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	enum EmLocation
	{
		z1=1,
		z2,
		z3,
		z4,
		z5,
		y1,
		y2,
		y3,
		y4,
		y5,
	};
	CString m_sExcelPath;
public:
	BOOL CreatBlcok(CString sBlockName,CString sZ1Name,CString sZ2Name,CString sZ3Name,CString sZ4Name,CString sZ5Name,
		CString sY1Name,CString sY2Name,CString sY3Name,CString sY4Name,CString sY5Name);
public:
	afx_msg void OnBnClickedSelectPath();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
