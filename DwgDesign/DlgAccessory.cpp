// DlgAccessory.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgAccessory.h"
#include "afxdialogex.h"

extern bool strdlg();
extern bool deletedlg();
extern CDlgProresstest *prodlg;
CDlgAccessory *pDlgAccessory;

// CDlgAccessory �Ի���

IMPLEMENT_DYNAMIC(CDlgAccessory, CDialogEx)

CDlgAccessory::CDlgAccessory(CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgAccessory::IDD, pParent)
{
	m_sNum = _T("*");
	m_bRU = TRUE;
	m_bRD = FALSE;
	m_bLD = FALSE;
	m_bLU = FALSE;
	m_dX = 9.518;
	m_dY = 18.370;
	m_dLen = 7.348;
	m_dLjLen = 0.945;

	m_dYLen = 1.16;
	m_dLeftX = 5.68;
	m_dRightX = 1.95;

	m_dTextHight = 5;
	m_dWidthFactor = 0.6;
}

CDlgAccessory::~CDlgAccessory()
{
}

void CDlgAccessory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_CMB_FOLDER, m_cmb_Folder);
	DDX_Text(pDX, IDC_EDIT_DLSJB, m_sDlsjb);
	DDX_Text(pDX, IDC_EDIT_YQJ, m_sYqj);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_sSearch);
	DDX_Control(pDX, IDC_LIST_FJ, m_listFj);
	DDX_Control(pDX, IDC_LIST_YXFJ, m_listYxfj);

	DDX_Control(pDX, IDC_CMB_WH, m_cmb_Wh);
	DDX_Control(pDX, IDC_CMB_DW, m_cmb_Dw);
	DDX_Text(pDX, IDC_EDIT_DH, m_sDh);
	DDX_Text(pDX, IDC_EDIT_NUM, m_sNum);
	DDX_Text(pDX, IDC_EDIT_MC, m_sMc);
	DDX_Text(pDX, IDC_EDIT_GGXH, m_sGgxh);

	DDX_Check(pDX, IDC_CHECK_CONNECT, m_bConnect);
	DDX_Check(pDX, IDC_RADIO_LD, m_bLD);
	DDX_Check(pDX, IDC_RADIO_LU, m_bLU);
	DDX_Check(pDX, IDC_RADIO_RD, m_bRD);
	DDX_Check(pDX, IDC_RADIO_RU, m_bRU);
}


BEGIN_MESSAGE_MAP(CDlgAccessory, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgAccessory::OnBnClickedButton1)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS,OnACADKeepFocus)
	ON_WM_CLOSE()
//	ON_CBN_SELCHANGE(IDC_CMB_FOLDER, &CDlgAccessory::OnCbnSelchangeCmbFolder)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FJ, &CDlgAccessory::OnNMDblclkListFj)
	ON_EN_CHANGE(IDC_EDIT_SEARCH, &CDlgAccessory::OnEnChangeEditSearch)
	ON_BN_CLICKED(IDC_BTN_INSERTFJ, &CDlgAccessory::OnBnClickedBtnInsertfj)
	ON_BN_CLICKED(IDC_BTN_CREATTAB, &CDlgAccessory::OnBnClickedBtnCreattab)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CDlgAccessory::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_JS, &CDlgAccessory::OnBnClickedBtnJs)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_GETMINMAXINFO()
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_LIST_FJ,OnNMCustomdraw)
	ON_BN_CLICKED(IDC_BTN_SELECT, &CDlgAccessory::OnBnClickedBtnSelect)
END_MESSAGE_MAP()


// CDlgAccessory ��Ϣ�������


void CDlgAccessory::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(_T("aa"));
}

afx_msg LRESULT CDlgAccessory::OnACADKeepFocus(WPARAM, LPARAM)
{
	return keepTheFocus() ? TRUE : FALSE;
	//	return TRUE;
}

BOOL CDlgAccessory::keepTheFocus()
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

void CDlgAccessory::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���
	delete this;
	if (pDlgAccessory != NULL)
	{
		pDlgAccessory = NULL;
	}
	CDialogEx::PostNcDestroy();
}

void CDlgAccessory::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnClose();
	DestroyWindow();
}

BOOL CDlgAccessory::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
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
		return CDialogEx::PreTranslateMessage(pMsg);
	}	
}

