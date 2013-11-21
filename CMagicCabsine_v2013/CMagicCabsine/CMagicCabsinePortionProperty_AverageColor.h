#ifndef cmagiccabsineportionpropertyaveragecolor
#define cmagiccabsineportionpropertyaveragecolor

#include <cstring>
#include <vector>
#include <fstream>
using namespace std;
#include <cv.h>

#include "CMagicCabsinePortionProperty.h"

class CMagicCabsinePortionProperty_AverageColor:public CMagicCabsinePortionProperty
{
public:
	//���๹�캯��
	CMagicCabsinePortionProperty_AverageColor(	const IplImage *tempSrcImage,
												vector< vector<int> > &tempSplitMatrix,
												vector< vector< vector<int> > > &tempRegionMasks);
	~CMagicCabsinePortionProperty_AverageColor();//��������,�����DeleteProperty()
	void ComputeProperty();				//ʵ�ֻ����д��麯��,��ɾֲ������ļ���,��isCalcedΪtrue
	void SaveProperty();				//ʵ�ֻ����д��麯��,���������ݱ��������ݿ���
	void LoadProperty();				//ʵ�ֻ����д��麯��,�����ݿ��������Ҫ������
	void SavePropertyFile(string filepath);	//ʵ�ֻ����д��麯��,���������ݱ������ļ���
	void LoadPropertyFile(string filepath);	//ʵ�ֻ����д��麯��,���ļ���������Ҫ������
	void DeleteProperty();				//ʵ�ֻ����д��麯��,ɾ�������е�����

protected:
	int height;							//ͼ��ĸ߶�,�������е�srcImage�߶Ⱦ���
	int width;							//ͼ��Ŀ��,�������е�srcImage��Ⱦ���
	int numOfRegion;					//�ָ�����в�ͬ���������
	vector<int> numOfRegionPoints;		//��ͬ����ĵ���,�±��1��ʼ
	vector<int> averageBlue;			//ĳ������ɫ��ƽ��ֵ,�±��1��ʼ
	vector<int> averageGreen;			//ĳ������ɫ��ƽ��ֵ,�±��1��ʼ
	vector<int> averageRed;				//ĳ�����ɫ��ƽ��ֵ,�±��1��ʼ
};

#endif
