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
	;//���Ըĳ�switchϵͳ״̬������ϵͳ���̵���ʽ
}

/*//ԭ�ȵ�RunWorkStep1()����,�ڶ���ͼƬ�����ȫ������
void CMagicCabsineProject::RunWorkStep1()
{
	//�����½����̶Ի����ȡ������Ϣ
	ProjectNewDLG projectNewDLG;
	if(projectNewDLG.DoModal()!=IDOK)
	{
		return;
	}
	projectName=projectNewDLG.getProjectName();
	projectPath=projectNewDLG.getProjectPath();
	projectDescription=projectNewDLG.getProjectDescription();

	theApp.SetProjectPath(projectPath+projectName+"\\");

	//����ͼ��ѡ��Ի����ȡͼ����Ϣ
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

	//������̲���Ϊ��ʼ״̬(PROCESS_START)
	currentProcessType=PROCESS_START;

	//��ȡ���ñ�ѡ����Ϣ
	projectConfig=new CMagicCabsineConfig(projectImageType);
	projectConfig->GetSeleted(universalPropertySelected,portionPropertySelected);

	//����Ҫ��ӷָ��ģ���ѡ����Ϣ,Ŀǰ�������ֺ���д�ڳ�����,�����ݲ���Ҫ

	//�������ñ��ʼ��ȫ������ָ��
	InitUniversalPropertyPoint();

	//�������е�ȫ������
	int i;
	for(i=0;i<universalProperties.size();i++)
	{
		universalProperties[i]->ComputeProperty();
	}

	//��ʾȫ�������ļ�����,�������ͼƬ�ͱ�ǩҳ
	//�ⲿ����Ҫ����mainfrm�е���غ������м���
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

	//������̲���Ϊ�ָ�֮ǰ(PROCESS_UNIVERSALCALCED)
	currentProcessType=PROCESS_UNIVERSALCALCED;

	//�������ñ��ʼ���ָ��ָ��
	InitSplitDataPoint();

	//��ʾ�ָ������ʾ��
	splitData->GetSplitTips(stringName);
	MessageBox(NULL,CString(stringName.c_str()),CString("ͼ��ָ���ʾ"),MB_OK|MB_ICONWARNING);

	m_leftView->displayImageInTab(CString(""),projectSrcImage,TABTYPE_SPLIT,0);
	m_leftView->myShowTab(TABTYPE_SPLIT,0);
}
*/

//���º��RunWorkStep1()����,ȫ�������ڵ���ͼƬʱʹ��,�򿪹��̺��ȡ��Щ��Ϣ
void CMagicCabsineProject::RunWorkStep1()
{
	//�����½����̶Ի����ȡ������Ϣ
	ProjectNewDLG projectNewDLG;
	if(projectNewDLG.DoModal()!=IDOK)
	{
		return;
	}
	projectName=projectNewDLG.getProjectName();
	projectPath=projectNewDLG.getProjectPath();
	projectDescription=projectNewDLG.getProjectDescription();

	theApp.SetProjectPath(projectPath+projectName+"\\");

	//����ͼ��ѡ��Ի����ȡͼ����Ϣ
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

	//����MainFrame�ϵı�������
	theApp.SetTitleText(projectName.c_str());

	//������̲���Ϊ��ʼ״̬(PROCESS_START)
	currentProcessType=PROCESS_START;

	//��ȡ���ñ�ѡ����Ϣ
	projectConfig=new CMagicCabsineConfig(projectImageType);
	projectConfig->GetSeleted(universalPropertySelected,portionPropertySelected);

	//����Ҫ��ӷָ��ģ���ѡ����Ϣ,Ŀǰ�������ֺ���д�ڳ�����,�����ݲ���Ҫ

	//�������ñ��ʼ��ȫ������ָ��
	InitUniversalPropertyPoint();

	//��ʼ��ͼƬ��·��
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

	//��ȡ���е�ȫ������
	CMagicCabsineUniversalProperty_CLD *tp0=(CMagicCabsineUniversalProperty_CLD *)(universalProperties[0]);
	tp0->LoadPropertyFile(propertyLibraryPath+"CLDres.txt");
	tp0=NULL;
	CMagicCabsineUniversalProperty_VectorField *tp1=(CMagicCabsineUniversalProperty_VectorField *)(universalProperties[1]);
	tp1->LoadPropertyFile(propertyLibraryPath+"VECTORFIELDres.txt");
	tp1=NULL;
	CMagicCabsineUniversalProperty_Saliency *tp2=(CMagicCabsineUniversalProperty_Saliency *)(universalProperties[2]);
	tp2->LoadPropertyFile(propertyLibraryPath+"SALIENCYres.txt");
	tp2=NULL;

	//��ʾȫ�������ļ�����,�������ͼƬ�ͱ�ǩҳ
	//�ⲿ����Ҫ����mainfrm�е���غ������м���
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

	//������̲���Ϊ�ָ�֮ǰ(PROCESS_UNIVERSALCALCED)
	currentProcessType=PROCESS_UNIVERSALCALCED;

	//�������ñ��ʼ���ָ��ָ��
	InitSplitDataPoint();

	//��ʾ�ָ������ʾ��
	splitData->GetSplitTips(stringName);
	MessageBox(NULL,CString(stringName.c_str()),CString("ͼ��ָ���ʾ"),MB_OK|MB_ICONINFORMATION);

	m_leftView->displayImageInTab(CString(""),projectSrcImage,TABTYPE_SPLIT,0);
	m_leftView->myShowTab(TABTYPE_SPLIT,0);
}

