// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "DlgMain.h"
#include "DlgViewSet.h"
#include "DlDwg.h"
#include "DlgAutoCreat.h"
#include "DoubleClick.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "DlgPpsj.h"
#include "DlgAccessory.h"
#include "DlgFrame.h"
#include "DlgJswz.h"
#include <acadi.h>
#include "DlgLhxx.h"
#include "WordEdit.h"
#include <atlbase.h>

extern CDlgMain *pDlg;
extern CDlgViewSet *pSetViewDlg;
extern CDlgAccessory *pDlgAccessory;
extern CDlgSelectItem *pDlgSelect;
//-----------------------------------------------------------------------------
#define szRDS _RXST("")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CDwgDesignApp : public AcRxArxApp {

public:
	CDwgDesignApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here
// 		CDoubleClick *pDouble = new CDoubleClick;
// 		AcDbBlockReference::desc()->addX(AcDbDoubleClickEdit::desc(), pDouble);
		LoadDwgEnvironment();

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here
		if (pDlg!=NULL)
		{
			pDlg->DestroyWindow();
			delete pDlg;
			pDlg = NULL;
		}
		if (pDlgAccessory!=NULL)
		{
			pDlgAccessory->DestroyWindow();
			delete pDlgAccessory;
			pDlgAccessory = NULL;
		}
		if (pSetViewDlg!=NULL)
		{
			pSetViewDlg->DestroyWindow();
			delete pSetViewDlg;
			pSetViewDlg = NULL;
		}
		if (pDlgSelect!=NULL)
		{
			pSetViewDlg->DestroyWindow();
			delete pSetViewDlg;
			pSetViewDlg = NULL;
		}
		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here
		AcDbBlockReference::desc()->delX(AcDbDoubleClickEdit::desc());

		return (retCode) ;
	}

	static void Cmds_Test()
	{
// 		CAcModuleResourceOverride rs;
// 		CDlgSelectItem dlg(100);
// 		dlg.DoModal();
// 		std::vector<CString> vecStr;
// 		vecStr = GetTextVal(GetTextPath());
// 		vecStr.push_back(_T("A11"));
// 
// 		CString s4 = RemoveMkTest(_T("A0X3X3MT"), vecStr);
// 		CString s1 = RemoveQhTest(_T("A0XS2"),vecStr);
//		CString s1 = _T("asdasf_PRD-TMP-ASDFAS_11123");
//		CString s2 = _T("bbbff_BMXXX_QWE_213_EEEEEE");
//		s1 = EditString(s1);
//		s2 = EditString(s2);
// 		CWordEdit edit;
// 		edit.Initialize();

// 		AcDbEntity *pent = NULL;
// 		AcGePoint3d pt;
// 		bool b=CSelectUtil::PromptSelectEntity(_T("xuanz"), AcDbLine::desc(), pent, pt);
// 		if (!b)
// 		{
// 			return;
// 		}
// 		pent->highlight();
// 		pent->close();

// 	   BOOL b=AddPoly(_T("1"),_T("wh"),_T("sh"));
// 	   if (b)
// 	   {
// 		   AfxMessageBox(_T("wan cheng"));
// 	   }

// 		acedSetStatusBarProgressMeter(TEXT("Do something...:"), 0, 5);
// 		for (int i = 0; i < 5; i++)
// 		{
// 			// 控制进度条当前进度位置    
// 			Sleep(1000);
// 			acedSetStatusBarProgressMeterPos(i + 1);
// 			// Do something  
// 		}
// 		// 还原状态栏之前的样子  
// 		acedRestoreStatusBar();

// 		SetDataBaseXdata(_T("asd"), _T("ggg"));
// 		CString sVALUE;
// 		GetDataBaseXdata(_T("aaa"), sVALUE);
// 		int a = 0;

// 		CAcModuleResourceOverride rs;
// 		CDlgLhxx dlg;
// 		dlg.DoModal();

		
		// TODO: 在此添加控件通知处理程序代码
	}

	static void Cmds_Test2()
	{
		SelectExcelCell(_T("C:\\Users\\66409\\Desktop\\层级+MS关系测试文件20180806\\电气特性表.xlsx"), _T("A0(X3)"), 4, 4);
	}

	static void Cmds_JXT()
	{
		CAcModuleResourceOverride rs;
		if (pDlg == NULL)
		{
			pDlg = new CDlgMain(acedGetAcadFrame());
			pDlg->Create(IDD_DLG_MAIN);
		}
		if (pSetViewDlg == NULL)
		{
			pSetViewDlg = new CDlgViewSet(acedGetAcadFrame());
			pSetViewDlg->Create(IDD_DLG_VIEW);
			pSetViewDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			pSetViewDlg->ShowWindow(SW_SHOW);
		}
	}

