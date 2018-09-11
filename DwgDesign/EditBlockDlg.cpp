// EditBlockDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EditBlockDlg.h"
#include "afxdialogex.h"


// CEditBlockDlg �Ի���

IMPLEMENT_DYNAMIC(CEditBlockDlg, CAcUiDialog)

CEditBlockDlg::CEditBlockDlg(AcDbObjectId entId,CWnd* pParent /*=NULL*/)
: CAcUiDialog(CEditBlockDlg::IDD, pParent)
{
	m_entId = entId;
}

CEditBlockDlg::~CEditBlockDlg()
{
}

void CEditBlockDlg::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_TH, m_cmbTh);
	DDX_Control(pDX, IDC_STATIC_PIC, m_fc);
	DDX_Check(pDX, IDC_CHECK_JX, m_bJx);
}


BEGIN_MESSAGE_MAP(CEditBlockDlg, CAcUiDialog)
	ON_BN_CLICKED(IDOK, &CEditBlockDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_CMB_TH, &CEditBlockDlg::OnCbnSelchangeCmbTh)
END_MESSAGE_MAP()


// CEditBlockDlg ��Ϣ�������


BOOL CEditBlockDlg::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	acDocManager->lockDocument(curDoc());
	std::vector<CString> vecTemp;
	vecTemp = GetDwgAllBlockName(GetBlockLibPath());
	size_t s = vecTemp.size();
	for (int i = 0; i < s; i++)
	{
		CString sTemp = vecTemp[i];
		m_cmbTh.AddString(sTemp);
	}
	acDocManager->unlockDocument(curDoc());

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CEditBlockDlg::OnCbnSelchangeCmbTh()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	acDocManager->lockDocument(curDoc());
	CString sTemp;
	int a = m_cmbTh.GetCurSel();
	m_cmbTh.GetLBString(a, sTemp);
	CBlockUtil::CopyBlockDefFromOtherDwg(GetBlockLibPath(), sTemp);
	m_fc.Clear();
	m_fc.Init(acdbHostApplicationServices()->workingDatabase(), sTemp);
	acDocManager->unlockDocument(curDoc());
	UpdateData(FALSE);
}


void CEditBlockDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	BeginEditorCommand();
	acDocManager->lockDocument(curDoc());
	AcGePoint3d pt;
	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt, m_entId, AcDb::kForWrite);
	if (es==eOk)
	{
		AcDbBlockReference* pRef = static_cast<AcDbBlockReference*>(pEnt);
		pt=pRef->position();
		pEnt->erase();
		pEnt->close();
	}
	else
	{
		acDocManager->unlockDocument(curDoc());
		CAcUiDialog::OnOK();
	}

	CString sTemp;
	GetDlgItemText(IDC_CMB_TH, sTemp);
	AcDbObjectId idTemp = CBlockUtil::CopyBlockDefFromOtherDwg(GetBlockLibPath(), sTemp);
	AcDbObjectId idInsert=CBlockUtil::InsertBlockRef(idTemp, pt);
	
	if (idInsert!=AcDbObjectId::kNull)
	{
		AcDbEntity *pEntTemp = NULL;
		es = acdbOpenAcDbEntity(pEntTemp, idInsert, AcDb::kForWrite);
		if (es==eOk)
		{
			CDwgDatabaseUtil::SetXdata(_T("ģ��ͼ��"), _T("��"), pEntTemp);
			pEntTemp->close();
		}
	}
	
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	CAcUiDialog::OnOK();
}