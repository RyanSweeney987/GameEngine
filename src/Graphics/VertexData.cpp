#include "VertexData.h"

namespace AirEngine {
	namespace Graphics {
		VertexData::VertexData(std::vector<Vertex> vertices, std::vector<GLuint> indices) :
			attributeData_({3, 3, 2}), attributeStride_(sizeof(Vertex)),
			attributeOffsets_({0, offsetof(Vertex, normal), offsetof(Vertex, texCoords)}) {
			vertices_ = vertices;
			indices_ = indices;
		}

		std::vector<Vertex>& VertexData::getVertices() {
			return vertices_;
		}

		std::vector<GLuint>& VertexData::getIndices() {
			return indices_;
		}

		std::vector<GLint>& VertexData::getAttributeData() {
			return attributeData_;
		}

		GLuint VertexData::getAttributeStride() {
			return attributeStride_;
		}

		std::vector<GLint> VertexData::getAttributeOffsets() {
			return attributeOffsets_;
		}

		size_t VertexData::getAttribCount() {
			return 3;
		}
	}
}