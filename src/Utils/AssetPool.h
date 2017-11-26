#pragma once

#include <memory>
#include <map>
#include <string>

#include "../Graphics/Texture.h"
#include "../Graphics/Material.h"
#include "../Graphics/Model.h"

#include "../Entity/BaseObject.h"

namespace AirEngine {
	namespace Utils {
		enum AssetType {
			MESH,
			TEXTURE,
			MATERIAL,
			MODEL,
			GAMEOBJECT
		};

		class AssetPool {
		public:
			AssetPool();

			~AssetPool();

			//void addMesh(std::string name, Mesh& mesh);
			void createMesh(std::string name, Graphics::VertexData& data);
			void createMesh(std::string name, const GLchar* path);

			//void addTexture(std::string name, Texture& tex);
			void createTexture(std::string name, const GLchar* path);

			//void addMaterial(std::string name, Material& mat);
			void createMaterial(std::string name, std::string albedo, std::string normal);

			//void addModel(std::string name, Model& model);
			void createModel(std::string name, std::string mesh, std::string material);

			void createBaseObject(std::string name, std::string model);

			std::shared_ptr<Graphics::Mesh>& getMesh(std::string name);
			std::shared_ptr<Graphics::Texture>& getTexture(std::string name);
			std::shared_ptr<Graphics::Material>& getMaterial(std::string name);
			std::shared_ptr<Graphics::Model>& getModel(std::string name);
			std::shared_ptr<Entity::BaseObject> getBaseObject(std::string name);
			
			void printUsage();
		private:
			std::map<std::string, std::shared_ptr<Graphics::Mesh>> meshPool;
			std::map<std::string, std::shared_ptr<Graphics::Texture>> texPool;
			std::map<std::string, std::shared_ptr<Graphics::Material>> matPool;
			std::map<std::string, std::shared_ptr<Graphics::Model>> modelPool;
			std::map<std::string, std::shared_ptr<Entity::BaseObject>> baseObjectPool;
		};
	}
}
