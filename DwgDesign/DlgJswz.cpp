//-----------------------------------------------------------------------------
//----- DlgJswz.cpp : Implementation of CDlgJswz
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "DlgJswz.h"
/*#include "Utility.h"*/
#include <shlwapi.h>

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CDlgJswz, CAcUiDialog)

BEGIN_MESSAGE_MAP(CDlgJswz, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CDlgJswz::OnNMClickTree1)
	ON_BN_CLICKED(IDOK, &CDlgJswz::OnBnClickedOk)
	//ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgJswz::OnBnClickedButtonSave)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CDlgJswz::OnNMRClickTree1)
	ON_COMMAND(ID_JS_ADD, &CDlgJswz::OnMenuAdd)
	ON_COMMAND(ID_JS_DELETE, &CDlgJswz::OnMenuDel)
	ON_COMMAND(ID_JS_EDIT, &CDlgJswz::OnMenuEdit)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE1, &CDlgJswz::OnTvnBeginlabeleditTree1)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, &CDlgJswz::OnTvnEndlabeleditTree1)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_COPY, &CDlgJswz::OnCopy)
	ON_COMMAND(ID_PASTE, &CDlgJswz::OnPaste)
	ON_COMMAND(ID_ADD_PATH, &CDlgJswz::OnMenuAddPath)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CDlgJswz::CDlgJswz (CWnd *pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CDlgJswz::IDD, pParent, hInstance) {
	AfxInitRichEdit();
}

//-----------------------------------------------------------------------------
void CDlgJswz::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_strSearch);
	DDX_Control(pDX, IDC_RICHEDIT2_UPDATE, m_EditUpdate);
}

//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CDlgJswz::OnAcadKeepFocus (WPARAM, LPARAM) {
	return (TRUE) ;
}


BOOL CDlgJswz::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	CAcUiDialog::OnInitDialog();
	CenterWindow(acedGetAcadDwgView());
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_TreeCtrl.ModifyStyle(0, TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES | TVS_EDITLABELS);
	m_strParentPath = /*MyBaseUtils::GetAppPath()*/CAppDirectoryUtil::GetParentDirectory()+_T("\\");
	m_TreeCtrl.SetParentPath(m_strParentPath);
	m_TreeCtrl.SetContent(m_strSearch);
	m_TreeCtrl.DisPlayTree(_T("��������"), TRUE);
	HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
	m_TreeCtrl.Expand(hRoot, TVE_EXPAND);
	//	m_TreeCtrl.Expand(hChild, TVE_EXPAND);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//if (!m_strSearch.IsEmpty())
	//{
	//	HTREEITEM hItem = m_TreeCtrl.GetRootItem();
	//	hItem = FindItem(hItem);
	//	if (hItem == NULL)
	//	{
	//		HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
	//		HTREEITEM hChild = m_TreeCtrl.GetChildItem(hRoot);
	//		m_TreeCtrl.Expand(hRoot, TVE_EXPAND);
	//		m_TreeCtrl.Expand(hChild, TVE_EXPAND);

	//		HTREEITEM hNextItem = m_TreeCtrl.GetChildItem(hChild);
	//		m_strFileName = m_TreeCtrl.GetFullPath(hNextItem) + _T(".tj");
	//	}
	//	else
	//	{
	//		m_strSearch = m_TreeCtrl.GetItemText(hItem);	
	//		m_TreeCtrl.SelectItem(hItem); //����ѡ�н��
	//		m_strFileName = m_TreeCtrl.GetFullPath(hItem) + _T(".tj");
	//	}
	//}
	//else
	//{
	//	HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
	//	HTREEITEM hChild = m_TreeCtrl.GetChildItem(hRoot);
	//	m_TreeCtrl.Expand(hRoot, TVE_EXPAND);
	//	m_TreeCtrl.Expand(hChild, TVE_EXPAND);

	//	HTREEITEM hNextItem = m_TreeCtrl.GetChildItem(hChild);
	//	m_strFileName = m_TreeCtrl.GetFullPath(hNextItem) + _T(".tj");
	//}

	//��ʼ���ÿ�
	if (OpenClipboard())
	{
		HGLOBAL clipBuffer;
		TCHAR* Buffer;
		//EmptyClipboard();
		CloseClipboard();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

HTREEITEM CDlgJswz::FindItem(HTREEITEM ht)
{
	CString strText;
	HTREEITEM hItem = NULL;
	m_TreeCtrl.Expand(ht,TVE_EXPAND);
	hItem = m_TreeCtrl.GetNextItem(ht,TVGN_NEXTVISIBLE);
	if(hItem != NULL)
	{
		strText = m_TreeCtrl.GetItemText(hItem);
		if (strText.CompareNoCase(m_strSearch) == 0)
		{
			return hItem;
		}
		hItem = FindItem(hItem);
	}
	else
		return NULL;
	return hItem;
}


vector<CString> CDlgJswz::readStringFromFile(CString strFile)
{
	vector<CString> tmpVec;
	CStdioFile File;
	if (!File.Open(strFile, CFile::modeRead | CFile::typeText)) 
	{
		return tmpVec;
	}
	CString buffer;
	while (File.ReadString(buffer))
	{
		tmpVec.push_back(buffer);
	}
	File.Close();
	return tmpVec;
}

BOOL CDlgJswz::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ((WM_KEYDOWN == pMsg-> message) && 
		(VK_RETURN ==  pMsg-> wParam))
	{
		if ( GetDlgItem(IDC_EDIT_SEARCH) == GetFocus())
		{
			GetDlgItem(IDC_EDIT_SEARCH)->GetWindowText(m_strSearch);
			m_TreeCtrl.SetContent(m_strSearch);
			m_TreeCtrl.DisPlayTree(_T("��������"), TRUE);
			HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
			m_TreeCtrl.Expand(hRoot, TVE_EXPAND);
			return FALSE;
		}
	}
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam)
		{
		case VK_F2:
			OnMenuEdit();
			break;
		default:
			return CAcUiDialog::PreTranslateMessage(pMsg);
		}
		return TRUE;
	}
	return CAcUiDialog::PreTranslateMessage(pMsg);
}

