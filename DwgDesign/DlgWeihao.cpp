// DlgWeihao.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgWeihao.h"
#include "afxdialogex.h"


// CDlgWeihao 对话框

IMPLEMENT_DYNAMIC(CDlgWeihao, CAcUiTabChildDialog)

CDlgWeihao::CDlgWeihao(CWnd* pParent /*=NULL*/)
: CAcUiTabChildDialog(pParent)
{
	m_bInsert = false;
	m_bShowPrompt = true;
}

CDlgWeihao::~CDlgWeihao()
{
}

void CDlgWeihao::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WEIHAO, m_listWeihao);

}


BEGIN_MESSAGE_MAP(CDlgWeihao, CAcUiTabChildDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_WEIHAO, &CDlgWeihao::OnNMDblclkListWeihao)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_WEIHAO, &CDlgWeihao::OnLvnItemchangedListWeihao)
//	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_WEIHAO, &CDlgWeihao::OnLvnItemchangingListWeihao)
ON_NOTIFY(NM_CLICK, IDC_LIST_WEIHAO, &CDlgWeihao::OnNMClickListWeihao)
ON_NOTIFY(NM_RDBLCLK, IDC_LIST_WEIHAO, &CDlgWeihao::OnNMRDblclkListWeihao)
ON_NOTIFY(NM_RCLICK, IDC_LIST_WEIHAO, &CDlgWeihao::OnNMRClickListWeihao)
END_MESSAGE_MAP()


// CDlgWeihao 消息处理程序


BOOL CDlgWeihao::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();
	// TODO:  在此添加额外的初始化
	m_listWeihao.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	m_listWeihao.InsertColumn(0, _T("标记(行号)"), LVCFMT_LEFT, 50);
	m_listWeihao.InsertColumn(1, _T("名称"), LVCFMT_LEFT, 100);
	m_listWeihao.InsertColumn(2, _T("模块用物资代码"), LVCFMT_LEFT, 150);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CDlgWeihao::RefreshList(CString sDqtxb,map<CString, CString> mapCover)
{
	UpdateData(TRUE);
	m_listWeihao.DeleteAllItems();
	m_vecLog.clear();
	m_mapName2Name.clear();//名称对应名称处理
	cExcel excel;
	if (!excel.StartApp())
	{
		acutPrintf(_T("\n打开excel失败."));
		return;
	}
	excel.OpenWorkBook(sDqtxb);
	long iNum = excel.GetSheetNum();
	acedSetStatusBarProgressMeter(TEXT("刷新位号信息...:"), 0, iNum);
	int iMark = 0;
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
			if (s1 == _T("名称")&&j>=5)
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
			if (s2 == _T("模块用物资代码") && s3 == _T("母板用物资代码") && s4 == _T("模块连接器名称") && s5 == _T("母板连接器名称"))
			{
				CString  sNAME, sMKWZDM, sMBWZDM, sMKLJQNAME, sMBLJQNAME, sConverWzdm;
				sNAME = excel.GetCString(2, j);
				sMKWZDM = excel.GetCString(2, j - 1);
				sMBWZDM = excel.GetCString(2, j - 2);
				sMKLJQNAME = excel.GetCString(2, j - 3);
				sMBLJQNAME = excel.GetCString(2, j - 4);

				if (sMKWZDM==_T("")&&sMKLJQNAME==_T("")&&sMBWZDM==_T("")&&sMBLJQNAME==_T(""))
				{
					CString si, srow;
					si.Format(_T("%d"), i);
					srow.Format(_T("%d"), j);
					Log temp;
					temp.sheet = /*si*/sSheetName;
					temp.row = srow;
					temp.col = _T("1");
					temp.wtms=sNAME+_T(":物资代码为空");
					temp.clfs = _T("添加物资代码信息");
					if(sNAME!=_T(""))
					{
						m_vecLog.push_back(temp);
					}
					continue;
				}
				CString weihao, wuzidaima;
				GetWeihaoAndWzdm(sNAME, sMKWZDM, sMBWZDM, sMKLJQNAME, sMBLJQNAME, sSheetName, weihao, wuzidaima);

				if (weihao != _T(""))
				{
					int nRow = m_listWeihao.InsertItem(iMark, _T(""));
					CString sI;
					sI.Format(_T("%d"), iMark + 1);
					m_listWeihao.SetItemText(nRow, 0, sI);
					iMark++;
					weihao = ConvertString(weihao);
					m_listWeihao.SetItemText(nRow, 1, weihao);
					m_listWeihao.SetItemText(nRow, 2, wuzidaima);
				}
				
			}
			else
			{
				CString si, srow;
				si.Format(_T("%d"), i);
				srow.Format(_T("%d"), j);
				Log temp;
				temp.sheet = /*si*/sSheetName;
				temp.row = srow;
				temp.col = _T("1");
				temp.wtms = _T("格式错误");
				temp.clfs = _T("调整格式");
				m_vecLog.push_back(temp);
				continue;
			}
		}
	}
	acedRestoreStatusBar();
	excel.Quit();
	UpdateData(FALSE);
}

