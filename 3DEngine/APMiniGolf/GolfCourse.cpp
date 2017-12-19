#include "GolfCourse.h"

GolfCourse::GolfCourse(const std::string& FileName)
{
	Load(FileName);
	std::vector<LevelData> m_Holes = std::vector<LevelData>();
}

GolfCourse::~GolfCourse()
{
}

bool GolfCourse::NextHole()
{
	if (m_CurrentHole < m_Holes.size()-1)
	{
		m_CurrentHole++;
		return true;
	}
	else
	{
		m_CurrentHole = 0;
		return false;
	}
}

LevelData GolfCourse::GetLevel(int LevelID)
{
	return m_Holes[LevelID];
}

void GolfCourse::Load(const std::string& FileName)
{
	int CurrentData[7][7] = {
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	};

	int Row = 1;

	std::string line;
	std::ifstream myfile(FileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line == "-")
			{
				LevelData New;
				New.SetLevelData(CurrentData);
				m_Holes.push_back(New);
				Row = 1;
			}
			else
			{
				int* RowData = ParseLine(line, ',');
				for (int i = 0; i < 7; i++)
					CurrentData[Row][i] = RowData[i];
				Row++;
			}
		}
		myfile.close();
		std::cout << FileName << ": Loaded" << std::endl;
	}

	else 
		std::cout << "Unable to open file";
}

int* GolfCourse::ParseLine(const std::string& Line, char Delim)
{
	int Row[7] = {0,0,0,0,0,0,0};
	std::string Token;
	std::istringstream TokenStream(Line);
	unsigned int Count = 1;
	while (std::getline(TokenStream, Token, Delim))
	{
		Token.erase(std::remove_if(Token.begin(), Token.end(), isspace), Token.end());
		Row[Count] = stoi(Token);
		Count++;
	}

	return Row;
}