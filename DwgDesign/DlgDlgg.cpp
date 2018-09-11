// DlgDlgg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgDlgg.h"
#include "afxdialogex.h"


// CDlgDlgg �Ի���

IMPLEMENT_DYNAMIC(CDlgDlgg, CAcUiDialog)

CDlgDlgg::CDlgDlgg(CWnd* pParent /*=NULL*/)
	: CAcUiDialog(IDD_DLG_DLGG, pParent)
{

}

CDlgDlgg::~CDlgDlgg()
{
}

void CDlgDlgg::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DLMC, m_sDlmc);
	DDX_Control(pDX, IDC_CMB_DLGG, m_cmb_Dlgg);
	DDX_Control(pDX, IDC_LIST_RESULT, m_list_Result);
}


BEGIN_MESSAGE_MAP(CDlgDlgg, CAcUiDialog)
	ON_BN_CLICKED(IDOK, &CDlgDlgg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_CMB_DLGG, &CDlgDlgg::OnCbnSelchangeCmbDlgg)
END_MESSAGE_MAP()


// CDlgDlgg ��Ϣ�������

void CDlgDlgg::FindExcelInfo()
{
	CString sFolder;
	m_cmb_Dlgg.GetLBString(m_cmb_Dlgg.GetCurSel(), sFolder);
	if (sFolder==_T(""))
	{
		return;
	}
	int iMark = 0;
	cExcel excel;
	CString sExcelPath = GetExcelFolder() + _T("DLGG\\") + sFolder;
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

	for (int i = 2; i <= iRowNum;i++)
	{
		struct_DLGG temp;
		temp.WZBM = excel.GetCString(1, i);
		temp.NAME = excel.GetCString(2, i);
		temp.XL = excel.GetCString(3, i);
		temp.GGXH = excel.GetCString(4, i);
		temp.CJ = excel.GetCString(9, i);
		m_vecDlgg.push_back(temp);
	}
	excel.Quit();
}

void CDlgDlgg::FillList()
{
	m_list_Result.DeleteAllItems();
	for (int i = 0;i<m_vecDlgg.size();i++)
	{
		struct_DLGG temp = m_vecDlgg[i];
		int nRow = m_list_Result.InsertItem(i, _T(""));
		m_list_Result.SetItemText(nRow, 0, temp.WZBM);
		m_list_Result.SetItemText(nRow, 1, temp.NAME);
		m_list_Result.SetItemText(nRow, 2, temp.XL);
		m_list_Result.SetItemText(nRow, 3, temp.GGXH);
		m_list_Result.SetItemText(nRow, 4, temp.CJ);
	}
}

void CDlgDlgg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iSelect = m_list_Result.GetSelectionMark();
	if (iSelect == -1)
	{
		AfxMessageBox(_T("δѡ���κ�һ��"));
		return;
	}
	m_sXlcl = m_list_Result.GetItemText(iSelect, 1) + m_list_Result.GetItemText(iSelect,3);
	m_sXlwzdm = m_list_Result.GetItemText(iSelect, 0);
	CAcUiDialog::OnOK();
}


BOOL CDlgDlgg::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	CString sFolderPath = GetExcelFolder() + _T("DLGG");
	FillCombo(sFolderPath, "xlsx", m_cmb_Dlgg);

	m_list_Result.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list_Result.InsertColumn(0, _T("���ʴ���"),LVCFMT_LEFT,100);
	m_list_Result.InsertColumn(1, _T("����"), LVCFMT_LEFT, 100);
	m_list_Result.InsertColumn(2, _T("ϵ��"), LVCFMT_LEFT, 80);
	m_list_Result.InsertColumn(3, _T("����ͺ�"), LVCFMT_LEFT, 120);
	m_list_Result.InsertColumn(4, _T("����"), LVCFMT_LEFT, 100);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgDlgg::OnCbnSelchangeCmbDlgg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	FindExcelInfo();
	FillList();
}
