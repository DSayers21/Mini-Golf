//Includes
#include "Shader.h"
#include "RenderEngine.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "BaseLight.h"

namespace D3DEngine
{
	Shader::Shader(const std::string& FileName, ShaderList* shaderList)
	{
		//Set name to the filename
		m_Name = FileName;
		//Set pointer to the shader list
		m_ShaderList = shaderList;
		//Try to get the shader resource from the shader list
		m_ShaderResource = m_ShaderList->GetShader(FileName);
		if (m_ShaderResource == nullptr) //If the shader resource doesnt exists, load it
		{
			//Display message
			std::cerr << "Loaded Shader: " << FileName << std::endl;
			//Create shader resource
			m_ShaderResource = new ShaderResource();
			//Init the shader
			InitShader(FileName);
			//Add the shader resource to the shader list
			m_ShaderList->AddShader(FileName, m_ShaderResource);
		}
		else
		{
			//Display message
			std::cerr << "Cached Shader: " << FileName << std::endl;
			m_ShaderResource->AddReference();
		}
	}

	void Shader::InitShader(const std::string& FileName)
	{
		std::string VertexShaderText = LoadShader(FileName + ".vert");		//Load the vert shader
		std::string FragmentShaderText = LoadShader(FileName + ".frag");	//Load the frag shader

		AddVertexShader(VertexShaderText);		//Add the vertex shader to the program
		AddFragmentShader(FragmentShaderText);	//Add the fragment shader to the program

		//Set Attribs
		AddAllAttributes(&VertexShaderText);

		//Compile the shader together
		CompileShader();

		//Add all the Uniforms, found in the fragment and vert files
		AddAllUniforms(&VertexShaderText);
		AddAllUniforms(&FragmentShaderText);
	}

	Shader::~Shader()
	{
		//Remove shader reference, if no references left, then remove the shader
		if (m_ShaderResource->RemoveReference())
		{
			//Display message
			std::cerr << "Destructor: Shader: " << m_Name << std::endl;
			//Remove the shader
			m_ShaderList->RemoveShader(m_Name);
		}
		else
			std::cerr << "Destructor: Shader - Removed Reference" << std::endl;	//Display message
	}

	Shader::Shader(const Shader & other)
	{
		//Display message
		std::cerr << "Copied Shader" << std::endl;
	}

	void Shader::CompileShader()
	{
		//Link the shader program
		glLinkProgram(m_ShaderResource->GetProgram());
		CheckShaderError(m_ShaderResource->GetProgram(), GL_LINK_STATUS, true, "Error linking shader program"); //Check link was okay
		//Validate the program
		glValidateProgram(m_ShaderResource->GetProgram());
		CheckShaderError(m_ShaderResource->GetProgram(), GL_VALIDATE_STATUS, true, "Invalid shader program");	//Check validation was okay
	}

	void Shader::Bind()
	{
		//Bind the shader
		glUseProgram(m_ShaderResource->GetProgram());
	}

	void Shader::UnBind()
	{
		//Bind the shader to -1 (to unbind)
		glUseProgram(-1);
	}

