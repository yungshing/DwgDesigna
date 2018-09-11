// DlgDiscern.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgDiscern.h"
#include "afxdialogex.h"


// CDlgDiscern �Ի���

IMPLEMENT_DYNAMIC(CDlgDiscern, CAcUiTabChildDialog)

CDlgDiscern::CDlgDiscern(CWnd* pParent /*=NULL*/)
: CAcUiTabChildDialog(pParent)
{
	m_bShowPrompt = true;
}

CDlgDiscern::~CDlgDiscern()
{
}

void CDlgDiscern::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, m_listInfo);
}


BEGIN_MESSAGE_MAP(CDlgDiscern, CAcUiTabChildDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_INFO, &CDlgDiscern::OnNMDblclkListInfo)
	ON_NOTIFY(NM_CLICK, IDC_LIST_INFO, &CDlgDiscern::OnNMClickListInfo)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_INFO, &CDlgDiscern::OnLvnItemchangedListInfo)
END_MESSAGE_MAP()


// CDlgDiscern ��Ϣ�������


BOOL CDlgDiscern::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_listInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	m_listInfo.InsertColumn(0, _T("�к�"), LVCFMT_LEFT, 50);
	m_listInfo.InsertColumn(1, _T("�Ժδ���"), LVCFMT_LEFT, 100);
	m_listInfo.InsertColumn(2, _T("�ӵ��δ�"), LVCFMT_LEFT, 100);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgDiscern::RefreshList(CString sJxb)
{
	UpdateData(TRUE);
	std::vector<HclToDhc> vec;
	m_listInfo.DeleteAllItems();
	cExcel excel;
	if (!excel.StartApp())
	{
		acutPrintf(_T("\n��excelʧ��."));
		return;
	}
	excel.OpenWorkBook(sJxb/*,_T("���߱�")*/);
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

	acedSetStatusBarProgressMeter(TEXT("ˢ�����ӹ�ϵ...:"), 0, iRowNum);
	for (int j = iStartRow; j < iRowNum + iStartRow; j++)
	{
		acedSetStatusBarProgressMeterPos(j-iStartRow+1);
		CString sHCL, sDHC;
		//2018.8.2 �޸Ľ��߱���ȡλ��
		CString sTemp = excel.GetCString(4, j);
		CString sTemp2 = excel.GetCString(6, j);
		if (sTemp==_T("")||sTemp2==_T(""))
		{
			continue;
		}
		std::vector<CString> vec1, vec2;
		CStringUtil::Split(sTemp, _T(":"), vec1, false);
		CStringUtil::Split(sTemp2, _T(":"), vec2, false);
		if (vec1.size()<2||vec2.size()<2)
		{
			continue;
		}
		sHCL = vec1[0];
		sDHC = vec2[0];
		HclToDhc temp;
		sHCL = ConvertString(sHCL);//ȥ����
		sDHC = ConvertString(sDHC);

		sHCL = RemoveMk(sHCL);
		sDHC = RemoveMk(sDHC);

		sHCL = RemoveQh(sHCL);//ȥǻ��
		sDHC = RemoveQh(sDHC);

		temp.sHcl = sHCL;
		temp.sDhc = sDHC;
		vec.push_back(temp);	
	}
	acedRestoreStatusBar();
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	for (int i = 0; i < vec.size();i++)
	{
		HclToDhc hcTemp = vec[i];
		CString sHcl, sDhc;
		sHcl = hcTemp.sHcl;
		sDhc = hcTemp.sDhc;

		int nRow = m_listInfo.InsertItem(i, _T(""));
		CString sI;
		sI.Format(_T("%d"), i + 1);
		m_listInfo.SetItemText(nRow, 0, sI);
		m_listInfo.SetItemText(nRow, 1, sHcl);
		m_listInfo.SetItemText(nRow, 2, sDhc);
	}
	excel.Quit();
	UpdateData(FALSE);
}

