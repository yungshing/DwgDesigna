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
		CDwgDatabaseUtil::getXdata(_T("ģ��ͼ��"), sTemp, pEnt);//����ģ����Ϣ�ж��ǲ��ǲ���Ŀ�
		CDwgDatabaseUtil::getXdata(_T("����ͼ��"), sTemp2, pEnt);
		pEnt->close();
		if (sTemp==_T("��"))
		{
			CAcModuleResourceOverride rs;
			CEditBlockDlg dlg(idEnt);
			dlg.DoModal();
		}
		if (sTemp2==_T("��"))
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