void CDlgJswz::UpdateMergeTreeCheck(const HTREEITEM hParent, const BOOL bCheck)
{
	CString strItem, strFileName;
	if (m_TreeCtrl.ItemHasChildren(hParent))
	{
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = m_TreeCtrl.GetChildItem(hParent);
		while (hChildItem != NULL)
		{
			//�ݹ��ȡ��ǰ�ڵ��µ��ӽڵ�
			m_TreeCtrl.SetCheck(hChildItem,bCheck);
			if (!m_TreeCtrl.ItemHasChildren(hChildItem))
			{
				strItem = m_TreeCtrl.GetItemText(hChildItem) ;//��ýڵ�ֵ
				strFileName = m_TreeCtrl.GetFullPath(hChildItem) + _T(".TJ");
				if (bCheck)//��ӵ��ұ�
				{
					m_DataMap.insert(make_pair(strFileName, 1));
				}
				else//���ұ�������ɾ��
				{
					map<CString,int>::iterator key = m_DataMap.find(strFileName);  
					if(key!=m_DataMap.end())  
					{  
						m_DataMap.erase(key);  
					}  
				}
			}

			UpdateMergeTreeCheck(hChildItem,bCheck);
			hNextItem = m_TreeCtrl.GetNextItem(hChildItem, TVGN_NEXT);
			hChildItem = hNextItem;
		}
	}
}
void CDlgJswz::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint point;
	GetCursorPos(&point);//����������λ��
	m_TreeCtrl.ScreenToClient(&point);//ת��Ϊ�ͻ�����
	UINT uFlags;

	HTREEITEM CurrentItem;
	CurrentItem=m_TreeCtrl.HitTest(point,&uFlags);//��õ�ǰ����ڵ��ITEM
	//��øýڵ�ĸ��ڵ�
	// HTREEITEM ParentItem=m_videotree.GetParentItem(CurrentItem);
	CString strItem;
	if (uFlags & TVHT_ONITEMSTATEICON)
	{
		BOOL bCheck = !m_TreeCtrl.GetCheck(CurrentItem);
		if (m_TreeCtrl.ItemHasChildren(CurrentItem))
		{
			UpdateMergeTreeCheck(CurrentItem, bCheck);
		}
		else
		{
			m_TreeCtrl.SetCheck(CurrentItem, bCheck);
			strItem = m_TreeCtrl.GetItemText(CurrentItem) ;//��ýڵ�ֵ
			CString strFileName = m_TreeCtrl.GetFullPath(CurrentItem) + _T(".TJ");
			if (bCheck)//��ӵ��ұ�
			{
				m_DataMap.insert(make_pair(strFileName, 1));
			}
			else//���ұ�������ɾ��
			{
				map<CString,int>::iterator key = m_DataMap.find(strFileName);  
				if(key!=m_DataMap.end())  
				{  
					m_DataMap.erase(key);  
				}  
			}	
			m_TreeCtrl.SetCheck(CurrentItem, !bCheck);
		}
		
		//��ʾ����
		displayText();
	}
}


