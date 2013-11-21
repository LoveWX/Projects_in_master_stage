#include "AffineLinesFast.h"

/*
class AffineLinesFast
{
public:
	AffineLinesFast();												//默认构造函数，需指定oldControlLine和newControlLine和commonPoint之后才能进行形变
	AffineLinesFast(vector<Segment> &oldCS);						//含参构造函数，需指定newControlLine和commonPoint之后才能进行形变
	~AffineLinesFast();												//析构函数
	void UpdateControlLine(vector<Segment> &newCS);					//仅更新形变后控制线段的位置
	void UpdateCommonPoint(vector<Point> &newCommonPoint);			//仅更新非控制点
	//void AffineLinesSlowOfOnePoint(Point &thepoint);				//取消对单个点进行形变的函数，因为无法使用预计算的结果
	int getNumOfControlLine()const;									//返回控制线段个数
	void getResultofCommonPoint(vector<Point> &resultPoint);		//调用doAffineLinesFast()进行形变并将结果拷贝到resultPoint中
protected:
	vector<Segment> oldControlLine;									//形变前控制线段
	vector<Segment> newControlLine;									//形变后控制线段
	vector<Point> precomputedpart;									//预计算后前半部分结果存储
	vector<Point> commonPoint;										//非控制点
	vector<Point> ansPoint;											//保存计算结果，而不是保存在commonPoint中
	int alpha;														//参数alpha
	double eps;														//1e-8
	double *sumofw;													//对于每个非控制点存储w值的和(控制点个数个w值)，长度为非控制点个数
	vector< vector<double> > delta00;								//存储中间结果delta00值，delta00[非控制点下标][控制点下标]
	vector< vector<double> > delta01;								//存储中间结果delta01值，delta01[非控制点下标][控制点下标]
	vector< vector<double> > delta11;								//存储中间结果delta11值，delta11[非控制点下标][控制点下标]
	vector< vector<Point> > A;										//存储中间结果A值，A[非控制点下标][控制点下标]
	double tempMatrix1[2][2];										//临时2*2矩阵
	double tempMatrix2[2][2];										//临时2*2矩阵
	double tempMatrix3[2][2];										//临时2*2矩阵
	bool isPreComputed;												//对于当前的commonPoint，预计算程序是否运行过
	bool isComputed;												//commonPoint是否已经按照控制点更新过
	void productoftwoMatrix();										//tempMatrix1*tempMatrix2，结果保存在tempMatrix1中
	void cleartempMatrix();											//清空临时矩阵tempMatrix1和tempMatrix2和tempMatrix3
	void doubleswap(double &a,double &b);							//交换两个double
	double doubleabs(double a)const;								//求一个double的绝对值
	int isOnControlLine(const Point &thepoint);						//判断一个点是不是在控制线段上
	void doAffineLinesFast();										//调用预计算结果对所有非控制点进行形变，形变结果保存在ansPoint向量中
	void calcA();													//预计算函数，结果存放在A向量中
};
*/

AffineLinesFast::AffineLinesFast()
{
	oldControlLine.clear();
	newControlLine.clear();
	precomputedpart.clear();
	commonPoint.clear();
	ansPoint.clear();
	alpha=2;
	eps=1e-8;
	sumofw=NULL;
	delta00.clear();
	delta01.clear();
	delta11.clear();
	A.clear();
	isPreComputed=false;
	isComputed=false;
}

AffineLinesFast::AffineLinesFast(vector<Segment> &oldCS)
{
	oldControlLine=oldCS;
	newControlLine.clear();
	precomputedpart.clear();
	commonPoint.clear();
	ansPoint.clear();
	alpha=2;
	eps=1e-8;
	sumofw=NULL;
	delta00.clear();
	delta01.clear();
	delta11.clear();
	A.clear();
	isPreComputed=false;
	isComputed=false;
}

AffineLinesFast::~AffineLinesFast()
{
	oldControlLine.clear();
	newControlLine.clear();
	precomputedpart.clear();
	commonPoint.clear();
	ansPoint.clear();
	if(sumofw!=NULL)
	{
		delete[] sumofw;
		sumofw=NULL;
	}
	delta00.clear();
	delta01.clear();
	delta11.clear();
	A.clear();
	isPreComputed=false;
	isComputed=false;
}

void AffineLinesFast::UpdateControlLine(vector<Segment> &newCS)
{
	newControlLine=newCS;
	isComputed=false;
}

