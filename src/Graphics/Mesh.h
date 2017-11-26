#pragma once

#include <GL/glew.h>

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

#include <memory>
#include <iostream>

#include "Material.h"
#include "VertexData.h"
#include "../Utils/MeshIOExcepton.h"

namespace AirEngine {
	namespace Graphics {
		class Mesh {
		public:
			Mesh();
			Mesh(VertexData& data);
			Mesh(const GLchar* path);

			Mesh(const Mesh& data);
			Mesh(Mesh&& data);

			~Mesh();

			GLuint getVAO();

			GLsizei getVertexDrawCount();

			//void rotateVertices(glm::vec3 axis, GLfloat radians);
		private:
			GLuint vao_;
			GLuint vbo_;
			GLuint ebo_;
			GLsizei vertexDrawCount_;

			std::vector<VertexData> meshes_;

			void loadMesh(const GLchar* path);
			void loadDefaultMesh();
			void processNode(aiNode* node, const aiScene* scene);
			VertexData processMesh(aiMesh* mesh, const aiScene* scene);
			void initMesh(VertexData& data);
		};
	}
}