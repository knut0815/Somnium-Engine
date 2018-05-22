#pragma once

#include <string>
#include <fstream>
#include <istream>
#include <vector>
#include "../Graphics/Mesh.h"

#ifdef _WIN32
	#define SSCANF sscanf_s
#else 
	#define SSCANF sscanf
#endif

using namespace std;

/**
	SOMNIUM Engine, FileUtilities.h
	Description: Manages the I/O and parsing of various model files into meshes and their mappings

	@author Luke K. Rose
	@version 0.2 21/05/2018

*/

namespace Somnium {
	namespace Utilities {
		static string readFile(const char* filePath)
		{
			ifstream file(filePath, ios::binary);
			
			if(!file.is_open())
			{
				cerr << "Could not open file " << filePath << endl;
				return string("");
			}

			file.seekg(0, file.end);
			unsigned long length = static_cast<unsigned long>(file.tellg());
			file.seekg(0, file.beg);

			char *buffer = new char[length];

			file.read(buffer, length);
			
			file.close();

			string result(buffer, length);
			
			result.shrink_to_fit();

			delete[] buffer;

			return result;
		}

		static Graphics::Mesh loadOBJ(const char* filePath)
		{
			ifstream file(filePath, ios::in);

			std::vector<Graphics::Vertex> vertices;
			std::vector<GLuint> indices;
			std::vector<Graphics::Texture> textures;

			if (!file.is_open())
			{
				cerr << "Could not load OBJ file " << filePath << endl;
				//Return an empty Mesh object, which can then be checked for emptiness with Mesh.StructureExists();
				return Graphics::Mesh(vertices, indices, textures);
			}

			string line;
			string splitLine[5];

			while (getline(file, line))
			{
				int currPos = 0, nextPos = 0;
				
				//Determine what structure the current line represents (Vertex, Normal, Index, etc.)
				string header = line.substr(0, currPos = line.find(" "));
				string values = line.substr(currPos + 1, line.find("\n"));

				//If the structure is a Vertex...
				if (header == "v")
				{
					Graphics::Vertex newVert;

					newVert.position.x = stof(line.substr(currPos + 1, nextPos = line.find(" ", currPos + 1)));
					currPos = nextPos + 1;
					newVert.position.y = stof(line.substr(currPos, nextPos = line.find(" ", currPos)));
					currPos = nextPos + 1;
					newVert.position.z = stof(line.substr(currPos, nextPos = line.find(" ", currPos)));

					vertices.push_back(newVert);

					cout << "VERTICES REQUIRE FURTHER DEVELOPMENT!" << endl;
				}
				//If the structure is an Object Name...
				else if (header == "o") 
				{
					cout << "OBJECT NAMES NOT IMPLEMENTED YET!" << endl;
				}
				//If the structure is a Texture Coordinate...
				else if (header == "vt") 
				{
					cout << "UV TEXTURE COORDINATES NOT IMPLEMENTED YET!" << endl;
				}
				//If the structure is a Normal...
				else if (header == "vn") 
				{
					cout << "NORMALS NOT IMPLEMENTED YET!" << endl;
				}
				//If the structure is a Face...
				else if (header == "f")
				{
					unsigned int vertexIndex, texCoordIndex, normalIndex;
					int end = values.find("\n");
					string value;

					for(int ind = 0; ind < 3; ind++){
						value = values.substr(0, values.find(' '));
						if (SSCANF(value.c_str(), "%d/%d/%d", &vertexIndex, &texCoordIndex, &normalIndex) != 3)
						{
							cerr << "Missing v/vt/vn value in OBJ file" << endl;
							break;
						}
					
						indices.push_back(vertexIndex);
						values = values.substr(values.find(' ') + 1, end); //TODO: This may be slightly/extremely inefficient; make it iterator based, not trim-reassignment based
					}
					cout << "FACES REQUIRE FURTHER DEVELOPMENT!" << endl;
				}
				//If the structure is a Parameter Space Vertex...
				else if (header == "vp")
				{
					cout << "PARAMETER SPACE VERTICES NOT IMPLEMENTED YET!" << endl;
				}
				//If the structure is a Line...
				else if (header == "l") 
				{
					cout << "LINES NOT IMPLEMENTED YET!" << endl;
				}
				//Ignore comments and check if the structure is unknown or invalid...
				else if (header != "#")
				{
					cerr << "UNKNOWN/INVALID STRUCTURE '" << header << "'!\n" 
						 << "If you believe it is valid, please file a bug report at www.GitHub.com/MrLukeKR/Somnium-Engine/issues/new" << endl;
				}
			}

			file.close();

			return Graphics::Mesh(vertices,indices, textures);
		}
	}
}
