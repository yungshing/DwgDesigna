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
	CString WZBM;//���ʱ���
	CString NAME;//����
	CString XL;//ϵ��
	CString GGXH;//����ͺ�
	CString CJ;//����
};

struct struct_DLGG
{
	CString WZBM;//���ʱ���
	CString NAME;//����
	CString XL;//ϵ��
	CString GGXH;//����ͺ�
	CString CJ;//����
};

struct Log
{
	CString sheet;//ҳ
	CString row;//��
	CString col;//��
	CString wtms;//��������
	CString clfs;//����ʽ
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
	CString CPBH;//��Ʒ���
	CString XMDJ;//��Ŀ�ȼ�
	CString SJS;//���ʦ
	CString XMJD;//��Ŀ�׶�
	CString CPMC;//��Ʒ����
	CString GZJ;//���ؼ�
};
