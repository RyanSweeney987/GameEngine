#include "Model.h"

namespace AirEngine {
	namespace Graphics {
		Model::Model(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Material>& material) {
			mesh_ = mesh;
			material_ = material;
		}

		Model::Model(const Model& data) {
			mesh_ = data.mesh_;
			material_ = data.material_;
		}

		Model::Model(Model&& data) {
			mesh_.swap(data.mesh_);
			material_.swap(data.material_);

			data.mesh_.reset();
			data.material_.reset();
		}

		Model::~Model() {
			std::cout << "Destroying model" << std::endl;
		}

		Mesh& Model::getMesh() {
			return *mesh_.lock();
		}

		Material& Model::getMaterial() {
			return *material_.lock();
		}
	}
}