BOOL CDlgAccessory::OnInitDialog()
{
	CDialogEx::OnInitDialog();

// 	CString sFoldPath = GetExcelFolder() + _T("DLFJ");
// 	FillCombo(sFoldPath,"xlsx", m_cmb_Folder);
	CIniFile ini(GetIniPath());
	CString sDlsjb;
	ini.GetValueOfKey(_T("PPSJ"), _T("DLSJB"), sDlsjb);
	SetDlgItemText(IDC_EDIT_DLSJB, sDlsjb);

	m_listFj.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listFj.InsertColumn(0, _T("Ԫ���������"), LVCFMT_LEFT, 120);
	m_listFj.InsertColumn(1, _T("����(���ʴ���)"), LVCFMT_LEFT, 120);
	m_listFj.InsertColumn(2, _T("����"), LVCFMT_LEFT, 160);
	m_listFj.InsertColumn(3, _T("����ͺ�"), LVCFMT_LEFT, 100);

	m_listYxfj.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listYxfj.InsertColumn(0, _T("���"), LVCFMT_LEFT, 50);
	m_listYxfj.InsertColumn(1, _T("Ԫ���������"), LVCFMT_LEFT, 120);
	m_listYxfj.InsertColumn(2, _T("����(���ʴ���)"), LVCFMT_LEFT, 120);
	m_listYxfj.InsertColumn(3, _T("����"), LVCFMT_LEFT, 160);
	m_listYxfj.InsertColumn(4, _T("����ͺ�"), LVCFMT_LEFT, 100);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetClientRect(&m_rect);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

BOOL CDlgAccessory::GetFjInfo(CString sExcelPath)
{
	m_vec_Fjinfo.clear();
	cExcel excel;
	if (!excel.StartApp())
	{
		return FALSE;
	}
	excel.OpenWorkBook(sExcelPath);
	excel.SwitchToSheet(2);
	int iStartRow, iStartCol,iRowNum,iColNum;
	_ExRange range;
	_ExRange usedRange;
	usedRange.AttachDispatch(excel.GetSheet().GetUsedRange());
	iStartRow=usedRange.GetRow();
	iStartCol = usedRange.GetColumn();
	range.AttachDispatch(usedRange.GetRows());
	iRowNum = range.GetCount();
	range.AttachDispatch(usedRange.GetColumns());
	iColNum = range.GetCount();
 
// 	int iWzdm=0, iMc=0, iXhgg=0;
// 	for (int i=iStartCol;i<iStartCol+iColNum;i++)
// 	{
// 		CString sTitle = excel.GetCString(i, 1);
// 		if (sTitle==_T("���ʱ���"))
// 		{
// 			iWzdm = i;
// 		}
// 		if (sTitle==_T("����"))
// 		{
// 			iMc = i;
// 		}
// 		if (sTitle==_T("�ͺŹ��"))
// 		{
// 			iXhgg = i;
// 		}
// 	}
// 	if (iWzdm == 0 || iMc == 0||iXhgg==0)
// 	{
// 		excel.Quit();
// 		AfxMessageBox(_T("excel��δͬʱ�ҵ����ʱ��룬���Ƽ��ͺŹ��"));
// 		return FALSE;
// 	}

	for (int i=iStartRow+1;i<iStartRow+iRowNum;i++)
	{
		FjInfo temp;
	    temp.YQJ=excel.GetCString(1,i);
		temp.WZDM = excel.GetCString(2, i);
		temp.MC = excel.GetCString(3,i);
		temp.GGXH = excel.GetCString(4,i);
		if (temp.YQJ!=_T("")&&temp.WZDM!=_T("")&&temp.MC!=_T("")&&temp.GGXH!=_T(""))
		{
			m_vec_Fjinfo.push_back(temp);
		}		
	}
	excel.Quit();
	return TRUE;
}

BOOL CDlgAccessory::RefreshLisht()
{
	int iSize=m_vec_Fjinfo.size();
	if (iSize==0)
	{
		return FALSE;
	}
	m_listFj.DeleteAllItems();
	for (int i=0;i<iSize;i++)
	{
		FjInfo temp = m_vec_Fjinfo[i];
		int nRow=m_listFj.InsertItem(i, _T(""));
		m_listFj.SetItemText(nRow, 0, temp.YQJ);
		m_listFj.SetItemText(nRow, 1, temp.WZDM);
		m_listFj.SetItemText(nRow, 2, temp.MC);
		m_listFj.SetItemText(nRow, 3, temp.GGXH);
		SetItemColor(i, RGB(255, 255, 255));
		for (int j = 0; j < m_vec_Yxfj.size(); j++)
		{
			FjMark markTemp = m_vec_Yxfj[j];
			if (markTemp.DH==temp.WZDM)
			{
				SetItemColor(i, RGB(127, 255, 127));
				break;
			}
		}
	}
	UpdateData(FALSE);
	return TRUE;
}

void CDlgAccessory::DrawPoly(AcGePoint3d pt1, AcGePoint3d pt2, AcGePoint3d pt3)
{
	AcDbPolyline *pPoly = new AcDbPolyline;
	pPoly->addVertexAt(0, CConvertUtil::ToPoint2d(pt1));
	pPoly->addVertexAt(1, CConvertUtil::ToPoint2d(pt2));
	pPoly->addVertexAt(2, CConvertUtil::ToPoint2d(pt3));
	CDwgDatabaseUtil::PostToModelSpace(pPoly);
}

void CDlgAccessory::DrawPoly(AcGePoint3d pt1, AcGePoint3d pt2, AcGePoint3d pt3, AcGePoint3d pt4)
{
	AcDbPolyline *pPoly = new AcDbPolyline;
	pPoly->addVertexAt(0, CConvertUtil::ToPoint2d(pt1));
	pPoly->addVertexAt(1, CConvertUtil::ToPoint2d(pt2));
	pPoly->addVertexAt(2, CConvertUtil::ToPoint2d(pt3));
	pPoly->addVertexAt(3, CConvertUtil::ToPoint2d(pt4));
	CDwgDatabaseUtil::PostToModelSpace(pPoly);
}

void CDlgAccessory::DrawFjMark(FjMark markInfo,AcGePoint3d ptInsert)
{
	AcGePoint3d pt1, pt2;//���ڻ���б�ߵ� ���-p1-p2
	AcGePoint3d pt3, pt4, pt5;//���ڻ��������ߵĵ�
	AcGePoint3d ptText,ptText2;//��1 ��2 ���ֵ�
	AcGePoint3d ptTextInsert;
	switch (m_fjLocation)
	{
	case LU:
		pt1 = AcGePoint3d(ptInsert.x - m_dX, ptInsert.y + m_dY, 0);
		pt2 = AcGePoint3d(pt1.x - m_dLen, pt1.y, 0);
		pt3 = AcGePoint3d(ptInsert.x - m_dLjLen, ptInsert.y - m_dLjLen, 0);
		pt4 = AcGePoint3d(ptInsert.x - m_dLjLen * 2, ptInsert.y, 0);
		pt5 = AcGePoint3d(pt4.x - m_dLen, pt4.y, 0);
		ptText = AcGePoint3d(pt1.x - m_dLeftX, pt1.y + m_dYLen, 0);
		ptText2 = AcGePoint3d(pt4.x - m_dLeftX, pt4.y + m_dYLen, 0);
		break;
	case LD:
		pt1 = AcGePoint3d(ptInsert.x - m_dX, ptInsert.y - m_dY, 0);
		pt2 = AcGePoint3d(pt1.x - m_dLen, pt1.y, 0);
		pt3 = AcGePoint3d(ptInsert.x - m_dLjLen, ptInsert.y - m_dLjLen, 0);
		pt4 = AcGePoint3d(ptInsert.x - m_dLjLen * 2, ptInsert.y, 0);
		pt5 = AcGePoint3d(pt4.x - m_dLen, pt4.y, 0);
		ptText = AcGePoint3d(pt1.x - m_dLeftX, pt1.y + m_dYLen, 0);
		ptText2 = AcGePoint3d(pt4.x - m_dLeftX, pt4.y + m_dYLen, 0);
		break;
	case RU:
		pt1 = AcGePoint3d(ptInsert.x + m_dX, ptInsert.y + m_dY, 0);
		pt2 = AcGePoint3d(pt1.x + m_dLen, pt1.y, 0);
		pt3 = AcGePoint3d(ptInsert.x + m_dLjLen, ptInsert.y - m_dLjLen, 0);
		pt4 = AcGePoint3d(ptInsert.x + m_dLjLen * 2, ptInsert.y, 0);
		pt5 = AcGePoint3d(pt4.x + m_dLen, pt4.y, 0);
		ptText = AcGePoint3d(pt1.x + m_dRightX, pt1.y + m_dYLen, 0);
		ptText2 = AcGePoint3d(pt4.x + m_dRightX, pt4.y + m_dYLen, 0);
		break;
	case RD:
		pt1 = AcGePoint3d(ptInsert.x + m_dX, ptInsert.y - m_dY, 0);
		pt2 = AcGePoint3d(pt1.x + m_dLen, pt1.y, 0);
		pt3 = AcGePoint3d(ptInsert.x + m_dLjLen, ptInsert.y - m_dLjLen, 0);
		pt4 = AcGePoint3d(ptInsert.x + m_dLjLen * 2, ptInsert.y, 0);
		pt5 = AcGePoint3d(pt4.x + m_dLen, pt4.y, 0);
		ptText = AcGePoint3d(pt1.x + m_dRightX, pt1.y + m_dYLen, 0);
		ptText2 = AcGePoint3d(pt4.x + m_dRightX, pt4.y + m_dYLen, 0);
		break;
	default:
		break;
	}
	if (m_bConnect)
	{
		ptTextInsert = ptText2;
		DrawPoly(ptInsert, pt3, pt4, pt5);
	}
	else
	{
		ptTextInsert = ptText;
		DrawPoly(ptInsert, pt1, pt2);
	}
	AcDbText *pText = new AcDbText;
	CString sWh = markInfo.WH;
	pText->setTextString(sWh);
	pText->setWidthFactor(m_dWidthFactor);
	pText->setHeight(m_dTextHight);
	pText->setPosition(ptTextInsert);
	CDwgDatabaseUtil::SetXdata(_T("Ԫ����"), markInfo.YQJ, pText);
	CDwgDatabaseUtil::SetXdata(_T("λ��"), markInfo.WH, pText);
	CDwgDatabaseUtil::SetXdata(_T("��λ"), markInfo.DW, pText);
	CDwgDatabaseUtil::SetXdata(_T("����"), markInfo.DH, pText);
	CDwgDatabaseUtil::SetXdata(_T("����"), markInfo.SL, pText);
	CDwgDatabaseUtil::SetXdata(_T("����"), markInfo.MC, pText);
	CDwgDatabaseUtil::SetXdata(_T("���"), markInfo.GGXH, pText);
	CDwgDatabaseUtil::PostToModelSpace(pText);
}

void CDlgAccessory::GetFjmxbInfo()
{
	m_vec_FjMark.clear();
	acDocManager->lockDocument(curDoc());
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
	for (int i = 0; i < idArr.length();i++)
	{
		prodlg->setpos(50 / idArr.length()*(i + 1));
		Sleep(100);

		AcDbObjectId idTemp = idArr[i];
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es;
		es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
		if (es!=eOk)
		{
			continue;
		}
		CString YQJ,WH,DH,MC,GGXH,DW,SL;
		CDwgDatabaseUtil::getXdata(_T("λ��"), WH, pEnt);
		if (WH==_T(""))
		{
			pEnt->close();
			continue;
		}
		CDwgDatabaseUtil::getXdata(_T("Ԫ����"), YQJ, pEnt);
		CDwgDatabaseUtil::getXdata(_T("����"), DH, pEnt);
		CDwgDatabaseUtil::getXdata(_T("����"), MC, pEnt);
		CDwgDatabaseUtil::getXdata(_T("���"), GGXH, pEnt);
		CDwgDatabaseUtil::getXdata(_T("��λ"), DW, pEnt);
		CDwgDatabaseUtil::getXdata(_T("����"), SL, pEnt);
		FjMark temp,temp2;
		temp.YQJ = YQJ;
		temp.WH = WH;
		temp.DH = DH;
		temp.MC = MC;
		temp.GGXH = GGXH;
		temp.DW = DW;
		temp.SL = SL;
		std::vector<FjMark>::iterator itr=std::find(m_vec_FjMark.begin(), m_vec_FjMark.end(),temp);
		if (itr!=m_vec_FjMark.end())
		{
			temp2 = *itr;
			*itr = temp + temp2;
		}
		else
		{
			m_vec_FjMark.push_back(temp);
		}
		pEnt->close();
	}
	std::sort(m_vec_FjMark.begin(), m_vec_FjMark.end());
	acDocManager->unlockDocument(curDoc());
}

BOOL CDlgAccessory::CreatFjmxb(CString sSaveExcelPath)
{
	if (m_vec_FjMark.size()==0)
	{
		return FALSE;
	}
	CString sExcelPath = GetExcelFjmxbPath();
	cExcel excel;
	if (!excel.StartApp())
	{
		AfxMessageBox(_T("�ֻ�ģ����ϸ���ʧ��"));
		return FALSE;
	}
	excel.OpenWorkBook(sExcelPath);
	for (int i = 0;i<m_vec_FjMark.size();i++)
	{
		prodlg->setpos(50+50 / m_vec_FjMark.size()*(i + 1));
		Sleep(100);

		FjMark temp = m_vec_FjMark[i];
		CString sI;
		sI.Format(_T("%d"), i+1);
		excel.PutValue(2, 4 + i, sI);
		excel.PutValue(3, 4 + i, temp.WH);
		excel.PutValue(4, 4 + i, temp.DH);
		excel.PutValue(6, 4 + i, temp.MC + temp.GGXH);
		excel.PutValue(7, 4 + i, temp.DW);
		excel.PutValue(8, 4 + i, temp.SL);
	}
	excel.SaveAs(sSaveExcelPath);
	excel.Quit();
	return FALSE;
}

//void CDlgAccessory::OnCbnSelchangeCmbFolder()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	UpdateData(TRUE);
//	CString sExcelPath = GetExcelFolder() + _T("DLFJ\\");
//	CString sTemp;
//	m_cmb_Folder.GetLBText(m_cmb_Folder.GetCurSel(),sTemp);
//	if (sTemp==_T(""))
//	{
//		return;
//	}
//	sExcelPath += sTemp;
//	GetFjInfo(sExcelPath);
//	RefreshLisht();
//	UpdateData(FALSE);
//}

void CDlgAccessory::OnNMDblclkListFj(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_listFj.ScreenToClient(&point);

	LVHITTESTINFO   lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	int nItem = m_listFj.SubItemHitTest(&lvinfo);
	if (nItem != -1)
	{
		CString sYqj,sDh, sMc,sGgxh;
		sYqj = m_listFj.GetItemText(nItem, 0);
		sDh = m_listFj.GetItemText(nItem, 1);
		sMc = m_listFj.GetItemText(nItem, 2);
		sGgxh = m_listFj.GetItemText(nItem, 3);
		m_sYqj = sYqj;
		m_sDh = sDh;
		m_sMc = sMc;
		m_sGgxh = sGgxh;
		//�洢��ǰitem
		m_iCurrentSelect = nItem;
	}
	UpdateData(FALSE);
	OnBnClickedBtnInsertfj();
	*pResult = 0;
}

void CDlgAccessory::OnEnChangeEditSearch()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CAcUiDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_sSearch == _T(""))
	{
		RefreshLisht();
		return;
	}
	m_listFj.DeleteAllItems();
	int iMark = 0;
	for (int i = 0; i < m_vec_Fjinfo.size(); i++)
	{
		FjInfo temp = m_vec_Fjinfo[i];
		CString sMc = temp.MC;
		int iFind=sMc.Find(m_sSearch);
		if (iFind!=-1)
		{
			int nRow=m_listFj.InsertItem(iMark, _T(""));
			m_listFj.SetItemText(nRow, 0, temp.YQJ);
			m_listFj.SetItemText(nRow, 1, temp.WZDM);
			m_listFj.SetItemText(nRow, 2, temp.MC);
			m_listFj.SetItemText(nRow, 3, temp.GGXH);
			iMark++;
		}
	}
	UpdateData(FALSE);
	return;
}

