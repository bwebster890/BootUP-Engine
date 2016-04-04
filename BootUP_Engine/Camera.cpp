#include "Camera.hpp"

Camera::Camera() 
{
	view = glm::mat4(1);
	perspective = glm::mat4(0);
}
Camera::~Camera() {}

void Camera::translate(float x, float y, float z)
{
	glm::translate(glm::mat4(view), glm::vec3(x, y, z));
}
void Camera::rotate(float angle, float x, float y, float z)
{
	glm::rotate(glm::mat4(view), angle, glm::vec3(x, y, z));
}
void Camera::scale(float x, float y, float z)
{
	glm::scale(glm::mat4(view), glm::vec3(x, y, z));
}
void Camera::set_ortho(float width, float height, float near, float far)
{
	perspective = glm::ortho(0.f, width, height, 0.f, near, far);
}
void Camera::set_projective(float width, float height, float fovy, float near, float far)
{
	perspective = glm::perspective(fovy, width / height, near, far);
}

glm::mat4 Camera::get_matrix() 
{
	return (view * perspective);
}