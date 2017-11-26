#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Mesh.h"
#include "Material.h"

namespace AirEngine {
	namespace Graphics {
		class Model {
		public:
			Model(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Material>& material);

			Model(const Model& data);
			Model(Model&& data);

			~Model();

			Mesh& getMesh();
			Material& getMaterial();
		private:
			std::weak_ptr<Mesh> mesh_;
			std::weak_ptr<Material> material_;
		};
	}
}