void CDlgJswz::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFile;
	GetDlgItem(IDC_RICHEDIT2_UPDATE)->GetWindowText(strFile);
	if (strFile.Right(1).CompareNoCase(_T("\n")) !=0)
	{
		strFile+= _T("\n");
	}
	strFile.Replace(_T("\\"), _T("\\\\"));
	AcGePoint3d pt;
	BeginEditorCommand();
	int nRet = acedGetPoint(NULL, _T("\n�ƶ�����㣺"), asDblArray(pt));
	if (nRet != RTNORM)
	{
		CancelEditorCommand();
		return;
	}
	AcDbObjectId textId = AcDbObjectId::kNull;
	double dlen,dTemp;
	dlen = dTemp = 0.0;
	int nFind = 0;
	CString strTemp,strNum;
	int i=1;
	AcGePoint3d cenPt;
	cenPt = pt;
	AcDbObjectIdArray objIdArr;
	CString strText;
	while (1)
	{
		nFind = strFile.Find(_T("\n"));
		if (nFind < 0)
		{
			break;
		}
		strTemp = strFile.Left(nFind);
		if (strTemp.GetLength() == 1)
		{
			strTemp.Trim();
			if (strTemp.IsEmpty())
			{
				strText += strTemp + _T("\n");
				pt.y -= 5;
				strFile = strFile.Right(strFile.GetLength()-nFind-1);
				continue;
			}
		}
		strNum.Format(_T("%d."), i);
		strTemp = strNum + strTemp + _T("\n");
		strText += strTemp;
		strFile = strFile.Right(strFile.GetLength()-nFind-1);
		i++;
		objIdArr.append(textId);
	}

// 	m_dJsTxtHeight = gGlobal.GetIniValue(_T("����Ҫ��"), _T("����Ҫ���ָ�"), 0);
// 	if (m_dJsTxtHeight < GeTol)
// 	{
 		m_dJsTxtHeight = 4.0;
// 	}
// 	m_dTextGap = gGlobal.GetIniValue(_T("����Ҫ��"), _T("���ּ��"), 0);
// 	if (m_dTextGap < GeTol)
// 	{
 		m_dTextGap = 5;
// 	}
// 	m_dTxtHeight = gGlobal.GetIniValue(_T("����Ҫ��"), _T("��������"), 0);
// 	if (m_dTxtHeight < GeTol)
// 	{
 		m_dTxtHeight = 3.0;
