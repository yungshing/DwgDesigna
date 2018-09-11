// DlgHbTab.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgHbTab.h"
#include "afxdialogex.h"


// CDlgHbTab �Ի���

IMPLEMENT_DYNAMIC(CDlgHbTab, CAcUiDialog)

CDlgHbTab::CDlgHbTab(CWnd* pParent /*=NULL*/)
: CAcUiDialog(CDlgHbTab::IDD, pParent)
{

}

CDlgHbTab::~CDlgHbTab()
{
}

void CDlgHbTab::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sDlt);
	DDX_Text(pDX, IDC_EDIT2, m_sGyk);
	DDX_Control(pDX, IDC_PROGRESS1, m_proGress);
}


BEGIN_MESSAGE_MAP(CDlgHbTab, CAcUiDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgHbTab::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgHbTab::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CDlgHbTab::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgHbTab ��Ϣ�������


void CDlgHbTab::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0,
		_T("excel��ʽ(*.xls;*.xlsx) |*.xls;*.xlsx|"), acedGetAcadFrame());
	if (importDlg.DoModal() == IDOK)
	{
		m_sDlt = importDlg.GetPathName();
	}
	else
	{
		return;
	}
	UpdateData(FALSE);
}


void CDlgHbTab::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0,
		_T("excel��ʽ(*.xls;*.xlsx) |*.xls;*.xlsx|"), acedGetAcadFrame());
	if (importDlg.DoModal() == IDOK)
	{
		m_sGyk = importDlg.GetPathName();
	}
	else
	{
		return;
	}
	UpdateData(FALSE);
}


