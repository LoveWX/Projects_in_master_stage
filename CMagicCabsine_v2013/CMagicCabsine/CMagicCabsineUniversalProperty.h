#ifndef cmagiccabsineuniversalproperty
#define cmagiccabsineuniversalproperty

#include <cstring>
#include <vector>
using namespace std;
#include <cv.h>

class CMagicCabsineUniversalProperty
{
public:
	CMagicCabsineUniversalProperty(const IplImage *tempSrcImage);//构造函数
	virtual ~CMagicCabsineUniversalProperty();//析构函数,释放基类中的数据,目前至少要释放displayImage,并将其置为空

	void GetPropertyName(string &tempName)const;//获取全局特征的名称
	void SetPropertyName(const string &tempName);//设置全局特征的名称

	//纯虚函数,子类实现该函数以完成某一全局特征的计算
	virtual void ComputeProperty()=0;//计算完成后置isCalced=true

	//返回现实全局特征计算结果的图像
	IplImage* GetDisplayImage();//检测isCalc==true?若不是则需要调用computeProperty()计算特征,返回displayImage

	virtual void SaveProperty()=0;//纯虚函数,将各种数据保存在数据库中
	virtual void LoadProperty()=0;//纯虚函数,从数据库读入所需要的数据

	virtual void SavePropertyFile(string filepath)=0;//纯虚函数,将各种数据保存在文件中
	virtual void LoadPropertyFile(string filepath)=0;//纯虚函数,从文件读入所需要的数据

	//删除特征,所有动态申请的空间都应在此函数中释放并将指针置为空,子类析构函数中可调用其类中对该函数的实现用于析构
	virtual void DeleteProperty()=0;
protected:
	const IplImage *srcImage;//全局特征所计算的源图像
	IplImage *displayImage;//全局特征计算结果用于显示的图像
	string propertyName;//全局特征的名称,方便数据库操作模块添加全局特征表
	bool isCalced;//标识全局特征是否已经计算完成,即displayImage是否可用
};

#endif
