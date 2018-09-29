#include "StdAfx.h"
#include "Tools.h"
#include "MathUtil.h"


bool GetSelection(AcDbObjectIdArray& adoia, CString sPrompt)
{
	// Check the pickfirst
	adoia.removeAll();
	ads_name anSs;
	if (acedSSGet(_T("I"), NULL, NULL, NULL, anSs) == RTNORM)
	{
		// Get objects
		GetObjectIdArray(anSs, adoia);
		if (adoia.length() > 0)
		{
			// Clear pickfirst
			int ret = acedSSSetFirst(NULL, NULL);
			return true;
		}
	}

	TCHAR*   pcaStringPointers[2];
	TCHAR    caPromptSelecting[2048],
		caPromptRemoving[2048];
	int      iReturn;

	// Intialization. Empty the selectionset. Very important
	ads_ssadd(NULL, NULL, anSs);

	if (!sPrompt.IsEmpty()) {
		// Copy prompt strings to TCHAR array
		_tcscpy(caPromptSelecting, sPrompt);
		_tcscpy(caPromptRemoving, sPrompt);

		// Set the address pointers for in the array to give as parameter
		pcaStringPointers[0] = caPromptSelecting;
		pcaStringPointers[1] = caPromptRemoving;

		// Start selection
		iReturn = acedSSGet(_T(":$"), pcaStringPointers, NULL, NULL, anSs);

		// User pressed escape
		if (iReturn == RTCAN)
			return false;
	}
	else {
		// Start selection
		iReturn = acedSSGet(NULL, NULL, NULL, NULL, anSs);
		// User pressed escape
		if (iReturn == RTCAN)
			return false;
	}

	// Convert anSs to adoia
	GetObjectIdArray(anSs, adoia);

	return true;
}

bool GetObjectIdArray(ads_name anSs, AcDbObjectIdArray& adoiaObjects)
{
	long         lLength = 0L;
	ads_name     anObject;
	AcDbObjectId adoiObject;

	// Empty the idarray
	adoiaObjects.removeAll();

	// Get length of idarray
	ads_sslength(anSs, &lLength);

	// For every objectid
	for (int i = 0; i < lLength; i++) {
		// Get objectid from idarray
		ads_ssname(anSs, i, anObject);

		// Convert objectid to AcDbObjectId
		if (acdbGetObjectId(adoiObject, anObject) != Acad::eOk) {
			return false;
		}

		// Check if AcDbObjectId is valid
		if (!adoiObject.isValid()) {
			return false;
		}

		// Append to objectid array
		adoiaObjects.append(adoiObject);
	}

	return true;
}

CString GetDwgPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\template.dwg");
	return sPath;
}

CString GetMenuPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\GR.mns");
	return sPath;
}

CString GetDocPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\test.docx");
	return sPath;
}

CString GetIniPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\DwgDesign.ini");
	return sPath;
}

CString GetTextIniPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\config.ini");
	return sPath;
}

CString GetWebexePath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\WEB\\WebofAutoCAD.exe");
	return sPath;
}

CString GetXmlPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\Design.xml");
	return sPath;
}

CString GetFolderPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\Project");
	return sPath;
}

CString GetBatchDesignFoldPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\excelpath\\");
	return sPath;
}

CString GetExcelLogPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\Log.xlsx");
	return sPath;
}

CString GetWhLogPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\CreatWhLog.xlsx");
	return sPath;
}

CString GetCheckMapPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\CheckMapLog.xlsx");
	return sPath;
}

CString GetExcelDlgxbPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\Dlgxb.xlsx");
	return sPath;
}

CString GetExcelDzbPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\Dzb.xlsx");
	return sPath;
}

CString GetExcelFjmxbPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\fjmkmxb.xlsx");
	return sPath;
}

CString GetLogFolderPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\Log\\");
	return sPath;
}

CString GetExcelFolder()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\");
	return sPath;
}

CString GetBlockLibPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\blocklib.dwg");
	return sPath;
}

std::vector<CString> GetDwgAllBlockName(const TCHAR* sDwgPath)
{
	std::vector<CString> vetAll;
	AcDbDatabase *pDatabase = new AcDbDatabase(Adesk::kFalse);
	Acad::ErrorStatus es;
	es=pDatabase->readDwgFile(sDwgPath, _SH_DENYNO);
	if (es != Acad::eOk)
	{
		delete pDatabase;
		pDatabase = NULL;
		return vetAll;
	}
	AcDbBlockTable *pTab = NULL;
	es=pDatabase->getBlockTable(pTab, AcDb::kForRead);
	if (es != Acad::eOk)
	{
		delete pDatabase;
		pDatabase = NULL;
		return vetAll;
	}
	AcDbBlockTableIterator *pItr = NULL;
	pTab->newIterator(pItr);
	for (pItr->start();!pItr->done();pItr->step())
	{
		AcDbBlockTableRecord *pRec = NULL;
		Acad::ErrorStatus es=pItr->getRecord(pRec, AcDb::kForWrite);
		if (es==Acad::eOk)
		{
			CString sTemp;
			ACHAR *sName;
			pRec->getName(sName);
			sTemp.Format(_T("%s"), sName);
			if (sTemp != ACDB_MODEL_SPACE&&sTemp != ACDB_PAPER_SPACE&&sTemp != _T("*Paper_Space0"))
			{
				vetAll.push_back(sTemp);
			}
			
			pRec->close();
		}
		else
		{
			continue;
		}
	}
	delete pItr;
	pTab->close();
	delete pDatabase;
	pDatabase = NULL;
	return vetAll;
}

