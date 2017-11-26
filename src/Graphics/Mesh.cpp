#include "Mesh.h"

namespace AirEngine {
	namespace Graphics {
		Mesh::Mesh() {
			loadDefaultMesh();
		}

		Mesh::Mesh(VertexData& data) {
			initMesh(data);

			vertexDrawCount_ = data.getIndices().size();
		}

		Mesh::Mesh(const GLchar* path) {
			if(path) {
				try {
					loadMesh(path);
				} catch(MeshIOException& e) {
					std::cout << e.what() << " - Loading default mesh" << std::endl;
					loadDefaultMesh();
				}
			} else {
				loadDefaultMesh();
			}
			
		}

		Mesh::Mesh(const Mesh& data) {
			vao_ = data.vao_;
			vbo_ = data.vbo_;
			ebo_ = data.ebo_;
			vertexDrawCount_ = data.vertexDrawCount_;
		}

		Mesh::Mesh(Mesh&& data) {
			vao_ = data.vao_;
			vbo_ = data.vbo_;
			ebo_ = data.ebo_;
			vertexDrawCount_ = data.vertexDrawCount_;

			data.vao_ = 0;
			data.vbo_ = 0;
			data.ebo_ = 0;
			data.vertexDrawCount_ = 0;
		}

		Mesh::~Mesh() {
			std::cout << "Destroying mesh" << std::endl;

			glDeleteVertexArrays(1, &vao_);
			glDeleteBuffers(1, &vbo_);
			glDeleteBuffers(1, &ebo_);
		}

		GLuint Mesh::getVAO() {
			return vao_;
		}

		GLsizei Mesh::getVertexDrawCount() {
			return vertexDrawCount_;
		}

		void Mesh::loadMesh(const GLchar* path) {
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

			if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
				throw MeshIOException(importer.GetErrorString());
			}

			processNode(scene->mRootNode, scene);

			vertexDrawCount_ = meshes_.at(0).getIndices().size();
			initMesh(meshes_.at(0));
		}

		void Mesh::loadDefaultMesh() {
			std::vector<Vertex> vertices {
				{Math::vec3(-1.0f, 1.0f, 0.0f), Math::vec3(0.0f, 1.0f, 0.0f), Math::vec2(0.0f, 0.0f)},
				{Math::vec3(1.0f, 1.0f, 0.0f), Math::vec3(0.0f, 1.0f, 0.0f), Math::vec2(1.0f, 0.0f)},
				{Math::vec3(-1.0f, -1.0f, 0.0f), Math::vec3(0.0f, 1.0f, 0.0f), Math::vec2(1.0f, 1.0f)},
				{Math::vec3(1.0f, -1.0f, 0.0f), Math::vec3(0.0f, 1.0f, 0.0f), Math::vec2(0.0f, 1.0f)}
			};

			std::vector<GLuint> indices {
				0, 1, 2, 1, 3, 2
			};

			initMesh(VertexData(vertices, indices));
		}

		void Mesh::processNode(aiNode* node, const aiScene* scene) {
			// Process each mesh located at the current node
			for(GLuint i = 0; i < node->mNumMeshes; i++) {
				// The node object only contains indices to index the actual objects in the scene. 
				// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshes_.push_back(processMesh(mesh, scene));
			}
			// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
			for(GLuint i = 0; i < node->mNumChildren; i++) {
				this->processNode(node->mChildren[i], scene);
			}
		}

		VertexData Mesh::processMesh(aiMesh* mesh, const aiScene* scene) {
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;

			// Walk through each of the mesh's vertices
			for(GLuint i = 0; i < mesh->mNumVertices; i++) {
				Vertex vertex;
				Math::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
								  // Positions
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.position = vector;
				// Normals
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;
				// Texture Coordinates
				if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
				{
					Math::vec2 vec;
					// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
					// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
					vec.x = mesh->mTextureCoords[0][i].x;
					vec.y = mesh->mTextureCoords[0][i].y;
					vertex.texCoords = vec;
				} else
					vertex.texCoords = Math::vec2(0.0f, 0.0f);
				vertices.push_back(vertex);
			}
			// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
			for(GLuint i = 0; i < mesh->mNumFaces; i++) {
				aiFace face = mesh->mFaces[i];
				// Retrieve all indices of the face and store them in the indices vector
				for(GLuint j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			return VertexData(vertices, indices);
		}

		void Mesh::initMesh(VertexData& data) {
			// Define Vertex Array Object
			glGenVertexArrays(1, &vao_);
			glBindVertexArray(vao_);
			// Define Vertex Buffer Object
			glGenBuffers(1, &vbo_);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_);

			glBufferData(GL_ARRAY_BUFFER, data.getVertices().size() * sizeof(Vertex), &data.getVertices()[0], GL_STATIC_DRAW);
			// Definde Element Buffer Object
			glGenBuffers(1, &ebo_);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.getIndices().size() * sizeof(GLuint), &data.getIndices()[0], GL_STATIC_DRAW);
			// Attributes get bound to to current VBO
			// First param, specific vertex attribute e.g:(location = 0)
			// Second param, size of vertex attribute e.g:(vec3 = 3 values)
			// Third param, type of data e.g:(GL_FLOAT, vec in GLSL = float)
			// Fourth param, whether to normalize e.g:(2 and -2 will become 1 and -1)
			// Fifth param, stride, space between consecutive attribute sets e.g:(next set is 3 GLFloats away, we specify that value)
			// Sixth param, offset of where data begins in buffer
			for(int i = 0; i < data.getAttribCount(); i++) {
				glVertexAttribPointer(i, data.getAttributeData().at(i), GL_FLOAT, GL_FALSE, data.getAttributeStride(),
					(GLvoid*) (data.getAttributeOffsets().at(i)));
				glEnableVertexAttribArray(i);
			}

			glBindVertexArray(0);
		}
	}
}