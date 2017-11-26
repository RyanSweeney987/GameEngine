#include "Texture.h"

#include <iostream>
#include <exception>

namespace AirEngine {
	namespace Graphics {
		Texture::Texture() {
			loadDefaultTexture();
		}

		Texture::Texture(const GLchar* path) {
			if(path) {
				try {
					loadTexture(path);
				} catch(ImageIOException& exception) {
					std::cout << exception.what() << " - Loading default texture!" << std::endl;
					loadDefaultTexture();
				}		
			} else {
				std::cout << "Texture path is null - Loading default texture!" << std::endl;
				loadDefaultTexture();
			}	
		}

		Texture::Texture(const Texture& data) {
			tex = data.tex;
		}

		Texture::Texture(Texture&& data) {
			tex = data.tex;

			data.tex = 0;
		}

		Texture::~Texture() {
			glDeleteTextures(1, &tex);
			tex = 0;

			std::cout << "Destroying texture" << std::endl;
		}

		GLuint Texture::getTexture() {
			return tex;
		}

		void Texture::loadTexture(const GLchar* path) {
			BYTE* bits = nullptr;
			unsigned int width, height;
			unsigned int bytesPerPixel;

			std::cout << "Loading texture: " << path << std::endl;
	
			FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path);
			FIBITMAP* image = FreeImage_Load(format, path, 0);

			// Get bit data
			bits = FreeImage_GetBits(image);
			// Release image, no longer needed

			// Get height and width of image
			width = FreeImage_GetWidth(image);
			height = FreeImage_GetHeight(image);

			if((bits == 0) || (width == 0) || (height == 0)) {
				throw ImageIOException("Error getting image data");
			}

			// Get bit depth
			bytesPerPixel = FreeImage_GetBPP(image) / 8;
			// Reorder byte data from BGR to RGB (BGRA to RBGA)
			for(unsigned int i = 0; i < width * height * bytesPerPixel; i += bytesPerPixel) {
				BYTE red = bits[i + 2];
				BYTE blue = bits[i];

				bits[i] = red;
				bits[i + 2] = blue;
			}

			initTexture(width, height, bytesPerPixel, bits);

			FreeImage_Unload(image);
		}

		void Texture::loadDefaultTexture() {
			BYTE bits[3] = {255, 0, 255};

			initTexture(1, 1, 3, bits);
		}

		void Texture::initTexture(int width, int height, unsigned int bytesPerPixel, const BYTE* bits) {
			glGenTextures(1, &tex);

			glBindTexture(GL_TEXTURE_2D, tex);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			// First param - Texture target
			// Second param - Mipmap level
			// Third param - Format (RGB or RGBA etc)
			// Fourth param - Width of texture
			// Fifth param - Height of texture
			// Sixth param - 0, legacy stuff
			// Seventh param - Format and data type of source image
			// Eigth param - Same as above (?)
			// Ninth param - Actual image data
			switch(bytesPerPixel) {
				case 3:
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bits);
					break;
				case 4:
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);
					break;
			}
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}