void CDlgAccessory::OnBnClickedBtnInsertfj()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	FjMark temp;
	GetDlgItemText(IDC_CMB_WH, temp.WH);
	if (temp.WH==_T(""))
	{
		AfxMessageBox(_T("λ����ϢΪ��"));
		return;
	}
	GetDlgItemText(IDC_CMB_DW, temp.DW);
	temp.YQJ = m_sYqj;
	temp.DH = m_sDh;
	temp.SL = m_sNum;
	temp.MC = m_sMc;
	temp.GGXH = m_sGgxh;
	GetYxfjInfo();
	acDocManager->lockDocument(curDoc());
	if (!CheckFjExist(temp))
	{
		AfxMessageBox(_T("������ͬ������ͬ���,��������Ϣ��"));
		return;
	}
	
	AcGePoint3d ptInsert;
	bool b=CGetInputUtil::GetPoint(_T("\nѡ����븽�����λ��:"), ptInsert);
	if (!b)
	{
		acDocManager->unlockDocument(curDoc());
		return;
	}
	if (m_bLD)
	{
		m_fjLocation = LD;
		DrawFjMark(temp, ptInsert);
	}
	if (m_bLU)
	{
		m_fjLocation = LU;
		DrawFjMark(temp, ptInsert);
	}
	if (m_bRD)
	{
		m_fjLocation = RD;
		DrawFjMark(temp, ptInsert);
	}
	if (m_bRU)
	{
		m_fjLocation = RU;
		DrawFjMark(temp, ptInsert);
	}
	acDocManager->unlockDocument(curDoc());

	int nCount = m_listYxfj.GetItemCount();
	m_listYxfj.InsertItem(nCount, _T(""));
	m_listYxfj.SetItemText(nCount, 0, temp.WH);
	m_listYxfj.SetItemText(nCount, 1, m_sYqj);
	m_listYxfj.SetItemText(nCount, 2, temp.DH);
	m_listYxfj.SetItemText(nCount, 3, temp.MC);
	m_listYxfj.SetItemText(nCount, 4, temp.GGXH);

	CString sWz;
	GetDlgItemText(IDC_CMB_WH, sWz);
	if (sWz==temp.WH)
	{
		int i = _wtoi(sWz);
		i++;
		sWz.Format(_T("%d"), i);
		SetDlgItemText(IDC_CMB_WH, sWz);
	}
	
	SetItemColor(m_iCurrentSelect, RGB(127, 255, 127));

	UpdateData(FALSE);
	return;
}

