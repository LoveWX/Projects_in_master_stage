#ifndef cmagiccabsineundostack
#define cmagiccabsineundostack

#include <cv.h>

struct SegmentationData 
{
	vector< vector<int> > splitMatrix;
	IplImage *boundaryImage;
	IplImage *maincolorImage;
	IplImage *frontBackImage;
	SegmentationData *next;
	SegmentationData();
	SegmentationData(const vector< vector<int> > &sMat,IplImage *bi,IplImage *mci,IplImage *fbi);
	~SegmentationData();
};

class CMagicCabsineUndoStack
{
public:
	CMagicCabsineUndoStack(SegmentationData *curState);
	~CMagicCabsineUndoStack();
	SegmentationData* getCurrentPoint();
	bool isLeftEmpty();
	bool isRightEmpty();
	bool pushState(SegmentationData *newState);
	bool Undo();
	bool Redo();
protected:
	SegmentationData *current;
	SegmentationData *lefthead;
	SegmentationData *righthead;
	void clearleft();
	void clearright();
};

#endif
