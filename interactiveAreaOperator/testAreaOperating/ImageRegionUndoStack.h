#ifndef imageregionundostack
#define imageregionundostack

#include <cv.h>
#include <highgui.h>
#include <vector>
using namespace std;

struct SegmentationData 
{
	vector< vector<int> > splitMatrix;
	IplImage *regionImage;
	SegmentationData *next;
	SegmentationData();
	SegmentationData(const vector< vector<int> > &sMat,IplImage *ri);
	~SegmentationData();
};

class ImageRegionUndoStack
{
public:
	ImageRegionUndoStack(SegmentationData *curState);
	~ImageRegionUndoStack();
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
