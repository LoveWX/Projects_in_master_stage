#ifndef similaritylinesfast
#define similaritylinesfast

#include "theDefinition.h"

class SimilarityLinesFast
{
public:
	SimilarityLinesFast();											//Ĭ�Ϲ��캯������ָ��oldControlLine��newControlLine��commonPoint֮����ܽ����α�
	SimilarityLinesFast(vector<Segment> &oldCS);					//���ι��캯������ָ��newControlLine��commonPoint֮����ܽ����α�
	~SimilarityLinesFast();											//��������
	void UpdateControlLine(vector<Segment> &newCS);					//�������α������߶ε�λ��
	void UpdateCommonPoint(vector<Point> &newCommonPoint);			//�����·ǿ��Ƶ�
	//void SimilarityLinesSlowOfOnePoint(Point &thepoint);			//ȡ���Ե���������α�ĺ�������Ϊ�޷�ʹ��Ԥ����Ľ��
	int getNumOfControlLine()const;									//���ؿ����߶θ���
	void getResultofCommonPoint(vector<Point> &resultPoint);		//����doSimilarityLinesFast()�����α䲢�����������resultPoint��
protected:
	vector<Segment> oldControlLine;									//�α�ǰ�����߶�
	vector<Segment> newControlLine;									//�α������߶�
	vector<Point> commonPoint;										//�ǿ��Ƶ�
	vector<Point> ansPoint;											//����������������Ǳ�����commonPoint��
	int alpha;														//����alpha
	double eps;														//1e-8
	double *sumofw;													//����ÿ���ǿ��Ƶ�洢wֵ�ĺ�(���Ƶ������wֵ)������Ϊ�ǿ��Ƶ����
	double *us;														//����ÿ���ǿ��Ƶ�洢usֵ������Ϊ�ǿ��Ƶ����
	vector< vector<double> > delta00;								//�洢�м���delta00ֵ��delta00[�ǿ��Ƶ��±�][���Ƶ��±�]
	vector< vector<double> > delta01;								//�洢�м���delta01ֵ��delta01[�ǿ��Ƶ��±�][���Ƶ��±�]
	vector< vector<double> > delta11;								//�洢�м���delta11ֵ��delta11[�ǿ��Ƶ��±�][���Ƶ��±�]
	vector< vector<Matrix42> > A;									//�洢�м���Aֵ��A[�ǿ��Ƶ��±�][���Ƶ��±�]
	double tempMatrix1[4][4];										//��ʱ4*4����
	double tempMatrix2[4][2];										//��ʱ4*2����
	double tempMatrix3[2][2];										//��ʱ2*2����
	bool isPreComputed;												//���ڵ�ǰ��commonPoint��Ԥ��������Ƿ����й�
	bool isComputed;												//commonPoint�Ƿ��Ѿ����տ��Ƶ���¹�
	void productofMatrix4442();										//tempMatrix1*tempMatrix2�����������tempMatrix2��
	void productofMatrix4222();										//tempMatrix2*tempMatrix3�����������tempMatrix2��
	void cleartempMatrix();											//�����ʱ����tempMatrix1��tempMatrix2��tempMatrix3
	void doubleswap(double &a,double &b);							//��������double
	double doubleabs(double a)const;								//��һ��double�ľ���ֵ
	int isOnControlLine(const Point &thepoint);						//�ж�һ�����ǲ����ڿ����߶���
	void doSimilarityLinesFast();									//����Ԥ�����������зǿ��Ƶ�����α䣬�α���������ansPoint������
	void calcA();													//Ԥ���㺯������������A������
};

#endif
