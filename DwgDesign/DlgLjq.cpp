// DlgLjq.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgLjq.h"
#include "afxdialogex.h"


// CDlgLjq �Ի���

IMPLEMENT_DYNAMIC(CDlgLjq, CAcUiDialog)

CDlgLjq::CDlgLjq(CWnd* pParent /*=NULL*/)
	: CAcUiDialog(IDD_DLG_LJQ, pParent)
{
}

CDlgLjq::~CDlgLjq()
{
}

void CDlgLjq::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LJQMC, m_sLjqmc);
	DDX_Control(pDX, IDC_CMB_LJQLX, m_cmb_Ljqlx);
	DDX_Control(pDX, IDC_LIST_RESULT, m_list_Result);
}


BEGIN_MESSAGE_MAP(CDlgLjq, CAcUiDialog)
	ON_BN_CLICKED(IDOK, &CDlgLjq::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgLjq::OnBnClickedButton1)
ON_CBN_SELCHANGE(IDC_CMB_LJQLX, &CDlgLjq::OnCbnSelchangeCmbLjqlx)
END_MESSAGE_MAP()


// CDlgLjq ��Ϣ�������

void CDlgLjq::FindExcelInfo()
{
	CString sFolder;
	m_cmb_Ljqlx.GetLBText(m_cmb_Ljqlx.GetCurSel(), sFolder);
	if (sFolder==_T(""))
	{
		return;
	}
	int iMark = 0;
	cExcel excel;
	CString sExcelPath = GetExcelFolder() + _T("LJQLX\\") + sFolder;
	if (!excel.StartApp())
	{
		return;
	}
	excel.OpenWorkBook(sExcelPath);
	int iNum = excel.GetSheetNum();

	excel.SwitchToSheet(1);
	_ExRange range;
	_ExRange usedRange;
	int iStartRow, iStartCol, iRowNum, iColNum;
	usedRange.AttachDispatch(excel.GetSheet().GetUsedRange());
	iStartRow = usedRange.GetRow();
	iStartCol = usedRange.GetColumn();
	range.AttachDispatch(usedRange.GetRows());
	iRowNum = range.GetCount();
	range.AttachDispatch(usedRange.GetColumns());
	iColNum = range.GetCount();

	for (int i = 2; i <= iRowNum; i++)
	{
		struct_LJQ temp;
		temp.WZBM = excel.GetCString(1, i);
		temp.NAME = excel.GetCString(2, i);
		temp.XL = excel.GetCString(3, i);
		temp.GGXH = excel.GetCString(4, i);
		temp.CJ = excel.GetCString(9, i);
		m_vecLjq.push_back(temp);
	}
	excel.Quit();
}

void CDlgLjq::FillList()
{
	m_list_Result.DeleteAllItems();
	for (int i = 0;i<m_vecLjq.size();i++)
	{
		struct_LJQ temp = m_vecLjq[i];
		int nRow = m_list_Result.InsertItem(i, _T(""));
		m_list_Result.SetItemText(nRow, 0, temp.WZBM);
		m_list_Result.SetItemText(nRow, 1, temp.NAME);
		m_list_Result.SetItemText(nRow, 2, temp.XL);
		m_list_Result.SetItemText(nRow, 3, temp.GGXH);
		m_list_Result.SetItemText(nRow, 4, temp.CJ);
	}
}

void CDlgLjq::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iSelect= m_list_Result.GetSelectionMark();
	if (iSelect==-1)
	{
		AfxMessageBox(_T("δѡ���κ�һ��"));
		return;
	}
	m_sLjqxh = m_list_Result.GetItemText(iSelect, 1);
	m_sWzdm = m_list_Result.GetItemText(iSelect, 0);
	CAcUiDialog::OnOK();
}


BOOL CDlgLjq::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	CString sFilePath = GetExcelFolder() + _T("LJQLX");
	FillCombo(sFilePath, "xlsx", m_cmb_Ljqlx);

	m_list_Result.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list_Result.InsertColumn(0, _T("���ʴ���"), LVCFMT_LEFT, 100);
	m_list_Result.InsertColumn(1, _T("����"), LVCFMT_LEFT, 100);
	m_list_Result.InsertColumn(2, _T("ϵ��"), LVCFMT_LEFT, 80);
	m_list_Result.InsertColumn(3, _T("����ͺ�"), LVCFMT_LEFT, 120);
	m_list_Result.InsertColumn(4, _T("����"), LVCFMT_LEFT, 100);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgLjq::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_list_Result.DeleteAllItems();
	int iMark = 0;
	for (int i = 0;i<m_vecLjq.size();i++)
	{
		struct_LJQ temp = m_vecLjq[i];
		int iTemp = temp.NAME.Find(m_sLjqmc);
		if (iTemp!=-1)
		{
			int nRow = m_list_Result.InsertItem(iMark, _T(""));
			m_list_Result.SetItemText(nRow, 0, temp.WZBM);
			m_list_Result.SetItemText(nRow, 1, temp.NAME);
			m_list_Result.SetItemText(nRow, 2, temp.XL);
			m_list_Result.SetItemText(nRow, 3, temp.GGXH);
			m_list_Result.SetItemText(nRow, 4, temp.CJ);
			iMark++;
		}
	}
	UpdateData(FALSE);
	return;
}


void CDlgLjq::OnCbnSelchangeCmbLjqlx()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	FindExcelInfo();
	FillList();
}
