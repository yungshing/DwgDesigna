#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "excel9.h"
#include "rwExcel.h"

// CDlgDlgg �Ի���

class CDlgDlgg : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgDlgg)

public:
	CDlgDlgg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDlgg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DLGG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	CString m_sDlmc;
	CAcUiComboBox m_cmb_Dlgg;
	CListCtrl m_list_Result;

	CString m_sXlcl;//���²���
	CString m_sXlwzdm;//�������ʴ���

	vector<struct_DLGG> m_vecDlgg;

	void FindExcelInfo();
	void FillList();

	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCmbDlgg();
};