// 	}
//	AcDbObjectId textStyleId = CUtility::getStyleIdByiniFile(_T("��������"), _T("1"));
//	textId = MyDrawEntity::DrawMText(pt, strText, m_dTxtHeight, textStyleId);
	AcDbObjectId idTextStyle;
	CString sTextStyle;
	CIniFile ini(GetTextIniPath());
	ini.GetValueOfKey(_T("��������"), _T("1"),sTextStyle);
	std::vector<CString> vecTemp;
	CStringUtil::Split(sTextStyle, _T(","), vecTemp);
	CTextStyleUtil::Add(vecTemp[0], vecTemp[1], vecTemp[2]);
	idTextStyle = CTextStyleUtil::GetAt(vecTemp[0]);
	textId = CTextUtil::AddMText(pt, strText,idTextStyle,m_dTxtHeight);
	objIdArr.append(textId);
	dlen = OpenObjAndGetLength(textId);

// 	BOOL bDraw = (int)gGlobal.GetIniValue(_T("����Ҫ��"), _T("�����Ʊ�ͷ"), 0);
// 	if (!bDraw)
// 	{
		cenPt.x = pt.x + dlen/2;
		cenPt.y = pt.y + m_dTextGap;
		cenPt.z = 0;
		AcDbObjectId objId = CTextUtil::AddText(cenPt, _T("����Ҫ��"), idTextStyle, m_dJsTxtHeight);
		objIdArr.append(objId);
//	}
	
// 	int nUser = 0;
// 	MyBaseUtils::GetVar(_T("USERI5"), &nUser);
// 	CString strGroupName;
// 	strNum.Format(_T("%d"), nUser);
// 	strGroupName = JSWZ + strNum;
// 	MyDrawEntity::MakeGroup(objIdArr, false, strGroupName);
// 	nUser++;
// 	MyBaseUtils::SetVar(_T("USERI5"), nUser);
	CompleteEditorCommand();
	CAcUiDialog::OnOK();
}

void CDlgJswz::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	CString strFile,strTemp;
	GetDlgItem(IDC_RICHEDIT2_UPDATE)->GetWindowText(strFile);
	if (strFile.IsEmpty())
	{
		AfxMessageBox(_T("�༭����û������"));
		return;
	}

	CString strCurrentPath;
	strCurrentPath = CAppDirectoryUtil::GetCurrentDirectoryW()+ _T("��������\\");
	
	struct resbuf* result = NULL;
	int status = acedGetFileNavDialog(_T("�������ֱ���Ŀ¼"), strCurrentPath, _T("TJ"), _T("�����ļ�"), 1, &result);
	if (status == RTNORM)
	{
		strCurrentPath = result->resval.rstring;
		acutRelRb( result );
	}
	else
	{
		acutRelRb( result );
		return;
	}
	

	CStdioFile File;
	if(!File.Open(strCurrentPath,CFile::modeReadWrite))     
	{     
		if (!File.Open(strCurrentPath, CFile::modeCreate | CFile::modeReadWrite| CFile::typeText)) 
		{
			return;
		} 
	}    	
	int nFind = 0;
	while (1)
	{
		nFind = strFile.Find(_T("\n"));
		if (nFind < 0)
		{
			break;
		}
		strTemp = strFile.Left(nFind);
		if (strTemp.GetLength() == 1)
		{
			strTemp.Trim();
			if (strTemp.IsEmpty())
			{
				strFile = strFile.Right(strFile.GetLength()-nFind-1);
				File.SeekToEnd();
				continue;
			}
		}
		File.SeekToEnd();
		File.WriteString(strTemp);
		strFile = strFile.Right(strFile.GetLength()-nFind-1);
	}
	
	File.Close();

	//m_TreeCtrl.UpdateWindow();
	m_TreeCtrl.SetParentPath(m_strParentPath);
	m_TreeCtrl.SetContent(m_strSearch);
	m_TreeCtrl.DisPlayTree(_T("��������"), TRUE);
	HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
	m_TreeCtrl.Expand(hRoot, TVE_EXPAND);
}

