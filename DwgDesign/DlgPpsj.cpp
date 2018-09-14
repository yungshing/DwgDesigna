// DlgPpsj.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgPpsj.h"
#include "afxdialogex.h"
#include <CPPAdapter.h>
#include "DlgProresstest.h"


// CDlgPpsj �Ի���
extern bool strdlg();
extern bool deletedlg();
extern CDlgProresstest *prodlg;

IMPLEMENT_DYNAMIC(CDlgPpsj, CDialogEx)

CDlgPpsj::CDlgPpsj(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_DLG_PPSJ, pParent)
{
	m_dX = 9.518;
	m_dY = 18.370;
	m_dLen = 7.348;
	m_bLh = FALSE;
}

CDlgPpsj::~CDlgPpsj()
{
}

void CDlgPpsj::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DLLJGXB, m_sDlljgxb);
	DDX_Text(pDX, IDC_EDIT_W, m_sW);
	DDX_Text(pDX, IDC_EDIT_BM, m_sBm);
//	DDX_Text(pDX, IDC_EDIT_DLGG, m_sDlgg);

	DDX_Control(pDX, IDC_CMB_DLLX, m_cmb_Dllx);
	DDX_Control(pDX, IDC_CMB_DLLJ, m_cmb_Dlljxs);

	DDX_Check(pDX, IDC_CHECK_LH, m_bLh);

	DDX_Control(pDX, IDC_LIST_LJQ, m_list_Ljqxh);
	DDX_Control(pDX, IDC_LIST_FJ, m_list_Dlfjxx);
	DDX_Control(pDX, IDC_LIST_DLGG, m_list_Dlgg);

	DDX_Control(pDX, IDC_STATIC_PREVIEW, m_fc);
	DDX_Control(pDX, IDC_EDIT_MOD, m_Edit);

}


BEGIN_MESSAGE_MAP(CDlgPpsj, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SEARCH1, &CDlgPpsj::OnBnClickedBtnSearch1)
	ON_BN_CLICKED(IDC_BTN_SEARCH3, &CDlgPpsj::OnBnClickedBtnSearch3)
	ON_BN_CLICKED(IDC_BTN_SELECT, &CDlgPpsj::OnBnClickedBtnSelect)
	ON_BN_CLICKED(IDC_BTN_SEARCH2, &CDlgPpsj::OnBnClickedBtnSearch2)
	ON_BN_CLICKED(IDOK, &CDlgPpsj::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_DLMXB, &CDlgPpsj::OnBnClickedBtnDlmxb)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LJQ, &CDlgPpsj::OnNMDblclkListLjq)
	ON_EN_KILLFOCUS(IDC_EDIT_MOD, &CDlgPpsj::OnEnKillfocusEditMod)
	ON_CBN_SELCHANGE(IDC_CMB_DLLJ, &CDlgPpsj::OnCbnSelchangeCmbDllj)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DLGG, &CDlgPpsj::OnNMDblclkListDlgg)
	ON_BN_CLICKED(IDC_BTN_SJ1, &CDlgPpsj::OnBnClickedBtnSj1)
	ON_BN_CLICKED(IDC_BTN_SJ2, &CDlgPpsj::OnBnClickedBtnSj2)
	ON_BN_CLICKED(IDC_BTN_SJ3, &CDlgPpsj::OnBnClickedBtnSj3)
	ON_BN_CLICKED(IDC_BTN_SJ4, &CDlgPpsj::OnBnClickedBtnSj4)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BTN_HBTAB, &CDlgPpsj::OnBnClickedBtnHbtab)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgPpsj::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_CONNECTSELECT, &CDlgPpsj::OnBnClickedButtonConnectselect)
END_MESSAGE_MAP()


// CDlgPpsj ��Ϣ�������


BOOL CDlgPpsj::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString sTemp;
	CIniFile ini(GetIniPath());
	//���������ļ���ȡ������
	ini.GetValueOfKey(_T("PPSJ"), _T("DLLJXS"), sTemp);
	FillCombo(m_cmb_Dlljxs, sTemp);
	ini.GetValueOfKey(_T("PPSJ"), _T("DLLX"), sTemp);
	FillCombo(m_cmb_Dllx, sTemp);
// 	//�����ļ��л�ȡexcel
// 	CString sFilePath = GetCableType();
// 	FillCombo(sFilePath, "xlsx", m_cmb_Dllx);

	m_list_Ljqxh.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list_Ljqxh.InsertColumn(0, _T("������λ��"), LVCFMT_LEFT, 50);
	m_list_Ljqxh.InsertColumn(1, _T("�������ͺ�"), LVCFMT_LEFT, 160);
	m_list_Ljqxh.InsertColumn(2, _T("���ʴ���"), LVCFMT_LEFT, 110);
	m_list_Ljqxh.InsertColumn(3, _T("���"), LVCFMT_LEFT, 50);

	m_list_Dlfjxx.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list_Dlfjxx.InsertColumn(0, _T("��������"), LVCFMT_LEFT, 190);
	m_list_Dlfjxx.InsertColumn(1, _T("�������"), LVCFMT_LEFT, 190);

	m_list_Dlgg.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list_Dlgg.InsertColumn(0, _T("λ��(��)"), LVCFMT_LEFT, 50);
	m_list_Dlgg.InsertColumn(1, _T("λ��(��)"), LVCFMT_LEFT, 50);
	m_list_Dlgg.InsertColumn(2, _T("���²���"), LVCFMT_LEFT, 160);
	m_list_Dlgg.InsertColumn(3, _T("�������ʴ���"), LVCFMT_LEFT, 90);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetClientRect(&m_rect);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgPpsj::OnBnClickedBtnSearch1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgLjq ljq;
	if (ljq.DoModal()==IDOK)
	{
		m_sW = ljq.m_sLjqmc;
	}
	
	UpdateData(FALSE);
}

void CDlgPpsj::OnBnClickedBtnSearch3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgDlfj dlfj;
	dlfj.DoModal();
}

void CDlgPpsj::OnBnClickedBtnSearch2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgDlgg dlgg;
	dlgg.DoModal();
}