bool CDlgWeihao::ExportLog(CString &sExcelPath)
{
	if (m_vecLog.size()==0)
	{
		return false;
	}
	CString sPath = GetExcelLogPath();
	cExcel excel;
	if (!excel.StartApp())
	{
		AfxMessageBox(_T("日志文件打开失败"));
		return false;
	}
	excel.OpenWorkBook(sPath);
	for (int i = 0; i < m_vecLog.size();i++)
	{
		Log temp = m_vecLog[i];
		excel.PutValue(1, i + 2, temp.sheet);
		excel.PutValue(2, i + 2, temp.row);
		excel.PutValue(3, i + 2, temp.col);
		excel.PutValue(4, i + 2, temp.wtms);
	}
	sExcelPath = GetLogFolderPath() + GetTimer();
	excel.SaveAs(sExcelPath);
	excel.Quit();
	return true;
}

extern CDlgSelectItem *pDlgSelect;

bool CDlgWeihao::CreatMark(CString sName, CString sWzdm, int iHeight,bool bNoneBlock/*=false*/)
{
	this->GetParent()->GetDlgItemText(IDC_CMB_VIEW, m_sView);
	acDocManager->lockDocument(curDoc());
	if (bNoneBlock)
	{
		bool bRetWzdm = false;
		AcGePoint3d ptTemp;
		m_bInsert = true;
		bool b = CGetInputUtil::GetPoint(_T("\n此处限定直接插入。请选择标记插入点:"), ptTemp);
		m_bInsert = false;
		if (b)
		{
			AcDbText *pText = new AcDbText(ptTemp, sName, AcDbObjectId::kNull, iHeight);
			pText->setHorizontalMode(AcDb::kTextCenter);
			pText->setVerticalMode(AcDb::kTextVertMid);
			pText->setAlignmentPoint(ptTemp);
			CDwgDatabaseUtil::SetXdata(_T("标记"), sName, pText);
			CDwgDatabaseUtil::SetXdata(_T("物资代码"), sWzdm, pText);
			CDwgDatabaseUtil::SetXdata(_T("视图"), m_sView, pText);
			CDwgDatabaseUtil::PostToModelSpace(pText);
			bRetWzdm = true;
		}
		acDocManager->unlockDocument(curDoc());
		acTransactionManagerPtr()->flushGraphics();
		acedUpdateDisplay();
		return bRetWzdm;
	}
	if (sWzdm==_T(""))
	{
		bool bRetWzdm = false;
		AcGePoint3d ptTemp;
		m_bInsert = true;
		bool b = CGetInputUtil::GetPoint(_T("\n此项无物资代码信息。请选择标记插入点:"), ptTemp);
		m_bInsert = false;
		if (b)
		{
			AcDbText *pText = new AcDbText(ptTemp, sName, AcDbObjectId::kNull, iHeight);
			pText->setHorizontalMode(AcDb::kTextCenter);
			pText->setVerticalMode(AcDb::kTextVertMid);
			pText->setAlignmentPoint(ptTemp);
			CDwgDatabaseUtil::SetXdata(_T("标记"), sName, pText);
			CDwgDatabaseUtil::SetXdata(_T("物资代码"), sWzdm, pText);
			CDwgDatabaseUtil::SetXdata(_T("视图"), m_sView, pText);
			CDwgDatabaseUtil::PostToModelSpace(pText);
			bRetWzdm = true;
		}
		acDocManager->unlockDocument(curDoc());
		acTransactionManagerPtr()->flushGraphics();
		acedUpdateDisplay();
		return bRetWzdm;
	}
	AcGePoint3dArray ptArr;
	AcDbObjectIdArray idArr2;
	AcDbExtents ext;
	double dX=20, dY=20;
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
	int iNumEnt = idArr.length();
	for (int i = 0; i < iNumEnt; i++)
	{
		AcDbObjectId idTemp = idArr[i];
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es;
		es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForRead);
		if (es != eOk)
		{
			continue;
		}
		if (!pEnt->isKindOf(AcDbBlockReference::desc()))
		{
			pEnt->close();
			continue;
		}
		CString sView;
		CDwgDatabaseUtil::getXdata(_T("视图"), sView, pEnt);
		AcDbBlockReference *pRef = static_cast<AcDbBlockReference*>(pEnt);
		AcDbObjectId RecId = pRef->blockTableRecord();
		AcDbBlockTableRecord *pRec = NULL;
		es = acdbOpenObject(pRec, RecId, AcDb::kForRead);
		if (es != eOk)
		{
			pRef->close();
			continue;
		}
		ACHAR* nameTemp; CString sNameTemp;
		pRec->getName(nameTemp);
		sNameTemp.Format(_T("%s"), nameTemp);
		if (/*sNameTemp == sWzdm*/Compare2String(sNameTemp,sWzdm)&&sView==m_sView)
		{
			//检测到此图块 
			AcGePoint3d ptTemp = GetBlcokRefCenter(pRef, dX, dY);
			AcDbExtents extTemp = GetBlockRefExten(pRef, 3);
 			if (!CheckPtCreatWh(sWzdm,m_sView,extTemp))
 			{
				ptArr.append(ptTemp);
				idArr2.append(idTemp);
			}		
			
		}
		pRec->close();
		pRef->close();
	}

	int iNum = ptArr.length();
	bool bRet = false;
	if (iNum == 1)
	{
		MoveView(ptArr[0], dX*3, dY*3);
		HighLight(idArr2);
		AcGePoint3d ptTemp;
		AcDbObjectId idWireTemp=WirePrompt(GetBlockRefExten(idArr2[0],3));
		bool b = CGetInputUtil::GetPoint(_T("\n找到1个同名块，已高亮显示。请选择标记插入点,且插入点应在红色提示框内:"), ptTemp);
		if (b)
		{
			if (!PtInExten(ptTemp, GetBlockRefExten(idArr2[0], 3)))
			{
				AfxMessageBox(_T("位号放置位置不在所属红框内！"));
			}
			AcDbText *pText = new AcDbText(ptTemp, sName, AcDbObjectId::kNull, iHeight);
			pText->setHorizontalMode(AcDb::kTextCenter);
			pText->setVerticalMode(AcDb::kTextVertMid);
			pText->setAlignmentPoint(ptTemp);
			CDwgDatabaseUtil::SetXdata(_T("标记"), sName, pText);
			CDwgDatabaseUtil::SetXdata(_T("物资代码"), sWzdm, pText);
			CDwgDatabaseUtil::SetXdata(_T("视图"), m_sView, pText);
			CDwgDatabaseUtil::PostToModelSpace(pText);
			bRet = true;
		}
		DeleteWire(idWireTemp);
		UnHighLight(idArr2);
	}
	else if (iNum > 1)
	{
		m_bSuccessInsert = false;
		m_iMenuClick = 0;
		m_iBlockNum = iNum;
		m_idArrBlock = idArr2;
		m_ptArr = ptArr;
		m_sCreatName = sName;
		m_sWzdm = sWzdm;
		m_iHeight = iHeight;
		m_dX = dX;
		m_dY = dY;

		if (pDlgSelect==NULL)
		{
			pDlgSelect = new CDlgSelectItem(m_iBlockNum, m_ptArr, m_idArrBlock, dX, dY, sName, sWzdm, m_sView, iHeight, &m_listWeihao,m_nItem, acedGetAcadFrame());
			pDlgSelect->Create(IDD_DLG_ITEMSELECT);
			pDlgSelect->ShowWindow(SW_SHOW);
			::SetWindowPos(pDlgSelect->m_hWnd, HWND_TOP, m_menuPoint.x, m_menuPoint.y, 0, 0, SWP_NOSIZE);
		}
		else
		{
			if (!pDlgSelect->m_bInsert)
			{
				pDlgSelect->DestroyWindow();
				pDlgSelect = new CDlgSelectItem(m_iBlockNum, m_ptArr, m_idArrBlock, dX, dY, sName, sWzdm, m_sView, iHeight, &m_listWeihao, m_nItem, acedGetAcadFrame());
				pDlgSelect->Create(IDD_DLG_ITEMSELECT);
				pDlgSelect->ShowWindow(SW_SHOW);
				::SetWindowPos(pDlgSelect->m_hWnd, HWND_TOP, m_menuPoint.x, m_menuPoint.y, 0, 0, SWP_NOSIZE);
			}
			else
			{
				AfxMessageBox(_T("请esc后再进行切换"));
				return bRet;
			}
		}

//如果存在多个 则创建菜单供使用
// 		CMenu menu;
// 		menu.CreatePopupMenu();
// 		for (int i = 0; i < iNum;i++)
// 		{
// 			CString sI;
// 			sI.Format(_T("%d"), i + 1);
// 			menu.AppendMenuW(MF_STRING, 10001+i, _T("图块")+sI);
// 			menu.AppendMenuW(0, MF_SEPARATOR);//增加一条直线
// 		}
// 		menu.TrackPopupMenu(TPM_LEFTBUTTON, m_menuPoint.x, m_menuPoint.y, this);
// 		menu.DestroyMenu();

// 		int iMark = 0;
// 		MoveView(ptArr[iMark], dX * 3, dY * 3);
// 
// 		AcDbObjectId idPrompt = WirePrompt(GetBlockRefExten(idArr2[iMark],3));
// 
// 		HighLight(idArr2);
// 		AcGePoint3d ptTemp;
// 
//  		int iRet;
// 		acutPrintf(_T("\n共找到%d个同名块"), iNum);
//  		while (CGetInputUtil::GetKeyword(_T("\n 生成标记<C>,跳转下一个<N>,跳转上一个<U>:"), _T("C N U"), _T("C"), 0, iRet))
//  		{
//  			if (iRet == 0)
//  			{
//  				break;
//  			}
//  			else if (iRet==1)
// 			{
//  				iMark++;
//  				if (iMark>=iNum)
//  				{
// 					iMark = iNum-1;
// 				}
// 				MoveView(ptArr[iMark], dX * 3, dY * 3);
// 				DeleteWire(idPrompt);
// 				idPrompt = WirePrompt(GetBlockRefExten(idArr2[iMark], 3));
// 			}
// 			else if (iRet==2)
// 			{
// 				iMark--;
// 				if (iMark<0)
// 				{
// 					iMark = 0;
// 				}
// 				MoveView(ptArr[iMark], dX * 3, dY * 3);
// 				DeleteWire(idPrompt);
// 				idPrompt = WirePrompt(GetBlockRefExten(idArr2[iMark], 3));
// 			}
// 		}
// 		DeleteWire(idPrompt);
// 
// 		AcDbObjectId idWireTemp = WirePrompt(GetBlockRefExten(idArr2[iMark], 3));
// 
// 		bool b = CGetInputUtil::GetPoint(_T("\n已高亮显示图块。请选择标记插入点,且插入点应在红色提示框内:"), ptTemp);
// 
// 		if (b)
// 		{
// 			if (!PtInExten(ptTemp, GetBlockRefExten(idArr2[iMark], 3)))
// 			{
// 				AfxMessageBox(_T("位号放置位置不在所属红框内！"));
// 			}
// 			AcDbText *pText = new AcDbText(ptTemp, sName, AcDbObjectId::kNull, iHeight);
// 			pText->setHorizontalMode(AcDb::kTextCenter);
// 			pText->setVerticalMode(AcDb::kTextVertMid);
// 			pText->setAlignmentPoint(ptTemp);
// 			CDwgDatabaseUtil::SetXdata(_T("标记"), sName, pText);
// 			CDwgDatabaseUtil::SetXdata(_T("物资代码"), sWzdm, pText);
// 			CDwgDatabaseUtil::SetXdata(_T("视图"), m_sView, pText);
// 			CDwgDatabaseUtil::PostToModelSpace(pText);
// 			bRet = true;
// 		}
// 		DeleteWire(idWireTemp);
// 		UnHighLight(idArr2);
	}
	else
	{
		/*acutPrintf(_T("\n未找到同名块，已取消生成."));*/
		AfxMessageBox(_T("\n未找到同名块，或所有同名块均已生成图形，已取消生成."), MB_OK);
	}
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	return bRet;
}