void AffineLinesFast::UpdateCommonPoint(vector<Point> &newCommonPoint)
{
	commonPoint=newCommonPoint;
	isPreComputed=false;
	isComputed=false;
}

void AffineLinesFast::calcA()
{
	int i,j;
	double td1,td2;
	Point tp1,tp2,tp3;
	double dt1,dt2,dt3,dt4,dt5;
	vector<double> tempVector00(oldControlLine.size(),0.0);
	vector<double> tempVector01(oldControlLine.size(),0.0);
	vector<double> tempVector11(oldControlLine.size(),0.0);
	tp1.xx=0.0;
	tp1.yy=0.0;
	vector<Point> tempPointVector(oldControlLine.size(),tp1);

	Point *pstar=new Point[commonPoint.size()];
	if(sumofw!=NULL)
	{
		delete[] sumofw;
		sumofw=NULL;
	}
	sumofw=new double[commonPoint.size()];
	delta00.clear();//delta00[非控制点下标][控制点下标]
	delta01.clear();//delta01[非控制点下标][控制点下标]
	delta11.clear();//delta11[非控制点下标][控制点下标]

	precomputedpart=commonPoint;
	for(i=0;i<commonPoint.size();i++)
	{
		if(isOnControlLine(commonPoint[i])>=0)//非控制点在控制线段上,不需要计算delta00,delta01,delta11
		{
			delta00.push_back(tempVector00);
			delta01.push_back(tempVector01);
			delta11.push_back(tempVector11);
			continue;
		}

		for(j=0;j<oldControlLine.size();j++)
		{
			tp1=oldControlLine[j].pa-commonPoint[i];
			tp2=commonPoint[i]-oldControlLine[j].pb;
			tp3=oldControlLine[j].pb-oldControlLine[j].pa;
			dt1=tp1.yy*tp3.xx-tp1.xx*tp3.yy;
			if(doubleabs(dt1)<eps)
			{
				td2=tp3.xx*tp3.xx+tp3.yy*tp3.yy;
				td1=sqrt(td2);
				dt2=tp2.xx*tp3.xx+tp2.yy*tp3.yy;
				dt3=tp1.xx*tp3.xx+tp1.yy*tp3.yy;
				td1=td2*td2*td1;
				tempVector00[j]=-td1/(3.0*dt2*dt3*dt3*dt3);
				tempVector01[j]=td1/(6.0*dt2*dt2*dt3*dt3);
				tempVector11[j]=-td1/(3.0*dt2*dt2*dt2*dt3);
				continue;
			}
			dt3=-(tp2.xx*tp3.xx+tp2.yy*tp3.yy);
			dt4=tp2.yy*tp3.xx-tp2.xx*tp3.yy;
			dt5=-(tp1.xx*tp3.xx+tp1.yy*tp3.yy);
			dt2=atan(dt3/dt4)-atan(dt5/dt1);
			dt2/=dt1;
			dt3=tp1.xx*tp1.xx+tp1.yy*tp1.yy;
			dt4=tp1.xx*tp2.xx+tp1.yy*tp2.yy;
			dt5=tp2.xx*tp2.xx+tp2.yy*tp2.yy;
			td1=sqrt(tp3.xx*tp3.xx+tp3.yy*tp3.yy)*0.5/(dt1*dt1);
			tempVector00[j]=td1*(dt4/dt3-dt5*dt2);
			tempVector01[j]=td1*(1.0-dt4*dt2);
			tempVector11[j]=td1*(dt4/dt5-dt3*dt2);
		}

		sumofw[i]=0.0;
		pstar[i].xx=0.0;
		pstar[i].yy=0.0;
		for(j=0;j<oldControlLine.size();j++)
		{
			td1=tempVector00[j]+tempVector01[j];
			td2=tempVector01[j]+tempVector11[j];
			pstar[i].xx+=oldControlLine[j].pa.xx*td1+oldControlLine[j].pb.xx*td2;
			pstar[i].yy+=oldControlLine[j].pa.yy*td1+oldControlLine[j].pb.yy*td2;
			dt1=td1+td2;
			sumofw[i]+=dt1;
		}
		pstar[i].xx/=sumofw[i];
		pstar[i].yy/=sumofw[i];
		delta00.push_back(tempVector00);
		delta01.push_back(tempVector01);
		delta11.push_back(tempVector11);

		cleartempMatrix();
		for(j=0;j<oldControlLine.size();j++)
		{
			tp1=oldControlLine[j].pa-pstar[i];
			tp2=oldControlLine[j].pb-pstar[i];
			tempMatrix1[0][0]=tp1.xx;
			tempMatrix1[0][1]=tp2.xx;
			tempMatrix1[1][0]=tp1.yy;
			tempMatrix1[1][1]=tp2.yy;
			tempMatrix2[0][0]=tempVector00[j];
			tempMatrix2[0][1]=tempVector01[j];
			tempMatrix2[1][0]=tempVector01[j];
			tempMatrix2[1][1]=tempVector11[j];
			productoftwoMatrix();
			tempMatrix2[0][0]=tp1.xx;
			tempMatrix2[0][1]=tp1.yy;
			tempMatrix2[1][0]=tp2.xx;
			tempMatrix2[1][1]=tp2.yy;
			productoftwoMatrix();
			tempMatrix3[0][0]+=tempMatrix1[0][0];
			tempMatrix3[0][1]+=tempMatrix1[0][1];
			tempMatrix3[1][0]+=tempMatrix1[1][0];
			tempMatrix3[1][1]+=tempMatrix1[1][1];
		}
		dt1=tempMatrix3[0][0]*tempMatrix3[1][1]-tempMatrix3[0][1]*tempMatrix3[1][0];
		
		dt1=1.0/dt1;
		tempMatrix1[0][0]=tempMatrix3[1][1]*dt1;
		tempMatrix1[0][1]=tempMatrix3[0][1]*(-dt1);
		tempMatrix1[1][0]=tempMatrix3[1][0]*(-dt1);
		tempMatrix1[1][1]=tempMatrix3[0][0]*dt1;

		tp1=commonPoint[i]-pstar[i];
		precomputedpart[i].xx=tp1.xx*tempMatrix1[0][0]+tp1.yy*tempMatrix1[1][0];
		precomputedpart[i].yy=tp1.xx*tempMatrix1[0][1]+tp1.yy*tempMatrix1[1][1];
	}

	A.clear();
	for(i=0;i<commonPoint.size();i++)
	{
		if(isOnControlLine(commonPoint[i])>=0)//非控制点在控制线段上,不需要计算相应的A值
		{
			A.push_back(tempPointVector);
			continue;
		}
		for(j=0;j<oldControlLine.size();j++)
		{
			tp1=oldControlLine[j].pa-pstar[i];
			tp2=oldControlLine[j].pb-pstar[i];
			td1=precomputedpart[i].xx*tp1.xx+precomputedpart[i].yy*tp1.yy;
			td2=precomputedpart[i].xx*tp2.xx+precomputedpart[i].yy*tp2.yy;
			tempPointVector[j].xx=td1*delta00[i][j]+td2*delta01[i][j];
			tempPointVector[j].yy=td1*delta01[i][j]+td2*delta11[i][j];
		}
		A.push_back(tempPointVector);
	}
	delete[] pstar;

	isPreComputed=true;
}

