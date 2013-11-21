#include "stdafx.h"
#include "CMagicCabsineProject.h"
#include "MainFrm.h"
#include "CMagicCabsineUniversalProperty_feature_texture_spectral_DFT.h"
#include "CMagicCabsineUniversalProperty_feature_texture_spectral_gabor.h"
#include "CMagicCabsineSplitData_MeanShift.h"
#include "CMagicCabsineSplitData_GraphBase.h"

CMagicCabsineProject::CMagicCabsineProject()
{
	projectConfig=NULL;
	projectSrcImage=NULL;
	universalPropertySelected.clear();
	universalProperties.clear();
	splitData=NULL;
	portionPropertySelected.clear();
	portionProperties.clear();
	simulateData=NULL;
	canvasLength=0;
	canvasWidth=0;
	stateInitialize();
	undoStack=NULL;
}

CMagicCabsineProject::~CMagicCabsineProject()
{
	DeleteData();

	if(projectConfig!=NULL)
	{
		delete projectConfig;
		projectConfig=NULL;
	}
	if(projectSrcImage!=NULL)
	{
		cvReleaseImage(&projectSrcImage);
		projectSrcImage=NULL;
	}
	canvasLength=0;
	canvasWidth=0;
	if(undoStack!=NULL)
	{
		delete undoStack;
		undoStack=NULL;
	}
}

void CMagicCabsineProject::stateInitialize()
{
	currentProcessType=PROCESS_START;
}

void CMagicCabsineProject::RunWork()
{
	;//可以改成switch系统状态来运行系统流程的形式
}

/*//原先的RunWorkStep1()函数,在读入图片后计算全局特征
void CMagicCabsineProject::RunWorkStep1()
{
	//调用新建工程对话框获取工程信息
	ProjectNewDLG projectNewDLG;
	if(projectNewDLG.DoModal()!=IDOK)
	{
		return;
	}
	projectName=projectNewDLG.getProjectName();
	projectPath=projectNewDLG.getProjectPath();
	projectDescription=projectNewDLG.getProjectDescription();

	theApp.SetProjectPath(projectPath+projectName+"\\");

	//调用图像选择对话框获取图像信息
	ProjectImageNewDLG projectImageNewDLG;
	if(projectImageNewDLG.DoModal()!=IDOK)
	{
		return;
	}
	projectImagePath=projectImageNewDLG.getImagePath();
	projectImageType=projectImageNewDLG.getImageType();
	projectSrcImage=cvLoadImage(projectImagePath.c_str(),1);
	if(projectSrcImage==NULL)
	{
		MessageBox(NULL,CString("Error opening image."),CString("Error"),MB_OK|MB_ICONERROR);
		return;
	}

	//标记流程步骤为开始状态(PROCESS_START)
	currentProcessType=PROCESS_START;

	//获取配置表选择信息
	projectConfig=new CMagicCabsineConfig(projectImageType);
	projectConfig->GetSeleted(universalPropertySelected,portionPropertySelected);

	//还需要添加分割和模拟的选择信息,目前这两部分函数写在程序中,所以暂不需要

	//按照配置表初始化全局特征指针
	InitUniversalPropertyPoint();

	//计算所有的全局特征
	int i;
	for(i=0;i<universalProperties.size();i++)
	{
		universalProperties[i]->ComputeProperty();
	}

	//显示全局特征的计算结果,包括结果图片和标签页
	//这部分需要放在mainfrm中的相关函数进行计算
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	string stringName;
	m_leftView->displayImageInTab(CString(""),projectSrcImage,TABTYPE_SRCIMAGE,0);

	for(i=0;i<universalProperties.size();i++)
	{
		if(!universalPropertySelected[i])
		{
			continue;
		}
		universalProperties[i]->GetPropertyName(stringName);
		CString cstringName=stringName.c_str();
		IplImage *tempImage=universalProperties[i]->GetDisplayImage();
		m_leftView->displayImageInTab(cstringName,tempImage,TABTYPE_UNIVERSAL,i);
		m_leftView->myShowTab(TABTYPE_UNIVERSAL,i);
		tempImage=NULL;
	}

	//标记流程步骤为分割之前(PROCESS_UNIVERSALCALCED)
	currentProcessType=PROCESS_UNIVERSALCALCED;

	//按照配置表初始化分割方法指针
	InitSplitDataPoint();

	//显示分割交互的提示框
	splitData->GetSplitTips(stringName);
	MessageBox(NULL,CString(stringName.c_str()),CString("图像分割提示"),MB_OK|MB_ICONWARNING);

	m_leftView->displayImageInTab(CString(""),projectSrcImage,TABTYPE_SPLIT,0);
	m_leftView->myShowTab(TABTYPE_SPLIT,0);
}
*/

//更新后的RunWorkStep1()函数,全局特征在导入图片时使用,打开工程后读取这些信息
void CMagicCabsineProject::RunWorkStep1()
{
	//调用新建工程对话框获取工程信息
	ProjectNewDLG projectNewDLG;
	if(projectNewDLG.DoModal()!=IDOK)
	{
		return;
	}
	projectName=projectNewDLG.getProjectName();
	projectPath=projectNewDLG.getProjectPath();
	projectDescription=projectNewDLG.getProjectDescription();

	theApp.SetProjectPath(projectPath+projectName+"\\");

	//调用图像选择对话框获取图像信息
	ProjectImageNewDLG projectImageNewDLG;
	if(projectImageNewDLG.DoModal()!=IDOK)
	{
		return;
	}
	projectImagePath=projectImageNewDLG.getImagePath();
	projectImageType=projectImageNewDLG.getImageType();
	projectSrcImage=cvLoadImage(projectImagePath.c_str(),1);
	if(projectSrcImage==NULL)
	{
		MessageBox(NULL,CString("Error opening image."),CString("Error"),MB_OK|MB_ICONERROR);
		return;
	}

	//设置MainFrame上的标题字样
	theApp.SetTitleText(projectName.c_str());

	//标记流程步骤为开始状态(PROCESS_START)
	currentProcessType=PROCESS_START;

	//获取配置表选择信息
	projectConfig=new CMagicCabsineConfig(projectImageType);
	projectConfig->GetSeleted(universalPropertySelected,portionPropertySelected);

	//还需要添加分割和模拟的选择信息,目前这两部分函数写在程序中,所以暂不需要

	//按照配置表初始化全局特征指针
	InitUniversalPropertyPoint();

	//初始化图片库路径
	int i,j;
	string imageName;
	string typeName=projectImagePath;
	for(i=typeName.length()-1;i>=0&&typeName[i]!='\\';i--);
	imageName=typeName.substr(i+1);
	for(i--;i>=0&&typeName[i]!='\\';i--);
	typeName=typeName.substr(i+1);
	for(i=imageName.length()-1;i>=0&&imageName[i]!='.';i--);
	imageName=imageName.substr(0,i);
	for(i=typeName.length()-1;i>=0&&typeName[i]!='\\';i--);
	typeName=typeName.substr(0,i);
	string imageLibraryPath=theApp.GetDefaultPath()+"ImageLibrary\\"+typeName+"\\";
	string propertyLibraryPath=theApp.GetDefaultPath()+"PropertyLibrary\\"+typeName+"\\"+imageName+"\\";

	//读取所有的全局特征
	CMagicCabsineUniversalProperty_CLD *tp0=(CMagicCabsineUniversalProperty_CLD *)(universalProperties[0]);
	tp0->LoadPropertyFile(propertyLibraryPath+"CLDres.txt");
	tp0=NULL;
	CMagicCabsineUniversalProperty_VectorField *tp1=(CMagicCabsineUniversalProperty_VectorField *)(universalProperties[1]);
	tp1->LoadPropertyFile(propertyLibraryPath+"VECTORFIELDres.txt");
	tp1=NULL;
	CMagicCabsineUniversalProperty_Saliency *tp2=(CMagicCabsineUniversalProperty_Saliency *)(universalProperties[2]);
	tp2->LoadPropertyFile(propertyLibraryPath+"SALIENCYres.txt");
	tp2=NULL;

	//显示全局特征的计算结果,包括结果图片和标签页
	//这部分需要放在mainfrm中的相关函数进行计算
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	string stringName;
	m_leftView->displayImageInTab(CString(""),projectSrcImage,TABTYPE_SRCIMAGE,0);

	for(i=0;i<universalProperties.size();i++)
	{
		if(!universalPropertySelected[i])
		{
			continue;
		}
		universalProperties[i]->GetPropertyName(stringName);
		CString cstringName=stringName.c_str();
		IplImage *tempImage=universalProperties[i]->GetDisplayImage();
		m_leftView->displayImageInTab(cstringName,tempImage,TABTYPE_UNIVERSAL,i);
		m_leftView->myShowTab(TABTYPE_UNIVERSAL,i);
		tempImage=NULL;
	}

	//标记流程步骤为分割之前(PROCESS_UNIVERSALCALCED)
	currentProcessType=PROCESS_UNIVERSALCALCED;

	//按照配置表初始化分割方法指针
	InitSplitDataPoint();

	//显示分割交互的提示框
	splitData->GetSplitTips(stringName);
	MessageBox(NULL,CString(stringName.c_str()),CString("图像分割提示"),MB_OK|MB_ICONINFORMATION);

	m_leftView->displayImageInTab(CString(""),projectSrcImage,TABTYPE_SPLIT,0);
	m_leftView->myShowTab(TABTYPE_SPLIT,0);
}

