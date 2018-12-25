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

CString GetDwgPath();//��ȡͼ���ļ�λ�� ����ͼ�� ˵��ͼ��

CString GetMenuPath();

CString GetDocPath();

CString GetBlockLibPath();//���ù̶����ͼֽ��ַ

CString GetIniPath();//��ȡini�ļ�λ��

CString GetTextIniPath();//��ȡini�ļ�λ��

CString GetWebexePath();//��ȡweb�����ַ

CString GetXmlPath();//��ȡXml�ļ�λ��

CString GetFolderPath();//��ñ������ļ���λ��

CString GetBatchDesignFoldPath();//�������µ�ַ

CString GetExcelLogPath();//��ȡexcel��־�ļ�λ��

CString GetWhLogPath();//��ȡλ����־�ļ���ַ

CString GetCheckMapPath();

CString GetExcelDlgxbPath();//��ȡexcel���¹�ϵ���ַ

CString GetLogFolderPath();//��ȡ��־�ļ���

CString GetExcelDzbPath();//���ӱ�excel��ַ��ȡ

CString GetExcelFjmxbPath();//��ȡ�ֻ���ϸ���ַ

CString GetExcelFolder();//��ȡ�洢excel�ļ�Ŀ¼

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

CString GetTimer2();//��ȡ������

//************************************
// Method:    CheckExcelPath
// FullName:  CheckExcelPath
// Access:    public 
// Returns:   BOOL
// Qualifier: ����ַ�Ƿ���excel
// Parameter: CString sExcelPath ����excel��ַ
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

CString GetDwgBm();//��õ�ǰͼֽBM��