#ifndef cmagiccabsinesimulineset
#define cmagiccabsinesimulineset

#include "CMagicCabsineSimuLine.h"
#include "CMagicCabsineChaosStitch.h"
#include "CMagicCabsineOrderlessStitch.h"

#include <vector>
using namespace std;
#include "cv.h"

struct SimuLineSet
{
	vector<SimuLine> lineSet;//��������
	int regionArea;//�������
	CvScalar mainColor;//������ɫ��
	THREAD_TYPE threadType;//������������

	STITCH_TYPE stitchType;//�뷨����
	void *stitchPoint;//�뷨��ָ��

	SimuLineSet();
	SimuLineSet(const SimuLineSet &tempLineSet);
	~SimuLineSet();
	SimuLineSet& operator= (const SimuLineSet& tempLineSet);
};

#endif