void CDlgHbTab::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_sDlt==_T("")||m_sGyk==_T(""))
	{
		AfxMessageBox(_T("excel·������"));
		return;
	}
	BOOL b1=CheckExcelPath(m_sDlt);
	BOOL b2 = CheckExcelPath(m_sGyk);
	if (!b1||!b2)
	{
		AfxMessageBox(_T("excel������"));
		return;
	}
	cExcel excel;
	if (!excel.StartApp())
	{
		AfxMessageBox(_T("��excelʧ��"));
		return;
	}
	excel.OpenWorkBook(m_sGyk);
	excel.SwitchToSheet(1);

	//ƥ����Ϣ�������ļ���ȡ
	CIniFile ini(GetIniPath());
	CString s1, s2, s4,sDx,sPpdx,sSpdl;
	ini.GetValueOfKey(_T("MERGETABLE"), _T("A"), s1);
	ini.GetValueOfKey(_T("MERGETABLE"), _T("B"), s4);
	ini.GetValueOfKey(_T("MERGETABLE"), _T("LJQ"), s2);
	ini.GetValueOfKey(_T("MERGETABLE"), _T("DX"), sDx);
	ini.GetValueOfKey(_T("MERGETABLE"), _T("PPDX"), sPpdx);
	ini.GetValueOfKey(_T("MERGETABLE"), _T("SPDL"), sSpdl);
	m_bSp = FALSE;
	m_bAorB = TRUE;
	int nA=0, nB=0;

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

	int iMark = 1;
	int iPos = 1000 / (iRowNum - 4);
	m_sW = excel.GetCString(3, 1);
	m_sBm = excel.GetCString(3, 2);
	for (int i = 4; i <= iRowNum;i++)
	{
		//������
		m_proGress.SetPos(iPos*iMark);
		iMark++;

		CString sTemp = excel.GetCString(1, i);
		CString sWzdm, sMc, sXh,sDwzl,sYl;
		sWzdm = excel.GetCString(2, i);
		sMc = excel.GetCString(3, i);
		sXh = excel.GetCString(4, i);
		sDwzl = excel.GetCString(5, i);
		sYl = excel.GetCString(6, i);

		FjMxbInfo fjTemp;
		fjTemp.yqjhcl = sTemp;
		fjTemp.wzdm = sWzdm;
		fjTemp.mc = sMc;
		fjTemp.xh = sXh;
		fjTemp.dwzl = sDwzl;
		fjTemp.yl = sYl;
		m_vecFjInfo.push_back(fjTemp);

		for (int j = 0; j < 10;j++)
		{
			CString s3;
			s3.Format(_T("%d"), j);
			CString sNameA = s1 + (s3 == _T("0") ? _T("") : s3) + s2;//��ȡ a�������� a1�� a2��
			CString sNameB = s4 + (s3 == _T("0") ? _T("") : s3) + s2;//��ȡ b�������� b1�� b2��

			CString sNameDx = s1 + (s3 == _T("0") ? _T("") : s3) + s2 + sDx;//��ȡa������������ ���ڲ�ѯ���µ���  ��ҪΪ��Ƶ����ƥ��
			CString sNamePpdx = s1 + (s3 == _T("0") ? _T("") : s3) + s2 + sPpdx;//��ȡa��ƥ�䵼�� ���ڲ�ѯ���µ��� ��ҪΪ��Ƶ����ƥ��
			CString sNameBDx = s4 + (s3 == _T("0") ? _T("") : s3) + s2 + sDx;//��ȡb������������ ���ڲ�ѯ���µ���  ��ҪΪ��Ƶ����ƥ��
			CString sNameBPpdx = s4 + (s3 == _T("0") ? _T("") : s3) + s2 + sPpdx;//��ȡb������������ ���ڲ�ѯ���µ���  ��ҪΪ��Ƶ����ƥ��
			CString sNameSpdl = sSpdl;//�����жϵ�����Ƶ����
			
			if (sNameA==sTemp)//������A��
			{
				WzdmNameXh wzTemp;
				wzTemp.wzdm = sWzdm;
				wzTemp.mc = sMc;
				wzTemp.xh = sXh;
				m_mapYqAndMc.insert(pair<CString, WzdmNameXh>(sNameA, wzTemp));//A������������ ��Ӧ���ʴ�����Ϣ

				vector<DesginTabInfo> vecTemp = GetDesInfoToWzdm(sTemp,sWzdm);
				for (int k = 0;k<vecTemp.size();k++)
				{
					m_vecDesginInfo.push_back(vecTemp[k]);
				}
				nA++;
			}
			if (sNameB == sTemp)
			{
				CString sLjqmc = sXh + _T("(") + sMc + _T(")");
				LjqmcYqj ljqTemp;
				ljqTemp.ljqmc = sLjqmc;
				ljqTemp.yqj = sTemp;
				m_mapBdinfo.insert(pair<CString, LjqmcYqj>(sWzdm, ljqTemp));
				nB++;
			}
			if (sNameDx==sTemp||sNamePpdx==sTemp||sNameBDx==sTemp||sNameBPpdx==sTemp)
			{
				WzdmNameXh wzTemp;
				wzTemp.wzdm = sWzdm;
				wzTemp.mc = sMc;
				wzTemp.xh = sXh;
				m_mapYqAndMc.insert(pair<CString, WzdmNameXh>(sTemp, wzTemp));
			}
			if (sNameSpdl==sTemp)
			{
				WzdmNameXh wzTemp;
				wzTemp.wzdm = sWzdm;
				wzTemp.mc = sMc;
				wzTemp.xh = sXh;
				m_mapYqAndMc.insert(pair<CString, WzdmNameXh>(sTemp, wzTemp));
				m_bSp = TRUE;
			}
		}
	}
	if (nB>nA)
	{
		m_bAorB = FALSE;
	}
	excel.Quit();
	ExportDesginInfo();
	CAcUiDialog::OnOK();
}