/************************************************************************/
/* 
注意在此处主要是做分割操作
此处的分割操作要注意对于不同的图片应该有不同的流程，根据不同图片最后的不同绣制要求
例如：
对于人物图片，我们就要求能够分割出大色块的区域，而且这些大色块的区域要能够标记出前背景
对于风景图片，我们不需要标记前背景，只需要能够分割出大色块区域就好
将分割过程分成四大步骤：
1.标记：这是对于某些分割方法而言的，在分割算法分割之前对其标注一定的指导信息
2.分割：采用特定的分割算法，有交互的或者全自动的，进行分割操作，获得初始分割的结果信息
3.修改：对分割的结果进行一定的操作，例如分割区域，合并区域，修改边界等
4.标注语义信息：对分割结果的区域进行一定的语义标注，指导后面的绘制操作
Note：
此处的不同流程是根据具体情况具体图片类型来确定的
例如
标记		过程，只跟具体的算法相关，如果算法不需要交互则灰掉标记按钮
分割		主要是根据采用的分割算法，加载不同的算法dll来加载不同的算法
修改		的话也是根据不同图片的要求来确定流程需要的操作，
例如对于风景图片，最后需要的是大色块的区域，只需要合并区域的修改操作，而划分区域和
修改区域边界的操作就不需要了
标注		过程也是对于不同图片有不同的操作的。
例如风景图片不存在前背景就不需要标注,而人物静物则需要标注出前背景信息
*/
/************************************************************************/
void CMagicCabsineProject::RunWorkStep2()
{
	currentProcessType = PROCESS_SPLIT_MARKDOWN;
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	void *tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tp;
	tp=NULL;

	//获得用户标记并进行分割
	vector< vector<CvPoint> > tempFore,tempBack;
	interactiveView->GetCvPoint(tempFore,tempBack);
	splitData->SetUserMark(tempFore,tempBack);
	splitData->ComputeSplitData();

	//显示分割结果
	string stringName;
	splitData->GetSplitName(stringName);
	CString cstringName=stringName.c_str();
	IplImage *tempImage1=splitData->GetDisplayImage();
	IplImage *tempImage2=splitData->GetBoundaryImage();
	IplImage *tempImage3=splitData->GetFrontBackImage();
	m_leftView->displayImageInTab(cstringName,tempImage3,TABTYPE_SPLIT_RES,2);
	m_leftView->myShowTab(TABTYPE_SPLIT_RES,2);
	m_leftView->displayImageInTab(cstringName,tempImage1,TABTYPE_SPLIT_RES,1);
	m_leftView->myShowTab(TABTYPE_SPLIT_RES,1);
	m_leftView->displayImageInTab(cstringName,tempImage2,TABTYPE_SPLIT_RES,0);
	m_leftView->myShowTab(TABTYPE_SPLIT_RES,0);
	m_leftView->displayImageInTab(cstringName,tempImage2,TABTYPE_SPLIT);
	m_leftView->myShowTab(TABTYPE_SPLIT);

	SegmentationData *currentState=new SegmentationData(splitData->getSplitMat(),tempImage2,tempImage1,tempImage3);
	undoStack=new CMagicCabsineUndoStack(currentState);

	tempImage1=NULL;
	tempImage2=NULL;
	tempImage3 = NULL;
	//标记流程步骤为分割完成(PROCESS_SPLITED)
//	currentProcessType=PROCESS_SPLITED;
}

void CMagicCabsineProject::RunWorkStep3()
{
	if(undoStack!=NULL)
	{
		delete undoStack;
		undoStack=NULL;
	}

	currentProcessType=PROCESS_SPLITED;
	//获取分割结果
	vector< vector<int> > splitMatrix;
	vector< vector< vector<int> > > splitMasks;
	splitData->GetSplitResult(splitMatrix,splitMasks);

	//初始化局部特征指针
	InitPortionPropertyPoint(splitMatrix,splitMasks);

	//计算所有局部特征
	size_t i;
	for(i=0;i<portionProperties.size();i++)
	{
		portionProperties[i]->ComputeProperty();
	}

	//显示局部特征计算结果
	string stringName;
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	for(i=0;i<portionProperties.size();i++)
	{
		if(!portionPropertySelected[i])
		{
			continue;
		}
		portionProperties[i]->GetPropertyName(stringName);
		CString cstringName=stringName.c_str();
		IplImage *tempImage=portionProperties[i]->GetDisplayImage();
		m_leftView->displayImageInTab(cstringName,tempImage,TABTYPE_PORTION,i);
		m_leftView->myShowTab(TABTYPE_PORTION,i);
		tempImage=NULL;
	}

	//保存需要存储的数据
	//删除进入数据库中的数据,主要为特征计算数据和分割数据
	SaveData();
	DeleteData();

	//标记流程步骤为系统左边完成(PROCESS_LEFTDONE)
	currentProcessType=PROCESS_LEFTDONE;
}

