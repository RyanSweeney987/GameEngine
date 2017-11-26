#pragma once

#include <string>
#include <memory>

#include "../Graphics/Model.h"
#include "../Math/vec3.h"
#include "../Math/mat4.h"

#include "Components/Component.h"

namespace AirEngine {
	namespace Entity {
		namespace Components {
			class Component;
			class MovementComponent;
		}

		class BaseObject {
		public:
			BaseObject(std::shared_ptr<Graphics::Model>& model);

			BaseObject(const BaseObject& data);
			BaseObject(BaseObject&& data);

			~BaseObject();

			void addComponent(Components::Component* component);

			const Math::mat4& getMatrix();
			const Math::mat4 getModelMatrix();

			Graphics::Model& getModel();

			void setMatrix(Math::mat4 matrix);

			void update();
		private:
			std::weak_ptr<Graphics::Model> model;
			Math::mat4 matrix;
			std::vector<Components::Component*> components;
		};
	}
}
