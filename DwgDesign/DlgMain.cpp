// DlgMain.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgMain.h"
#include "afxdialogex.h"

CDlgMain *pDlg = NULL;

// CDlgMain 对话框

IMPLEMENT_DYNAMIC(CDlgMain, CAcUiTabMainDialog)

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
: CAcUiTabMainDialog(CDlgMain::IDD, pParent)
{
	m_bSelect = FALSE;
	m_bShowPrompt = TRUE;
	m_bZh = TRUE;
	m_bWcl = FALSE;
	m_bYcl = FALSE;
// 	m_sDqtx = _T("C:\\Users\\xzh\\Desktop\\装配资料\\电气特性连接表.xlsx");
// 	m_sJxb = _T("C:\\Users\\xzh\\Desktop\\装配资料\\2.617.30015JL（接线表样例）.xls");
}

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabMainDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
	DDX_Text(pDX, IDC_EDIT_PATH_DQTX, m_sDqtx);
	DDX_Text(pDX, IDC_EDIT_PATH_JXB, m_sJxb);
	DDX_Text(pDX, IDC_EDIT_PATH_ZJYS, m_sZjys);
	DDX_Check(pDX, IDC_RADIO_YCL, m_bYcl);
	DDX_Check(pDX, IDC_RADIO_WCL, m_bWcl);
	DDX_Check(pDX, IDC_RADIO_ZH, m_bZh);
	DDX_Control(pDX, IDC_CMB_VIEW, m_cmb_View);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_sSearch);
}

BEGIN_MESSAGE_MAP(CDlgMain, CAcUiTabMainDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnACADKeepFocus)
	ON_BN_CLICKED(IDC_BTN_SELECTBLOCK, &CDlgMain::OnBnClickedBtnSelectBlock)
	ON_BN_CLICKED(IDC_BTN_DQTX, &CDlgMain::OnBnClickedBtnDqtx)
	ON_BN_CLICKED(IDC_BTN_JXB, &CDlgMain::OnBnClickedBtnJxb)
	ON_BN_CLICKED(IDC_BTN_CREATMARK, &CDlgMain::OnBnClickedBtnCreatmark)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_CRETEJXB, &CDlgMain::OnBnClickedBtnCretejxb)
	ON_BN_CLICKED(IDC_BTN_REFLIST, &CDlgMain::OnBnClickedBtnReflist)
	ON_BN_CLICKED(IDC_BTN_CHECKINFO, &CDlgMain::OnBnClickedBtnCheckinfo)
	ON_BN_CLICKED(IDC_BTN_TABTOMARK, &CDlgMain::OnBnClickedBtnTabtomark)
	ON_BN_CLICKED(IDC_BTN_AUTOWH, &CDlgMain::OnBnClickedBtnAutowh)
	ON_BN_CLICKED(IDC_BTN_CHECKWH, &CDlgMain::OnBnClickedBtnCheckwh)
	ON_BN_CLICKED(IDC_RADIO_YCL, &CDlgMain::OnBnClickedRadioYcl)
	ON_BN_CLICKED(IDC_RADIO_ZH, &CDlgMain::OnBnClickedRadioZh)
	ON_BN_CLICKED(IDC_RADIO_WCL, &CDlgMain::OnBnClickedRadioWcl)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CDlgMain::OnTcnSelchangeTab)
	ON_BN_CLICKED(IDC_BTN_MXB, &CDlgMain::OnBnClickedBtnMxb)
	ON_BN_CLICKED(IDC_BTN_SETVIEW, &CDlgMain::OnBnClickedBtnSetview)
	ON_BN_CLICKED(IDC_BTN_CHECKDWG, &CDlgMain::OnBnClickedBtnCheckdwg)
	ON_BN_CLICKED(IDC_BTN_RESTOREDWG, &CDlgMain::OnBnClickedBtnRestoredwg)
	ON_CBN_SELCHANGE(IDC_CMB_VIEW, &CDlgMain::OnCbnSelchangeCmbView)
	ON_EN_CHANGE(IDC_EDIT_SEARCH, &CDlgMain::OnEnChangeEditSearch)
	ON_BN_CLICKED(IDC_BTN_ZJYS, &CDlgMain::OnBnClickedBtnZjys)
	ON_BN_CLICKED(IDC_BTN_HIGHTLIGHT, &CDlgMain::OnBnClickedBtnHightlight)
	ON_BN_CLICKED(IDC_BTN_UNHIGHTLIGHT, &CDlgMain::OnBnClickedBtnUnhightlight)
	ON_BN_CLICKED(IDC_BTN_MAPCHECK, &CDlgMain::OnBnClickedBtnMapcheck)
END_MESSAGE_MAP()


// CDlgMain 消息处理程序


BOOL CDlgMain::OnInitDialog()
{
	CAcUiTabMainDialog::OnInitDialog();
	CIniFile ini(GetIniPath());
	ini.GetValueOfKey(_T("DL"), _T("DQTXB"), m_sDqtx);
	ini.GetValueOfKey(_T("DL"), _T("JXB"), m_sJxb);

	GetDlgItem(IDC_STATIC_MAIN)->SetWindowText(_T("此处提示选择的块块名。"));
	GetDlgItem(IDC_STATIC_NUM)->SetWindowText(_T("此处提示选择的块的数量。"));
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(_T("此处提示选择的块匹配的名称。"));
	SetAcadTabPointer(&m_tab);
	m_tab.AddTab(0, _T("位号识别"), CDlgWeihao::IDD, &m_dlgWeihao);
	m_tab.AddTab(1, _T("连接关系识别"), CDlgDiscern::IDD, &m_dlgDiscern);
	m_tab.SetActiveTab(0);

	CString sViewTemp;
	ini.GetValueOfKey(_T("DL"), _T("VIEW"), sViewTemp);
	FillCombo(m_cmb_View, sViewTemp, _T(","));

	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CDlgMain::OnBnClickedBtnSelectBlock()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bSelect)
	{
		acutPrintf(_T("\n正在进行选择操作,请选择图块或者esc退出选择。"));
		return;
	}
	GetDlgItem(IDC_STATIC_MAIN)->SetWindowText(_T("此处提示选择的块块名。"));
	GetDlgItem(IDC_STATIC_NUM)->SetWindowText(_T("此处提示选择的块的数量。"));
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(_T("此处提示选择的块匹配的名称。"));
	FindInfo();
	GetParent()->SetFocus();
	std::vector <AcRxClass*> vecType;
	vecType.push_back(AcDbBlockReference::desc());
	AcDbEntity* pEnt = NULL;
	AcGePoint3d ptPick;
	acDocManager->lockDocument(curDoc());
	m_bSelect = TRUE;
	bool b = CSelectUtil::PromptSelectEntity(_T("\n选择需要标记的块:"), vecType, pEnt, ptPick);
	m_bSelect = FALSE;
	if (!b)
	{
		acDocManager->unlockDocument(curDoc());
		return;
	}
	AcDbBlockReference *pRef = static_cast<AcDbBlockReference*>(pEnt);
	AcDbObjectId pID = pRef->blockTableRecord();
	AcDbBlockTableRecord *pRec = NULL;
	acdbOpenObject(pRec, pID, AcDb::kForWrite);
	ACHAR* sName;
	pRec->getName(sName);
	m_sBlockName.Format(_T("%s"), sName);
	AcGePoint3d pt = pRef->position();
	CString sPro;
	sPro.Format(_T("块名为: %s."), sName);
	GetDlgItem(IDC_STATIC_MAIN)->SetWindowText(sPro);
	pRef->close();
	pRec->close();
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	this->SetFocus();
	UpdateData(FALSE);

	OnBnClickedBtnCreatmark();
	return;
}

