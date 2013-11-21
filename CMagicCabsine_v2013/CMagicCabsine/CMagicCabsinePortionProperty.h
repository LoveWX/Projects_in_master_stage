#ifndef cmagiccabsineportionproperty
#define cmagiccabsineportionproperty

#include <cstring>
#include <vector>
using namespace std;
#include <cv.h>

class CMagicCabsinePortionProperty
{
public:
	CMagicCabsinePortionProperty(	const IplImage *tempSrcImage,
									vector< vector<int> > &tempSplitMatrix,
									vector< vector< vector<int> > > &tempRegionMasks);//���캯��
	virtual ~CMagicCabsinePortionProperty();//��������,�ͷŻ����е�����,Ŀǰ����Ҫ�ͷ�displayImage,��������Ϊ��
	
	void GetPropertyName(string &tempName)const;//��ȡ�ֲ�����������
	void SetPropertyName(const string &tempName);//���þֲ�����������
	
	//���麯��,����ʵ�ָú��������ĳһ�ֲ������ļ���
	virtual void ComputeProperty()=0;//������ɺ���isCalced=true
	
	//������ʵ�ֲ�������������ͼ��
	IplImage *GetDisplayImage();//���isCalc==true?����������Ҫ����computeProperty()��������,����displayImage
	
	virtual void SaveProperty()=0;//���麯��,���������ݱ��������ݿ���
	virtual void LoadProperty()=0;//���麯��,�����ݿ��������Ҫ������

	virtual void SavePropertyFile(string filepath)=0;//���麯��,���������ݱ������ļ���
	virtual void LoadPropertyFile(string filepath)=0;//���麯��,���ļ���������Ҫ������

	//ɾ������,���ж�̬����Ŀռ䶼Ӧ�ڴ˺������ͷŲ���ָ����Ϊ��,�������������пɵ��������жԸú�����ʵ����������
	virtual void DeleteProperty()=0;
	
protected:
	const IplImage *srcImage;//�ֲ������������Դͼ��
	IplImage *displayImage;//�ֲ�����������������ʾ��ͼ��
	string propertyName;//�ֲ�����������,�������ݿ����ģ�����ȫ��������
	bool isCalced;//��ʶ�ֲ������Ƿ��Ѿ��������,��displayImage�Ƿ����
	bool isSplited;//��ʶ�Ƿ��Ѿ�ȡ�÷ָ���

	//��Դͼ��ߴ�һ�µĶ�ά�����ʾ�ָ���,���в�ͬ����ֵ��ʾ��ͬ������
	vector< vector<int> > splitMatrix;
	//�������������,ÿ��������Դͼ��ߴ�һ��,��splitMatrix�б�ǵ�����Ž��д洢,�±�
	vector< vector< vector<int> > > regionMasks;
};

#endif