CString GetConnectionString()
{
	CString mdbFile = CAppDirectoryUtil::GetParentDirectory() + TEXT("\\Support\\Xylem.mdb");
	return _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=") + mdbFile;
}

BOOL FillCombo(CAcUiComboBox &cmbTemp, CString sTemp,CString sSplit /*= _T(",")*/)
{
	cmbTemp.Clear();
	std::vector<CString> vecStr;
	CStringUtil::Split(sTemp,sSplit, vecStr, false);
	size_t iLen = vecStr.size();
	for (int i = 0; i < iLen;i++)
	{
		CString s = vecStr[i];
		cmbTemp.AddString(s);
	}
	cmbTemp.SetCurSel(0);
	return TRUE;
}

BOOL CopeDwgToFolder(CString sSourcePath, CString sExportPath)
{
	AcDbDatabase *pData = new AcDbDatabase(false);
	//pData->readDwgFile()
	return TRUE;
}

BOOL CreatFolder(CString sFolderpath)
{
	if (!PathIsDirectory(sFolderpath))
	{
		::CreateDirectory(sFolderpath, NULL);
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

void HighLight(AcDbObjectIdArray idArr)
{
	int iNum = idArr.length();
	for (int i = 0; i < iNum; i++)
	{
		AcDbObjectId idTemp = idArr[i];
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es;
		es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
		if (es != eOk)
		{
			continue;
		}
		pEnt->highlight();
		pEnt->close();
	}
}

void UnHighLight(AcDbObjectIdArray idArr)
{
	int iNum = idArr.length();
	for (int i = 0; i < iNum; i++)
	{
		AcDbObjectId idTemp = idArr[i];
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es;
		es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
		if (es != eOk)
		{
			continue;
		}
		pEnt->unhighlight();
		pEnt->close();
	}
}

ads_real GetWidth()
{
	ads_real width = 0;
	if (acedGetReal(_T("\n输入线宽："), &width) == RTNORM)
	{
		return width;
	}
	else
	{
		return 0;
	}
}

int GetColorIndex()
{
	int colorIndex = 0;
	if (acedGetInt(_T("输入颜色索引值(0~256)："), &colorIndex) != RTNORM)
	{
		return 0;
	}

	while (colorIndex < 0 || colorIndex >256)
	{
		acedPrompt(_T("输入了错误的颜色索引值！"));
		if (acedGetInt(_T("输入颜色索引值(0~256)"), &colorIndex) != RTNORM)
		{
			return 0;
		}
	}

	return colorIndex;
}

BOOL AddPoly(CString sIndex, CString sHcl, CString sDhc,CString sView, AcGePoint3d ptEnd,AcDbObjectId &polyId)
{
	polyId = AcDbObjectId::kNull;
	CLayerUtil::Add(_T("连接线段图层"));
	AcDbObjectId idLayer = CLayerUtil::GetLayerId(_T("连接线段图层"));

	BOOL b = FALSE;

	int colorIndex = 0;
	ads_real width = 0;

	int index = 2;
	ads_point ptStart;

	if (acedGetPoint(NULL, _T("\n输入第一点:"), ptStart) != RTNORM)
		return b;
	MoveView(ptEnd, 20, 20);
	ads_point ptPrevious, ptCurrent;
	acdbPointSet(ptStart, ptPrevious);

	acedInitGet(NULL, _T("W C O"));
	int rc = acedGetPoint(ptPrevious,
		_T("\n输入下一点[宽度(W)/颜色(C)]<完成(O)>"), ptCurrent);
	while (rc == RTNORM || rc == RTKWORD)
	{
		if (rc == RTKWORD)
		{
			ACHAR kword[20];
			if (acedGetInput(kword) != RTNORM)
				return FALSE;
			if (strcmp((LPSTR)(LPCTSTR)kword, "W") == 0)
			{
				width = GetWidth();
			}
			else if (strcmp((LPSTR)(LPCTSTR)kword, "C") == 0)
			{
				colorIndex = GetColorIndex();
			}
			else if (strcmp((LPSTR)(LPCTSTR)kword, "O") == 0)
			{
				return b;
			}
			else
			{
				acutPrintf(_T("\n无效的关键字"));
			}
		}
		else if (rc == RTNORM)
		{
			if (index == 2)
			{
				AcDbPolyline *pPoly = new AcDbPolyline(2);
				AcGePoint2d ptGe1, ptGe2;
				ptGe1[X] = ptPrevious[X];
				ptGe1[Y] = ptPrevious[Y];
				ptGe2[X] = ptCurrent[X];
				ptGe2[Y] = ptCurrent[Y];
				pPoly->addVertexAt(0, ptGe1);
				pPoly->addVertexAt(1, ptGe2);

				pPoly->setConstantWidth(width);
				pPoly->setColorIndex(colorIndex);

				AcDbBlockTable *pBlkTbl;
				acdbHostApplicationServices()->workingDatabase()
					->getSymbolTable(pBlkTbl, AcDb::kForRead);

				AcDbBlockTableRecord *pBlkTblRcd;
				pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForWrite);

				CDwgDatabaseUtil::SetXdata(_T("Index"), sIndex, pPoly);
				CDwgDatabaseUtil::SetXdata(_T("Hcl"), sHcl, pPoly);
				CDwgDatabaseUtil::SetXdata(_T("Dhc"), sDhc, pPoly);
				CDwgDatabaseUtil::SetXdata(_T("视图"), sView, pPoly);
				pPoly->setLayer(idLayer);

				pBlkTblRcd->appendAcDbEntity(polyId, pPoly);
				b = TRUE;
				pBlkTblRcd->close();
				pBlkTbl->close();
				pPoly->close();

			}
			else if (index > 2)
			{
				AcDbPolyline *pPoly;
				acdbOpenObject(pPoly, polyId, AcDb::kForWrite);

				AcGePoint2d ptGe;
				ptGe[X] = ptCurrent[X];
				ptGe[Y] = ptCurrent[Y];

				pPoly->addVertexAt(index - 1, ptGe);
				pPoly->setConstantWidth(width);
				pPoly->setColorIndex(colorIndex);

				pPoly->close();
				b = TRUE;
			}
			index++;

			acdbPointSet(ptCurrent, ptPrevious);
		}

		acedInitGet(NULL, _T("W C O"));
		rc = acedGetPoint(ptPrevious,
			_T("\n输入下一点[宽度(W)/颜色(C)]<完成(O)>"), ptCurrent);
	}
	return b;
}

BOOL AddPoly(AcGePoint3d ptStr,AcGePoint3d ptEnd, AcDbObjectId &polyId)
{
	polyId = AcDbObjectId::kNull;

	BOOL b = FALSE;

	int colorIndex = 0;
	ads_real width = 0;

	int index = 2;
	ads_point ptStart;
	MoveView(ptStr, 20, 20);
	if (acedGetPoint(NULL, _T("\n输入第一点:"), ptStart) != RTNORM)
		return b;
	MoveView(ptEnd, 20, 20);
	ads_point ptPrevious, ptCurrent;
	acdbPointSet(ptStart, ptPrevious);

	acedInitGet(NULL, _T("W C O"));
	int rc = acedGetPoint(ptPrevious,
		_T("\n输入下一点[宽度(W)/颜色(C)]<完成(O)>"), ptCurrent);
	while (rc == RTNORM || rc == RTKWORD)
	{
		if (rc == RTKWORD)
		{
			ACHAR kword[20];
			if (acedGetInput(kword) != RTNORM)
				return FALSE;
			if (strcmp((LPSTR)(LPCTSTR)kword, "W") == 0)
			{
				width = GetWidth();
			}
			else if (strcmp((LPSTR)(LPCTSTR)kword, "C") == 0)
			{
				colorIndex = GetColorIndex();
			}
			else if (strcmp((LPSTR)(LPCTSTR)kword, "O") == 0)
			{
				return b;
			}
			else
			{
				acutPrintf(_T("\n无效的关键字"));
			}
		}
		else if (rc == RTNORM)
		{
			if (index == 2)
			{
				AcDbPolyline *pPoly = new AcDbPolyline(2);
				AcGePoint2d ptGe1, ptGe2;
				ptGe1[X] = ptPrevious[X];
				ptGe1[Y] = ptPrevious[Y];
				ptGe2[X] = ptCurrent[X];
				ptGe2[Y] = ptCurrent[Y];
				pPoly->addVertexAt(0, ptGe1);
				pPoly->addVertexAt(1, ptGe2);

				pPoly->setConstantWidth(width);
				pPoly->setColorIndex(colorIndex);

				AcDbBlockTable *pBlkTbl;
				acdbHostApplicationServices()->workingDatabase()
					->getSymbolTable(pBlkTbl, AcDb::kForRead);

				AcDbBlockTableRecord *pBlkTblRcd;
				pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForWrite);

				pBlkTblRcd->appendAcDbEntity(polyId, pPoly);
				b = TRUE;
				pBlkTblRcd->close();
				pBlkTbl->close();
				pPoly->close();

			}
			else if (index > 2)
			{
				AcDbPolyline *pPoly;
				acdbOpenObject(pPoly, polyId, AcDb::kForWrite);

				AcGePoint2d ptGe;
				ptGe[X] = ptCurrent[X];
				ptGe[Y] = ptCurrent[Y];

				pPoly->addVertexAt(index - 1, ptGe);
				pPoly->setConstantWidth(width);
				pPoly->setColorIndex(colorIndex);

				pPoly->close();
				b = TRUE;
			}
			index++;

			acdbPointSet(ptCurrent, ptPrevious);
		}

		acedInitGet(NULL, _T("W C O"));
		rc = acedGetPoint(ptPrevious,
			_T("\n输入下一点[宽度(W)/颜色(C)]<完成(O)>"), ptCurrent);
	}
	return b;
}