void CDlgAccessory::OnBnClickedBtnCreattab()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString sSavePath;
	CString sTime = GetTimer();
	CFileDialog dlgSave(FALSE, _T("xlsx"), sTime + _T("���¸�����ϸ��"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("excel�ļ�(*.xlsx)|*.xlsx||"), NULL);
	if (dlgSave.DoModal()==IDOK)
	{
		sSavePath = dlgSave.GetPathName();
	}
	else
	{
		return;
	}
	strdlg();
	Sleep(100);
	if (prodlg != NULL)
	{
		prodlg->SetWindowText(_T("����excel��"));
	}

	GetFjmxbInfo();
	CreatFjmxb(sSavePath);

	prodlg->setpos(100);
	Sleep(100);
	deletedlg();
	AfxMessageBox(_T("��������������"));
	return;
}

void CDlgAccessory::GetYxfjInfo()
{
	m_vec_Yxfj.clear();

	acDocManager->lockDocument(curDoc());
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
	FjMark temp;
	for (int i = 0; i < idArr.length(); i++)
	{
		AcDbObjectId idTemp = idArr[i];
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es;
		es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
		if (es != eOk)
		{
			continue;
		}
		if (!pEnt->isKindOf(AcDbText::desc()))
		{
			pEnt->close();
			continue;
		}
		CString sYqj,sWh, sDw, sDh, sSl, sMc, sGg;
		CDwgDatabaseUtil::getXdata(_T("λ��"), sWh, pEnt);
		if (sWh == _T(""))
		{
			pEnt->close();
			continue;
		}
		CDwgDatabaseUtil::getXdata(_T("Ԫ����"), sYqj, pEnt);
		CDwgDatabaseUtil::getXdata(_T("��λ"), sDw, pEnt);
		CDwgDatabaseUtil::getXdata(_T("����"), sDh, pEnt);
		CDwgDatabaseUtil::getXdata(_T("����"), sSl, pEnt);
		CDwgDatabaseUtil::getXdata(_T("����"), sMc, pEnt);
		CDwgDatabaseUtil::getXdata(_T("���"), sGg, pEnt);
		temp.WH = sWh;
		temp.YQJ = sYqj;
		temp.DW = sDw;
		temp.DH = sDh;
		temp.SL = sSl;
		temp.MC = sMc;
		temp.GGXH = sGg;
		m_vec_Yxfj.push_back(temp);
		pEnt->close();
	}
	acDocManager->unlockDocument(curDoc());
}

