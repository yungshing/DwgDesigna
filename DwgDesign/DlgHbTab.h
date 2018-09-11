#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "excel9.h"
#include "rwExcel.h"
#include <algorithm>

// CDlgHbTab �Ի���
struct DesginTabInfo
{
	CString Yqzjhcl;//Ԫ���������ϣ�����ɸѡ������������������
	CString xh;
	CString dljt;
	CString wzdm;
	CString wh;
	CString dybs;
	CString dz;
	CString tx;
	CString dljt2;
	CString wzdm2;
	CString wh2;
	CString dybs2;
	CString dz2;
	CString tx2;
	CString xlcl;
	CString xlwzdm;
	CString cd;
	CString dllx;

	bool operator<(const DesginTabInfo &b)
	{
		return this->wzdm2 < b.wzdm2;
	}
};

struct FjMxbInfo
{
	CString yqjhcl;
	CString wzdm;
	CString mc;
	CString xh;
	CString dwzl;
	CString yl;
};

struct WzdmNameXh
{
	CString wzdm;
	CString mc;
	CString xh;
};

struct LjqmcYqj//���������ƺ�Ԫ����
{
	CString ljqmc;
	CString yqj;
};

class CDlgHbTab : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgHbTab)

public:
	CDlgHbTab(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHbTab();

// �Ի�������
	enum { IDD = IDD_DLG_HBTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_sDlt;//��·ͼ
	CString m_sGyk;//���տ�
	CProgressCtrl m_proGress;
	CString m_sW;
	CString m_sBm;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
private:
	vector<DesginTabInfo> m_vecDesginInfo;//�洢��ȡ������Ʊ���Ϣ
	vector<FjMxbInfo> m_vecFjInfo;//������Ϣ��ȡ
	map<CString, WzdmNameXh> m_mapYqAndMc;//A�� �Լ�A�˵�����Ϣ
	map<CString, LjqmcYqj> m_mapBdinfo;//B�� ���ʴ����Լ�����
	vector<DesginTabInfo> GetDesInfoToWzdm(CString YQJCL,CString WZDM);
	void ExportDesginInfo();
	BOOL m_bSp;//�Ƿ�����Ƶ����
	BOOL m_bAorB;//�жϴ�A���������Ϣ����B  Ture��ӦA
public:
	virtual BOOL OnInitDialog();
};