void MoveView(AcGePoint3d ptCenter, double dHight, double dWidth)
{
	AcDbViewTableRecord view;
	view.setCenterPoint(AcGePoint2d(ptCenter.x, ptCenter.y));
	view.setHeight(dHight);
	view.setWidth(dWidth);
	acedSetCurrentView(&view, NULL);
	acdbHostApplicationServices()->workingDatabase()->updateExt(TRUE);

}

void getFiles(string path, string exd, vector<string>& files)
{
	//文件句柄
	long hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string pathName, exdName;

	if (0 != strcmp(exd.c_str(), ""))
	{
		exdName = "\\*." + exd;
	}
	else
	{
		exdName = "\\*";
	}

	if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是文件夹中仍有文件夹,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(pathName.assign(path).append("\\").append(fileinfo.name), exd, files);
			}
			else
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void FillCombo(CString sFolderPath, string exd, CAcUiComboBox &cmbTemp)
{
	cmbTemp.Clear();
	string sPath = (LPCSTR)(CStringA)sFolderPath;
	std::vector<string> vecFile;
	getFiles(sPath, exd, vecFile);
	int iLen = vecFile.size();
	for (int i = 0;i < iLen;i++)
	{
		string sTemp = vecFile[i];
		CString sFile = sTemp.c_str();
		int iTemp = sFile.ReverseFind('\\');
		sFile = sFile.Right(sFile.GetLength() - iTemp - 1);
		cmbTemp.AddString(sFile);
	}
}