void CDlgAccessory::RefreshYxfjList()
{
	m_listYxfj.DeleteAllItems();
	int nCount = m_vec_Yxfj.size();
	if (nCount<=0)
	{
		return;
	}
	sort(m_vec_Yxfj.begin(), m_vec_Yxfj.end());
	for (int i = 0; i < nCount;i++)
	{
		FjMark temp = m_vec_Yxfj[i];
		int nRow=m_listYxfj.InsertItem(i, _T(""));
		m_listYxfj.SetItemText(i, 0, temp.WH);
		m_listYxfj.SetItemText(i, 1, temp.YQJ);
		m_listYxfj.SetItemText(i, 2, temp.DH);
		m_listYxfj.SetItemText(i, 3, temp.MC);
		m_listYxfj.SetItemText(i, 4, temp.GGXH);
	}
}

BOOL CDlgAccessory::CheckFjExist(FjMark &fj)
{
	RefreshYxfjList();
	int nCount = m_vec_Yxfj.size();
	for (int i = 0; i < nCount;i++)
	{
		FjMark temp = m_vec_Yxfj[i];
		if (fj.WH==temp.WH)
		{
			if (!(fj==temp))
			{
				return FALSE;
			}
		}
		else
		{
			if (fj==temp)
			{
				fj.WH = temp.WH;
				return TRUE;
			}
		}
	}
	return TRUE;
}

