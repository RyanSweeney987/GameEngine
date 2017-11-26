#pragma once

#include "../../Math/Maths.h"
#include "../../Math/mat4.h"
#include "../../Math/vec3.h"

#include "Component.h"

#include "../BaseObject.h"

namespace AirEngine {
	namespace Entity {
		namespace Components {
			// TODO: seperate movement and rotation
			class MovementComponent : public Component {
			public:
				void update(BaseObject& parent);

				Math::vec3& getPosition();
				Math::vec3& getVelocity();
				float getRotation();

				void setPosition(const Math::vec3& position);
				void setVelocity(const Math::vec3& velocity);
				void setRotation(float radians);
				void addRotation(float radians);
			private:
				Math::vec3 position;
				Math::vec3 velocity;
				bool autoRotation;
				float rotation;
			};
		}
	}
}