AcGePoint3d GetBlcokRefCenter(AcDbBlockReference *pRef, double &dx, double &dy)
{
	Acad::ErrorStatus es = pRef->upgradeOpen();
	if (es != eOk)
	{
		return AcGePoint3d::kOrigin;
	}
	AcDbExtents extAll;
	AcDbVoidPtrArray ptarr;
	pRef->explode(ptarr);
	for (int i = 0;i < ptarr.length();i++)
	{
		AcDbEntity *pEnt = static_cast<AcDbEntity*>(ptarr[i]);
		AcDbExtents ext;
		pEnt->getGeomExtents(ext);
		extAll.addExt(ext);
		pEnt->close();
	}
	AcGePoint3d ptMax = extAll.maxPoint();
	AcGePoint3d ptMin = extAll.minPoint();
	dx = ptMax.x - ptMin.x;
	dy = ptMax.y - ptMin.y;
	AcGePoint3d ptRet = AcGePoint3d((ptMax.x + ptMin.x) / 2, (ptMax.y + ptMin.y) / 2, 0);
	return ptRet;
}

AcGePoint3d GetBlockRefCenterTop(AcDbBlockReference*pRef, double &dx, double &dy)
{
	Acad::ErrorStatus es = pRef->upgradeOpen();
	if (es != eOk)
	{
		return AcGePoint3d::kOrigin;
	}
	AcDbExtents extAll;
	AcDbVoidPtrArray ptarr;
	pRef->explode(ptarr);
	for (int i = 0; i < ptarr.length(); i++)
	{
		AcDbEntity *pEnt = static_cast<AcDbEntity*>(ptarr[i]);
		AcDbExtents ext;
		pEnt->getGeomExtents(ext);
		extAll.addExt(ext);
		pEnt->close();
	}
	AcGePoint3d ptMax = extAll.maxPoint();
	AcGePoint3d ptMin = extAll.minPoint();
	dx = ptMax.x - ptMin.x;
	dy = ptMax.y - ptMin.y;
	AcGePoint3d ptCenterTop = AcGePoint3d((ptMax.x + ptMin.x) / 2, ptMax.y, ptMax.z);
	return ptCenterTop;
}

AcDbExtents GetBlockRefExten(AcDbObjectId idBlock,double dEnlarge/*=0*/)
{
	AcDbExtents extAll;
	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es;
	es = acdbOpenAcDbEntity(pEnt, idBlock, AcDb::kForWrite);
	if (es!=eOk)
	{
		return extAll;
	}
	if (!pEnt->isKindOf(AcDbBlockReference::desc()))
	{
		if (pEnt->isKindOf(AcDbText::desc()))
		{
			pEnt->getGeomExtents(extAll);
		}
		pEnt->close();
		return extAll;
	}
	AcDbBlockReference *pRef = static_cast<AcDbBlockReference*>(pEnt);
	AcDbVoidPtrArray ptarr;
	pRef->explode(ptarr);
	for (int i = 0; i < ptarr.length(); i++)
	{
		AcDbEntity *pEnt = static_cast<AcDbEntity*>(ptarr[i]);
		AcDbExtents ext;
		pEnt->getGeomExtents(ext);
		extAll.addExt(ext);
		pEnt->close();
	}
	pRef->close();
	if (dEnlarge>0)
	{
		AcGePoint3d ptMax, ptMin;
		ptMax = extAll.maxPoint();
		ptMin = extAll.minPoint();
		extAll.addPoint(AcGePoint3d(ptMax.x + dEnlarge, ptMax.y + dEnlarge, 0));
		extAll.addPoint(AcGePoint3d(ptMin.x - dEnlarge, ptMin.y - dEnlarge, 0));
	}
	return extAll;
}

