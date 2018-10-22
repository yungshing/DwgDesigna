// DlgPrompt.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgPrompt.h"
#include "afxdialogex.h"


// CDlgPrompt 对话框

IMPLEMENT_DYNAMIC(CDlgPrompt, CAcUiDialog)

CDlgPrompt::CDlgPrompt(vector<Log> vec,CString sDqtxPath,CWnd* pParent /*=NULL*/)
: CAcUiDialog(CDlgPrompt::IDD, pParent)
{
	m_sDqtx = sDqtxPath;
	m_vecLog = vec;
	bFirst = true;
	m_bCreatWh = false;
}

CDlgPrompt::CDlgPrompt(vector<CreatWhLog> vec, CWnd* pParent /*= NULL*/) :CAcUiDialog(CDlgPrompt::IDD,pParent)
{
	m_vecCreatWh = vec;
	m_bCreatWh = true;
}

CDlgPrompt::~CDlgPrompt()
{
}

void CDlgPrompt::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}


BEGIN_MESSAGE_MAP(CDlgPrompt, CAcUiDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnNMCustomdraw)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDlgPrompt::OnNMDblclkList1)
	ON_BN_CLICKED(IDOK, &CDlgPrompt::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgPrompt::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgPrompt 消息处理程序


void CDlgPrompt::RefreshWhList()
{
	int nCount = m_vecCreatWh.size();
	m_list1.DeleteAllItems();
	for (int i = 0; i < nCount; i++)
	{
		CreatWhLog temp = m_vecCreatWh[i];
		m_list1.InsertItem(i, _T(""));
		m_list1.SetItemText(i, 0, temp.wtms);
	}
}

BOOL CDlgPrompt::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (!m_bCreatWh)
	{
		m_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		m_list1.InsertColumn(0, _T("Sheet名称"), LVCFMT_LEFT, 100);
		m_list1.InsertColumn(1, _T("行"), LVCFMT_LEFT, 40);
		m_list1.InsertColumn(2, _T("列"), LVCFMT_LEFT, 40);
		m_list1.InsertColumn(3, _T("错误信息"), LVCFMT_LEFT, 200);
		m_list1.InsertColumn(4, _T("处理方法"), LVCFMT_LEFT, 200);

		RefreshList();
	}
	else
	{
		m_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		m_list1.InsertColumn(0, _T("问题描述"), LVCFMT_LEFT, 600);

		RefreshWhList();

		SetDlgItemText(IDOK, _T("确定"));
		SetDlgItemText(IDCANCEL, _T("保存excel"));
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CDlgPrompt::ShowExcelPrompt(CString sSheetName, int nRow, int nCol)
{
// 	bool b =m_excel.isOpenExcel(m_sDqtx);
// 	if (b&&bFirst)
// 	{
// 		AfxMessageBox(_T("当前特性表已打开，请先关闭！"));
// 		return;
// 	}
// 	if (!b)
// 	{
// 		if (!m_excel.StartApp())
// 		{
// 			AfxMessageBox(_T("excel打开失败"));
// 			return;
// 		}
// 		bFirst = false;
// 		m_excel.OpenWorkBook(m_sDqtx);
// 	}
// 	else
// 	{
// 		m_excel.GetSheets();
// 	}
	m_excel.openSpecailFile(m_sDqtx);


	m_excel.SwitchToSheet(sSheetName);	
	m_excel.ActiveRange(nRow, nCol);
	m_excel.ShowExcel();

	int i=m_sDqtx.ReverseFind('\\');
	CString sFileName = m_sDqtx.Mid(i + 1)+_T(" - Excel");
	CString sFileName2 = _T("Microsoft Excel - ") + m_sDqtx.Mid(i + 1);
	CWnd *hw64 = FindWindow(NULL, sFileName);
	CWnd *hw32 = FindWindow(NULL, sFileName2);
	if (hw64 != NULL)
	{
		::SetWindowPos(hw64->m_hWnd, this->m_hWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	if (hw32!=NULL)
	{
		::SetWindowPos(hw32->m_hWnd, this->m_hWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
}

void CDlgPrompt::RefreshList()
{
	int nCount = m_vecLog.size();
	m_list1.DeleteAllItems();
	for (int i = 0; i < nCount;i++)
	{
		Log temp = m_vecLog[i];
		m_list1.InsertItem(i, _T(""));
		m_list1.SetItemText(i, 0, temp.sheet);
		m_list1.SetItemText(i, 1, temp.row);
		m_list1.SetItemText(i, 2, temp.col);
		m_list1.SetItemText(i, 3, temp.wtms);
		m_list1.SetItemText(i, 4, temp.clfs);
		if (temp.wtms==_T("名称为空"))
		{
			SetItemColor(i, RGB(255, 0, 0));
		}		
	}
}

void CDlgPrompt::CloseExcel()
{
	if (m_excel.isOpenExcel(m_sDqtx))
	{
		m_excel.SaveAs(m_sDqtx);
		m_excel.Quit();
	}
}

void CDlgPrompt::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_DODEFAULT;
	NMLVCUSTOMDRAW * lplvdr = (NMLVCUSTOMDRAW*)pNMHDR;
	NMCUSTOMDRAW &nmcd = lplvdr->nmcd;
	switch (lplvdr->nmcd.dwDrawStage)//判断状态
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	}
	case CDDS_ITEMPREPAINT://如果为画ITEM之前就要进行颜色的改变
	{
		COLORREF ItemColor;
		if (MapItemColor.Lookup((unsigned long&)nmcd.dwItemSpec, ItemColor))//根据在SetItemColor(DWORD iItem, COLORREF color) 设置的//ITEM号和COLORREF 在摸板中查找，然后进行颜色赋值。
		{
			lplvdr->clrTextBk = ItemColor;
			*pResult = CDRF_DODEFAULT;
		}
	}
	break;
	}
}

void CDlgPrompt::SetItemColor(DWORD iItem, COLORREF color)
{

	MapItemColor.SetAt(iItem, color);//设置某行的颜色。
	m_list1.RedrawItems(iItem, iItem);//重新染色
	m_list1.SetFocus();//设置焦点
	UpdateWindow();
}

void CDlgPrompt::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	if (m_bCreatWh)
	{
		*pResult = 0;
		return;
	}
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_list1.ScreenToClient(&point);

	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	int nItem = m_list1.SubItemHitTest(&lvinfo);
	if (nItem != -1)
	{
		CString sSheetName, sRow, sCol;
		sSheetName = m_list1.GetItemText(nItem, 0);
		sRow = m_list1.GetItemText(nItem, 1);
		sCol = m_list1.GetItemText(nItem, 2);
		int nRow = _wtoi(sRow);
		int nCol = _wtoi(sCol);
		ShowExcelPrompt(sSheetName, nRow, nCol);
	}
	*pResult = 0;
}


void CDlgPrompt::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_bCreatWh)
	{
		CloseExcel();
	}	
	CAcUiDialog::OnOK();
}


void CDlgPrompt::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_bCreatWh)
	{
		CloseExcel();
	}
	CAcUiDialog::OnCancel();
}


void CDlgPrompt::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!m_bCreatWh)
	{
		CloseExcel();
	}	
	CAcUiDialog::OnClose();
}
