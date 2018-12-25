#pragma once
#include "Stdafx.h"
#include "excel9.h"
#include <fstream>
#include <comdef.h>
using namespace std;

//excel ��д
//typedef LPDISPATCH Interior;

//const COleVariant covTrue((short)TRUE);
//const COleVariant covFalse((short)FALSE);

//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);

class cExcel
{
public:
	cExcel();
	~cExcel();
	bool StartApp(CString strMoldName = _T(""));

	void CreateWorkBook(void);
	void OpenWorkBook(CString filename, CString sSheetName = _T(""));
	//2018.10.15///////////////////////////
	BOOL openSpecailFile(CString strFile);
	void CloseExcelFile(BOOL if_save = FALSE);
	CString strFilePath;
	///////////////////////////////////////
	void SelectAcitveSheet(void);
	void SetSheetName(CString sheetname);
	void SelectRange(CString range);
	void SelectRange(int x, int y);
	void SetBackColor(long color);
	void GetFont(void);
	void SwitchToSheet(CString sSheetName);
	void SwitchToSheet(long iIndex);
	void AddSheet(CString sSheetName);
	long GetSheetNum();
	void RemoveSheet(CString sSheetName);
	// 	void SetFontName(CString fontname);
	// 	void SetFontSytle(CString fontsytle);
	// 	void SetFontSize(long size);
	void PutValue(CString string);
	void PutValue(int x, int y, CString string);
	//
	CString GetCString(int x, int y);
	CString GetCString0(int x, int y);
	double GetValue(int x, int y);

	void InsertRow(int nRow);
	void InsertRow(CString strBegin, CString strEnd, long nStart);
	void SaveAs(CString filename);
	void SaveAs(CString path, CString filename);
	void Quit(void);
	bool isOpenExcel(CString filePath);


	void ActiveRange(int x,int y);
	void ShowExcel();
	void UnShowExcel();
	void GetSheets();
	void SetRangeType(int x,int y);

	_Worksheet GetSheet(){return pSheet;}
	_ExSheets GetExSheet(){ return pSheets; }
//	friend class CAutoRank;//��CAutoRank�����cExcel�����Ԫ�࣬��CAutoRank����ʹ��cExcel���˽�б���
//	friend class CBudgetView;//Ԥ��������ϢԤ��
//	friend class CAlterPrices;
private:
	_ExApplication pApp;
	Workbooks pBooks;
	_Workbook pBook;
	_ExSheets  pSheets;
	_Worksheet pSheet;
	_ExRange  pRange;
	Interior  pInterior;
	FontPtr   pFont;
};