void CDlgMain::OnBnClickedBtnDqtx()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
// 	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0,
// 		_T("格式1(*.xls) |*.xls|格式2(*.xlsx) |*.xlsx||"), acedGetAcadFrame());
	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0,
		_T("excel格式(*.xls;*.xlsx) |*.xls;*.xlsx|"), acedGetAcadFrame());
	if (importDlg.DoModal() == IDOK)
	{
		m_sDqtx = importDlg.GetPathName();
		m_vecInfo.clear();
		CIniFile ini(GetIniPath());
		ini.SetValueOfKey(_T("DL"), _T("DQTXB"), m_sDqtx);
	}
	else
	{
		return;
	}
	UpdateData(FALSE);
	return;
}

void CDlgMain::OnBnClickedBtnJxb()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
// 	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0,
// 		_T("格式1(*.xls) |*.xls|格式2(*.xlsx) |*.xlsx||"), acedGetAcadFrame());
	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0,
		_T("excel格式(*.xls;*.xlsx) |*.xls;*.xlsx|"), acedGetAcadFrame());
	if (importDlg.DoModal() == IDOK)
	{
		m_sJxb = importDlg.GetPathName();
		CIniFile ini(GetIniPath());
		ini.SetValueOfKey(_T("DL"), _T("JXB"), m_sJxb);
	}
	else
	{
		return;
	}
	UpdateData(FALSE);
	return;
}

BOOL CDlgMain::FindInfo()
{
	BOOL b = TRUE;
	if (m_vecInfo.size()!=0)
	{
		return TRUE;
	}
	cExcel excel;
	if (!excel.StartApp())
	{
		acutPrintf(_T("\n打开excel失败."));
		return FALSE;
	}
	excel.OpenWorkBook(m_sDqtx);
	long iNum = excel.GetSheetNum();
	acedSetStatusBarProgressMeter(TEXT("检索excel信息...:"), 0,iNum);
	for (int i = 1; i <= iNum; i++)
	{
		acedSetStatusBarProgressMeterPos(i);
		excel.SwitchToSheet(i);
		CString sSheetName = excel.GetSheet().GetName();
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

		for (int j = iStartRow; j < iRowNum + iStartRow; j++)
		{
			CString s1, s2, s3, s4, s5;
			s1 = excel.GetCString(1, j);
			if (s1==_T("名称")&&j>=5)
			{
				s2 = excel.GetCString(1, j - 1);
				s3 = excel.GetCString(1, j - 2);
				s4 = excel.GetCString(1, j - 3);
				s5 = excel.GetCString(1, j - 4);
			}
			else
			{
				continue;
			}
			if (s2==_T("模块用物资代码")&&s3==_T("母板用物资代码")&&s4==_T("模块连接器名称")&&s5==_T("母板连接器名称"))
			{
				CString  sNAME,sMKWZDM,sMBWZDM,sMKLJQNAME,sMBLJQNAME, sConverWzdm;
				sNAME = excel.GetCString(2, j);
				sMKWZDM = excel.GetCString(2, j - 1);
				sMBWZDM = excel.GetCString(2, j - 2);
				sMKLJQNAME = excel.GetCString(2, j - 3);
				sMBLJQNAME = excel.GetCString(2, j - 4);

				if(sMKWZDM==_T("")&&sMBWZDM==_T("")&&sMKLJQNAME==_T("")&&sMBLJQNAME==_T(""))
				{
					continue;
				}

				CString weihao, wuzidaima;
				GetWeihaoAndWzdm(sNAME, sMKWZDM, sMBWZDM, sMKLJQNAME, sMBLJQNAME, sSheetName, weihao, wuzidaima);

				sConverWzdm = wuzidaima;
				if (m_mapZjys.size() != 0)
				{
					map<CString, CString>::iterator atTemp = m_mapZjys.find(wuzidaima);
					if (atTemp != m_mapZjys.end())
					{
						sConverWzdm = atTemp->second;
					}
				}
				if (sNAME != _T("") /*&& sWZDM != _T("") && sLJQNAME != _T("")*/)
				{
					InfoAddress temp;
					temp.SheetNum = i;
					temp.RowNum = j;
					temp.ColNum = 1;
					temp.WZDM = wuzidaima;
					temp.COVERWZDM = sConverWzdm;
					temp.LJQNAME = sMKLJQNAME;
					temp.NAME = ConvertString(weihao);//2018.5.8 
					temp.COVERNAME = ConvertString(weihao);//2018.8.6
					m_vecInfo.push_back(temp);
					//存储连线关系中要用到的位号信息
					m_dlgDiscern.m_vecWeihao.push_back(ConvertString(weihao));
				}
				else
				{
					b = FALSE;
				}
			}
			
		}
	}
	acedRestoreStatusBar();
	excel.Quit();
	return b;
}

void CDlgMain::CreatMark(CString sText,int iHeight)
{
	acDocManager->lockDocument(curDoc());
	AcGePoint3dArray ptArr;
	AcDbObjectIdArray idArr2;
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
	int iNumEnt = idArr.length();
	for (int i = 0; i < iNumEnt;i++)
	{
		AcDbObjectId idTemp = idArr[i];
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es;
		es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
		if (es!=eOk)
		{
			continue;
		}
		if (!pEnt->isKindOf(AcDbBlockReference::desc()))
		{
			pEnt->close();
			continue;
		}
		AcDbBlockReference *pRef = static_cast<AcDbBlockReference*>(pEnt);		
		AcDbObjectId RecId=pRef->blockTableRecord();
		AcDbBlockTableRecord *pRec=NULL;
		es=acdbOpenObject(pRec, RecId, AcDb::kForWrite);
		if (es!=eOk)
		{
			pRef->close();
			continue;
		}
		ACHAR* nameTemp; CString sNameTemp;
		pRec->getName(nameTemp);
		sNameTemp.Format(_T("%s"), nameTemp);
		if (sNameTemp==m_sBlockName)
		{
			AcGePoint3d ptTemp = pRef->position();
			ptArr.append(ptTemp);
			idArr2.append(idTemp);
		}
		pRec->close();
		pRef->close();
	}

	int iNum = ptArr.length();
	CString sNumTemp;
	sNumTemp.Format(_T("共找到: %d个相同图块.如果有多个请选择生成位置..."),iNum);
	GetDlgItem(IDC_STATIC_NUM)->SetWindowText(sNumTemp);
	if (iNum==1)
	{
		AcGePoint3d ptTemp = ptArr[0];
		AcGePoint3d ptTemp2 = AcGePoint3d(ptTemp.x + 3, ptTemp.y + 3, 0);
		AcDbText *pText = new AcDbText(ptTemp2, sText, AcDbObjectId::kNull, iHeight);
		CDwgDatabaseUtil::SetXdata(_T("标记"), sText, pText);
		CDwgDatabaseUtil::PostToModelSpace(pText);
	}
	if (iNum>1)
	{
		HighLight(idArr2);
		AcGePoint3d ptTemp;
		m_bSelect = TRUE;
		bool b=CGetInputUtil::GetPoint(_T("\n找到多个同名块，已高亮显示。请选择标记插入点:"),ptTemp);
		m_bSelect = FALSE;
		if (b)
		{
			AcDbText *pText = new AcDbText(ptTemp, sText, AcDbObjectId::kNull, iHeight);
			CDwgDatabaseUtil::SetXdata(_T("标记"), sText, pText);
			CDwgDatabaseUtil::PostToModelSpace(pText);
		}
		UnHighLight(idArr2);
	}
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	return;
}

