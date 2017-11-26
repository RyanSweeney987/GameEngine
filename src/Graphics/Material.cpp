#include "Material.h"

namespace AirEngine {
	namespace Graphics {
		Material::Material(std::shared_ptr<Texture>& albedo, std::shared_ptr<Texture>& normal) {
			albedo_ = albedo;
			normal_ = normal;
		}

		Material::Material(const Material& data) {
			albedo_ = data.albedo_;
			normal_ = data.normal_;
		}

		Material::Material(Material&& data) {
			albedo_.swap(data.albedo_);
			normal_.swap(data.normal_);

			data.albedo_.reset();
			data.normal_.reset();
		}

		GLuint Material::getAlbedoTex() {
			return albedo_.lock()->getTexture();
		}

		GLuint Material::getNormalTex() {
			return normal_.lock()->getTexture();
		}
	}
}