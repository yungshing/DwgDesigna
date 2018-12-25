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
	CString dz;//����
	CString tx;//����
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

enum CableType
{
	������Ƶ =1,
	������Ƶ,
	������Ƶn,
	��ͷ����,
	��Ƶ����,
	������Ƶ,
	������Ƶ,
	������Ƶn,
	errorType
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

private:
	CString m_sAlreadyExistBm;

	

	CString m_sW;//w ��ȡ
	CString m_sBm;//bm ��ȡ
	bool isLhCable();//�ж��ǲ������ŵ���

	int m_nLhCableNum;//���ŵ�������
	int m_nLjqNum;//����������

	void getLhCableNum();//��ȡ���ŵ�������

	bool m_bJS;//��¼�Ҷ��ǲ��Ǵ�����
	vector<CString> m_vecLhBm;//bm����Ϣ�洢
	vector<CString> m_vecLhW;//���±����Ϣ�洢

	CString GetCableTypeIniPath();
	CString m_sDllx;//��������
	CString m_sLeftWzdm, m_sRightWzdm;
	CableType m_enmuCableType;
	CableType GetCableType();
	bool m_bLeftDt, m_bRightDt;//���Ҷ˵ĵ�ͷ����
//	CString m_sDlgg;//���¹��
	CString m_sDlName; //���ڼ�¼���ɵĵ������� ���Ƶһ������

	CAcUiComboBox m_cmb_Dllx;//��������
	CAcUiComboBox m_cmb_Dlljxs;//����������ʽ

	BOOL m_bLh;//���ŵ�������

	CListCtrl m_list_Ljqxh;//�������ͺ�
	CListCtrl m_list_Dlfjxx;//���¸�����Ϣ
	CListCtrl m_list_Dlgg;//���¹��

	map<CString, CString> m_mapLoc;//λ����Ϣ�洢

	vector<dlljqInfo> m_vecLeft;//��˻�ȡ����Ϣ
	vector<CString> m_vecLeftDuanzi;//������Ϣ�����洢
	vector<dlljqInfo> m_vecRight;//�Ҷ˻�ȡ����Ϣ
	vector<CString> m_vecRightDuanzi;

	vector<vector<dlljqInfo>> m_vecLhLeftAll;
	vector<vector<dlljqInfo>> m_vecLhRightAll;



	vector<dlggInfo> m_vecDlgg;//���¹����Ϣ
	vector<Log> m_vecLog;//����ƥ����Ƶ���������

	vector<dlLocationAndName> m_vecLocAndName;//�洢λ���Լ�����

	fcGsPreviewCtrl m_fc;


	
	BOOL CheckExcel();//���excel�еĴ�����Ϣ
	void GetDlInfo();//��ȡ����Լ��Ҷ˵Ķ�������
	void GetNewDlInfo();
	CString GetDlType(int iLeft, int iRight);//�������Ҷ˵���������ƥ�����������
	void FillListLjq();
	void FillListDlgg();

	BOOL GetDljxbInfo();//��ȡ���߱���Ϣ��������
	bool JudgeCreatJxb(CString sName);//�ж��Ƿ���Ҫ���߱�
	BOOL CreatDljxb(AcGePoint3d ptInsert);//���ɵ��½��߱�
	
	BOOL GetDlMxbInfo();//��ȡ������ϸ����Ϣ
	BOOL CreatDlMxb();//���ɵ�����ϸ��

	BOOL CreatDlYzb(CString sYzbName,BOOL bLh,AcGePoint3d ptInsert);//����ӡ�ֱ����� ����

	BOOL CreatLhDlYzb(CString sYzbName, CString sYzbUnitName, BOOL bLh, AcGePoint3d ptInsert);//����ӡ�ӱ� ����


	BOOL CreatTableYzb(AcGePoint3d ptInsert,BOOL Lh);

	int m_nItem;//���ڲ����޸�edit
	int m_nSubItem;//�޸�
	CEdit m_Edit;//�޸Ŀؼ� 
	void ShowEdit(bool bShow, int nItem, int nSubitem, CRect rc);

	BOOL CreatDlDwg(CString sBlockName,AcGePoint3d ptInsert);
	AcDbObjectId m_idModNBloock;
	void ExplodeRefAndModN(AcDbObjectId IdRef);
	BOOL CreatLjqDwg(CString sLocation, AcGePoint3d ptInsert,int &iMark);

	double m_dX;//��������X����
	double m_dY;//��������Y����
	double m_dLen;//ˮƽ����

	void CreatMark(FjMark temp,AcGePoint3d ptInsert,CString sMark);

	CString DisposeBlockName(CString sName);
private:
	std::vector<dljxbInfo> m_vecTabInfo;
	CRect m_rect;//�洢��ʼ���ؼ���С
public:
	bool m_bWlpp;//����ƥ��
	CString m_sDlljgxb;//�������ӹ�ϵ��
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
