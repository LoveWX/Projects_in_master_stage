#include "SimilarityDeformationFast.h"

/*
class SimilarityDeformationFast
{
public:
	SimilarityDeformationFast();									//Ĭ�Ϲ��캯������ָ��newControlPoint��commonPoint֮����ܽ����α�
	SimilarityDeformationFast(vector<Point> &oldCP);				//���ι��캯������ָ��newControlPoint��commonPoint֮����ܽ����α�
	~SimilarityDeformationFast();									//��������
	void UpdateControlPoint(vector<Point> &newCP);					//�������α����Ƶ㣬Ԥ�������ݲ��øı�
	void UpdateCommonPoint(vector<Point> &newCommonPoint);			//�����·ǿ��Ƶ㣬Ԥ����������Ҫ�ı�
	int getNumOfControlPoint()const;								//���ؿ��Ƶ����
	void getResultofCommonPoint(vector<Point> &resultPoint);		//����doSimilarityDeformation()�����α䲢�����������resultPoint��
protected:
	static const double alpha;										//����alpha
	vector<Point> oldControlPoint;									//�α�ǰ���Ƶ�
	vector<Point> commonPoint;										//�ǿ��Ƶ�
	vector<Point> newControlPoint;									//�α����Ƶ�
	vector<Point> ansPoint;											//����������������Ǳ�����commonPoint��
	double *sumofw;													//����ÿ���ǿ��Ƶ�洢wֵ�ĺ�(���Ƶ������wֵ)������Ϊ�ǿ��Ƶ����
	vector< vector<double> > w;										//�洢�м���wֵ��w[�ǿ��Ƶ��±�][���Ƶ��±�]
	vector< vector<Point> > A;										//�洢�м���Aֵ��A[�ǿ��Ƶ��±�][���Ƶ��±�]
	bool isPreComputed;												//���ڵ�ǰ��commonPoint��Ԥ��������Ƿ����й�
	bool isComputed;												//commonPoint�Ƿ��Ѿ����տ��Ƶ���¹�
	void doubleswap(double &a,double &b);							//��������double
	double doubleabs(double a)const;								//��һ��double�ľ���ֵ
	int isControlPoint(const Point &thepoint)const;					//�ж�һ�����ǲ��ǿ��Ƶ�
	void doSimilarityDeformation();									//����Ԥ�����������зǿ��Ƶ�����α䣬���α�������commonPoint����
	void calcA();													//Ԥ���㺯������������A������
};
*/

const double SimilarityDeformationFast::alpha=1.0;

SimilarityDeformationFast::SimilarityDeformationFast()
{
	oldControlPoint.clear();
	commonPoint.clear();
	newControlPoint.clear();
	ansPoint.clear();
	sumofw=NULL;
	w.clear();
	A.clear();
	isPreComputed=false;
	isComputed=false;
}

SimilarityDeformationFast::SimilarityDeformationFast(vector<Point> &oldCP)
{
	oldControlPoint=oldCP;
	commonPoint.clear();
	newControlPoint.clear();
	ansPoint.clear();
	sumofw=NULL;
	w.clear();
	A.clear();
	isPreComputed=false;
	isComputed=false;
}

SimilarityDeformationFast::~SimilarityDeformationFast()
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
	w.clear();
	A.clear();
	isPreComputed=false;
	isComputed=false;
}

void SimilarityDeformationFast::UpdateControlPoint(vector<Point> &newCP)
{
	newControlPoint=newCP;
	isComputed=false;
}

void SimilarityDeformationFast::UpdateCommonPoint(vector<Point> &newCommonPoint)
{
	commonPoint=newCommonPoint;
	isPreComputed=false;
	isComputed=false;
}

int SimilarityDeformationFast::getNumOfControlPoint()const
{
	return oldControlPoint.size();
}

void SimilarityDeformationFast::doubleswap(double &a,double &b)
{
	double temp=a;
	a=b;
	b=temp;
}

double SimilarityDeformationFast::doubleabs(double a)const
{
	if(a<0)
	{
		return -a;
	}
	return a;
}

int SimilarityDeformationFast::isControlPoint(const Point &thepoint)const
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

void SimilarityDeformationFast::getResultofCommonPoint(vector<Point> &resultPoint)
{
	if(!isComputed)
	{
		doSimilarityDeformation();
	}
	resultPoint=ansPoint;
}

void SimilarityDeformationFast::calcA()
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
		w.push_back(tempVector);
	}

	A.clear();//[�ǿ��Ƶ��±�][���Ƶ��±�]
	Point pA,vp;
	vp.xx=0.0;
	vp.yy=0.0;
	vector<Point> tempPointVector(oldControlPoint.size(),vp);
	double sumofwpp;
	for(i=0;i<commonPoint.size();i++)
	{
		vp.xx=commonPoint[i].xx-pstar[i].xx;
		vp.yy=commonPoint[i].yy-pstar[i].yy;
		sumofwpp=0.0;
		for(j=0;j<oldControlPoint.size();j++)
		{
			pA.xx=oldControlPoint[j].xx-pstar[i].xx;
			pA.yy=oldControlPoint[j].yy-pstar[i].yy;
			sumofwpp+=w[i][j]*(pA.xx*pA.xx+pA.yy*pA.yy);

			/*
			//Aj = | a , b | * | c , d | = | ac+bd , ad-bc |
			//	   | b ,-a |   | d ,-c |   | bc-ad , bd+ac |
			//��ʽ��||�����Ĳ���Ϊ2*2�������������������ʣ�����A��ֻ����4��Ԫ���е�2��
			//��Aj = ( ac+bd , ad-bc )
			*/
			//A[i][j].xx=w[i][j]*(pA.xx*vp.xx+pA.yy*vp.yy);
			//A[i][j].yy=w[i][j]*(pA.xx*vp.yy-pA.yy*vp.xx);

			tempPointVector[j].xx=w[i][j]*(pA.xx*vp.xx+pA.yy*vp.yy);
			tempPointVector[j].yy=w[i][j]*(pA.xx*vp.yy-pA.yy*vp.xx);
		}
		for(j=0;j<oldControlPoint.size();j++)
		{
			//A[i][j].xx/=sumofwpp;
			//A[i][j].yy/=sumofwpp;
			tempPointVector[j].xx/=sumofwpp;
			tempPointVector[j].yy/=sumofwpp;
		}
		A.push_back(tempPointVector);
	}
	delete[] pstar;

	isPreComputed=true;
}

void SimilarityDeformationFast::doSimilarityDeformation()
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
	Point tempPoint,sumPoint,qstar;
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
		
		sumPoint.xx=0;
		sumPoint.yy=0;
		for(j=0;j<oldControlPoint.size();j++)
		{
			tempPoint.xx=newControlPoint[j].xx-qstar.xx;
			tempPoint.yy=newControlPoint[j].yy-qstar.yy;
			sumPoint.xx+=(tempPoint.xx*A[i][j].xx-tempPoint.yy*A[i][j].yy);
			sumPoint.yy+=(tempPoint.xx*A[i][j].yy+tempPoint.yy*A[i][j].xx);
		}
		ansPoint[i].xx=sumPoint.xx+qstar.xx;
		ansPoint[i].yy=sumPoint.yy+qstar.yy;
	}
	
	isComputed=true;
}