#include "Shader.h"
#include "RenderEngine.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "BaseLight.h"

namespace D3DEngine
{
	Shader::Shader(std::string FileName, ShaderList* shaderList)
	{
		m_Name = FileName;
		m_ShaderList = shaderList;
		m_ShaderResource = m_ShaderList->GetShader(FileName);
		if (m_ShaderResource == nullptr)
		{
			std::cerr << "Loaded Shader: " << FileName << std::endl;
			m_ShaderResource = new ShaderResource();
			InitShader(FileName);
			m_ShaderList->AddShader(FileName, m_ShaderResource);
		}
		else
		{
			std::cerr << "Cached Shader: " << FileName << std::endl;
			m_ShaderResource->AddReference();
		}
	}

	void Shader::InitShader(std::string FileName)
	{
		std::string VertexShaderText = LoadShader(FileName + ".vert");
		std::string FragmentShaderText = LoadShader(FileName + ".frag");

		AddVertexShader(VertexShaderText);
		AddFragmentShader(FragmentShaderText);

		//Set Attribs
		AddAllAttributes(&VertexShaderText);

		CompileShader();

		//Uniforms
		AddAllUniforms(&VertexShaderText);
		AddAllUniforms(&FragmentShaderText);
	}

	Shader::~Shader()
	{
		if (m_ShaderResource->RemoveReference())
		{
			m_ShaderList->RemoveShader(m_Name);
			//delete m_ShaderResource;
			std::cerr << "Destructor: Shader: " << m_Name << std::endl;
		}
		else
		{
			std::cerr << "Destructor: Shader - Removed Reference" << std::endl;
		}
	}

	Shader::Shader(const Shader & other)
	{
		std::cerr << "Copied Shader" << std::endl;
	}

	void Shader::CompileShader()
	{
		glLinkProgram(m_ShaderResource->GetProgram());
		CheckShaderError(m_ShaderResource->GetProgram(), GL_LINK_STATUS, true, "Error linking shader program");

		glValidateProgram(m_ShaderResource->GetProgram());
		CheckShaderError(m_ShaderResource->GetProgram(), GL_VALIDATE_STATUS, true, "Invalid shader program");
	}

	void Shader::Bind()
	{
		glUseProgram(m_ShaderResource->GetProgram());
	}

