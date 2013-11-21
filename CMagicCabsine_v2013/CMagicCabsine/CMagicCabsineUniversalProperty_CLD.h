#ifndef cmagiccabsineuniversalpropertycld
#define cmagiccabsineuniversalpropertycld

#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
#include <cv.h>
#include <highgui.h>

#include "CMagicCabsineUniversalProperty.h"

class CMagicCabsineUniversalProperty_CLD:public CMagicCabsineUniversalProperty
{
public:
	CMagicCabsineUniversalProperty_CLD(const IplImage *tempSrcImage);
	~CMagicCabsineUniversalProperty_CLD();
	void ComputeProperty();//����ȫ������,�������н�������ݵ�׼��
	void SaveProperty();//��������
	void LoadProperty();//��ȡ����
	void SavePropertyFile(string filepath);//��������
	void LoadPropertyFile(string filepath);//��ȡ����
	void DeleteProperty();//ɾ������Ҫ������

	void GetProperty(vector< vector<int> > &tempMatrix);//��������ļ�����

protected:
	int height;//��Ҫ����ľ���ĸ߶�
	int width;//��Ҫ����ľ���Ŀ��
	vector< vector<int> > ansMatrix;//��Ҫ����ľ���
};

#endif
