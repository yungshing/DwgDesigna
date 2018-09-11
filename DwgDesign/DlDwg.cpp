// DlDwg.cpp : 实现文件
//

#include "stdafx.h"
#include "DlDwg.h"
#include "afxdialogex.h"

// CDlDwg 对话框

IMPLEMENT_DYNAMIC(CDlDwg, CAcUiDialog)

CDlDwg::CDlDwg(CWnd* pParent /*=NULL*/)
: CAcUiDialog(CDlDwg::IDD, pParent)
{

}

CDlDwg::~CDlDwg()
{
}

void CDlDwg::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_L1, m_cmbL1);
	DDX_Control(pDX, IDC_CMB_L2, m_cmbL2);
	DDX_Control(pDX, IDC_CMB_L3, m_cmbL3);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_fc);
}

BEGIN_MESSAGE_MAP(CDlDwg, CAcUiDialog)
	ON_BN_CLICKED(IDOK, &CDlDwg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_CMB_L3, &CDlDwg::OnCbnSelchangeCmbL3)
//	ON_NOTIFY(NM_CLICK, IDC_CMB_L1, &CDlDwg::OnMouseUpListPhoto)
	ON_CBN_DBLCLK(IDC_CMB_L1, &CDlDwg::OnCbnDblclkCmbL1)
	ON_BN_CLICKED(IDC_CMB_L1,&CDlDwg::OnMouseUpListPhoto)
END_MESSAGE_MAP()

// CDlDwg 消息处理程序

BOOL CDlDwg::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CIniFile ini(GetIniPath());
	CString sL1, sL2,sL3;
	ini.GetValueOfKey(_T("DL"), _T("L1"), sL1);
	ini.GetValueOfKey(_T("DL"), _T("L2"), sL2);
	ini.GetValueOfKey(_T("DL"), _T("L3"), sL3);
	FillCombo(m_cmbL1, sL1);
	FillCombo(m_cmbL2, sL2);
	FillCombo(m_cmbL3, sL3);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CDlDwg::OnCbnSelchangeCmbL3()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString sTemp;
	int a =m_cmbL3.GetCurSel();
	m_cmbL3.GetLBString(a, sTemp);
	CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), sTemp);
	m_fc.Clear();
	m_fc.Init(acdbHostApplicationServices()->workingDatabase(), sTemp);

}

void CDlDwg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	BeginEditorCommand();
	CString sBlockName/*=_T("低频一分三")*/;
	GetDlgItemText(IDC_CMB_L3, sBlockName);
	AcGePoint3d ptInsert;
	bool b=CGetInputUtil::GetPoint(_T("\n选择模版插入点"), ptInsert);
	if (!b)
	{
		CompleteEditorCommand();
		return;
	}
	AcDbObjectId idBlock = CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), sBlockName);
	AcDbObjectId idInsert = CBlockUtil::InsertBlockRef(idBlock, ptInsert);
	AcDbBlockReference *pRef = NULL;
	acdbOpenObject(pRef, idInsert, AcDb::kForWrite);
	AcDbVoidPtrArray ptArr;
	pRef->explode(ptArr);
	pRef->erase();
	pRef->close();
	int iNum = ptArr.length();
	for (int i = 0; i < iNum; i++)
	{
		ACHAR *cName;
		AcDbEntity*pEnt = static_cast<AcDbEntity*>(ptArr[i]);

		AcDbBlockReference *pRef = static_cast<AcDbBlockReference*>(pEnt);
		AcDbBlockTableRecord *pRec = NULL;
		AcDbObjectId idTemp = pRef->blockTableRecord();
		Acad::ErrorStatus es;
		es = acdbOpenObject(pRec, idTemp, AcDb::kForWrite);
		if (es == eOk)
		{
			pRec->getName(cName);
			CString sName;
			sName.Format(_T("%s"), cName);
			std::vector<CString> vecStr;
			CStringUtil::Split(sName, _T("-"), vecStr, false);
			size_t si = vecStr.size();
			if (si == 2)
			{
				CDwgDatabaseUtil::SetXdata(_T("模版图块"), _T("是"), pEnt);
			}
			if (si == 1)
			{
				CDwgDatabaseUtil::SetXdata(_T("电缆图块"), _T("是"), pEnt);
			}
			pRec->close();
		}
		CDwgDatabaseUtil::PostToModelSpace(pEnt);
	}
	CAcUiDialog::OnOK();
}

void CDlDwg::OnMouseUpListPhoto()
{
	AfxMessageBox(_T("asd"));
}

void CDlDwg::OnCbnDblclkCmbL1()
{
	// TODO:  在此添加控件通知处理程序代码
	AfxMessageBox(_T("ddd"));
}