void CDlgMain::CreatDzXh(std::vector<DzAndXh> vec, AcGePoint3d ptInsert,CString sName)
{
	acDocManager->lockDocument(curDoc());
	AcDbObjectId idBlock=CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), _T("标题"));
	AcDbObjectId idBlockDzXh = CBlockUtil::CopyBlockDefFromOtherDwg(GetDwgPath(), _T("端子线号"));
	AcDbObjectId idTemp = CBlockUtil::InsertBlockRefWithAttribute(idBlock, ptInsert);
	AcDbBlockReference *pRef = NULL;
	Acad::ErrorStatus es;
	es = acdbOpenObject(pRef, idTemp, AcDb::kForWrite);
	if (es!=eOk)
	{
		acDocManager->unlockDocument(curDoc());
		return;
	}
	CBlockUtil::SetBlockRefAttribute(pRef, _T("名称"), sName, 1, AcDb::kLnWtByBlock, 3);
	CDwgDatabaseUtil::SetXdata(_T("端子表"), sName, pRef);
	pRef->close();
	size_t num = vec.size();
	acedSetStatusBarProgressMeter(TEXT("生成端子信息...:"), 0, num);
	for (int i = 0; i < num;i++)
	{
		acedSetStatusBarProgressMeterPos(i + 1);
		ptInsert = AcGePoint3d(ptInsert.x, ptInsert.y-7, ptInsert.z);
		AcDbObjectId idDzXh=CBlockUtil::InsertBlockRefWithAttribute(idBlockDzXh, ptInsert);
		AcDbBlockReference *pRefDzXh = NULL;
		es = acdbOpenObject(pRefDzXh, idDzXh, AcDb::kForWrite);
		if (es!=eOk)
		{
			continue;
		}
		DzAndXh temp = vec[i];
		CBlockUtil::SetBlockRefAttribute(pRefDzXh, _T("端子"), temp.DZ, 7, AcDb::kLnWtByBlock, 3);
		CBlockUtil::SetBlockRefAttribute(pRefDzXh, _T("线号"), temp.XH, 7, AcDb::kLnWtByBlock, 3);
		pRefDzXh->close();
	}
	acedRestoreStatusBar();
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	return;
}

void CDlgMain::CreatMarkToText(int iHeight)
{
	m_vecPointAndId.clear();

	CString sPrompt=_T("已生成:");
	acDocManager->lockDocument(curDoc());
	for (int i = 0; i < m_vecNameAndPosition.size();i++)
	{
		NameAndPosition NPtemp = m_vecNameAndPosition[i];
		CString sName = NPtemp.NAME;
		for (int nCount = 0; nCount < m_vecExistWh.size();nCount++)
		{
			CString sExistTemp = m_vecExistWh[nCount];
			if (Compare2String(sName,sExistTemp))
			{
				continue;;
			}
		}
// 		std::vector<CString>::iterator it = std::find(m_vecExistWh.begin(), m_vecExistWh.end(), sName);
// 		if (it != m_vecExistWh.end())
// 		{
// 			continue;
// 		}
		AcGePoint3dArray ptArr = NPtemp.PTARR;
		int k = ptArr.length();
		for (int j = 0; j < m_vecInfo.size();j++)
		{
			InfoAddress IAtemp = m_vecInfo[j];
			if (/*sName==IAtemp.WZDM*/Compare2String(sName,IAtemp.COVERWZDM))
			{
				CString sMarkText = /*IAtemp.NAME*/IAtemp.NAME;//2018.8.6

				if (k>1)
				{
					CreatWhLog logTemp;
// 					for (int o = 0; o < k;o++)
// 					{
// 						PointAndID temp;
// 						AcGePoint3d ptInsert = ptArr[o];
// 						ptInsert = AcGePoint3d(ptInsert.x, ptInsert.y + iHeight, 0);
// 						temp.POINT = ptInsert;
// 						AcDbText *pText = new AcDbText(ptInsert, sMarkText, AcDbObjectId::kNull, iHeight);
// 						pText->setHorizontalMode(AcDb::kTextCenter);
// 						pText->setVerticalMode(AcDb::kTextVertMid);
// 						pText->setAlignmentPoint(ptInsert);
// 						CDwgDatabaseUtil::SetXdata(_T("标记"), sMarkText, pText);
// 						CDwgDatabaseUtil::SetXdata(_T("物资代码"), sName, pText);
// 						CDwgDatabaseUtil::SetXdata(_T("视图"), m_sCurrentView, pText);
// 						temp.NAME = sMarkText;
// 						temp.ID=CDwgDatabaseUtil::PostToModelSpace(pText);
// 						m_vecPointAndId.push_back(temp);
// 					}
// 					sPrompt = sPrompt + sMarkText + _T(";");
// 					logTemp.wtms = sMarkText + _T(":已生成位号");
					logTemp.wtms = sMarkText + _T(":位号一对多");
					m_vecWhLog.push_back(logTemp);
				}
				if (k==1)
				{
					CreatWhLog logTemp;
					PointAndID temp;
					AcGePoint3d ptInsert = ptArr[0];
					ptInsert = AcGePoint3d(ptInsert.x , ptInsert.y + iHeight, 0);
					temp.POINT = ptInsert;
					AcDbText *pText = new AcDbText(ptInsert, sMarkText, AcDbObjectId::kNull, iHeight);
					pText->setHorizontalMode(AcDb::kTextCenter);
					pText->setVerticalMode(AcDb::kTextVertMid);
					pText->setAlignmentPoint(ptInsert);
					CDwgDatabaseUtil::SetXdata(_T("标记"), sMarkText, pText);
					CDwgDatabaseUtil::SetXdata(_T("物资代码"), sName, pText);
					CDwgDatabaseUtil::SetXdata(_T("视图"), m_sCurrentView, pText);
					temp.NAME = sMarkText;
					temp.ID=CDwgDatabaseUtil::PostToModelSpace(pText);
					m_vecPointAndId.push_back(temp);
					sPrompt = sPrompt + sMarkText + _T(";");
					logTemp.wtms = sMarkText + _T(":已生成位号");
					m_vecWhLog.push_back(logTemp);
				}
			}
		}
	}
//	AfxMessageBox(sPrompt, MB_OK);

	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	return;
}

void CDlgMain::GetAllDwgTextAndPosition()
{
	m_vecNameAndPosition.clear();//清空容器
	acDocManager->lockDocument(curDoc());
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
	for (int i = 0; i < idArr.length();i++)
	{
		AcDbObjectId idTemp = idArr[i];
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es;
		es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForRead);
		if (es!=Acad::eOk)
		{
			continue;
		}
		if (!pEnt->isKindOf(AcDbBlockReference::desc()))
		{
			pEnt->close();
			continue;
		}
		CString sViewTemp;
		CDwgDatabaseUtil::getXdata(_T("视图"), sViewTemp, pEnt);
		if (sViewTemp!=m_sCurrentView)
		{
			pEnt->close();
			continue;
		}
		AcDbBlockReference *pRef = static_cast<AcDbBlockReference*>(pEnt);
		AcDbObjectId pID = pRef->blockTableRecord();
		AcDbBlockTableRecord *pRec = NULL;
		acdbOpenObject(pRec, pID, AcDb::kForRead);
		ACHAR* sName;
		CString sBlockName;
		pRec->getName(sName);
		sBlockName.Format(_T("%s"), sName);
		AcGePoint3d pt;
		double dx, dy;
		pt = GetBlockRefCenterTop(pRef, dx, dy);
		AcGePoint3dArray ptArr;
		ptArr.append(pt);
		
		NameAndPosition NPtemp;
		NPtemp.NAME = sBlockName;
		NPtemp.PTARR = ptArr;

		bool bAdd = true;
		for (int i = 0; i < m_vecNameAndPosition.size();i++)
		{
			if (m_vecNameAndPosition[i] == NPtemp)
			{
				m_vecNameAndPosition[i] + NPtemp;
				bAdd = false;
				break;
			}
		}
		if (bAdd)
		{
			m_vecNameAndPosition.push_back(NPtemp);
		}	
		pRec->close();
		pRef->close();
	}
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
}

void CDlgMain::CheckDwgWh()
{
	m_vecExistWh.clear();
	acDocManager->lockDocument(curDoc());
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
	for (int i = 0; i < idArr.length();i++)
	{
		AcDbObjectId idTemp = idArr[i];
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es;
		es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
		if (es!=eOk)
		{
			continue;
		}
		CString sWzdm,sViewTemp;
		CDwgDatabaseUtil::getXdata(_T("物资代码"), sWzdm, pEnt);
		CDwgDatabaseUtil::getXdata(_T("视图"), sViewTemp, pEnt);
		pEnt->close();
		if (sWzdm!=_T("")&&sViewTemp==m_sCurrentView)
		{
			m_vecExistWh.push_back(sWzdm);
		}
	}
	acDocManager->unlockDocument(curDoc());
}