BOOL CDlgDiscern::HighLightText(CString sRowNum,CString sText,CString sText2)
{
	acDocManager->lockDocument(curDoc());
	BOOL b = TRUE;
	BOOL bCreat=FALSE;
//	UnHighLight(m_idArrHighLight);
	m_idArrHighLight.removeAll();
	AcDbObjectIdArray idarr=CDwgDatabaseUtil::GetAllEntityIds();
	int iNum = idarr.length();
	AcGePoint3d pt1 = AcGePoint3d::kOrigin, pt2 = AcGePoint3d::kOrigin;
	CString sWzdm1, sWzdm2;//����pt1 pt2��Ӧ�����ʴ������Ʊ���
	AcDbObjectId idText1, idText2;//�洢�ҵ�������id
	AcDbObjectId idBlock1, idBlock2;//���ڴ洢�����ҵ��Ŀ��id
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
		if (sTemp==sText&&sView==m_sViewTemp)
		{
			CDwgDatabaseUtil::getXdata(_T("���ʴ���"), sWzdm1, pEnt);
			AcDbText *ptext = static_cast<AcDbText*>(pEnt);
			pt1 = ptext->alignmentPoint();
			idText1 = idTemp;
			m_idArrHighLight.append(idTemp);
		}
		if (sTemp==sText2&&sView==m_sViewTemp)
		{
			CDwgDatabaseUtil::getXdata(_T("���ʴ���"), sWzdm2, pEnt);
			AcDbText *ptext = static_cast<AcDbText*>(pEnt);
			pt2 = ptext->alignmentPoint();
			idText2 = idTemp;
			m_idArrHighLight.append(idTemp);
		}
		pEnt->close();
	}
	if (pt1==AcGePoint3d::kOrigin&&pt2==AcGePoint3d::kOrigin)
	{
		CString sPrompt =_T("��ǰ��ͼ")+ sText + _T(",") + sText2 + _T("δ�ҵ���Ϣ.");
		AfxMessageBox(sPrompt);
		b = FALSE;
	}
	else if (pt1==AcGePoint3d::kOrigin)
	{
		CString sPrompt = _T("��ǰ��ͼ") + sText + _T("δ�ҵ���Ϣ.");
		AfxMessageBox(sPrompt);
		b = FALSE;
	}
	else if (pt2 == AcGePoint3d::kOrigin)
	{
		CString sPrompt = _T("��ǰ��ͼ") + sText2 + _T("δ�ҵ���Ϣ.");
		AfxMessageBox(sPrompt);
		b = FALSE;
	}
	else
	{
		if (sWzdm1==_T(""))
		{
			idBlock1 = idText1;
		}
		else
		{
			idBlock1 = GetBlockIdForText(pt1, sWzdm1);
		}
		if (sWzdm2==_T(""))
		{
			idBlock2 = idText2;
		}
		else
		{
			idBlock2 = GetBlockIdForText(pt2, sWzdm2);
		}
		

		MoveView(pt1, 20, 20);
		AcDbExtents extTemp = GetBlockRefExten(idBlock1);
		AcDbExtents extTemp2 = GetBlockRefExten(idBlock2);

	    AcDbObjectId idWireTemp=WirePrompt(extTemp);
		AcDbObjectId idWireTemp2 = WirePrompt(extTemp2);

		HighLight(m_idArrHighLight);
		AcDbObjectId polyId;
		b = AddPoly(sRowNum,sText,sText2,m_sViewTemp,pt2,polyId);
		if (b)
		{
			bCreat = CheckPolylineInExtens(extTemp, extTemp2, polyId);
			if (!bCreat)
			{
				AfxMessageBox(_T("���������δ���ں�ɫ����."));
			}
		}
		

		DeleteWire(idWireTemp);
		DeleteWire(idWireTemp2);
		UnHighLight(m_idArrHighLight);
	}
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	return bCreat;
}

void CDlgDiscern::CheckInfo()
{
	UpdateData(TRUE);
	CString sTemp=_T("������δ����: ");

	int iItem=m_listInfo.GetItemCount();
	for (int i = 0; i < iItem;i++)
	{
		BOOL b=m_listInfo.GetCheck(i);
		if (!b/*&&m_listInfo.GetItemState(i,LVIS_SELECTED)!=LVIS_SELECTED*/)
		{
			CString sT; sT.Format(_T("%d"), i + 1);
			sTemp = sTemp + _T("��") + sT + _T("��. ");
		}
	}
	AfxMessageBox(sTemp);
	return;
}