void CMagicCabsineProject::RunWorkStep4()
{
	//调用画布选择对话框获取画布信息
	ProjectCanvasNewDLG projectCanvasNewDLG;
	projectCanvasNewDLG.SetCanvasSize(projectSrcImage->height,projectSrcImage->width);
	if(projectCanvasNewDLG.DoModal()!=IDOK)
	{
		return;
	}
	canvasLength=projectCanvasNewDLG.getCanvasLength();
	canvasWidth=projectCanvasNewDLG.getCanvasWidth();
	canvasType=projectCanvasNewDLG.getClothType();
	threadNorm=projectCanvasNewDLG.getThreadType();

	//进行模拟绣制之前对于较长绣制时间的提示
	MessageBox(NULL,CString("点击确定后进行模拟绣制\n这会花费比较长的时间\n请耐心等待"),CString("即将进行模拟绣制..."),MB_OK|MB_ICONINFORMATION);

	//按照配置表初始化模拟方法指针
	InitSimulateDataPoint();

	//为模拟绣制准备生成表数据
	simulateData->PrepareSimulateData();

	//计算模拟结果
	simulateData->ComputeSimulateData();

	//显示模拟方法计算结果
	string stringName;
	simulateData->GetSimulateName(stringName);
	CString cstringName=stringName.c_str();
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineRightView *m_rightView=(CMagicCabsineRightView *)mainFrame->m_WndSplitter.GetPane(0,1);
	IplImage *tempImage=simulateData->GetDisplayImage();
	vector<IplImage *> tempImageVector;
	simulateData->GetLevelImage(tempImageVector);
	int i;
	vector< vector<int> > tempMatrix;
	simulateData->GetSplitMatrix(tempMatrix);
	m_rightView->SetSplitMatrix(tempMatrix);
	for(i=0;i<tempImageVector.size();i++)
	{
		m_rightView->displayImageInTab(cstringName,tempImageVector[i],TABTYPE_SIMU_LEVEL,i);
		m_rightView->myShowTab(TABTYPE_SIMU_LEVEL,i);
	}
	m_rightView->displayImageInTab(cstringName,tempImage,TABTYPE_SIMU_ALL,0);
	m_rightView->myShowTab(TABTYPE_SIMU_ALL,0);
	tempImage=NULL;
	for(i=0;i<tempImageVector.size();i++)
	{
		tempImageVector[i]=NULL;
	}
	tempImageVector.clear();

	//标记流程步骤为模拟初步完成(PROCESS_SIMULATED)
	currentProcessType=PROCESS_SIMULATED;
}

void CMagicCabsineProject::RunWorkStep5()
{
	//标记流程步骤为模拟完成(PROCESS_SIMULATEDONE)
	currentProcessType=PROCESS_SIMULATEDONE;

	//保存需要存储的数据
	//删除进入数据库中的数据,主要为模拟数据
	simulateData->SaveSimulateData();
	simulateData->DeleteSimulateData();

	//还需要添加生成机绣表的模块

	//标记流程步骤为流程完成(PROCESS_DONE)
	currentProcessType=PROCESS_DONE;
}

void CMagicCabsineProject::SaveData()
{
	//新建以工程名称命名的文件夹
	CreateFolder(CString(theApp.GetProjectPath().c_str()));

	int i;
	for(i=0;i<universalProperties.size();i++)
	{
		if(universalProperties[i]!=NULL)
		{
			universalProperties[i]->SaveProperty();
		}
	}
	if(splitData!=NULL)
	{
		splitData->SaveSplitData();
	}
	for(i=0;i<portionProperties.size();i++)
	{
		if(portionProperties[i]!=NULL)
		{
			portionProperties[i]->SaveProperty();
		}
	}
}

void CMagicCabsineProject::DeleteData()
{
	int i;
	for(i=0;i<universalProperties.size();i++)
	{
		if(universalProperties[i]!=NULL)
		{
			delete universalProperties[i];
			universalProperties[i]=NULL;
		}
	}
	universalProperties.clear();
	universalPropertySelected.clear();
	if(splitData!=NULL)
	{
		delete splitData;
		splitData=NULL;
	}
	for(i=0;i<portionProperties.size();i++)
	{
		if(portionProperties[i]!=NULL)
		{
			delete portionProperties[i];
			portionProperties[i]=NULL;
		}
	}
	portionProperties.clear();
	portionPropertySelected.clear();
	if(simulateData!=NULL)
	{
		delete simulateData;
		simulateData=NULL;
	}
}

void CMagicCabsineProject::InitUniversalPropertyPoint()
{
	//初始化全局特征的指针
	CMagicCabsineUniversalProperty_CLD *tp0=new CMagicCabsineUniversalProperty_CLD(projectSrcImage);
	universalProperties.push_back((CMagicCabsineUniversalProperty *)tp0);
	CMagicCabsineUniversalProperty_VectorField *tp1=new CMagicCabsineUniversalProperty_VectorField(projectSrcImage);
	universalProperties.push_back((CMagicCabsineUniversalProperty *)tp1);
	CMagicCabsineUniversalProperty_Saliency *tp2=new CMagicCabsineUniversalProperty_Saliency(projectSrcImage);
	universalProperties.push_back((CMagicCabsineUniversalProperty *)tp2);

	// 	CMagicCabsineUniversalProperty_feature_texture_spectral_DFT *tp3=new CMagicCabsineUniversalProperty_feature_texture_spectral_DFT(projectSrcImage);
	// 	universalProperties.push_back((CMagicCabsineUniversalProperty *)tp3);

	//CMagicCabsineUniversalProperty_feature_texture_spectral_gabor *tp4=new CMagicCabsineUniversalProperty_feature_texture_spectral_gabor(projectSrcImage);
	//universalProperties.push_back((CMagicCabsineUniversalProperty *)tp4);

	tp0=NULL;
	tp1=NULL;
	tp2=NULL;
	//	tp3=NULL;
	//	tp4=NULL;
}

void CMagicCabsineProject::InitSplitDataPoint()
{
	//初始化分割方法的指针
	//CMagicCabsineSplitData_Test *tp=new CMagicCabsineSplitData_Test(projectSrcImage);
	//splitData=(CMagicCabsineSplitData *)tp;

	//	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//	typedef   CMagicCabsineSplitData*  (*FUN)(const IplImage* tempSrcImg);   
	//	HMODULE   hMod; 
	//	FUN   pfun;   
	//	string dll_file;
	//	projectConfig->GetPathOfSplitData(dll_file);
	//	hMod   =   ::LoadLibrary(_T(dll_file.c_str())); 
	////	hMod   =   ::LoadLibrary(_T("dll_debug\\split_meanshift_dll.dll"));   
	//	pfun  =   (FUN)::GetProcAddress(hMod,   "CreateObject");   
	//	if (splitData != NULL)
	//	{
	//		delete splitData;
	//		splitData = NULL;
	//	}
	//	splitData =  pfun(projectSrcImage);

	if (projectConfig->GetSplitDataName() == SPLIT_MEANSHIFT)
	{
		splitData = new CMagicCabsineSplitData_Meanshift(projectSrcImage);
	}
	else if (projectConfig->GetSplitDataName() == SPLIT_GRAPHBASE)
	{
		splitData = new CMagicCabsineSplitData_GraphBase(projectSrcImage);
	}
}

void CMagicCabsineProject::InitPortionPropertyPoint(vector< vector<int> > &splitMatrix,
	vector< vector< vector<int> > > &splitMasks)
{
	//初始化局部特征的指针
	CMagicCabsinePortionProperty_AverageColor *tp0=
		new CMagicCabsinePortionProperty_AverageColor(projectSrcImage,splitMatrix,splitMasks);
	portionProperties.push_back((CMagicCabsinePortionProperty_AverageColor *)tp0);
}

void CMagicCabsineProject::InitSimulateDataPoint()
{
	//初始化模拟方法的指针
	CMagicCabsineSimulateData_Test *tp=new CMagicCabsineSimulateData_Test(projectSrcImage);
	simulateData=(CMagicCabsineSimulateData *)tp;
}

