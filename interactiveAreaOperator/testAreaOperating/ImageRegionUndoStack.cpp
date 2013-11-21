/*
struct SegmentationData 
{
	vector< vector<int> > splitMatrix;
	IplImage *regionImage;
	SegmentationData *next;
	SegmentationData();
	SegmentationData(const vector< vector<int> > &sMat,IplImage *ri);
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
*/

#include "ImageRegionUndoStack.h"

SegmentationData::SegmentationData()
{
	regionImage=NULL;
	next=NULL;
}

SegmentationData::SegmentationData(const vector< vector<int> > &sMat,IplImage *ri)
{
	splitMatrix=sMat;
	regionImage=cvCloneImage(ri);
	next=NULL;
}

SegmentationData::~SegmentationData()
{
	splitMatrix.clear();
	if(regionImage!=NULL)
	{
		cvReleaseImage(&regionImage);
		regionImage=NULL;
	}
	next=NULL;
}

ImageRegionUndoStack::ImageRegionUndoStack(SegmentationData *curState)
{
	current=curState;
	lefthead=new SegmentationData();
	righthead=new SegmentationData();
}

ImageRegionUndoStack::~ImageRegionUndoStack()
{
	if(current!=NULL)
	{
		delete current;
		current=NULL;
	}
	clearleft();
	delete lefthead;
	lefthead=NULL;
	clearright();
	delete righthead;
	righthead=NULL;
}

SegmentationData* ImageRegionUndoStack::getCurrentPoint()
{
	return current;
}

bool ImageRegionUndoStack::isLeftEmpty()
{
	return lefthead->next==NULL;
}

bool ImageRegionUndoStack::isRightEmpty()
{
	return righthead->next==NULL;
}

bool ImageRegionUndoStack::pushState(SegmentationData *newState)
{
	clearright();
	current->next=lefthead->next;
	lefthead->next=current;
	current=newState;
	current->next=NULL;
	return true;
}

bool ImageRegionUndoStack::Undo()
{
	if(isLeftEmpty())
	{
		return false;
	}
	SegmentationData *newState=lefthead->next;
	lefthead->next=newState->next;
	current->next=righthead->next;
	righthead->next=current;
	current=newState;
	newState=NULL;
	current->next=NULL;
	return true;
}

bool ImageRegionUndoStack::Redo()
{
	if(isRightEmpty())
	{
		return false;
	}
	SegmentationData *newState=righthead->next;
	righthead->next=newState->next;
	current->next=lefthead->next;
	lefthead->next=current;
	current=newState;
	newState=NULL;
	current->next=NULL;
	return true;
}

void ImageRegionUndoStack::clearleft()
{
	SegmentationData *p=lefthead->next,*q;
	while(p!=NULL)
	{
		q=p->next;
		delete p;
		p=q;
	}
	lefthead->next=NULL;
}

void ImageRegionUndoStack::clearright()
{
	SegmentationData *p=righthead->next,*q;
	while(p!=NULL)
	{
		q=p->next;
		delete p;
		p=q;
	}
	righthead->next=NULL;
}