BOOL CDlgDiscern::CheckEntity(CString sHcl, CString sDhc, AcGePoint3d &ptCenter)
{
	acDocManager->lockDocument(curDoc());
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds(_T("�����߶�ͼ��"));
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
		if (!pEnt->isKindOf(AcDbPolyline::desc()))
		{
			pEnt->close();
			continue;
		}
		CString sIndex, sEntHcl, sEntDhc,sViewTemp;
		int iIndex=0;
		CDwgDatabaseUtil::getXdata(_T("Index"), sIndex, pEnt);
		CDwgDatabaseUtil::getXdata(_T("Hcl"), sEntHcl, pEnt);
		CDwgDatabaseUtil::getXdata(_T("Dhc"), sEntDhc, pEnt);
		CDwgDatabaseUtil::getXdata(_T("��ͼ"), sViewTemp, pEnt);
		AcDbPolyline *pPoly = static_cast<AcDbPolyline*>(pEnt);
		pPoly->getStartPoint(ptCenter);
		pEnt->close();

// 		iIndex = _wtoi(sIndex);
// 		CString sGetHcl = m_listInfo.GetItemText(iIndex, 1);
// 		CString sGetDhc = m_listInfo.GetItemText(iIndex, 2);
		if (sHcl == sEntHcl&&sDhc == sEntDhc&&sViewTemp==m_sViewTemp)
		{
			acDocManager->unlockDocument(curDoc());
			return FALSE;
		}
	}
	acDocManager->unlockDocument(curDoc());
	return TRUE;
}

void CDlgDiscern::CheckAndRefreshList()
{
	m_vecLjxxinfo.clear();
	int iItem = m_listInfo.GetItemCount();
	for (int i = 0; i < iItem;i++)
	{
		m_listInfo.SetCheck(i, FALSE);
		ListLjxxinfo temp;
		temp.check = FALSE;
		temp.hcl = m_listInfo.GetItemText(i, 1);
		temp.dhc = m_listInfo.GetItemText(i, 2);
		m_vecLjxxinfo.push_back(temp);
	}
	acDocManager->lockDocument(curDoc());
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds(_T("�����߶�ͼ��"));
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
		if (!pEnt->isKindOf(AcDbPolyline::desc()))
		{
			pEnt->close();
			continue;
		}
		CString sIndex, sHcl, sDhc,sView;
		int iIndex;
		CDwgDatabaseUtil::getXdata(_T("Index"), sIndex, pEnt);
		CDwgDatabaseUtil::getXdata(_T("Hcl"), sHcl, pEnt);
		CDwgDatabaseUtil::getXdata(_T("Dhc"), sDhc, pEnt);
		CDwgDatabaseUtil::getXdata(_T("��ͼ"), sView, pEnt);
		pEnt->close();

		iIndex = _wtoi(sIndex);
		iIndex--;
		CString sGetHcl =m_listInfo.GetItemText(iIndex, 1);
		CString sGetDhc = m_listInfo.GetItemText(iIndex, 2);
		if (sHcl==sGetHcl&&sDhc==sGetDhc&&sView==m_sViewTemp)
		{
			m_listInfo.SetCheck(iIndex, TRUE);
			m_vecLjxxinfo[i].check = TRUE;
		}
	}
	acDocManager->unlockDocument(curDoc());
	return;
}

AcDbObjectId CDlgDiscern::GetBlockIdForText(AcGePoint3d ptTextInsert, CString sWzdm)
{
	AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
	for (int i = 0; i < idArr.length();i++)
	{
		AcDbObjectId idTemp = idArr[i];
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es;
		es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForRead);
		if (es!=eOk)
		{
			continue;
		}
		if (!pEnt->isKindOf(AcDbBlockReference::desc()))
		{
			pEnt->close();
			continue;
		}
		AcDbBlockReference* pRef = static_cast<AcDbBlockReference*>(pEnt);
//		double dx, dy;
//		AcGePoint3d ptPos=GetBlcokRefCenter(pRef, dx, dy);
		AcDbExtents extTemp = GetBlockRefExten(pRef, 3);
		if (!PtInExten(ptTextInsert,extTemp))
		{
			pRef->close();
			continue;
		}
// 		double dLen = ptPos.distanceTo(ptTextInsert);
// 		if (dLen>10)
// 		{
// 			pRef->close();
// 			continue;
// 		}
		AcDbObjectId idBlockTabRec;
		idBlockTabRec = pRef->blockTableRecord();
		AcDbBlockTableRecord *pRec = NULL;
		es = acdbOpenObject(pRec,idBlockTabRec, AcDb::kForRead);
		if (es != eOk)
		{
			pRef->close();
			continue;
		}
		ACHAR* nameTemp; CString sNameTemp;
		pRec->getName(nameTemp);
		sNameTemp.Format(_T("%s"), nameTemp);
		pRef->close();
		pRec->close();
		if (/*sNameTemp==sWzdm*/Compare2String(sNameTemp,sWzdm))
		{
			return idTemp;
		}

	}
	acutPrintf(_T("\n�˶�λ�Ÿ���û�д������ʴ���ͼ��."));
	return AcDbObjectId::kNull;
}

