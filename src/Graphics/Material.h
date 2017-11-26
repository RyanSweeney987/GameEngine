#pragma once

#include "Texture.h"

#include <memory>

namespace AirEngine {
	namespace Graphics {
		enum TextureType {
			ALBEDO = GL_TEXTURE0,
			NORMAL = GL_TEXTURE1
		};

		class Material {
		public:
			Material(std::shared_ptr<Texture>& albedo, std::shared_ptr<Texture>& normal);

			Material(const Material& data);
			Material(Material&& data);

			GLuint getAlbedoTex();
			GLuint getNormalTex();
		private:
			std::weak_ptr<Texture> albedo_;
			std::weak_ptr<Texture> normal_;
		};
	}
}