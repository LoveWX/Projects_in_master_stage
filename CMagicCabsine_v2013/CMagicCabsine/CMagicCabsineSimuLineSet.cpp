#include "stdafx.h"

#include "CMagicCabsineSimuLineSet.h"

/*
struct SimuLineSet
{
	vector<SimuLine> lineSet;//��������
	int regionArea;//�������
	CvScalar mainColor;//������ɫ��
	THREAD_TYPE threadType;//������������
	
	STITCH_TYPE stitchType;
	void *stitchPoint;//�뷨��ָ��
	
	SimuLineSet();
	SimuLineSet(const SimuLineSet &tempLineSet);
	~SimuLineSet();
	SimuLineSet& operator= (const SimuLineSet& tempLineSet);
};
*/

SimuLineSet::SimuLineSet()
{
	lineSet.clear();
	regionArea=0;
	mainColor=cvScalar(0,0,0);
	threadType=THREAD_TYPE1;	
	stitchType=STITCH_OrderlessCross;
	stitchPoint=NULL;
}

SimuLineSet::SimuLineSet(const SimuLineSet &tempLineSet)
{
	lineSet=tempLineSet.lineSet;
	regionArea=tempLineSet.regionArea;
	mainColor=tempLineSet.mainColor;
	threadType=tempLineSet.threadType;
	
	stitchType=tempLineSet.stitchType;
	if(tempLineSet.stitchPoint==NULL)
	{
		stitchPoint=NULL;
		return;
	}
	if(stitchType==STITCH_ChaosVerticalCross
		||stitchType==STITCH_ChaosHorizontalCross
		||stitchType==STITCH_ChaosVectorFieldCross)
	{
		ChaosStitch *tp1=(ChaosStitch *)(tempLineSet.stitchPoint);
		ChaosStitch *tp2=new ChaosStitch(*tp1);
		stitchPoint=(void *)tp2;
		tp1=NULL;
		tp2=NULL;
	}
	else if(stitchType==STITCH_OrderlessCross)
	{
		OrderlessStitch *tp1=(OrderlessStitch *)(tempLineSet.stitchPoint);
		OrderlessStitch *tp2=new OrderlessStitch(*tp1);
		stitchPoint=(void *)tp2;
		tp1=NULL;
		tp2=NULL;
	}
	else
	{
		stitchPoint=NULL;//��Ҫ���������������͵����������Է�ֹ�ڴ�й¶
	}
}

SimuLineSet::~SimuLineSet()
{
	lineSet.clear();
	regionArea=0;
	mainColor=cvScalar(0,0,0);
	if(stitchPoint!=NULL)
	{
		if(stitchType==STITCH_ChaosVerticalCross
			||stitchType==STITCH_ChaosHorizontalCross
			||stitchType==STITCH_ChaosVectorFieldCross)
		{
			ChaosStitch *tp1=(ChaosStitch *)stitchPoint;
			stitchPoint=NULL;
			delete tp1;
			tp1=NULL;
		}
		else if(stitchType==STITCH_OrderlessCross)
		{
			OrderlessStitch *tp1=(OrderlessStitch *)stitchPoint;
			stitchPoint=NULL;
			delete tp1;
			tp1=NULL;
		}
		else
		{
			stitchPoint=NULL;//��Ҫ�����������͵����������Է�ֹ�ڴ�й¶
		}
	}
}

SimuLineSet& SimuLineSet::operator =(const SimuLineSet& tempLineSet)
{
	lineSet=tempLineSet.lineSet;
	regionArea=tempLineSet.regionArea;
	mainColor=tempLineSet.mainColor;
	threadType=tempLineSet.threadType;
	
	stitchType=tempLineSet.stitchType;
	if(tempLineSet.stitchPoint==NULL)
	{
		stitchPoint=NULL;
		return *this;
	}
	if(stitchType==STITCH_ChaosVerticalCross
		||stitchType==STITCH_ChaosHorizontalCross
		||stitchType==STITCH_ChaosVectorFieldCross)
	{
		ChaosStitch *tp1=(ChaosStitch *)(tempLineSet.stitchPoint);
		ChaosStitch *tp2=new ChaosStitch(*tp1);
		stitchPoint=(void *)tp2;
		tp1=NULL;
		tp2=NULL;
	}
	else if(stitchType==STITCH_OrderlessCross)
	{
		OrderlessStitch *tp1=(OrderlessStitch *)(tempLineSet.stitchPoint);
		OrderlessStitch *tp2=new OrderlessStitch(*tp1);
		stitchPoint=(void *)tp2;
		tp1=NULL;
		tp2=NULL;
	}
	else
	{
		stitchPoint=NULL;//��Ҫ���������������͵����������Է�ֹ�ڴ�й¶
	}
	return *this;
}
