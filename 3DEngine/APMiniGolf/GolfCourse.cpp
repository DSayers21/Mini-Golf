//Includes
#include "GolfCourse.h"

GolfCourse::GolfCourse(const std::string& FileName)
{
	//Load the course
	Load(FileName);
	//Setup the holes vector
	std::vector<LevelData> m_Holes = std::vector<LevelData>();
}

GolfCourse::~GolfCourse()
{
	//Empty
}

bool GolfCourse::NextHole()
{
	//Check if there is another hole
	if (m_CurrentHole < m_Holes.size()-1)
	{
		m_CurrentHole++;	//Increment current hole by one
		return true;		//Return true (there is another hole)
	}
	else
	{
		m_CurrentHole = 0;	//Set current hole to 0
		return false;		//Return false (there is not another hole)
	}
}

LevelData GolfCourse::GetLevel(int LevelID)
{
	//Get current hole
	return m_Holes[LevelID];
}

void GolfCourse::Load(const std::string& FileName)
{
	//Setup temp storage for level
	int CurrentData[7][7] = {
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	};
	//Init Row to 1
	int Row = 1;

	//Current line being loaded
	std::string line;
	//Create ifstream
	std::ifstream myfile(FileName);
	if (myfile.is_open())
	{
		//Loop over every line in the text file
		while (getline(myfile, line))
		{
			//Check if there is a hyphen
			if (line == "-")
			{
				//Store the current hole in the vector
				LevelData New;
				New.SetLevelData(CurrentData);
				m_Holes.push_back(New);
				//Set row back to 1
				Row = 1;
			}
			else
			{
				//Get the current row data from the current line (parseing by comma)
				int* RowData = ParseLine(line, ',');
				for (int i = 0; i < 7; i++)
					CurrentData[Row][i] = RowData[i];
				//Increment row
				Row++;
			}
		}
		//Close the text file
		myfile.close();
		//Display Message
		std::cout << FileName << ": Loaded" << std::endl;
	}

	else 
		std::cout << "Unable to open file";	//Display Message
}

int* GolfCourse::ParseLine(const std::string& Line, char Delim)
{
	//Temp storage of line
	int Row[7] = {0,0,0,0,0,0,0};
	//Current token
	std::string Token;
	std::istringstream TokenStream(Line);
	unsigned int Count = 1;
	//Loop through line
	while (std::getline(TokenStream, Token, Delim))
	{
		//Remove whitespace from token
		Token.erase(std::remove_if(Token.begin(), Token.end(), isspace), Token.end());
		//Convert token to int, and store it in temp line storage
		Row[Count] = stoi(Token);
		//Increment count
		Count++;
	}
	//Return the row
	return Row;
}