CMagicCabsineSimulateData* CMagicCabsineProject::GetSimulateData()
{
	//仅仅用于返回指针将数据显示在右边的属性栏,不希望其它地方使用该函数
	return simulateData;
}

void CMagicCabsineProject::UpdateSimulateImage(int levelIndex)
{
	string stringName;
	simulateData->GetSimulateName(stringName);
	CString cstringName=stringName.c_str();
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineRightView *m_rightView=(CMagicCabsineRightView *)mainFrame->m_WndSplitter.GetPane(0,1);

	IplImage *tempImage=simulateData->GetDisplayImage();
	m_rightView->displayImageInTab(cstringName,tempImage,TABTYPE_SIMU_ALL,0);
	m_rightView->myShowTab(TABTYPE_SIMU_ALL,0);

	tempImage=simulateData->GetSingleLevelImage(levelIndex);
	m_rightView->displayImageInTab(cstringName,tempImage,TABTYPE_SIMU_LEVEL,levelIndex);
	m_rightView->myShowTab(TABTYPE_SIMU_LEVEL,levelIndex);

	mainFrame=NULL;
	m_rightView=NULL;
	tempImage=NULL;
}

//创建目录：
BOOL CMagicCabsineProject::CreateFolder(CString strPath)
{
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
	//上面定义的属性可以省略。 直接return ::CreateDirectory( path, NULL); 即可
	return ::CreateDirectory( strPath, &attrib);
}

void CMagicCabsineProject::SaveProject()
{
	switch (currentProcessType)
	{
	case PROCESS_START:
		SaveProjectLeftPart(0);
		break;
	case PROCESS_UNIVERSALCALCED:
		SaveProjectLeftPart(1);
		break;
	case PROCESS_SPLIT_MARKDOWN:
		SaveProjectLeftPart(1);
		break;
	case PROCESS_SPLITED:
		SaveProjectLeftPart(2);
		break;
	case PROCESS_LEFTDONE:
		SaveProjectRightPart(3);
		break;
	case PROCESS_SIMULATED:
		SaveProjectRightPart(4);
		break;
	case PROCESS_SIMULATEDONE:
	case PROCESS_DONE:
		SaveProjectRightPart(5);
		break;
	default:
		break;
	}
}

void CMagicCabsineProject::SaveProjectLeftPart(int numOfStep)
{
	int i;
	if(projectName.length()==0)//还未创建工程
	{
		return;
	}
	string savePath=projectPath+projectName+"\\";
	string fileName="Project.lzx";

	//新建savePath标识的文件夹
	CreateFolder(CString(savePath.c_str()));

	ofstream fout(savePath+fileName);
	fout<<numOfStep<<endl;

	//step 0:保存配置表的信息
	int numOfUniversal=projectConfig->GetNumOfUniversalProperty();
	int numOfPortion=projectConfig->GetNumOfPortionProperty();
	vector<bool> tempUniversal,tempPortion;
	projectConfig->GetSeleted(tempUniversal,tempPortion);
	//string pathOfSplit,pathOfSimulate;
	//projectConfig->GetPathOfSplitData(pathOfSplit);
	//projectConfig->GetPathOfSimulateData(pathOfSimulate);
	SPLIT_METHOD_NAME tempSplitName;
	tempSplitName = projectConfig->GetSplitDataName();

	fout<<"#0:CONFIG_FILE"<<endl;
	fout<<"Universal_Property:"<<numOfUniversal<<endl;
	for(i=0;i<numOfUniversal;i++)
	{
		if(tempUniversal[i])
		{
			fout<<'1'<<endl;
		}
		else
		{
			fout<<'0'<<endl;
		}
	}
	fout<<"Split_Data:"<<endl;
	fout<<tempSplitName<<endl;
	fout<<"Portion_Property:"<<numOfPortion<<endl;
	for(i=0;i<numOfPortion;i++)
	{
		if(tempPortion[i])
		{
			fout<<'1'<<endl;
		}
		else
		{
			fout<<'0'<<endl;
		}
	}
//	fout<<"Simulata_Data:"<<pathOfSimulate<<endl;
	tempUniversal.clear();
	tempPortion.clear();

	//step 1.1:保存工程信息,包括工程名称,工程描述,工程路径,图片路径,图片类型
	if(numOfStep<1)
	{
		fout.close();
		//MessageBox(NULL,CString("已成功保存工程:")+CString(projectName.c_str()),CString("保存工程提示"),MB_OK|MB_ICONWARNING);
		return;
	}
	fout<<endl<<"#1:PROCESS_START"<<endl;
	fout<<projectName<<endl
		<<projectPath<<endl;
	//fout<<projectDescription<<endl;//工程描述可能有多行,先输出总字数,再换行输出描述
	fout<<projectDescription.length()<<endl
		<<projectDescription<<endl;
	//fout<<projectImagePath<<endl;//原图片重新进行保存
	string srcImagePath=savePath+"TABTYPE_SRCIMAGE_0.jpg";
	cvSaveImage(srcImagePath.c_str(),projectSrcImage);
	fout<<"TABTYPE_SRCIMAGE_0.jpg"<<endl;
	switch (projectImageType)
	{
	case IMAGE_HUMAN:
		fout<<'0'<<endl;
		break;
	case IMAGE_SCENERY:
		fout<<'1'<<endl;
		break;
	case IMAGE_ANIMAL:
		fout<<'2'<<endl;
		break;
	case IMAGE_CUSTOM:
		fout<<'3'<<endl;
		break;
	default:
		fout<<'0'<<endl;
		break;
	}

	//step 1.2:保存各种全局特征
	fout<<endl<<"#2:PROCESS_UNIVERSALCALCED"<<endl;
	string propertyName;
	string propertyPath;
	for(i=0;i<numOfUniversal;i++)
	{
		universalProperties[i]->GetPropertyName(propertyName);
		propertyPath=propertyName+"result.txt";
		fout<<propertyPath<<endl;
		propertyPath=savePath+propertyPath;
		universalProperties[i]->SavePropertyFile(propertyPath);
	}

	//step 1.3:还需要保存可能有的分割交互
	fout<<endl<<"#3:PROCESS_SPLITED"<<endl;
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	void *tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tp;
	tp=NULL;

	vector< vector<CvPoint> > foreLines,backLines;
	string splitName;
	splitData->GetSplitName(splitName);
	string splitPath=splitName+"result.txt";
	fout<<splitPath<<endl;
	interactiveView->GetCvPoint(foreLines,backLines);
	splitData->SetUserMark(foreLines,backLines);

	splitPath=savePath+splitPath;
	splitData->SaveSplitDataFile(splitPath);

	//IplImage *tempImage=interactiveView->GetDisplayImage();
	//fout<<"TABTYPE_SPLIT_0.jpg"<<endl;
	//splitPath=savePath+"TABTYPE_SPLIT_0.jpg";
	//cvSaveImage(splitPath.c_str(),tempImage);
	//tempImage=NULL;

	//存储分割标签页和可能有的分割结果页的图片
	if(!interactiveView->IsSplited())//还没有进行分割
	{
		fout<<0<<endl;//表示还没有进行分割
	}
	else
	{
		fout<<1<<endl;//表示已经进行了分割
		//tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT_RES,0);
		//CMagicCabsineDisplayView *displayView=(CMagicCabsineDisplayView *)tp;
		//tempImage=displayView->GetDisplayImage();
		//fout<<"TABTYPE_SPLIT_RES_0.jpg"<<endl;
		//splitPath=savePath+"TABTYPE_SPLIT_RES_0.jpg";
		//cvSaveImage(splitPath.c_str(),tempImage);
		//tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT_RES,1);
		//displayView=(CMagicCabsineDisplayView *)tp;
		//tempImage=displayView->GetDisplayImage();
		//fout<<"TABTYPE_SPLIT_RES_1.jpg"<<endl;
		//splitPath=savePath+"TABTYPE_SPLIT_RES_1.jpg";
		//cvSaveImage(splitPath.c_str(),tempImage);
		//tempImage=NULL;
		//displayView=NULL;
		//tp=NULL;
	}

	fout.close();
	// 	MessageBox(NULL,CString("已成功保存工程:")+CString(projectName.c_str()),CString("保存工程提示"),MB_OK|MB_ICONWARNING);
}