bool CDlgMain::CheckWhPostion()
{
	if (m_vecPointAndId.size()==0)
	{
		AfxMessageBox(_T("此视图下未生成任何标记,请检查是否设置视图,或者位号全部为一对多."));
		return false;
	}
	acDocManager->lockDocument(curDoc());
	CString sPrompt=_T("以下图形在视图中有重叠或存在多个:");
	CString sPrompt2;
	for (int i = 0; i < m_vecPointAndId.size() - 1; i++)
	{
		bool bCd = true;
		bool bDelete = false;
		PointAndID ptTemp = m_vecPointAndId[i];
		for (int j = i + 1; j < m_vecPointAndId.size(); j++)
		{
			PointAndID ptTemp2 = m_vecPointAndId[j];
			double dis = ptTemp.POINT.distanceTo(ptTemp2.POINT);
// 			if (ptTemp.NAME==ptTemp2.NAME)
// 			{
// 				bool bTemp2 = DeleteWire(ptTemp2.ID);
// 				if (bTemp2)
// 				{
// 					sPrompt2 = ptTemp.NAME+_T("存在一对多关系");
// 					bCd = false;
// 					bDelete = true;
// 				}
// 			}
			if (dis<10)
			{
				CString sName1, sName2;
				sName1 = ptTemp.NAME;
				sName2 = ptTemp2.NAME;
				bool bTemp2=DeleteWire(ptTemp2.ID);			
				if (/*bTemp2*/1)
				{
					sPrompt = sPrompt + (bCd ? sName1 : _T("")) + _T("---") + sName2;
					sPrompt2 = (bCd ? sName1 : _T("")) + _T("---") + sName2;
					/*bCd = false;*/
					bDelete = true;

					//如果存在重叠 则删除
					CreatWhLog sT1, sT2;
					sT1.wtms = sName1+_T(":已生成位号");
					sT2.wtms = sName2+_T(":已生成位号");
					vector<CreatWhLog>::iterator itr1 = find(m_vecWhLog.begin(), m_vecWhLog.end(), sT1);
					if (itr1!=m_vecWhLog.end())
					{
						m_vecWhLog.erase(itr1);
					}
					vector<CreatWhLog>::iterator itr2 = find(m_vecWhLog.begin(), m_vecWhLog.end(), sT2);
					if (itr2!=m_vecWhLog.end())
					{
						m_vecWhLog.erase(itr2);
					}	
				}						
			}
		}
		if (bDelete)
		{
			bool bTemp = DeleteWire(ptTemp.ID);

			CreatWhLog whlog;
			whlog.wtms = sPrompt2 + _T("存在重叠;");
			m_vecWhLog.push_back(whlog);

			sPrompt = sPrompt + _T(" ; ");
		}
	}
	acDocManager->unlockDocument(curDoc());
	if (sPrompt!=_T("以下图形在视图中有重叠或存在多个:"))
	{
		//AfxMessageBox(sPrompt);
	}
	return true;
}

void CDlgMain::CheckDwgDzb()
{
	m_vecExistDzb.clear();
	acDocManager->lockDocument(curDoc());
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
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
		CString sDzb;
		CDwgDatabaseUtil::getXdata(_T("端子表"), sDzb, pEnt);
		pEnt->close();
		if (sDzb != _T(""))
		{
			m_vecExistDzb.push_back(sDzb);
		}
	}
	acDocManager->unlockDocument(curDoc());
}

bool CDlgMain::ExportDzb(CString &sExcelPath)
{
	if (m_vecDzb.size() == 0)
	{
		return false;
	}
	CString sPath = GetExcelDzbPath();
	cExcel excel;
	if (!excel.StartApp())
	{
		AfxMessageBox(_T("日志文件打开失败"));
		return false;
	}
	excel.OpenWorkBook(sPath);
	int iMark1=0, iMark2=0;
	for (int i = 0; i < m_vecDzb.size(); i++)
	{
		CString sTemp = m_vecDzb[i];
		if (sTemp.Find(_T("."))==-1)
		{
			excel.PutValue(1, iMark1 + 2, sTemp);
			iMark1++;
		}
		else
		{
			excel.PutValue(2, iMark2 + 2, sTemp);
			iMark2++;
		}	
	}
	sExcelPath = GetLogFolderPath() + GetTimer();
	excel.SaveAs(sExcelPath);
	excel.Quit();
	return true;

}

int CDlgMain::CreatJxb(CString sCreatName, AcGePoint3d ptInsert)
{
	int iRetLen = 0;
	std::vector<DzAndXh> vecDzXh;//存储端子线号
	cExcel excel;
	if (!excel.StartApp())
	{
		acutPrintf(_T("\n打开excel失败."));
		return iRetLen;
	}
	excel.OpenWorkBook(m_sJxb);

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

	CString sPrompt;
	sPrompt.Format(_T("获取%s接线端子表信息...:"), sCreatName);
	acedSetStatusBarProgressMeter(sPrompt, 0, iRowNum);
	for (int j = iStartRow; j < iRowNum + iStartRow; j++)
	{
		acedSetStatusBarProgressMeterPos(j-iStartRow + 1);
		CString sTemp = excel.GetCString(4, j);
		CString sTemp2 = excel.GetCString(6, j);
		std::vector<CString> vecTemp;
		std::vector<CString> vecTemp2;
		CStringUtil::Split(sTemp, _T(":"), vecTemp, false);
		CStringUtil::Split(sTemp2, _T(":"), vecTemp2, false);
		size_t t = vecTemp.size();
		size_t t2 = vecTemp2.size();
		if (t != 2||t2!=2)
		{
			continue;
		}
		if (t==2)
		{
			CString sName = vecTemp[0];
			CString sDz = vecTemp[1];
			if (sName == sCreatName)
			{
				DzAndXh temp;
				temp.DZ = sDz;
				CString sXh = excel.GetCString(2, j);
				temp.XH = sXh;
				vecDzXh.push_back(temp);
			}
		}
		if (t2==2)
		{
			CString sName = vecTemp2[0];
			CString sDz = vecTemp2[1];
			if (sName == sCreatName)
			{
				DzAndXh temp;
				temp.DZ = sDz;
				CString sXh = excel.GetCString(2, j);
				temp.XH = sXh;
				vecDzXh.push_back(temp);
			}
		}
	}
	acedRestoreStatusBar();
	if (vecDzXh.size() == 0)
	{
		sPrompt.Format(_T("\n%s :未找到匹配的端子信息."), sCreatName);
		acutPrintf(sPrompt);
		m_vecDzb.push_back(sCreatName+_T("."));
	}
	else
	{
		sPrompt.Format(_T("\n%s :已生成端子信息"), sCreatName);
		acutPrintf(sPrompt);
		m_vecDzb.push_back(sCreatName);
		iRetLen = vecDzXh.size();

		CreatDzXh(vecDzXh, ptInsert,sCreatName);
	}
	excel.Quit();
	return iRetLen;
}

//void CDlgMain::OnBnClickedBtnFindinfo()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//	FindInfo();
//	return;
//}

void CDlgMain::OnBnClickedBtnCreatmark()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bSelect)
	{
		acutPrintf(_T("\n正在进行选择操作,请选择图块或者esc退出选择。"));
		return;
	}
	CString sText;
	if (m_vecInfo.size()==0)
	{
		AfxMessageBox(_T("请先查找数据，或查找到的数据为空无意义"));
		return;
	}
	int iNum = m_vecInfo.size();
	for (int i = 0; i < iNum;i++)
	{
		InfoAddress infotemp=m_vecInfo[i];
		if (m_sBlockName==infotemp.WZDM)
		{
			sText = infotemp.NAME;
			break;
		}
	}
	CString sTemp;
	if (sText!=_T(""))
	{
		sTemp.Format(_T("根据块名匹配的名称为：%s"), sText);
		GetDlgItem(IDC_STATIC_NAME)->SetWindowText(sTemp);
		CreatMark(sText, 3);
	}
	else
	{
		sTemp.Format(_T("通过块名: %s,未找到excel中对应名称标记."), m_sBlockName);
		GetDlgItem(IDC_STATIC_NAME)->SetWindowText(sTemp);
	}	
	return;
}

