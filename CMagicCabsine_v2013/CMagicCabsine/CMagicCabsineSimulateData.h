#ifndef cmagiccabsinesimulatedata
#define cmagiccabsinesimulatedata

#include <cstring>
#include <vector>
using namespace std;
#include <cv.h>

#include "CMagicCabsineDataForSimulating.h"
#include "CMagicCabsineStitchLibrary.h"

class CMagicCabsineSimulateData
{
public:
	CMagicCabsineSimulateData(const IplImage *tempSrcImage);//���캯��
	//��������,�ͷŻ����е�����,Ŀǰ����Ҫ�ͷ�stitchThreads��displayImage��displayEveryLevel,��������Ϊ��
	virtual ~CMagicCabsineSimulateData();

	void GetSimulateName(string &tempName)const;//��ȡģ�ⷽ��������
	void SetSimulateName(const string &tempName);//����ģ�ⷽ��������
	
	//���麯��,����ʵ�ָú��������ģ�ⷽ�����ݵ�׼��
	virtual void PrepareSimulateData()=0;//������ɺ���isPrepare=true

	//���麯��,����ʵ�ָú��������ĳһģ�ⷽ���ļ���
	virtual void ComputeSimulateData()=0;//������ɺ���isCalced=true
	
	//������ʾģ�ⷽ����������ͼ��
	IplImage* GetDisplayImage();//���isCalc==true?����������Ҫ����computeProperty()��������,����displayImage
	void GetLevelImage(vector<IplImage *> &tempLevelImage);//���isCalc==true?����������Ҫ����computeProperty()��������,����displayEveryLevel
	IplImage* GetSingleLevelImage(int levelIndex);//�ȼ��isCalc��ֵ,����levelIndex�����ʾͼ��,������һ���ͼ���򷵻�NULL

	//�ڹ��̶�ȡʱ���ü�������ͼ��
	void SetDisplayImage(IplImage *tempImage);//����ģ������ͼ��
	void SetLevelImage(vector<IplImage *> &tempLevelImage);//���õ���ģ������ͼ��
	
	virtual void LoadSimulateData();//�麯��,�����ݿ��������Ҫ������
	virtual void SaveSimulateData();//�麯��,���������ݱ��������ݿ���

	virtual void LoadSimulateDataFile(string filepath);//�麯��,���ļ���������Ҫ������
	virtual void SaveSimulateDataFile(string filepath);//�麯��,���������ݱ������ļ���
	
	//ɾ������,���ж�̬����Ŀռ䶼Ӧ�ڴ˺������ͷŲ���ָ����Ϊ��,�������������пɵ��������жԸú�����ʵ����������
	virtual void DeleteSimulateData()=0;

	void GetSplitMatrix(vector< vector<int> > &tempMatrix);//��÷ָ����

	IplImage* GetSrcImage(){return srcImage;}
	CMagicCabsineDataForSimulating* GetMakeTable(){return theMakeTable;}
	
protected:
	IplImage *srcImage;//ģ�ⷽ����ʹ�õ�Դͼ��
	IplImage *displayImage;//ģ�������������ʾ��ͼ��
	vector<IplImage *> displayLevelImage;//ģ����ÿһ��������ʾ��ͼ��,�±��0��ʼ

	string simulateName;//ģ�ⷽ��������,�������ݿ����ģ�����ģ�ⷽ����
	bool isPrepared;//��ʶģ������Ҫ�������Ƿ��Ѿ�׼����(�Ƿ��Ѿ������ɱ���ȡ��)
	bool isCalced;//��ʶģ���Ƿ��Ѿ��������,��stitchThreads��displayImage��displayEveryLevel�Ƿ����

	//�����ݷ��������ж���
	//vector< vector<CMagicCabsineSimuLine> > simuLine;//ģ�ⷽ�����ɵ�ģ������,��һά�������,�ڶ�ά�ǲ��

	vector< vector<int> > splitMatrix;//�����ݿ��ж����ķָ����

	CMagicCabsineDataForSimulating *theMakeTable;//���ɱ�ָ��
	CMagicCabsineStitchLibrary *theStitchLibrary;//�뷨��ָ��
};

#endif