void CMagicCabsineProject::SaveProjectRightPart(int numOfStep)
{
	if(numOfStep<3)
	{
		return;
	}

	int i;
	//保存的路径使用saveFolder还是已经定义好的projectPath？
	string savePath=projectPath+projectName+"\\";
	string fileName="Project.lzx";

	//新建savePath标识的文件夹
	CreateFolder(CString(savePath.c_str()));

	ofstream fout(savePath+fileName);
	fout<<numOfStep<<endl;

	//step 0.1:保存配置表的信息
	int numOfUniversal=projectConfig->GetNumOfUniversalProperty();
	int numOfPortion=projectConfig->GetNumOfPortionProperty();
	vector<bool> tempUniversal,tempPortion;
	projectConfig->GetSeleted(tempUniversal,tempPortion);
	SPLIT_METHOD_NAME tempSplitName = projectConfig->GetSplitDataName();

	fout<<"#0:CONFIG_FILE"<<endl;
	fout<<"Universal_Property:"<<numOfUniversal<<endl;
	for(i=0;i<numOfUniversal;i++)
	{
		if(tempUniversal[i])
		{
			fout<<'1'<<endl;
		}
		else
		{
			fout<<'0'<<endl;
		}
	}
	fout<<"Split_Data:"<<endl;
	fout<<tempSplitName<<endl;
	fout<<"Portion_Property:"<<numOfPortion<<endl;
	for(i=0;i<numOfPortion;i++)
	{
		if(tempPortion[i])
		{
			fout<<'1'<<endl;
		}
		else
		{
			fout<<'0'<<endl;
		}
	}
//	fout<<"Simulata_Data:"<<pathOfSimulate<<endl;

	//step 0.2:保存工程信息,包括工程名称,工程描述,工程路径,图片路径,图片类型
	fout<<endl<<"#1:PROCESS_START"<<endl;
	fout<<projectName<<endl
		<<projectPath<<endl;
	//fout<<projectDescription<<endl;//工程描述可能有多行,先输出总字数,再换行输出描述
	fout<<projectDescription.length()<<endl
		<<projectDescription<<endl;
	//fout<<projectImagePath<<endl;//原图片重新进行保存
	string srcImagePath=savePath+"TABTYPE_SRCIMAGE_0.jpg";
	cvSaveImage(srcImagePath.c_str(),projectSrcImage);
	fout<<"TABTYPE_SRCIMAGE_0.jpg"<<endl;
	switch (projectImageType)
	{
	case IMAGE_HUMAN:
		fout<<'0'<<endl;
		break;
	case IMAGE_SCENERY:
		fout<<'1'<<endl;
		break;
	case IMAGE_ANIMAL:
		fout<<'2'<<endl;
		break;
	case IMAGE_CUSTOM:
		fout<<'3'<<endl;
		break;
	default:
		fout<<'0'<<endl;
		break;
	}

	//step 0.3:保存左侧标签页中显示的图片
	vector<TABVIEW_TYPE> tabviewType;
	vector<int> indexInType;
	vector<IplImage *> theImage;
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	m_leftView->GetDisplayImage(tempUniversal,tempPortion,tabviewType,indexInType,theImage);

	string imageName;
	char str[10];
	fout<<endl<<"#4:PROCESS_LEFTDONE"<<endl;
	fout<<theImage.size()<<endl;
	for(i=0;i<theImage.size();i++)
	{
		switch (tabviewType[i])
		{
		case TABTYPE_SRCIMAGE:
			fout<<"0 0"<<endl;
			imageName="TABTYPE_SRCIMAGE_0.jpg";
			fout<<imageName<<endl;
			imageName=savePath+imageName;
			cvSaveImage(imageName.c_str(),theImage[i]);
			break;
		case TABTYPE_UNIVERSAL:
			fout<<"1 "<<indexInType[i]<<endl;
			sprintf_s(str,"%d",indexInType[i]);
			imageName=string("TABTYPE_UNIVERSAL_")+str+".jpg";
			fout<<imageName<<endl;
			imageName=savePath+imageName;
			cvSaveImage(imageName.c_str(),theImage[i]);
			break;
		case TABTYPE_SPLIT:
			fout<<"2 0"<<endl;
			imageName="TABTYPE_SPLIT_0.jpg";
			fout<<imageName<<endl;
			imageName=savePath+imageName;
			cvSaveImage(imageName.c_str(),theImage[i]);
			break;
		case TABTYPE_SPLIT_RES:
			fout<<"3 "<<indexInType[i]<<endl;
			sprintf_s(str,"%d",indexInType[i]);
			imageName=string("TABTYPE_SPLIT_RES_")+str+".jpg";
			fout<<imageName<<endl;
			imageName=savePath+imageName;
			cvSaveImage(imageName.c_str(),theImage[i]);
			break;
		case TABTYPE_PORTION:
			fout<<"4 "<<indexInType[i]<<endl;
			sprintf_s(str,"%d",indexInType[i]);
			imageName=string("TABTYPE_PORTION_")+str+".jpg";
			fout<<imageName<<endl;
			imageName=savePath+imageName;
			cvSaveImage(imageName.c_str(),theImage[i]);
			break;
		default:
			break;
		}
	}
	for(i=0;i<theImage.size();i++)
	{
		theImage[i]=NULL;
	}
	theImage.clear();

	//step 1.1:保存画布信息
	if(numOfStep<4)
	{
		fout.close();
		//MessageBox(NULL,CString("已成功保存工程:")+CString(projectName.c_str()),CString("保存工程提示"),MB_OK|MB_ICONWARNING);
		return;
	}

	fout<<endl<<"#5:PROCESS_SIMULATED"<<endl;
	fout<<canvasLength<<endl
		<<canvasWidth<<endl;
	switch (canvasType)
	{
	case CLOTH_TYPE1:
		fout<<1<<endl;
		break;
	case CLOTH_TYPE2:
		fout<<2<<endl;
		break;
	default:
		break;
	}
	switch (threadNorm)
	{
	case THREAD_TYPE1:
		fout<<1<<endl;
		break;
	case THREAD_TYPE2:
		fout<<2<<endl;
		break;
	default:
		break;
	}

	//step 1.2:保存右侧标签页中显示的图片
	//MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineRightView *m_rightView=(CMagicCabsineRightView *)mainFrame->m_WndSplitter.GetPane(0,1);
	m_rightView->GetDisplayImage(tabviewType,indexInType,theImage);

	fout<<theImage.size()<<endl;
	for(i=0;i<theImage.size();i++)
	{
		switch (tabviewType[i])
		{
		case TABTYPE_SIMU_ALL:
			fout<<"5 0"<<endl;
			imageName="TABTYPE_SIMU_ALL_0.jpg";
			fout<<imageName<<endl;
			imageName=savePath+imageName;
			cvSaveImage(imageName.c_str(),theImage[i]);
			break;
		case TABTYPE_SIMU_LEVEL:
			fout<<"6 "<<indexInType[i]<<endl;
			sprintf_s(str,"%d",indexInType[i]);
			imageName=string("TABTYPE_SIMU_LEVEL_")+str+".jpg";
			fout<<imageName<<endl;
			imageName=savePath+imageName;
			cvSaveImage(imageName.c_str(),theImage[i]);
			break;
		default:
			break;
		}
	}
	m_rightView=NULL;

	//step 1.3:保存模拟绣制数据
	string simulateName;
	simulateData->GetSimulateName(simulateName);
	if(numOfStep==4)
	{
		string simulatePath=simulateName+"result.txt";
		fout<<simulatePath<<endl;
		simulatePath=savePath+simulatePath;
		simulateData->SaveSimulateDataFile(simulatePath);
	}
	/*
	//step 2.1:保存右侧标签页中显示的图片
	if(numOfStep<5)
	{
		fout.close();
 		//MessageBox(NULL,CString("已成功保存工程:")+CString(projectName.c_str()),CString("保存工程提示"),MB_OK|MB_ICONWARNING);
		return;
	}

	//step 3.1:保存绣制结果,目前暂无其它数据需要保存
	fout<<endl<<"#6:PROCESS_SIMULATEDONE"<<endl;
	*/
	fout.close();
// 	MessageBox(NULL,CString("已成功保存工程:")+CString(projectName.c_str()),CString("保存工程提示"),MB_OK|MB_ICONWARNING);
}