void CDlgJswz::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	LPPOINT lpoint=new tagPOINT;   
	::GetCursorPos(lpoint);                                //������

	CPoint point = *lpoint;
	::ScreenToClient(m_TreeCtrl.m_hWnd,  &point);

	HTREEITEM Item;
	UINT nFlag = TVHT_ONITEM; // ���� Item ���һ�ʱ
	Item = m_TreeCtrl.HitTest( point, &nFlag );
	m_TreeCtrl.SelectItem(Item);
	if (!Item)
	{
		return;
	}
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_MENU);
	CMenu* popMenu = menu.GetSubMenu(0);
	if (m_TreeCtrl.ItemHasChildren(Item))//�ļ���
	{
		popMenu->EnableMenuItem(ID_ADD_PATH, MF_ENABLED);
		popMenu->EnableMenuItem(ID_JS_ADD, MF_GRAYED);
	}
	else
	{
		popMenu->EnableMenuItem(ID_ADD_PATH, MF_GRAYED);
		popMenu->EnableMenuItem(ID_JS_ADD, MF_ENABLED);
	}
	popMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, lpoint->x, lpoint->y, this, NULL);
	*pResult = 0;
}


void CDlgJswz::OnMenuAdd()
{
	CString strFile,strTemp;
	GetDlgItem(IDC_RICHEDIT2_UPDATE)->GetWindowText(strFile);
	if (strFile.IsEmpty())
	{
		AfxMessageBox(_T("�༭����û������"));
		return;
	}

	CString strCurrentPath;
	//strCurrentPath = MyBaseUtils::GetAppPath() + _T("��������\\");
	strCurrentPath =m_TreeCtrl.GetFullPath(m_TreeCtrl.GetSelectedItem());
	strCurrentPath += _T("\\");

	struct resbuf* result = NULL;
	int status = acedGetFileNavDialog(_T("�������ֱ���Ŀ¼"), strCurrentPath, _T("TJ"), _T("�����ļ�"), 1, &result);
	if (status == RTNORM)
	{
		strCurrentPath = result->resval.rstring;
		acutRelRb( result );
	}
	else
	{
		acutRelRb( result );
		return;
	}
	

	CStdioFile File;
	if(!File.Open(strCurrentPath,CFile::modeReadWrite))     
	{     
		if (!File.Open(strCurrentPath, CFile::modeCreate | CFile::modeReadWrite| CFile::typeText)) 
		{
			return;
		} 
	}    	
	int nFind = 0;
	while (1)
	{
		nFind = strFile.Find(_T("\n"));
		if (nFind < 0)
		{
			if (!strTemp.IsEmpty())
			{
				File.SeekToEnd();
				File.WriteString(strTemp);
			}
			
			break;
		}
		strTemp = strFile.Left(nFind);
		if (strTemp.GetLength() == 1)
		{
			strTemp.Trim();
			if (strTemp.IsEmpty())
			{
				strFile = strFile.Right(strFile.GetLength()-nFind-1);
				File.SeekToEnd();
				continue;
			}
		}
		File.SeekToEnd();
		File.WriteString(strTemp);
		strFile = strFile.Right(strFile.GetLength()-nFind-1);
	}
	
	File.Close();

	m_TreeCtrl.SetParentPath(m_strParentPath);
	m_TreeCtrl.SetContent(m_strSearch);
	m_TreeCtrl.DisPlayTree(_T("��������"), TRUE);
	HTREEITEM hRoot = m_TreeCtrl.GetRootItem();
	m_TreeCtrl.Expand(hRoot, TVE_EXPAND);
}

void CDlgJswz::OnMenuDel()
{	
	CString strItem,strFileName;
	HTREEITEM CurrentItem;

	CurrentItem = m_TreeCtrl.GetSelectedItem();
	if (m_TreeCtrl.ItemHasChildren(CurrentItem))
	{
		AfxMessageBox(_T("�����������ɾ���ļ���"));
	}
	else
	{
		strFileName = m_TreeCtrl.GetFullPath(CurrentItem);
		if (::PathIsDirectory(strFileName))
		{
			m_TreeCtrl.DelFolder(strFileName);
		}
		else
		{
			strFileName += _T(".TJ");
			::DeleteFile(strFileName);
		}
		m_TreeCtrl.DeleteItem(CurrentItem);
	}
}

