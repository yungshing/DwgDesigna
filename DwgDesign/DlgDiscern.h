#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "excel9.h"
#include "rwExcel.h"
#include <vector>
#include <algorithm>

// CDlgDiscern 对话框
struct ListLjxxinfo
{
	BOOL check;
	CString hcl;
	CString dhc;
};

class CDlgDiscern : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(CDlgDiscern)

public:
	CDlgDiscern(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDiscern();

// 对话框数据
	enum { IDD = IDD_DLG_DISCERN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	struct HclToDhc
	{
		CString sHcl;
		CString sDhc;
		BOOL operator<(const HclToDhc&b)const
		{
			return this->sDhc+this->sHcl < b.sDhc+b.sHcl;
		}
		BOOL operator==(const HclToDhc&b)const
		{
			if (this->sHcl==b.sHcl)
			{
				if (this->sDhc==b.sDhc)
				{
					return TRUE;
				}
			}
			return FALSE;
		}
	};
	
	CListCtrl m_listInfo;
	AcDbObjectIdArray m_idArrHighLight;
	std::vector<ListLjxxinfo> m_vecLjxxinfo;
	std::vector<CString> m_vecWeihao;
	bool m_bShowPrompt;
	CString m_sViewTemp;
public: 
	void RefreshList(CString sJxb);
	BOOL HighLightText(CString sRowNum,CString sText,CString sText2);
	void CheckInfo();
	BOOL CheckEntity(CString sHcl,CString sDhc,AcGePoint3d &ptCenter);
	void CheckAndRefreshList();

	AcDbObjectId GetBlockIdForText(AcGePoint3d ptTextInsert,CString sWzdm);
	BOOL CheckPolylineInExtens(AcDbExtents ext1,AcDbExtents ext2,AcDbObjectId idPolyline);

	bool RestoreList();
	void SearchInfo(CString Searchstr);
	void SetView(bool bCheck);

	CString RemoveQh(CString sValue);
	CString RemoveMk(CString sValue);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkListInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListInfo(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
