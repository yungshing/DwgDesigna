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

// CDlgPpsj �Ի���
struct dljxbInfo
{
	CString xxh;//о�ߺ�
	CString lx;//����
	CString zjh1;//��ź�
	CString qx;//ȥ��
	CString zjh2;//��ź�
	CString xx;//����
	CString cd;//����
	CString bz;//��ע
};

//������������Ϣ
struct dlljqInfo
{
	CString dljt;//���½�ͷ
	CString wzdm;//���ʴ���
	CString wh;//λ��
	CString dybs;//��ӡ��ʶ
};

//���¹����Ϣ
struct dlggInfo
{
	CString LEFTLOCATION;//���λ��
	CString RIGHTLOCATION;//�ұ�λ��
	CString XLCL;//���²���
	CString XLWZDM;//�������ʴ���
};

struct dlLocationAndName
{
	CString LOCATION;
	CString NAME;
	CString WZDM;
};

class CDlgPpsj : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPpsj)

public:
	CDlgPpsj(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPpsj();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PPSJ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString m_sDlljgxb;//�������ӹ�ϵ��
	CString m_sW;//w ����
	CString m_sBm;//bm ����
	CString m_sDllx;
//	CString m_sDlgg;//���¹��

	CAcUiComboBox m_cmb_Dllx;//��������
	CAcUiComboBox m_cmb_Dlljxs;//����������ʽ

	BOOL m_bLh;//���ŵ�������

	CListCtrl m_list_Ljqxh;//�������ͺ�
	CListCtrl m_list_Dlfjxx;//���¸�����Ϣ
	CListCtrl m_list_Dlgg;//���¹��

	map<CString, char> m_mapLoc;

	CString m_sDlName;//���ڴ洢��������е�����

	vector<dlljqInfo> m_vecLeft;//��˻�ȡ����Ϣ
	vector<dlljqInfo> m_vecRight;//�Ҷ˻�ȡ����Ϣ
	vector<dlggInfo> m_vecDlgg;//���¹����Ϣ
	vector<Log> m_vecLog;//����ƥ����Ƶ���������

	vector<dlLocationAndName> m_vecLocAndName;//�洢λ���Լ�����

	fcGsPreviewCtrl m_fc;
	
	BOOL CheckExcel();//���excel�еĴ�����Ϣ
	void GetDlInfo();//��ȡ����Լ��Ҷ˵Ķ�������
	CString GetDlType(int iLeft, int iRight);//�������Ҷ˵���������ƥ�����������
	void FillListLjq();
	void FillListDlgg();
	BOOL GetDljxbInfo();//��ȡ���߱���Ϣ��������
	BOOL CreatDljxb(AcGePoint3d ptInsert);//���ɵ��½��߱�
	
	BOOL GetDlMxbInfo();//��ȡ������ϸ����Ϣ
	BOOL CreatDlMxb();//���ɵ�����ϸ��

	BOOL CreatDlYzb(CString sYzbName,BOOL bLh,AcGePoint3d ptInsert);//����ӡ�ֱ�����

	int m_nItem;//���ڲ����޸�edit
	int m_nSubItem;//�޸�
	CEdit m_Edit;//�޸Ŀؼ� 
	void ShowEdit(bool bShow, int nItem, int nSubitem, CRect rc);

	BOOL CreatDlDwg(CString sBlockName,AcGePoint3d ptInsert);
	BOOL CreatLjqDwg(CString sLocation, AcGePoint3d ptInsert,int &iMark);

	double m_dX;//��������X����
	double m_dY;//��������Y����
	double m_dLen;//ˮƽ����

	void CreatMark(FjMark temp,AcGePoint3d ptInsert);

	CString DisposeBlockName(CString sName);
private:
	std::vector<dljxbInfo> m_vecTabInfo;
	CRect m_rect;//�洢��ʼ���ؼ���С
public:
	virtual BOOL OnInitDialog();
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
};
