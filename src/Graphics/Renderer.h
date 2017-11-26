#pragma once

#include <memory>

#include <stdexcept>

#include "Window.h"

#include "../Entity/BaseObject.h"
#include "../Entity/Camera.h"

namespace AirEngine {
	namespace Graphics {
		class Renderer {
		public:
			Renderer(Shader& shader);

			Entity::Camera& getCamera();

			void update(Window& window, std::vector<std::weak_ptr<Entity::BaseObject>>& objects);
		private:
			Shader* shader_;

			Entity::Camera camera;

			Uniform modelLoc;
			Uniform viewLoc;
			Uniform projectionLoc;

			Uniform albedoTexUniform;
			Uniform normalTexUniform;
		};
	}
}
