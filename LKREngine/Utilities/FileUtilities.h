#pragma once

#include <string>
#include <fstream>
#include <istream>
#include <vector>
#include "../Graphics/Mesh.h"

using namespace std;

namespace LKREngine {
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
				//return ...;
			}

			string line;
			string splitLine[5];

			while (getline(file, line))
			{
				int currPos = 0, nextPos = 0;

				if (line.substr(0, currPos = line.find(" ")) == "v")
				{
					Graphics::Vertex newVert;

					newVert.position.x = stof(line.substr(currPos + 1, nextPos = line.find(" ", currPos + 1)));
					currPos = nextPos + 1;
					newVert.position.y = stof(line.substr(currPos, nextPos = line.find(" ", currPos)));
					currPos = nextPos + 1;
					newVert.position.z = stof(line.substr(currPos, nextPos = line.find(" ", currPos)));

					vertices.push_back(newVert);
				}

				if (line.substr(0, currPos = line.find(" ")) == "vn")
				{
					cout << "NORMALS NOT IMPLEMENTED YET!" << endl;
				}
			}

			file.close();

			return Graphics::Mesh(vertices,indices, textures);
		}
	}
}