BOOL CDlgDiscern::CheckPolylineInExtens(AcDbExtents ext1, AcDbExtents ext2, AcDbObjectId idPolyline)
{
	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es;
	es = acdbOpenAcDbEntity(pEnt, idPolyline, AcDb::kForWrite);
	if (es!=eOk)
	{
		return FALSE;
	}
	AcDbPolyline *pPoly = static_cast<AcDbPolyline*>(pEnt);
	AcGePoint3d ptStr, ptEnd;
	pPoly->getStartPoint(ptStr);
	pPoly->getEndPoint(ptEnd);
	if (CheckPtInRect(ptStr,ext1)||CheckPtInRect(ptStr,ext2))
	{
		if (CheckPtInRect(ptEnd,ext1)||CheckPtInRect(ptEnd,ext2))
		{
			pPoly->close();
			return TRUE;
		}
		else
		{
			pPoly->erase();
			pPoly->close();
			return FALSE;
		}
	}
	else
	{
		pPoly->erase();
		pPoly->close();
		return FALSE;
	}
	return FALSE;
}

bool CDlgDiscern::RestoreList()
{
	int iLen = m_vecLjxxinfo.size();
	if (iLen == 0)
	{
		if (m_bShowPrompt)
		{
			AfxMessageBox(_T("����������Ϣȷ��׼ȷ�Ժ��ٽ���ɸѡ"));
		}	
		return false;
	}
	for (int i = 0; i < m_listInfo.GetItemCount(); i++)
	{
		CString sItemp = m_listInfo.GetItemText(i, 0);
		int iTemp = _wtoi(sItemp);
		m_vecLjxxinfo[iTemp - 1].check = m_listInfo.GetCheck(i);
	}
	m_listInfo.DeleteAllItems();
	for (int i = 0; i < iLen; i++)
	{
		CString sI;
		sI.Format(_T("%d"), i + 1);

		int nRow = m_listInfo.InsertItem(i, _T(""));
		m_listInfo.SetItemText(nRow, 0, sI);
		m_listInfo.SetItemText(nRow, 1, m_vecLjxxinfo[i].hcl);
		m_listInfo.SetItemText(nRow, 2, m_vecLjxxinfo[i].dhc);
		m_listInfo.SetCheck(nRow, m_vecLjxxinfo[i].check);
	}
	UpdateData(FALSE);
	return true;
}

void CDlgDiscern::SearchInfo(CString Searchstr)
{
	for (int i = m_listInfo.GetItemCount(); i >= 0;i--)
	{
		CString sName = m_listInfo.GetItemText(i, 1);
		CString sWzdm=m_listInfo.GetItemText(i,2);
		int iCount = sName.Find(Searchstr);
		int iCount2=sWzdm.Find(Searchstr);
		if (iCount==-1&&iCount2==-1)
		{
			m_listInfo.DeleteItem(i);
		}
	}
	UpdateData(FALSE);
}

void CDlgDiscern::SetView(bool bCheck)
{
	bool b=RestoreList();
	if (b)
	{
		int iItem = m_listInfo.GetItemCount();
		for (int i = iItem - 1; i >= 0; i--)
		{
			bool b = m_listInfo.GetCheck(i);
			if (b != bCheck)
			{
				m_listInfo.DeleteItem(i);
			}
		}
	}	
	return;
}

CString CDlgDiscern::RemoveQh(CString sValue)
{
	for (int i = 0; i < m_vecWeihao.size();i++)
	{
		CString sWh = m_vecWeihao[i];
		if (sWh==sValue)
		{
			return sWh;
		}
		int iCount = sValue.Find(sWh);
		if (iCount==0)
		{
			CString s2 = sValue.Mid(iCount+sWh.GetLength(), 1);
			CString s3 = s2.SpanIncluding(_T("0123456789:"));
			if (s2 != s3)
			{
				return sWh;
			}
		}
	}
	return sValue;
}

