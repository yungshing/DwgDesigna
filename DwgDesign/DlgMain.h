#pragma once
#include "resource.h"
#include "DlgDiscern.h"
#include "DlgWeihao.h"
#include "excel9.h"
#include "rwExcel.h"
#include "DlgPrompt.h"
#include "Common/Tools.h"

// CDlgMain �Ի���

class CDlgMain : public CAcUiTabMainDialog
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	CDlgMain(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMain();

// �Ի�������
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CAcUiTab m_tab;//tab����
	CDlgDiscern m_dlgDiscern;//����ʶ��Ի���
	CDlgWeihao m_dlgWeihao;//λ�����ɶԻ���

	CString m_sDqtx;//�������Ա��ַ
	CString m_sJxb;//���߱��ַ
	CString m_sZjys;//�м�ӳ���

	CString m_sBlockName;//�洢��ǰ����
	CString m_sName;//�洢ƥ���������

	BOOL m_bYcl;//�Ѵ���
	BOOL m_bWcl;//δ����
	BOOL m_bZh;//�ۺ�

	CString m_sSearch;//����

	CAcUiComboBox m_cmb_View;//��ͼ
	CString m_sCurrentView;//��ǰ��ͼ�ַ���
	AcDbObjectIdArray m_ViewIdArr;

	AcDbObjectIdArray m_ErrorId;
	std::vector<Adesk::UInt16> m_vecColor;

	BOOL m_bSelect;//�����ж��Ƿ���ѡ��׶�
	BOOL m_bShowPrompt;

	struct InfoAddress//���ʴ������Ƽ�����excel����
	{
		int SheetNum;
		int RowNum;
		int ColNum;
		CString WZDM;//ģ�������ʴ���
		CString COVERWZDM;//ӳ������ʴ���
		CString NAME;//����
		CString COVERNAME;//��������
		CString LJQNAME;//����������
	};

	struct DzAndXh//�����ߺ���Ϣ
	{
		CString DZ;
		CString XH;
	};

	struct PointAndID//��¼���ɵĲ�����id
	{
		AcGePoint3d POINT;
		CString NAME;
		AcDbObjectId ID;
	};

	std::map<CString, CString> m_mapZjys;//�洢�м�ӳ���

	std::vector <InfoAddress> m_vecInfo;//�洢���ʴ�����Ϣ�ṹ��
	std::vector<CString> m_vecExistWh;//�洢ͼֽ�д��ڵ�λ����Ϣ
	std::vector<CString> m_vecExistDzb;//�洢ͼֽ�д��ڵĶ��ӱ���Ϣ
	std::vector<CreatWhLog> m_vecWhLog;//����λ�ŵ�����־��Ϣ�Ĵ洢
	std::vector<CString> m_vecCheckMap;//�洢ӳ��У���е�����

	std::vector<CString> m_vecDzb;//�����ɶ��ӱ�洢

	struct NameAndPosition//�洢��Ҫ����λ����Ϣ�Ŀ�����Ƽ������
	{
		CString NAME;
		AcGePoint3dArray PTARR;
		bool operator==(const NameAndPosition &b)
		{
			//�޸ıȽϷ�ʽ
			/*return this->NAME == b.NAME;*/
			return Compare2String(this->NAME, b.NAME);
		}
		NameAndPosition* operator+(const NameAndPosition &b)
		{
			this->PTARR.append(b.PTARR);
			return this;
		}
	};
	std::vector<NameAndPosition> m_vecNameAndPosition;//���Ʋ������Ϣ�洢

	struct MxbInfo//��ϸ��ṹ��
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
	std::vector<MxbInfo> m_vecMxb;//�ֻ�ģ����ϸ����Ϣ��ȡ

	std::vector<PointAndID> m_vecPointAndId;
public:
	BOOL FindInfo();//����excel�е��������ƶ�Ӧ���ʴ�����Ϣ
	
	BOOL GetMapTab();//ͨ������excel�����м�ӳ����

	//************************************
	// Method:    CreatMark
	// FullName:  CDlgMain::CreatMark
	// Access:    public 
	// Returns:   void
	// Qualifier: ����λ�ű��
	// Parameter: CString sText ���ɵ�����
	// Parameter: int iHeight ���ָ߶�
	//************************************
	void CreatMark(CString sText,int iHeight);
	//************************************
	// Method:    CreatDzXh
	// FullName:  CDlgMain::CreatDzXh
	// Access:    public 
	// Returns:   void
	// Qualifier: ���ɶ����ߺ�
	// Parameter: std::vector<DzAndXh> vec �����ߺ���Ϣ�洢
	// Parameter: AcGePoint3d ptInsert //�����
	// Parameter: CString sName //��ͷ����
	//************************************
	void CreatDzXh(std::vector<DzAndXh> vec, AcGePoint3d ptInsert,CString sName);

	void GetAllDwgTextAndPosition();//��ȡͼֽ�����п��Ӧ�������Լ������
	void CheckDwgWh();//���λ����Ϣ

	bool CheckWhPostion();//���λ��λ�������Ƿ��ص�

	void CheckDwgDzb();//�����ӱ���Ϣ
	//************************************
	// Method:    CreatMarkToText
	// FullName:  CDlgMain::CreatMarkToText
	// Access:    public 
	// Returns:   void
	// Qualifier:����λ�ű��
	// Parameter: int iHeight �������ֵĸ߶�
	//************************************
	void CreatMarkToText(int iHeight);

	//************************************
	// Method:    ExportDzb
	// FullName:  CDlgMain::ExportDzb
	// Access:    public 
	// Returns:   bool
	// Qualifier:�������ӱ���־��Ϣ
	// Parameter: CString & sExcelPath ������excel��ַ
	//************************************
	bool ExportDzb(CString &sExcelPath);

	//************************************
	// Method:    CreatJxb
	// FullName:  CDlgMain::CreatJxb
	// Access:    public 
	// Returns:   int ���ӱ������
	// Qualifier:���ɶ��ӽ��߱�
	// Parameter: CString sCreatName ��ͷ����
	// Parameter: AcGePoint3d ptInsert �����
	//************************************
	int CreatJxb(CString sCreatName,AcGePoint3d ptInsert);

	//************************************
	// Method:    GetMarkNum
	// FullName:  CDlgMain::GetMarkNum
	// Access:    public 
	// Returns:   CString �����ַ�
	// Qualifier: ��ȡ���ƶ�Ӧ������
	// Parameter: CString sName ��������
	//************************************
	CString GetMarkNum(CString sName);
	void GetMxbInfo();//������ϸ����Ϣ��ȡ
	bool CreatMxb(bool bAddFrameInfo,FrameInfo fm);//�ֻ���ϸ������
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
