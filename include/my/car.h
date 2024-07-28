#ifndef CAR_H
#define CAR_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <queue>

enum Direction
{
	CAR_FORWARD,
	CAR_BACKWARD,
	CAR_LEFT,
	CAR_RIGHT
};

class Car
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	float Yaw;

	queue<float> HistoryYaw;
	int DelayFrameNum = 20;
	float DelayYaw;

	queue<glm::vec3> HistoryPosition;
	glm::vec3 DelayPosition;
	float MovementSpeed;
	float TurningSpeed;

	Car(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f))
		:MovementSpeed(30.0f), TurningSpeed(9.0f), Yaw(0.0f), DelayYaw(0.0f)
	{
		Position = position;
		updateFront();
	}
	glm::vec3 getPossition()
	{
		return Position;
	}
	float getYaw()
	{
		return Yaw;
	}
	float getDelayYaw()
	{
		return DelayYaw;
	}

	float getYawDif()
	{
		return Yaw - DelayYaw;
	}

	float getMidValYaw()
	{
		return (DelayYaw + Yaw) / 2;

	}

	glm::vec3 getMidValPosition()
	{
		return (DelayPosition + Position) / 2.0f;
	}

	glm::mat4 GetViewMatrix(glm::vec3 cameraPosition)
	{
		return glm::lookAt(cameraPosition,Position, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void ProcessKeyboard(Direction direction, float deltaTime)
	{
		if (direction == CAR_FORWARD)
			Position += Front * MovementSpeed * deltaTime;
		if (direction == CAR_BACKWARD)
			Position -= Front * MovementSpeed * deltaTime;
		if (direction == CAR_LEFT)
			Yaw += TurningSpeed * deltaTime;
		if (direction == CAR_RIGHT)
			Yaw -= TurningSpeed * deltaTime;
		updateFront();
	}

	void UpdateDelayYaw()
	{
		HistoryYaw.push(Yaw);
		if (HistoryYaw.size() > DelayFrameNum)
		{
			DelayYaw = HistoryYaw.front();
			HistoryYaw.pop();
		}
		DelayYaw = HistoryYaw.front();
	}

private:
	void updateFront()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(getMidValYaw()));
		front.y = 0.0f;
		front.z = -cos(glm::radians(getMidValYaw()));
		Front = glm::normalize(front);
	}

};

#endif