CString CDlgDiscern::RemoveMk(CString sValue)
{
	
	for (int i = 0; i < m_vecWeihao.size(); i++)
	{
		CString sWh = m_vecWeihao[i];
		CString sTemp = sWh;
		if (sWh.GetLength()<3)
		{
			continue;
		}
		if (sWh[0] == 'A' || sWh[0] == 'B' || sWh[0] == 'C' || sWh[0] == 'D' || sWh[0] == 'E')
		{
			if (sWh[1]!='0')
			{
				sTemp.Insert(1, _T("0X"));
				if (sTemp==sValue)
				{
					return sWh;
				}
				int iCount = sValue.Find(sTemp);
				if (iCount == 0)
				{
					CString s2 = sValue.Mid(iCount+sTemp.GetLength(), 1);
					CString s3 = s2.SpanIncluding(_T("0123456789:"));
					if (s2 != s3)
					{
						sValue.Replace(sTemp,sWh);
						return sValue;
					}
				}
			}
			else
			{
// 				if (sTemp==sValue)
// 				{
// 					return sWh;
// 				}
// 				int iCount = sValue.Find(sTemp);
// 				if (iCount == 0)
// 				{
// 					CString s2 = sValue.Mid(iCount + sTemp.GetLength(), 1);
// 					CString s3 = s2.SpanIncluding(_T("0123456789:"));
// 					if (s2 != s3)
// 					{
// 						sValue.Replace(sTemp, sWh);
// 						return sValue;
// 					}
// 				}
			}
		}
		
	}
	return sValue;
}

void CDlgDiscern::OnNMDblclkListInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_listInfo.ScreenToClient(&point);

	LVHITTESTINFO   lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	UINT nFlag;
	int nItem2 = m_listInfo.HitTest(point, &nFlag);
	if (nFlag == LVHT_ONITEMSTATEICON)
	{
		BOOL b = m_listInfo.GetCheck(nItem2);
		m_listInfo.SetCheck(nItem2, !b);
		*pResult = 0;
		return;
	}

	int nItem = m_listInfo.SubItemHitTest(&lvinfo);
	this->GetParent()->GetDlgItemText(IDC_CMB_VIEW, m_sViewTemp);
	if (nItem != -1)
	{
		CString sRowNum,sHcl, sDhc;
		sRowNum = m_listInfo.GetItemText(nItem, 0);
		sHcl=m_listInfo.GetItemText(nItem, 1);
		sDhc=m_listInfo.GetItemText(nItem, 2);

		AcGePoint3d ptCenter;
		BOOL bCheckEntity=CheckEntity(sHcl, sDhc,ptCenter);
		if (!bCheckEntity)
		{
			AfxMessageBox(_T("��ǰ�����Ѵ�������,Ҫ�����ɾ������"));
			MoveView(ptCenter, 20, 20);
		}
		else
		{
			BOOL b = HighLightText(sRowNum, sHcl, sDhc);
			if (b)
			{
				m_listInfo.SetCheck(nItem);
			}
		}	
	}
	*pResult = 0;
}

void CDlgDiscern::OnNMClickListInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
// 	DWORD dwPos = GetMessagePos();
// 	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
// 	m_listInfo.ScreenToClient(&point);
// 
// 	LVHITTESTINFO   lvinfo;
// 	lvinfo.pt = point;
// 	lvinfo.flags = LVHT_ABOVE;
// 
// 	UINT nFlag;
// 	int nItem = m_listInfo.HitTest(point, &nFlag);
// 	
// 	if (nFlag == LVHT_ONITEMSTATEICON)
// 	{
// 		BOOL b = m_listInfo.GetCheck(nItem);
// 		if (b==FALSE)
// 		{
// 			m_listInfo.SetCheck(nItem);
// 		}
// 		else
// 		{
// 			m_listInfo.SetCheck(nItem, FALSE);
// 		}			
// 	}	
	*pResult = 0;
}

void CDlgDiscern::OnLvnItemchangedListInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_listInfo.ScreenToClient(&point);

	LVHITTESTINFO   lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	UINT nFlag;
	int nItem = m_listInfo.HitTest(point, &nFlag);

	if (nFlag == LVHT_ONITEMSTATEICON)
	{
		m_listInfo.SetCheck(nItem, FALSE);		
	}
	*pResult = 0;
}


BOOL CDlgDiscern::PreTranslateMessage(MSG* pMsg)
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
