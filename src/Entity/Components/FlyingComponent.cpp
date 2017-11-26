#include "FlyingComponent.h"

namespace AirEngine {
	namespace Entity {
		namespace Components {
			void FlyingComponent::update(BaseObject& parent) {
				// Current direction vector
				float x = Math::cos(getRotation());
				float y = Math::sin(getRotation());
				// Add angle vector to current velocity vector to move towards said vector
				Math::vec3 velocity = getVelocity() + (Math::vec3(x, y, 0.0f) * thrust);
				
				// Get the length of the velocity 
				float maxSpeed = 1.0f;
				float velocityLength = velocity.magnitude();
				float ratio = maxSpeed / velocityLength;
				if(velocityLength > maxSpeed) velocity = velocity * ratio;

				// Slow down to eventual stop when no longer thrusting
				velocity.magnitude() > 0.001f ? velocity = velocity * 0.99f : velocity = Math::vec3(0.0f, 0.0f, 0.0f);

				setVelocity(velocity);
				setPosition(getPosition() += velocity);

				Math::mat4 trans = parent.getMatrix().translate(getPosition());
				Math::mat4 rot = parent.getMatrix().rotate(getRotation(), Math::vec3(0.0f, 0.0f, 1.0f));
				parent.setMatrix(trans *= rot);
			}

			bool FlyingComponent::isPlayerControlled() {
				return playerControlled;
			}

			float FlyingComponent::getThrust() {
				return thrust;
			}

			void FlyingComponent::setPlayerControlled(bool isPlayerControlled) {
				playerControlled = isPlayerControlled;
			}

			void FlyingComponent::setThrust(float amount) {
				thrust = amount;
			}
		}
	}
}