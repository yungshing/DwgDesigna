#pragma once
#include "resource.h"
#include "Common/Tools.h"
#include "Common/AllHead.h"
#include "excel9.h"
#include "rwExcel.h"
#include <algorithm>

// CDlgAccessory �Ի���
struct FjInfo
{
	CString YQJ;//Ԫ����
	CString WZDM;//���ʴ���
	CString MC;//����
	CString GGXH;//����ͺ�
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
	CString YQJ;//Ԫ����
	CString WH;//λ��
	CString DW;//��λ
	CString DH;//����
	CString SL;//����
	CString MC;//����
	CString GGXH;//���
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
	CDlgAccessory(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAccessory();

// �Ի�������
	enum { IDD = IDD_DLG_ACCESSORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CAcUiComboBox m_cmb_Folder;//�����ļ�
	CString m_sDlsjb;//������Ʊ�
	CString m_sYqj;//Ԫ����
	CString m_sSearch;//�����ַ���
	CAcUiComboBox m_cmb_Wh;//λ��
	CAcUiComboBox m_cmb_Dw;//��λ
	CString m_sDh;//����
	CString m_sNum;//����
	CString m_sMc;//����
	CString m_sGgxh;//����ͺ�

	CRect m_rect;

	BOOL m_bConnect;//�Ƿ�����
	BOOL m_bLU;//����
	BOOL m_bLD;//����
	BOOL m_bRU;//����
	BOOL m_bRD;//����

	double m_dX;//��������X����
	double m_dY;//��������Y����
	double m_dLen;//ˮƽ����

	double m_dLjLen;//V���߳���

	double m_dYLen;//���־����߸߶�
	double m_dLeftX;//�����������
	double m_dRightX;//�������Ҿ���

	double m_dTextHight;//���ָ߶�
	double m_dWidthFactor;//��ȱ���

	CListCtrl m_listFj;//����List
	CListCtrl m_listYxfj;//��ѡ����List

	std::vector<FjInfo> m_vec_Fjinfo;
	FjLocation m_fjLocation;

	std::vector<FjMark> m_vec_FjMark;//�洢ͼֽ����ȡ����Ϣ
	std::vector<FjMark> m_vec_Yxfj;//��ѡ�����洢
	int m_iCurrentSelect;

	BOOL GetFjInfo(CString sExcelPath);
	BOOL RefreshLisht();

	void DrawPoly(AcGePoint3d pt1, AcGePoint3d pt2, AcGePoint3d pt3);
	void DrawPoly(AcGePoint3d pt1, AcGePoint3d pt2, AcGePoint3d pt3, AcGePoint3d pt4);
	void DrawFjMark(FjMark markInfo,AcGePoint3d ptInsert);
	void GetFjmxbInfo();
	BOOL CreatFjmxb(CString sSaveExcelPath);

	void GetYxfjInfo();//��ȡ��ѡ������Ϣ
	void RefreshYxfjList();//ˢ����ѡ������Ϣ

	BOOL CheckFjExist(FjMark &fj);//��⸽������
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