void CDlgJswz::OnMenuEdit()
{
	m_TreeCtrl.ModifyStyle(NULL,TVS_EDITLABELS);
	HTREEITEM hti;
	hti = m_TreeCtrl.GetSelectedItem();
	m_TreeCtrl.EditLabel(hti);
}



void CDlgJswz::OnTvnBeginlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	CEdit *pEdit;

	pEdit = m_TreeCtrl.GetEditControl();
	pEdit->SetLimitText(100);	
	*pResult = 0;
}

void CDlgJswz::OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	TV_DISPINFO *ptvinfo;

	// Called at exit from Edit Mode
	ptvinfo = (TV_DISPINFO *)pNMHDR;
	CString strPre,strCur,strpreFileName,strCurFileName;
	bool bIsDir = false;
	if (ptvinfo->item.pszText != NULL)
	{		
		strpreFileName = m_TreeCtrl.GetFullPath(m_TreeCtrl.GetSelectedItem());
		if (::PathIsDirectory(strpreFileName))
		{
			//��ô����һ��Ŀ¼
			bIsDir = true;
		}
		else
		{
			strpreFileName +=  _T(".TJ");
		}

		ptvinfo->item.mask = TVIF_TEXT;
		m_TreeCtrl.SetItem(&ptvinfo->item);
		if (bIsDir)
		{
			strCurFileName = m_TreeCtrl.GetFullPath(m_TreeCtrl.GetSelectedItem());
			m_TreeCtrl.RenameFolder(strpreFileName, strCurFileName);
		}
		else
		{
			strCurFileName = m_TreeCtrl.GetFullPath(m_TreeCtrl.GetSelectedItem()) + _T(".TJ");
			::CFile::Rename(strpreFileName, strCurFileName);
		}
	}

	*pResult = TRUE; // TRUE => Accept the label
}


void CDlgJswz::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������
	CRect rect1;
	LPPOINT lpoint=new tagPOINT;   
	::GetCursorPos(lpoint); 
	GetDlgItem(IDC_RICHEDIT2_UPDATE)->GetWindowRect(&rect1);
	if (!OpenClipboard())
	{
		return;
	}
	if (rect1.PtInRect(point))
	{
		CMenu* pPopup;
		CMenu popMenu;
		popMenu.LoadMenu(IDR_MENU_EDIT);
		pPopup = popMenu.GetSubMenu(0);

		TCHAR* buffer;
		CString strFromClipboard;
		HANDLE hData = GetClipboardData(CF_UNICODETEXT);
		buffer = (TCHAR*)GlobalLock(hData);
		strFromClipboard = buffer;
		if (strFromClipboard.IsEmpty())
		{
			pPopup->EnableMenuItem(ID_COPY, MF_ENABLED);
			pPopup->EnableMenuItem(ID_PASTE, MF_GRAYED);
		}
		else
		{
			pPopup->EnableMenuItem(ID_COPY, MF_GRAYED);
			pPopup->EnableMenuItem(ID_PASTE, MF_ENABLED);
		}
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, lpoint->x, lpoint->y, this, NULL);
		pPopup->Detach();
		pPopup->DestroyMenu();
	}
	CloseClipboard();
}


void CDlgJswz::OnCopy()
{
	// TODO: �ڴ���������������
	long nStart,nEnd;
	m_EditUpdate.GetSel(nStart, nEnd);
	//m_EditUpdate.Copy();
	if (nStart == nEnd)
	{
		return;
	}
	else
	{
		CString strTemp,strTemp1,strTemp2,strTemp3;
		CString source;
		m_EditUpdate.GetWindowText(strTemp);
		
		int nSize1 = getEnterCode(nStart, strTemp);
		int nSize2 = getEnterCode(nEnd, strTemp);

		strTemp = strTemp.Mid(nStart + nSize1, nEnd+nSize2-nStart-nSize1);
		
		//strTemp = strTemp1 - strTemp2;
		if (OpenClipboard())
		{
			HGLOBAL clipBuffer;
			TCHAR* Buffer;
			EmptyClipboard();
			clipBuffer = GlobalAlloc(GMEM_MOVEABLE, strTemp.GetLength()*2+2);
			Buffer = (TCHAR*)GlobalLock(clipBuffer);
			_tcscpy(Buffer, LPCTSTR(strTemp));
			GlobalUnlock(clipBuffer);
			SetClipboardData(CF_UNICODETEXT, clipBuffer);//unicode����
			CloseClipboard();
		}
	}
}


