#pragma once

#include <iostream>

namespace AirEngine {
	namespace Entity {
		class BaseObject;
		namespace Components {
			class Component {
			public:
				virtual void update(BaseObject& parent);
			private:
			};
		}
	}
}