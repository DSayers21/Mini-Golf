#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

class LevelData
{
public:
	LevelData() {}

	void LevelData::SetLevelData(int LevelData[7][7])
	{
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 7; j++)
				m_LevelData[i][j] = LevelData[i][j];
	}

	int m_LevelData[7][7] = {
		{ 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 0
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 1
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 2
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 3
		{ 0, 0, 0, 0, 0, 0, 0 } ,   //Row 4
		{ 0, 0, 0, 0, 0, 0, 0 } ,
	};
};

class GolfCourse
{
public:
	GolfCourse() {}
	GolfCourse(const std::string& FileName);
	~GolfCourse();

	bool NextHole();

	LevelData GetLevel(int LevelID);
	inline int GetCurrentHole() { return m_CurrentHole; }
	inline void SetCurrentHole(int CurHole) { m_CurrentHole = CurHole; }

private:
	void Load(const std::string& FileName);
	int* ParseLine(const std::string& Line, char Delim);

	int m_CurrentHole = 0;
	std::vector<LevelData> m_Holes = std::vector<LevelData>();
};