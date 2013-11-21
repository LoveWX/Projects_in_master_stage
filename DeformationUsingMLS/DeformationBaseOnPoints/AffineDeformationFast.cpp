#include "AffineDeformationFast.h"

/*
class AffineDeformationFast
{
public:
	AffineDeformationFast();										//默认构造函数，需指定newControlPoint和commonPoint之后才能进行形变
	AffineDeformationFast(vector<Point> &oldCP);					//含参构造函数，需指定newControlPoint和commonPoint之后才能进行形变
	~AffineDeformationFast();										//析构函数
	void UpdateControlPoint(vector<Point> &newCP);					//仅更新形变后控制点，预计算内容不用改变
	void UpdateCommonPoint(vector<Point> &newCommonPoint);			//仅更新非控制点，预计算内容需要改变
	//void AffineDeformationOfOnePoint(Point &thepoint);			//取消对单个点进行形变的函数，因为无法使用预计算的结果
	int getNumOfControlPoint()const;								//返回控制点个数
	void getResultofCommonPoint(vector<Point> &resultPoint);		//调用doAffineDeformation()进行形变并将结果拷贝到resultPoint中
protected:
	static const double alpha;										//参数alpha
	vector<Point> precomputedpart;									//预计算后前半部分结果存储
	vector<Point> oldControlPoint;									//形变前控制点
	vector<Point> commonPoint;										//非控制点
	vector<Point> newControlPoint;									//形变后控制点
	vector<Point> ansPoint;											//保存计算结果，而不是保存在commonPoint中
	double *sumofw;													//对于每个非控制点存储w值的和(控制点个数个w值)，长度为非控制点个数
	vector< vector<double> > w;										//存储中间结果w值，w[非控制点下标][控制点下标]
	vector< vector<double> > A;										//存储中间结果A值，A[非控制点下标][控制点下标]
	bool isPreComputed;												//对于当前的commonPoint，预计算程序是否运行过
	bool isComputed;												//commonPoint是否已经按照控制点更新过
	double tempMatrix[2][2];										//临时2*2矩阵
	void cleartempMatrix();											//清空临时矩阵tempMatrix
	void doubleswap(double &a,double &b);							//交换两个double
	double doubleabs(double a)const;								//求一个double的绝对值
	int isControlPoint(const Point &thepoint)const;					//判断一个点是不是控制点
	void doAffineDeformation();										//调用预计算结果对所有非控制点进行形变，用形变结果更新commonPoint向量
	void calcA();													//预计算函数，结果存放在A向量中
};
*/

const double AffineDeformationFast::alpha=1.0;

AffineDeformationFast::AffineDeformationFast()
{
	precomputedpart.clear();
	oldControlPoint.clear();
	commonPoint.clear();
	newControlPoint.clear();
	ansPoint.clear();
	sumofw=NULL;
	A.clear();
	w.clear();
	isPreComputed=false;
	isComputed=false;
}

AffineDeformationFast::AffineDeformationFast(vector<Point> &oldCP)
{
	precomputedpart.clear();
	oldControlPoint=oldCP;
	commonPoint.clear();
	newControlPoint.clear();
	ansPoint.clear();
	sumofw=NULL;
	A.clear();
	w.clear();
	isPreComputed=false;
	isComputed=false;
}

AffineDeformationFast::~AffineDeformationFast()
{
	precomputedpart.clear();
	oldControlPoint.clear();
	commonPoint.clear();
	newControlPoint.clear();
	ansPoint.clear();
	if(sumofw!=NULL)
	{
		delete[] sumofw;
		sumofw=NULL;
	}
	w.clear();
	A.clear();
	isPreComputed=false;
	isComputed=false;
}

void AffineDeformationFast::UpdateControlPoint(vector<Point> &newCP)
{
	newControlPoint=newCP;
	isComputed=false;
}

void AffineDeformationFast::UpdateCommonPoint(vector<Point> &newCommonPoint)
{
	commonPoint=newCommonPoint;
	isPreComputed=false;
	isComputed=false;
}