/************************************************************************/
/* 
ע���ڴ˴���Ҫ�����ָ����
�˴��ķָ����Ҫע����ڲ�ͬ��ͼƬӦ���в�ͬ�����̣����ݲ�ͬͼƬ���Ĳ�ͬ����Ҫ��
���磺
��������ͼƬ�����Ǿ�Ҫ���ܹ��ָ����ɫ������򣬶�����Щ��ɫ�������Ҫ�ܹ���ǳ�ǰ����
���ڷ羰ͼƬ�����ǲ���Ҫ���ǰ������ֻ��Ҫ�ܹ��ָ����ɫ������ͺ�
���ָ���̷ֳ��Ĵ��裺
1.��ǣ����Ƕ���ĳЩ�ָ�����Եģ��ڷָ��㷨�ָ�֮ǰ�����עһ����ָ����Ϣ
2.�ָ�����ض��ķָ��㷨���н����Ļ���ȫ�Զ��ģ����зָ��������ó�ʼ�ָ�Ľ����Ϣ
3.�޸ģ��Էָ�Ľ������һ���Ĳ���������ָ����򣬺ϲ������޸ı߽��
4.��ע������Ϣ���Էָ������������һ���������ע��ָ������Ļ��Ʋ���
Note��
�˴��Ĳ�ͬ�����Ǹ��ݾ����������ͼƬ������ȷ����
����
���		���̣�ֻ��������㷨��أ�����㷨����Ҫ������ҵ���ǰ�ť
�ָ�		��Ҫ�Ǹ��ݲ��õķָ��㷨�����ز�ͬ���㷨dll�����ز�ͬ���㷨
�޸�		�Ļ�Ҳ�Ǹ��ݲ�ͬͼƬ��Ҫ����ȷ��������Ҫ�Ĳ�����
������ڷ羰ͼƬ�������Ҫ���Ǵ�ɫ�������ֻ��Ҫ�ϲ�������޸Ĳ����������������
�޸�����߽�Ĳ����Ͳ���Ҫ��
��ע		����Ҳ�Ƕ��ڲ�ͬͼƬ�в�ͬ�Ĳ����ġ�
����羰ͼƬ������ǰ�����Ͳ���Ҫ��ע,�����ﾲ������Ҫ��ע��ǰ������Ϣ
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

	//����û���ǲ����зָ�
	vector< vector<CvPoint> > tempFore,tempBack;
	interactiveView->GetCvPoint(tempFore,tempBack);
	splitData->SetUserMark(tempFore,tempBack);
	splitData->ComputeSplitData();

	//��ʾ�ָ���
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
	//������̲���Ϊ�ָ����(PROCESS_SPLITED)
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
	//��ȡ�ָ���
	vector< vector<int> > splitMatrix;
	vector< vector< vector<int> > > splitMasks;
	splitData->GetSplitResult(splitMatrix,splitMasks);

	//��ʼ���ֲ�����ָ��
	InitPortionPropertyPoint(splitMatrix,splitMasks);

	//�������оֲ�����
	size_t i;
	for(i=0;i<portionProperties.size();i++)
	{
		portionProperties[i]->ComputeProperty();
	}

	//��ʾ�ֲ�����������
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

	//������Ҫ�洢������
	//ɾ���������ݿ��е�����,��ҪΪ�����������ݺͷָ�����
	SaveData();
	DeleteData();

	//������̲���Ϊϵͳ������(PROCESS_LEFTDONE)
	currentProcessType=PROCESS_LEFTDONE;
}

void CMagicCabsineProject::RunWorkStep4()
{
	//���û���ѡ��Ի����ȡ������Ϣ
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

	//����ģ������֮ǰ���ڽϳ�����ʱ�����ʾ
	MessageBox(NULL,CString("���ȷ�������ģ������\n��Ứ�ѱȽϳ���ʱ��\n�����ĵȴ�"),CString("��������ģ������..."),MB_OK|MB_ICONINFORMATION);

	//�������ñ��ʼ��ģ�ⷽ��ָ��
	InitSimulateDataPoint();

	//Ϊģ������׼�����ɱ�����
	simulateData->PrepareSimulateData();

	//����ģ����
	simulateData->ComputeSimulateData();

	//��ʾģ�ⷽ��������
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

	//������̲���Ϊģ��������(PROCESS_SIMULATED)
	currentProcessType=PROCESS_SIMULATED;
}

void CMagicCabsineProject::RunWorkStep5()
{
	//������̲���Ϊģ�����(PROCESS_SIMULATEDONE)
	currentProcessType=PROCESS_SIMULATEDONE;

	//������Ҫ�洢������
	//ɾ���������ݿ��е�����,��ҪΪģ������
	simulateData->SaveSimulateData();
	simulateData->DeleteSimulateData();

	//����Ҫ������ɻ�����ģ��

	//������̲���Ϊ�������(PROCESS_DONE)
	currentProcessType=PROCESS_DONE;
}

void CMagicCabsineProject::SaveData()
{
	//�½��Թ��������������ļ���
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
	//��ʼ��ȫ��������ָ��
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
	//��ʼ���ָ����ָ��
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
	//��ʼ���ֲ�������ָ��
	CMagicCabsinePortionProperty_AverageColor *tp0=
		new CMagicCabsinePortionProperty_AverageColor(projectSrcImage,splitMatrix,splitMasks);
	portionProperties.push_back((CMagicCabsinePortionProperty_AverageColor *)tp0);
}

void CMagicCabsineProject::InitSimulateDataPoint()
{
	//��ʼ��ģ�ⷽ����ָ��
	CMagicCabsineSimulateData_Test *tp=new CMagicCabsineSimulateData_Test(projectSrcImage);
	simulateData=(CMagicCabsineSimulateData *)tp;
}

CMagicCabsineSimulateData* CMagicCabsineProject::GetSimulateData()
{
	//�������ڷ���ָ�뽫������ʾ���ұߵ�������,��ϣ�������ط�ʹ�øú���
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

//����Ŀ¼��
BOOL CMagicCabsineProject::CreateFolder(CString strPath)
{
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
	//���涨������Կ���ʡ�ԡ� ֱ��return ::CreateDirectory( path, NULL); ����
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
	if(projectName.length()==0)//��δ��������
	{
		return;
	}
	string savePath=projectPath+projectName+"\\";
	string fileName="Project.lzx";

	//�½�savePath��ʶ���ļ���
	CreateFolder(CString(savePath.c_str()));

	ofstream fout(savePath+fileName);
	fout<<numOfStep<<endl;

	//step 0:�������ñ����Ϣ
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

	//step 1.1:���湤����Ϣ,������������,��������,����·��,ͼƬ·��,ͼƬ����
	if(numOfStep<1)
	{
		fout.close();
		//MessageBox(NULL,CString("�ѳɹ����湤��:")+CString(projectName.c_str()),CString("���湤����ʾ"),MB_OK|MB_ICONWARNING);
		return;
	}
	fout<<endl<<"#1:PROCESS_START"<<endl;
	fout<<projectName<<endl
		<<projectPath<<endl;
	//fout<<projectDescription<<endl;//�������������ж���,�����������,�ٻ����������
	fout<<projectDescription.length()<<endl
		<<projectDescription<<endl;
	//fout<<projectImagePath<<endl;//ԭͼƬ���½��б���
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

	//step 1.2:�������ȫ������
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

	//step 1.3:����Ҫ��������еķָ��
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

	//�洢�ָ��ǩҳ�Ϳ����еķָ���ҳ��ͼƬ
	if(!interactiveView->IsSplited())//��û�н��зָ�
	{
		fout<<0<<endl;//��ʾ��û�н��зָ�
	}
	else
	{
		fout<<1<<endl;//��ʾ�Ѿ������˷ָ�
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
	// 	MessageBox(NULL,CString("�ѳɹ����湤��:")+CString(projectName.c_str()),CString("���湤����ʾ"),MB_OK|MB_ICONWARNING);
}

void CMagicCabsineProject::SaveProjectRightPart(int numOfStep)
{
	if(numOfStep<3)
	{
		return;
	}

	int i;
	//�����·��ʹ��saveFolder�����Ѿ�����õ�projectPath��
	string savePath=projectPath+projectName+"\\";
	string fileName="Project.lzx";

	//�½�savePath��ʶ���ļ���
	CreateFolder(CString(savePath.c_str()));

	ofstream fout(savePath+fileName);
	fout<<numOfStep<<endl;

	//step 0.1:�������ñ����Ϣ
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

	//step 0.2:���湤����Ϣ,������������,��������,����·��,ͼƬ·��,ͼƬ����
	fout<<endl<<"#1:PROCESS_START"<<endl;
	fout<<projectName<<endl
		<<projectPath<<endl;
	//fout<<projectDescription<<endl;//�������������ж���,�����������,�ٻ����������
	fout<<projectDescription.length()<<endl
		<<projectDescription<<endl;
	//fout<<projectImagePath<<endl;//ԭͼƬ���½��б���
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

	//step 0.3:��������ǩҳ����ʾ��ͼƬ
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

	//step 1.1:���滭����Ϣ
	if(numOfStep<4)
	{
		fout.close();
		//MessageBox(NULL,CString("�ѳɹ����湤��:")+CString(projectName.c_str()),CString("���湤����ʾ"),MB_OK|MB_ICONWARNING);
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

	//step 1.2:�����Ҳ��ǩҳ����ʾ��ͼƬ
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

	//step 1.3:����ģ����������
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
	//step 2.1:�����Ҳ��ǩҳ����ʾ��ͼƬ
	if(numOfStep<5)
	{
		fout.close();
 		//MessageBox(NULL,CString("�ѳɹ����湤��:")+CString(projectName.c_str()),CString("���湤����ʾ"),MB_OK|MB_ICONWARNING);
		return;
	}

	//step 3.1:�������ƽ��,Ŀǰ��������������Ҫ����
	fout<<endl<<"#6:PROCESS_SIMULATEDONE"<<endl;
	*/
	fout.close();
