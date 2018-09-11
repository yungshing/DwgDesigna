#pragma once
#include "resource.h"
#include "DlgDiscern.h"
#include "DlgWeihao.h"
#include "excel9.h"
#include "rwExcel.h"
#include "DlgPrompt.h"
#include "Common/Tools.h"

// CDlgMain 对话框

class CDlgMain : public CAcUiTabMainDialog
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	CDlgMain(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMain();

// 对话框数据
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CAcUiTab m_tab;//tab容器
	CDlgDiscern m_dlgDiscern;//接线识别对话框
	CDlgWeihao m_dlgWeihao;//位号生成对话框

	CString m_sDqtx;//电气特性表地址
	CString m_sJxb;//接线表地址
	CString m_sZjys;//中间映射表

	CString m_sBlockName;//存储当前块名
	CString m_sName;//存储匹配出的名称

	BOOL m_bYcl;//已处理
	BOOL m_bWcl;//未处理
	BOOL m_bZh;//综合

	CString m_sSearch;//搜索

	CAcUiComboBox m_cmb_View;//视图
	CString m_sCurrentView;//当前视图字符串
	AcDbObjectIdArray m_ViewIdArr;

	AcDbObjectIdArray m_ErrorId;
	std::vector<Adesk::UInt16> m_vecColor;

	BOOL m_bSelect;//用于判断是否在选择阶段
	BOOL m_bShowPrompt;

	struct InfoAddress//物资代码名称及所在excel行列
	{
		int SheetNum;
		int RowNum;
		int ColNum;
		CString WZDM;//模块用物资代码
		CString COVERWZDM;//映射后物资代码
		CString NAME;//名称
		CString COVERNAME;//生成名称
		CString LJQNAME;//连接器名称
	};

	struct DzAndXh//端子线号信息
	{
		CString DZ;
		CString XH;
	};

	struct PointAndID//记录生成的插入点和id
	{
		AcGePoint3d POINT;
		CString NAME;
		AcDbObjectId ID;
	};

	std::map<CString, CString> m_mapZjys;//存储中间映射表

	std::vector <InfoAddress> m_vecInfo;//存储物资代码信息结构体
	std::vector<CString> m_vecExistWh;//存储图纸中存在的位号信息
	std::vector<CString> m_vecExistDzb;//存储图纸中存在的端子表信息
	std::vector<CreatWhLog> m_vecWhLog;//生成位号导出日志信息的存储
	std::vector<CString> m_vecCheckMap;//存储映射校验中的问题

	std::vector<CString> m_vecDzb;//需生成端子表存储

	struct NameAndPosition//存储需要生成位号信息的块的名称及插入点
	{
		CString NAME;
		AcGePoint3dArray PTARR;
		bool operator==(const NameAndPosition &b)
		{
			//修改比较方式
			/*return this->NAME == b.NAME;*/
			return Compare2String(this->NAME, b.NAME);
		}
		NameAndPosition* operator+(const NameAndPosition &b)
		{
			this->PTARR.append(b.PTARR);
			return this;
		}
	};
	std::vector<NameAndPosition> m_vecNameAndPosition;//名称插入点信息存储

	struct MxbInfo//明细表结构体
	{
		CString XH;
		CString WH;
		CString DH;
		CString BB;
		CString MC;
		CString DW;
		CString SL;
		CString BZ;
		CString GG;
	};
	std::vector<MxbInfo> m_vecMxb;//分机模块明细表信息提取

	std::vector<PointAndID> m_vecPointAndId;
public:
	BOOL FindInfo();//查找excel中的所有名称对应物资代码信息
	
	BOOL GetMapTab();//通过导入excel查找中间映射表格

	//************************************
	// Method:    CreatMark
	// FullName:  CDlgMain::CreatMark
	// Access:    public 
	// Returns:   void
	// Qualifier: 生成位号标记
	// Parameter: CString sText 生成的文字
	// Parameter: int iHeight 文字高度
	//************************************
	void CreatMark(CString sText,int iHeight);
	//************************************
	// Method:    CreatDzXh
	// FullName:  CDlgMain::CreatDzXh
	// Access:    public 
	// Returns:   void
	// Qualifier: 生成端子线号
	// Parameter: std::vector<DzAndXh> vec 端子线号信息存储
	// Parameter: AcGePoint3d ptInsert //插入点
	// Parameter: CString sName //表头名称
	//************************************
	void CreatDzXh(std::vector<DzAndXh> vec, AcGePoint3d ptInsert,CString sName);

	void GetAllDwgTextAndPosition();//获取图纸中所有块对应的文字以及插入点
	void CheckDwgWh();//检测位号信息

	bool CheckWhPostion();//检测位号位置生成是否重叠

	void CheckDwgDzb();//检测端子表信息
	//************************************
	// Method:    CreatMarkToText
	// FullName:  CDlgMain::CreatMarkToText
	// Access:    public 
	// Returns:   void
	// Qualifier:生成位号标记
	// Parameter: int iHeight 生成文字的高度
	//************************************
	void CreatMarkToText(int iHeight);

	//************************************
	// Method:    ExportDzb
	// FullName:  CDlgMain::ExportDzb
	// Access:    public 
	// Returns:   bool
	// Qualifier:导出端子表日志信息
	// Parameter: CString & sExcelPath 导出的excel地址
	//************************************
	bool ExportDzb(CString &sExcelPath);

	//************************************
	// Method:    CreatJxb
	// FullName:  CDlgMain::CreatJxb
	// Access:    public 
	// Returns:   int 端子表的行数
	// Qualifier:生成端子接线表
	// Parameter: CString sCreatName 表头名称
	// Parameter: AcGePoint3d ptInsert 插入点
	//************************************
	int CreatJxb(CString sCreatName,AcGePoint3d ptInsert);

	//************************************
	// Method:    GetMarkNum
	// FullName:  CDlgMain::GetMarkNum
	// Access:    public 
	// Returns:   CString 数量字符
	// Qualifier: 获取名称对应的数量
	// Parameter: CString sName 名称输入
	//************************************
	CString GetMarkNum(CString sName);
	void GetMxbInfo();//分析明细表信息提取
	bool CreatMxb(bool bAddFrameInfo,FrameInfo fm);//分机明细表生成
	CString FindDhName(CString sDh);

	bool ExportWhLog(CString &sExcelPath);
	bool ExportCheckMapLog(CString &sExcelPath);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSelectBlock();
	afx_msg void OnBnClickedBtnDqtx();
	afx_msg void OnBnClickedBtnJxb();
//	afx_msg void OnBnClickedBtnFindinfo();
	afx_msg void OnBnClickedBtnCreatmark();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	afx_msg LRESULT OnACADKeepFocus(WPARAM, LPARAM);
	BOOL keepTheFocus();
	afx_msg void OnBnClickedBtnCretejxb();
	afx_msg void OnBnClickedBtnReflist();
	afx_msg void OnBnClickedBtnCheckinfo();
	afx_msg void OnBnClickedBtnTabtomark();
	afx_msg void OnBnClickedBtnAutowh();
	afx_msg void OnBnClickedBtnCheckwh();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnBnClickedRadioYcl();
	afx_msg void OnBnClickedRadioZh();
	afx_msg void OnBnClickedRadioWcl();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnMxb();
	afx_msg void OnBnClickedBtnSetview();
	afx_msg void OnBnClickedBtnCheckdwg();
	afx_msg void OnBnClickedBtnRestoredwg();
	afx_msg void OnCbnSelchangeCmbView();
	afx_msg void OnEnChangeEditSearch();
	afx_msg void OnBnClickedBtnZjys();
	afx_msg void OnBnClickedBtnHightlight();
	afx_msg void OnBnClickedBtnUnhightlight();
	afx_msg void OnBnClickedBtnMapcheck();
};