vector<DesginTabInfo> CDlgHbTab::GetDesInfoToWzdm(CString YQJCL,CString WZDM)
{
	vector<DesginTabInfo> vecRet;

	cExcel excel;
	if (!excel.StartApp())
	{
		AfxMessageBox(_T("��excelʧ��"));
		return vecRet;
	}
	excel.OpenWorkBook(m_sDlt);
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
		CString sWzdm = excel.GetCString(4, i);
		if (sWzdm==WZDM)
		{
			DesginTabInfo temp;
			temp.Yqzjhcl = YQJCL;
			temp.wzdm = sWzdm;
			temp.xh = excel.GetCString(1, i);
			temp.wh = excel.GetCString(5, i);
			temp.dybs = excel.GetCString(6, i);
			temp.dz = excel.GetCString(7, i);
			temp.tx = excel.GetCString(8, i);
			temp.wzdm2 = excel.GetCString(10, i);
			temp.wh2 = excel.GetCString(11, i);
			temp.dybs2 = excel.GetCString(12, i);
			temp.dz2 = excel.GetCString(13, i);
			temp.tx2 = excel.GetCString(14, i);
			temp.dllx = excel.GetCString(18, i);
			vecRet.push_back(temp);
		}
	}
	excel.Quit();
	return vecRet;
}