bool CDlgWeihao::ConnectDzb(CString sMarkText)
{
	this->GetParent()->GetDlgItemText(IDC_CMB_VIEW, m_sView);
	acDocManager->lockDocument(curDoc());
	AcGePoint3d ptMark = AcGePoint3d::kOrigin, ptDzb = AcGePoint3d::kOrigin;
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
		if (!pEnt->isKindOf(AcDbText::desc()) && !pEnt->isKindOf(AcDbBlockReference::desc()))
		{
			pEnt->close();
			continue;
		}
		CString sMark, sDzb, sView;
		CDwgDatabaseUtil::getXdata(_T("标记"), sMark, pEnt);
		CDwgDatabaseUtil::getXdata(_T("端子表"), sDzb, pEnt);
		CDwgDatabaseUtil::getXdata(_T("视图"), sView, pEnt);
		if (sMarkText == sMark&&sView == m_sView)
		{
			AcDbText *pText = static_cast<AcDbText*>(pEnt);
			ptMark = pText->position();
		}
		if (sMarkText == sDzb)
		{
			AcDbBlockReference *pRef = static_cast<AcDbBlockReference*>(pEnt);
			ptDzb = pRef->position();
		}
		pEnt->close();
	}
	if (ptMark == AcGePoint3d::kOrigin || ptDzb == AcGePoint3d::kOrigin)
	{
		AfxMessageBox(_T("位号以及端子表有一端未找到"));
		acDocManager->unlockDocument(curDoc());
		return false;
	}
	AcDbObjectId idPoly;
	if (AddPoly(ptMark, ptDzb, idPoly))
	{
		acDocManager->unlockDocument(curDoc());
		return true;
	}
	acDocManager->unlockDocument(curDoc());
	return false;
}

