#pragma once

#include "MovementComponent.h"

namespace AirEngine {
	namespace Entity {
		namespace Components {
			class FlyingComponent : public MovementComponent {
			public:
				void update(BaseObject& parent);

				bool isPlayerControlled();
				float getThrust();
				
				void setPlayerControlled(bool isPlayerControlled);
				void setThrust(float amount);
			private:
				bool playerControlled;
				float thrust;
			};
		}
	}
}