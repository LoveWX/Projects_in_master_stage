#pragma once
#include "cmagiccabsinesplitdata.h"
#include "stdhead.h"


class CMagicCabsineSplitData_GraphBase :
	public CMagicCabsineSplitData
{
public:
	CMagicCabsineSplitData_GraphBase(const IplImage *tempSrcImage);
	~CMagicCabsineSplitData_GraphBase(void);

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
	Mat GetRC(const Mat &img3f, double sigmaDist, double segK, int segMinSize, double segSigma);

	int Quantize(const Mat& img3f, Mat &idx1i, Mat &_color3f, Mat &_colorNum, double ratio = 0.95);

	void DrawContoursAroundSegments(vector<vector<int>> &segmentedImage,
		const int&								width,
		const int&								height,
		const int&								color);
//	void paintRegionResult();

private:
	int regNum;
};

