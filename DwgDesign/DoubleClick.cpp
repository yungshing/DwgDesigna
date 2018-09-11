#include "StdAfx.h"
#include "DoubleClick.h"


CDoubleClick::CDoubleClick()
{
}


CDoubleClick::~CDoubleClick()
{
}

ACRX_DEFINE_MEMBERS(AcDbDoubleClickEdit);

void CDoubleClick::startEdit(AcDbEntity *pEnt, AcGePoint3d pt)
{
	AcDbObjectId idEnt = pEnt->id();
	if (pEnt->isKindOf(AcDbBlockReference::desc()))
	{
		CString sTemp,sTemp2;
		CDwgDatabaseUtil::getXdata(_T("模版图块"), sTemp, pEnt);//根据模版信息判断是不是插入的块
		CDwgDatabaseUtil::getXdata(_T("电缆图块"), sTemp2, pEnt);
		pEnt->close();
		if (sTemp==_T("是"))
		{
			CAcModuleResourceOverride rs;
			CEditBlockDlg dlg(idEnt);
			dlg.DoModal();
		}
		if (sTemp2==_T("是"))
		{
			CAcModuleResourceOverride rs;
			CEditDlDlg dlg(idEnt);
			dlg.DoModal();
		}
	}
	else
	{
		pEnt->close();
	}	
}

void CDoubleClick::finishEdit(void)
{

}