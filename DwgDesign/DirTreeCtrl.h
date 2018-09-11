#pragma once

class CDirTreeCtrl : public CTreeCtrl
{
public:
	CDirTreeCtrl(void);
	~CDirTreeCtrl(void);

public:
	BOOL SetSelPath(LPCTSTR strPath);
	CString GetFullPath(HTREEITEM hItem);  //��ȡȫ�ļ���
	CString GetPath(HTREEITEM hItem);
	LPCTSTR GetSubPath(LPCTSTR strPath);       //��ȡ��Ŀ¼
	BOOL DisPlayTree(LPCTSTR strRoot, BOOL bFile);   //��ʾ��
	BOOL IsValidPath(LPCTSTR strPath);
	void ExpandItem(HTREEITEM hItem, UINT nCode);   //չ����
	
	HTREEITEM SearchSiblingItem(HTREEITEM hItem, LPCTSTR strText);
	BOOL FindSubDir(LPCTSTR strPath);     //������Ŀ¼
	HTREEITEM AddItem(HTREEITEM hParent, LPCTSTR strPath); //�����Ŀ
	void DisplayPath(HTREEITEM hParent, LPCTSTR strPath);  //չ��Ŀ¼
	BOOL GetSysImgList();   //��ȡϵͳͼ��
	BOOL DisplayDrives();                //��ʾ����
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);

	void SetParentPath(LPCTSTR strPath);//���÷�·��
	void SetContent(LPCTSTR strContent);
	bool readContent(LPCTSTR strFileName);
	//ɾ���ļ���
	bool DelFolder(CString strPath);
	bool RenameFolder(CString strFromPath, CString strToPath);
	DECLARE_MESSAGE_MAP();


private:
	CImageList m_ImageList;
	CString m_strRoot;       
	BOOL m_bFile;         //�ļ���Ŀ¼��־
	CString m_strError;              //������Ϣ
	CString m_strParent;
	bool m_bFlag;
	CString m_strContent;//�ļ�����
};