void CDlgAccessory::OnBnClickedBtnRefresh()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ѡ������Ϣ��ȡ
	GetYxfjInfo();
	RefreshYxfjList();

	//���¸�����ѡˢ��
	RefreshLisht();

	AfxMessageBox(_T("ˢ�����"));
}

void CDlgAccessory::OnBnClickedBtnJs()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	strdlg();
	Sleep(100);
	if (prodlg != NULL)
	{
		prodlg->SetWindowText(_T("����excel��Ϣ"));
	}
	//��ѡ������Ϣˢ��
	GetYxfjInfo();
	prodlg->setpos(20);
	Sleep(100);
	RefreshYxfjList();
	prodlg->setpos(50);
	Sleep(100);
	//���¸�����Ϣ��ȡ
	GetFjInfo(m_sDlsjb);
	prodlg->setpos(70);
	Sleep(100);
	RefreshLisht();
	prodlg->setpos(100);
	Sleep(100);
	deletedlg();
	UpdateData(FALSE);
}

void CDlgAccessory::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	CWnd *pWnd1 = GetDlgItem(IDC_LIST_FJ);
	CWnd *pWnd2 = GetDlgItem(IDC_LIST_YXFJ);
	CWnd *pWnd3 = GetDlgItem(IDC_STATIC_FJXZ);
	CWnd *pWnd4 = GetDlgItem(IDC_STATIC_YXFJ);
	if (pWnd1)
	{
		CRect rec;
		pWnd1->GetWindowRect(&rec);
		ScreenToClient(&rec);
		rec.left = rec.left;  //���ձ��������ռ����λ��
		rec.top = rec.top;
		rec.bottom = rec.bottom;
		rec.right = rec.right + (cx - m_rect.Width());
		pWnd1->MoveWindow(rec);

		int n1 = m_listFj.GetColumnWidth(0);
		int n2 = m_listFj.GetColumnWidth(1);
		int n3 = m_listFj.GetColumnWidth(2);
		int n4 = m_listFj.GetColumnWidth(3);

		m_listFj.SetColumnWidth(0, n1 + (cx - m_rect.Width()) / 4);
		m_listFj.SetColumnWidth(1, n2 + (cx - m_rect.Width()) / 4);
		m_listFj.SetColumnWidth(2, n3 + (cx - m_rect.Width()) / 4);
		m_listFj.SetColumnWidth(3, n4 + (cx - m_rect.Width()) / 4);
	}
	if (pWnd2)
	{
		CRect rec;
		pWnd2->GetWindowRect(&rec);
		ScreenToClient(&rec);
		rec.left = rec.left;  //���ձ��������ռ����λ��
		rec.top = rec.top;
		rec.bottom = rec.bottom;
		rec.right = rec.right + (cx - m_rect.Width());
		pWnd2->MoveWindow(rec);

		int n1 = m_listYxfj.GetColumnWidth(0);
		int n2 = m_listYxfj.GetColumnWidth(1);
		int n3 = m_listYxfj.GetColumnWidth(2);
		int n4 = m_listYxfj.GetColumnWidth(3);
		int n5 = m_listYxfj.GetColumnWidth(4);

		m_listYxfj.SetColumnWidth(0, n1 + (cx - m_rect.Width()) / 5);
		m_listYxfj.SetColumnWidth(1, n2 + (cx - m_rect.Width()) / 5);
		m_listYxfj.SetColumnWidth(2, n3 + (cx - m_rect.Width()) / 5);
		m_listYxfj.SetColumnWidth(3, n4 + (cx - m_rect.Width()) / 5);
		m_listYxfj.SetColumnWidth(4, n5 + (cx - m_rect.Width()) / 5);
	}
	if (pWnd3)
	{
		CRect rec;
		pWnd3->GetWindowRect(&rec);
		ScreenToClient(&rec);
		rec.left = rec.left;  //���ձ��������ռ����λ��
		rec.top = rec.top;
		rec.bottom = rec.bottom;
		rec.right = rec.right + (cx - m_rect.Width());
		pWnd3->MoveWindow(rec);
	}
	if (pWnd4)
	{
		CRect rec;
		pWnd4->GetWindowRect(&rec);
		ScreenToClient(&rec);
		rec.left = rec.left;  //���ձ��������ռ����λ��
		rec.top = rec.top;
		rec.bottom = rec.bottom;
		rec.right = rec.right + (cx - m_rect.Width());
		pWnd4->MoveWindow(rec);
	}
	GetClientRect(&m_rect);
}