AcDbExtents GetBlockRefExten(AcDbBlockReference*pRef, double dLen)
{
	AcDbExtents extAll;
	AcDbVoidPtrArray ptarr;
	pRef->explode(ptarr);
	for (int i = 0; i < ptarr.length(); i++)
	{
		AcDbEntity *pEnt = static_cast<AcDbEntity*>(ptarr[i]);
		AcDbExtents ext;
		pEnt->getGeomExtents(ext);
		extAll.addExt(ext);
		pEnt->close();
	}
	if (dLen > 0)
	{
		AcGePoint3d ptMax, ptMin;
		ptMax = extAll.maxPoint();
		ptMin = extAll.minPoint();
		extAll.addPoint(AcGePoint3d(ptMax.x + dLen, ptMax.y + dLen, 0));
		extAll.addPoint(AcGePoint3d(ptMin.x - dLen, ptMin.y - dLen, 0));
	}
	return extAll;
}

bool PtInExten(AcGePoint3d pt, AcDbExtents ext)
{
	AcGePoint3d ptMax, ptMin;
	ptMax = ext.maxPoint();
	ptMin = ext.minPoint();
	if (pt.x>=ptMin.x&&pt.x<=ptMax.x&&pt.y>=ptMin.y&&pt.y<=ptMax.y)
	{
		return true;
	}
	return false;
}

AcDbObjectId WirePrompt(AcDbExtents ext)
{
	AcGePoint3d ptMax, ptMin;
	ptMax = ext.maxPoint();
	ptMin = ext.minPoint();
	AcDbPolyline *pLine = new AcDbPolyline();
	pLine->addVertexAt(0, AcGePoint2d(ptMin.x, ptMin.y));
	pLine->addVertexAt(1, AcGePoint2d(ptMax.x, ptMin.y));
	pLine->addVertexAt(2, AcGePoint2d(ptMax.x, ptMax.y));
	pLine->addVertexAt(3, AcGePoint2d(ptMin.x, ptMax.y));
	pLine->addVertexAt(4, AcGePoint2d(ptMin.x, ptMin.y));
	pLine->setColorIndex(1);
	return CDwgDatabaseUtil::PostToModelSpace(pLine);
}

AcDbObjectId WirePrompt(AcGePoint3d ptCirCenter, double dRadius)
{
	AcDbCircle *pCir = new AcDbCircle(ptCirCenter, AcGeVector3d(0, 0, 1), dRadius);
	pCir->setColorIndex(1);
	return CDwgDatabaseUtil::PostToModelSpace(pCir);
}

bool DeleteWire(AcDbObjectId idTemp)
{
	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es;
	es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
	if (es!=eOk)
	{
		return false;
	}
	pEnt->erase();
	pEnt->close();
	return true;
}

bool CheckPtInRect(AcGePoint3d pt, AcDbExtents ext)
{
	double dX, dY,Minx,Miny,Maxx,Maxy;
	dX = pt.x;
	dY = pt.y;
	Minx = ext.minPoint().x;
	Miny = ext.minPoint().y;
	Maxx = ext.maxPoint().x;
	Maxy = ext.maxPoint().y;
	if (dX>Minx&&dX<Maxx&&dY>Miny&&dY<Maxy)
	{
		return true;
	}
	return false;
}

CString GetTimer()
{
	CTime t = CTime::GetCurrentTime();
	int nYear = t.GetYear() - 2000;
	int nMonth = t.GetMonth();
	int nDay = t.GetDay();
	int nTime = t.GetHour();
	int nMin = t.GetMinute();
	int nSec = t.GetSecond();

	CString str;
	str.Format(_T("%2d%2d%2d%2d%2d%2d"), nYear, nMonth, nDay, nTime, nMin, nSec);
	str.Replace(_T(' '), _T('0'));
	return str;
}

CString GetTimer2()
{
	CTime t = CTime::GetCurrentTime();
	int nYear = t.GetYear();
	int nMonth = t.GetMonth();
	int nDay = t.GetDay();

	CString str;
	str.Format(_T("%4d-%2d-%2d"), nYear, nMonth, nDay);
	str.Replace(_T(' '), _T('0'));
	return str;
}

BOOL CheckExcelPath(CString sExcelPath)
{
	CString sExt1,sExt2;
	sExt1=sExcelPath.Right(4);
	sExt2 = sExcelPath.Right(3);
	if (sExt1!=_T("xlsx")&&sExt2!=_T("xls"))
	{
		return FALSE;
	}
	fstream _file;
	_file.open(sExcelPath,ios::in);
	if (!_file)
	{
		return FALSE;
	}
	else
	{
		_file.close();
		return TRUE;
	}
}

