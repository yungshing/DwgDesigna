#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "excel9.h"
#include "rwExcel.h"

// CDlgLjq �Ի���


class CDlgLjq : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgLjq)

public:
	CDlgLjq(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLjq();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_LJQ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString m_sLjqmc;//����������
	CAcUiComboBox m_cmb_Ljqlx;//����
	CListCtrl m_list_Result;//list����

	CString m_sLjqxh;//�������ͺ�
	CString m_sWzdm;//���ʴ���

	vector<struct_LJQ> m_vecLjq;
	void FindExcelInfo();
	void FillList();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCmbLjqlx();
};
