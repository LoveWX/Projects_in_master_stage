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

	void stateInitialize();//置系统的流程为PROCESS_START

	//运行系统的主要流程
	void RunWork();
	//运行流程的第一步,从开始(PROCESS_START)到分割之前(PROCESS_UNIVERSALCALCED),目前写在了RunWork()中
	void RunWorkStep1();
	//运行流程的第二步,从标记完成至分割完成(PROCESS_SPLITED)
	void RunWorkStep2();
	//运行流程的第三步,从分割完成(PROCESS_SPLITED)至系统左边完成(PROCESS_LEFTDONE)
	void RunWorkStep3();
	//运行流程的第四步,从系统左边完成(PROCESS_LEFTDONE)至模拟初步完成(PROCESS_SIMULATED)
	void RunWorkStep4();
	//运行流程的第五步,从模拟初步完成(PROCESS_SIMULATED)至流程完成(PROCESS_DONE)
	void RunWorkStep5();

	//设置全局特征的指针universalProperties
	void InitUniversalPropertyPoint();
	//根据配置表设置分割方法的指针splitData
	void InitSplitDataPoint();
	//设置局部特征的指针portionProperties
	void InitPortionPropertyPoint(	vector< vector<int> > &splitMatrix,
									vector< vector< vector<int> > > &splitMasks);
	//根据配置表设置模拟方法的指针simulateData
	void InitSimulateDataPoint();

	//////////////////////////////////////////////////////////////////////////
	//	获取全局特征
	//////////////////////////////////////////////////////////////////////////
	vector<CMagicCabsineUniversalProperty *>& getUniversalProperties(){return universalProperties;}

	//获得工程名称
	string GetProjectName(){return projectName;}
	//设置工程名称
	void SetProjectName(string tempName){projectName=tempName;}

	//获得工程路径
	string GetProjectPath(){return projectPath;}
	//设置工程路径
	void SetProjectPath(string tempPath){projectPath=tempPath;}

	//返回模拟方法的指针用于显示属性在右边的属性框
	CMagicCabsineSimulateData* GetSimulateData();

	//配置信息模块的指针
	CMagicCabsineConfig *projectConfig;

	//数据库操作模块,需要在整个过程中存在,所以不使用指针
	//CMagicCabsineDatabaseOperator *databaseOperator;

	void SaveData();//调用各个特征中的保存函数保存数据
	void DeleteData();//调用各个特征中的数据清除函数清除数据

	PROCESS_TYPE currentProcessType;//标识现在运行到程序的哪个步骤

	//根据属性框的修改更新模拟叠加图片和第levelNum层图片
	void UpdateSimulateImage(int levelIndex);

	void SaveProject();//保存数据
	void LoadProject();//打开工程,读取数据

	void CloseProject();//关闭当前工程

	void ImportImage();//导入图片并进行全局特征的计算

public:
	CMagicCabsineSplitData* getSplitData(){return splitData;}
	IMAGE_TYPE getImageType(){return projectImageType;}
protected:
	//以下三项为工程描述信息
	string projectName;//工程名称
	string projectPath;//工程路径
	string projectDescription;//工程描述

	//以下三项为图像信息
	IplImage *projectSrcImage;//所选择的图像
	string projectImagePath;//图像路径
	IMAGE_TYPE projectImageType;//图像类型

	//所选取的全局特征,true为选择了某特征,false为未选择,长度为可选全局特征的数量
	vector<bool> universalPropertySelected;//用于显示所选择的全局特征显示给用户
	//所选取的局部特征,true为选择了某特征,false为未选择,长度为可选局部特征的数量
	vector<bool> portionPropertySelected;//用于显示所选择的局部特征显示给用户

	//全局特征,长度为可选全局特征的数量,都为非空指针
	vector<CMagicCabsineUniversalProperty *> universalProperties;

	//分割方法,只能有一个,且非空
	CMagicCabsineSplitData *splitData;

	//局部特征,长度为可选局部特征的数量,都为非空指针
	vector<CMagicCabsinePortionProperty *> portionProperties;
	//模拟方法,只能有一个,且非空
	CMagicCabsineSimulateData *simulateData;

	int canvasLength;//画布高度
	int canvasWidth;//画布宽度
	CLOTH_TYPE canvasType;//画布类型
	THREAD_TYPE threadNorm;//绣线类型

	//保存左半部分的数据,在系统流程标识为PROCESS_START和PROCESS_UNIVERSALCALCED和PROCESS_SPLITED时运行
	void SaveProjectLeftPart(int numOfStep);
	//保存右半部分的数据,在系统流程标识为PROCESS_LEFTDONE和PROCESS_SIMULATED和PROCESS_SIMULATEDONE时运行
	void SaveProjectRightPart(int numOfStep);

	//关闭左半部分,在系统流程标识为PROCESS_START和PROCESS_UNIVERSALCALCED和PROCESS_SPLITED时运行
	void CloseProjectLeftPart(int numOfStep);
	//关闭右半部分,在系统流程标识为PROCESS_LEFTDONE和PROCESS_SIMULATED和PROCESS_SIMULATEDONE时运行
	void CloseProjectRightPart(int numOfStep);

	//读取左半部分的数据,在系统流程标识为PROCESS_START和PROCESS_UNIVERSALCALCED和PROCESS_SPLITED时运行
	void LoadProjectLeftPart(int numOfStep);
	//读取右半部分的数据,在系统流程标识为PROCESS_LEFTDONE和PROCESS_SIMULATED和PROCESS_SIMULATEDONE时运行
	void LoadProjectRightPart(int numOfStep);

	//创建目录
	BOOL CreateFolder(CString strPath);

	//如果图片过大,则需要对图片进行缩小
	void SmallerImage(IplImage *&theImage);

public:
	//添加用于撤销和重做操作的栈结构
	CMagicCabsineUndoStack *undoStack;
};

#endif
