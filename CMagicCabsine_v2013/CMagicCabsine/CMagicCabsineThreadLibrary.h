#ifndef cmagiccabsinethreadtype
#define cmagiccabsinethreadtype

#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Thread
{
	string threadName;
	int colorR;
	int colorG;
	int colorB;
};

class CMagicCabsineThreadLibrary
{
public:
	CMagicCabsineThreadLibrary();
	~CMagicCabsineThreadLibrary();
	int GetNumOfThreadSet();
	void GetThreadSetName(vector<string> &tempName);
	void SetThreadSetName(vector<string> &tempName);
	void GetThreadSet(vector< vector<Thread> > &tempThreadSet);
	void SetThreadSet(vector< vector<Thread> > &tempThreadSet);

	void GetThreads(int index,vector<Thread> &tempThread);
	void GetThreads(string factoryName,vector<Thread> &tempThread);

	void SaveConfigToFile();//将配置表信息保存至文件中
	void LoadConfigFromFile();//从文件中读取配置表信息

protected:
	string pathOfConfig;
	vector< vector<Thread> > threadLibrary;
	vector<string> threadFactoryName;
};

#endif
