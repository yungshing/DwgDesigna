#pragma once
#include <AcDblClkEdit.h>
#include "Common/AllHead.h"
#include "Common/Tools.h"
#include "EditBlockDlg.h"
#include "EditDlDlg.h"


class CDoubleClick: public AcDbDoubleClickEdit
{
public:
	CDoubleClick();
	~CDoubleClick();
	void startEdit(AcDbEntity *pEnt, AcGePoint3d pt);
	void finishEdit(void);
};

