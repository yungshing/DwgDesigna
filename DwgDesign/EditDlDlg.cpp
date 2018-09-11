// EditDlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EditDlDlg.h"
#include "afxdialogex.h"


// CEditDlDlg 对话框

IMPLEMENT_DYNAMIC(CEditDlDlg, CAcUiDialog)

CEditDlDlg::CEditDlDlg(AcDbObjectId idEnt,CWnd* pParent /*=NULL*/)
: CAcUiDialog(CEditDlDlg::IDD, pParent)
{
	m_idEnt = idEnt;
}

CEditDlDlg::~CEditDlDlg()
{
}

void CEditDlDlg::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_DLGG, m_cmbDlgg);
	DDX_Control(pDX, IDC_CMB_DYDJ, m_cmbDydj);
}


BEGIN_MESSAGE_MAP(CEditDlDlg, CAcUiDialog)
	ON_BN_CLICKED(IDOK, &CEditDlDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditDlDlg 消息处理程序


BOOL CEditDlDlg::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	CIniFile ini(GetIniPath());
	CString sTemp;
	ini.GetValueOfKey(_T("DL"), _T("DLGG"), sTemp);
	FillCombo(m_cmbDlgg, sTemp, _T(","));
	ini.GetValueOfKey(_T("DL"), _T("DYDJ"), sTemp);
	FillCombo(m_cmbDydj, sTemp, _T(","));
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CEditDlDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString DLGG, DYDJ;
	GetDlgItemText(IDC_CMB_DLGG, DLGG);
	GetDlgItemText(IDC_CMB_DYDJ, DYDJ);
	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es;
	es = acdbOpenAcDbEntity(pEnt, m_idEnt, AcDb::kForWrite);
	if (es==eOk)
	{
		CDwgDatabaseUtil::SetXdata(_T("电缆规格"), DLGG, pEnt);
		CDwgDatabaseUtil::SetXdata(_T("电压等级"), DYDJ, pEnt);
		pEnt->close();
	}
	CAcUiDialog::OnOK();
}
