#ifndef similaritylinesfast
#define similaritylinesfast

#include "theDefinition.h"

class SimilarityLinesFast
{
public:
	SimilarityLinesFast();											//默认构造函数，需指定oldControlLine和newControlLine和commonPoint之后才能进行形变
	SimilarityLinesFast(vector<Segment> &oldCS);					//含参构造函数，需指定newControlLine和commonPoint之后才能进行形变
	~SimilarityLinesFast();											//析构函数
	void UpdateControlLine(vector<Segment> &newCS);					//仅更新形变后控制线段的位置
	void UpdateCommonPoint(vector<Point> &newCommonPoint);			//仅更新非控制点
	//void SimilarityLinesSlowOfOnePoint(Point &thepoint);			//取消对单个点进行形变的函数，因为无法使用预计算的结果
	int getNumOfControlLine()const;									//返回控制线段个数
	void getResultofCommonPoint(vector<Point> &resultPoint);		//调用doSimilarityLinesFast()进行形变并将结果拷贝到resultPoint中
protected:
	vector<Segment> oldControlLine;									//形变前控制线段
	vector<Segment> newControlLine;									//形变后控制线段
	vector<Point> commonPoint;										//非控制点
	vector<Point> ansPoint;											//保存计算结果，而不是保存在commonPoint中
	int alpha;														//参数alpha
	double eps;														//1e-8
	double *sumofw;													//对于每个非控制点存储w值的和(控制点个数个w值)，长度为非控制点个数
	double *us;														//对于每个非控制点存储us值，长度为非控制点个数
	vector< vector<double> > delta00;								//存储中间结果delta00值，delta00[非控制点下标][控制点下标]
	vector< vector<double> > delta01;								//存储中间结果delta01值，delta01[非控制点下标][控制点下标]
	vector< vector<double> > delta11;								//存储中间结果delta11值，delta11[非控制点下标][控制点下标]
	vector< vector<Matrix42> > A;									//存储中间结果A值，A[非控制点下标][控制点下标]
	double tempMatrix1[4][4];										//临时4*4矩阵
	double tempMatrix2[4][2];										//临时4*2矩阵
	double tempMatrix3[2][2];										//临时2*2矩阵
	bool isPreComputed;												//对于当前的commonPoint，预计算程序是否运行过
	bool isComputed;												//commonPoint是否已经按照控制点更新过
	void productofMatrix4442();										//tempMatrix1*tempMatrix2，结果保存在tempMatrix2中
	void productofMatrix4222();										//tempMatrix2*tempMatrix3，结果保存在tempMatrix2中
	void cleartempMatrix();											//清空临时矩阵tempMatrix1和tempMatrix2和tempMatrix3
	void doubleswap(double &a,double &b);							//交换两个double
	double doubleabs(double a)const;								//求一个double的绝对值
	int isOnControlLine(const Point &thepoint);						//判断一个点是不是在控制线段上
	void doSimilarityLinesFast();									//调用预计算结果对所有非控制点进行形变，形变结果保存在ansPoint向量中
	void calcA();													//预计算函数，结果存放在A向量中
};

#endif
