#pragma once

#include <GL/glew.h>
#include <FreeImage/FreeImagePlus.h>

#include "Uniform.h"
#include "../Utils/ImageIOException.h"

namespace AirEngine {
	namespace Graphics {
		class Texture {
		public:
			Texture();
			Texture(const GLchar* path);

			Texture(const Texture& data);
			Texture(Texture&& data);

			~Texture();

			GLuint getTexture();
		private:
			GLuint tex;
	
			void loadTexture(const GLchar* path);
			void loadDefaultTexture();
			void initTexture(int width, int height, unsigned int bytesPerPixel, const BYTE* bits);
		};
	}
}