double OpenObjAndGetLength(AcDbObjectId objId)
{
	double dWidth = 0.0;
	if (objId.isNull())
	{
		return dWidth;
	}
	AcDbExtents exts;
	AcDbEntity* pEnt = NULL;
	if (acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead) != Acad::eOk)
	{
		return dWidth;
	}
	pEnt->getGeomExtents(exts);
	pEnt->close();
	dWidth = abs(exts.minPoint().x - exts.maxPoint().x);
	double dTmp = abs(exts.minPoint().y - exts.maxPoint().y);
	if (dWidth > dTmp)
	{
		return dWidth;
	}
	else
	{
		return dTmp;
	}
}

void SetDataBaseXdata(CString appname, CString value)
{
	Acad::ErrorStatus es;
	AcDbBlockTable *pTab = NULL;
	es=acdbHostApplicationServices()->workingDatabase()->getBlockTable(pTab, AcDb::kForRead);
	if (es!=eOk)
	{
		return;
	}
	AcDbBlockTableRecord *pRec = NULL;
	es=pTab->getAt(ACDB_MODEL_SPACE, pRec, AcDb::kForWrite);
	if (es!=eOk)
	{
		pTab->close();
		return;
	}
	pTab->close();
	acdbRegApp(appname);
	struct resbuf*rb = acutBuildList(AcDb::kDxfRegAppName, appname, AcDb::kDxfXdAsciiString, value, RTNONE);
	pRec->setXData(rb);
	acutRelRb(rb);
	pRec->close();
}

void GetDataBaseXdata(CString appname, CString &value)
{
	Acad::ErrorStatus es;
	AcDbBlockTable *pTab = NULL;
	es=acdbHostApplicationServices()->workingDatabase()->getBlockTable(pTab, AcDb::kForRead);
	if (es!=eOk)
	{
		return;
	}
	AcDbBlockTableRecord *pRec = NULL;
	es=pTab->getAt(ACDB_MODEL_SPACE, pRec, AcDb::kForWrite);
	if (es!=eOk)
	{
		pTab->close();
		return;
	}
	pTab->close();
	struct resbuf *pRb = pRec->xData(appname);
	if (pRb)
	{
		struct resbuf *pTemp = pRb;
		pTemp = pTemp->rbnext;
		while (pTemp)
		{
			if (AcDb::kDxfXdAsciiString==pTemp->restype)
			{
				value = pTemp->resval.rstring;
				acutRelRb(pRb);
				pRec->close();
				return;
			}
			pTemp = pTemp->rbnext;
		}
	}
	acutRelRb(pRb);
	pRec->close();
	return;
}

CString ConvertString(CString str)
{
	int n1 = str.Find(_T("("));
	int n2 = str.Find(_T(")"));
	int n3 = str.Find(_T("（"));
	int n4 = str.Find(_T("）"));
	int n5 = str.Find(_T("["));
	int n6 = str.Find(_T("]"));
	if (n1 != -1 && n2 != -1)
	{
		str.Delete(n1, (n2-n1)+1);
		return str;
	}
	else if (n3!=-1&&n4!=-1)
	{
		str.Delete(n3, (n4-n3)+1);
		return str;
	}
	else if (n5 != -1 && n6 != -1)
	{
		str.Delete(n5, (n6-n5)+1);
		return str;
	}
	else
	{
		return str;
	}
//	CString sRemove = str.Mid(n1, n2);
//	str.TrimRight(sRemove);// trim 使用错误
	
	return str;
}

CString NumberConver(int i)
{
	switch (i)
	{
	case 1:
		return _T("一");
	case 2:
		return _T("二");
	case 3:
		return _T("三");
	case 4:
		return _T("四");
	case 5:
		return _T("五");
	case 6:
		return _T("六");
	case 7:
		return _T("七");
	case 8:
		return _T("八");
	case 9:
		return _T("九");
	case 10:
		return _T("十");
	default:
		break;
	}
	return _T("error");
}

AcDbObjectId AddTableStyle()
{
	AcDbDictionary *pDict = NULL;
	AcDbObjectId idTblStyle;
	acdbHostApplicationServices()->workingDatabase()->getTableStyleDictionary(pDict, AcDb::kForWrite);
	if (!pDict->has(_T("GRTABLE")))
	{
		AcDbTableStyle *pTabStyle = new AcDbTableStyle;
		pTabStyle->suppressHeaderRow(false);
		pDict->setAt(_T("GRTABLE"), pTabStyle, idTblStyle);
		pTabStyle->close();
	}
	else
	{
		pDict->getAt(_T("GRTABLE"), idTblStyle);
	}
	pDict->close();
	return idTblStyle;
}

