#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"

// CDlgSelectItem 对话框

class CDlgSelectItem : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgSelectItem)

public:
	CDlgSelectItem(int iBlockNum, AcGePoint3dArray ptArr, AcDbObjectIdArray idArr, double dx, double dy,CString sName,CString sWzdm,CString sView,
		int iTextHight,CListCtrl* weihaolist,int nItem,CWnd* pParent = NULL);   // 标准构造函数
	CDlgSelectItem(std::vector<NamePtAndID> MAPinfo, double dx, double dy, CWnd* pParent = NULL);   // 标准构造函数
 	virtual ~CDlgSelectItem();

// 对话框数据
	enum { IDD = IDD_DLG_ITEMSELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	//多余位号的处理记录
	std::vector<NamePtAndID> m_VecNamePtAndId;
	bool m_bWhdw;//多余位号定位是不是运行
	////////////////////

	CTreeCtrl m_tree;
	int m_iBlockNum;
	AcDbObjectIdArray m_idArr;
	AcGePoint3dArray m_ptArr;

	AcDbObjectId m_idWire;
	double m_dx;
	double m_dy;
	CString m_sName;
	CString m_sWzdm;
	CString m_sView;
	int m_iTextHight;

	CListCtrl* m_weihaolist;
	int m_nItem;

	bool m_bInsert;

	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickTreeSelect(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnNMDblclkTreeSelect(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeSelect(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	BOOL keepTheFocus();
	afx_msg LRESULT OnACADKeepFocus(WPARAM, LPARAM);
};

