#include "AffineDeformationFast.h"

/*
class AffineDeformationFast
{
public:
	AffineDeformationFast();										//Ĭ�Ϲ��캯������ָ��newControlPoint��commonPoint֮����ܽ����α�
	AffineDeformationFast(vector<Point> &oldCP);					//���ι��캯������ָ��newControlPoint��commonPoint֮����ܽ����α�
	~AffineDeformationFast();										//��������
	void UpdateControlPoint(vector<Point> &newCP);					//�������α����Ƶ㣬Ԥ�������ݲ��øı�
	void UpdateCommonPoint(vector<Point> &newCommonPoint);			//�����·ǿ��Ƶ㣬Ԥ����������Ҫ�ı�
	//void AffineDeformationOfOnePoint(Point &thepoint);			//ȡ���Ե���������α�ĺ�������Ϊ�޷�ʹ��Ԥ����Ľ��
	int getNumOfControlPoint()const;								//���ؿ��Ƶ����
	void getResultofCommonPoint(vector<Point> &resultPoint);		//����doAffineDeformation()�����α䲢�����������resultPoint��
protected:
	static const double alpha;										//����alpha
	vector<Point> precomputedpart;									//Ԥ�����ǰ�벿�ֽ���洢
	vector<Point> oldControlPoint;									//�α�ǰ���Ƶ�
	vector<Point> commonPoint;										//�ǿ��Ƶ�
	vector<Point> newControlPoint;									//�α����Ƶ�
	vector<Point> ansPoint;											//����������������Ǳ�����commonPoint��
	double *sumofw;													//����ÿ���ǿ��Ƶ�洢wֵ�ĺ�(���Ƶ������wֵ)������Ϊ�ǿ��Ƶ����
	vector< vector<double> > w;										//�洢�м���wֵ��w[�ǿ��Ƶ��±�][���Ƶ��±�]
	vector< vector<double> > A;										//�洢�м���Aֵ��A[�ǿ��Ƶ��±�][���Ƶ��±�]
	bool isPreComputed;												//���ڵ�ǰ��commonPoint��Ԥ��������Ƿ����й�
	bool isComputed;												//commonPoint�Ƿ��Ѿ����տ��Ƶ���¹�
	double tempMatrix[2][2];										//��ʱ2*2����
	void cleartempMatrix();											//�����ʱ����tempMatrix
	void doubleswap(double &a,double &b);							//��������double
	double doubleabs(double a)const;								//��һ��double�ľ���ֵ
	int isControlPoint(const Point &thepoint)const;					//�ж�һ�����ǲ��ǿ��Ƶ�
	void doAffineDeformation();										//����Ԥ�����������зǿ��Ƶ�����α䣬���α�������commonPoint����
	void calcA();													//Ԥ���㺯������������A������
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
	w.clear();//w[�ǿ��Ƶ��±�][���Ƶ��±�]
	vector<double> tempVector(oldControlPoint.size(),0.0);

	precomputedpart=commonPoint;
	for(i=0;i<commonPoint.size();i++)
	{
		if(isControlPoint(commonPoint[i])>=0)//�ǿ��Ƶ�,����Ҫ����wֵ
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

	A.clear();//A[�ǿ��Ƶ��±�][���Ƶ��±�]
	for(i=0;i<commonPoint.size();i++)
	{
		if(isControlPoint(commonPoint[i])>=0)//�ǿ��Ƶ�,����Ҫ����wֵ
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
		return;//���Ƶ��α�ǰ����Ŀ���ȣ������α�
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