void LoadDwgEnvironment()
{
	CTextStyleUtil::Add(_T("HZ"), _T("txt.shx"), _T("bigfont.shx"));
// 	CString menupath = GetMenuPath();
// 	acedCommand(RTSTR, _T("menuload"), RTSTR, menupath/*_T("GR")*/, RTNONE);
}

CString EditString(const CString &str)
{
	CString sRet = str;
	sRet=sRet.MakeUpper();
	sRet.Replace(_T("."), _T("_"));
	int i1 = sRet.Find(_T("PRD-TMP"));
	int i2 = sRet.Find(_T("BM"));
	if ( i1!= -1)
	{
		sRet = sRet.Mid(i1);
		int iTemp = sRet.Find(_T("---"));
		if (iTemp!=-1)
		{
			sRet=sRet.Left(iTemp);
		}
		return sRet;
	}
	else if (i2!=-1)
	{	
		sRet = sRet.Mid(i2);
		int iTemp = sRet.Find(_T("---"));
		if (iTemp!=-1)
		{
			sRet = sRet.Left(iTemp);
		}
		return sRet;
	}
	else
	{
		int iTemp=sRet.Find(_T("---"));
		if(iTemp!=-1)
		{
			sRet=sRet.Left(iTemp);
		}
		int iTemp2=sRet.Find(_T("-"));
		if(iTemp2!=-1)
		{
			CString sTag=sRet.SpanIncluding(_T("0123456789-"));
			if(sTag==sRet)
			{
				return sRet;
			}
		}
	}
	return sRet;
}

bool Compare2String(CString s1, CString s2)
{
	s1 = EditString(s1);
	s2 = EditString(s2);
	if (s1==s2)
	{
		return true;
	}
	return false;
// 	int iLen = s1.Find(_T("__"));
// 	if (iLen!=-1)
// 	{
// 		s1 = s1.Left(iLen);
// 	}	
// 	s1.Replace(_T("."), _T("_"));
// 	int iLen2 = s2.Find(_T("__"));
// 	if (iLen2!=-1)
// 	{
// 		s2 = s2.Left(iLen2);
// 	}	
// 	s2.Replace(_T("."), _T("_"));
// 
// 	
// 	if (s1.MakeUpper()==s2.MakeUpper())	
// 	{
// 		return true;
// 	}
// 	else
// 	{
// 		return false;
// 	}
}

bool GetWeihaoAndWzdm(CString sName, CString sMkwzdm, CString sMbwzdm, CString sMkljqmc, CString sMbljqmc, CString sSheetName, CString &weihao, CString &wuzidaima)
{
	int nCount = sSheetName.Find(_T("("));
	int nCount2 = sSheetName.Find(_T(")"));
	CString sSheet1,sSheet2;
	if (nCount!=-1)
	{
		sSheet1= sSheetName.Left(nCount);
	}
	else
	{
		sSheet1 = sSheetName;
	}

	if (sMbwzdm != _T("") && sMbljqmc != _T(""))
	{
		if (sSheet1 == _T("A0") || sSheet1 == _T("B0")|| sSheet1 == _T("C0")|| sSheet1 == _T("D0")|| sSheet1 == _T("E0"))
		{
			weihao = sSheet1 + sName;
			wuzidaima = sMbwzdm;
		}
		else
		{
			weihao = sName;
			wuzidaima = sMbwzdm;
		}
		return true;
	}
	else if (sMbwzdm == _T("") && sMbljqmc == _T("") && sMkljqmc != _T("") && sMkwzdm != _T(""))
	{
		if(sSheet1 == _T("A0") || sSheet1 == _T("B0")||sSheet1 == _T("C0")|| sSheet1 == _T("D0")|| sSheet1 == _T("E0"))
		{
			weihao = sSheet1.Left(1) + sName.Mid(1);
		    wuzidaima = sMkwzdm;
		}
		else
		{
			weihao=sName;
			wuzidaima=sMkwzdm;
		}
		return true;
	}
	else
	{
		if(sSheet1 !=_T("A0") && sSheet1 != _T("B0")&& sSheet1 != _T("C0")
			&& sSheet1 != _T("D0")&& sSheet1 != _T("E0"))
		{
			weihao=sName;
			wuzidaima=sMkwzdm;
		}
		return true;
	}
	return false;
}

CString RemoveQhTest(CString sValue, std::vector<CString> vecWh)
{
	for (int i = 0; i < vecWh.size(); i++)
	{
		CString sWh = vecWh[i];
		if (sWh == sValue)
		{
			return sWh;
		}
		int iCount = sValue.Find(sWh);
		if (iCount != -1)
		{
			CString s2 = sValue.Mid(iCount + sWh.GetLength(), 1);
			CString s3 = s2.SpanIncluding(_T("0123456789:"));
			if (s2 != s3)
			{
				return sWh;
			}
		}
	}
	return sValue;
}

