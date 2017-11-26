#pragma once

#include "../Math/vec3.h"
#include "../Math/mat4.h"

namespace AirEngine {
	namespace Entity {
		class Camera {
		public:
			Camera(Math::vec3 position, Math::vec3 front, Math::vec3 up);
			Camera(Math::vec3 position, Math::vec3 front, Math::vec3 up, float fov, float aspectRatio, float near, float far);

			Math::mat4 getViewMatrix();
			Math::mat4 getProjectionMatrix();

			void setPosition(Math::vec3 position);
		private:
			Math::vec3 position;
			Math::vec3 front;
			Math::vec3 up;
			Math::vec3 right;

			float fov;
			float aspectRatio;
			float nearClip;
			float farClip;
		};
	}
}