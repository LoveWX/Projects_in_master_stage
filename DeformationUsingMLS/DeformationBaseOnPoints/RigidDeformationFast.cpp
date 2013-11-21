#include "RigidDeformationFast.h"

/*
class RigidDeformationFast
{
public:
	RigidDeformationFast();											//默认构造函数，需指定newControlPoint和CommonPoint之后才能进行形变
	RigidDeformationFast(vector<Point> &oldCP);						//含参构造函数，需指定newControlPoint和CommonPoint之后才能进行形变
	~RigidDeformationFast();										//析构函数
	void UpdateControlPoint(vector<Point> &newCP);					//仅更新形变后控制点，预计算内容不用改变
	void UpdateCommonPoint(vector<Point> &newCommonPoint);			//仅更新非控制点，预计算内容需要改变
	int getNumOfControlPoint()const;								//返回控制点个数
	void getResultofCommonPoint(vector<Point> &resultPoint);		//调用doRigidDeformation()进行形变并将结果拷贝到resultPoint中
protected:
	static const double alpha;										//参数alpha
	vector<Point> oldControlPoint;									//形变前控制点
	vector<Point> commonPoint;										//非控制点
	vector<Point> newControlPoint;									//形变后控制点
	vector<Point> ansPoint;											//保存计算结果，而不是保存在commonPoint中
	double *lengthofvp;												//向量v-pstar的长度
	double *sumofw;													//对于每个非控制点存储w值的和(控制点个数个w值)，长度为非控制点个数
	vector< vector<double> > w;										//存储中间结果w值，w[非控制点下标][控制点下标]
	vector< vector<Point> > A;										//存储中间结果A值，A[非控制点下标][控制点下标]
	bool isPreComputed;												//对于当前的commonPoint，预计算程序是否运行过
	bool isComputed;												//commonPoint是否已经按照控制点更新过
	void doubleswap(double &a,double &b);							//交换两个double
	double doubleabs(double a)const;								//求一个double的绝对值
	int isControlPoint(const Point &thepoint)const;					//判断一个点是不是控制点
	void doRigidDeformation();										//调用预计算结果对所有非控制点进行形变，用形变结果更新CommonPoint向量
	void calcA();													//预计算函数，结果存放在A向量中
};
*/

const double RigidDeformationFast::alpha=1.0;

RigidDeformationFast::RigidDeformationFast()
{
	oldControlPoint.clear();
	commonPoint.clear();
	newControlPoint.clear();
	ansPoint.clear();
	sumofw=NULL;
	lengthofvp=NULL;
	w.clear();
	A.clear();
	isPreComputed=false;
	isComputed=false;
}

RigidDeformationFast::RigidDeformationFast(vector<Point> &oldCP)
{
	oldControlPoint=oldCP;
	commonPoint.clear();
	newControlPoint.clear();
	ansPoint.clear();
	sumofw=NULL;
	lengthofvp=NULL;
	w.clear();
	A.clear();
	isPreComputed=false;
	isComputed=false;
}

RigidDeformationFast::~RigidDeformationFast()
{
	oldControlPoint.clear();
	commonPoint.clear();
	newControlPoint.clear();
	ansPoint.clear();
	if(sumofw!=NULL)
	{
		delete[] sumofw;
		sumofw=NULL;
	}
	if(lengthofvp!=NULL)
	{
		delete[] lengthofvp;
		lengthofvp=NULL;
	}
	w.clear();
	A.clear();
	isPreComputed=false;
	isComputed=false;
}

void RigidDeformationFast::UpdateControlPoint(vector<Point> &newCP)
{
	newControlPoint=newCP;
	isComputed=false;
}

void RigidDeformationFast::UpdateCommonPoint(vector<Point> &newCommonPoint)
{
	commonPoint=newCommonPoint;
	isPreComputed=false;
	isComputed=false;
}

int RigidDeformationFast::getNumOfControlPoint()const
{
	return oldControlPoint.size();
}

void RigidDeformationFast::doubleswap(double &a,double &b)
{
	double temp=a;
	a=b;
	b=temp;
}

double RigidDeformationFast::doubleabs(double a)const
{
	if(a<0)
	{
		return -a;
	}
	return a;
}

int RigidDeformationFast::isControlPoint(const Point &thepoint)const
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

void RigidDeformationFast::getResultofCommonPoint(vector<Point> &resultPoint)
{
	if(!isComputed)
	{
		doRigidDeformation();
	}
	resultPoint=ansPoint;
}

void RigidDeformationFast::calcA()
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
	if(lengthofvp!=NULL)
	{
		delete[] lengthofvp;
		lengthofvp=NULL;
	}
	lengthofvp=new double[commonPoint.size()];
	w.clear();//w[非控制点下标][控制点下标]
	vector<double> tempVector(oldControlPoint.size(),0.0);

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
		w.push_back(tempVector);
	}

	A.clear();//[非控制点下标][控制点下标]
	Point pA,vp;
	vp.xx=0.0;
	vp.yy=0.0;
	vector<Point> tempPointVector(oldControlPoint.size(),vp);
	for(i=0;i<commonPoint.size();i++)
	{
		vp.xx=commonPoint[i].xx-pstar[i].xx;
		vp.yy=commonPoint[i].yy-pstar[i].yy;
		lengthofvp[i]=sqrt(vp.xx*vp.xx+vp.yy*vp.yy);

		for(j=0;j<oldControlPoint.size();j++)
		{
			pA.xx=oldControlPoint[j].xx-pstar[i].xx;
			pA.yy=oldControlPoint[j].yy-pstar[i].yy;

			/*
			//Aj = | a , b | * | c , d | = | ac+bd , ad-bc |
			//	   | b ,-a |   | d ,-c |   | bc-ad , bd+ac |
			//上式中||包括的部分为2*2矩阵。由于有这样的性质，所以A中只保存4个元素中的2个
			//即Aj = ( ac+bd , ad-bc )
			*/
			//A[i][j].xx=w[i][j]*(pA.xx*vp.xx+pA.yy*vp.yy);
			//A[i][j].yy=w[i][j]*(pA.xx*vp.yy-pA.yy*vp.xx);

			tempPointVector[j].xx=w[i][j]*(pA.xx*vp.xx+pA.yy*vp.yy);
			tempPointVector[j].yy=w[i][j]*(pA.xx*vp.yy-pA.yy*vp.xx);
		}
		A.push_back(tempPointVector);
	}
	delete[] pstar;

	isPreComputed=true;
}

void RigidDeformationFast::doRigidDeformation()
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
	Point tempPoint,sumPoint,qstar;
	double sumofwqx,sumofwqy,lengthoffrv;
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
		
		sumPoint.xx=0;
		sumPoint.yy=0;
		for(j=0;j<oldControlPoint.size();j++)
		{
			tempPoint.xx=newControlPoint[j].xx-qstar.xx;
			tempPoint.yy=newControlPoint[j].yy-qstar.yy;
			sumPoint.xx+=(tempPoint.xx*A[i][j].xx-tempPoint.yy*A[i][j].yy);
			sumPoint.yy+=(tempPoint.xx*A[i][j].yy+tempPoint.yy*A[i][j].xx);
		}
		lengthoffrv=sqrt(sumPoint.xx*sumPoint.xx+sumPoint.yy*sumPoint.yy);

		ansPoint[i].xx=sumPoint.xx*lengthofvp[i]/lengthoffrv+qstar.xx;
		ansPoint[i].yy=sumPoint.yy*lengthofvp[i]/lengthoffrv+qstar.yy;
	}
	
	isComputed=true;
}