void CDlgPpsj::OnBnClickedBtnSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
// 	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0,
// 		_T("��ʽ1(*.xls) |*.xls|��ʽ2(*.xlsx) |*.xlsx||"), acedGetAcadFrame());
	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0,
		_T("excel��ʽ(*.xls;*.xlsx) |*.xls;*.xlsx|"), acedGetAcadFrame());
	if (importDlg.DoModal() == IDOK)
	{
		m_sDlljgxb = importDlg.GetPathName();
	}
	else
	{
		return;
	}
	UpdateData(FALSE);
	if (!CheckExcelPath(m_sDlljgxb))
	{
		AfxMessageBox(_T("excel�ļ��򿪴�������,���飡"));
		return;
	}
	strdlg();
	Sleep(100);
	if (prodlg!=NULL)
	{
		prodlg->SetWindowText(_T("����excel��Ϣ"));
	}
	
    //���excel��Ϣ����
	if (!CheckExcel())
	{			
		prodlg->setpos(100);
		Sleep(100);
		deletedlg();
		AfxMessageBox(_T("excel����Ϣ�������⣬��鿴��־�ļ�!"));
		return;
	}	
	prodlg->setpos(20);
	Sleep(100);
	
	UpdateData(FALSE);
	GetDlInfo();//��ȡ������������Ϣ�Լ����¹����Ϣ
	CString sDlName = GetDlType(m_vecLeft.size(), m_vecRight.size());//����������Ϣȷ����������
	/*SetDlgItemText(IDC_CMB_DLLJ, sDlName);*/
	m_cmb_Dlljxs.SetCurSel(m_cmb_Dlljxs.FindString(0, sDlName));
	m_cmb_Dllx.SetCurSel(m_cmb_Dllx.FindString(0, m_sDllx));
	FillListLjq();
	FillListDlgg();
	prodlg->setpos(95);
	Sleep(100);
	
	UpdateData(FALSE);
	OnCbnSelchangeCmbDllj();
	prodlg->setpos(100);
	Sleep(100);
	deletedlg();
	AfxMessageBox(_T("�򿪼�������"));
	return;
}

BOOL CDlgPpsj::CheckExcel()
{
	CString sPrompt;
	cExcel excel;

	m_vecLog.clear();

	if (!excel.StartApp())
	{
		AfxMessageBox(_T("��excelʧ��"));
		return FALSE;
	}
	excel.OpenWorkBook(m_sDlljgxb);
	excel.SwitchToSheet(1);

	//��ȡexcle �����Լ���ʼ��Ĭ��1��1
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
	CString sTempPrompt;
	CString sI;
	sI.Format(_T("%d"), 1);
		
	CString sW = excel.GetCString(2, 1);
	CString sBm = excel.GetCString(4, 1);
	CString sDllx = excel.GetCString(17, 3);
	if (sW==_T("")||sBm==_T(""))
	{
		Log temp;
		temp.sheet = sI;
		if (sW==_T("")&&sBm!=_T(""))
		{
			temp.row = _T("1");
			temp.col = _T("2");
			sTempPrompt = _T("���±��Ϊ��; ");
			temp.wtms = _T("���±��Ϊ��; ");
			m_vecLog.push_back(temp);
		}
		if (sW != _T("") && sBm == _T(""))
		{
			temp.row = _T("1");
			temp.col = _T("4");
			sTempPrompt = _T("bm��Ϊ��; ");
			temp.wtms = _T("bm��Ϊ��; ");
			m_vecLog.push_back(temp);
		}
		if (sW == _T("") && sBm == _T(""))
		{
			temp.row = _T("1");
			temp.col = _T("2");
			sTempPrompt = _T("���±�ż�bm�ž�Ϊ��; ");
			temp.wtms = _T("���±�ż�bm�ž�Ϊ��; ");
			m_vecLog.push_back(temp);
		}		
	}
	else
	{
		m_sW = sW;//���õ��±��
		m_sBm = sBm;//bm�����ü��洢
		if (sDllx!=_T(""))
		{
			m_sDllx = sDllx;
		}
	}
	for (int j=3;j<=iRowNum;j++)
	{
		Log temp;
		temp.sheet = sI;
		temp.row.Format(_T("%d"), j);

		CString sDljt = excel.GetCString(2, j);
		CString sWzdm = excel.GetCString(3, j);
		CString sWh = excel.GetCString(4, j);
		CString sDybs = excel.GetCString(5, j);
		if (sDljt!=_T("")&&(sWzdm==_T("")||sWh==_T("")||sDybs==_T("")))
		{
			if (sWzdm==_T(""))
			{
				temp.col = _T("3");
				sTempPrompt += _T("A��:���½�ͷΪ��; ");
				temp.wtms = _T("A��:���½�ͷΪ��; ");
				m_vecLog.push_back(temp);
			}
			if (sWh == _T(""))
			{
				temp.col = _T("4");
				sTempPrompt += _T("A��:λ��Ϊ��; ");
				temp.wtms = _T("A��:λ��Ϊ��; ");
				m_vecLog.push_back(temp);
			}
			if (sDybs==_T(""))
			{
				temp.col = _T("5");
				sTempPrompt += _T("A��:��ӡ��ʶΪ��; ");
				temp.wtms = _T("A��:��ӡ��ʶΪ��; ");
				m_vecLog.push_back(temp);
			}
		}
		CString sDljt2 = excel.GetCString(8, j);
		CString sWzdm2 = excel.GetCString(9, j);
		CString sWh2 = excel.GetCString(10, j);
		CString sDybs2 = excel.GetCString(11, j);
		if (sDljt2!=_T("")&&(sWzdm2==_T("")||sWh2==_T("")||sDybs2==_T("")))
		{
			if (sWzdm2 == _T(""))
			{
				temp.col = _T("9");
				sTempPrompt += _T("B��:���½�ͷΪ��; ");
				temp.wtms = _T("B��:���½�ͷΪ��; ");
				m_vecLog.push_back(temp);
			}
			if (sWh2 == _T(""))
			{
				temp.col = _T("10");
				sTempPrompt += _T("B��:λ��Ϊ��; ");
				temp.wtms = _T("B��:λ��Ϊ��; ");
				m_vecLog.push_back(temp);
			}
			if (sDybs2 == _T(""))
			{
				temp.col = _T("11");
				sTempPrompt += _T("B��:��ӡ��ʶΪ��; ");
				temp.wtms = _T("B��:��ӡ��ʶΪ��; ");
				m_vecLog.push_back(temp);
			}
		}
	}
	if (sTempPrompt!=_T(""))
	{
		sTempPrompt = _T("��") + sI + _T("ҳ:") + sTempPrompt;
		sPrompt += sTempPrompt;
		sPrompt += _T(" ����excel�����µ���!");
	}

	excel.Quit();
	if (sPrompt!=_T(""))
	{
//		AfxMessageBox(sPrompt);
		CString sPath = GetExcelLogPath();
		cExcel excel;
		if (!excel.StartApp())
		{
			AfxMessageBox(_T("��־�ļ���ʧ��"));
			return FALSE;
		}
		excel.OpenWorkBook(sPath);
		for (int i = 0;i<m_vecLog.size();i++)
		{
			Log temp = m_vecLog[i];
			excel.PutValue(1, i + 2, temp.sheet);
			excel.PutValue(2, i + 2, temp.row);
			excel.PutValue(3, i + 2, temp.col);
			excel.PutValue(4, i + 2, temp.wtms);
		}
		CString sExcelPath;
		sExcelPath = GetLogFolderPath() + GetTimer();
		excel.SaveAs(sExcelPath);
		excel.Quit();
		ShellExecute(
			0,
			_T("open"),
			sExcelPath+_T(".xlsx"),
			NULL,
			NULL,
			SW_SHOWNORMAL);
		return FALSE;
	}
	return TRUE;
} 

