// DlgLhxx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgLhxx.h"
#include "afxdialogex.h"


// CDlgLhxx �Ի���

IMPLEMENT_DYNAMIC(CDlgLhxx, CAcUiDialog)

CDlgLhxx::CDlgLhxx(CWnd* pParent /*=NULL*/)
: CAcUiDialog(CDlgLhxx::IDD, pParent)
{

}

CDlgLhxx::~CDlgLhxx()
{
}

void CDlgLhxx::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLhxx, CAcUiDialog)
	ON_BN_CLICKED(123, bnclick)
	ON_BN_CLICKED(IDOK, &CDlgLhxx::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLhxx ��Ϣ�������


BOOL CDlgLhxx::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ�� 
// 	btn = new CButton;
// 	btn->Create(_T(" "), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,CRect(0, 0, 100, 100), this, 123);

// 	Edit = new CEdit;
// 	Edit->Create(WS_BORDER|ES_AUTOHSCROLL, CRect(0, 60, 100, 80), this, 100082);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CDlgLhxx::bnclick()
{
	AfxMessageBox(_T("click button"));
}

void CDlgLhxx::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}
