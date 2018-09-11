#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "excel9.h"
#include "rwExcel.h"
#include "DlgSelectItem.h"

// CDlgWeihao �Ի���

struct Listinfo
{
	BOOL check;
	CString mc;
	CString wzdm;
};

class CDlgWeihao : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(CDlgWeihao)

public:
	CDlgWeihao(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWeihao();

// �Ի�������
	enum { IDD = IDD_DLG_WEIHAO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listWeihao;//�洢λ�ŵ�����
	CString m_sDqtxljb;//�����������ӱ�
	std::vector<Listinfo> m_vecListinfo;
	std::vector<Log> m_vecLog;//���ڴ洢������Ϣ
	bool m_bInsert;
	bool m_bShowPrompt;
	CString m_sView;
	std::map<CString, CString> m_mapZjys;//�м�ӳ���
	std::map<CString, CString> m_mapName2Name;//�洢��������
	//�˵���������
	CPoint m_menuPoint;
	int m_iBlockNum;
	int m_iMenuClick;
	AcDbObjectIdArray m_idArrBlock;
	AcGePoint3dArray m_ptArr;
	CString m_sCreatName;
	CString m_sWzdm;
	int m_iHeight;
	bool m_bSuccessInsert;
	double m_dX;
	double m_dY;
	int m_nItem;


	void RefreshList(CString sDqtxb,map<CString,CString> mapCover);
	bool ExportLog(CString &sExcelPath);
	bool CreatMark(CString sName,CString sWzdm, int iHeight,bool bNoneBlock=false);
	bool ConnectDzb(CString sMarkText);
	void FindWh();
	bool RestoreList();
	void SetView(bool bCheck);
	void SearchWh(CString searchStr);
	bool CheckPtCreatWh(CString sWzdm, CString sView,AcDbExtents ext);

	friend class CDlgSelectItem;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkListWeihao(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLvnItemchangedListWeihao(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLvnItemchangingListWeihao(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListWeihao(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRDblclkListWeihao(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMRClickListWeihao(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