void CDlgPpsj::GetDlInfo()
{
	cExcel excel;
	if (!excel.StartApp())
	{
		AfxMessageBox(_T("��excelʧ��"));
		return;
	}
	excel.OpenWorkBook(m_sDlljgxb);

	excel.SwitchToSheet(1);
	//��ȡexcle �����Լ���ʼ��Ĭ��1��1
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

	int iMark1 = 1, iMark2 = 1;
	CString LEFT, RIGHT;//���ұ��
	CString LOC1, LOC2;//λ��1λ��2
	CString WZDM1=_T(""), WZDM2=_T("");//�������ʴ������ֶ���ͷ

	m_vecLeft.clear();
	m_vecRight.clear();
	m_vecDlgg.clear();

	for (int i=3;i<=iRowNum;i++)
	{
		BOOL bLeftChange = FALSE, bRightChange = FALSE;

		dlljqInfo leftTemp, rightTemp;
		CString sDljt = excel.GetCString(2, i);
		CString sWzdm = excel.GetCString(3, i);
		CString sWh = excel.GetCString(4, i);
		CString sDybs = excel.GetCString(5, i);
		leftTemp.dljt = sDljt;
		leftTemp.wzdm = sWzdm;
		leftTemp.wh = sWh;
		leftTemp.dybs = sDybs;

		if (sWzdm==_T(""))
		{
			continue;
		}
		
		CString sDljt2 = excel.GetCString(8, i);
		CString sWzdm2 = excel.GetCString(9, i);
		CString sWh2 = excel.GetCString(10, i);
		CString sDybs2 = excel.GetCString(11, i);
		rightTemp.dljt = sDljt2;
		rightTemp.wzdm = sWzdm2;
		rightTemp.wh = sWh2;
		rightTemp.dybs = sDybs2;
		
		if (sWzdm2==_T(""))
		{
			continue;
		}

		CString sXlcl,sXlwzdm;//���²��� �������ʴ���
		sXlcl=excel.GetCString(14, i);
		sXlwzdm=excel.GetCString(15, i);

		CString sZuo, sYou;//�����ļ��ж�ȡ����
		CIniFile ini(GetIniPath());
		ini.GetValueOfKey(_T("PPSJ"), _T("LEFT"), sZuo);
		ini.GetValueOfKey(_T("PPSJ"), _T("RIGHT"), sYou);

		if (WZDM1 == _T(""))
		{
			WZDM1 = sWzdm;
			CString sI;
			sI.Format(_T("%d"), iMark1);
			LOC1 = sZuo + sI;
			iMark1++;

			m_vecLeft.push_back(leftTemp);
			bLeftChange = TRUE;
		}
		else
		{
			if (sWzdm!=WZDM1)
			{
				WZDM1 = sWzdm;
				CString sI;
				sI.Format(_T("%d"), iMark1);
				LOC1 = sZuo + sI;
				iMark1++;

				m_vecLeft.push_back(leftTemp);
				bLeftChange = TRUE;
			}
		}
		if (WZDM2 == _T(""))
		{
			WZDM2 = sWzdm2;
			CString sI;
			sI.Format(_T("%d"), iMark2);
			LOC2 = sYou + sI;
			iMark2++;

			m_vecRight.push_back(rightTemp);
			bRightChange = TRUE;
		}
		else
		{
			if (sWzdm2!=WZDM2)
			{

				WZDM2 = sWzdm2;
				CString sI;
				sI.Format(_T("%d"), iMark2);
				LOC2 = sYou + sI;
				iMark2++;

				m_vecRight.push_back(rightTemp);
				bRightChange = TRUE;
			}
		}
		if (bLeftChange!=FALSE||bRightChange!=FALSE)
		{
			dlggInfo temp;
			temp.LEFTLOCATION = LOC1;
			temp.RIGHTLOCATION = LOC2;
			temp.XLCL = sXlcl;
			temp.XLWZDM = sXlwzdm;
			m_vecDlgg.push_back(temp);
		}
	}		
	excel.Quit();
	return;
}

CString CDlgPpsj::GetDlType(int iLeft, int iRight)
{
	CString sL, sR;
	sL = NumberConver(iLeft);
	sR = NumberConver(iRight);
	CString sRet = sL + _T("��") + sR;
	if (sRet==_T("һ��һ"))
	{
		sRet = _T("����");
	}
	return sRet;
}

void CDlgPpsj::FillListLjq()
{
	CString sZuo, sYou;//�����ļ��ж�ȡ����
	CIniFile ini(GetIniPath());
	ini.GetValueOfKey(_T("PPSJ"), _T("LEFT"), sZuo);
	ini.GetValueOfKey(_T("PPSJ"), _T("RIGHT"), sYou);

	m_mapLoc.clear();
	char wc = 'A';

	int iXhMark = 1;
	m_list_Ljqxh.DeleteAllItems();
	for (int i = 0; i < m_vecLeft.size();i++)
	{
		CString sXhMark;
		sXhMark.Format(_T("%d"), iXhMark);
		CString sI;
		int iTemp = i + 1;
		sI.Format(_T("%d"), iTemp);
		CString sWz = sZuo + sI;
		int nRow=m_list_Ljqxh.InsertItem(i, _T(""));
		m_list_Ljqxh.SetItemText(nRow, 0, sWz);
		m_list_Ljqxh.SetItemText(nRow, 1, m_vecLeft[i].dljt);
		m_list_Ljqxh.SetItemText(nRow, 2, m_vecLeft[i].wzdm);
		m_list_Ljqxh.SetItemText(nRow, 3, sXhMark);
		iXhMark++;
		m_mapLoc.insert(pair<CString, char>(sWz, wc));
		wc++;
	}
	int nCount = m_list_Ljqxh.GetItemCount();
	for (int j = 0; j < m_vecRight.size();j++)
	{
		CString sXhMark;
		sXhMark.Format(_T("%d"), iXhMark);
		CString sJ;
		int iTemp = j + 1;
		sJ.Format(_T("%d"), iTemp);
		CString sWz = sYou + sJ;
		int nRow = m_list_Ljqxh.InsertItem(j+nCount, _T(""));
		m_list_Ljqxh.SetItemText(nRow, 0, sWz);
		m_list_Ljqxh.SetItemText(nRow, 1, m_vecRight[j].dljt);
		m_list_Ljqxh.SetItemText(nRow, 2, m_vecRight[j].wzdm);
		m_list_Ljqxh.SetItemText(nRow, 3, sXhMark);
		iXhMark++;
		m_mapLoc.insert(pair<CString, char>(sWz, wc));
		wc++;
	}
}

