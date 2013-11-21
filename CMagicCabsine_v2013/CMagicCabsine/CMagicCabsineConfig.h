/*
//���ñ����ģ��,��ҪΪCMagicCabsineConfig�ඨ�弰ʵ��
//��Ҫ�ڹ��캯����ָ��ͼƬ����,
//�Ӷ��������ļ���ConfigFile�н�������Ҫ����Ϣ
//2012-11-28,zhouzhou
*/

#ifndef cmagiccabsineconfig
#define cmagiccabsineconfig

#include "stdafx.h"

#include <cstring>
#include <vector>
#include <fstream>
using namespace std;
#include <cv.h>

class CMagicCabsineConfig
{
public:
	CMagicCabsineConfig(IMAGE_TYPE tempImageType);
	~CMagicCabsineConfig();
	int GetNumOfUniversalProperty()const;//���ؿ�ѡȫ������������
	int GetNumOfPortionProperty()const;//���ؿ�ѡ�ֲ�����������

	//���ڲ�ͬ��ͼƬ���ͽ�pathOfConfig��Ϊ�������ļ���Ĭ��·��
	void FindoutPathOfConfig();

	void SaveConfigToFile();//�����ñ���Ϣ�������ļ���
	void LoadConfigFromFile();//���ļ��ж�ȡ���ñ���Ϣ

	//��ȡͼƬ����
	IMAGE_TYPE GetImageType();
	//����ͼƬ����
	void SetImageType(const IMAGE_TYPE tempImageType);

	//��ȡ���ñ�ѡ����Ϣ
	void GetSeleted(vector<bool> &tempUniversal,vector<bool> &tempPortion)const;
	//�������ñ�ѡ����Ϣ
	void SetSeleted(const vector<bool> &tempUniversal,const vector<bool> &tempPortion);

	//��ȡ��ѡȡ�ķָ��dll�ļ���·��
	SPLIT_METHOD_NAME GetSplitDataName(){return splitName;}
	//������ѡȡ�ķָ��dll�ļ���·��
	void SetSplitDataName(SPLIT_METHOD_NAME tempSplitName){splitName = tempSplitName;}
	// 	//��ȡ��ѡȡ��ģ�ⷽ��dll�ļ���·��
	// 	void GetPathOfSimulateData(string &tempPathOfSimulate)const;
	// 	//������ѡȡ��ģ�ⷽ��dll�ļ���·��
	// 	void SetPathOfSimulateData(const string &tempPathOfSimulate);

protected:
	IMAGE_TYPE imageType;
	string pathOfConfig;//�������Ѿ��رչ����·������Ϊ��

	int numOfUniversalProperty;//��ѡȫ������������
	int numOfPortionProperty;//��ѡ�ֲ�����������

	//��ѡȡ��ȫ������,trueΪѡ����ĳ����,falseΪδѡ��,����Ϊ��ѡȫ������������
	vector<bool> universalPropertySelected;
	//��ѡȡ�ľֲ�����,trueΪѡ����ĳ����,falseΪδѡ��,����Ϊ��ѡ�ֲ�����������
	vector<bool> portionPropertySelected;

	//��ѡ��ķָ����trueΪѡ�������ַָ����falseΪ��ѡ��
	SPLIT_METHOD_NAME splitName;

	// 	//�ָ����dll�ļ�·��
	// 	string pathOfSplitData;
	// 	//ģ�ⷽ����dll�ļ�·��
	// 	string pathOfSimulateData;
};

#endif
