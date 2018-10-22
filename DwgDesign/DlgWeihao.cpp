// DlgWeihao.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgWeihao.h"
#include "afxdialogex.h"


// CDlgWeihao �Ի���

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


// CDlgWeihao ��Ϣ�������


BOOL CDlgWeihao::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_listWeihao.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	m_listWeihao.InsertColumn(0, _T("���(�к�)"), LVCFMT_LEFT, 50);
	m_listWeihao.InsertColumn(1, _T("����"), LVCFMT_LEFT, 100);
	m_listWeihao.InsertColumn(2, _T("ģ�������ʴ���"), LVCFMT_LEFT, 150);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CDlgWeihao::RefreshList(CString sDqtxb,map<CString, CString> mapCover)
{
	UpdateData(TRUE);
	m_listWeihao.DeleteAllItems();
	m_vecLog.clear();
	m_mapName2Name.clear();//���ƶ�Ӧ���ƴ���
	cExcel excel;
	if (!excel.StartApp())
	{
		acutPrintf(_T("\n��excelʧ��."));
		return;
	}
	excel.OpenWorkBook(sDqtxb);
	long iNum = excel.GetSheetNum();
	acedSetStatusBarProgressMeter(TEXT("ˢ��λ����Ϣ...:"), 0, iNum);
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
			if (s1 == _T("����")&&j>=5)
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
			if (s2 == _T("ģ�������ʴ���") && s3 == _T("ĸ�������ʴ���") && s4 == _T("ģ������������") && s5 == _T("ĸ������������"))
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
					temp.wtms=sNAME+_T(":���ʴ���Ϊ��");
					temp.clfs = _T("������ʴ�����Ϣ");
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
				temp.wtms = _T("��ʽ����");
				temp.clfs = _T("������ʽ");
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
		AfxMessageBox(_T("��־�ļ���ʧ��"));
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
		bool b = CGetInputUtil::GetPoint(_T("\n�˴��޶�ֱ�Ӳ��롣��ѡ���ǲ����:"), ptTemp);
		m_bInsert = false;
		if (b)
		{
			AcDbText *pText = new AcDbText(ptTemp, sName, AcDbObjectId::kNull, iHeight);
			pText->setHorizontalMode(AcDb::kTextCenter);
			pText->setVerticalMode(AcDb::kTextVertMid);
			pText->setAlignmentPoint(ptTemp);
			CDwgDatabaseUtil::SetXdata(_T("���"), sName, pText);
			CDwgDatabaseUtil::SetXdata(_T("���ʴ���"), sWzdm, pText);
			CDwgDatabaseUtil::SetXdata(_T("��ͼ"), m_sView, pText);
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
		bool b = CGetInputUtil::GetPoint(_T("\n���������ʴ�����Ϣ����ѡ���ǲ����:"), ptTemp);
		m_bInsert = false;
		if (b)
		{
			AcDbText *pText = new AcDbText(ptTemp, sName, AcDbObjectId::kNull, iHeight);
			pText->setHorizontalMode(AcDb::kTextCenter);
			pText->setVerticalMode(AcDb::kTextVertMid);
			pText->setAlignmentPoint(ptTemp);
			CDwgDatabaseUtil::SetXdata(_T("���"), sName, pText);
			CDwgDatabaseUtil::SetXdata(_T("���ʴ���"), sWzdm, pText);
			CDwgDatabaseUtil::SetXdata(_T("��ͼ"), m_sView, pText);
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
		CDwgDatabaseUtil::getXdata(_T("��ͼ"), sView, pEnt);
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
			//��⵽��ͼ�� 
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
		bool b = CGetInputUtil::GetPoint(_T("\n�ҵ�1��ͬ���飬�Ѹ�����ʾ����ѡ���ǲ����,�Ҳ����Ӧ�ں�ɫ��ʾ����:"), ptTemp);
		if (b)
		{
			if (!PtInExten(ptTemp, GetBlockRefExten(idArr2[0], 3)))
			{
				AfxMessageBox(_T("λ�ŷ���λ�ò�����������ڣ�"));
			}
			AcDbText *pText = new AcDbText(ptTemp, sName, AcDbObjectId::kNull, iHeight);
			pText->setHorizontalMode(AcDb::kTextCenter);
			pText->setVerticalMode(AcDb::kTextVertMid);
			pText->setAlignmentPoint(ptTemp);
			CDwgDatabaseUtil::SetXdata(_T("���"), sName, pText);
			CDwgDatabaseUtil::SetXdata(_T("���ʴ���"), sWzdm, pText);
			CDwgDatabaseUtil::SetXdata(_T("��ͼ"), m_sView, pText);
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
				AfxMessageBox(_T("��esc���ٽ����л�"));
				return bRet;
			}
		}

//������ڶ�� �򴴽��˵���ʹ��
// 		CMenu menu;
// 		menu.CreatePopupMenu();
// 		for (int i = 0; i < iNum;i++)
// 		{
// 			CString sI;
// 			sI.Format(_T("%d"), i + 1);
// 			menu.AppendMenuW(MF_STRING, 10001+i, _T("ͼ��")+sI);
// 			menu.AppendMenuW(0, MF_SEPARATOR);//����һ��ֱ��
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
// 		acutPrintf(_T("\n���ҵ�%d��ͬ����"), iNum);
//  		while (CGetInputUtil::GetKeyword(_T("\n ���ɱ��<C>,��ת��һ��<N>,��ת��һ��<U>:"), _T("C N U"), _T("C"), 0, iRet))
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
// 		bool b = CGetInputUtil::GetPoint(_T("\n�Ѹ�����ʾͼ�顣��ѡ���ǲ����,�Ҳ����Ӧ�ں�ɫ��ʾ����:"), ptTemp);
// 
// 		if (b)
// 		{
// 			if (!PtInExten(ptTemp, GetBlockRefExten(idArr2[iMark], 3)))
// 			{
// 				AfxMessageBox(_T("λ�ŷ���λ�ò�����������ڣ�"));
// 			}
// 			AcDbText *pText = new AcDbText(ptTemp, sName, AcDbObjectId::kNull, iHeight);
// 			pText->setHorizontalMode(AcDb::kTextCenter);
// 			pText->setVerticalMode(AcDb::kTextVertMid);
// 			pText->setAlignmentPoint(ptTemp);
// 			CDwgDatabaseUtil::SetXdata(_T("���"), sName, pText);
// 			CDwgDatabaseUtil::SetXdata(_T("���ʴ���"), sWzdm, pText);
// 			CDwgDatabaseUtil::SetXdata(_T("��ͼ"), m_sView, pText);
// 			CDwgDatabaseUtil::PostToModelSpace(pText);
// 			bRet = true;
// 		}
// 		DeleteWire(idWireTemp);
// 		UnHighLight(idArr2);
	}
	else
	{
		/*acutPrintf(_T("\nδ�ҵ�ͬ���飬��ȡ������."));*/
		AfxMessageBox(_T("\nδ�ҵ�ͬ���飬������ͬ�����������ͼ�Σ���ȡ������."), MB_OK);
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
		CDwgDatabaseUtil::getXdata(_T("���"), sMark, pEnt);
		CDwgDatabaseUtil::getXdata(_T("���ӱ�"), sDzb, pEnt);
		CDwgDatabaseUtil::getXdata(_T("��ͼ"), sView, pEnt);
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
		AfxMessageBox(_T("λ���Լ����ӱ���һ��δ�ҵ�"));
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

	//���ڴ洢����ͼֽ�е�λ�� ������Լ�id
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
		CDwgDatabaseUtil::getXdata(_T("���"), sTag, pEnt);
		CDwgDatabaseUtil::getXdata(_T("���ʴ���"), sWzdm, pEnt);
		CDwgDatabaseUtil::getXdata(_T("��ͼ"), sView, pEnt);
		//ȡ��λ�ŵ�����
		AcDbText *pText = static_cast<AcDbText*>(pEnt);
		AcGePoint3d ptInsert = pText->alignmentPoint();

		pEnt->close();		
		if (sTag!=_T(""))
		{
			bool TabExistWh = false;//������Ƿ���ڴ�λ��

			for (int j = 0; j < m_listWeihao.GetItemCount();j++)
			{
		    	CString sTemp = m_listWeihao.GetItemText(j, 1);
				CString sTemp2 = m_listWeihao.GetItemText(j, 2);
				//�����м�ӳ����Ϣ �����ʴ���ת��Ϊ�м�ӳ����Ϣ
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
			if (!TabExistWh)//���λ�Ų�������tab��
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
		int nRet=AfxMessageBox(_T("���ҵ�����λ��,�Ƿ���"), MB_OKCANCEL);
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
					AfxMessageBox(_T("��esc���ٽ����л�"));
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
			AfxMessageBox(_T("��ˢ��λ����Ϣȷ��׼ȷ�Ժ��ٽ���ɸѡ"));
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
	rb = acutBuildList(1001, TEXT("���"),RTNONE);
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
		CDwgDatabaseUtil::getXdata(_T("���ʴ���"), sEntWzdm, pEnt);
		CDwgDatabaseUtil::getXdata(_T("��ͼ"), sEntView, pEnt);
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
		AfxMessageBox(_T("���ڽ��в������,��ȡ���������²���."));
		*pResult = 0;
		return;
	}
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_menuPoint = point;
	m_listWeihao.ScreenToClient(&point);

	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	UINT nFlag;
	int nItem2 = m_listWeihao.HitTest(point, &nFlag);
	//˫���� �����˫����checkbox ��ȡ���仯
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
					CDwgDatabaseUtil::getXdata(_T("���"), sTemp, pEnt);
					CDwgDatabaseUtil::getXdata(_T("��ͼ"), sView, pEnt);
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
			AfxMessageBox(_T("�����Ѿ����Ϊ����,��ɾ����Ǻ�ʹ�ü��λ��ˢ��."), MB_OK);
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
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_listWeihao.ScreenToClient(&point);

	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	UINT nFlag;
	int nItem2 = m_listWeihao.HitTest(point, &nFlag);
	//������ �����˫����checkbox ��ȡ���仯
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
		AfxMessageBox(_T("���ڽ��в������,��ȡ���������²���."));
		*pResult = 0;
		return;
	}
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_listWeihao.ScreenToClient(&point);

	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	UINT nFlag;
	int nItem2 = m_listWeihao.HitTest(point, &nFlag);
	//˫���� �����˫����checkbox ��ȡ���仯
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
			AfxMessageBox(_T("������δ����,�޷�����."), MB_OK);
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
	// TODO:  �ڴ����ר�ô����/����û���
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
		AfxMessageBox(_T("���ڽ��в������,��ȡ���������²���."));
		*pResult = 0;
		return;
	}
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_listWeihao.ScreenToClient(&point);

	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	UINT nFlag;
	int nItem2 = m_listWeihao.HitTest(point, &nFlag);
	//˫���� �����˫����checkbox ��ȡ���仯
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
//			AfxMessageBox(_T("�����Ѿ����Ϊ����,��ɾ����Ǻ�ʹ�ü��λ��ˢ��."), MB_OK);
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
	// TODO:  �ڴ����ר�ô����/����û���
	UINT uID = (UINT)wParam;
	m_iMenuClick = uID - 10001;
	if (m_iMenuClick>=0&&m_iMenuClick<1000)
	{
		acDocManager->lockDocument(curDoc());

		MoveView(m_ptArr[m_iMenuClick], m_dX * 3, m_dY * 3);
		HighLight(m_idArrBlock);
		AcDbObjectId idPrompt = WirePrompt(GetBlockRefExten(m_idArrBlock[m_iMenuClick], 3));
		AcGePoint3d ptTemp;
		acutPrintf(_T("����%d��ͼ��"), m_iBlockNum);

// 		int iRet;
// 		bool insertBlock = false;
// 
// 		m_bInsert = true;
// 		while (CGetInputUtil::GetKeyword(_T("\n ���ɱ��<C>,��ת��һ��<N>,��ת��һ��<U>:"), _T("C N U"), _T("C"), 0, iRet))
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
			bool b = CGetInputUtil::GetPoint(_T("\n�Ѹ�����ʾͼ�顣��ѡ���ǲ����,�Ҳ����Ӧ�ں�ɫ��ʾ����:"), ptTemp);
			m_bInsert = false;
			if (b)
			{
				if (!PtInExten(ptTemp, GetBlockRefExten(m_idArrBlock[m_iMenuClick], 3)))
				{
					AfxMessageBox(_T("λ�ŷ���λ�ò�����������ڣ�"));
				}
				AcDbText *pText = new AcDbText(ptTemp, m_sCreatName, AcDbObjectId::kNull, m_iHeight);
				pText->setHorizontalMode(AcDb::kTextCenter);
				pText->setVerticalMode(AcDb::kTextVertMid);
				pText->setAlignmentPoint(ptTemp);
				CDwgDatabaseUtil::SetXdata(_T("���"), m_sCreatName, pText);
				CDwgDatabaseUtil::SetXdata(_T("���ʴ���"), m_sWzdm, pText);
				CDwgDatabaseUtil::SetXdata(_T("��ͼ"), m_sView, pText);
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