void CMagicCabsineProject::CloseProject()
{
	switch (currentProcessType)
	{
	case PROCESS_START:
		return;
	case PROCESS_UNIVERSALCALCED:
	case PROCESS_SPLIT_MARKDOWN:
	case PROCESS_SPLITED:
		CloseProjectLeftPart(0);
		break;
	case PROCESS_LEFTDONE:
		CloseProjectLeftPart(3);
		break;
	case PROCESS_SIMULATED:
		CloseProjectRightPart(4);
		break;
	case PROCESS_SIMULATEDONE:
	case PROCESS_DONE:
		CloseProjectRightPart(5);
		break;
	default:
		return;
	}

	currentProcessType=PROCESS_START;
	if(projectConfig!=NULL)
	{
		delete projectConfig;
		projectConfig=NULL;
	}
	if(projectSrcImage!=NULL)
	{
		cvReleaseImage(&projectSrcImage);
		projectSrcImage=NULL;
	}
	projectName="";
	canvasLength=0;
	canvasWidth=0;

	universalPropertySelected.clear();
	portionPropertySelected.clear();
}

void CMagicCabsineProject::CloseProjectLeftPart(int numOfStep)
{
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);

	int numOfUniversal=projectConfig->GetNumOfUniversalProperty();
	int numOfPortion=projectConfig->GetNumOfPortionProperty();

	//清除左侧标签页
	m_leftView->CloseTabView(numOfUniversal,numOfPortion);

	if(numOfStep==3)
	{
		return;
	}

	//清除左侧已经存在的数据
	DeleteData();
}

void CMagicCabsineProject::CloseProjectRightPart(int numOfStep)
{
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	CMagicCabsineRightView *m_rightView=(CMagicCabsineRightView *)mainFrame->m_WndSplitter.GetPane(0,1);

	int numOfUniversal=projectConfig->GetNumOfUniversalProperty();
	int numOfPortion=projectConfig->GetNumOfPortionProperty();

	//清除左侧标签页
	m_leftView->CloseTabView(numOfUniversal,numOfPortion);

	//清除右侧标签页
	m_rightView->CloseTabView();

	if(numOfStep>=5)
	{
		return;
	}

	//清除右侧已经存在的数据
	if(simulateData!=NULL)
	{
		simulateData->DeleteSimulateData();
	}
}