void CDlgPpsj::FillListDlgg()
{
	m_list_Dlgg.DeleteAllItems();
	for (int i = 0; i < m_vecDlgg.size(); i++)
	{
		dlggInfo temp=m_vecDlgg[i];
		int nRow = m_list_Dlgg.InsertItem(i, _T(""));
		m_list_Dlgg.SetItemText(nRow, 0, temp.LEFTLOCATION);
		m_list_Dlgg.SetItemText(nRow, 1, temp.RIGHTLOCATION);
		m_list_Dlgg.SetItemText(nRow, 2, temp.XLCL);
		m_list_Dlgg.SetItemText(nRow, 3, temp.XLWZDM);
	}
}

BOOL CDlgPpsj::GetDljxbInfo()
{
	UpdateData(TRUE);
	CString sZuo, sYou;
	CIniFile ini(GetIniPath());
	ini.GetValueOfKey(_T("PPSJ"), _T("LEFT"), sZuo);
	ini.GetValueOfKey(_T("PPSJ"), _T("RIGHT"), sYou);
	vector<dlggInfo> vecDlggInfo;
	for (int i = 0; i < m_list_Dlgg.GetItemCount();i++)
	{
		dlggInfo temp;
		temp.LEFTLOCATION = m_list_Dlgg.GetItemText(i, 0);
		temp.RIGHTLOCATION = m_list_Dlgg.GetItemText(i, 1);
		temp.XLCL = m_list_Dlgg.GetItemText(i, 2);
		temp.XLWZDM = m_list_Dlgg.GetItemText(i, 3);
		vecDlggInfo.push_back(temp);
	}

	if (m_sDlljgxb==_T(""))
	{
		AfxMessageBox(_T("�������ӹ�ϵ��Ϊ��,�޷����ɱ��"));
		return FALSE;
	}
	cExcel excel;
	if (!excel.StartApp())
	{
		acutPrintf(_T("\n��excelʧ��."));
		return FALSE;
	}
	m_vecTabInfo.clear();
	excel.OpenWorkBook(m_sDlljgxb);
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
	int iXxh = 1;

	//���ڶ�λ����Ϣ������һ�������
	int iMark1 = 1, iMark2 = 1;
	CString LEFT, RIGHT;
	CString LOC1, LOC2;
	CString WZDM1=_T(""),WZDM2=_T("");

	for (int i = 3; i <= iRowNum;i++)
	{
		dljxbInfo temp;
		CString sXxh;
		sXxh.Format(_T("%d"), iXxh);
		iXxh++;
		temp.xxh=sXxh;
		temp.zjh1 = excel.GetCString(6, i);
		temp.zjh2 = excel.GetCString(12, i);
		temp.xx = excel.GetCString(14, i);
		temp.cd = excel.GetCString(16, i);
		if (temp.cd.Left(1)==_T("."))
		{
			temp.cd = _T("0") + temp.cd;
		}
		temp.bz = _T("");

		CString sDljt = excel.GetCString(2, i);
		CString sDljt2 = excel.GetCString(8, i);

		CString sWzdm = excel.GetCString(3, i);
		CString sWzdm2 = excel.GetCString(9, i);
		if (sWzdm==_T(""))
		{
			continue;
		}
		if (sWzdm2==_T(""))
		{
			continue;
		}
		if (WZDM1 == _T(""))
		{
			WZDM1 = sWzdm;
			CString sI;
			sI.Format(_T("%d"), iMark1);
			LOC1 = sZuo + sI;
			iMark1++;
		}
		else
		{
			if (sWzdm!=WZDM1)
			{
				WZDM1 = sWzdm;
				CString sI;
				sI.Format(_T("%d"), iMark1);
				LOC1 = sZuo + sI;
				iMark1++;
			}
		}
		if (WZDM2==_T(""))
		{
			WZDM2 = sWzdm2;
			CString sI;
			sI.Format(_T("%d"), iMark2);
			LOC2 = sYou + sI;
			iMark2++;
		}
		else
		{
			if (sWzdm2!=WZDM2)
			{
				WZDM2 = sWzdm2;
				CString sI;
				sI.Format(_T("%d"), iMark2);
				LOC2 = sYou + sI;
				iMark2++;
			}
		}
		map<CString,char>::iterator itr=m_mapLoc.find(LOC1);
		if (itr!=m_mapLoc.end())
		{
			char c1 = itr->second;
			temp.lx = c1;
		}	
		map<CString, char>::iterator itr2 = m_mapLoc.find(LOC2);
		if (itr2!=m_mapLoc.end())
		{
			char c2 = itr2->second;
			temp.qx = c2;
		}
		
		for (int j = 0;j<vecDlggInfo.size();j++)
		{
			dlggInfo temp2 = vecDlggInfo[j];
			if (temp2.LEFTLOCATION==LOC1&&temp2.RIGHTLOCATION==LOC2)
			{
				temp.xx = temp2.XLCL;
				break;
			}
		}
		m_vecTabInfo.push_back(temp);
	}
	excel.Quit();
	return TRUE;
}

