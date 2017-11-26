#include "AssetPool.h"

namespace AirEngine {
	namespace Utils {
		AssetPool::AssetPool() {
		}

		AssetPool::~AssetPool() {

		}

		//void AssetPool::addMesh(std::string name, Mesh& mesh) {
		//	meshPool.emplace(name, std::make_shared<Mesh>(mesh));
		//}

		//void AssetPool::addTexture(std::string name, Texture& tex) {
		//	texPool.emplace(name, std::make_shared<Texture>(tex));
		//}

		//void AssetPool::addMaterial(std::string name, Material& mat) {
		//	matPool.emplace(name, std::make_shared<Material>(mat));
		//}

		//void AssetPool::addModel(std::string name, Model& model) {
		//	modelPool.emplace(name, std::make_shared<Model>(model));
		//}

		void AssetPool::createMesh(std::string name, Graphics::VertexData& data) {
			meshPool.emplace(name, std::make_shared<Graphics::Mesh>(data));
		}

		void AssetPool::createMesh(std::string name, const GLchar* path) {
			meshPool.emplace(name, std::make_shared<Graphics::Mesh>(path));
		}

		void AssetPool::createTexture(std::string name, const GLchar* path) {
			texPool.emplace(name, std::make_shared<Graphics::Texture>(path));
		}

		void AssetPool::createMaterial(std::string name, std::string albedo, std::string normal) {
			matPool.emplace(name, std::make_shared<Graphics::Material>(texPool[albedo], texPool[normal]));
		}

		void AssetPool::createModel(std::string name, std::string mesh, std::string material) {
			modelPool.emplace(name, std::make_shared<Graphics::Model>(meshPool[mesh], matPool[material]));
		}

		void AssetPool::createBaseObject(std::string name, std::string model) {
			baseObjectPool.emplace(name, std::make_shared<Entity::BaseObject>(modelPool[model]));
		}

		std::shared_ptr<Graphics::Mesh>& AssetPool::getMesh(std::string name) {
			return meshPool[name];
		}

		std::shared_ptr<Graphics::Texture>& AssetPool::getTexture(std::string name) {
			return texPool[name];
		}

		std::shared_ptr<Graphics::Material>& AssetPool::getMaterial(std::string name) {
			return matPool[name];
		}

		std::shared_ptr<Graphics::Model>& AssetPool::getModel(std::string name) {
			return modelPool[name];
		}

		std::shared_ptr<Entity::BaseObject> AssetPool::getBaseObject(std::string name) {
			return baseObjectPool[name];
		}

		void AssetPool::printUsage() {
			std::cout << "##### Meshes #####" << std::endl;
			for(const auto& elem : meshPool) {
				std::cout << elem.first << " : " << elem.second.use_count() << std::endl;
			}
			std::cout << "##### Textures #####" << std::endl;
			for(const auto& elem : texPool) {
				std::cout << elem.first << " : " << elem.second.use_count() << std::endl;
			}
			std::cout << "##### Materials #####" << std::endl;
			for(const auto& elem : matPool) {
				std::cout << elem.first << " : " << elem.second.use_count() << std::endl;
			}
			std::cout << "##### Models #####" << std::endl;
			for(const auto& elem : modelPool) {
				std::cout << elem.first << " : " << elem.second.use_count() << std::endl;
			}
			std::cout << "##### BaseObjects #####" << std::endl;
			for(const auto& elem : baseObjectPool) {
				std::cout << elem.first << " : " << elem.second.use_count() << std::endl;
			}
		}
	}
}