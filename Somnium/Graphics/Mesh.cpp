#include "Mesh.h"

namespace Somnium
{
	namespace Graphics
	{
	    int indiceSize = 0;

		Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
			: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
		{
			setup();
		}

		Mesh::~Mesh()
		{
			glDeleteVertexArrays(1, &m_VAO);
			glDeleteBuffers(1, &m_VBO);
			glDeleteBuffers(1, &m_EBO);
		}

		inline void Mesh::setup()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_EBO);

            float vertices[] = {
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, -0.5f,
                0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f,
                -0.5f, 0.5f, -0.5f
			};

			unsigned int indices[] = {
                1, 2, 6,
                6, 5, 1,

                1, 5, 4,
                4, 0, 1,

                0, 3, 2,
                2, 1, 0,

                0, 4, 7,
                7, 3, 0,

                6, 2, 3,
                3, 7, 6,

                6, 7, 4,
                4, 5, 6
			};

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)/* * m_Vertices.size() */, vertices, GL_STATIC_DRAW); //Originally GL_STATIC_DRAW

			printf("VERT ARR: %d CLASS: %d\r\n", sizeof(vertices), sizeof(m_Vertices));
			printf("VERTEX: %d\r\n", sizeof(Vertex));
            printf("IND  ARR: %d CLASS: %d\r\n", indiceSize = sizeof(indices), sizeof(m_Indices));


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) /* *m_Indices.size()*/, indices, GL_STATIC_DRAW); //Originally GL_STATIC_DRAW

			glVertexAttribPointer(SHADER_POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
            glEnableVertexAttribArray(SHADER_POSITION_INDEX);

		//	glEnableVertexAttribArray(SHADER_NORMAL_INDEX);
		//	glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

			//glEnableVertexAttribArray(SHADER_TEXTURE_COORDINATE_INDEX);
			//glVertexAttribPointer(SHADER_TEXTURE_COORDINATE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

			glBindVertexArray(0);
		}

		void Mesh::draw(Shader& shader)
		{
			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, indiceSize, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0); //TODO: Binding/unbinding every object is a waste of processing!!! OPTIMISE!
		}
	}
}
