#ifndef affinedeformationfast
#define affinedeformationfast

#include "theDefinition.h"

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

#endif
