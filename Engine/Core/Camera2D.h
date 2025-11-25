




#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:
glm::vec2 position;
float zoom = 1.0f;


glm::mat4 GetMatrix(float width, float height) const {
return glm::ortho(0.0f, width / zoom, 0.0f, height / zoom) * glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0));
}
};