	void Shader::UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine)
	{
		//Get the world matrix, and the Model view project matrix
		Matrix4f& WorldMatrix = transform->GetTransformation();
		Matrix4f& MVPMatrix = renderEngine->GetCamera()->GetViewProjection().Mult(WorldMatrix);

		//Loop Over all Uniforms
		std::vector<StructComponent>* UniStruct = m_ShaderResource->GetUniformsStruct();
		int Size = UniStruct->size(); //Get amound of uniforms
		for (int i = 0; i < Size; i++)
		{
			std::string& UniformName = *(&UniStruct->at(i))->GetName(); //Get the name of the current uniform
			std::string& UniformType = *(&UniStruct->at(i))->GetType(); //Get the type of the current uniform

			std::string& UnprefixedUniformName = UniformName.substr(2); //Get the unprefixed uniform name

			char FirstLetter = UniformName[0]; //Get the first letter of the uniforms name

			if (UniformType == "sampler2D")	//Check if a Texture Uniform
			{
				//Get the sampler slot
				int SamplerSlot = renderEngine->GetSamplerSlot(UniformName);
				//Get the texture, and bind
				material->GetTexture(UniformName)->Bind(SamplerSlot);
				//Set the sampler slot uniform
				SetUniformI(UniformName, SamplerSlot);
			}
			else if (FirstLetter == 'T')	//Check if a Transform Uniform
			{
				if (UniformName == "T_MVP") //Check if a Model view projection uniform
					SetUniformM4(UniformName, MVPMatrix); //Set the matrix uniform
				else if (UniformName == "T_Model") //Check if a world matrix uniform
					SetUniformM4(UniformName, WorldMatrix); //Set the matrix uniform
				else
					std::cerr << UniformName << ": Illegal Argument" << std::endl; //Display message
			}
			else if (FirstLetter == 'R')	//Check if a Rendering Engine uniform
			{
				if (UniformType == "vec3") //Check if a vector3 uniform
					SetUniformV(UniformName, renderEngine->GetVector3f(UnprefixedUniformName)); //Update the vector 3 uniform
				else if (UniformType == "float") //Check if a float uniform
					SetUniformF(UniformName, renderEngine->GetFloat(UnprefixedUniformName)); //Update the float uniform
				else if (UniformType == "DirectionalLight") //Check if a directional light uniform
					SetUniformDL(UniformName, renderEngine->GetActiveLight()); //Update the directional light uniform
				else if (UniformType == "PointLight") //Check if a point light uniform
					SetUniformPL(UniformName, renderEngine->GetActiveLight()); //Update the point light uniform
				else if (UniformType == "SpotLight") //Check if a spot light uniform
					SetUniformSL(UniformName, renderEngine->GetActiveLight()); //Update the spot light uniform
				else	//Handle Extra Struct Case if needed
					renderEngine->UpdateUniformStruct(transform, material, this, UniformName, UniformType);	
			}
			else if (FirstLetter == 'C')	//Check if a Camera uniform
			{
				if (UniformName == "C_EyePos") //Check if its the eyepos uniform
					SetUniformV(UniformName, renderEngine->GetCamera()->GetTransform()->GetTransformedPos()); //Update the camera position uniform
				else
					std::cerr << UniformName << ": Illegal Argument" << std::endl; //Display message
			}
			else							//Check if it is a Material uniform
			{
				if (UniformType == "vec3") //Check if a vector3 uniform
					SetUniformV(UniformName, material->GetVector3f(UniformName)); //Update the vector 3 uniform
				else if (UniformType == "float") //Check if a float uniform
					SetUniformF(UniformName, material->GetFloat(UniformName)); //Update the float uniform
				else
					std::cerr << UniformName << ": Illegal Argument" << std::endl; //Display message
			}
		}
	}

	void Shader::AddAllAttributes(std::string* ShaderText)
	{
		//Store the keyword
		std::string ATTRIBUTE_KEYWORD = "attribute";
		//Find the keyword
		size_t AttributeStartLocation = ShaderText->find(ATTRIBUTE_KEYWORD);
		//Set counter to 0
		int AttribCounter = 0;
		//Check if there is still text to process
		while (AttributeStartLocation != std::string::npos)
		{
			//Get start and end pos of the Attribute
			int Begin = AttributeStartLocation + ATTRIBUTE_KEYWORD.size() + 1;
			int End = ShaderText->find(";", Begin);

			//Get The Attribute name
			std::string AttributeLine = ShaderText->substr(Begin, End - Begin);
			int SpacePos = AttributeLine.find(" ");
			std::string AttributeName = AttributeLine.substr(SpacePos + 1, AttributeLine.size());		//Gets name of the Attribute name
			//Set the attribute
			SetAttribLocation(AttributeName, AttribCounter);	//Add the Attribute
			AttribCounter++;									//Increment Count
			//Update the start location
			AttributeStartLocation = ShaderText->find(ATTRIBUTE_KEYWORD, AttributeStartLocation + ATTRIBUTE_KEYWORD.size());
		}
	}
	
	void Shader::AddAllUniforms(std::string* ShaderText)
	{
		//Get the uniform structs
		STRUCTMAP Structs = FindUniformStructs(*ShaderText);
		//Set the uniform keyword to uniform
		std::string UNIFORM_KEYWORD = "uniform";
		//Find the uniform keyword
		size_t UniformStartLocation = ShaderText->find(UNIFORM_KEYWORD);
		//Check if there is still text to process
		while (UniformStartLocation != std::string::npos)
		{
			//Get start and end pos of the uniform
			int Begin = UniformStartLocation + UNIFORM_KEYWORD.size() + 1;
			int End = ShaderText->find(";", Begin);

			//Get The uniform name
			std::string UniformLine = ShaderText->substr(Begin, End - Begin);
			
			int WhiteSpacePos = UniformLine.find(" ") + 1;
			std::string UniformName = UniformLine.substr(WhiteSpacePos, UniformLine.size());		//Gets name of the uniform name
			std::string UniformType = UniformLine.substr(0, WhiteSpacePos - 1);

			//Add the uniform struct to the shader resource
			m_ShaderResource->AddUniformsStruct(StructComponent(UniformName, UniformType));
			//Add the uniform struct with struct check
			AddUniformWithStructCheck(UniformName, UniformType, Structs);
			
			//Update the start location
			UniformStartLocation = ShaderText->find(UNIFORM_KEYWORD, UniformStartLocation + UNIFORM_KEYWORD.size());
		}
	}

	void Shader::AddUniformWithStructCheck(const std::string& UniformName, const std::string& UniformType, STRUCTMAP Structs)
	{
		//Set add this to true
		bool AddThis = true;
		//Get the structs from the map
		std::vector<StructComponent> StructComp = GetStuctFromMap(Structs, UniformType);
		//Check if the struct has some size
		if (StructComp.size() != 0)
		{
			AddThis = false; //Set add this to false
			//Add all structs which reference another struct
			for (int i = 0; i < StructComp.size(); i++)
				AddUniformWithStructCheck(UniformName + "." + *StructComp[i].GetName(), *StructComp[i].GetType(), Structs);
		}
		//If add this is true, add the uniform
		if (AddThis)
			AddUniform(UniformName);
	}

	std::vector<StructComponent> Shader::GetStuctFromMap(STRUCTMAP Structs, const std::string& Key)
	{
		//Find the struct from the map
		STRUCTMAP::const_iterator it = Structs.find(Key);
		if (it != Structs.end()) //If the struct exists, then return it
			return it->second;
		return std::vector<StructComponent>(); //If the struct does not exists then return empty component
	}

	void Shader::AddUniform(const std::string& Uniform)
	{
		//Get the uniform location
		int UniformLocation = glGetUniformLocation(m_ShaderResource->GetProgram(), Uniform.c_str());
		//Make sure the uniform can be found, else display a message
		if (UniformLocation == -1)
			std::cerr << "Error: Couldnt find uniform: " << Uniform << std::endl;
		//Add Uniform to Map
		m_ShaderResource->AddUniform(Uniform, UniformLocation);
		//Display message
		std::cerr << "Uniform: " << Uniform << " added." << std::endl;
	}

	void Shader::SetUniformI(const std::string& UniformName, const int& Value) const
	{
		//Update the int uniform
		glUniform1i(m_ShaderResource->GetUniforms()->find(UniformName)->second, Value);
	}

	void Shader::SetUniformF(const std::string& UniformName, float Value) const
	{
		//Update the float uniform
		glUniform1f(m_ShaderResource->GetUniforms()->find(UniformName)->second, Value);
	}

	void Shader::SetUniformV(const std::string& UniformName, Vector3f Value) const
	{
		//Update the vector3 uniform
		glUniform3f(m_ShaderResource->GetUniforms()->find(UniformName)->second, Value.GetX(), Value.GetY(), Value.GetZ());
	}

	void Shader::SetUniformM4(const std::string& UniformName, const Matrix4f& Value) const
	{
		//Update the matrix uniform
		glUniformMatrix4fv(m_ShaderResource->GetUniforms()->at(UniformName), 1, GL_TRUE, &(Value[0][0]));
	}

	void Shader::SetUniformDL(const std::string& UniformName, BaseLight* DirLight) const
	{
		//Update the base light uniform
		SetUniformBL(UniformName + ".Light", DirLight);
		//Update the vector3 uniform
		SetUniformV(UniformName + ".Direction", DirLight->GetDirection());
	}

	void Shader::SetUniformBL(const std::string& UniformName, BaseLight* BaseLight) const
	{
		//Update the vector3 uniform
		SetUniformV(UniformName + ".Colour", BaseLight->GetColour());
		//Update the float uniform
		SetUniformF(UniformName + ".Intensity", BaseLight->GetIntensity());
	}

	void Shader::SetUniformPL(const std::string& UniformName, BaseLight* pointLight) const
	{
		//Update the base light uniform
		SetUniformBL(UniformName + ".Light", pointLight);
		//Attenuation
		SetUniformF(UniformName + ".Atten.Constant", pointLight->GetAttenuation().GetConstant()); //Update the float uniform
		SetUniformF(UniformName + ".Atten.Linear", pointLight->GetAttenuation().GetLinear());	  //Update the float uniform
		SetUniformF(UniformName + ".Atten.Exponent", pointLight->GetAttenuation().GetExponent()); //Update the float uniform

		SetUniformV(UniformName + ".Position", pointLight->GetTransform()->GetTransformedPos());  //Update the vector3 uniform
		SetUniformF(UniformName + ".Range", pointLight->GetRange());							  //Update the float uniform
	}

	void Shader::SetUniformSL(const std::string& UniformName, BaseLight* spotLight) const
	{
		//Update the point light uniform
		SetUniformPL(UniformName + ".PLight", spotLight);
		//Update the vector3 uniform
		SetUniformV(UniformName + ".Direction", spotLight->GetDirection());
		//Update the float uniform
		SetUniformF(UniformName + ".Cutoff", spotLight->GetCutoff());
	}

	void Shader::SetAttribLocation(const std::string& AttribName, int& Location)
	{
		//Bind the attrib location
		glBindAttribLocation(m_ShaderResource->GetProgram(), Location, AttribName.c_str());
	}

	void Shader::AddProgram(const std::string& Text, int Type)
	{
		//Create the shader
		int Shader = glCreateShader(Type);

		if (Shader == 0) //Ensure the shader created okay, else display a message
			std::cerr << "Shader Creation Failed: Could not find valid memory location when adding shader" << std::endl;

		//Process Text
		const GLchar* p[1];
		p[0] = Text.c_str();
		GLint Lengths[1];
		Lengths[0] = Text.length();

		//Set the shader source to the created shader with the shader text data
		glShaderSource(Shader, 1, p, Lengths);
		//Compile the shader
		glCompileShader(Shader);
		//Check to make sure the shader compiled correctly
		CheckShaderError(Shader, GL_COMPILE_STATUS, false, "ERR");
		//Attach the shader to the program
		glAttachShader(m_ShaderResource->GetProgram(), Shader);
	}

	void Shader::CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage)
	{
		//Set success to 0
		GLint Success = 0;
		GLchar Error[1024] = { 0 };

		//Check if porgram created okay
		if (isProgram)
			glGetProgramiv(shader, flag, &Success);
		else
			glGetShaderiv(shader, flag, &Success);

		if (!Success) //If not a success
		{
			if (isProgram) //Check program status
				glGetProgramInfoLog(shader, sizeof(Error), NULL, Error);
			else
				glGetShaderInfoLog(shader, sizeof(Error), NULL, Error);
			//Print the error message
			fprintf(stderr, "%s: '%s'\n", errorMessage.c_str(), Error);
		}
	}

	std::string Shader::LoadShader(const std::string& fileName)
	{
		//Include keyword
		std::string INCLUDE_DIRECTIVE = "#include";
		//Create file stream
		std::ifstream File;
		//Open the file
		File.open(("./Shaders/" + fileName).c_str());

		//Create output and current line
		std::string Output, Line;

		if (File.is_open()) //Check if file opened properly
		{
			while (File.good()) //While there is still text to process
			{
				//Get the current line
				getline(File, Line);
				//Find the include directive
				if (Line.find(INCLUDE_DIRECTIVE) == std::string::npos)
					Output.append(Line + "\n"); //Append the line to the output
				else
				{
					//Get the include filename, and the file being pointed at
					std::string IncludeFileName = Util::Split(Line, ' ')[1];
					IncludeFileName = IncludeFileName.substr(1, IncludeFileName.length() - 2);
					//Load the file being include
					std::string toAppend = LoadShader(IncludeFileName);
					//Add the file being included's text to the output
					Output.append(toAppend + "\n");
				}
			}
		}
		else //File didnt open properly, so display message
			std::cerr << "Unable to load shader: " << fileName << std::endl;
		//Return the loaded shader text
		return Output;
	}

	STRUCTMAP Shader::FindUniformStructs(const std::string& ShaderText)
	{
		//Prepare return struct map
		STRUCTMAP Result = STRUCTMAP();
		//Define struct keyword
		std::string STRUCT_KEYWORD = "struct";
		//Get struct start location
		size_t StructStartLocation = ShaderText.find(STRUCT_KEYWORD);
		//While there is still data to process
		while (StructStartLocation != std::string::npos)
		{
			//Get start and end pos of the struct
			int NameBegin = StructStartLocation + STRUCT_KEYWORD.size() + 1;
			int BraceBegin = ShaderText.find("{", NameBegin);
			int BraceEnd = ShaderText.find("}", BraceBegin);

			//Get The struct name
			std::string StructName = ShaderText.substr(NameBegin, BraceBegin - NameBegin -1);		//Gets name of the struct name

			//Add All the struct components
			std::vector<StructComponent> StructComp = std::vector<StructComponent>();

			//Find the semi colon position
			size_t ComponentSemiColonPos = ShaderText.find(";", BraceBegin);
			//Search for end of element
			while ((ComponentSemiColonPos != std::string::npos) && (ComponentSemiColonPos < BraceEnd))
			{
				int ComponentNameStart = ComponentSemiColonPos;
				//Backtrack for space
				while (!isspace(ShaderText[ComponentNameStart - 1]))
					ComponentNameStart--;

				int ComponentTypeEnd = ComponentNameStart - 1;
				int ComponentTypeStart = ComponentTypeEnd ;
				//Backtrack for whitespace
				while (!isspace(ShaderText[ComponentTypeStart - 1]))
					ComponentTypeStart--;

				std::string ComponentName = ShaderText.substr(ComponentNameStart, ComponentSemiColonPos - ComponentNameStart);
				std::string ComponentType = ShaderText.substr(ComponentTypeStart, ComponentTypeEnd - ComponentTypeStart);
				//Add the component
				StructComp.push_back(StructComponent(ComponentName, ComponentType));
				//Find the next semicolon
				ComponentSemiColonPos = ShaderText.find(";", ComponentSemiColonPos + 1);
			}
			//Add the struct pair to the map
			Result.insert(STRUCTPAIR(StructName, StructComp));
			//Update the struct start location
			StructStartLocation = ShaderText.find(STRUCT_KEYWORD, StructStartLocation + STRUCT_KEYWORD.size());
		}
		//Return the map of all the structures
		return Result;
	}
}