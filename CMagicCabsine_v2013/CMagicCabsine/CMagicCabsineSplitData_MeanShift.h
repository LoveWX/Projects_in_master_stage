#pragma once
#include "cmagiccabsinesplitdata.h"
#include "Meanshift(C)/msImageProcessor.h"
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

typedef unsigned int        UINT;

class CMagicCabsineSplitData_Meanshift :
	public CMagicCabsineSplitData
{
public:
	CMagicCabsineSplitData_Meanshift(const IplImage *tempSrcImage);
	~CMagicCabsineSplitData_Meanshift(void);

public:
	void DrawMarks();//���û���ǻ�����Դͼ����,���������markImage��

	void LoadSplitData();//���麯��,�����ݿ���ļ���������Ҫ������
	void SaveSplitData();//���麯��,���������ݱ��������ݿ���ļ���

	void LoadSplitDataFile(string filepath);//���麯��,���������ݱ������ļ���
	void SaveSplitDataFile(string filepath);//���麯��,���ļ���������Ҫ������

	//���麯��,����ʵ�ָú��������ĳһȫ�������ļ���,������ɺ���isCalced=true
	void ComputeSplitData();

	//ɾ���ָ�����,���ж�̬����Ŀռ䶼Ӧ�ڴ˺������ͷŲ���ָ����Ϊ��,�������������пɵ��������жԸú�����ʵ����������
	void DeleteSplitData();

private:

	//===========================================================================
	//	DoMeanShiftSegmentation
	//===========================================================================
	void DoMeanShiftSegmentation(
		const vector<UINT>&						inputImg,
		const int&								width,
		const int&								height,
		vector<UINT>&							segimg,
		const int&								sigmaS,
		const float&							sigmaR,
		const int&								minRegion,
		vector<int>&							labels,
		int&									numlabels);
	//�������߽�
	void DrawContoursAroundSegments(
		vector<UINT>&							segmentedImage,
		const int&								width,
		const int&								height,
		const UINT&								color);
};