BOOL CDlgPpsj::CreatDljxb(AcGePoint3d ptInsert)
{
	UpdateData(TRUE);
	int iLen = m_vecTabInfo.size();
	if (iLen==0)
	{
		return FALSE;
	}

	AcDbTable *pTable = new AcDbTable;
	AcDbDictionary *pDict = NULL;
	AcDbObjectId idTblStyle;
	acdbHostApplicationServices()->workingDatabase()->getTableStyleDictionary(pDict, AcDb::kForRead);
	pDict->getAt(_T("Standard"), idTblStyle);
	pDict->close();
//	AcDbObjectId idTblStyle = AddTableStyle();

	pTable->setTableStyle(idTblStyle);
    pTable->setTextStyle(CTextStyleUtil::GetAt(_T("Standard")));

	pTable->setNumColumns(8);
	pTable->setNumRows(iLen + 2);

	pTable->generateLayout();
	pTable->suppressHeaderRow(true);//���ñ���

	pTable->setPosition(AcGePoint3d(ptInsert.x-170,ptInsert.y -72, 0));

	
	for (int j = 0; j < iLen+1;j++)
	{
		pTable->setRowHeight(j, 6.4);
		pTable->setAlignment(AcDb::kMiddleCenter,j);
	}
	pTable->setColumnWidth(0, 16);
	pTable->setColumnWidth(1, 21);
	pTable->setColumnWidth(2, 16);
	pTable->setColumnWidth(3, 21);
	pTable->setColumnWidth(4, 19);
	pTable->setColumnWidth(5, 60);
	pTable->setColumnWidth(6, 14);
	pTable->setColumnWidth(7, 16);

	pTable->setTextHeight(3);

	pTable->setTextString(1, 0, _T("о�ߺ�"));
	pTable->setTextString(1, 1, _T("����"));
	pTable->setTextString(1, 2, _T("��ź�"));
	pTable->setTextString(1, 3, _T("ȥ��"));
	pTable->setTextString(1, 4, _T("��ź�"));
	pTable->setTextString(1, 5, _T("����"));
	pTable->setTextString(1, 6, _T("����"));
	pTable->setTextString(1, 7, _T("��ע"));
	for (int i = 0; i < iLen; i++)
	{
		pTable->setTextString(i + 2, 0, m_vecTabInfo[i].xxh);
		pTable->setTextString(i + 2, 1, m_vecTabInfo[i].lx);
		pTable->setTextString(i + 2, 2, m_vecTabInfo[i].zjh1);
		pTable->setTextString(i + 2, 3, m_vecTabInfo[i].qx);
		pTable->setTextString(i + 2, 4, m_vecTabInfo[i].zjh2);
		pTable->setTextString(i + 2, 5, m_vecTabInfo[i].xx);
		pTable->setTextString(i + 2, 6, m_vecTabInfo[i].cd);
		pTable->setTextString(i + 2, 7, m_vecTabInfo[i].bz);
	}
	pTable->deleteRows(0);
	CDwgDatabaseUtil::PostToModelSpace(pTable);
	actrTransactionManager->flushGraphics(); /*refresh screen*/
	acedUpdateDisplay();
	return TRUE;
}

void CDlgPpsj::ShowEdit(bool bShow, int nItem, int nSubItem, CRect rc)
{
	if (m_Edit.m_hWnd==NULL)
	{
		m_Edit.Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN | WS_BORDER, CRect(0, 0, 0, 0), GetDlgItem(IDC_LIST_LJQ), IDC_EDIT_MOD);
		m_Edit.ShowWindow(SW_HIDE);

		CFont tpFont;
		tpFont.CreateStockObject(DEFAULT_GUI_FONT);
		m_Edit.SetFont(&tpFont);
		tpFont.DeleteObject();
	}
	if (bShow == TRUE)
	{
		CString strItem = m_list_Ljqxh.GetItemText(nItem, nSubItem);
		rc.top += 317;
		rc.bottom += 317;
		rc.left += 47;
		rc.right += 47;
		m_Edit.MoveWindow(&rc);
		m_Edit.ShowWindow(SW_SHOW);
		m_Edit.SetWindowText(strItem);
		m_Edit.SetFocus();
		m_Edit.SetSel(-1);
	}
	else
		m_Edit.ShowWindow(SW_HIDE);
}

BOOL CDlgPpsj::CreatDlDwg(CString sBlockName,AcGePoint3d ptInsert)
{
	AcDbObjectId idBlockDef = CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), sBlockName);
	if (idBlockDef==AcDbObjectId::kNull)
	{
		CString sPrompt;
		sPrompt.Format(_T("δ�ҵ�: %s ͼ��."),sBlockName);
		AfxMessageBox(sPrompt);
		return FALSE;
	}
	AcDbObjectId idDlmb= CBlockUtil::InsertBlockRef(idBlockDef, ptInsert);
	AcDbBlockReference *pRef = NULL;
	Acad::ErrorStatus es;
	es = acdbOpenObject(pRef, idDlmb, AcDb::kForWrite);
	if (es!=eOk)
	{
		return FALSE;
	}
	AcDbVoidPtrArray ptArr;
	pRef->explode(ptArr);
	pRef->erase();
	pRef->close();
	int iNum = ptArr.length();
	int iMark = 1;
	for (int i = 0; i < iNum;i++)
	{
		ACHAR *cName;
		AcDbBlockReference *pRefLocation = static_cast<AcDbBlockReference*>(ptArr[i]);
		AcGePoint3d ptDlljqLocation = pRefLocation->position();

		AcDbBlockTableRecord *pRec = NULL;
		AcDbObjectId idTemp = pRefLocation->blockTableRecord();

		Acad::ErrorStatus es;
		es = acdbOpenObject(pRec, idTemp, AcDb::kForWrite);
		if (es==eOk)
		{
			pRec->getName(cName);
		    CString sName;
			sName.Format(_T("%s"), cName);
			std::vector<CString> vecStr;
			CStringUtil::Split(sName, _T("-"), vecStr, false);
			size_t sit = vecStr.size();
			if (sit==2)
			{
				CString s1, s2;
				s1 = vecStr[0];
				s2 = vecStr[1];
				CreatLjqDwg(s2, ptDlljqLocation,iMark);
				pRefLocation->close();
			}
			if (sit==1)
			{
				CDwgDatabaseUtil::SetXdata(_T("����ͼ��"), _T("��"), pRefLocation);
				CDwgDatabaseUtil::PostToModelSpace(pRefLocation);
			}
			pRec->close();
		}	
		else
		{
			pRefLocation->close();
		}		
	}
	return TRUE;
}

