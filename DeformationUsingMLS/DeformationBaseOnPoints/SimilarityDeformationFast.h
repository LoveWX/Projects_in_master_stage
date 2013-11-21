#ifndef similaritydeformationfast
#define similaritydeformationfast

#include "theDefinition.h"

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

#endif
