#pragma once
#include "resource.h"

// CDlgViewSet �Ի���

class CDlgViewSet : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgViewSet)

public:
	CDlgViewSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgViewSet();

// �Ի�������
	enum { IDD = IDD_DLG_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnACADKeepFocus(WPARAM, LPARAM);
	BOOL keepTheFocus();
	virtual void OnCancel();
public:
	CString m_sCurrentView;
	CAcUiComboBox m_cmb_view;
	AcDbObjectIdArray m_ViewIdArr;
	bool m_boK;
	afx_msg void OnBnClickedBtnSetview();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