void CDlgMain::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类
	delete this;
	if (pDlg!=NULL)
	{
		pDlg = NULL;
	}
	CAcUiTabMainDialog::PostNcDestroy();
}

void CDlgMain::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CAcUiTabMainDialog::OnClose();
	DestroyWindow();
}

afx_msg LRESULT CDlgMain::OnACADKeepFocus(WPARAM, LPARAM)
{
	return keepTheFocus() ? TRUE : FALSE;
	//	return TRUE;
}

BOOL CDlgMain::keepTheFocus()
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

void CDlgMain::OnBnClickedBtnCretejxb()
{
	// TODO:  在此添加控件通知处理程序代码
// 	UpdateData(TRUE);
// 	if (m_bSelect)
// 	{
// 		acutPrintf(_T("\n正在进行选择操作,请选择图块或者esc退出选择。"));
// 		return;
// 	}
// 	acDocManager->lockDocument(curDoc());
// 
// 	std::vector<AcRxClass*> vecType;
// 	vecType.push_back(AcDbText::desc());
// 	AcDbEntity *pEnt = NULL;
// 	AcGePoint3d pickPoint;
// 	bool bSelect=CSelectUtil::PromptSelectEntity(_T("\n选择位号生成接表："), vecType, pEnt, pickPoint);
// 	if (!bSelect)
// 	{
// 		acDocManager->unlockDocument(curDoc());
// 		return;
// 	}
// 	CDwgDatabaseUtil::getXdata(_T("标记"), m_sName, pEnt);
// 	pEnt->close();
// 
// 	if (m_sName==_T(""))
// 	{
// 		acDocManager->unlockDocument(curDoc());
// 		AfxMessageBox(_T("未找到对应名称无法生成接线表."), MB_OK);
// 		return;
// 	}
// 	std::vector<DzAndXh> vecDzXh;//存储端子线号
// 	cExcel excel;
// 	if (!excel.StartApp())
// 	{
// 		acDocManager->unlockDocument(curDoc());
// 		acutPrintf(_T("\n打开excel失败."));
// 		return;
// 	}
// 	excel.OpenWorkBook(m_sJxb,_T("接线表"));
// 
// 	_ExRange range;
// 	_ExRange usedRange;
// 	int iStartRow, iStartCol, iRowNum, iColNum;
// 	usedRange.AttachDispatch(excel.GetSheet().GetUsedRange());
// 	iStartRow = usedRange.GetRow();
// 	iStartCol = usedRange.GetColumn();
// 	range.AttachDispatch(usedRange.GetRows());
// 	iRowNum = range.GetCount();
// 	range.AttachDispatch(usedRange.GetColumns());
// 	iColNum = range.GetCount();
// 	for (int j = iStartRow; j < iRowNum + iStartRow; j++)
// 	{
// 		CString sTemp = excel.GetCString(3, j);
// 		std::vector<CString> vecTemp;
// 		CStringUtil::Split(sTemp, _T(":"), vecTemp, false);
// 		size_t t=vecTemp.size();
// 		if (t!=2)
// 		{
// 			continue;
// 		}
// 		CString sName = vecTemp[0];
// 		CString sDz = vecTemp[1];
// 		if (sName==m_sName)
// 		{
// 			DzAndXh temp;
// 			temp.DZ = sDz;
// 			CString sXh = excel.GetCString(2, j);
// 			temp.XH = sXh;
// 			vecDzXh.push_back(temp);
// 		}
//     }
// 	if (vecDzXh.size()==0)
// 	{
// 		acDocManager->unlockDocument(curDoc());
// 		acutPrintf(_T("\n未找到匹配的端子信息."));
// 	}
// 	else
// 	{
// 		AcGePoint3d ptInsert;
// 		m_bSelect = TRUE;
// 		bool b = CGetInputUtil::GetPoint(_T("\n选择端子信息插入点"), ptInsert);
// 		m_bSelect = FALSE;
// 		acDocManager->unlockDocument(curDoc());
// 		if (b)
// 		{
// 			CreatDzXh(vecDzXh, ptInsert);
// 		}
// 	}
// 	excel.Quit();

	UpdateData(TRUE);
	if (m_vecInfo.size()==0)
	{
		AfxMessageBox(_T("请进行位号识别提取信息后在进行生成接线端子表。"));
		return;
	}
	CheckDwgDzb();
	m_vecDzb.clear();//初始化导出信息列表
	std::vector<CString> vecStr;
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
	int iLen = idArr.length();
	acDocManager->lockDocument(curDoc());
	for (int i=0;i<iLen;i++)
	{
		AcDbObjectId idTemp = idArr[i];
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es;
		es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
		if (es!=eOk)
		{
			continue;
		}
		CString sTag;
		CDwgDatabaseUtil::getXdata(_T("标记"), sTag, pEnt);
		pEnt->close();
		if (sTag!=_T(""))
		{
			vecStr.push_back(sTag);
		}	
	}
	//去除重复
	sort(vecStr.begin(), vecStr.end());
	vecStr.erase(unique(vecStr.begin(), vecStr.end()), vecStr.end());

	AcGePoint3d ptStr;
	double dYsave=0;
	bool b=CGetInputUtil::GetPoint(_T("\n选择接线表起始位置:"),ptStr);
	double dYLenAll = 350, dLenTemp = 0;
	acDocManager->unlockDocument(curDoc());
	if (b)
	{
		dYsave = ptStr.y;
		int iLen = vecStr.size();
		for (int i = 0; i < iLen; i++)
		{
		    std::vector<CString>::iterator itr=	std::find(m_vecExistDzb.begin(), m_vecExistDzb.end(), vecStr[i]);
			if (itr!=m_vecExistDzb.end())
			{
				continue;
			}
	        int iNum=CreatJxb(vecStr[i], ptStr);
			if (iNum!=0)
			{
				dLenTemp = dLenTemp + 20 + iNum * 7;
				if (dLenTemp > 250)
				{
					ptStr = AcGePoint3d(ptStr.x + 45, dYsave, 0);
					dLenTemp = 0;
				}
				else
				{
					ptStr = AcGePoint3d(ptStr.x, ptStr.y -20-iNum*7, 0);
				}
			}
			
		}
		CString sExcelPath;
		bool b = ExportDzb(sExcelPath);
		sExcelPath += _T(".xlsx");
		AfxMessageBox(_T("接线端子表生成完成"));	
		if (b)
		{
			ShellExecute(
				0,
				_T("open"),
				sExcelPath,
				NULL,
				NULL,
				SW_SHOWNORMAL);
		}		
	}		
}

void CDlgMain::OnBnClickedBtnReflist()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!CheckExcelPath(m_sJxb))
	{
		AfxMessageBox(_T("excel文件打开存在问题,请检查！"));
		return;
	}
	if (m_dlgDiscern.m_vecWeihao.size()==0)
	{
		AfxMessageBox(_T("请先检索位号信息后再进行连接关系识别！"));
		return;
	}
	UpdateData(TRUE);
	if (m_bSelect)
	{
		acutPrintf(_T("\n正在进行选择操作,请选择图块或者esc退出选择。"));
		return;
	}
	m_dlgDiscern.RefreshList(m_sJxb);
	UpdateData(FALSE);
	m_bShowPrompt = FALSE;
	OnBnClickedBtnCheckinfo();
	m_bShowPrompt = TRUE;
	AfxMessageBox(_T("识别完成"));
}

