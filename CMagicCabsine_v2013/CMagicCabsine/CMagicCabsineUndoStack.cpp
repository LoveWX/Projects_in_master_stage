/*
struct SegmentationData 
{
	IplImage *boundaryImage;
	IplImage *maincolorImage;
	IplImage *frontBackImage;
	SegmentationData *next;
	SegmentationData();
	SegmentationData(IplImage *bi,IplImage *mci,IplImage *fbi);
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
#include "stdafx.h"

#include "CMagicCabsineUndoStack.h"

SegmentationData::SegmentationData()
{
	boundaryImage=NULL;
	maincolorImage=NULL;
	frontBackImage=NULL;
	next=NULL;
}

SegmentationData::SegmentationData(const vector< vector<int> > &sMat,IplImage *bi,IplImage *mci,IplImage *fbi)
{
	splitMatrix=sMat;
	boundaryImage=cvCloneImage(bi);
	maincolorImage=cvCloneImage(mci);
	frontBackImage=cvCloneImage(fbi);
	next=NULL;
}

SegmentationData::~SegmentationData()
{
	splitMatrix.clear();
	if(boundaryImage!=NULL)
	{
		cvReleaseImage(&boundaryImage);
		boundaryImage=NULL;
	}
	if(maincolorImage!=NULL)
	{
		cvReleaseImage(&maincolorImage);
		maincolorImage=NULL;
	}
	if(frontBackImage!=NULL)
	{
		cvReleaseImage(&frontBackImage);
		frontBackImage=NULL;
	}
	next=NULL;
}

CMagicCabsineUndoStack::CMagicCabsineUndoStack(SegmentationData *curState)
{
	current=curState;
	lefthead=new SegmentationData();
	righthead=new SegmentationData();
}

CMagicCabsineUndoStack::~CMagicCabsineUndoStack()
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

SegmentationData* CMagicCabsineUndoStack::getCurrentPoint()
{
	return current;
}

bool CMagicCabsineUndoStack::isLeftEmpty()
{
	return lefthead->next==NULL;
}

bool CMagicCabsineUndoStack::isRightEmpty()
{
	return righthead->next==NULL;
}

bool CMagicCabsineUndoStack::pushState(SegmentationData *newState)
{
	clearright();
	current->next=lefthead->next;
	lefthead->next=current;
	current=newState;
	current->next=NULL;
	return true;
}

bool CMagicCabsineUndoStack::Undo()
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

bool CMagicCabsineUndoStack::Redo()
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

void CMagicCabsineUndoStack::clearleft()
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

void CMagicCabsineUndoStack::clearright()
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
