// DlgDlfj.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgDlfj.h"
#include "afxdialogex.h"


// CDlgDlfj �Ի���

IMPLEMENT_DYNAMIC(CDlgDlfj, CAcUiDialog)

CDlgDlfj::CDlgDlfj(CWnd* pParent /*=NULL*/)
	: CAcUiDialog(IDD_DLG_DLFJ, pParent)
{

}

CDlgDlfj::~CDlgDlfj()
{
}

void CDlgDlfj::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FJMC, m_sFjmc);
	DDX_Control(pDX, IDC_CMB_FJLX, m_cmb_Fjlx);
}


BEGIN_MESSAGE_MAP(CDlgDlfj, CAcUiDialog)
	ON_BN_CLICKED(IDOK, &CDlgDlfj::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgDlfj ��Ϣ�������


void CDlgDlfj::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CDlgDlfj::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	CString sFolderPath = GetExcelFolder() + _T("DLFJ");
	FillCombo(sFolderPath, "xlsx", m_cmb_Fjlx);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