int AffineLinesFast::getNumOfControlLine()const
{
	return oldControlLine.size();
}

void AffineLinesFast::getResultofCommonPoint(vector<Point> &resultPoint)
{
	if(!isComputed)
	{
		doAffineLinesFast();
	}
	resultPoint=ansPoint;
}

void AffineLinesFast::productoftwoMatrix()
{
	double temp[2][2];
	temp[0][0]=tempMatrix1[0][0]*tempMatrix2[0][0]+tempMatrix1[0][1]*tempMatrix2[1][0];
	temp[0][1]=tempMatrix1[0][0]*tempMatrix2[0][1]+tempMatrix1[0][1]*tempMatrix2[1][1];
	temp[1][0]=tempMatrix1[1][0]*tempMatrix2[0][0]+tempMatrix1[1][1]*tempMatrix2[1][0];
	temp[1][1]=tempMatrix1[1][0]*tempMatrix2[0][1]+tempMatrix1[1][1]*tempMatrix2[1][1];
	tempMatrix1[0][0]=temp[0][0];
	tempMatrix1[0][1]=temp[0][1];
	tempMatrix1[1][0]=temp[1][0];
	tempMatrix1[1][1]=temp[1][1];
}

void AffineLinesFast::cleartempMatrix()
{
	tempMatrix1[0][0]=0;
	tempMatrix1[0][1]=0;
	tempMatrix1[1][0]=0;
	tempMatrix1[1][1]=0;
	tempMatrix2[0][0]=0;
	tempMatrix2[0][1]=0;
	tempMatrix2[1][0]=0;
	tempMatrix2[1][1]=0;
	tempMatrix3[0][0]=0;
	tempMatrix3[0][1]=0;
	tempMatrix3[1][0]=0;
	tempMatrix3[1][1]=0;
}

