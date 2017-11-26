#include "BaseObject.h"

namespace AirEngine {
	namespace Entity {
		BaseObject::BaseObject(std::shared_ptr<Graphics::Model>& model) : model(model), matrix(1.0f) {
		}

		BaseObject::BaseObject(const BaseObject& data) {
			model = data.model;

			matrix = data.matrix;
		}

		BaseObject::BaseObject(BaseObject&& data) {
			model = data.model;

			matrix = data.matrix;

			data.model.reset();

			data.matrix = Math::mat4(1.0f);
		}

		BaseObject::~BaseObject() {
		}

		void BaseObject::addComponent(Components::Component* component) {
			components.push_back(component);
		}

		const Math::mat4& BaseObject::getMatrix() {
			return matrix;
		}

		const Math::mat4 BaseObject::getModelMatrix() {
			Math::mat4 temp = matrix;

			Math::mat4 identity(1.0f);
			matrix = identity;

			return temp;
		}
				
		Graphics::Model& BaseObject::getModel() {
			return *model.lock();
		}

		void BaseObject::setMatrix(Math::mat4 matrix) {
			this->matrix = matrix;
		}

		void BaseObject::update() {
			for(auto& elem : components) {
				elem->update(*this);
			}
		}
	}
}