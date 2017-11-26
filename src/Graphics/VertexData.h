#pragma once

#include <GL/glew.h>

#include <vector>
#include <iostream>

#include "../Math/vec3.h"
#include "../Math/vec2.h"

namespace AirEngine {
	namespace Graphics {
		struct Vertex {
			Math::vec3 position;
			Math::vec3 normal;
			Math::vec2 texCoords;
		};

		class VertexData {
		public:
			VertexData(std::vector<Vertex> vertices, std::vector<GLuint> indices);

			std::vector<Vertex>& getVertices();

			std::vector<GLuint>& getIndices();

			std::vector<GLint>& getAttributeData();

			GLuint getAttributeStride();

			std::vector<GLint> getAttributeOffsets();

			size_t getAttribCount();
		private:
			std::vector<Vertex> vertices_;
			std::vector<GLuint> indices_;
			std::vector<GLint> attributeData_;
			GLuint attributeStride_;
			std::vector<GLint> attributeOffsets_;
		};
	}
}