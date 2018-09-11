#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"

// CEditDlDlg �Ի���

class CEditDlDlg : public CAcUiDialog
{
	DECLARE_DYNAMIC(CEditDlDlg)

public:
	CEditDlDlg(AcDbObjectId idEnt,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditDlDlg();

// �Ի�������
	enum { IDD = IDD_DLG_EDITDL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	AcDbObjectId m_idEnt;
	CAcUiComboBox m_cmbDlgg;
	CAcUiComboBox m_cmbDydj;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