void CDlgHbTab::ExportDesginInfo()
{
	cExcel excel;
	if (!excel.StartApp())
	{
		AfxMessageBox(_T("��excelʧ��"));
		return;
	}
	excel.OpenWorkBook(GetExcelDlgxbPath());
	excel.SwitchToSheet(1);

	CIniFile ini(GetIniPath());
	CString sDx, sPpdx, sSpdl;
	ini.GetValueOfKey(_T("MERGETABLE"), _T("DX"), sDx);
	ini.GetValueOfKey(_T("MERGETABLE"), _T("PPDX"), sPpdx);
	ini.GetValueOfKey(_T("MERGETABLE"), _T("SPDL"), sSpdl);

	//W �� bm �����
	excel.PutValue(2, 1, m_sW);
	excel.PutValue(4, 1, m_sBm);

	std::sort(m_vecDesginInfo.begin(), m_vecDesginInfo.end());
	for (int i = 0; i < m_vecDesginInfo.size();i++)
	{
		DesginTabInfo temp = m_vecDesginInfo[i];
		CString sYqj = temp.Yqzjhcl;
		CString sDlyqj = temp.Yqzjhcl + sDx;
		CString sDlyqj2 = temp.Yqzjhcl + sPpdx;
		CString sDlyqjB1;
		CString sDlyqjB2;
	
		map<CString, LjqmcYqj>::iterator itr2;
		itr2 = m_mapBdinfo.find(temp.wzdm2);
		if (itr2!=m_mapBdinfo.end())
		{
			excel.PutValue(8, i + 3, itr2->second.ljqmc);
			sDlyqjB1 = itr2->second.yqj + sDx;
			sDlyqjB2 = itr2->second.yqj + sPpdx;
		}

		map<CString, WzdmNameXh>::iterator itr;	
		map<CString, WzdmNameXh>::iterator itrB;
		itr = m_mapYqAndMc.find(sYqj);	
		//��ȡA������������
		if (itr!=m_mapYqAndMc.end())
		{
			WzdmNameXh wzTemp = itr->second;
			excel.PutValue(2,i+3,wzTemp.xh + _T("(") + wzTemp.mc + _T(")"));
		}
		if (m_bSp)
		{
			itr = m_mapYqAndMc.find(sSpdl);
			if (itr!=m_mapYqAndMc.end())
			{
				WzdmNameXh wzTemp = itr->second;
				excel.PutValue(14, i + 3, wzTemp.mc + _T(" ") + wzTemp.xh);
				excel.PutValue(15, i + 3, wzTemp.wzdm);
			}
		}
		else
		{
			itr = m_mapYqAndMc.find(sDlyqj);//���ҵ���Ԫ���� ����������
			itrB = m_mapYqAndMc.find(sDlyqjB1);
			if (itr != m_mapYqAndMc.end())
			{
				WzdmNameXh wzTemp = itr->second;
				WzdmNameXh wzTempB;
				if (itrB!=m_mapYqAndMc.end())
				{
					wzTempB = itrB->second;
				}
				CString sXlcl;
				CString sXlwzdm;
				if (wzTemp.mc==wzTempB.mc&&wzTemp.xh==wzTempB.xh&&wzTemp.wzdm==wzTempB.wzdm)
				{
					sXlcl = wzTemp.mc + _T(" ") + wzTemp.xh;
					sXlwzdm = wzTemp.wzdm;
				}
				else
				{
					sXlcl = wzTemp.mc + _T(" ") + wzTemp.xh + _T("/") + wzTempB.mc + _T(" ") + wzTempB.xh;
					sXlwzdm = wzTemp.wzdm + _T("/") + wzTempB.wzdm;
				}
				excel.PutValue(14, i + 3, sXlcl);
				excel.PutValue(15, i + 3, sXlwzdm);
			}
			else
			{
				itr = m_mapYqAndMc.find(sDlyqj2);//���� ������ƥ�䵼��
				itrB = m_mapYqAndMc.find(sDlyqjB2);
				if (itr!=m_mapYqAndMc.end())
				{
					WzdmNameXh wzTemp = itr->second;
					WzdmNameXh wzTempB;
					if (itrB != m_mapYqAndMc.end())
					{
						wzTempB = itrB->second;
					}
					CString sXlcl;
					CString sXlwzdm;
					if (wzTemp.mc == wzTempB.mc&&wzTemp.xh == wzTempB.xh&&wzTemp.wzdm == wzTempB.wzdm)
					{
						sXlcl = wzTemp.mc + _T(" ") + wzTemp.xh;
						sXlwzdm = wzTemp.wzdm;
					}
					else
					{
						sXlcl = wzTemp.mc + _T(" ") + wzTemp.xh + _T("/") + wzTempB.mc + _T(" ") + wzTempB.xh;
						sXlwzdm = wzTemp.wzdm + _T("/") + wzTempB.wzdm;
					}
					excel.PutValue(14, i + 3, sXlcl);
					excel.PutValue(15, i + 3, sXlwzdm);
				}
			}
		}
		
		excel.PutValue(1, i + 3, temp.xh);
//		excel.PutValue(2, i + 3, temp.dljt);
		excel.PutValue(3, i + 3, temp.wzdm);
		excel.PutValue(4, i + 3, temp.wh);
		excel.PutValue(5, i + 3, temp.dybs);
		excel.PutValue(6, i + 3, temp.dz);
		excel.PutValue(7, i + 3, temp.tx);
//		excel.PutValue(8, i + 3, temp.dljt2);
		excel.PutValue(9, i + 3, temp.wzdm2);
		excel.PutValue(10, i + 3, temp.wh2);
		excel.PutValue(11, i + 3, temp.dybs2);
		excel.PutValue(12, i + 3, temp.dz2);
		excel.PutValue(13, i + 3, temp.tx2);
//		excel.PutValue(14, i + 3, temp.xlcl);
//		excel.PutValue(15, i + 3, temp.xlwzdm);
		excel.PutValue(16, 1 + 3, temp.cd);
		excel.PutValue(17, i + 3, temp.dllx);
	}
	excel.SwitchToSheet(2);
	for (int i = 0;i<m_vecFjInfo.size();i++)
	{
		FjMxbInfo fjTemp = m_vecFjInfo[i];
		excel.PutValue(1, i + 2, fjTemp.yqjhcl);
		excel.PutValue(2, i + 2, fjTemp.wzdm);
		excel.PutValue(3, i + 2, fjTemp.mc);
		excel.PutValue(4, i + 2, fjTemp.xh);
		excel.PutValue(5, i + 2, fjTemp.dwzl);
		excel.PutValue(6, i + 2, fjTemp.yl); 
	}

	CString sSavePath;
	CString sSaveTemp = GetTimer() + _T("���½�����Ʊ�");
	CFileDialog dlgFile(FALSE, _T("xlsx"), sSaveTemp, OFN_HIDEREADONLY, _T("excelFile(*.xlsx)|*.xlsx|excelFile (*.xls)|*.xls||"), NULL);
	if (IDOK==dlgFile.DoModal())
	{
		sSavePath = dlgFile.GetPathName();
	}
	else
	{
		excel.Quit();
		return;
	}
	excel.SaveAs(sSavePath);
	excel.Quit();
	return;
}


BOOL CDlgHbTab::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_proGress.SetRange(0, 1000);
	m_proGress.SetStep(1);
	m_proGress.SetPos(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