void CDlgMain::OnBnClickedBtnCheckinfo()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bSelect)
	{
		acutPrintf(_T("\n正在进行选择操作,请选择图块或者esc退出选择。"));
		return;
	}
	m_bZh = TRUE;
	m_bYcl = FALSE;
	m_bWcl = FALSE;
	UpdateData(FALSE);
	m_dlgDiscern.m_bShowPrompt = false;
	m_tab.SetCurFocus(1);
	OnBnClickedRadioZh();
	m_dlgDiscern.m_bShowPrompt = true;
	
	GetDlgItemText(IDC_CMB_VIEW, m_sCurrentView);
	m_dlgDiscern.m_sViewTemp=m_sCurrentView;
	m_dlgDiscern.CheckAndRefreshList();
//	m_dlgDiscern.CheckInfo(); 取消对话框提示未处理端子线号
	UpdateData(FALSE);
	if (m_bShowPrompt)
	{
		AfxMessageBox(_T("检测完成"));
	}	
	return;
}

void CDlgMain::OnBnClickedBtnTabtomark()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!CheckExcelPath(m_sDqtx))
	{
		AfxMessageBox(_T("excel文件打开存在问题,请检查！"));
		return;
	}
	BOOL b1 = GetMapTab();
	m_dlgDiscern.m_vecWeihao.clear();
	m_vecInfo.clear();
 	BOOL b  = FindInfo();//查找出excel中物资代码对应的名称
	m_dlgWeihao.m_vecListinfo.clear();
// 	GetAllDwgTextAndPosition();//从图纸中获取所有的名字和对应点
// 	CreatMarkToText(3);//根据位置生成标记
	
	if (m_bSelect)
	{
		acutPrintf(_T("\n正在进行选择操作,请选择图块或者esc退出选择。"));
		return;
	}
	m_dlgWeihao.RefreshList(m_sDqtx,m_mapZjys);
	CString sExcelPath;
	bool bShowExcel = false;
	bShowExcel=m_dlgWeihao.ExportLog(sExcelPath);
	sExcelPath += _T(".xlsx");
	if (bShowExcel)
	{
		//存在错误信息 则直接dele所有项
		if (!b)
		{
			m_vecInfo.clear();
			m_dlgWeihao.m_listWeihao.DeleteAllItems();
			AfxMessageBox(_T("包含不可忽略掉的错误请参考错误日志修改以后再导入"));
		}
	}
	UpdateData(FALSE);
	m_bShowPrompt = FALSE;
	OnBnClickedBtnCheckwh();
	m_bShowPrompt = TRUE;
	AfxMessageBox(_T("识别完成"));

	if (bShowExcel)
	{
		CDlgPrompt dlg(m_dlgWeihao.m_vecLog, m_sDqtx, acedGetAcadFrame());
		int nRow= dlg.DoModal();
		if (nRow==2)
		{
			m_vecInfo.clear();
			m_dlgWeihao.m_listWeihao.DeleteAllItems();
		}
// 		ShellExecute(
// 			0,
// 			_T("open"),
// 			sExcelPath,
// 			NULL,
// 			NULL,
// 			SW_SHOWNORMAL);
// 		if (b)
// 		{
// 			int nRet= AfxMessageBox(_T("查看日志消息判断是否忽略"),MB_YESNO);
// 			if (nRet!=6)
// 			{
// 				m_vecInfo.clear();
// 				m_dlgWeihao.m_listWeihao.DeleteAllItems();
// 			}
// 		}
	}	
}

void CDlgMain::OnBnClickedBtnAutowh()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_vecInfo.size() == 0)
	{
		AfxMessageBox(_T("请进行位号识别提取信息后在进行生成位号。"));
		return;
	}
	m_vecWhLog.clear();
	GetDlgItemText(IDC_CMB_VIEW, m_sCurrentView);
	FindInfo();
	GetAllDwgTextAndPosition();
	CheckDwgWh();
	CreatMarkToText(3);
	CheckWhPostion();
	CString sWhLogExcel;
	if (ExportWhLog(sWhLogExcel))
	{
		ShellExecute(0,
		 	_T("open"),
			sWhLogExcel+_T(".xlsx"),
		 	NULL,
		 	NULL,
		 	SW_SHOWNORMAL);
	}
}

bool CDlgMain::ExportWhLog(CString &sExcelPath)
{
	if (m_vecWhLog.size()==0)
	{
		return false;
	}
	sort(m_vecWhLog.begin(), m_vecWhLog.end());
	CString sPath = GetWhLogPath();
	cExcel excel;
	if (!excel.StartApp())
	{
		AfxMessageBox(_T("日志文件打开失败"));
		return false;
	}
	excel.OpenWorkBook(sPath);
	int iMarkYsc=3, iMarkWsc=3;
	for (int i = 0;i<m_vecWhLog.size();i++)
	{
		CreatWhLog temp = m_vecWhLog[i];
		CString sWt = temp.wtms;
		if (sWt.Find(_T("已生成位号"))!=-1)
		{
			excel.PutValue(2, iMarkYsc, temp.wtms);
			CString sIndex;
			sIndex.Format(_T("%d"), iMarkYsc - 2);
			excel.PutValue(1, iMarkYsc, sIndex);
			iMarkYsc++;
			
		}
		else
		{
			excel.PutValue(3, iMarkWsc, temp.wtms);
			CString sIndex;
			sIndex.Format(_T("%d"), iMarkWsc - 2);
			excel.PutValue(1, iMarkWsc, sIndex);
			iMarkWsc++;
		}
	}
	sExcelPath = GetLogFolderPath() + GetTimer();
	excel.SaveAs(sExcelPath);
	excel.Quit();
	return true;
}

bool CDlgMain::ExportCheckMapLog(CString &sExcelPath)
{
	if (m_vecCheckMap.size() == 0)
	{
		return false;
	}
	CString sPath = GetCheckMapPath();
	cExcel excel;
	if (!excel.StartApp())
	{
		AfxMessageBox(_T("日志文件打开失败"));
		return false;
	}
	excel.OpenWorkBook(sPath);
	for (int i = 0; i < m_vecCheckMap.size(); i++)
	{
		CString temp = m_vecCheckMap[i];
		excel.PutValue(1, i + 2, temp);
	}
	sExcelPath = GetLogFolderPath() + GetTimer();
	excel.SaveAs(sExcelPath);
	excel.Quit();
	return true;
}

void CDlgMain::OnBnClickedBtnCheckwh()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bSelect)
	{
		acutPrintf(_T("\n正在进行选择操作,请选择图块或者esc退出选择。"));
		return;
	}
	m_bZh = TRUE;
	m_bYcl = FALSE;
	m_bWcl = FALSE;
	UpdateData(FALSE);
	m_dlgWeihao.m_bShowPrompt = false;
	m_tab.SetCurFocus(0);
	OnBnClickedRadioZh();
	m_dlgWeihao.m_bShowPrompt = true;
	
	//获取视图信息
	GetDlgItemText(IDC_CMB_VIEW, m_sCurrentView);
	m_dlgWeihao.m_sView = m_sCurrentView;
	m_dlgWeihao.FindWh();
	UpdateData(FALSE);
	if (m_bShowPrompt)
	{
		AfxMessageBox(_T("刷新完成"));
	}	
	return;
}

BOOL CDlgMain::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
	{
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
// 	else if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_SPACE)
// 	{
// 		return TRUE;
// 	}
	else
	{
		return CAcUiTabMainDialog::PreTranslateMessage(pMsg);
	}

}

void CDlgMain::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	return;
}

void CDlgMain::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	return;
}

void CDlgMain::OnBnClickedRadioYcl()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int i=m_tab.GetCurFocus();
	if (i == 0)
	{
		if (m_bYcl)
		{
			m_dlgWeihao.SetView(true);
		}
	}
	if (i==1)
	{
		if (m_bYcl)
		{
			m_dlgDiscern.SetView(true);
		}
	}
	UpdateData(FALSE);
}

void CDlgMain::OnBnClickedRadioZh()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int i = m_tab.GetCurFocus();
	if (i == 0)
	{
		if (m_bZh)
		{
			m_dlgWeihao.RestoreList();
		}
	}
	if (i==1)
	{
		if (m_bZh)
		{
			m_dlgDiscern.RestoreList();
		}
	}
	UpdateData(FALSE);
}

