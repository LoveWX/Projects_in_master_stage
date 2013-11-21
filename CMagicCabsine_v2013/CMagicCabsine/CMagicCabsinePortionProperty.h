#ifndef cmagiccabsineportionproperty
#define cmagiccabsineportionproperty

#include <cstring>
#include <vector>
using namespace std;
#include <cv.h>

class CMagicCabsinePortionProperty
{
public:
	CMagicCabsinePortionProperty(	const IplImage *tempSrcImage,
									vector< vector<int> > &tempSplitMatrix,
									vector< vector< vector<int> > > &tempRegionMasks);//构造函数
	virtual ~CMagicCabsinePortionProperty();//析构函数,释放基类中的数据,目前至少要释放displayImage,并将其置为空
	
	void GetPropertyName(string &tempName)const;//获取局部特征的名称
	void SetPropertyName(const string &tempName);//设置局部特征的名称
	
	//纯虚函数,子类实现该函数以完成某一局部特征的计算
	virtual void ComputeProperty()=0;//计算完成后置isCalced=true
	
	//返回现实局部特征计算结果的图像
	IplImage *GetDisplayImage();//检测isCalc==true?若不是则需要调用computeProperty()计算特征,返回displayImage
	
	virtual void SaveProperty()=0;//纯虚函数,将各种数据保存在数据库中
	virtual void LoadProperty()=0;//纯虚函数,从数据库读入所需要的数据

	virtual void SavePropertyFile(string filepath)=0;//纯虚函数,将各种数据保存在文件中
	virtual void LoadPropertyFile(string filepath)=0;//纯虚函数,从文件读入所需要的数据

	//删除特征,所有动态申请的空间都应在此函数中释放并将指针置为空,子类析构函数中可调用其类中对该函数的实现用于析构
	virtual void DeleteProperty()=0;
	
protected:
	const IplImage *srcImage;//局部特征所计算的源图像
	IplImage *displayImage;//局部特征计算结果用于显示的图像
	string propertyName;//局部特征的名称,方便数据库操作模块添加全局特征表
	bool isCalced;//标识局部特征是否已经计算完成,即displayImage是否可用
	bool isSplited;//标识是否已经取得分割结果

	//与源图像尺寸一致的二维数组表示分割结果,其中不同的数值表示不同的区域
	vector< vector<int> > splitMatrix;
	//各个区域的掩码,每个掩码与源图像尺寸一致,以splitMatrix中标记的区域号进行存储,下标
	vector< vector< vector<int> > > regionMasks;
};

#endif
