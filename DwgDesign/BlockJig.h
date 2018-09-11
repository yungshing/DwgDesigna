#pragma once
#include "Common\AllHead.h"
#include "Common\Tools.h"
/*#include "D:\work\DwgDesign\SDK\inc\dbjig.h"*/

class CJigEntity :public AcDbEntity
{
public:
	CJigEntity(AcDbObjectId idBlock,FrameInfo info);
	virtual~CJigEntity();
	virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw * mode);
	void PostToModleSpace();
	void SetPt(AcGePoint3d pt);
private:
	void DrawOrAddSubEnts(AcGiWorldDraw * mode);
	AcDbObjectId m_idBlock;
	AcGePoint3d m_ptInsert;
	FrameInfo m_frameInfo;
};


class CBlockJig :public AcEdJig
{
public:
	CBlockJig();
	virtual~CBlockJig();

	bool doIt(AcDbObjectId idBlock,FrameInfo info);
	virtual AcEdJig::DragStatus sampler();
	virtual Adesk::Boolean update();
	virtual AcDbEntity* entity() const;

private:
	AcGePoint3d m_curPt;
	CJigEntity *m_pJigEnt;
};