void CDlgWeihao::FindWh()
{
	m_vecListinfo.clear();

	//用于存储不在图纸中的位号 插入点以及id
	m_vecWeihaoAndPostionID.clear();

	int iItem = m_listWeihao.GetItemCount();
	for (int i = 0; i < iItem; i++)
	{
		m_listWeihao.SetCheck(i, FALSE);
		Listinfo temp;
		temp.check = FALSE;
		temp.mc = m_listWeihao.GetItemText(i, 1);
		temp.wzdm = m_listWeihao.GetItemText(i, 2);
		m_vecListinfo.push_back(temp);
	}
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
		if (!pEnt->isKindOf(AcDbText::desc()))
		{
			pEnt->close();
			continue;
		}
		CString sTag = _T("");
		CString sWzdm,sView;
		CDwgDatabaseUtil::getXdata(_T("标记"), sTag, pEnt);
		CDwgDatabaseUtil::getXdata(_T("物资代码"), sWzdm, pEnt);
		CDwgDatabaseUtil::getXdata(_T("视图"), sView, pEnt);
		//取出位号的坐标
		AcDbText *pText = static_cast<AcDbText*>(pEnt);
		AcGePoint3d ptInsert = pText->alignmentPoint();

		pEnt->close();		
		if (sTag!=_T(""))
		{
			bool TabExistWh = false;//表格中是否存在此位号

			for (int j = 0; j < m_listWeihao.GetItemCount();j++)
			{
		    	CString sTemp = m_listWeihao.GetItemText(j, 1);
				CString sTemp2 = m_listWeihao.GetItemText(j, 2);
				//如有中间映射信息 则将物资代码转化为中间映射消息
				if (m_mapZjys.size() != 0)
				{
					map<CString, CString>::iterator atTemp = m_mapZjys.find(sTemp2);
					if (atTemp != m_mapZjys.end())
					{
						sTemp2 = atTemp->second;
					}
				}
// 				if (m_mapName2Name.size()!=0)
// 				{
// 					map<CString, CString>::iterator atTemp = m_mapName2Name.find(sTemp);
// 					if (atTemp!=m_mapName2Name.end())
// 					{
// 						sTemp = atTemp->second;
// 					}
// 				}
				if (sTemp==sTag&&/*sWzdm==sTemp2*/(sWzdm!=_T("")?Compare2String(sWzdm,sTemp2):true)&&sView==m_sView)
				{
					m_listWeihao.SetCheck(j,TRUE);
					m_vecListinfo[j].check = TRUE;
					TabExistWh = true;
				}
			}
			if (!TabExistWh)//如果位号不在现有tab中
			{
				NamePtAndID temp;
				temp.name = sTag;
				temp.pt = ptInsert;
				temp.id = idTemp;
				m_vecWeihaoAndPostionID.push_back(temp);
			}
		}
	}
	acDocManager->unlockDocument(curDoc());

	if (m_vecWeihaoAndPostionID.size() != 0)
	{
		int nRet=AfxMessageBox(_T("查找到遗留位号,是否处理？"), MB_OKCANCEL);
		if (nRet==1)
		{
			if (pDlgSelect == NULL)
			{
				pDlgSelect = new CDlgSelectItem(m_vecWeihaoAndPostionID,20,20, acedGetAcadFrame());
				pDlgSelect->Create(IDD_DLG_ITEMSELECT);
				pDlgSelect->ShowWindow(SW_SHOW);
			}
			else
			{
				if (!pDlgSelect->m_bInsert)
				{
					pDlgSelect->DestroyWindow();
					pDlgSelect = new CDlgSelectItem (m_vecWeihaoAndPostionID,20,20, acedGetAcadFrame());
					pDlgSelect->Create(IDD_DLG_ITEMSELECT);
					pDlgSelect->ShowWindow(SW_SHOW);
				}
				else
				{
					AfxMessageBox(_T("请esc后再进行切换"));
				}
			}
		}
	}
	return;
}