void CMagicCabsineProject::LoadProject()
{
	CFileDialog dlgFile(TRUE,_T("*.lzx"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
		_T("LZX FILES(*.lzx)|*.lzx|All Files(*.*)|*.*||"),NULL);
	CString tempCString=theApp.GetDefaultPath().c_str();
	tempCString+="Projects\\";
	dlgFile.m_ofn.lpstrInitialDir=tempCString;

	if(dlgFile.DoModal()!=IDOK)
	{
		return;
	}
	tempCString=dlgFile.GetPathName();//获取打开的文件路径
	if(tempCString.Right(4)!=CString(".lzx"))
	{
		MessageBox(NULL,CString("打开工程失败,文件类型错误:\n")+tempCString,CString("打开工程提示"),MB_OK|MB_ICONWARNING);
		return;
	}

	int i,j;
	int numOfStep;
	string tempString=tempCString;
	for(i=tempString.length()-1;i>=0&&tempString[i]!='\\';i--);
	string loadPath=tempString.substr(0,i+1);//找到保存工程的文件夹路径

	theApp.SetProjectPath(loadPath);

	ifstream fin(tempCString);
	fin>>numOfStep;//读取工程状态,并据此读出接下来的数据?????

	//读取工程配置表,文件标识行为"#0:CONFIG FILE"
	const int SizeOfStr=256;
	char str[SizeOfStr];
	do 
	{
		fin.getline(str,SizeOfStr);
	}while(str[0]!='#');

	int numOfUniversal,numOfPortion;
	fin.getline(str,SizeOfStr,':');
	fin>>numOfUniversal;
	fin.getline(str,SizeOfStr);
	for(i=0;i<numOfUniversal;i++)
	{
		fin>>j;
		if(j==1)
		{
			universalPropertySelected.push_back(true);
		}
		else
		{
			universalPropertySelected.push_back(false);
		}
	}
	fin.getline(str,SizeOfStr);
	fin>>str;
	int tempSplitID;
	fin >> tempSplitID;
	SPLIT_METHOD_NAME tempSplitName = (SPLIT_METHOD_NAME)tempSplitID;
	fin.getline(str,SizeOfStr,':');
	fin>>numOfPortion;
	fin.getline(str,SizeOfStr);
	for(i=0;i<numOfPortion;i++)
	{
		fin>>j;
		if(j==1)
		{
			portionPropertySelected.push_back(true);
		}
		else
		{
			portionPropertySelected.push_back(false);
		}
	}
	fin.getline(str,SizeOfStr);
	fin.getline(str,SizeOfStr);
	for(i=0;i<SizeOfStr&&str[i]!=':';i++);
	string pathOfSimulateData=(str+i+1);

	//读取工程信息和图片信息,文件标识行为"#1:PROCESS_START"
	do 
	{
		fin.getline(str,SizeOfStr);
	}while(str[0]!='#');
	fin.getline(str,SizeOfStr);
	projectName=str;
	fin.getline(str,SizeOfStr);
	projectPath=str;
	//工程描述可能包括好几行,先读取char个数,再逐char读取工程描述字符串
	int numOfChar;
	fin>>numOfChar;
	fin.getline(str,SizeOfStr);
	for(i=0;i<numOfChar;i++)
	{
		fin.get(str[i]);
	}
	str[i]='\0';
	projectDescription=str;
	fin.getline(str,SizeOfStr);

	fin.getline(str,SizeOfStr);
	projectImagePath=str;
	if(projectSrcImage!=NULL)
	{
		cvReleaseImage(&projectSrcImage);
		projectSrcImage=NULL;
	}
 	projectSrcImage=cvLoadImage((theApp.GetProjectPath()+projectImagePath).c_str(),1);
	if(projectSrcImage==NULL)
	{
		fin.close();
		MessageBox(NULL,CString("Error opening image."),CString("Error"),MB_OK|MB_ICONERROR);
		return;
	}
	fin>>i;
	switch (i)
	{
	case 0:
		projectImageType=IMAGE_HUMAN;
		break;
	case 1:
		projectImageType=IMAGE_SCENERY;
		break;
	case 2:
		projectImageType=IMAGE_ANIMAL;
		break;
	case 3:
		projectImageType=IMAGE_CUSTOM;
		break;
	default:
		projectImageType=IMAGE_HUMAN;
		break;
	}
	if(projectConfig!=NULL)
	{
		delete projectConfig;
		projectConfig=NULL;
	}
	projectConfig=new CMagicCabsineConfig(projectImageType);
	projectConfig->SetImageType(projectImageType);
	projectConfig->SetSeleted(universalPropertySelected,portionPropertySelected);
	projectConfig->SetSplitDataName(tempSplitName);

	IplImage *tempImage=NULL;
	vector< vector<CvPoint> > foreLines,backLines;
	string stringName;
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	//根据不同的工程状态读取存储文件
	if(numOfStep==1 || numOfStep==2)//PROCESS_UNIVERSALCALCED或PROCESS_SPLITED阶段
	{
		do 
		{
			fin.getline(str,SizeOfStr);
		}while(str[0]!='#');
		InitUniversalPropertyPoint();//初始化全局特征计算类的指针
		for(i=0;i<numOfUniversal;i++)//读取全局特征存储数据
		{
			fin.getline(str,SizeOfStr);
			universalProperties[i]->LoadPropertyFile(loadPath+str);
		}

		//将全局特征的结果图片显示出来
		void *tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT,0);
		CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tp;
		tp=NULL;

		m_leftView->displayImageInTab(CString(""),projectSrcImage,TABTYPE_SRCIMAGE,0);
		for(i=0;i<universalProperties.size();i++)
		{
			if(!universalPropertySelected[i])
			{
				continue;
			}
			universalProperties[i]->GetPropertyName(stringName);
			CString cstringName=stringName.c_str();
			tempImage=universalProperties[i]->GetDisplayImage();
			m_leftView->displayImageInTab(cstringName,tempImage,TABTYPE_UNIVERSAL,i);
			m_leftView->myShowTab(TABTYPE_UNIVERSAL,i);
			tempImage=NULL;
		}

		//读取可能有的分割标注
		do 
		{
			fin.getline(str,SizeOfStr);
		}while(str[0]!='#');
		InitSplitDataPoint();//初始化分割方法指针
		fin.getline(str,SizeOfStr);
		tempString=str;
		splitData->LoadSplitDataFile(loadPath+tempString);//读取分割方法存储数据
		splitData->GetSplitName(stringName);
		m_leftView->displayImageInTab(CString(stringName.c_str()),projectSrcImage,TABTYPE_SPLIT,0);
		m_leftView->myShowTab(TABTYPE_SPLIT,0);
		tempImage=NULL;

		//将用户标记绘制在标签页上
		splitData->GetUserMark(foreLines,backLines);
		if(foreLines.size()>0||backLines.size()>0)
		{
			interactiveView->SetCvPoint(foreLines,backLines);
		}

		fin>>i;
		if(i==1)//已经进行了分割,需要将分割结果显示在标签页中
		{
			IplImage *tempImage2=splitData->GetFrontBackImage();
			m_leftView->displayImageInTab(CString(stringName.c_str()),tempImage2,TABTYPE_SPLIT_RES,2);
			m_leftView->myShowTab(TABTYPE_SPLIT_RES,2);
			IplImage *tempImage1=splitData->GetDisplayImage();
			m_leftView->displayImageInTab(CString(stringName.c_str()),tempImage1,TABTYPE_SPLIT_RES,1);
			m_leftView->myShowTab(TABTYPE_SPLIT_RES,1);
			IplImage *tempImage0=splitData->GetBoundaryImage();
			m_leftView->displayImageInTab(CString(stringName.c_str()),tempImage0,TABTYPE_SPLIT_RES,0);
			m_leftView->myShowTab(TABTYPE_SPLIT_RES,0);

			m_leftView->displayImageInTab(CString(stringName.c_str()),tempImage0,TABTYPE_SPLIT);
			m_leftView->myShowTab(TABTYPE_SPLIT);

			SegmentationData *currentState=new SegmentationData(splitData->getSplitMat(),tempImage0,tempImage1,tempImage2);
			undoStack=new CMagicCabsineUndoStack(currentState);
			tempImage0=NULL;
			tempImage1=NULL;
			tempImage2=NULL;

			interactiveView->SetSplitDone();//设置已经进行了分割
			if (numOfStep == 1)
			{
				currentProcessType=PROCESS_SPLIT_MARKDOWN;
			}
			else
			{
				currentProcessType = PROCESS_SPLITED;
			}
		}
		else
		{
			currentProcessType=PROCESS_UNIVERSALCALCED;
		}
		//MessageBox(NULL,CString("工程成功打开:")+CString(projectName.c_str()),CString("打开工程提示"),MB_OK|MB_ICONWARNING);
		fin.close();
		return;
	}

	//PROCESS_LEFTDONE阶段
	do 
	{
		fin.getline(str,SizeOfStr);
	}while(str[0]!='#');
	int numOfTabView;
	fin>>numOfTabView;
	fin.getline(str,SizeOfStr);
	for(;numOfTabView>0;numOfTabView--)
	{
		fin>>i>>j;
		fin.getline(str,SizeOfStr);
		fin.getline(str,SizeOfStr);
		tempString=loadPath+str;
		tempImage=cvLoadImage(tempString.c_str(),1);
		switch (i)
		{
		case 0:
			m_leftView->displayImageInTab(CString(""),tempImage,TABTYPE_SRCIMAGE,0);
			break;
		case 1:
			m_leftView->displayImageInTab(CString(""),tempImage,TABTYPE_UNIVERSAL,j);
			m_leftView->myShowTab(TABTYPE_UNIVERSAL,j);
			break;
		case 2:
			m_leftView->displayImageInTab(CString(""),tempImage,TABTYPE_SPLIT,j);
			m_leftView->myShowTab(TABTYPE_SPLIT,j);
			break;
		case 3:
			m_leftView->displayImageInTab(CString(""),tempImage,TABTYPE_SPLIT_RES,j);
			m_leftView->myShowTab(TABTYPE_SPLIT_RES,j);
			break;
		case 4:
			m_leftView->displayImageInTab(CString(""),tempImage,TABTYPE_PORTION,j);
			m_leftView->myShowTab(TABTYPE_PORTION,j);
			break;
		default:
			break;
		}
		cvReleaseImage(&tempImage);
		tempImage=NULL;
	}

	if(numOfStep==3)
	{
		currentProcessType=PROCESS_LEFTDONE;
		//MessageBox(NULL,CString("工程成功打开:")+CString(projectName.c_str()),CString("打开工程提示"),MB_OK|MB_ICONWARNING);
		fin.close();
		return;
	}

	do 
	{
		fin.getline(str,SizeOfStr);
	}while(str[0]!='#');
	fin>>canvasLength>>canvasWidth;
	fin>>i>>j;
	switch (i)
	{
	case 1:
		canvasType=CLOTH_TYPE1;
		break;
	case 2:
		canvasType=CLOTH_TYPE2;
		break;
	default:
		break;
	}
	switch (j)
	{
	case 1:
		threadNorm=THREAD_TYPE1;
		break;
	case 2:
		threadNorm=THREAD_TYPE2;
		break;
	default:
		break;
	}

	//PROCESS_SIMULATED阶段
	InitSimulateDataPoint();
	CMagicCabsineRightView *m_rightView=(CMagicCabsineRightView *)mainFrame->m_WndSplitter.GetPane(0,1);
	fin>>numOfTabView;
	fin.getline(str,SizeOfStr);
	for(;numOfTabView>0;numOfTabView--)
	{
		fin>>i>>j;
		fin.getline(str,SizeOfStr);
		fin.getline(str,SizeOfStr);
		tempString=loadPath+str;
		tempImage=cvLoadImage(tempString.c_str(),1);
		switch (i)
		{
		case 5:
			m_rightView->displayImageInTab(CString(""),tempImage,TABTYPE_SIMU_ALL,j);
			m_rightView->myShowTab(TABTYPE_SIMU_ALL,j);
			break;
		case 6:
			m_rightView->displayImageInTab(CString(""),tempImage,TABTYPE_SIMU_LEVEL,j);
			m_rightView->myShowTab(TABTYPE_SIMU_LEVEL,j);
			break;
		default:
			break;
		}
		cvReleaseImage(&tempImage);
		tempImage=NULL;
	}

	if(numOfStep==4)
	{
		fin.getline(str,SizeOfStr);
		tempString=str;
		simulateData->LoadSimulateDataFile(loadPath+tempString);
		simulateData->SetSimulateName(stringName);
// 		tempImage=simulateData->GetDisplayImage();
// 		vector<IplImage *> tempImageVector;
// 		simulateData->GetLevelImage(tempImageVector);
		vector< vector<int> > tempMatrix;
		simulateData->GetSplitMatrix(tempMatrix);
		m_rightView->SetSplitMatrix(tempMatrix);
// 		for(i=0;i<tempImageVector.size();i++)
// 		{
// 			m_rightView->displayImageInTab(CString(stringName.c_str()),tempImageVector[i],TABTYPE_SIMU_LEVEL,i);
// 			m_rightView->myShowTab(TABTYPE_SIMU_LEVEL,i);
// 		}
// 		m_rightView->displayImageInTab(CString(stringName.c_str()),tempImage,TABTYPE_SIMU_ALL,0);
// 		m_rightView->myShowTab(TABTYPE_SIMU_ALL,0);
// 		tempImage=NULL;
// 		for(i=0;i<tempImageVector.size();i++)
// 		{
// 			tempImageVector[i]=NULL;
// 		}
// 		tempImageVector.clear();

		currentProcessType=PROCESS_SIMULATED;
		//MessageBox(NULL,CString("工程成功打开:")+CString(projectName.c_str()),CString("打开工程提示"),MB_OK|MB_ICONWARNING);
		fin.close();
		return;
	}

	//PROCESS_SIMULATEDONE阶段
	currentProcessType=PROCESS_DONE;
	//MessageBox(NULL,CString("工程成功打开:")+CString(projectName.c_str()),CString("打开工程提示"),MB_OK|MB_ICONWARNING);
	fin.close();
}

