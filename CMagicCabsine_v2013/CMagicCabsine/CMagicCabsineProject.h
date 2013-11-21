#ifndef cmagiccabsineproject
#define cmagiccabsineproject

#include <cstring>
#include <vector>
using namespace std;
#include "cv.h"

#include "CMagicCabsineLeftView.h"
#include "CMagicCabsineDisplayView.h"

#include "CMagicCabsineConfig.h"
#include "CMagicCabsineUniversalProperty.h"
#include "CMagicCabsineSplitData.h"
#include "CMagicCabsinePortionProperty.h"
#include "CMagicCabsineSimulateData.h"
// #include "CMagicCabsineDatabaseOperator.h"

#include "CMagicCabsineUniversalProperty_CLD.h"
#include "CMagicCabsineUniversalProperty_VectorField.h"
#include "CMagicCabsineUniversalProperty_Saliency.h"
#include "CMagicCabsineSplitData_Test.h"
#include "CMagicCabsinePortionProperty_AverageColor.h"
#include "CMagicCabsineSimulateData_Test.h"

#include "ProjectNewDLG.h"
#include "ProjectImageNewDLG.h"
#include "ProjectCanvasNewDLG.h"

#include "CMagicCabsineUndoStack.h"

class CMagicCabsineProject
{
public:
	CMagicCabsineProject();
	~CMagicCabsineProject();

	void stateInitialize();//��ϵͳ������ΪPROCESS_START

	//����ϵͳ����Ҫ����
	void RunWork();
	//�������̵ĵ�һ��,�ӿ�ʼ(PROCESS_START)���ָ�֮ǰ(PROCESS_UNIVERSALCALCED),Ŀǰд����RunWork()��
	void RunWorkStep1();
	//�������̵ĵڶ���,�ӱ��������ָ����(PROCESS_SPLITED)
	void RunWorkStep2();
	//�������̵ĵ�����,�ӷָ����(PROCESS_SPLITED)��ϵͳ������(PROCESS_LEFTDONE)
	void RunWorkStep3();
	//�������̵ĵ��Ĳ�,��ϵͳ������(PROCESS_LEFTDONE)��ģ��������(PROCESS_SIMULATED)
	void RunWorkStep4();
	//�������̵ĵ��岽,��ģ��������(PROCESS_SIMULATED)���������(PROCESS_DONE)
	void RunWorkStep5();

	//����ȫ��������ָ��universalProperties
	void InitUniversalPropertyPoint();
	//�������ñ����÷ָ����ָ��splitData
	void InitSplitDataPoint();
	//���þֲ�������ָ��portionProperties
	void InitPortionPropertyPoint(	vector< vector<int> > &splitMatrix,
									vector< vector< vector<int> > > &splitMasks);
	//�������ñ�����ģ�ⷽ����ָ��simulateData
	void InitSimulateDataPoint();

	//////////////////////////////////////////////////////////////////////////
	//	��ȡȫ������
	//////////////////////////////////////////////////////////////////////////
	vector<CMagicCabsineUniversalProperty *>& getUniversalProperties(){return universalProperties;}

	//��ù�������
	string GetProjectName(){return projectName;}
	//���ù�������
	void SetProjectName(string tempName){projectName=tempName;}

	//��ù���·��
	string GetProjectPath(){return projectPath;}
	//���ù���·��
	void SetProjectPath(string tempPath){projectPath=tempPath;}

	//����ģ�ⷽ����ָ��������ʾ�������ұߵ����Կ�
	CMagicCabsineSimulateData* GetSimulateData();

	//������Ϣģ���ָ��
	CMagicCabsineConfig *projectConfig;

	//���ݿ����ģ��,��Ҫ�����������д���,���Բ�ʹ��ָ��
	//CMagicCabsineDatabaseOperator *databaseOperator;

	void SaveData();//���ø��������еı��溯����������
	void DeleteData();//���ø��������е�������������������

	PROCESS_TYPE currentProcessType;//��ʶ�������е�������ĸ�����

