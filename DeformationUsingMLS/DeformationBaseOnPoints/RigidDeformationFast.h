#ifndef rigiddeformationfast
#define rigiddeformationfast

#include "theDefinition.h"

class RigidDeformationFast
{
public:
	RigidDeformationFast();											//默认构造函数，需指定newControlPoint和commonPoint之后才能进行形变
	RigidDeformationFast(vector<Point> &oldCP);						//含参构造函数，需指定newControlPoint和commonPoint之后才能进行形变
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
	void doRigidDeformation();										//调用预计算结果对所有非控制点进行形变，用形变结果更新commonPoint向量
	void calcA();													//预计算函数，结果存放在A向量中
};

#endif