void AffineLinesFast::doubleswap(double &a,double &b)
{
	double temp=a;
	a=b;
	b=temp;
}

double AffineLinesFast::doubleabs(double a)const
{
	if(a<0)
	{
		return -a;
	}
	return a;
}

int AffineLinesFast::isOnControlLine(const Point &thepoint)
{
	int i;
	Point tva,tvb;
	double dta,dtb;
	for(i=0;i<oldControlLine.size();i++)
	{
		tva=oldControlLine[i].pa-thepoint;
		tvb=oldControlLine[i].pb-thepoint;
		dta=tva.xx*tvb.xx+tva.yy*tvb.yy;
		dtb=sqrt((tva.xx*tva.xx+tva.yy*tva.yy)*(tvb.xx*tvb.xx+tvb.yy*tvb.yy));
		//if(doubleabs(dtb*(-1)-dta)<eps)
		if(doubleabs(dtb+dta)<eps)
		{
			return i;
		}
	}
	return -1;
}

void AffineLinesFast::doAffineLinesFast()
{
	if(oldControlLine.size()!=newControlLine.size())
	{
		return;//控制线段形变前后数目不等，不能形变
	}

	if(!isPreComputed)
	{
		calcA();
	}

	int i,j;
	double td1;
	Point qstar,thePoint;
	Point tp1,tp2,tp3;
	ansPoint=commonPoint;
	for(i=0;i<commonPoint.size();i++)
	{
		j=isOnControlLine(commonPoint[i]);
		if(j>=0)
		{
			if(oldControlLine[j].pa==commonPoint[i])
			{
				ansPoint[i].xx=newControlLine[j].pa.xx;
				ansPoint[i].yy=newControlLine[j].pa.yy;
				continue;
			}
			if(oldControlLine[j].pb==commonPoint[i])
			{
				ansPoint[i].xx=newControlLine[j].pb.xx;
				ansPoint[i].yy=newControlLine[j].pb.yy;
				continue;
			}
			tp1=commonPoint[i]-oldControlLine[j].pa;
			tp2=oldControlLine[j].pb-oldControlLine[j].pa;
			if(doubleabs(tp2.xx)<eps)
			{
				td1=tp1.yy/tp2.yy;
			}
			else
			{
				td1=tp1.xx/tp2.xx;
			}
			tp3=newControlLine[j].pb-newControlLine[j].pa;
			ansPoint[i].xx=newControlLine[j].pa.xx+tp3.xx*td1;
			ansPoint[i].yy=newControlLine[j].pa.yy+tp3.yy*td1;
			continue;
		}

		qstar.xx=0.0;
		qstar.yy=0.0;
		for(j=0;j<oldControlLine.size();j++)
		{
			qstar.xx+=newControlLine[j].pa.xx*(delta00[i][j]+delta01[i][j])+newControlLine[j].pb.xx*(delta01[i][j]+delta11[i][j]);
			qstar.yy+=newControlLine[j].pa.yy*(delta00[i][j]+delta01[i][j])+newControlLine[j].pb.yy*(delta01[i][j]+delta11[i][j]);
		}
		qstar.xx/=sumofw[i];
		qstar.yy/=sumofw[i];

		thePoint.xx=0.0;
		thePoint.yy=0.0;
		for(j=0;j<oldControlLine.size();j++)
		{
			tp1=newControlLine[j].pa-qstar;
			tp2=newControlLine[j].pb-qstar;
			thePoint.xx+=A[i][j].xx*tp1.xx+A[i][j].yy*tp2.xx;
			thePoint.yy+=A[i][j].xx*tp1.yy+A[i][j].yy*tp2.yy;
		}
		ansPoint[i].xx=thePoint.xx+qstar.xx;
		ansPoint[i].yy=thePoint.yy+qstar.yy;
	}
	isComputed=true;
}
