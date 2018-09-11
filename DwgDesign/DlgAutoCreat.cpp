// DlgAutoCreat.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgAutoCreat.h"
#include "afxdialogex.h"


// CDlgAutoCreat 对话框

IMPLEMENT_DYNAMIC(CDlgAutoCreat, CAcUiDialog)

CDlgAutoCreat::CDlgAutoCreat(CWnd* pParent /*=NULL*/)
: CAcUiDialog(CDlgAutoCreat::IDD, pParent)
{

}

CDlgAutoCreat::~CDlgAutoCreat()
{
}

void CDlgAutoCreat::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EXCELPATH, m_sExcelPath);
}


BEGIN_MESSAGE_MAP(CDlgAutoCreat, CAcUiDialog)
	ON_BN_CLICKED(IDC_BTN_SELECTPATH, &CDlgAutoCreat::OnBnClickedSelectPath)
	ON_BN_CLICKED(IDOK, &CDlgAutoCreat::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgAutoCreat 消息处理程序


void CDlgAutoCreat::OnBnClickedSelectPath()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0, _T("格式1(*.xls) |*.xls|格式2(*.xlsx) |*.xlsx||"), acedGetAcadFrame());
	if (importDlg.DoModal()==IDOK)
	{
		m_sExcelPath = importDlg.GetPathName();
	}
	else
	{
		return;
	}
	UpdateData(FALSE);
	return;
}

BOOL CDlgAutoCreat::CreatBlcok(CString sBlockName,CString sZ1Name, CString sZ2Name, CString sZ3Name, CString sZ4Name, CString sZ5Name,
	CString sY1Name, CString sY2Name, CString sY3Name, CString sY4Name, CString sY5Name)
{	
	AcGePoint3d ptInsert;
	bool b=CGetInputUtil::GetPoint(_T("\n选择模版插入点"), ptInsert);
	if (!b)
	{
		return FALSE;
	}
	AcDbObjectId idBlock = CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), sBlockName);
	if (idBlock==AcDbObjectId::kNull)
	{
		acutPrintf(_T("\n未从图库中找到对应块 : %s"), sBlockName);
		return FALSE;
	}
	AcDbObjectId idInsert = CBlockUtil::InsertBlockRef(idBlock, ptInsert);
	if (idInsert==AcDbObjectId::kNull)
	{
		acutPrintf(_T("\n插入特定块失败 :%s"), sBlockName);
		return FALSE;
	}
	Acad::ErrorStatus es;
	AcDbBlockReference *pRef = NULL;
	es=acdbOpenObject(pRef, idInsert, AcDb::kForWrite);
	if (es!=eOk)
	{
		acutPrintf(_T("\n打开失败"));
		return FALSE;
	}
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
				CString sMbTemp1 = vecStr[0];
				CDwgDatabaseUtil::SetXdata(_T("归属电缆"), sMbTemp1, pEnt);
				CString sMbTemp = vecStr[1];
				CDwgDatabaseUtil::SetXdata(_T("模版位置"), sMbTemp, pEnt);
			}
			if (si == 1)
			{
				CDwgDatabaseUtil::SetXdata(_T("电缆图块"), _T("是"), pEnt);
				CDwgDatabaseUtil::SetXdata(_T("图块名"), sBlockName, pEnt);
				CString sDlTemp = vecStr[0];
				CDwgDatabaseUtil::SetXdata(_T("电缆名"), sDlTemp, pEnt);
			}
			pRec->close();
		}
		CDwgDatabaseUtil::PostToModelSpace(pEnt);
	}
	return TRUE;
}

BOOL CDlgAutoCreat::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	CIniFile ini(GetIniPath());
	ini.GetValueOfKey(_T("DL"), _T("AUTOCREAT"), m_sExcelPath);
	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CDlgAutoCreat::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CIniFile ini(GetIniPath());
	ini.SetValueOfKey(_T("DL"), _T("AUTOCREAT"), m_sExcelPath);

//	CreatBlcok(_T("低频二分三"));
	CAcUiDialog::OnOK();
}
