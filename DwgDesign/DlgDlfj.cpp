// DlgDlfj.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgDlfj.h"
#include "afxdialogex.h"


// CDlgDlfj 对话框

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


// CDlgDlfj 消息处理程序


void CDlgDlfj::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CDlgDlfj::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	CString sFolderPath = GetExcelFolder() + _T("DLFJ");
	FillCombo(sFolderPath, "xlsx", m_cmb_Fjlx);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