bool CDlgWeihao::RestoreList()
{
	int iLen = m_vecListinfo.size();
	if (iLen==0)
	{
		if (m_bShowPrompt)
		{
			AfxMessageBox(_T("请刷新位号信息确保准确性后再进行筛选"));
		}		
		return false;
// 		m_vecListinfo.clear();
// 		for (int i = 0; i < m_listWeihao.GetItemCount();i++)
// 		{
// 			Listinfo temp;
// 			temp.check = m_listWeihao.GetCheck(i);
// 			temp.mc = m_listWeihao.GetItemText(i, 1);
// 			temp.wzdm = m_listWeihao.GetItemText(i, 2);
// 			m_vecListinfo.push_back(temp);
// 		}
	}
	for (int i = 0; i < m_listWeihao.GetItemCount();i++)
	{
		CString sItemp=m_listWeihao.GetItemText(i, 0);
		int iTemp = _wtoi(sItemp);
		m_vecListinfo[iTemp - 1].check = m_listWeihao.GetCheck(i);
	}
	m_listWeihao.DeleteAllItems();
	for (int i = 0; i < iLen;i++)
	{
		CString sI;
		sI.Format(_T("%d"), i + 1);

		int nRow=m_listWeihao.InsertItem(i, _T(""));
		m_listWeihao.SetItemText(nRow, 0, sI);
		m_listWeihao.SetItemText(nRow, 1, m_vecListinfo[i].mc);
		m_listWeihao.SetItemText(nRow, 2, m_vecListinfo[i].wzdm);
		m_listWeihao.SetCheck(nRow, m_vecListinfo[i].check);
	}
	UpdateData(FALSE);
	return true;
}