void AffineDeformationFast::calcA()
{
	int i,j;
	double sumofwpx,sumofwpy;
	Point *pstar=new Point[commonPoint.size()];
	if(sumofw!=NULL)
	{
		delete[] sumofw;
		sumofw=NULL;
	}
	sumofw=new double[commonPoint.size()];
	w.clear();//w[非控制点下标][控制点下标]
	vector<double> tempVector(oldControlPoint.size(),0.0);

	precomputedpart=commonPoint;
	for(i=0;i<commonPoint.size();i++)
	{
		if(isControlPoint(commonPoint[i])>=0)//是控制点,不需要计算w值
		{
			w.push_back(tempVector);
			continue;
		}
		sumofw[i]=0.0;
		sumofwpx=0.0;
		sumofwpy=0.0;
		for(j=0;j<oldControlPoint.size();j++)
		{
			double t1=oldControlPoint[j].xx-commonPoint[i].xx;
			double t2=oldControlPoint[j].yy-commonPoint[i].yy;
			t1=1.0/pow(t1*t1+t2*t2,alpha);
			sumofw[i]+=t1;
			sumofwpx+=t1*oldControlPoint[j].xx;
			sumofwpy+=t1*oldControlPoint[j].yy;
			tempVector[j]=t1;
		}
		pstar[i].xx=sumofwpx/sumofw[i];
		pstar[i].yy=sumofwpy/sumofw[i];
		precomputedpart[i].xx=commonPoint[i].xx-pstar[i].xx;
		precomputedpart[i].yy=commonPoint[i].yy-pstar[i].yy;
		w.push_back(tempVector);

		cleartempMatrix();
		for(j=0;j<oldControlPoint.size();j++)
		{
			double a=oldControlPoint[j].xx-pstar[i].xx;
			double b=oldControlPoint[j].yy-pstar[i].yy;
			tempMatrix[0][0]+=tempVector[j]*a*a;
			tempMatrix[1][1]+=tempVector[j]*b*b;
			a*=b;
			tempMatrix[0][1]+=tempVector[j]*a;
			tempMatrix[1][0]+=tempVector[j]*a;
		}
		double tt,dt=tempMatrix[0][0]*tempMatrix[1][1]-tempMatrix[0][1]*tempMatrix[1][0];
		doubleswap(tempMatrix[0][0],tempMatrix[1][1]);
		tempMatrix[0][0]/=dt;
		tempMatrix[1][1]/=dt;
		tempMatrix[0][1]/=(-dt);
		tempMatrix[1][0]/=(-dt);
		tt=precomputedpart[i].xx*tempMatrix[0][0]+precomputedpart[i].yy*tempMatrix[1][0];
		dt=precomputedpart[i].xx*tempMatrix[0][1]+precomputedpart[i].yy*tempMatrix[1][1];
		precomputedpart[i].xx=tt;
		precomputedpart[i].yy=dt;
	}

	A.clear();//A[非控制点下标][控制点下标]
	for(i=0;i<commonPoint.size();i++)
	{
		if(isControlPoint(commonPoint[i])>=0)//是控制点,不需要计算w值
		{
			A.push_back(tempVector);
			continue;
		}
		for(j=0;j<oldControlPoint.size();j++)
		{
			Point tempPoint;
			tempPoint.xx=oldControlPoint[j].xx-pstar[i].xx;
			tempPoint.yy=oldControlPoint[j].yy-pstar[i].yy;
			tempVector[j]=w[i][j]*(precomputedpart[i].xx*tempPoint.xx+precomputedpart[i].yy*tempPoint.yy);
		}
		A.push_back(tempVector);
	}
	delete[] pstar;

	isPreComputed=true;
}

int AffineDeformationFast::getNumOfControlPoint()const
{
	return oldControlPoint.size();
}

void AffineDeformationFast::getResultofCommonPoint(vector<Point> &resultPoint)
{
	if(!isComputed)
	{
		doAffineDeformation();
	}
	resultPoint=ansPoint;
}

void AffineDeformationFast::cleartempMatrix()
{
	tempMatrix[0][0]=0;
	tempMatrix[0][1]=0;
	tempMatrix[1][0]=0;
	tempMatrix[1][1]=0;
}

void AffineDeformationFast::doubleswap(double &a,double &b)
{
	double temp=a;
	a=b;
	b=temp;
}

double AffineDeformationFast::doubleabs(double a)const
{
	if(a<0)
	{
		return -a;
	}
	return a;
}

int AffineDeformationFast::isControlPoint(const Point &thepoint)const
{
	int i;
	for(i=0;i<oldControlPoint.size();i++)
	{
		if(doubleabs(thepoint.xx-oldControlPoint[i].xx)<0.0001&&doubleabs(thepoint.yy-oldControlPoint[i].yy)<0.0001)
		{
			return i;
		}
	}
	return -1;
}

void AffineDeformationFast::doAffineDeformation()
{
	if(oldControlPoint.size()!=newControlPoint.size())
	{
		return;//控制点形变前后数目不等，不能形变
	}

	if(!isPreComputed)
	{
		calcA();
	}

	int i,j;
	Point tempPoint,qstar;
	double sumofwqx,sumofwqy;
	ansPoint=commonPoint;
	for(i=0;i<ansPoint.size();i++)
	{
		if((j=isControlPoint(commonPoint[i]))>=0)
		{
			ansPoint[i].xx=newControlPoint[j].xx;
			ansPoint[i].yy=newControlPoint[j].yy;
			continue;
		}

		sumofwqx=0.0;
		sumofwqy=0.0;
		for(j=0;j<oldControlPoint.size();j++)
		{
			sumofwqx+=w[i][j]*newControlPoint[j].xx;
			sumofwqy+=w[i][j]*newControlPoint[j].yy;
		}
		qstar.xx=sumofwqx/sumofw[i];
		qstar.yy=sumofwqy/sumofw[i];
		
		tempPoint.xx=0;
		tempPoint.yy=0;
		for(j=0;j<oldControlPoint.size();j++)
		{
			tempPoint.xx+=A[i][j]*(newControlPoint[j].xx-qstar.xx);
			tempPoint.yy+=A[i][j]*(newControlPoint[j].yy-qstar.yy);
		}
		ansPoint[i].xx=tempPoint.xx+qstar.xx;
		ansPoint[i].yy=tempPoint.yy+qstar.yy;
	}

	isComputed=true;
}
