#include "Renderer.h"

namespace AirEngine {
	namespace Graphics {
		Renderer::Renderer(Shader& shader) : camera(Math::vec3(0.0f, 0.0f, 50.0f), Math::vec3(0.0f, 0.0f, -1.0f), 
			Math::vec3(0.0f, 1.0f, 0.0f)) {
			shader_ = &shader;
			shader_->useProgram();

			modelLoc = Uniform(shader.getUniformLocation("model"));
			viewLoc = Uniform(shader.getUniformLocation("view"));
			projectionLoc = Uniform(shader.getUniformLocation("projection"));

			albedoTexUniform = Uniform(shader.getUniformLocation("albedo"));
			normalTexUniform = Uniform(shader.getUniformLocation("normal"));
		}

		Entity::Camera& Renderer::getCamera() {
			return camera;
		}

		void Renderer::update(Window& window, std::vector<std::weak_ptr<Entity::BaseObject>>& objects) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUniformMatrix4fv(viewLoc.getUniformLocation(), 1, GL_FALSE, 
				camera.getViewMatrix().transpose().elements);
			glUniformMatrix4fv(projectionLoc.getUniformLocation(), 1, GL_FALSE, 
				camera.getProjectionMatrix().transpose().elements);

			for(auto&& elem : objects) {
				if(auto ptr = elem.lock()) {
					glUniformMatrix4fv(modelLoc.getUniformLocation(), 1, GL_FALSE, ptr.get()->getModelMatrix().transpose().elements);

					glBindVertexArray(ptr.get()->getModel().getMesh().getVAO());

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, ptr.get()->getModel().getMaterial().getAlbedoTex());
					glUniform1i(albedoTexUniform.getUniformLocation(), GL_TEXTURE0);

					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, ptr.get()->getModel().getMaterial().getNormalTex());
					glUniform1i(normalTexUniform.getUniformLocation(), GL_TEXTURE1);

					glDrawElements(GL_TRIANGLES, ptr.get()->getModel().getMesh().getVertexDrawCount(), GL_UNSIGNED_INT, 0);
					glBindVertexArray(0);
				}
			}

			glfwSwapBuffers(window.getGLFWWindow());
		}

	}
}

