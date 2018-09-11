/********************************************************************
�� ���� ����Ԥ��DWGͼ�εĿؼ�
*********************************************************************/
#ifndef _FC_GS_PREVIEW_CTRL_H__
#define _FC_GS_PREVIEW_CTRL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "acgi.h"
#include <math.h>
#include "gs.h"
#include "acgs.h"
#include "acgsmanager.h"
#define GCL_HCURSOR         (-12)

// ����Ԥ��DWGͼ�εĿؼ�
class fcGsPreviewCtrl : public CStatic
{
public:
fcGsPreviewCtrl();
virtual ~fcGsPreviewCtrl();

public:
//��������:����dwg�ļ�����Ԥ��
BOOL Init(LPCTSTR szDwgFile);
//��������:�������ݿ�ָ�뼴��Ԥ�����ݿ��е�ʵ��
BOOL Init(AcDbDatabase *pDb, CString strBlkTblRcd=ACDB_MODEL_SPACE);
// ���ŵ�����ͼֽ�ɼ�
void ZoomE();

void Clear();

protected:
	void InitGS(HINSTANCE hRes); // ��ʼ��ͼ��ϵͳ
	BOOL InitInner(AcDbDatabase *pDb, CString strBlkTblRcd= ACDB_MODEL_SPACE); // �ڲ���ʼ��
	bool GetActiveViewPortInfo (ads_real &height, ads_real &width, AcGePoint3d &target, 
		AcGeVector3d &viewDir, ads_real &viewTwist, bool getViewCenter);
	//��ÿ��е�����ʵ��
	void GetAllEnt(const AcDbObjectId& idBlockRec, AcDbObjectIdArray& IDArray);
	//���ʵ��ķ�Χ
	Acad::ErrorStatus GetEntExtents(const AcDbObjectId& idEnt, AcDbExtents& extents);
	void GetEntExtents(const AcDbObjectIdArray& aridEnt, AcDbExtents& extents);
	void Mid(const AcGePoint3d& pt1, const AcGePoint3d& pt2, AcGePoint3d& ptMid); 
protected:
	//{{AFX_MSG(fcGsPreviewCtrl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	AcDbExtents m_extents; // ͼֽ��Χ 
	HCURSOR m_hPanCursor; // �ƶ�ʱ��ͼ��
	HCURSOR m_hCrossCursor; // ʮ��ͼ��
	HCURSOR m_hOrbitCursor; // ��תͼ��
	AcGsView *m_pView; // ͼ��ϵͳ�е���ͼ����������ͼ�ε�����
	AcGsDevice *m_pDevice; // ͼ��ϵͳ�е��豸��
	AcGsModel *m_pModel;

	bool m_bPanning; // �Ƿ����ƶ�ͼ��״̬
	bool m_bOrbiting; // �Ƿ�����תͼ��״̬
	AcDbDatabase* m_pDb; // ��Ԥ���ռ�󶨵����ݿ� 
	CPoint m_StartPt; // �ƶ�����תʱ�����

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_FC_GS_PREVIEW_CTRL_H__)