BOOL CDlgPpsj::CreatLjqDwg(CString sLocation, AcGePoint3d ptInsert,int &iMark)
{
	int iLoc=sLocation.Find(_T("z"));
	int iLoc2 = sLocation.Find(_T("y"));
	CString sZuo, sYou;
	CIniFile ini(GetIniPath());
	ini.GetValueOfKey(_T("PPSJ"), _T("LEFT"), sZuo);
	ini.GetValueOfKey(_T("PPSJ"), _T("RIGHT"), sYou);
	CString sLoc;//����ȷ��ͼ��λ�� �޸�����
	if (iLoc!=-1)
	{
		sLoc = _T("L-");
		sLocation.Replace(_T("z"), sZuo);
	}
	if (iLoc2!=-1)
	{
		sLoc = _T("R-");
		sLocation.Replace(_T("y"), sYou);
	}
	int iNum = m_vecLocAndName.size();
	for (int i = 0; i < iNum;i++)
	{
		dlLocationAndName temp = m_vecLocAndName[i];
		if (temp.LOCATION==sLocation)
		{
			CString sBlockName;
			CString sMC, sXHGG;
			sMC = DisposeBlockName(temp.NAME);
			int iTemp = temp.NAME.Find(_T("("));
			sXHGG=temp.NAME.Left(iTemp);
			sBlockName=sLoc+sMC;
			AcDbObjectId idBlock= CBlockUtil::CopyBlockDefFromOtherDwg(GetBlockLibPath(), sBlockName);
			if (idBlock!=AcDbObjectId::kNull)
			{
				CBlockUtil::InsertBlockRef(idBlock, ptInsert);

				FjMark markTemp;
				CString sWh;
				sWh.Format(_T("%d"), iMark);
				iMark++;
				markTemp.WH = sWh;
				markTemp.DW = _T("");
				markTemp.DH = temp.WZDM;
				markTemp.SL = _T("1");
				markTemp.MC = sMC;
				markTemp.GGXH = sXHGG;
				CreatMark(markTemp, ptInsert);
				return TRUE;
			}
			else
			{
				CString sPrompt;
				sPrompt.Format(_T("������: %s ͼ��δ�ҵ���"), temp.NAME);
				acutPrintf(sPrompt);
				return FALSE;
			}
		}
	}
	return FALSE;
}

void CDlgPpsj::CreatMark(FjMark temp, AcGePoint3d ptInsert)
{
	AcGePoint3d pt2, pt3,ptText;
	pt2 = AcGePoint3d(ptInsert.x + m_dX, ptInsert.y + m_dY, 0);
	pt3 = AcGePoint3d(pt2.x + m_dLen, pt2.y, 0);
	ptText = AcGePoint3d(pt2.x + 1.95, pt2.y + 1.16, 0);

	AcDbPolyline *pPoly = new AcDbPolyline;
	pPoly->addVertexAt(0, CConvertUtil::ToPoint2d(ptInsert));
	pPoly->addVertexAt(1, CConvertUtil::ToPoint2d(pt2));
	pPoly->addVertexAt(2, CConvertUtil::ToPoint2d(pt3));
	CDwgDatabaseUtil::PostToModelSpace(pPoly);

	AcDbText *pText = new AcDbText;
	CString sWh = temp.WH;
	pText->setTextString(sWh);
	pText->setWidthFactor(0.6);
	pText->setHeight(5);
	pText->setPosition(ptText);
	CDwgDatabaseUtil::SetXdata(_T("λ��"), temp.WH, pText);
	CDwgDatabaseUtil::SetXdata(_T("��λ"), temp.DW, pText);
	CDwgDatabaseUtil::SetXdata(_T("����"), temp.DH, pText);
	CDwgDatabaseUtil::SetXdata(_T("����"), temp.SL, pText);
	CDwgDatabaseUtil::SetXdata(_T("����"), temp.MC, pText);
	CDwgDatabaseUtil::SetXdata(_T("���"), temp.GGXH, pText);
	CDwgDatabaseUtil::PostToModelSpace(pText);
}

CString CDlgPpsj::DisposeBlockName(CString sName)
{
	int iMark1, iMark2;
	iMark1 = sName.Find(_T("("));
	iMark2 = sName.Find(_T(")"));
	if (iMark1>iMark2 || iMark1 == -1 || iMark2 == -1)
	{
		return sName;
	}
	CString sRetName=sName.Mid(iMark1+1, iMark2 - iMark1-1);
	return sRetName;
}

#define COLOR 1