// 	MessageBox(NULL,CString("�ѳɹ����湤��:")+CString(projectName.c_str()),CString("���湤����ʾ"),MB_OK|MB_ICONWARNING);
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

	//�������ǩҳ
	m_leftView->CloseTabView(numOfUniversal,numOfPortion);

	if(numOfStep==3)
	{
		return;
	}

	//�������Ѿ����ڵ�����
	DeleteData();
}

void CMagicCabsineProject::CloseProjectRightPart(int numOfStep)
{
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	CMagicCabsineRightView *m_rightView=(CMagicCabsineRightView *)mainFrame->m_WndSplitter.GetPane(0,1);

	int numOfUniversal=projectConfig->GetNumOfUniversalProperty();
	int numOfPortion=projectConfig->GetNumOfPortionProperty();

	//�������ǩҳ
	m_leftView->CloseTabView(numOfUniversal,numOfPortion);

	//����Ҳ��ǩҳ
	m_rightView->CloseTabView();

	if(numOfStep>=5)
	{
		return;
	}

	//����Ҳ��Ѿ����ڵ�����
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
	tempCString=dlgFile.GetPathName();//��ȡ�򿪵��ļ�·��
	if(tempCString.Right(4)!=CString(".lzx"))
	{
		MessageBox(NULL,CString("�򿪹���ʧ��,�ļ����ʹ���:\n")+tempCString,CString("�򿪹�����ʾ"),MB_OK|MB_ICONWARNING);
		return;
	}

	int i,j;
	int numOfStep;
	string tempString=tempCString;
	for(i=tempString.length()-1;i>=0&&tempString[i]!='\\';i--);
	string loadPath=tempString.substr(0,i+1);//�ҵ����湤�̵��ļ���·��

	theApp.SetProjectPath(loadPath);

	ifstream fin(tempCString);
	fin>>numOfStep;//��ȡ����״̬,���ݴ˶���������������?????

	//��ȡ�������ñ�,�ļ���ʶ��Ϊ"#0:CONFIG FILE"
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

	//��ȡ������Ϣ��ͼƬ��Ϣ,�ļ���ʶ��Ϊ"#1:PROCESS_START"
	do 
	{
		fin.getline(str,SizeOfStr);
	}while(str[0]!='#');
	fin.getline(str,SizeOfStr);
	projectName=str;
	fin.getline(str,SizeOfStr);
	projectPath=str;
	//�����������ܰ����ü���,�ȶ�ȡchar����,����char��ȡ���������ַ���
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
	//���ݲ�ͬ�Ĺ���״̬��ȡ�洢�ļ�
	if(numOfStep==1 || numOfStep==2)//PROCESS_UNIVERSALCALCED��PROCESS_SPLITED�׶�
	{
		do 
		{
			fin.getline(str,SizeOfStr);
		}while(str[0]!='#');
		InitUniversalPropertyPoint();//��ʼ��ȫ�������������ָ��
		for(i=0;i<numOfUniversal;i++)//��ȡȫ�������洢����
		{
			fin.getline(str,SizeOfStr);
			universalProperties[i]->LoadPropertyFile(loadPath+str);
		}

		//��ȫ�������Ľ��ͼƬ��ʾ����
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

		//��ȡ�����еķָ��ע
		do 
		{
			fin.getline(str,SizeOfStr);
		}while(str[0]!='#');
		InitSplitDataPoint();//��ʼ���ָ��ָ��
		fin.getline(str,SizeOfStr);
		tempString=str;
		splitData->LoadSplitDataFile(loadPath+tempString);//��ȡ�ָ���洢����
		splitData->GetSplitName(stringName);
		m_leftView->displayImageInTab(CString(stringName.c_str()),projectSrcImage,TABTYPE_SPLIT,0);
		m_leftView->myShowTab(TABTYPE_SPLIT,0);
		tempImage=NULL;

		//���û���ǻ����ڱ�ǩҳ��
		splitData->GetUserMark(foreLines,backLines);
		if(foreLines.size()>0||backLines.size()>0)
		{
			interactiveView->SetCvPoint(foreLines,backLines);
		}

		fin>>i;
		if(i==1)//�Ѿ������˷ָ�,��Ҫ���ָ�����ʾ�ڱ�ǩҳ��
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

			interactiveView->SetSplitDone();//�����Ѿ������˷ָ�
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
		//MessageBox(NULL,CString("���̳ɹ���:")+CString(projectName.c_str()),CString("�򿪹�����ʾ"),MB_OK|MB_ICONWARNING);
		fin.close();
		return;
	}

	//PROCESS_LEFTDONE�׶�
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
		//MessageBox(NULL,CString("���̳ɹ���:")+CString(projectName.c_str()),CString("�򿪹�����ʾ"),MB_OK|MB_ICONWARNING);
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

	//PROCESS_SIMULATED�׶�
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
		//MessageBox(NULL,CString("���̳ɹ���:")+CString(projectName.c_str()),CString("�򿪹�����ʾ"),MB_OK|MB_ICONWARNING);
		fin.close();
		return;
	}

	//PROCESS_SIMULATEDONE�׶�
	currentProcessType=PROCESS_DONE;
	//MessageBox(NULL,CString("���̳ɹ���:")+CString(projectName.c_str()),CString("�򿪹�����ʾ"),MB_OK|MB_ICONWARNING);
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
// 		string imageLibraryPath=theApp.GetDefaultPath()+"ImageLibrary\\"+imageName+"\\";//ͼƬ����������ֿ�
		string imageLibraryPath=theApp.GetDefaultPath()+"ImageLibrary\\unclassified\\";
		CreateFolder(CString(imageLibraryPath.c_str()));
		string propertyLibraryPath=theApp.GetDefaultPath()+"PropertyLibrary\\unclassified\\";
		CreateFolder(CString(propertyLibraryPath.c_str()));
		propertyLibraryPath+=imageName+"\\";
		CreateFolder(CString(propertyLibraryPath.c_str()));

		string tempPath=imageLibraryPath+imageName+".jpg";
		cvSaveImage(tempPath.c_str(),theImage);

		//���㲢�������е�ȫ������
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
	MessageBox(NULL,CString("�ɹ�����ͼƬ"),CString("����ͼƬ��ʾ"),MB_OK|MB_ICONINFORMATION);
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
