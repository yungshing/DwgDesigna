// DlgProresstest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgProresstest.h"
#include "afxdialogex.h"


// CDlgProresstest �Ի���

IMPLEMENT_DYNAMIC(CDlgProresstest, CDialogEx)

CDlgProresstest::CDlgProresstest(CWnd* pParent /*=NULL*/)
: CAcUiDialog(CDlgProresstest::IDD, pParent)
{

}

CDlgProresstest::~CDlgProresstest()
{
}

void CDlgProresstest::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}


BEGIN_MESSAGE_MAP(CDlgProresstest, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
END_MESSAGE_MAP()

LRESULT CDlgProresstest::OnAcadKeepFocus(WPARAM, LPARAM) {
	return (TRUE);
}

void CDlgProresstest::setpos(int nPos)
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	m_progress.SetPos(nPos);
}


BOOL CDlgProresstest::Create(CWnd* pParentWnd /*= NULL*/)
{
	return CAcUiDialog::Create(CDlgProresstest::IDD, pParentWnd);
}

// CDlgProresstest ��Ϣ�������


BOOL CDlgProresstest::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	CenterWindow(acedGetAcadDwgView());
	m_progress.SetRange(0, 100);
	m_progress.SetStep(1);
	m_progress.SetPos(0);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