void CDlgWeihao::SetView(bool bCheck)
{
	bool b=RestoreList();
	if (b)
	{
		int iItem = m_listWeihao.GetItemCount();
		for (int i = iItem - 1; i >= 0; i--)
		{
			bool b = m_listWeihao.GetCheck(i);
			if (b != bCheck)
			{
				m_listWeihao.DeleteItem(i);
			}
		}
	}	
	return;
}

void CDlgWeihao::SearchWh(CString searchStr)
{
	for (int i = m_listWeihao.GetItemCount(); i >=0; i--)
	{
		CString sName = m_listWeihao.GetItemText(i, 1);
		int iCount=sName.Find(searchStr);
		if (iCount==-1)
		{
			m_listWeihao.DeleteItem(i);
		}
	}
	UpdateData(FALSE);
}

bool CDlgWeihao::CheckPtCreatWh(CString sWzdm, CString sView,AcDbExtents ext)
{
	bool bRet = false;
	struct resbuf *rb;
	rb = acutBuildList(1001, TEXT("标记"),RTNONE);
	ads_name textArr;
	acedSSGet(TEXT("X"), NULL, NULL, rb, textArr);
	long Lenth;
	acedSSLength(textArr, &Lenth);
	for (int i = 0; i < Lenth;i++)
	{
		ads_name ent;
		acedSSName(textArr, i, ent);
		AcDbObjectId objId;
		acdbGetObjectId(objId, ent);
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es= acdbOpenAcDbEntity(pEnt, objId, AcDb::kForWrite);
		if (es!=eOk)
		{
			continue;
		}
		CString sEntName, sEntWzdm, sEntView;
		CDwgDatabaseUtil::getXdata(_T("物资代码"), sEntWzdm, pEnt);
		CDwgDatabaseUtil::getXdata(_T("视图"), sEntView, pEnt);
		if (Compare2String(sWzdm,sEntWzdm)&&sView==sEntView)
		{
			AcDbText *pText = static_cast<AcDbText*>(pEnt);
			AcGePoint3d ptTemp = pText->alignmentPoint();
			if (PtInExten(ptTemp,ext))
			{
				pText->close();
				bRet = true;
				break;
			}
		}
		pEnt->close();
	}
	acutRelRb(rb);
	acedSSFree(textArr);
	return bRet;
}

void CDlgWeihao::OnNMDblclkListWeihao(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_bInsert)
	{
		AfxMessageBox(_T("正在进行插入操作,请取消后再重新操作."));
		*pResult = 0;
		return;
	}
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_menuPoint = point;
	m_listWeihao.ScreenToClient(&point);

	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	UINT nFlag;
	int nItem2 = m_listWeihao.HitTest(point, &nFlag);
	//双击后 如果是双击的checkbox 则取消变化
	if (nFlag == LVHT_ONITEMSTATEICON)
	{
		BOOL b = m_listWeihao.GetCheck(nItem2);
		m_listWeihao.SetCheck(nItem2, !b);
		*pResult = 0;
		return;
	}

	int nItem = m_listWeihao.SubItemHitTest(&lvinfo);
	if (nItem!=-1)
	{
		BOOL bCheck = m_listWeihao.GetCheck(nItem);
		if (bCheck)
		{
			AcGePoint3d ptLoc=AcGePoint3d::kOrigin;

			CString sName;
			sName = m_listWeihao.GetItemText(nItem, 1);
			this->GetParent()->GetDlgItemText(IDC_CMB_VIEW, m_sView);

	        acDocManager->lockDocument(curDoc());
			AcDbObjectIdArray idarr=CDwgDatabaseUtil::GetAllEntityIds();
	        int iNum = idarr.length();
			for (int i = 0; i < iNum; i++)
			{
					AcDbObjectId idTemp = idarr[i];
					AcDbEntity *pEnt = NULL;
					Acad::ErrorStatus es;
					es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
					if (es!=eOk)
					{
						continue;
					}
					if (!pEnt->isKindOf(AcDbText::desc()))
					{
						pEnt->close();
						continue;
					}
					CString sTemp,sView; 
					CDwgDatabaseUtil::getXdata(_T("标记"), sTemp, pEnt);
					CDwgDatabaseUtil::getXdata(_T("视图"), sView, pEnt);
					if(sName==sTemp&&sView==m_sView)
					{
						AcDbText *ptext = static_cast<AcDbText*>(pEnt);
						ptLoc = ptext->alignmentPoint();
			            ptext->close();
						break;
					}
					pEnt->close();
			}
			if(ptLoc!=AcGePoint3d::kOrigin)
			{
				MoveView(ptLoc,20,20);
			}		
			acDocManager->unlockDocument(curDoc());
			acTransactionManagerPtr()->flushGraphics();
			acedUpdateDisplay();
			AfxMessageBox(_T("此项已经标记为处理,请删除标记后使用检测位号刷新."), MB_OK);
			*pResult = 0;
			return;
		}
		CString sName, sWzdm;
		sName = m_listWeihao.GetItemText(nItem, 1);
		sWzdm = m_listWeihao.GetItemText(nItem, 2);
		if (m_mapZjys.size() != 0)
		{
			map<CString, CString>::iterator atTemp = m_mapZjys.find(sWzdm);
			if (atTemp != m_mapZjys.end())
			{
				sWzdm = atTemp->second;
			}
		}
// 		if (m_mapName2Name.size()!=0)
// 		{
// 			map<CString, CString>::iterator atTemp = m_mapName2Name.find(sName);
// 			if (atTemp!=m_mapName2Name.end())
// 			{
// 				sName = atTemp->second;
// 			}
// 		}

		m_bInsert = true;
		m_nItem = nItem;
		bool b=CreatMark(sName, sWzdm, 3);
		m_bInsert = false;
		if (b)
		{
			m_listWeihao.SetCheck(nItem,TRUE);		
		}
	}
	*pResult = 0;
}

