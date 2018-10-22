#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"

// CDlgPrompt �Ի���

class CDlgPrompt : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgPrompt)

public:
	CDlgPrompt(vector<Log> vec,CString sDqtxPath,CWnd* pParent = NULL);   // ��׼���캯��
	CDlgPrompt(vector<CreatWhLog> vec, CWnd* pParent = NULL);
	virtual ~CDlgPrompt();

// �Ի�������
	enum { IDD = IDD_DLG_PROMPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMap<DWORD, DWORD&, COLORREF, COLORREF&> MapItemColor;
	//������Ϣ��ʾ
	vector<Log> m_vecLog;
	CString m_sDqtx;
	CListCtrl m_list1;
	cExcel m_excel;
	int m_nRow;
	int m_nClo;
	bool bFirst;
	void ShowExcelPrompt(CString sSheetName,int nRow,int nCol);
	void RefreshList();
	void CloseExcel();

	//cratewhʱ������ʾ
	vector<CreatWhLog> m_vecCreatWh;
	bool m_bCreatWh;
	void RefreshWhList();
public:
	virtual BOOL OnInitDialog();
	afx_msg void CDlgPrompt::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	void SetItemColor(DWORD iItem, COLORREF color);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
};