void CDlgMain::OnBnClickedRadioWcl()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int i = m_tab.GetCurFocus();
	if (i == 0)
	{
		if (m_bWcl)
		{
			m_dlgWeihao.SetView(false);
		}
	}
	if (i==1)
	{
		if (m_bWcl)
		{
			m_dlgDiscern.SetView(false);
		}
	}
	UpdateData(FALSE);
}

void CDlgMain::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	if (m_bWcl)
	{
		OnBnClickedRadioWcl();
	}
	else if (m_bYcl)
	{
		OnBnClickedRadioYcl();
	}
	else if (m_bZh)
	{
		OnBnClickedRadioZh();
	}
	else
	{
	}
	*pResult = 0;
}

void CDlgMain::OnBnClickedBtnMxb()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!CheckExcelPath(m_sDqtx))
	{
		AfxMessageBox(_T("excel文件打开存在问题,请检查！"));
		return;
	}
//	FindInfo();
	acDocManager->lockDocument(curDoc());
	FrameInfo fm;
	bool b = GetDwgFrameInfo(fm);
	acDocManager->unlockDocument(curDoc());
	GetMxbInfo();
	CreatMxb(b,fm);
	UpdateData(FALSE);
}

CString CDlgMain::GetMarkNum(CString sName)
{
	acDocManager->lockDocument(curDoc());
	int iNum = 0;
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
	for (int i = 0; i < idArr.length();i++)
	{
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es;
		es = acdbOpenAcDbEntity(pEnt, idArr[i], AcDb::kForWrite);
		if (es!=eOk)
		{
			continue;
		}
		CString sBj;//标记获取
		CDwgDatabaseUtil::getXdata(_T("标记"), sBj, pEnt);
		if (sBj==sName)
		{
			iNum++;
		}
		pEnt->close();
	}
	acDocManager->unlockDocument(curDoc());
	if (iNum==0)
	{
		return _T("");
	}
	CString sNum;
	sNum.Format(_T("%d"), iNum);
	return sNum;
}

void CDlgMain::GetMxbInfo()
{
	UpdateData(TRUE);
	m_vecMxb.clear();
	FindInfo();
	acedSetStatusBarProgressMeter(TEXT("获取明细表信息...:"), 0, m_vecInfo.size());
	int iMark = 1;
	for (int i = 0; i < m_vecInfo.size();i++)
	{
		acedSetStatusBarProgressMeterPos(i + 1);
		InfoAddress temp = m_vecInfo[i]; 
		MxbInfo mxbTemp;
		CString sI;
		sI.Format(_T("%d"),iMark);
		mxbTemp.XH=sI;
		mxbTemp.WH = temp.NAME;//名称
		mxbTemp.DH = temp.WZDM;//物资代码
	    if(temp.NAME!=_T(""))
		{
			m_vecMxb.push_back(mxbTemp);
			iMark++;
		}	
	}
	acedRestoreStatusBar();
	UpdateData(FALSE);
}

bool CDlgMain::CreatMxb(bool bAddFrameInfo,FrameInfo fm)
{
	UpdateData(TRUE);
	if (m_vecMxb.size()==0)
	{
		AfxMessageBox(_T("图纸中未提取到任何分机明细表信息!"));
		return false;
	}
	CString sPath = GetExcelFjmxbPath();
	cExcel excel;
	if (!excel.StartApp())
	{
		AfxMessageBox(_T("明细表模版打开失败"));
		return false;
	}
	excel.OpenWorkBook(sPath);
	int iMark = 1;
	int iMove = 0;
	if (bAddFrameInfo)
	{
		excel.PutValue(2, 1, fm.CPBH+_T("MX"));
		excel.PutValue(7, 45, fm.CPBH+_T("MX"));
		excel.PutValue(6, 45, fm.CPMC);
		excel.PutValue(7, 49, fm.XMDJ);
		excel.PutValue(8, 49, fm.XMJD);
	}
	for (int i = 0; i < m_vecMxb.size(); i++)
	{
		if (iMark > 0 && iMark <= 40)
		{
			iMove = 4;
		}
		if (iMark > 40)
		{
			iMove = 11;
		}
		MxbInfo temp = m_vecMxb[i];
		//2018.8.2 明细表修改 第四行开始
// 		if (iMark>46)
// 		{
// 			excel.SetRangeType(2, i + iMove);
// 			excel.SetRangeType(3, i + iMove);
// 			excel.SetRangeType(4, i + iMove);
// 			excel.SetRangeType(5, i + iMove);
// 			excel.SetRangeType(6, i + iMove);
// 			excel.SetRangeType(7, i + iMove);
// 			excel.SetRangeType(8, i + iMove);
// 			excel.SetRangeType(9, i + iMove);
// 			excel.SetRangeType(10, i + iMove);
// 		}
		excel.PutValue(2, i + iMove, temp.XH);
		excel.PutValue(3, i + iMove, temp.WH);
		excel.PutValue(4, i + iMove, temp.DH);	
		excel.PutValue(6, i + iMove, FindDhName(temp.DH));
		excel.PutValue(8, i + iMove, temp.SL);

		
		iMark++;
	}
	CString sExcelPath;

	CFileDialog openFileDlg(FALSE, NULL, _T("分机或模块明细表.xlsx"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("文件(*.xls;*.xlsx)|*.xls;*.xlsx||"), NULL);
	INT_PTR result = openFileDlg.DoModal();
	if (result==IDOK)
	{
		sExcelPath = openFileDlg.GetPathName();
	}
	else
	{
		excel.Quit();
		return false;
	}
	excel.SaveAs(sExcelPath);
	excel.Quit();

	ShellExecute(
		0,
		_T("open"),
		sExcelPath,
		NULL,
		NULL,
		SW_SHOWNORMAL);

	return true;
}

CString CDlgMain::FindDhName(CString sDh)
{
	std::vector<CString> vecText=GetTextVal(GetTextPath());
	for (int i = 0; i < vecText.size();i++)
	{
		CString sTemp = vecText[i];
		std::vector<CString> vecConver;
		CStringUtil::Split(sTemp, _T("|"), vecConver);
		if (vecConver.size()==3)
		{
			if (sDh==vecConver[0])
			{
				return vecConver[1];
			}
		}
	}
	return _T("");
}

void CDlgMain::OnBnClickedBtnSetview()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GetDlgItemText(IDC_CMB_VIEW, m_sCurrentView);
	if (m_sCurrentView == _T(""))
	{
		AfxMessageBox(_T("视图信息获取为空"));
		return;
	}
	acDocManager->lockDocument(curDoc());
	AcDbObjectIdArray idArr;
	bool b=GetSelection(idArr, _T("\n选择需要设置视图的实体."));
	if (b)
	{
		for (int i = 0; i < idArr.length();i++)
		{
			AcDbEntity *pEnt = NULL;
			Acad::ErrorStatus es;
			es = acdbOpenAcDbEntity(pEnt, idArr[i], AcDb::kForWrite);
			if (es!=eOk)
			{
				continue;
			}
			CDwgDatabaseUtil::SetXdata(_T("视图"), m_sCurrentView, pEnt);
			pEnt->close();
		}
	}
	acDocManager->unlockDocument(curDoc());
	UpdateData(FALSE);
}

void CDlgMain::OnBnClickedBtnCheckdwg()
{
	// TODO:  在此添加控件通知处理程序代码
	m_ErrorId.removeAll();
	m_vecColor.clear();
	acDocManager->lockDocument(curDoc());
	int iMark = 0;
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
	for (int i = 0; i < idArr.length();i++)
	{
		AcDbObjectId idTemp = idArr[i];
		Acad::ErrorStatus es;
		AcDbEntity *pEnt = NULL;
		es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
		if (es!=eOk)
		{
			acutPrintf(_T("检索到一个打开失败实体."));
			continue;
		}
		if (!pEnt->isKindOf(AcDbBlockReference::desc()))
		{
			m_vecColor.push_back(pEnt->colorIndex());//存储颜色
			m_ErrorId.append(idTemp);//存储Id
			pEnt->setColorIndex(1);//设置颜色
			iMark++;
		}
		pEnt->close();
	}
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	if (iMark>0)
	{
		CString sMark;
		sMark.Format(_T("%d"), iMark);
		CString sPrompt;
		sPrompt = _T("发现: ") + sMark + _T(" 个不是图块的实体,并修改颜色为红色.");
		AfxMessageBox(sPrompt);
	}
	this->GetParent()->SetFocus();
	this->SetFocus();
}