void CDlgJswz::OnPaste()
{
	// TODO: �ڴ���������������
	TCHAR* buffer = NULL;
	CString strFromClipboard;
	if (OpenClipboard())
	{
		HANDLE hData = GetClipboardData(CF_UNICODETEXT);
		buffer = (TCHAR*)GlobalLock(hData);
		strFromClipboard = buffer;
		GlobalUnlock(hData);
		CloseClipboard();
	}
	if (!strFromClipboard.IsEmpty())
	{	
		m_EditUpdate.Paste();
		//ճ��һ�κ��������
		if (OpenClipboard())
		{
			HGLOBAL clipBuffer;
			TCHAR* Buffer;
			EmptyClipboard();
			CloseClipboard();
		}
	}
}

void CDlgJswz::OnMenuAddPath()
{
	CString strItem,strFileName;
	HTREEITEM CurrentItem, hti;

	CurrentItem = m_TreeCtrl.GetSelectedItem();
	
	CString strPath = m_TreeCtrl.GetFullPath(CurrentItem);
	strPath += _T("\\�½��ļ���");
	CString strTemp = strPath;
	int nIndex = 1;
	CString strNo;
	while (PathFileExists(strTemp))
	{
		strNo.Format(_T("%d"), nIndex);
		strTemp = strPath + strNo;
		nIndex++;
	}
	strPath = strTemp;
	::CreateDirectory(strPath, NULL);
	hti = m_TreeCtrl.AddItem(CurrentItem, strPath);
	m_TreeCtrl.SelectItem(hti);
	m_TreeCtrl.EditLabel(hti);
}

int CDlgJswz::getEnterCode(int nFlag, CString strText)
{
	int nCout = 0;
	CString strTemp;
	int i=0;
	int nFind = 0;
	while (1)
	{
		nFind = strText.Find(_T("\n"));
		if (nFind < 0)
		{
			break;
		}
		if (nFind > nFlag)
		{
			break;
		}
		nFlag -= nFind;
		strTemp = strText.Left(nFind);
		if (strTemp.GetLength() == 1)
		{
			strTemp.Trim();
			if (strTemp.IsEmpty())
			{
				strText = strText.Right(strText.GetLength()-nFind-1);
				continue;
			}
		}
		strText = strText.Right(strText.GetLength()-nFind-1);
		i++;
	} ;

	return i;
}

void CDlgJswz::displayText()
{
	CString strFile;
	m_EditUpdate.SetWindowText(_T(""));//�ÿ�
	for (map<CString, int>::iterator iTer = m_DataMap.begin(); iTer != m_DataMap.end(); ++iTer)
	{
		vector<CString> tmpVec;
		strFile = iTer->first;
		tmpVec = readStringFromFile(strFile);
		m_EditUpdate.SetTargetDevice(NULL,0);
		int i=1;
		for (vector<CString>::iterator iter = tmpVec.begin(); iter != tmpVec.end(); ++iter)
		{
			m_EditUpdate.SetSel(-1, -1);
			m_EditUpdate.ReplaceSel(*iter);
			m_EditUpdate.SetSel(-1, -1);
			m_EditUpdate.ReplaceSel(_T("\n"));
		}
		m_EditUpdate.ShowScrollBar(SB_VERT,FALSE);
		int nFirstVisible = m_EditUpdate.GetFirstVisibleLine();
		if (nFirstVisible > 0)
		{
			m_EditUpdate.LineScroll(-nFirstVisible, 0);
		}
	}
}