void CDlgAccessory::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CAcUiDialog::OnPaint()
}

void CDlgAccessory::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.x = 600;
	lpMMI->ptMinTrackSize.y = 800;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CDlgAccessory::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_DODEFAULT;
	NMLVCUSTOMDRAW * lplvdr = (NMLVCUSTOMDRAW*)pNMHDR;
	NMCUSTOMDRAW &nmcd = lplvdr->nmcd;
	switch (lplvdr->nmcd.dwDrawStage)//�ж�״̬
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	}
	case CDDS_ITEMPREPAINT://���Ϊ��ITEM֮ǰ��Ҫ������ɫ�ĸı�
	{
		COLORREF ItemColor;
		if (MapItemColor.Lookup((unsigned long&)nmcd.dwItemSpec, ItemColor))//������SetItemColor(DWORD iItem, COLORREF color) ���õ�//ITEM�ź�COLORREF �������в��ң�Ȼ�������ɫ��ֵ��
		{
			lplvdr->clrTextBk = ItemColor;
			*pResult = CDRF_DODEFAULT;
		}
	}
	break;
	}
}

void CDlgAccessory::SetItemColor(DWORD iItem, COLORREF color)
{

	MapItemColor.SetAt(iItem, color);//����ĳ�е���ɫ��
	m_listFj.RedrawItems(iItem, iItem);//����Ⱦɫ
	m_listFj.SetFocus();//���ý���
	UpdateWindow();
}

void CDlgAccessory::OnBnClickedBtnSelect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// 	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0,
	// 		_T("��ʽ1(*.xls) |*.xls|��ʽ2(*.xlsx) |*.xlsx||"), acedGetAcadFrame());
	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0,
		_T("excel��ʽ(*.xls;*.xlsx) |*.xls;*.xlsx|"), acedGetAcadFrame());
	if (importDlg.DoModal() == IDOK)
	{
		m_sDlsjb = importDlg.GetPathName();
	}
	else
	{
		return;
	}
	UpdateData(FALSE);
}