BOOL CDlgPpsj::CreatDlYzb(CString sYzbName,BOOL bLh,AcGePoint3d ptInsert)
{
	AcDbObjectId idDef=CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), sYzbName);
	if (idDef==AcDbObjectId::kNull)
	{
		AfxMessageBox(_T("δ�ҵ�ӡ�ֱ�ͼ��"));
		return FALSE;
	}
	AcDbObjectId idBlock=CBlockUtil::InsertBlockRefWithAttribute(idDef, AcGePoint3d(ptInsert.x+30,ptInsert.y -72, 0));
	AcDbBlockReference *pRef = NULL;
	Acad::ErrorStatus es;
	es = acdbOpenObject(pRef, idBlock, AcDb::kForWrite);
	if (es!=eOk)
	{
		AfxMessageBox(_T("��ӡ�ֱ�ͼ��ʧ��"));
		return FALSE;
	}
	if (bLh)
	{
		CBlockUtil::SetBlockRefAttribute(pRef, _T("����1"), m_sW, COLOR);
		CBlockUtil::SetBlockRefAttribute(pRef, _T("���±��1"), m_sBm, COLOR);
		CBlockUtil::SetBlockRefAttribute(pRef, _T("����2"), m_sW, COLOR);
		CBlockUtil::SetBlockRefAttribute(pRef, _T("���±��2"), m_sBm, COLOR);
		CBlockUtil::SetBlockRefAttribute(pRef, _T("����3"), m_sW, COLOR);
		CBlockUtil::SetBlockRefAttribute(pRef, _T("���±��3"), m_sBm, COLOR);

		int iMark = 1;
		for (int i = 0; i < m_vecLeft.size(); i++)
		{
			dlljqInfo temp = m_vecLeft[i];
			CString sI;
			sI.Format(_T("%d"), iMark);
			CString sWh =_T("1-") + sI + _T("��λ��");//��ͬ�˵�λ�ű�ʶ
			CString sBh = _T("1-���±��-") + sI;//��ͬ�˵ĵ��±��
			CString sWh2 = _T("2-") + sI + _T("��λ��");//��ͬ�˵�λ�ű�ʶ
			CString sBh2 = _T("2-���±��-") + sI;//��ͬ�˵ĵ��±��
			CString sWh3 = _T("3-") + sI + _T("��λ��");//��ͬ�˵�λ�ű�ʶ
			CString sBh3 = _T("3-���±��-") + sI;//��ͬ�˵ĵ��±��
			CBlockUtil::SetBlockRefAttribute(pRef, sWh, temp.wh, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sBh, temp.dybs, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sWh2, temp.wh, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sBh2, temp.dybs, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sWh3, temp.wh, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sBh3, temp.dybs, COLOR);
			iMark++;
		}
		for (int i = 0; i < m_vecRight.size(); i++)
		{
			dlljqInfo temp = m_vecRight[i];
			CString sI;
			sI.Format(_T("%d"), iMark);
			CString sWh =_T("1-") + sI + _T("��λ��");//��ͬ�˵�λ�ű�ʶ
			CString sBh = _T("1-���±��-") + sI;//��ͬ�˵ĵ��±��
			CString sWh2 = _T("2-") + sI + _T("��λ��");//��ͬ�˵�λ�ű�ʶ
			CString sBh2 = _T("2-���±��-") + sI;//��ͬ�˵ĵ��±��
			CString sWh3 = _T("3-") + sI + _T("��λ��");//��ͬ�˵�λ�ű�ʶ
			CString sBh3 = _T("3-���±��-") + sI;//��ͬ�˵ĵ��±��
			CBlockUtil::SetBlockRefAttribute(pRef, sWh, temp.wh, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sBh, temp.dybs, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sWh2, temp.wh, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sBh2, temp.dybs, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sWh3, temp.wh, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sBh3, temp.dybs, COLOR);
			iMark++;
		}
	}
	else
	{
		CBlockUtil::SetBlockRefAttribute(pRef, _T("����"), m_sBm, COLOR);
		CBlockUtil::SetBlockRefAttribute(pRef, _T("���±��"), m_sW, COLOR);

		int iMark = 1;
		for (int i = 0; i < m_vecLeft.size(); i++)
		{
			dlljqInfo temp = m_vecLeft[i];
			CString sI;
			sI.Format(_T("%d"), iMark);
			CString sWh = sI + _T("��λ��");//��ͬ�˵�λ�ű�ʶ
			CString sBh = _T("���±��-") + sI;//��ͬ�˵ĵ��±��
			CBlockUtil::SetBlockRefAttribute(pRef, sWh, temp.wh, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sBh, temp.dybs, COLOR);
			iMark++;
		}
		for (int i = 0; i < m_vecRight.size(); i++)
		{
			dlljqInfo temp = m_vecRight[i];
			CString sI;
			sI.Format(_T("%d"), iMark);
			CString sWh = sI + _T("��λ��");//��ͬ�˵�λ�ű�ʶ
			CString sBh = _T("���±��-") + sI;//��ͬ�˵ĵ��±��
			CBlockUtil::SetBlockRefAttribute(pRef, sWh, temp.wh, COLOR);
			CBlockUtil::SetBlockRefAttribute(pRef, sBh, temp.dybs, COLOR);
			iMark++;
		}
	}	
	pRef->close();

	return TRUE;
}

void CDlgPpsj::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	this->ShowWindow(SW_HIDE);
	this->GetParent()->SetFocus();
	AcGePoint3d pt;
	bool b=CGetInputUtil::GetPoint(_T("\nѡ�����ͼ��λ��:"), pt);
	if (!b)
	{
		this->ShowWindow(SW_SHOW);
		this->SetFocus();
		return;
	}
	int iCount = m_list_Ljqxh.GetItemCount();
	if (iCount==0)
	{
		AfxMessageBox(_T("��������Ϣ����"));
		return;
	}
	for (int i = 0; i < iCount;i++)
	{
		dlLocationAndName temp;
		temp.LOCATION = m_list_Ljqxh.GetItemText(i, 0);
		temp.NAME = m_list_Ljqxh.GetItemText(i, 1);
		temp.WZDM = m_list_Ljqxh.GetItemText(i, 2);
		m_vecLocAndName.push_back(temp);
	}
	CString sDllx, sDlljxs;
	GetDlgItemText(IDC_CMB_DLLX, sDllx);
	GetDlgItemText(IDC_CMB_DLLJ, sDlljxs);
	CString sBlockName=sDllx+sDlljxs;
	CString sYzbName = sBlockName + _T("-ӡ�ֱ�");//���ݵ������ƻ��ӡ�ֱ�����
	if (m_bLh)
	{
		sBlockName += _T("����");
		sYzbName += _T("-����");
	}

// 	AcDbObjectId idBlockDef=CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), sBlockName);
// 	CBlockUtil::InsertBlockRef(idBlockDef,AcGePoint3d::kOrigin);

	CreatDlDwg(sBlockName, pt);//���Ƶ���ͼ

	GetDljxbInfo();//���½��߱���Ϣ��ȡ
	CreatDljxb(pt);//���½��߱�����

	CreatDlYzb(sYzbName,m_bLh,pt);
	
    SetDataBaseXdata(_T("BM"), m_sBm);
	CIniFile ini(GetIniPath());
	ini.SetValueOfKey(_T("PPSJ"), _T("DLSJB"), m_sDlljgxb);
	CDialogEx::OnOK();
}

void CDlgPpsj::OnBnClickedBtnDlmxb()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CDlgPpsj::OnNMDblclkListLjq(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DWORD   dwPos = GetMessagePos();
	CPoint   point(LOWORD(dwPos), HIWORD(dwPos));
	m_list_Ljqxh.ScreenToClient(&point);
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	m_nItem = m_list_Ljqxh.SubItemHitTest(&lvinfo);
	m_nSubItem = lvinfo.iSubItem;
	CRect rect;
	m_list_Ljqxh.GetSubItemRect(lvinfo.iItem, m_nSubItem, LVIR_LABEL, rect);
	if (m_nItem != -1)
	{
// 		ShowEdit(true, m_nItem, m_nSubItem, rect);
// 		UpdateWindow();
		if (m_nSubItem==1)
		{
			CDlgLjq ljq;
			if (ljq.DoModal() == IDOK)
			{
				m_list_Ljqxh.SetItemText(m_nItem, 1, ljq.m_sLjqxh);
				m_list_Ljqxh.SetItemText(m_nItem, 2, ljq.m_sWzdm);
				UpdateData(FALSE);
			}
		}		
	}

	*pResult = 0;
}

void CDlgPpsj::OnEnKillfocusEditMod()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString sTemp;
	m_Edit.GetWindowText(sTemp);
	if (sTemp != _T(""))
	{
		m_list_Ljqxh.SetItemText(m_nItem, m_nSubItem, sTemp);
		m_Edit.ShowWindow(SW_HIDE);
	}
	UpdateData(FALSE);
}

