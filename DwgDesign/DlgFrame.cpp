// DlgFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgFrame.h"
#include "afxdialogex.h"


// CDlgFrame 对话框

IMPLEMENT_DYNAMIC(CDlgFrame, CAcUiDialog)

CDlgFrame::CDlgFrame(CWnd* pParent /*=NULL*/)
: CAcUiDialog(CDlgFrame::IDD, pParent)
{

}

CDlgFrame::~CDlgFrame()
{
}

void CDlgFrame::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CPBH, m_sCpbh);
	DDX_Text(pDX, IDC_EDIT_XMDJ, m_sXmdj);
	DDX_Text(pDX, IDC_EDIT_SHS, m_sSjs);
	DDX_Text(pDX, IDC_EDIT_XMJD, m_sXmjd);
	DDX_Text(pDX, IDC_EDIT_CPMC, m_sCpmc);
	DDX_Text(pDX, IDC_EDIT_GZJ, m_sGzj);
	DDX_Control(pDX, IDC_COMBO_TF, m_cmbTf);
}


BEGIN_MESSAGE_MAP(CDlgFrame, CAcUiDialog)
	ON_BN_CLICKED(IDOK, &CDlgFrame::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgFrame 消息处理程序


void CDlgFrame::GetIniInfo()
{
	CIniFile ini(GetIniPath());
//	ini.GetValueOfKey(_T("FRAME"), _T("CPBH"), m_sCpbh);
	ini.GetValueOfKey(_T("FRAME"), _T("XMDJ"), m_sXmdj);
	ini.GetValueOfKey(_T("FRAME"), _T("SJS"), m_sSjs);
	ini.GetValueOfKey(_T("FRAME"), _T("XMJD"), m_sXmjd);
	ini.GetValueOfKey(_T("FRAME"), _T("CPMC"), m_sCpmc);
	ini.GetValueOfKey(_T("FRAME"), _T("GZJ"), m_sGzj);
	UpdateData(FALSE);
}


void CDlgFrame::SetIniInfo()
{
	CIniFile ini(GetIniPath());
	ini.SetValueOfKey(_T("FRAME"), _T("CPBH"), m_sCpbh);
	ini.SetValueOfKey(_T("FRAME"), _T("XMDJ"), m_sXmdj);
	ini.SetValueOfKey(_T("FRAME"), _T("SJS"), m_sSjs);
	ini.SetValueOfKey(_T("FRAME"), _T("XMJD"), m_sXmjd);
	ini.SetValueOfKey(_T("FRAME"), _T("CPMC"), m_sCpmc);
	ini.SetValueOfKey(_T("FRAME"), _T("GZJ"), m_sGzj);
}


BOOL CDlgFrame::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	GetIniInfo();
	CIniFile ini(GetIniPath());
	CString sTemp;
	ini.GetValueOfKey(_T("FRAME"), _T("TFBX"), sTemp);
	FillCombo(m_cmbTf, sTemp);
	ini.GetValueOfKey(_T("FRAME"), _T("TF"), sTemp);
	SetDlgItemText(IDC_COMBO_TF, sTemp);

 	GetDataBaseXdata(_T("BM"), m_sCpbh);
	// TODO:  在此添加额外的初始化
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgFrame::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetIniInfo();
	CString sTf;
	GetDlgItemText(IDC_COMBO_TF, sTf);
	CIniFile ini(GetIniPath());
	ini.SetValueOfKey(_T("FRAME"), _T("TF"), sTf);
	BeginEditorCommand();
	CString sBlockName;
	sBlockName = _T("FRAME2-") + sTf;
	AcDbObjectId idBlock=CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), sBlockName);

	m_frameInfo.CPBH = m_sCpbh;
	m_frameInfo.XMDJ = m_sXmdj;
	m_frameInfo.SJS = m_sSjs+_T(" ")+GetTimer2();
	m_frameInfo.XMJD = m_sXmjd;
	m_frameInfo.CPMC = m_sCpmc;
	m_frameInfo.GZJ = m_sGzj;


	if (idBlock==AcDbObjectId::kNull)
	{
		AfxMessageBox(_T("图框模版未找到"));
		CompleteEditorCommand(TRUE);
		return;
	}
	CBlockJig jig;
	bool b =jig.doIt(idBlock,m_frameInfo);
	if (b)
	{
		CompleteEditorCommand(FALSE);
		CAcUiDialog::OnOK();
		return;
	}
	else
	{
		CompleteEditorCommand(TRUE);
		return;
	}
	
}
