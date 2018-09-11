#include "StdAfx.h"
#include "BlockJig.h"

CJigEntity::CJigEntity(AcDbObjectId idBlock,FrameInfo info)
{
	m_idBlock = idBlock;
	m_frameInfo = info;
}

CJigEntity::~CJigEntity()
{

}

void CJigEntity::DrawOrAddSubEnts(AcGiWorldDraw * mode)
{
	AcDbBlockReference *pRef = new AcDbBlockReference(m_ptInsert, m_idBlock);
	if (mode!=NULL)
	{
		pRef->worldDraw(mode);
		delete pRef;
		pRef = NULL;
	}
	else
	{
		delete pRef;
		pRef = NULL;
		AcDbObjectId idTemp=CBlockUtil::InsertBlockRefWithAttribute(m_idBlock, m_ptInsert);
		AcDbBlockReference *pRefTemp = NULL;
		acdbOpenObject(pRefTemp, idTemp, AcDb::kForWrite);
		CBlockUtil::SetBlockRefAttribute(pRefTemp, _T("��Ʒ���1"), m_frameInfo.CPBH);
		CBlockUtil::SetBlockRefAttribute(pRefTemp, _T("��Ʒ���2"), m_frameInfo.CPBH);
		CBlockUtil::SetBlockRefAttribute(pRefTemp, _T("���ʦ"), m_frameInfo.SJS);
		CBlockUtil::SetBlockRefAttribute(pRefTemp, _T("��Ʒ����"), m_frameInfo.CPMC);
		CBlockUtil::SetBlockRefAttribute(pRefTemp, _T("���ؼ�"), m_frameInfo.GZJ);
		CDwgDatabaseUtil::SetXdata(_T("��Ʒ���"), m_frameInfo.CPBH, pRefTemp);
		CDwgDatabaseUtil::SetXdata(_T("��Ŀ�ȼ�"), m_frameInfo.XMDJ, pRefTemp);
		CDwgDatabaseUtil::SetXdata(_T("���ʦ"), m_frameInfo.SJS, pRefTemp);
		CDwgDatabaseUtil::SetXdata(_T("��Ŀ�׶�"), m_frameInfo.XMJD, pRefTemp);
		CDwgDatabaseUtil::SetXdata(_T("��Ʒ����"), m_frameInfo.CPMC, pRefTemp);
		CDwgDatabaseUtil::SetXdata(_T("���ؼ�"), m_frameInfo.GZJ, pRefTemp);
		pRefTemp->close();
	}
}

Adesk::Boolean CJigEntity::subWorldDraw(AcGiWorldDraw* mode)
{
	DrawOrAddSubEnts(mode);
	return Adesk::kTrue;
}

void CJigEntity::PostToModleSpace()
{
	DrawOrAddSubEnts(NULL);
}

void CJigEntity::SetPt(AcGePoint3d pt)
{
	assertWriteEnabled();
	m_ptInsert = pt;
}


CBlockJig::CBlockJig()
{
}

CBlockJig::~CBlockJig()
{
}

bool CBlockJig::doIt(AcDbObjectId idBlock,FrameInfo info)
{
	m_pJigEnt = new CJigEntity(idBlock,info);
	CString sPrompt = TEXT("\nѡ��λ��:");
	setDispPrompt(sPrompt);
	AcEdJig::DragStatus stat = drag();
	if (stat==kNormal)
	{
		m_pJigEnt->PostToModleSpace();
	}
	else
	{
		delete m_pJigEnt;
		m_pJigEnt = NULL;
		return false;
	}
	delete m_pJigEnt;
	m_pJigEnt = NULL;
	return true;
}

AcEdJig::DragStatus CBlockJig::sampler()
{
	setUserInputControls((UserInputControls)(AcEdJig::kAccept3dCoordinates | AcEdJig::kNoNegativeResponseAccepted | AcEdJig::kNullResponseAccepted));
	static AcGePoint3d pointTemp;
	DragStatus stat = acquirePoint(m_curPt);
	if (pointTemp != m_curPt)
	{
		pointTemp = m_curPt;
	}
	else if (stat == AcEdJig::kNormal)
	{
		return AcEdJig::kNoChange;
	}
	return stat;
}

Adesk::Boolean CBlockJig::update()
{
	m_pJigEnt->SetPt(m_curPt);
	return Adesk::kTrue;
}

AcDbEntity* CBlockJig::entity() const
{
	return m_pJigEnt;
}
