#ifndef cmagiccabsineuniversalpropertysaliency
#define cmagiccabsineuniversalpropertysaliency

#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
#include <cv.h>
#include <highgui.h>

#include "CMagicCabsineUniversalProperty.h"

class CMagicCabsineUniversalProperty_Saliency:public CMagicCabsineUniversalProperty
{
public:
	CMagicCabsineUniversalProperty_Saliency(const IplImage *tempSrcImage);
	~CMagicCabsineUniversalProperty_Saliency();
	void ComputeProperty();//����ȫ������,�������н�������ݵ�׼��
	void SaveProperty();//��������
	void LoadProperty();//��ȡ����
	void SavePropertyFile(string filepath);//��������
	void LoadPropertyFile(string filepath);//��ȡ����
	void DeleteProperty();//ɾ������Ҫ������

	void GetProperty(vector< vector<float> > &tempMatrix);//��������ļ�����

protected:
	int height;//��Ҫ����ľ���ĸ߶�
	int width;//��Ҫ����ľ���Ŀ��
	vector< vector<float> > ansMatrix;//��Ҫ����ľ���
};

#endif