	void Shader::UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine)
	{
		Matrix4f& WorldMatrix = transform->GetTransformation();
		Matrix4f& MVPMatrix = renderEngine->GetCamera()->GetViewProjection().Mult(WorldMatrix);

		//Loop Over all Uniforms
		std::vector<StructComponent>* UniStruct = m_ShaderResource->GetUniformsStruct();
		int Size = UniStruct->size();
		for (int i = 0; i < Size; i++)
		{
			std::string& UniformName = *(&UniStruct->at(i))->GetName();
			std::string& UniformType = *(&UniStruct->at(i))->GetType();

			std::string& UnprefixedUniformName = UniformName.substr(2);

			char FirstLetter = UniformName[0];

			if (UniformType == "sampler2D")	//Texture Uniform
			{
				int SamplerSlot = renderEngine->GetSamplerSlot(UniformName);

				material->GetTexture(UniformName)->Bind(SamplerSlot);
				SetUniformI(UniformName, SamplerSlot);
			}
			else if (FirstLetter == 'T')	//Transform Uniform
			{
				if (UniformName == "T_MVP")
					SetUniformM4(UniformName, MVPMatrix);
				else if (UniformName == "T_Model")
					SetUniformM4(UniformName, WorldMatrix);
				else
					std::cerr << UniformName << ": Illegal Argument" << std::endl;
			}
			else if (FirstLetter == 'R')	//Rendering Engine
			{
				if (UniformType == "vec3")
					SetUniformV(UniformName, renderEngine->GetVector3f(UnprefixedUniformName));
				else if (UniformType == "float")
					SetUniformF(UniformName, renderEngine->GetFloat(UnprefixedUniformName));
				else if (UniformType == "DirectionalLight")
					SetUniformDL(UniformName, renderEngine->GetActiveLight());
				else if (UniformType == "PointLight")
					SetUniformPL(UniformName, renderEngine->GetActiveLight());
				else if (UniformType == "SpotLight")
					SetUniformSL(UniformName, renderEngine->GetActiveLight());
				else	//Handle Extra Struct Case if needed
					renderEngine->UpdateUniformStruct(transform, material, this, UniformName, UniformType);	
			}
			else if (FirstLetter == 'C')	//Camera Engine
			{
				if (UniformName == "C_EyePos")
					SetUniformV(UniformName, renderEngine->GetCamera()->GetTransform()->GetTransformedPos());
				else
					std::cerr << UniformName << ": Illegal Argument" << std::endl;
			}
			else							//Material
			{
				if (UniformType == "vec3")
					SetUniformV(UniformName, material->GetVector3f(UniformName));
				else if (UniformType == "float")
					SetUniformF(UniformName, material->GetFloat(UniformName));
				else
					std::cerr << UniformName << ": Illegal Argument" << std::endl;
			}

		}
		//delete WorldMatrix;
		//delete MVPMatrix;
	}

	void Shader::AddAllAttributes(std::string* ShaderText)
	{
		std::string ATTRIBUTE_KEYWORD = "attribute";

		size_t AttributeStartLocation = ShaderText->find(ATTRIBUTE_KEYWORD);

		int AttribCounter = 0;

		while (AttributeStartLocation != std::string::npos)
		{
			//Get start and end pos of the Attribute
			int Begin = AttributeStartLocation + ATTRIBUTE_KEYWORD.size() + 1;
			int End = ShaderText->find(";", Begin);

			//Get The Attribute name
			std::string AttributeLine = ShaderText->substr(Begin, End - Begin);
			int SpacePos = AttributeLine.find(" ");
			std::string AttributeName = AttributeLine.substr(SpacePos + 1, AttributeLine.size());		//Gets name of the Attribute name

			SetAttribLocation(AttributeName, AttribCounter);	//Add the Attribute
			AttribCounter++;									//Increment Count

			AttributeStartLocation = ShaderText->find(ATTRIBUTE_KEYWORD, AttributeStartLocation + ATTRIBUTE_KEYWORD.size());
		}
	}
	
	void Shader::AddAllUniforms(std::string* ShaderText)
	{
		STRUCTMAP Structs = FindUniformStructs(*ShaderText);

		std::string UNIFORM_KEYWORD = "uniform";

		size_t UniformStartLocation = ShaderText->find(UNIFORM_KEYWORD);
	
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

			m_ShaderResource->AddUniformsStruct(StructComponent(UniformName, UniformType));
			AddUniformWithStructCheck(UniformName, UniformType, Structs);

			UniformStartLocation = ShaderText->find(UNIFORM_KEYWORD, UniformStartLocation + UNIFORM_KEYWORD.size());
		}
	}

	void Shader::AddUniformWithStructCheck(std::string UniformName, std::string UniformType, STRUCTMAP Structs)
	{
		bool AddThis = true;
		std::vector<StructComponent> StructComp = GetStuctFromMap(Structs, UniformType);

		if (StructComp.size() != 0)
		{
			AddThis = false;
			//Add all structs which reference another struct
			for (int i = 0; i < StructComp.size(); i++)
				AddUniformWithStructCheck(UniformName + "." + *StructComp[i].GetName(), *StructComp[i].GetType(), Structs);
		}

		if (AddThis)
		{
			AddUniform(UniformName);
		}
		
	}

	std::vector<StructComponent> Shader::GetStuctFromMap(STRUCTMAP Structs, std::string Key)
	{
		STRUCTMAP::const_iterator it = Structs.find(Key);
		if (it != Structs.end())
		{
			return it->second;
		}
		return std::vector<StructComponent>();
	}

	void Shader::AddUniform(std::string Uniform)
	{
		int UniformLocation = glGetUniformLocation(m_ShaderResource->GetProgram(), Uniform.c_str());
		if (UniformLocation == -1)
			std::cerr << "Error: Couldnt find uniform: " << Uniform << std::endl;
		//Add Uniform to Map
		m_ShaderResource->AddUniform(Uniform, UniformLocation);
		std::cerr << "Uniform: " << Uniform << " added." << std::endl;
	}

	void Shader::SetUniformI(const std::string& UniformName, const int& Value) const
	{
		glUniform1i(m_ShaderResource->GetUniforms()->find(UniformName)->second, Value);
	}

	void Shader::SetUniformF(const std::string& UniformName, float Value) const
	{
		glUniform1f(m_ShaderResource->GetUniforms()->find(UniformName)->second, Value);
	}

	void Shader::SetUniformV(const std::string& UniformName, Vector3f Value) const
	{
		glUniform3f(m_ShaderResource->GetUniforms()->find(UniformName)->second, Value.GetX(), Value.GetY(), Value.GetZ());
	}

	void Shader::SetUniformM4(const std::string& UniformName, const Matrix4f& Value) const
	{
		glUniformMatrix4fv(m_ShaderResource->GetUniforms()->at(UniformName), 1, GL_TRUE, &(Value[0][0]));
	}

	void Shader::SetUniformDL(const std::string& UniformName, BaseLight* DirLight) const
	{
		SetUniformBL(UniformName + ".Light", DirLight);
		SetUniformV(UniformName + ".Direction", DirLight->GetDirection());
	}

	void Shader::SetUniformBL(const std::string& UniformName, BaseLight* BaseLight) const
	{
		SetUniformV(UniformName + ".Colour", BaseLight->GetColour());
		SetUniformF(UniformName + ".Intensity", BaseLight->GetIntensity());
	}

	void Shader::SetUniformPL(const std::string& UniformName, BaseLight* pointLight) const
	{
		SetUniformBL(UniformName + ".Light", pointLight);
		//Attenuation
		SetUniformF(UniformName + ".Atten.Constant", pointLight->GetAttenuation().GetConstant());
		SetUniformF(UniformName + ".Atten.Linear", pointLight->GetAttenuation().GetLinear());
		SetUniformF(UniformName + ".Atten.Exponent", pointLight->GetAttenuation().GetExponent());

		SetUniformV(UniformName + ".Position", pointLight->GetTransform()->GetTransformedPos());
		SetUniformF(UniformName + ".Range", pointLight->GetRange());
	}

	void Shader::SetUniformSL(const std::string& UniformName, BaseLight* spotLight) const
	{
		SetUniformPL(UniformName + ".PLight", spotLight);
		//
		SetUniformV(UniformName + ".Direction", spotLight->GetDirection());
		SetUniformF(UniformName + ".Cutoff", spotLight->GetCutoff());
	}

	void Shader::SetAttribLocation(const std::string& AttribName, int& Location)
	{
		glBindAttribLocation(m_ShaderResource->GetProgram(), Location, AttribName.c_str());
	}

	void Shader::AddProgram(std::string Text, int Type)
	{
		int Shader = glCreateShader(Type);

		if (Shader == 0)
			std::cerr << "Shader Creation Failed: Could not find valid memory location when adding shader" << std::endl;

		const GLchar* p[1];
		p[0] = Text.c_str();
		GLint Lengths[1];
		Lengths[0] = Text.length();

		glShaderSource(Shader, 1, p, Lengths);
		glCompileShader(Shader);

		CheckShaderError(Shader, GL_COMPILE_STATUS, false, "ERR");

		glAttachShader(m_ShaderResource->GetProgram(), Shader);
	}

	void Shader::CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage)
	{
		GLint success = 0;
		GLchar error[1024] = { 0 };

		if (isProgram)
			glGetProgramiv(shader, flag, &success);
		else
			glGetShaderiv(shader, flag, &success);

		if (!success)
		{
			if (isProgram)
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			else
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);

			fprintf(stderr, "%s: '%s'\n", errorMessage.c_str(), error);
		}
	}

	std::string Shader::LoadShader(const std::string& fileName)
	{
		std::string INCLUDE_DIRECTIVE = "#include";
		std::ifstream File;
		File.open(("./Shaders/" + fileName).c_str());

		std::string Output, Line;

		if (File.is_open())
		{
			while (File.good())
			{
				getline(File, Line);

				if (Line.find("#include") == std::string::npos)
					Output.append(Line + "\n");
				else
				{
					std::string includeFileName = Util::Split(Line, ' ')[1];
					includeFileName = includeFileName.substr(1, includeFileName.length() - 2);

					std::string toAppend = LoadShader(includeFileName);
					Output.append(toAppend + "\n");
				}
			}
		}
		else
			std::cerr << "Unable to load shader: " << fileName << std::endl;

		return Output;
	}

	STRUCTMAP Shader::FindUniformStructs(std::string ShaderText)
	{
		STRUCTMAP Result = STRUCTMAP();

		std::string STRUCT_KEYWORD = "struct";

		size_t StructStartLocation = ShaderText.find(STRUCT_KEYWORD);
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

			size_t ComponentSemiColonPos = ShaderText.find(";", BraceBegin);
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
				//std::cerr << ComponentType << " " << ComponentName << std::endl;

				ComponentSemiColonPos = ShaderText.find(";", ComponentSemiColonPos + 1);
			}
			//Add
			Result.insert(STRUCTPAIR(StructName, StructComp));

			StructStartLocation = ShaderText.find(STRUCT_KEYWORD, StructStartLocation + STRUCT_KEYWORD.size());
		}
		return Result;
	}
}