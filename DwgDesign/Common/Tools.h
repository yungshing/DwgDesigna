#pragma once
#include <vector>
#include <math.h>
#include <string>
#include <io.h>
#include <time.h>
#include <sys/timeb.h>
#include <iostream>
#include <fstream>
#include "AllHead.h"
using namespace std;
#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")

bool GetSelection(AcDbObjectIdArray& adoia, CString sPrompt = _T(""));

bool GetObjectIdArray(ads_name anSs, AcDbObjectIdArray& adoiaObjects);

CString GetDwgPath();//获取图库文件位置 包含图框 说明图等

CString GetMenuPath();

CString GetDocPath();

CString GetBlockLibPath();//调用固定块的图纸地址

CString GetIniPath();//获取ini文件位置

CString GetTextIniPath();//获取ini文件位置

CString GetWebexePath();//获取web程序地址

CString GetXmlPath();//获取Xml文件位置

CString GetFolderPath();//获得保存总文件夹位置

CString GetBatchDesignFoldPath();//批量电缆地址

CString GetExcelLogPath();//获取excel日志文件位置

CString GetWhLogPath();//获取位号日志文件地址

CString GetCheckMapPath();

CString GetExcelDlgxbPath();//获取excel电缆关系表地址

CString GetLogFolderPath();//获取日志文件夹

CString GetExcelDzbPath();//端子表excel地址获取

CString GetExcelFjmxbPath();//获取分机明细表地址

CString GetExcelFolder();//获取存储excel文件目录

std::vector<CString> GetDwgAllBlockName(const TCHAR* sDwgPath);

CString GetConnectionString();

BOOL FillCombo(CAcUiComboBox &cmbTemp, CString sTemp,CString sSplit=_T(","));

BOOL CopeDwgToFolder(CString sSourcePath, CString sExportPath);

BOOL CreatFolder(CString sFolderpath);

void HighLight(AcDbObjectIdArray idArr);

void UnHighLight(AcDbObjectIdArray idArr);

ads_real GetWidth();

int GetColorIndex();

BOOL AddPoly(CString sIndex,CString sHcl,CString sDhc,CString sView,AcGePoint3d ptEnd,AcDbObjectId &polyId);

BOOL AddPoly(AcGePoint3d ptStr,AcGePoint3d ptEnd, AcDbObjectId &polyId);

void MoveView(AcGePoint3d ptCenter, double dHight, double dWidth);

void getFiles(string path, string exd, vector<string>& files);

void FillCombo(CString sFolderPath, string exd, CAcUiComboBox &cmbTemp);

AcGePoint3d GetBlcokRefCenter(AcDbBlockReference*pRef, double &dx, double &dy);

AcGePoint3d GetBlockRefCenterTop(AcDbBlockReference*pRef, double &dx, double &dy);

AcDbExtents GetBlockRefExten(AcDbObjectId idBlock,double dEnlarge=0);

AcDbExtents GetBlockRefExten(AcDbBlockReference*pRef, double dLen);

bool PtInExten(AcGePoint3d pt, AcDbExtents ext);

AcDbObjectId WirePrompt(AcDbExtents ext);

AcDbObjectId WirePrompt(AcGePoint3d ptCirCenter, double dRadius);

bool DeleteWire(AcDbObjectId idTemp);

bool CheckPtInRect(AcGePoint3d pt, AcDbExtents ext);

CString GetTimer();

CString GetTimer2();//获取年月日

//************************************
// Method:    CheckExcelPath
// FullName:  CheckExcelPath
// Access:    public 
// Returns:   BOOL
// Qualifier: 检测地址是否是excel
// Parameter: CString sExcelPath 传入excel地址
//************************************
BOOL CheckExcelPath(CString sExcelPath);

double OpenObjAndGetLength(AcDbObjectId objId);

void SetDataBaseXdata(CString appname, CString value);

void GetDataBaseXdata(CString appname, CString &value);

CString ConvertString(CString str);

CString NumberConver(int i);

AcDbObjectId AddTableStyle();

void LoadDwgEnvironment();

CString EditString(const CString &str);

bool Compare2String(CString s1, CString s2);

bool GetWeihaoAndWzdm(CString sName, CString sMkwzdm, CString sMbwzdm, CString sMkljqmc, CString sMbljqmc, CString sSheetName,CString &weihao,CString &wuzidaima);

CString RemoveQhTest(CString sValue, std::vector<CString> vecWh);

CString RemoveMkTest(CString sValue, std::vector<CString>vecWh);

bool SelectExcelCell(CString sExcelPath, CString sSheetName, int nRow, int nCol);

bool GetDwgFrameInfo(FrameInfo &fm);

CString GetTextPath();

std::vector<CString> GetTextVal(CString sTextPath);

AcGePoint3d offsetPoint(AcGePoint3d pt, double x, double y);

AcDbObjectId MirrorBlock(AcDbObjectId idBlock);

double GetBlockHight(AcDbObjectId objId);

bool AddObjToGroup(CString strLabel, AcDbObjectId objId);

void UsageReat(CString sName, CString sBm = _T(""));

CString GetDwgBm();//获得当前图纸BM号