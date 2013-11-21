#include "stdafx.h"

#include "CMagicCabsineSplitData_Test.h"

CMagicCabsineSplitData_Test::CMagicCabsineSplitData_Test(const IplImage *tempSrcImage)
	:CMagicCabsineSplitData(tempSrcImage)
{
	foregroundPoints.clear();
	backgroundPoints.clear();
	foregroundLines.clear();
	backgroundLines.clear();
	splitName=string("SplitMethodTest");
	splitTips=string("���ڽ���ͼ��ָ�:\n�����ť\"ǰ\"��ǰ���ϱ��\n�����ť\"��\"�ڱ����ϱ��\n�����ť\"��\"������\n�����ť\"��\"���зָ�\n�����ť\"��\"��ɷָ�");
	if(tempSrcImage!=NULL)
	{
		height=tempSrcImage->height;
		width=tempSrcImage->width;
	}
}

CMagicCabsineSplitData_Test::~CMagicCabsineSplitData_Test()
{
	DeleteSplitData();
	height=NULL;
	width=NULL;
}

void CMagicCabsineSplitData_Test::SetUserMark(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines)
{
	foregroundLines=foreLines;
	backgroundLines=backLines;
	int i,j;
	foregroundPoints.clear();
	backgroundPoints.clear();
	for(i=0;i<foreLines.size();i++)
	{
		for(j=0;j<foreLines[i].size();j++)
		{
			foregroundPoints.push_back(foreLines[i][j]);
		}
	}
	for(i=0;i<backLines.size();i++)
	{
		for(j=0;j<backLines[i].size();j++)
		{
			backgroundPoints.push_back(backgroundLines[i][j]);
		}
	}
	isMarked=true;
}

void CMagicCabsineSplitData_Test::GetUserMark(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines)
{
	foreLines=foregroundLines;
	backLines=backgroundLines;
}

void CMagicCabsineSplitData_Test::DrawMarks()
{
	if(markImage!=NULL)
	{
		cvReleaseImage(&markImage);
		markImage=NULL;
	}
	//�Ƚ�ͼƬ��Ϊȫ��ɫ
	markImage=cvCloneImage(srcImage);
//	SetImageToOneColor(markImage,cvScalar(255,255,255));

	CvScalar redColor=cvScalar(0,0,255);//��ɫ���ǰ������
	CvScalar blueColor=cvScalar(255,0,0);//��ɫ��Ǳ�������
	int i,x,y;
	int height=srcImage->height;
	int width=srcImage->width;
	for(i=0;i<foregroundPoints.size();i++)
	{
		x=foregroundPoints[i].x;
		y=foregroundPoints[i].y;
		if(x<0||x>=height||y<0||y>=width)
		{
			continue;//�����곬��ͼ��ߴ�
		}
		cvSet2D(markImage,x,y,redColor);
	}
	for(i=0;i<backgroundPoints.size();i++)
	{
		x=backgroundPoints[i].x;
		y=backgroundPoints[i].y;
		if(x<0||x>=height||y<0||y>=width)
		{
			continue;//�����곬��ͼ��ߴ�
		}
		cvSet2D(markImage,x,y,blueColor);
	}
}

void CMagicCabsineSplitData_Test::LoadSplitData()
{
	//Ŀǰ��ʱ�ȴ��ļ��ж�ȡ
// 	LoadSplitDataFile(theApp.GetDefaultPath()+"SPLITres.txt");
	LoadSplitDataFile(theApp.GetProjectPath()+"SPLITres.txt");
}

void CMagicCabsineSplitData_Test::SaveSplitData()
{
	//Ŀǰ��ʱ�������ļ���
// 	SaveSplitDataFile(theApp.GetDefaultPath()+"SPLITres.txt");
	SaveSplitDataFile(theApp.GetProjectPath()+"SPLITres.txt");
}

void CMagicCabsineSplitData_Test::LoadSplitDataFile(string filepath)
{
	int i,j;
	string tempPath=filepath.substr(0,filepath.size()-10)+"MARKres.txt";
	ifstream ffin(tempPath);
	int numOfForeLines,numOfBackLines,numOfPoints,xx,yy;
	ffin>>numOfForeLines>>numOfBackLines;
	CvPoint tempPoint;
	vector<CvPoint> tempLine;
	foregroundLines.clear();
	foregroundPoints.clear();
	for(i=0;i<numOfForeLines;i++)
	{
		ffin>>numOfPoints;
		tempLine.clear();
		for(j=0;j<numOfPoints;j++)
		{
			ffin>>xx>>yy;
			tempPoint.x=xx;
			tempPoint.y=yy;
			tempLine.push_back(tempPoint);
			foregroundPoints.push_back(tempPoint);
		}
		foregroundLines.push_back(tempLine);
	}
	backgroundLines.clear();
	for(i=0;i<numOfBackLines;i++)
	{
		ffin>>numOfPoints;
		tempLine.clear();
		for(j=0;j<numOfPoints;j++)
		{
			ffin>>xx>>yy;
			tempPoint.x=xx;
			tempPoint.y=yy;
			tempLine.push_back(tempPoint);
			backgroundPoints.push_back(tempPoint);
		}
		backgroundLines.push_back(tempLine);
	}
	ffin.close();
	if(foregroundPoints.size()>0||backgroundPoints.size()>0)
	{
		isMarked=true;
	}
	else
	{
		isMarked=false;
	}

	ifstream fin(filepath);
	fin>>height>>width;
	//ע������height��width�����������ܳ���ͬʱΪ0�����
	//���������ʾ�������Ϣ��ֻ���û����û�м���ָ����
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fin>>splitMatrix[i][j];
		}
	}
	fin.close();

	if(height==0&&width==0)
	{
		isCalced=false;
		return;
	}

	tempPath=filepath.substr(0,filepath.size()-10)+"BOUNDARYresult.bmp";
	boundaryImage=cvLoadImage(tempPath.c_str(),1);
	tempPath=filepath.substr(0,filepath.size()-10)+"result.bmp";
	displayImage=cvLoadImage(tempPath.c_str(),1);
	isCalced=true;

