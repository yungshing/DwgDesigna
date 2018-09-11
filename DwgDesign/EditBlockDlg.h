#pragma once
#include "resource.h"
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "fcGsPreviewCtrl.h"

// CEditBlockDlg �Ի���

class CEditBlockDlg : public CAcUiDialog
{
	DECLARE_DYNAMIC(CEditBlockDlg)

public:
	CEditBlockDlg(AcDbObjectId entId,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditBlockDlg();

// �Ի�������
	enum { IDD = IDD_DLG_EDITBLOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	AcDbObjectId m_entId;//����ɾ�������
	CAcUiComboBox m_cmbTh;//�滻����ͼ��ѡ��
	fcGsPreviewCtrl m_fc;
	BOOL m_bJx;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCmbTh();
	afx_msg void OnBnClickedOk();

};