// 	static void Cmds_JXT()
// 	{
// 		int nRet=AfxMessageBox(_T("请确保此图是从微波组件结构设计模块中导出，并且该图纸中无图框"),MB_YESNO);
// 		if (nRet==6)
// 		{
// 			if (pDlg == NULL)
// 			{
// 				pDlg = new CDlgMain(acedGetAcadFrame());
// 				pDlg->Create(IDD_DLG_MAIN);
// 				pDlg->ShowWindow(SW_SHOW);
// 			}
// 			else
// 			{
// 				pDlg->ShowWindow(SW_SHOW);
// 			}
// 		}
// 	}

	static void Cmds_DLT()
	{
		CAcModuleResourceOverride rs;
		CDlgPpsj dlg;
		dlg.DoModal();
	}

	static void Cmds_FJ()
	{
		CAcModuleResourceOverride rs;
		if (pDlgAccessory==NULL)
		{
			pDlgAccessory = new CDlgAccessory(acedGetAcadFrame());
			pDlgAccessory->Create(IDD_DLG_ACCESSORY);
			pDlgAccessory->ShowWindow(SW_SHOW);
		}
		else
		{
			pDlgAccessory->ShowWindow(SW_SHOW);
		}
	}

	static void Cmds_WJ()
	{
		AcGePoint3d ptStr, ptMid, ptEnd;
		AcDbObjectId idLine,idLine2;
		bool b;
		b = CGetInputUtil::GetPoint(_T("\n选择外接绘制起点:"), ptStr);
		if (!b)
		{
			return;
		}
		b = CGetInputUtil::GetPoint(ptStr, _T("\n选择外接绘制拐点"), ptMid);
		if (!b)
		{
			return;
		}
		idLine = CLineUtil::Add(ptStr, ptMid);
		b = CGetInputUtil::GetPoint(ptMid, _T("\n选择外接绘制终点"), ptEnd);
		if (!b)
		{
			DeleteWire(idLine);
			return;
		}
		idLine2 = CLineUtil::Add(ptMid, ptEnd);
		CString str;
		int nRet=acedGetString(FALSE, _T("\n输入标记字符"), str.GetBufferSetLength(1000));
		if (nRet!=RTNORM)
		{
			DeleteWire(idLine);
			DeleteWire(idLine2);
			return;
		}
		str.ReleaseBufferSetLength(1000);

		DeleteWire(idLine);
		AcDbPolyline *pPoly = new AcDbPolyline;
		pPoly->addVertexAt(0, CConvertUtil::ToPoint2d(ptStr));
		pPoly->addVertexAt(1, CConvertUtil::ToPoint2d(ptMid));
		pPoly->addVertexAt(2, CConvertUtil::ToPoint2d(ptEnd));
		CDwgDatabaseUtil::PostToModelSpace(pPoly);
		double dLen = ptMid.distanceTo(ptEnd);
		double dTextHight = dLen / 5;
		AcGePoint3d ptInsert = AcGePoint3d((ptMid.x + ptEnd.x) / 2, (ptMid.y + ptEnd.y) / 2 + dTextHight/2+dTextHight/10, 0);
		AcDbText*pText = new AcDbText(ptInsert, str, AcDbObjectId::kNull, dTextHight);
		pText->setHorizontalMode(AcDb::kTextCenter);
		pText->setVerticalMode(AcDb::kTextVertMid);
		pText->setAlignmentPoint(ptInsert);
		CDwgDatabaseUtil::PostToModelSpace(pText);

	}

	static void Cmds_TK2()
	{
		CAcModuleResourceOverride rs;
		CDlgFrame dlg;
		dlg.DoModal();
	}

	static void Cmds_JSWZ2()
	{
		CAcModuleResourceOverride rs;
		CDlgJswz dlg;
		dlg.DoModal();
	}

	static void Cmds_Ww()
	{
		CAcModuleResourceOverride rs;
		CDlDwg dlg;
		dlg.DoModal();
	}

	static void Cmds_Ee()
	{
		CAcModuleResourceOverride rs;
		CDlgAutoCreat dlg;
		dlg.DoModal();
	}

	struct DLinfo
	{
		CString sName;
		CString sNote;
	};

	static void Cmds_Rr()
	{
		std::vector<DLinfo> vecInfo;
		AcDbObjectIdArray idArr = CDwgDatabaseUtil::GetAllEntityIds();
		int iLen = idArr.length();
		for (int i = 0; i < iLen;i++)
		{
			AcDbObjectId idTemp = idArr[i];
			AcDbEntity *pEnt = NULL;
			Acad::ErrorStatus es;
			es = acdbOpenAcDbEntity(pEnt, idTemp, AcDb::kForWrite);
			if (es!=Acad::eOk)
			{
				continue;
			}
			if (!pEnt->isKindOf(AcDbBlockReference::desc()))
			{
				pEnt->close();
				continue;
			}
			DLinfo dlTemp;
			CString sTemp;
			CDwgDatabaseUtil::getXdata(_T("电缆图块"), sTemp, pEnt);
			if (sTemp==_T("是"))
			{
				dlTemp.sName = _T("电缆");
				vecInfo.push_back(dlTemp);
			}
			CString sTemp2;
			CDwgDatabaseUtil::getXdata(_T("模版图块"), sTemp2, pEnt);
			if (sTemp2==_T("是"))
			{
				dlTemp.sName = _T("模版");
				vecInfo.push_back(dlTemp);
			}		
			pEnt->close();
		}
		AcDbTable *pTab = new AcDbTable;
		int iSize=vecInfo.size();
		pTab->setNumColumns(2);
		pTab->setNumRows(iSize + 1);
		pTab->setTextString(0, 0, _T("列1"));
		pTab->setTextString(0, 1, _T("列2"));
		pTab->setPosition(AcGePoint3d::kOrigin);
		for (int i = 0; i < iSize + 1;i++)
		{
			pTab->setRowHeight(i, 20);
		}
		pTab->setColumnWidth(0, 100);
		pTab->setColumnWidth(1, 200);
		for (int i = 0; i < iSize ;i++)
		{
			DLinfo dlTemp = vecInfo[i];
			CString sName = dlTemp.sName;
			pTab->setTextString(i+1, 0, sName);
		}
		CDwgDatabaseUtil::PostToModelSpace(pTab);
		actrTransactionManager->flushGraphics(); /*refresh screen*/
		acedUpdateDisplay();
	}

	virtual void RegisterServerComponents () {
	}

} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CDwgDesignApp)
ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _Test, Test, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _Test2, Test2, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _ST, ST, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _JXT, JXT, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _DLT, DLT, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _FJ, FJ, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _WJ, WJ, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _TK2, TK2, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _JSWZ2, JSWZ2, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _Ww, Ww, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _Ee, Ee, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDwgDesignApp, Cmds, _Rr, Rr, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)