	//�������Կ���޸ĸ���ģ�����ͼƬ�͵�levelNum��ͼƬ
	void UpdateSimulateImage(int levelIndex);

	void SaveProject();//��������
	void LoadProject();//�򿪹���,��ȡ����

	void CloseProject();//�رյ�ǰ����

	void ImportImage();//����ͼƬ������ȫ�������ļ���

public:
	CMagicCabsineSplitData* getSplitData(){return splitData;}
	IMAGE_TYPE getImageType(){return projectImageType;}
protected:
	//��������Ϊ����������Ϣ
	string projectName;//��������
	string projectPath;//����·��
	string projectDescription;//��������

	//��������Ϊͼ����Ϣ
	IplImage *projectSrcImage;//��ѡ���ͼ��
	string projectImagePath;//ͼ��·��
	IMAGE_TYPE projectImageType;//ͼ������

	//��ѡȡ��ȫ������,trueΪѡ����ĳ����,falseΪδѡ��,����Ϊ��ѡȫ������������
	vector<bool> universalPropertySelected;//������ʾ��ѡ���ȫ��������ʾ���û�
	//��ѡȡ�ľֲ�����,trueΪѡ����ĳ����,falseΪδѡ��,����Ϊ��ѡ�ֲ�����������
	vector<bool> portionPropertySelected;//������ʾ��ѡ��ľֲ�������ʾ���û�

	//ȫ������,����Ϊ��ѡȫ������������,��Ϊ�ǿ�ָ��
	vector<CMagicCabsineUniversalProperty *> universalProperties;

	//�ָ��,ֻ����һ��,�ҷǿ�
	CMagicCabsineSplitData *splitData;

	//�ֲ�����,����Ϊ��ѡ�ֲ�����������,��Ϊ�ǿ�ָ��
	vector<CMagicCabsinePortionProperty *> portionProperties;
	//ģ�ⷽ��,ֻ����һ��,�ҷǿ�
	CMagicCabsineSimulateData *simulateData;

	int canvasLength;//�����߶�
	int canvasWidth;//�������
	CLOTH_TYPE canvasType;//��������
	THREAD_TYPE threadNorm;//��������

	//������벿�ֵ�����,��ϵͳ���̱�ʶΪPROCESS_START��PROCESS_UNIVERSALCALCED��PROCESS_SPLITEDʱ����
	void SaveProjectLeftPart(int numOfStep);
	//�����Ұ벿�ֵ�����,��ϵͳ���̱�ʶΪPROCESS_LEFTDONE��PROCESS_SIMULATED��PROCESS_SIMULATEDONEʱ����
	void SaveProjectRightPart(int numOfStep);

	//�ر���벿��,��ϵͳ���̱�ʶΪPROCESS_START��PROCESS_UNIVERSALCALCED��PROCESS_SPLITEDʱ����
	void CloseProjectLeftPart(int numOfStep);
	//�ر��Ұ벿��,��ϵͳ���̱�ʶΪPROCESS_LEFTDONE��PROCESS_SIMULATED��PROCESS_SIMULATEDONEʱ����
	void CloseProjectRightPart(int numOfStep);

	//��ȡ��벿�ֵ�����,��ϵͳ���̱�ʶΪPROCESS_START��PROCESS_UNIVERSALCALCED��PROCESS_SPLITEDʱ����
	void LoadProjectLeftPart(int numOfStep);
	//��ȡ�Ұ벿�ֵ�����,��ϵͳ���̱�ʶΪPROCESS_LEFTDONE��PROCESS_SIMULATED��PROCESS_SIMULATEDONEʱ����
	void LoadProjectRightPart(int numOfStep);

	//����Ŀ¼
	BOOL CreateFolder(CString strPath);

	//���ͼƬ����,����Ҫ��ͼƬ������С
	void SmallerImage(IplImage *&theImage);

public:
	//������ڳ���������������ջ�ṹ
	CMagicCabsineUndoStack *undoStack;
};

#endif
