#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "excel9.h"
#include "rwExcel.h"
#include <algorithm>

// CDlgHbTab 对话框
struct DesginTabInfo
{
	CString Yqzjhcl;//元气组件或材料，用于筛选连接器名称线缆名称
	CString xh;
	CString dljt;
	CString wzdm;
	CString wh;
	CString dybs;
	CString dz;
	CString tx;
	CString dljt2;
	CString wzdm2;
	CString wh2;
	CString dybs2;
	CString dz2;
	CString tx2;
	CString xlcl;
	CString xlwzdm;
	CString cd;
	CString dllx;

	bool operator<(const DesginTabInfo &b)
	{
		return this->wzdm2 < b.wzdm2;
	}
};

struct FjMxbInfo
{
	CString yqjhcl;
	CString wzdm;
	CString mc;
	CString xh;
	CString dwzl;
	CString yl;
};

struct WzdmNameXh
{
	CString wzdm;
	CString mc;
	CString xh;
};

struct LjqmcYqj//连接器名称和元器件
{
	CString ljqmc;
	CString yqj;
};

class CDlgHbTab : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgHbTab)

public:
	CDlgHbTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgHbTab();

// 对话框数据
	enum { IDD = IDD_DLG_HBTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sDlt;//电路图
	CString m_sGyk;//工艺库
	CProgressCtrl m_proGress;
	CString m_sW;
	CString m_sBm;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
private:
	vector<DesginTabInfo> m_vecDesginInfo;//存储提取出的设计表信息
	vector<FjMxbInfo> m_vecFjInfo;//附件信息提取
	map<CString, WzdmNameXh> m_mapYqAndMc;//A端 以及A端导线信息
	map<CString, LjqmcYqj> m_mapBdinfo;//B端 物资代码以及名称
	vector<DesginTabInfo> GetDesInfoToWzdm(CString YQJCL,CString WZDM);
	void ExportDesginInfo();
	BOOL m_bSp;//是否是射频单根
	BOOL m_bAorB;//判断从A处理电缆信息还是B  Ture对应A
public:
	virtual BOOL OnInitDialog();
};
