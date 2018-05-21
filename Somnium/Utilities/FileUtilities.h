#pragma once

#include <string>
#include <fstream>
#include <istream>
#include <vector>
#include "../Graphics/Mesh.h"

using namespace std;

namespace Somnium {
	namespace Utilities {
		static string ReadFile(const char* filePath)
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

		static Graphics::Mesh LoadOBJ(const char* filePath)
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
					cout << "FACES NOT IMPLEMENTED YET!" << endl;
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
				//If the structure is unknown or invalid...
				else
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