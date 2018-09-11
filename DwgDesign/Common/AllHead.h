#pragma once
#include "ConvertUtil.h"
#include "IniFile.h"
#include "StringUtil.h"
#include "BlockUtil.h"
#include "TextStyleUtil.h"
#include "DwgDatabaseUtil.h"
#include "TextUtil.h"
#include "MathUtil.h"
#include "LayerUtil.h"
#include "LineUtil.h"
#include "AppDirectoryUtil.h"
#include "SelectUtil.h"
#include "GetInputUtil.h"
#include "../excel9.h"
#include "../rwExcel.h"

struct struct_LJQ
{
	CString WZBM;//物资编码
	CString NAME;//名称
	CString XL;//系列
	CString GGXH;//规格型号
	CString CJ;//厂家
};

struct struct_DLGG
{
	CString WZBM;//物资编码
	CString NAME;//名称
	CString XL;//系列
	CString GGXH;//规格型号
	CString CJ;//厂家
};

struct Log
{
	CString sheet;//页
	CString row;//行
	CString col;//列
	CString wtms;//问题描述
	CString clfs;//处理方式
};

struct CreatWhLog
{
	CString wtms;
	bool operator<(const CreatWhLog& b)
	{
		return this->wtms < b.wtms;
	}
	bool operator==(const CreatWhLog&b)
	{
		return this->wtms == b.wtms;
	}
};


struct FrameInfo
{
	CString CPBH;//产品编号
	CString XMDJ;//项目等级
	CString SJS;//设计师
	CString XMJD;//项目阶段
	CString CPMC;//产品名称
	CString GZJ;//关重件
};
