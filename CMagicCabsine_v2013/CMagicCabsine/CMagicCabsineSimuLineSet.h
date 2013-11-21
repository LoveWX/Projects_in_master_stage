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
	vector<SimuLine> lineSet;//线条集合
	int regionArea;//区域面积
	CvScalar mainColor;//区域主色调
	THREAD_TYPE threadType;//区域绣线类型

	STITCH_TYPE stitchType;//针法类型
	void *stitchPoint;//针法类指针

	SimuLineSet();
	SimuLineSet(const SimuLineSet &tempLineSet);
	~SimuLineSet();
	SimuLineSet& operator= (const SimuLineSet& tempLineSet);
};

#endif