CString RemoveMkTest(CString sValue, std::vector<CString>vecWh)
{
	for (int i = 0; i < vecWh.size(); i++)
	{
		CString sWh = vecWh[i];
		CString sTemp = sWh;
		if (sWh.GetLength() < 3)
		{
			continue;
		}
		if (sWh[0] == 'A' || sWh[0] == 'B' || sWh[0] == 'C' || sWh[0] == 'D' || sWh[0] == 'E')
		{
			if (sWh[1] != '0')
			{
				sTemp.Insert(1, _T("0X"));
				int iCount = sValue.Find(sTemp);
				if (iCount != -1)
				{
					CString s2 = sValue.Mid(iCount+sTemp.GetLength(), 1);
					CString s3 = s2.SpanIncluding(_T("0123456789"));
					if (s2 != s3)
					{
						sValue.Replace(sTemp, sWh);
						return sValue;
					}
				}
			}
		}

	}
	return sValue;
}

bool SelectExcelCell(CString sExcelPath, CString sSheetName, int nRow, int nCol)
{
	cExcel excel;
	if (!excel.StartApp())
	{
		AfxMessageBox(_T("excel打开失败"));
		return false;
	}
	excel.OpenWorkBook(sExcelPath);
	excel.SwitchToSheet(sSheetName);
	excel.ActiveRange(nRow, nCol);
	excel.ShowExcel();
	AcGePoint3d pt;
	int i = 2;
	while (true)
	{
		bool b = CGetInputUtil::GetPoint(_T("aa"), pt);
		if (!b)
		{
			break;
		}
		excel.SwitchToSheet(i);
		excel.ActiveRange(nRow, nCol);
		excel.ShowExcel();
		i++;
	}

	excel.SaveAs(sExcelPath);
	excel.Quit();

	return true;

}

bool GetDwgFrameInfo(FrameInfo &fm)
{
	Acad::ErrorStatus es;
	struct resbuf *rb;
	rb = acutBuildList(1001, TEXT("产品编号"), RTNONE);
	ads_name textArr;
	acedSSGet(TEXT("X"), NULL, NULL, rb, textArr);
	long Lenth;
	acedSSLength(textArr, &Lenth);
	if (Lenth!=1)
	{
		acutRelRb(rb);
		acedSSFree(textArr);
		return false;
	}
	ads_name ent;
	acedSSName(textArr, 0, ent);
	AcDbObjectId objId;
	es=acdbGetObjectId(objId, ent);
	if (es!=eOk)
	{
		acutRelRb(rb);
		acedSSFree(textArr);
		return false;
	}
	AcDbEntity *pEnt = NULL;
	es = acdbOpenAcDbEntity(pEnt, objId, AcDb::kForWrite);
	if (es!=eOk)
	{
		acutRelRb(rb);
		acedSSFree(textArr);
		return false;
	}
	CDwgDatabaseUtil::getXdata(_T("产品编号"), fm.CPBH, pEnt);
	CDwgDatabaseUtil::getXdata(_T("项目等级"), fm.XMDJ, pEnt);
	CDwgDatabaseUtil::getXdata(_T("设计师"), fm.SJS, pEnt);
	CDwgDatabaseUtil::getXdata(_T("项目阶段"), fm.XMJD, pEnt);
	CDwgDatabaseUtil::getXdata(_T("产品名称"), fm.CPMC, pEnt);
	CDwgDatabaseUtil::getXdata(_T("关重件"), fm.GZJ, pEnt);
	pEnt->close();
	acutRelRb(rb);
	acedSSFree(textArr);
	return true;
}

CString GetTextPath()
{
	CString sPath = CAppDirectoryUtil::GetCurrentDirectory();
	sPath = sPath + _T("\\support\\物资库.txt");
	return sPath;
}

std::vector<CString> GetTextVal(CString sTextPath)
{
	std::vector<CString> vecRet;
	ifstream infile;
	infile.open(sTextPath);   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

	string s;
	while (getline(infile, s))
	{
		CString sTemp;
		CA2T szr(s.c_str());
		sTemp = (LPCTSTR)szr;
		vecRet.push_back(sTemp);
	}
	infile.close();
	return vecRet;
}

AcGePoint3d offsetPoint(AcGePoint3d pt, double x, double y)
{
	return AcGePoint3d(pt.x + x, pt.y + y, pt.z);
}

AcDbObjectId MirrorBlock(AcDbObjectId idBlock)
{
	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es;
	es = acdbOpenAcDbEntity(pEnt, idBlock, AcDb::kForWrite);
	if (es!=eOk)
	{
		return idBlock;
	}
	if (!pEnt->isKindOf(AcDbBlockReference::desc()))
	{
		pEnt->close();
		return idBlock;
	}
	AcDbBlockReference *pRef = static_cast<AcDbBlockReference*>(pEnt);
	AcGePoint3d ptPos=pRef->position();
	AcGePoint3d ptMir1, ptMir2;
	ptMir1 = offsetPoint(ptPos, 0, 50);
	ptMir2 = offsetPoint(ptPos, 0, -50);
	AcGeLine3d line(ptMir1, ptMir2);
	AcGeMatrix3d mat;
	mat.setToMirroring(line);
	pEnt->transformBy(mat);
	pEnt->close();
	return idBlock;
}
