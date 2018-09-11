#pragma once
#include "resource.h"
#include "Common/Tools.h"
#include "Common/AllHead.h"
#include "excel9.h"
#include "rwExcel.h"
#include <algorithm>

// CDlgAccessory 对话框
struct FjInfo
{
	CString YQJ;//元器件
	CString WZDM;//物资代码
	CString MC;//名称
	CString GGXH;//规格型号
};

enum FjLocation
{
	LU=1,
	LD,
	RU,
	RD
};

struct FjMark
{
	CString YQJ;//元器件
	CString WH;//位号
	CString DW;//单位
	CString DH;//代号
	CString SL;//数量
	CString MC;//名称
	CString GGXH;//规格
	bool operator<(const FjMark b) const
	{
		return this->WH < b.WH;
	}
	bool operator==(const FjMark b) const
	{
		return this->MC == b.MC&&this->GGXH == b.GGXH&&this->DH==b.DH;
	}
	FjMark operator+(const FjMark b)
	{	
		CString sSlAll;
		if (this->DW==_T("m"))
		{
			if (this->SL==_T("*")||b.SL==_T("*"))
			{
				sSlAll = _T("*");
			}
			else
			{
				double dSl = _wtof(this->SL);
				double dSl2 = _wtof(b.SL);
				double dSlAll = dSl + dSl2;
				sSlAll.Format(_T("%.2f"), dSlAll);
			}		
		}
		else
		{
			if (this->SL == _T("*") || b.SL == _T("*"))
			{
				sSlAll = _T("*");
			}
			else
			{
				int iSl = _wtoi(this->SL);
				int iSl2 = _wtoi(b.SL);
				int iSlAll = iSl + iSl2;
				sSlAll.Format(_T("%d"), iSlAll);
			}		
		}
		this->SL = sSlAll;
		return *this;
	}
};


class CDlgAccessory : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAccessory)

public:
	CDlgAccessory(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAccessory();

// 对话框数据
	enum { IDD = IDD_DLG_ACCESSORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CAcUiComboBox m_cmb_Folder;//搜索文件
	CString m_sDlsjb;//电缆设计表
	CString m_sYqj;//元器件
	CString m_sSearch;//搜索字符串
	CAcUiComboBox m_cmb_Wh;//位号
	CAcUiComboBox m_cmb_Dw;//单位
	CString m_sDh;//代号
	CString m_sNum;//数量
	CString m_sMc;//名称
	CString m_sGgxh;//规格型号

	CRect m_rect;

	BOOL m_bConnect;//是否连接
	BOOL m_bLU;//左上
	BOOL m_bLD;//左下
	BOOL m_bRU;//右上
	BOOL m_bRD;//右下

	double m_dX;//绘制连线X长度
	double m_dY;//绘制连线Y长度
	double m_dLen;//水平长度

	double m_dLjLen;//V型线长度

	double m_dYLen;//文字距离线高度
	double m_dLeftX;//文字向左距离
	double m_dRightX;//文字向右距离

	double m_dTextHight;//文字高度
	double m_dWidthFactor;//宽度比例

	CListCtrl m_listFj;//附件List
	CListCtrl m_listYxfj;//已选附件List

	std::vector<FjInfo> m_vec_Fjinfo;
	FjLocation m_fjLocation;

	std::vector<FjMark> m_vec_FjMark;//存储图纸中提取的信息
	std::vector<FjMark> m_vec_Yxfj;//已选附件存储
	int m_iCurrentSelect;

	BOOL GetFjInfo(CString sExcelPath);
	BOOL RefreshLisht();

	void DrawPoly(AcGePoint3d pt1, AcGePoint3d pt2, AcGePoint3d pt3);
	void DrawPoly(AcGePoint3d pt1, AcGePoint3d pt2, AcGePoint3d pt3, AcGePoint3d pt4);
	void DrawFjMark(FjMark markInfo,AcGePoint3d ptInsert);
	void GetFjmxbInfo();
	BOOL CreatFjmxb(CString sSaveExcelPath);

	void GetYxfjInfo();//获取已选附件信息
	void RefreshYxfjList();//刷新已选附件信息

	BOOL CheckFjExist(FjMark &fj);//检测附件存在
	CMap<DWORD, DWORD&, COLORREF, COLORREF&> MapItemColor;
	void SetItemColor(DWORD iItem, COLORREF color);
public:
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnACADKeepFocus(WPARAM, LPARAM);
	BOOL keepTheFocus();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
//	afx_msg void OnCbnSelchangeCmbFolder();
	afx_msg void OnNMDblclkListFj(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditSearch();
	afx_msg void OnBnClickedBtnInsertfj();
	afx_msg void OnBnClickedBtnCreattab();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedBtnJs();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};
