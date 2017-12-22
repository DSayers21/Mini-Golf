#pragma once

//Includes
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

class LevelData
{
public:
	//Empty Constructor
	LevelData() {}

	void LevelData::SetLevelData(int LevelData[7][7])
	{
		//Loop through level data and set each element to the nee level data passed in
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 7; j++)
				m_LevelData[i][j] = LevelData[i][j];
	}

	//Representation of the level
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
	//Empty Constructor
	GolfCourse() {}
	//Copy constructor
	GolfCourse(const std::string& FileName);
	//Destructor
	~GolfCourse();
	//Goes to the next hole
	bool NextHole();

	//Getters
	LevelData GetLevel(int LevelID);
	inline int GetCurrentHole() { return m_CurrentHole; }
	//Setters
	inline void SetCurrentHole(int CurHole) { m_CurrentHole = CurHole; }

private:
	//Load course function
	void Load(const std::string& FileName);
	//Parse current line in course being loaded
	int* ParseLine(const std::string& Line, char Delim);

	//Current hole data
	int m_CurrentHole = 0;
	//All the holes for the course
	std::vector<LevelData> m_Holes = std::vector<LevelData>();
};