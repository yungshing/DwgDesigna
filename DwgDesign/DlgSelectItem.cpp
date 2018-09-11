// DlgSelectItem.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgSelectItem.h"
#include "afxdialogex.h"

// CDlgSelectItem 对话框
CDlgSelectItem *pDlgSelect = NULL;

IMPLEMENT_DYNAMIC(CDlgSelectItem, CAcUiDialog)

CDlgSelectItem::CDlgSelectItem(int iBlockNum, AcGePoint3dArray ptArr, AcDbObjectIdArray idArr, double dx, double dy, CString sName, CString sWzdm,CString sView,
int iTextHight,CListCtrl* weihaolist,int nItem ,CWnd* pParent /*=NULL*/)
: CAcUiDialog(CDlgSelectItem::IDD, pParent)
{
	m_iBlockNum = iBlockNum;
	m_ptArr = ptArr;
	m_idArr = idArr;
	m_dx = dx;
	m_dy = dy;
	m_sName = sName;
	m_sWzdm = sWzdm;
	m_sView = sView;
	m_iTextHight = iTextHight;

	m_weihaolist = weihaolist;
	m_nItem = nItem;

	m_bInsert = false;
}

CDlgSelectItem::~CDlgSelectItem()
{
	if (m_idWire!=AcDbObjectId::kNull)
	{
		acDocManager->lockDocument(curDoc());
		DeleteWire(m_idWire);
		UnHighLight(m_idArr);
		acDocManager->unlockDocument(curDoc());
		acTransactionManagerPtr()->flushGraphics();
		acedUpdateDisplay();
	}	
}

void CDlgSelectItem::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_SELECT, m_tree);
}


BEGIN_MESSAGE_MAP(CDlgSelectItem, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS,OnACADKeepFocus)
	ON_NOTIFY(NM_CLICK, IDC_TREE_SELECT, &CDlgSelectItem::OnNMClickTreeSelect)
//	ON_NOTIFY(NM_DBLCLK, IDC_TREE_SELECT, &CDlgSelectItem::OnNMDblclkTreeSelect)
ON_NOTIFY(NM_RCLICK, IDC_TREE_SELECT, &CDlgSelectItem::OnNMRClickTreeSelect)
ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgSelectItem 消息处理程序


BOOL CDlgSelectItem::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HTREEITEM htr=NULL;
	for (int i = 0; i < m_iBlockNum;i++)
	{
		CString sTemp, sI;
		sI.Format(_T("%d"), i + 1);
		sTemp = _T("图块") + sI;
		htr=m_tree.InsertItem(sTemp,NULL,htr);
		m_tree.SetItemData(htr, i);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgSelectItem::OnNMClickTreeSelect(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	CPoint point;
	GetCursorPos(&point);
	m_tree.ScreenToClient(&point);
	UINT uFlags;
	HTREEITEM CurrentItem;
	CurrentItem = m_tree.HitTest(point, &uFlags);
	int i=m_tree.GetItemData(CurrentItem);
	//获取点击index后删除
	acDocManager->lockDocument(curDoc());
	if (m_idWire!=AcDbObjectId::kNull)
	{
		DeleteWire(m_idWire);
		UnHighLight(m_idArr);
	}
	MoveView(m_ptArr[i], m_dx * 3, m_dy * 3);
	m_idWire = WirePrompt(GetBlockRefExten(m_idArr[i], 3));
	HighLight(m_idArr);
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	*pResult = 0;
}


//void CDlgSelectItem::OnNMDblclkTreeSelect(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO:  在此添加控件通知处理程序代码
//	CPoint point;
//	GetCursorPos(&point);
//	m_tree.ScreenToClient(&point);
//	UINT uFlags;
//	HTREEITEM CurrentItem;
//	CurrentItem = m_tree.HitTest(point, &uFlags);
//	int i = m_tree.GetItemData(CurrentItem);
//
//	CString si;
//	si.Format(_T("%d"), i);
//	AfxMessageBox(si+_T("双击"));
//	*pResult = 0;
//}


void CDlgSelectItem::OnNMRClickTreeSelect(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_bInsert)
	{
		AfxMessageBox(_T("请esc后再进行重新插入"));
		*pResult = 0;
		return;
	}
	CPoint point;
	GetCursorPos(&point);
	m_tree.ScreenToClient(&point);
	UINT uFlags;
	HTREEITEM CurrentItem;
	CurrentItem = m_tree.HitTest(point, &uFlags);
	int i = m_tree.GetItemData(CurrentItem);
	
	//获取点击index后删除
	acDocManager->lockDocument(curDoc());
	if (m_idWire != AcDbObjectId::kNull)
	{
		DeleteWire(m_idWire);
		UnHighLight(m_idArr);
	}
	MoveView(m_ptArr[i], m_dx * 3, m_dy * 3);
	m_idWire = WirePrompt(GetBlockRefExten(m_idArr[i], 3));
	HighLight(m_idArr);

	AcGePoint3d ptTemp;
	m_bInsert = true;
	bool b = CGetInputUtil::GetPoint(_T("\n已高亮显示图块。请选择标记插入点,且插入点应在红色提示框内:"), ptTemp);
	m_bInsert = false;
	if (b)
	{
		if (!PtInExten(ptTemp, GetBlockRefExten(m_idArr[i], 3)))
		{
			AfxMessageBox(_T("位号放置位置不在所属红框内！"));
		}
		AcDbText *pText = new AcDbText(ptTemp, m_sName, AcDbObjectId::kNull, m_iTextHight);
		pText->setHorizontalMode(AcDb::kTextCenter);
		pText->setVerticalMode(AcDb::kTextVertMid);
		pText->setAlignmentPoint(ptTemp);
		CDwgDatabaseUtil::SetXdata(_T("标记"), m_sName, pText);
		CDwgDatabaseUtil::SetXdata(_T("物资代码"), m_sWzdm, pText);
		CDwgDatabaseUtil::SetXdata(_T("视图"), m_sView, pText);
		CDwgDatabaseUtil::PostToModelSpace(pText);
		m_weihaolist->SetCheck(m_nItem, TRUE);
	}

	DeleteWire(m_idWire);
	UnHighLight(m_idArr);
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();

	DestroyWindow();
	*pResult = 0;
}


BOOL CDlgSelectItem::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN&&pMsg->wParam)
	{
		return TRUE;
	}
	else
	{
		return CAcUiDialog::PreTranslateMessage(pMsg);
	}
}


void CDlgSelectItem::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类
	delete this;
	if (pDlgSelect!=NULL)
	{
		pDlgSelect = NULL;
	}
	CAcUiDialog::PostNcDestroy();
}


void CDlgSelectItem::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CAcUiDialog::OnClose();
	DestroyWindow();
}

BOOL CDlgSelectItem::keepTheFocus()
{
	POINT pt;
	GetCursorPos(&pt);
	CRect rec;
	GetWindowRect(&rec);
	bool b = PtInRect(&rec, pt);
	if (b)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

LRESULT CDlgSelectItem::OnACADKeepFocus(WPARAM, LPARAM)
{
	return keepTheFocus() ? TRUE : FALSE;
}
