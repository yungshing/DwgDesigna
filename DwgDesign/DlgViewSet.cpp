// DlgViewSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgViewSet.h"
#include "afxdialogex.h"
#include "DlgMain.h"

CDlgViewSet *pSetViewDlg = NULL;
// CDlgViewSet �Ի���

IMPLEMENT_DYNAMIC(CDlgViewSet, CAcUiDialog)

CDlgViewSet::CDlgViewSet(CWnd* pParent /*=NULL*/)
: CAcUiDialog(CDlgViewSet::IDD, pParent)
{

}

CDlgViewSet::~CDlgViewSet()
{
}

void CDlgViewSet::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_VIEW, m_cmb_view);
}


BEGIN_MESSAGE_MAP(CDlgViewSet, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnACADKeepFocus)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_SETVIEW, &CDlgViewSet::OnBnClickedBtnSetview)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgViewSet::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgViewSet::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgViewSet::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDlgViewSet ��Ϣ�������


void CDlgViewSet::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���
	delete this;
	if (pSetViewDlg != NULL)
	{
		pSetViewDlg = NULL;
	}
	CAcUiDialog::PostNcDestroy();
}


void CDlgViewSet::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CAcUiDialog::OnClose();
	DestroyWindow();
}


BOOL CDlgViewSet::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	CIniFile ini(GetIniPath());
	CString sViewTemp;
	ini.GetValueOfKey(_T("DL"), _T("VIEW"), sViewTemp);
	FillCombo(m_cmb_view, sViewTemp, _T(","));
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

afx_msg LRESULT CDlgViewSet::OnACADKeepFocus(WPARAM, LPARAM)
{
	return keepTheFocus() ? TRUE : FALSE;
	//	return TRUE;
}

BOOL CDlgViewSet::keepTheFocus()
{
	POINT pt;
	GetCursorPos(&pt);
	CRect rec;
	GetWindowRect(&rec);
	bool b = PtInRect(&rec, pt);
	if (b)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CDlgViewSet::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN&&pMsg->wParam)
	{
		return TRUE;
	}
	else
	{
		return CAcUiDialog::PreTranslateMessage(pMsg);
	}

}

void CDlgViewSet::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CAcUiDialog::OnCancel();
}



void CDlgViewSet::OnBnClickedBtnSetview()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	GetDlgItemText(IDC_CMB_VIEW, m_sCurrentView);
	if (m_sCurrentView == _T(""))
	{
		AfxMessageBox(_T("��ͼ��Ϣ��ȡΪ��"));
		return;
	}
	acDocManager->lockDocument(curDoc());
	AcDbObjectIdArray idArr;
	bool b = GetSelection(idArr, _T("\nѡ����Ҫ������ͼ��ʵ��."));
	if (b)
	{
		for (int i = 0; i < idArr.length(); i++)
		{
			AcDbEntity *pEnt = NULL;
			Acad::ErrorStatus es;
			es = acdbOpenAcDbEntity(pEnt, idArr[i], AcDb::kForWrite);
			if (es != eOk)
			{
				continue;
			}
			CDwgDatabaseUtil::SetXdata(_T("��ͼ"), m_sCurrentView, pEnt);
			pEnt->close();
		}
	}
	acDocManager->unlockDocument(curDoc());
	UpdateData(FALSE);
}

extern CDlgMain* pDlg;

void CDlgViewSet::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	PostNcDestroy();
	int nRet = AfxMessageBox(_T("��ȷ����ͼ�Ǵ�΢������ṹ���ģ���е��������Ҹ�ͼֽ����ͼ��"), MB_YESNO);
	if (nRet == 6)
	{
		pDlg->ShowWindow(SW_SHOW);
	}
}


void CDlgViewSet::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	acDocManager->lockDocument(curDoc());

	if (m_ViewIdArr.length() != 0)
	{
		UnHighLight(m_ViewIdArr);
	}
	m_ViewIdArr.removeAll();
	GetDlgItemText(IDC_CMB_VIEW, m_sCurrentView);

	struct resbuf *rb;
	rb = acutBuildList(1001, TEXT("��ͼ"), RTNONE);
	ads_name textArr;
	acedSSGet(TEXT("X"), NULL, NULL, rb, textArr);
	long Lenth;
	acedSSLength(textArr, &Lenth);
	for (int i = 0; i < Lenth; i++)
	{
		ads_name ent;
		acedSSName(textArr, i, ent);
		AcDbObjectId objId;
		acdbGetObjectId(objId, ent);
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt, objId, AcDb::kForWrite);
		if (es != eOk)
		{
			continue;
		}
		if (!pEnt->isKindOf(AcDbBlockReference::desc()))
		{
			pEnt->close();
			continue;
		}
		CString sEntView;
		CDwgDatabaseUtil::getXdata(_T("��ͼ"), sEntView, pEnt);
		if (sEntView == m_sCurrentView)
		{
			m_ViewIdArr.append(objId);
		}

		pEnt->close();
	}
	acutRelRb(rb);
	acedSSFree(textArr);
	HighLight(m_ViewIdArr);
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	this->GetParent()->SetFocus();
	this->SetFocus();
}


void CDlgViewSet::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_ViewIdArr.length() == 0)
	{
		return;
	}
	acDocManager->lockDocument(curDoc());
	UnHighLight(m_ViewIdArr);
	acDocManager->unlockDocument(curDoc());
	acTransactionManagerPtr()->flushGraphics();
	acedUpdateDisplay();
	this->GetParent()->SetFocus();
	this->SetFocus();
}
