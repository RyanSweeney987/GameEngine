#include "MovementComponent.h"

namespace AirEngine {
	namespace Entity {
		namespace Components {
			void MovementComponent::update(BaseObject& parent) {
				position += velocity;

				Math::mat4 trans = parent.getMatrix().translate(position);
				Math::mat4 rot = parent.getMatrix().rotate(rotation, Math::vec3(0.0f, 0.0f, 1.0f));
				parent.setMatrix(trans *= rot);
			}

			Math::vec3& MovementComponent::getPosition() {
				return position;
			}

			Math::vec3& MovementComponent::getVelocity() {
				return velocity;
			}

			float MovementComponent::getRotation() {
				return rotation;
			}
			
			void MovementComponent::setPosition(const Math::vec3& position) {
				this->position = position;
			}

			void MovementComponent::setVelocity(const Math::vec3& velocity) {
				this->velocity = velocity;
			}

			void MovementComponent::setRotation(float radians) {
				rotation = radians;
			}

			void MovementComponent::addRotation(float radians) {
				rotation += radians;
			}
		}
	}
}
