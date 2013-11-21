#ifndef cmagiccabsineuniversalproperty
#define cmagiccabsineuniversalproperty

#include <cstring>
#include <vector>
using namespace std;
#include <cv.h>

class CMagicCabsineUniversalProperty
{
public:
	CMagicCabsineUniversalProperty(const IplImage *tempSrcImage);//���캯��
	virtual ~CMagicCabsineUniversalProperty();//��������,�ͷŻ����е�����,Ŀǰ����Ҫ�ͷ�displayImage,��������Ϊ��

	void GetPropertyName(string &tempName)const;//��ȡȫ������������
	void SetPropertyName(const string &tempName);//����ȫ������������

	//���麯��,����ʵ�ָú��������ĳһȫ�������ļ���
	virtual void ComputeProperty()=0;//������ɺ���isCalced=true

	//������ʵȫ��������������ͼ��
	IplImage* GetDisplayImage();//���isCalc==true?����������Ҫ����computeProperty()��������,����displayImage

	virtual void SaveProperty()=0;//���麯��,���������ݱ��������ݿ���
	virtual void LoadProperty()=0;//���麯��,�����ݿ��������Ҫ������

	virtual void SavePropertyFile(string filepath)=0;//���麯��,���������ݱ������ļ���
	virtual void LoadPropertyFile(string filepath)=0;//���麯��,���ļ���������Ҫ������

	//ɾ������,���ж�̬����Ŀռ䶼Ӧ�ڴ˺������ͷŲ���ָ����Ϊ��,�������������пɵ��������жԸú�����ʵ����������
	virtual void DeleteProperty()=0;
protected:
	const IplImage *srcImage;//ȫ�������������Դͼ��
	IplImage *displayImage;//ȫ������������������ʾ��ͼ��
	string propertyName;//ȫ������������,�������ݿ����ģ�����ȫ��������
	bool isCalced;//��ʶȫ�������Ƿ��Ѿ��������,��displayImage�Ƿ����
};

#endif
