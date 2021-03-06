#pragma once
#include "resource.h"
#include "Common/Tools.h"
#include "Common/AllHead.h"
#include "DlgLjq.h"
#include "DlgDlgg.h"
#include "DlgDlfj.h"
#include "rwExcel.h"
#include "excel9.h"
#include "fcGsPreviewCtrl.h"
#include "DlgAccessory.h"
#include "DlgHbTab.h"
#include "DlgLhxx.h"

// CDlgPpsj 对话框
struct dljxbInfo
{
	CString xxh;//芯线号
	CString lx;//来向
	CString zjh1;//针脚号
	CString qx;//去向
	CString zjh2;//针脚号
	CString xx;//线型
	CString cd;//长度
	CString bz;//备注
};

//电缆连接器信息
struct dlljqInfo
{
	CString dljt;//电缆接头
	CString wzdm;//物资代码
	CString wh;//位号
	CString dybs;//打印标识
	CString dz;//端子
	CString tx;//特性
};

//电缆规格信息
struct dlggInfo
{
	CString LEFTLOCATION;//左边位置
	CString RIGHTLOCATION;//右边位置
	CString XLCL;//线缆材料
	CString XLWZDM;//线缆物资代码
};

struct dlLocationAndName
{
	CString LOCATION;
	CString NAME;
	CString WZDM;
};

enum CableType
{
	单根射频 =1,
	集束射频,
	集束射频n,
	两头集束,
	低频类型,
	单根低频,
	集束低频,
	集束低频n,
	errorType
};

class CDlgPpsj : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPpsj)

public:
	CDlgPpsj(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPpsj();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PPSJ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CString m_sAlreadyExistBm;

	

	CString m_sW;//w 获取
	CString m_sBm;//bm 获取
	bool isLhCable();//判断是不是连号电缆

	int m_nLhCableNum;//连号电缆数量
	int m_nLjqNum;//连接器数量

	void getLhCableNum();//获取连号电缆数量

	bool m_bJS;//记录右端是不是大于三
	vector<CString> m_vecLhBm;//bm号信息存储
	vector<CString> m_vecLhW;//电缆编号信息存储

	CString GetCableTypeIniPath();
	CString m_sDllx;//电缆类型
	CString m_sLeftWzdm, m_sRightWzdm;
	CableType m_enmuCableType;
	CableType GetCableType();
	bool m_bLeftDt, m_bRightDt;//左右端的单头处理
//	CString m_sDlgg;//电缆规格
	CString m_sDlName; //用于记录生成的电缆名称 如低频一分三等

	CAcUiComboBox m_cmb_Dllx;//电缆类型
	CAcUiComboBox m_cmb_Dlljxs;//电缆连接形式

	BOOL m_bLh;//连号电缆生成

	CListCtrl m_list_Ljqxh;//连接器型号
	CListCtrl m_list_Dlfjxx;//电缆附件信息
	CListCtrl m_list_Dlgg;//电缆规格

	map<CString, CString> m_mapLoc;//位置信息存储

	vector<dlljqInfo> m_vecLeft;//左端获取的信息
	vector<CString> m_vecLeftDuanzi;//端子信息单独存储
	vector<dlljqInfo> m_vecRight;//右端获取的信息
	vector<CString> m_vecRightDuanzi;

	vector<vector<dlljqInfo>> m_vecLhLeftAll;
	vector<vector<dlljqInfo>> m_vecLhRightAll;



	vector<dlggInfo> m_vecDlgg;//电缆规格信息
	vector<Log> m_vecLog;//电缆匹配设计导出的问题

	vector<dlLocationAndName> m_vecLocAndName;//存储位置以及名称

	fcGsPreviewCtrl m_fc;


	
	BOOL CheckExcel();//检测excel中的错误信息
	void GetDlInfo();//获取左端以及右端的端子名称
	void GetNewDlInfo();
	CString GetDlType(int iLeft, int iRight);//根据左右端的物资数量匹配出电缆类型
	void FillListLjq();
	void FillListDlgg();

	BOOL GetDljxbInfo();//获取接线表信息到容器中
	bool JudgeCreatJxb(CString sName);//判断是否需要接线表
	BOOL CreatDljxb(AcGePoint3d ptInsert);//生成电缆接线表
	
	BOOL GetDlMxbInfo();//获取电缆明细表信息
	BOOL CreatDlMxb();//生成电缆明细表

	BOOL CreatDlYzb(CString sYzbName,BOOL bLh,AcGePoint3d ptInsert);//电缆印字表生成 单根

	BOOL CreatLhDlYzb(CString sYzbName, CString sYzbUnitName, BOOL bLh, AcGePoint3d ptInsert);//电缆印子表 连号


	BOOL CreatTableYzb(AcGePoint3d ptInsert,BOOL Lh);

	int m_nItem;//用于操作修改edit
	int m_nSubItem;//修改
	CEdit m_Edit;//修改控件 
	void ShowEdit(bool bShow, int nItem, int nSubitem, CRect rc);

	BOOL CreatDlDwg(CString sBlockName,AcGePoint3d ptInsert);
	AcDbObjectId m_idModNBloock;
	void ExplodeRefAndModN(AcDbObjectId IdRef);
	BOOL CreatLjqDwg(CString sLocation, AcGePoint3d ptInsert,int &iMark);

	double m_dX;//绘制连线X长度
	double m_dY;//绘制连线Y长度
	double m_dLen;//水平长度

	void CreatMark(FjMark temp,AcGePoint3d ptInsert,CString sMark);

	CString DisposeBlockName(CString sName);
private:
	std::vector<dljxbInfo> m_vecTabInfo;
	CRect m_rect;//存储初始化控件大小
public:
	bool m_bWlpp;//物料匹配
	CString m_sDlljgxb;//电缆连接关系表
	void doParseExcel();
	void setAlreadyExistBm(CString sAlExBm);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnACADKeepFocus(WPARAM, LPARAM);
	BOOL keepTheFocus();
	afx_msg void OnBnClickedBtnSearch1();
	afx_msg void OnBnClickedBtnSearch3();
	afx_msg void OnBnClickedBtnSelect();
	afx_msg void OnBnClickedBtnSearch2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnDlmxb();
	afx_msg void OnNMDblclkListLjq(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEditMod();
	afx_msg void OnCbnSelchangeCmbDllj();
	afx_msg void OnNMDblclkListDlgg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnSj1();
	afx_msg void OnBnClickedBtnSj2();
	afx_msg void OnBnClickedBtnSj3();
	afx_msg void OnBnClickedBtnSj4();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedBtnHbtab();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonConnectselect();
//	afx_msg void OnNcDestroy();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