// 	tempPath=filepath.substr(0,filepath.size()-10);
// 	tempPath+=string("MARKres.bmp");
// 	markImage=cvLoadImage(tempPath.c_str(),1);
// 	foregroundPoints.clear();
// 	backgroundPoints.clear();
// 	CvScalar tempColor;
// 	int b,g,r;
// 	for(i=0;i<height;i++)
// 	{
// 	 	for(j=0;j<width;j++)
// 	 	{
// 	 		tempColor=cvGet2D(markImage,i,j);
// 	 		b=(int)(tempColor.val[0]);
// 	 		g=(int)(tempColor.val[1]);
// 	 		r=(int)(tempColor.val[2]);
// 	 		if(b==255&&g==255&&r==255)
// 	 		{
// 	 			continue;
// 	 		}
// 	 		if(r==255)
// 	 		{
// 	 			foregroundPoints.push_back(cvPoint(i,j));
// 	 		}
// 	 		else
// 	 		{
// 				backgroundPoints.push_back(cvPoint(i,j));
// 	 		}
// 	 	}
// 	}
// 	if(foregroundPoints.size()>0||backgroundPoints.size()>0)
// 	{
// 	 	isMarked=true;
// 	}
// 	else
// 	{
// 	 	isMarked=false;
// 	}
}

void CMagicCabsineSplitData_Test::SaveSplitDataFile(string filepath)
{
// 	if(markImage==NULL)
// 	{
// 	 	DrawMarks();
// 	}
// 	string tempPath=filepath.substr(0,filepath.size()-10);
// 	tempPath+=string("MARKres.bmp");
// 	cvSaveImage(tempPath.c_str(),markImage);

	int i,j;
	string tempPath=filepath.substr(0,filepath.size()-10)+"MARKres.txt";
	ofstream ffout(tempPath);
	ffout<<foregroundLines.size()<<' '<<backgroundLines.size()<<endl;
	for(i=0;i<foregroundLines.size();i++)
	{
		ffout<<foregroundLines[i].size()<<endl;
		for(j=0;j<foregroundLines[i].size();j++)
		{
			ffout<<foregroundLines[i][j].x<<' '<<foregroundLines[i][j].y<<endl;
		}
	}
	for(i=0;i<backgroundLines.size();i++)
	{
		ffout<<backgroundLines[i].size()<<endl;
		for(j=0;j<backgroundLines[i].size();j++)
		{
			ffout<<backgroundLines[i][j].x<<' '<<backgroundLines[i][j].y<<endl;
		}
	}
	ffout.close();

	//�п������û���ǵ���û�м�����ָ��������
	//��������·ָ����ĳ�����Ϊ0,û�������������,loadʱ�����ж�������ֵ
	ofstream fout(filepath);
	if(!isCalced)//ֻ���û����,û�м���ָ����
	{
		fout<<"0 0"<<endl;
		fout.close();
		return;
	}
	fout<<height<<' '<<width<<endl;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fout<<splitMatrix[i][j]<<' ';
		}
		fout<<endl;
	}
	fout.close();

	tempPath=filepath.substr(0,filepath.size()-10)+"BOUNDARYresult.bmp";
	cvSaveImage(tempPath.c_str(),boundaryImage);
	tempPath=filepath.substr(0,filepath.size()-10)+"result.bmp";
	cvSaveImage(tempPath.c_str(),displayImage);
}

void CMagicCabsineSplitData_Test::ComputeSplitData()
{
	int i,j;
// 	ifstream fin(theApp.GetDefaultPath()+"SPLITTEST.txt");
	ifstream fin(theApp.GetProjectPath()+"SPLITTEST.txt");
	fin>>height>>width;
	height=srcImage->height;
	width=srcImage->width;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fin>>splitMatrix[i][j];
		}
	}
// 	string tempPath=theApp.GetDefaultPath()+"SPLITTEST.bmp";
	string tempPath=theApp.GetProjectPath()+"SPLITTEST.bmp";
	displayImage=cvLoadImage(tempPath.c_str(),1);
// 	tempPath=theApp.GetDefaultPath()+"SPLITBOUNDARY.bmp";
	tempPath=theApp.GetProjectPath()+"SPLITBOUNDARY.bmp";
	boundaryImage=cvLoadImage(tempPath.c_str(),1);

	isCalced=true;
	fin.close();
}

void CMagicCabsineSplitData_Test::DeleteSplitData()
{
	foregroundPoints.clear();
	backgroundPoints.clear();
	foregroundLines.clear();
	backgroundLines.clear();
}