//void CDlgWeihao::OnLvnItemchangedListWeihao(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO:  在此添加控件通知处理程序代码
//
//	DWORD dwPos = GetMessagePos();
//	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
//	m_listWeihao.ScreenToClient(&point);
//
//	LVHITTESTINFO   lvinfo;
//	lvinfo.pt = point;
//	lvinfo.flags = LVHT_ABOVE;
//
//	UINT nFlag;
//	int nItem = m_listWeihao.HitTest(point, &nFlag);
//
//	
//	if (nFlag == LVHT_ONITEMSTATEICON)
//	{
//		m_listWeihao.SetCheck(nItem, FALSE);
//	}
//	*pResult = 0;
//
//}


//void CDlgWeihao::OnLvnItemchangingListWeihao(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO:  在此添加控件通知处理程序代码
//	DWORD dwPos = GetMessagePos();
//	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
//	m_listWeihao.ScreenToClient(&point);
//
//	LVHITTESTINFO   lvinfo;
//	lvinfo.pt = point;
//	lvinfo.flags = LVHT_ABOVE;
//
//	UINT nFlag;
//	int nItem = m_listWeihao.HitTest(point, &nFlag);
//
//
//	if (nFlag == LVHT_ONITEMSTATEICON)
//	{
//		BOOL b = m_listWeihao.GetCheck(nItem);
//		m_listWeihao.SetCheck(!b);
//	}
//	*pResult = 0;
//}


void CDlgWeihao::OnNMClickListWeihao(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_listWeihao.ScreenToClient(&point);

	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	UINT nFlag;
	int nItem2 = m_listWeihao.HitTest(point, &nFlag);
	//单击后 如果是双击的checkbox 则取消变化
	if (nFlag == LVHT_ONITEMSTATEICON)
	{
		BOOL b=m_listWeihao.GetCheck(nItem2);
		m_listWeihao.SetCheck(nItem2,!b);
		*pResult = 0;
		return;
	}
	*pResult = 0;
}


void CDlgWeihao::OnNMRDblclkListWeihao(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_bInsert)
	{
		AfxMessageBox(_T("正在进行插入操作,请取消后再重新操作."));
		*pResult = 0;
		return;
	}
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_listWeihao.ScreenToClient(&point);

	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	UINT nFlag;
	int nItem2 = m_listWeihao.HitTest(point, &nFlag);
	//双击后 如果是双击的checkbox 则取消变化
	if (nFlag == LVHT_ONITEMSTATEICON)
	{
		BOOL b = m_listWeihao.GetCheck(nItem2);
		m_listWeihao.SetCheck(nItem2, !b);
		*pResult = 0;
		return;
	}

	int nItem = m_listWeihao.SubItemHitTest(&lvinfo);
	if (nItem != -1)
	{
		BOOL bCheck = m_listWeihao.GetCheck(nItem);
		if (!bCheck)
		{
			AfxMessageBox(_T("此项标记未处理,无法操作."), MB_OK);
			*pResult = 0;
			return;
		}

		CString sName;
		sName = m_listWeihao.GetItemText(nItem, 1);

		m_bInsert = true;
		bool b = ConnectDzb(sName);
		m_bInsert = false;
		
	}
	*pResult = 0;
}


BOOL CDlgWeihao::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_SPACE)
	{
	 	return TRUE;
	}
	else
	{
		return CAcUiTabChildDialog::PreTranslateMessage(pMsg);
	}
	
}