void CDlgMain::OnBnClickedBtnRestoredwg()
{
	// TODO:  在此添加控件通知处理程序代码
	int iSize = m_vecColor.size();
	int iSizeId = m_ErrorId.length();
	if (iSize == iSizeId&&iSize != 0 && iSizeId != 0)
	{
		acDocManager->lockDocument(curDoc());
		for (int i = 0; i < iSize;i++)
		{
			AcDbObjectId idTemp = m_ErrorId[i];
			Acad::ErrorStatus es;
			AcDbEntity *pEnt = NULL;
			es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
			if (es!=eOk)
			{
				continue;
			}
			pEnt->setColorIndex(m_vecColor[i]);
			pEnt->close();
		}
		acDocManager->unlockDocument(curDoc());
		acTransactionManagerPtr()->flushGraphics();
		acedUpdateDisplay();
		if (iSizeId > 0)
		{
			CString sMark;
			sMark.Format(_T("%d"), iSizeId);
			CString sPrompt;
			sPrompt = _T("还原: ") + sMark + _T(" 个不是图块的实体.颜色已还原为原始颜色.");
			AfxMessageBox(sPrompt);
		}
	}
	this->GetParent()->SetFocus();
	this->SetFocus();
}

void CDlgMain::OnCbnSelchangeCmbView()
{
	// TODO:  在此添加控件通知处理程序代码
//	OnBnClickedBtnCheckwh();
}

void CDlgMain::OnEnChangeEditSearch()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CAcUiTabMainDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bSelect)
	{
		acutPrintf(_T("\n正在进行选择操作,请选择图块或者esc退出选择。"));
		return;
	}
	if (m_tab.GetCurSel() == 0 && m_dlgWeihao.m_vecListinfo.size() == 0)
	{
		AfxMessageBox(_T("请刷新位号信息后再进行检索处理."));
		return;
	}
	if (m_tab.GetCurSel() == 1 && m_dlgDiscern.m_vecLjxxinfo.size() == 0)
	{
		AfxMessageBox(_T("请刷新连接信息后再进行检索处理."));
		return;
	}	
	m_bZh = TRUE;
	m_bYcl = FALSE;
	m_bWcl = FALSE;
	if (m_tab.GetCurSel()==0)
	{
		m_dlgWeihao.m_bShowPrompt = false;
		m_dlgWeihao.RestoreList();
		m_dlgWeihao.m_bShowPrompt = true;
		if (m_sSearch!=_T(""))
		{
			m_dlgWeihao.SearchWh(m_sSearch);
		}
	}
	else
	{
		m_dlgDiscern.m_bShowPrompt = false;
		m_dlgDiscern.RestoreList();
		m_dlgDiscern.m_bShowPrompt = true;
		if (m_sSearch!=_T(""))
		{
			m_dlgDiscern.SearchInfo(m_sSearch);
		}
	}
	UpdateData(FALSE);
}

void CDlgMain::OnBnClickedBtnZjys()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFileDialog importDlg(TRUE, _T(".xls"), NULL, 0,
		_T("excel格式(*.xls;*.xlsx) |*.xls;*.xlsx|"), acedGetAcadFrame());
	if (importDlg.DoModal() == IDOK)
	{
		m_sZjys = importDlg.GetPathName();
	}
	else
	{
		return;
	}
	UpdateData(FALSE);
	return;
}

BOOL CDlgMain::GetMapTab()
{
	m_mapZjys.clear();//中间映射表清空
	m_dlgWeihao.m_mapZjys.clear();

	BOOL b=CheckExcelPath(m_sZjys);
	if (!b)
	{
		return FALSE;
	}
	cExcel excel;
	if (!excel.StartApp())
	{
		acutPrintf(_T("\n打开excel失败."));
		return FALSE;
	}
	excel.OpenWorkBook(m_sZjys);

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
		CString sKey, sValue;
		sKey=excel.GetCString(2,i );
		sValue = excel.GetCString(1, i);
		m_mapZjys.insert(pair<CString, CString>(sKey, sValue));
		m_dlgWeihao.m_mapZjys.insert(pair<CString, CString>(sKey, sValue));
	}
	excel.Quit();
	return TRUE;
}


void CDlgMain::OnBnClickedBtnHightlight()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	

	acDocManager->lockDocument(curDoc());

	if (m_ViewIdArr.length() != 0)
	{
		UnHighLight(m_ViewIdArr);
	}
	m_ViewIdArr.removeAll();
	GetDlgItemText(IDC_CMB_VIEW, m_sCurrentView);

	struct resbuf *rb;
	rb = acutBuildList(1001, TEXT("视图"), RTNONE);
	ads_name textArr;
	acedSSGet(TEXT("X"), NULL, NULL, rb, textArr);
	long Lenth;
	acedSSLength(textArr, &Lenth);
	for (int i = 0; i < Lenth; i++)
	{
		ads_name ent;
		acedSSName(textArr, i, ent);
		AcDbObjectId objId;
		acdbGetObjectId(objId, ent);
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt, objId, AcDb::kForWrite);
		if (es != eOk)
		{
			continue;
		}
		if (!pEnt->isKindOf(AcDbBlockReference::desc()))
		{
			pEnt->close();
			continue;
		}
		CString sEntView;
		CDwgDatabaseUtil::getXdata(_T("视图"), sEntView, pEnt);
		if (sEntView==m_sCurrentView)
		{
			m_ViewIdArr.append(objId);
		}
		
		pEnt->close();
	}
	acutRelRb(rb);
	acedSSFree(textArr);
	HighLight(m_ViewIdArr);
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	this->GetParent()->SetFocus();
	this->SetFocus();
}


void CDlgMain::OnBnClickedBtnUnhightlight()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_ViewIdArr.length()==0)
	{
		return;
	}
	acDocManager->lockDocument(curDoc());
	UnHighLight(m_ViewIdArr);
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	this->GetParent()->SetFocus();
	this->SetFocus();
}


void CDlgMain::OnBnClickedBtnMapcheck()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//检测地址
	if (!CheckExcelPath(m_sZjys)||!CheckExcelPath(m_sDqtx))
	{
		AfxMessageBox(_T("中间映射表及电气特性表地址校验失败"));
		return;
	}
	m_vecCheckMap.clear();//映射校验清空
	m_vecInfo.clear();
	GetMapTab();
	FindInfo();
	for (int i = 0; i < m_vecInfo.size();i++)
	{
		InfoAddress txbTemp = m_vecInfo[i];
		if (txbTemp.WZDM==txbTemp.COVERWZDM)
		{
			if(txbTemp.WZDM!=_T(""))
			{
				m_vecCheckMap.push_back(txbTemp.WZDM);
			}
			
		}
	}
	if (m_vecCheckMap.size()>1)
	{
 		sort(m_vecCheckMap.begin(), m_vecCheckMap.end());
 		m_vecCheckMap.erase(unique(m_vecCheckMap.begin(), m_vecCheckMap.end()), m_vecCheckMap.end());
		CString sCheckMapLogExcel;
		if (ExportCheckMapLog(sCheckMapLogExcel))
		{
			ShellExecute(0,
				_T("open"),
				sCheckMapLogExcel + _T(".xlsx"),
				NULL,
				NULL,
				SW_SHOWNORMAL);
		}
	}
	else
	{
		AfxMessageBox(_T("映射校验通过，未发现问题."));
	}
	return;
}
