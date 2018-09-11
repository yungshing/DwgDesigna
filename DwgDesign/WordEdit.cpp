#include "StdAfx.h"
#include "WordEdit.h"
// #include "CApplication.h"
// #include "CDocuments.h"
// #include "CDocument0.h"
// #include "CSelection.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"

CWordEdit::CWordEdit()
{
}


CWordEdit::~CWordEdit()
{
}

void CWordEdit::Initialize()
{
// 	//初始化COM库  
// 	AfxOleInit();
// 
// 	//定义变量  
// 	COleVariant varstrNull(_T(""));
// 	COleVariant varTrue(short(1), VT_BOOL);
// 	COleVariant varFalse(short(0), VT_BOOL);
// 	COleVariant vTure(SHORT(TRUE)), vFalse(SHORT(FALSE));
// 	COleVariant vE(_T(""));
// 	COleVariant v0(SHORT(0)), v1(SHORT(1)), v2(SHORT(2)), v5(SHORT(5)), v6(SHORT(6)), v12(SHORT(12)), v22(SHORT(22));
// 
// 	CString strPath = GetDocPath();
// 
// 	CApplication app;
// 	app.CreateDispatch(_T("Word.Aoolication"));
// 	app.put_Visible(TRUE);
// 
// 	CDocuments docs = app.get_Documents();
// 	docs.AttachDispatch(app.get_Documents());
// 	
// 	docs.Open2000(COleVariant(strPath), varFalse, varFalse, varFalse,
// 		varstrNull, varstrNull, varFalse, varstrNull,
// 		varstrNull, varTrue, varTrue, varTrue);
// 
// 	CDocument0 doc0 = app.get_ActiveDocument();
// 	CSelection select = app.get_Selection();
// 
// 	select.TypeText(_T("test select"));
// 	select.TypeBackspace();
// 	select.TypeBackspace();
// 	
// 	CString sSave = _T("‪C:\\Users\\66409\\Desktop\\test.docx");
// 	COleVariant vF(SHORT(FALSE));
// 	doc0.SaveAs(COleVariant(sSave), v0, vF, vE, vF, vE, vF, vF, vF, vF, vF, vF, vF, vF, vF, vF);
// 	select.ReleaseDispatch();
// 	doc0.ReleaseDispatch();
// 	docs.ReleaseDispatch();
// 	app.Quit(vFalse, vFalse, vFalse);
// 	app.ReleaseDispatch();
}
