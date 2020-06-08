#include "Camera.h"

#include <math.h>

glm::mat4 baseMatrix;
Camera::Camera() {
	follower = NULL;
	glm::mat4 m1 = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3{ 0,0,1 });
	baseMatrix = glm::rotate(m1, glm::radians(90.0f), glm::vec3{ 0,1,0 });
}

Camera::Camera(vec3d p, vec3d r) {
	position.x = p.x;
	position.y = p.y;
	position.z = p.z;

	rotation.x = r.x;
	rotation.y = r.y;
	rotation.z = r.z;
}

void Camera::setPosition(vec3d p)
{
	position.x = p.x;
	position.y = p.y;
	position.z = p.z;


}

void Camera::setRotation(vec3d r)
{
	rotation.x = r.x;
	rotation.y = r.y;
	rotation.z = r.z;
}


void Camera::Turn(int deltaX, int deltaY)
{
	rotation.x += float(deltaX) * 0.5f;
	rotation.y += float(deltaY) * 0.5f;
}

void Camera::UpDown(int deltaX, int deltaY)
{
	float side = 0.01f * float(deltaX);
	float fwd = 0.01f * float(deltaY);
	float s = sinf(DEG2RAD(position.x));
	float c = cosf(DEG2RAD(position.y));

	position.x += -s * side + c * fwd;
	position.y += c * side + s * fwd;
}

void Camera::setFollower(vec3d* follow)
{
	follower = follow;
}

void Camera::setCamera()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glRotatef(rotation.z, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(-rotation.x, 0, 0, 1);
	glTranslatef(-position.x, -position.y, -position.z);

}

void Camera::setProjectionMatrix(float fov,float zNear, float zFar)
{
	float ratio = this->width / this->height;
	this->projection = glm::perspective(glm::radians(fov), ratio, zNear, zFar);
	
}

void Camera::recalculateViewMatrix()
{
	
	glm::mat4 m3 = glm::rotate(baseMatrix, glm::radians(rotation.z), glm::vec3{ 1,0,0 });
	glm::mat4 m4 = glm::rotate(m3, glm::radians(rotation.y), glm::vec3{ 0,1,0 });
	glm::mat4 m5 = glm::rotate(m4, glm::radians(-rotation.x), glm::vec3{ 0,0,1 });

	this->view = glm::translate(m5, glm::vec3{ -position.x,-position.y,-position.z });
}