void CDlgPpsj::OnCbnSelchangeCmbDllj()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString sDllx,sDlljxs;
	m_cmb_Dllx.GetLBString(m_cmb_Dllx.GetCurSel(), sDllx);
	m_cmb_Dlljxs.GetLBString(m_cmb_Dlljxs.GetCurSel(), sDlljxs);
	CString sBlockName = sDllx + sDlljxs;
	CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), sBlockName);
	m_fc.Clear();
	m_fc.Init(acdbHostApplicationServices()->workingDatabase(), sBlockName);
	UpdateData(FALSE);
}

void CDlgPpsj::OnNMDblclkListDlgg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DWORD   dwPos = GetMessagePos();
	CPoint   point(LOWORD(dwPos), HIWORD(dwPos));
	m_list_Dlgg.ScreenToClient(&point);
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	m_nItem = m_list_Dlgg.SubItemHitTest(&lvinfo);
	m_nSubItem = lvinfo.iSubItem;
	CRect rect;
	m_list_Dlgg.GetSubItemRect(lvinfo.iItem, m_nSubItem, LVIR_LABEL, rect);
	if (m_nItem != -1)
	{
// 		ShowEdit(true, m_nItem, m_nSubItem, rect);
// 		UpdateWindow();
		if (m_nSubItem == 2)
		{
			CDlgDlgg dlgg;
			if (dlgg.DoModal() == IDOK)
			{
				m_list_Dlgg.SetItemText(m_nItem, 2, dlgg.m_sXlcl);
				m_list_Dlgg.SetItemText(m_nItem, 3, dlgg.m_sXlwzdm);
				UpdateData(FALSE);
			}
		}
	}
	*pResult = 0;
}


void CDlgPpsj::OnBnClickedBtnSj1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
// 	CString sTemp = GetWebexePath() + _T(" Url1");
// 	const size_t strsize = (sTemp.GetLength() + 1) * 2;
// 	char *pStr = new char[strsize];
// 	size_t sz = 0;
// 	wcstombs_s(&sz, pStr, strsize, sTemp, _TRUNCATE);
// 	int n = atoi((const char*)pStr);
// 	system(pStr);	
	wchar_t excel_file[MAX_PATH];
	glaway::LowFrequencyCableDesign(m_hWnd, excel_file);
}


void CDlgPpsj::OnBnClickedBtnSj2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
// 	CString sTemp = GetWebexePath() + _T(" Url2");
// 	const size_t strsize = (sTemp.GetLength() + 1) * 2;
// 	char *pStr = new char[strsize];
// 	size_t sz = 0;
// 	wcstombs_s(&sz, pStr, strsize, sTemp, _TRUNCATE);
// 	int n = atoi((const char*)pStr);
// 	system(pStr);

	wchar_t excel_file[MAX_PATH];
	glaway::LowFrequencyBranchCableDesign(m_hWnd, excel_file);
}


void CDlgPpsj::OnBnClickedBtnSj3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
// 	CString sTemp = GetWebexePath() + _T(" Url3");
// 	const size_t strsize = (sTemp.GetLength() + 1) * 2;
// 	char *pStr = new char[strsize];
// 	size_t sz = 0;
// 	wcstombs_s(&sz, pStr, strsize, sTemp, _TRUNCATE);
// 	int n = atoi((const char*)pStr);
// 	system(pStr);

	wchar_t excel_file[MAX_PATH];
	glaway::SingleCableDesign(m_hWnd, excel_file);
}


void CDlgPpsj::OnBnClickedBtnSj4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
// 	CString sTemp = GetWebexePath() + _T(" Url4");
// 	const size_t strsize = (sTemp.GetLength() + 1) * 2;
// 	char *pStr = new char[strsize];
// 	size_t sz = 0;
// 	wcstombs_s(&sz, pStr, strsize, sTemp, _TRUNCATE);
// 	int n = atoi((const char*)pStr);
// 	system(pStr);

	wchar_t excel_file[MAX_PATH];
	glaway::MultipleCableDesign(m_hWnd, excel_file);
}


void CDlgPpsj::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������

	CWnd *pWnd1=GetDlgItem(IDC_LIST_LJQ);
	CWnd *pWnd2 = GetDlgItem(IDC_LIST_DLGG);
	CWnd *pWnd3 = GetDlgItem(IDC_STATIC_PPXX);
	CWnd *pWnd4 = GetDlgItem(IDOK);
	if (pWnd1)
	{
		CRect rec;
		pWnd1->GetWindowRect(&rec);
		ScreenToClient(&rec);
		rec.left = rec.left;  //���ձ��������ռ����λ��
		rec.top = rec.top;
		rec.bottom = rec.bottom;
		rec.right = rec.right+(cx - m_rect.Width());
		pWnd1->MoveWindow(rec);

		int n2 = m_list_Ljqxh.GetColumnWidth(1);
		int n3 = m_list_Ljqxh.GetColumnWidth(2);

		m_list_Ljqxh.SetColumnWidth(1, n2+(cx - m_rect.Width())/2);
		m_list_Ljqxh.SetColumnWidth(2, n3+(cx - m_rect.Width())/2);
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

		int n2 = m_list_Dlgg.GetColumnWidth(2);
		int n3 = m_list_Dlgg.GetColumnWidth(3);

		m_list_Dlgg.SetColumnWidth(2, n2 + (cx - m_rect.Width()) / 2);
		m_list_Dlgg.SetColumnWidth(3, n3 + (cx - m_rect.Width()) / 2);
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
		rec.left = rec.left + (cx - m_rect.Width());  //���ձ��������ռ����λ��
		rec.top = rec.top;
		rec.bottom = rec.bottom;
		rec.right = rec.right + (cx - m_rect.Width());
		pWnd4->MoveWindow(rec);
	}
	GetClientRect(&m_rect);
}


void CDlgPpsj::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CAcUiDialog::OnPaint()
}


void CDlgPpsj::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.x=860;
	lpMMI->ptMinTrackSize.y =450;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CDlgPpsj::OnBnClickedBtnHbtab()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDlgHbTab dlg;
	dlg.DoModal();
}


void CDlgPpsj::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDlgLhxx dlg;
	dlg.DoModal();
}


void CDlgPpsj::OnBnClickedButtonConnectselect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	const wchar_t* excelpath = GetBatchDesignFoldPath();
	glaway::BatchCableDesign(m_hWnd,excelpath );
}