void CMagicCabsineProject::LoadProjectLeftPart(int numOfStep)
{
	;
}

void CMagicCabsineProject::LoadProjectRightPart(int numOfStep)
{
	;
}

void CMagicCabsineProject::ImportImage()
{
	CFileDialog dlgFile(TRUE,_T("*.jpg"),NULL,
		OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT,
		_T("IMAGE FILES(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*||"),NULL);
	CString tempPath=theApp.GetDefaultPath().c_str();
	dlgFile.m_ofn.lpstrInitialDir=tempPath;
	if(dlgFile.DoModal()!=IDOK)
	{
		return;
	}

	int i;
	IplImage *theImage=NULL;
	POSITION pos=dlgFile.GetStartPosition();
	while(pos!=NULL)
	{
		CString filePath=dlgFile.GetNextPathName(pos);
		theImage=cvLoadImage(filePath,1);
		SmallerImage(theImage);

		string imageName=filePath;
		for(i=imageName.length()-1;i>=0&&imageName[i]!='\\';i--);
		imageName=imageName.substr(i+1);
		for(i=imageName.length()-1;i>=0&&imageName[i]!='.';i--);
		imageName=imageName.substr(0,i);
// 		string imageLibraryPath=theApp.GetDefaultPath()+"ImageLibrary\\"+imageName+"\\";//图片库与特征库分开
		string imageLibraryPath=theApp.GetDefaultPath()+"ImageLibrary\\unclassified\\";
		CreateFolder(CString(imageLibraryPath.c_str()));
		string propertyLibraryPath=theApp.GetDefaultPath()+"PropertyLibrary\\unclassified\\";
		CreateFolder(CString(propertyLibraryPath.c_str()));
		propertyLibraryPath+=imageName+"\\";
		CreateFolder(CString(propertyLibraryPath.c_str()));

		string tempPath=imageLibraryPath+imageName+".jpg";
		cvSaveImage(tempPath.c_str(),theImage);

		//计算并保存所有的全局特征
		CMagicCabsineUniversalProperty_CLD *tp0=new CMagicCabsineUniversalProperty_CLD(theImage);
		tp0->ComputeProperty();
		tp0->SavePropertyFile(propertyLibraryPath+"CLDres.txt");

		CMagicCabsineUniversalProperty_VectorField *tp1=new CMagicCabsineUniversalProperty_VectorField(theImage,tp0);
		tp1->ComputeProperty();
		tp1->SavePropertyFile(propertyLibraryPath+"VECTORFIELDres.txt");

		CMagicCabsineUniversalProperty_Saliency *tp2=new CMagicCabsineUniversalProperty_Saliency(theImage);
		tp2->ComputeProperty();
		tp2->SavePropertyFile(propertyLibraryPath+"SALIENCYres.txt");

		delete tp0;
		tp0=NULL;
		delete tp1;
		tp1=NULL;
		delete tp2;
		tp2=NULL;
		cvReleaseImage(&theImage);
		theImage=NULL;
	}
	MessageBox(NULL,CString("成功导入图片"),CString("导入图片提示"),MB_OK|MB_ICONINFORMATION);
}

void CMagicCabsineProject::SmallerImage(IplImage *&theImage)
{
	int h=theImage->height;
	int w=theImage->width;
	int maxlen=600;
	IplImage *tempImage;
	if(h>=w)
	{
		if(h>maxlen)
		{
			w=(int)((double)maxlen*w/h+0.5);
			h=maxlen;
			tempImage=cvCreateImage(cvSize(w,h),IPL_DEPTH_8U,3);
			cvResize(theImage,tempImage);
			cvReleaseImage(&theImage);
			theImage=cvCloneImage(tempImage);
			cvReleaseImage(&tempImage);
			tempImage=NULL;
		}
	}
	else
	{
		if(w>maxlen)
		{
			h=(int)((double)maxlen*h/w+0.5);
			w=maxlen;
			tempImage=cvCreateImage(cvSize(w,h),IPL_DEPTH_8U,3);
			cvResize(theImage,tempImage);
			cvReleaseImage(&theImage);
			theImage=cvCloneImage(tempImage);
			cvReleaseImage(&tempImage);
			tempImage=NULL;
		}
	}
}
