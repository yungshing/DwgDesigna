#pragma once
#include "resource.h"
#include "afxwin.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "BlockJig.h"

// CDlgFrame �Ի���

class CDlgFrame : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgFrame)

public:
	CDlgFrame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgFrame();

// �Ի�������
	enum { IDD = IDD_DLG_FRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_sCpbh;
	CString m_sXmdj;
	CString m_sSjs;
	CString m_sXmjd;
	CString m_sCpmc;
	CString m_sGzj;
	CAcUiComboBox m_cmbTf;
	FrameInfo m_frameInfo;
	void GetIniInfo();
	void SetIniInfo();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
