#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	glm::mat4 perspective;
	glm::mat4 view;

public:
	Camera();
	~Camera();

	void translate(float x, float y, float z);
	void rotate(float angle, float x, float y, float z);
	void scale(float x, float y, float z);
	void set_ortho(float width, float height, float near, float far);
	void set_projective(float width, float height, float fovy, float near, float far);

	glm::mat4 get_matrix();
};

#endif//CAMERA_HPP