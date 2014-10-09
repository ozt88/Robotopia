#pragma once
#include "cocos2d.h"
#include "Utils.h"
#define MODULES_FILE_NAME "Data\\Stage\\moduleList.mld"
#define FLOOR_FILE_NAME "Data\\Stage\\floorData.fdd"


struct StageModuleData
{
	int width, height;
	std::vector<int> data;
};

struct StageData
{
	int x, y;
	int width, height;
	std::vector<int> data;
};

struct FloorData
{
	int width, height;
	std::vector<int> data;
};

class DataManager
{
public:
	bool init();
	bool initModuleData();
	bool initFloorData();
	DataManager();
	~DataManager();

private:	
	std::map < Directions, std::vector<StageModuleData>> m_ModuleData;
	std::map < int, std::vector<StageData>> m_FloorData;

};