void CDlgWeihao::OnNMRClickListWeihao(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_bInsert)
	{
		AfxMessageBox(_T("正在进行插入操作,请取消后再重新操作."));
		*pResult = 0;
		return;
	}
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_listWeihao.ScreenToClient(&point);

	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	UINT nFlag;
	int nItem2 = m_listWeihao.HitTest(point, &nFlag);
	//双击后 如果是双击的checkbox 则取消变化
	if (nFlag == LVHT_ONITEMSTATEICON)
	{
		BOOL b = m_listWeihao.GetCheck(nItem2);
		m_listWeihao.SetCheck(nItem2, !b);
		*pResult = 0;
		return;
	}

	int nItem = m_listWeihao.SubItemHitTest(&lvinfo);
	if (nItem != -1)
	{
		BOOL bCheck = m_listWeihao.GetCheck(nItem);
		if (bCheck)
		{
//			AfxMessageBox(_T("此项已经标记为处理,请删除标记后使用检测位号刷新."), MB_OK);
			CString sName;
		    sName = m_listWeihao.GetItemText(nItem, 1);

		    m_bInsert = true;
		    bool b = ConnectDzb(sName);
		    m_bInsert = false;

			*pResult = 0;
			return;
		}
		CString sName, sWzdm;
		sName = m_listWeihao.GetItemText(nItem, 1);
		sWzdm = m_listWeihao.GetItemText(nItem, 2);
		if (m_mapZjys.size() != 0)
		{
			map<CString, CString>::iterator atTemp = m_mapZjys.find(sWzdm);
			if (atTemp != m_mapZjys.end())
			{
				sWzdm = atTemp->second;
			}
		}
		m_bInsert = true;
		bool b = CreatMark(sName, _T(""), 3,true);
		m_bInsert = false;
		if (b)
		{
			m_listWeihao.SetCheck(nItem, TRUE);
		}
	}
	*pResult = 0;
}


BOOL CDlgWeihao::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO:  在此添加专用代码和/或调用基类
	UINT uID = (UINT)wParam;
	m_iMenuClick = uID - 10001;
	if (m_iMenuClick>=0&&m_iMenuClick<1000)
	{
		acDocManager->lockDocument(curDoc());

		MoveView(m_ptArr[m_iMenuClick], m_dX * 3, m_dY * 3);
		HighLight(m_idArrBlock);
		AcDbObjectId idPrompt = WirePrompt(GetBlockRefExten(m_idArrBlock[m_iMenuClick], 3));
		AcGePoint3d ptTemp;
		acutPrintf(_T("共有%d个图块"), m_iBlockNum);

// 		int iRet;
// 		bool insertBlock = false;
// 
// 		m_bInsert = true;
// 		while (CGetInputUtil::GetKeyword(_T("\n 生成标记<C>,跳转下一个<N>,跳转上一个<U>:"), _T("C N U"), _T("C"), 0, iRet))
// 		{
// 			if (iRet == 0)
// 			{
// 				insertBlock = true;
// 				break;
// 			}
// 			else if (iRet == 1)
// 			{
// 				m_iMenuClick++;
// 				if (m_iMenuClick >= m_iBlockNum)
// 				{
// 					m_iMenuClick = m_iBlockNum - 1;
// 				}
// 				MoveView(m_ptArr[m_iMenuClick], m_dX * 3, m_dY * 3);
// 				DeleteWire(idPrompt);
// 				idPrompt = WirePrompt(GetBlockRefExten(m_idArrBlock[m_iMenuClick], 3));
// 			}
// 			else if (iRet == 2)
// 			{
// 				m_iMenuClick--;
// 				if (m_iMenuClick < 0)
// 				{
// 					m_iMenuClick = 0;
// 				}
// 				MoveView(m_ptArr[m_iMenuClick], m_dX * 3, m_dY * 3);
// 				DeleteWire(idPrompt);
// 				idPrompt = WirePrompt(GetBlockRefExten(m_idArrBlock[m_iMenuClick], 3));
// 			}
// 		}

// 		if (insertBlock)
// 		{
		    m_bInsert = true;
			bool b = CGetInputUtil::GetPoint(_T("\n已高亮显示图块。请选择标记插入点,且插入点应在红色提示框内:"), ptTemp);
			m_bInsert = false;
			if (b)
			{
				if (!PtInExten(ptTemp, GetBlockRefExten(m_idArrBlock[m_iMenuClick], 3)))
				{
					AfxMessageBox(_T("位号放置位置不在所属红框内！"));
				}
				AcDbText *pText = new AcDbText(ptTemp, m_sCreatName, AcDbObjectId::kNull, m_iHeight);
				pText->setHorizontalMode(AcDb::kTextCenter);
				pText->setVerticalMode(AcDb::kTextVertMid);
				pText->setAlignmentPoint(ptTemp);
				CDwgDatabaseUtil::SetXdata(_T("标记"), m_sCreatName, pText);
				CDwgDatabaseUtil::SetXdata(_T("物资代码"), m_sWzdm, pText);
				CDwgDatabaseUtil::SetXdata(_T("视图"), m_sView, pText);
				CDwgDatabaseUtil::PostToModelSpace(pText);
				m_bSuccessInsert = true;
			}
// 		}
// 		else
// 		{
// 			m_bInsert = false;
// 		}
		
		DeleteWire(idPrompt);
		UnHighLight(m_idArrBlock);

		acDocManager->unlockDocument(curDoc());
		acTransactionManagerPtr()->flushGraphics();
		acedUpdateDisplay();
		if (m_bSuccessInsert)
		{
			m_listWeihao.SetCheck(m_nItem, TRUE);
		}
	}
	return CAcUiTabChildDialog::OnCommand(wParam, lParam);
}
