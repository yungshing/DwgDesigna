// EditDlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EditDlDlg.h"
#include "afxdialogex.h"


// CEditDlDlg �Ի���

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


// CEditDlDlg ��Ϣ�������


BOOL CEditDlDlg::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	CIniFile ini(GetIniPath());
	CString sTemp;
	ini.GetValueOfKey(_T("DL"), _T("DLGG"), sTemp);
	FillCombo(m_cmbDlgg, sTemp, _T(","));
	ini.GetValueOfKey(_T("DL"), _T("DYDJ"), sTemp);
	FillCombo(m_cmbDydj, sTemp, _T(","));
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CEditDlDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString DLGG, DYDJ;
	GetDlgItemText(IDC_CMB_DLGG, DLGG);
	GetDlgItemText(IDC_CMB_DYDJ, DYDJ);
	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es;
	es = acdbOpenAcDbEntity(pEnt, m_idEnt, AcDb::kForWrite);
	if (es==eOk)
	{
		CDwgDatabaseUtil::SetXdata(_T("���¹��"), DLGG, pEnt);
		CDwgDatabaseUtil::SetXdata(_T("��ѹ�ȼ�"), DYDJ, pEnt);
		pEnt->close();
	}
	CAcUiDialog::OnOK();
}
