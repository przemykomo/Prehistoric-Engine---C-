#ifndef CAMERA_H
#define CAMERA_H

#include "engine/prehistoric/common/framework/CameraInput.h"

static const Vector3f yAxis(0, 1, 0);

class Camera
{
public:
	Camera(float moveAmt = 0.1f, float rotAmt = 0.8f, float mouseSensitivity = 0.8f, float fov = 70.0f, const Vector3f& position = Vector3f());
	Camera(const Vector3f& position, float fov);

	virtual ~Camera();

	void LogStage() const;
	void SetProjection(const float& fov, const float& width, const float& height);

    void AddCameraInput(CameraInput* input) { inputs.push_back(input); }

	void Input(Window* window, float delta);
	void Move(const Vector3f& dir, const float& amount);
	void RotateX(const float& angle);
	void RotateY(const float& angle);

	Vector3f GetLeft() const { return forward.cross(up).normalize(); }
	Vector3f GetRight() const { return up.cross(forward).normalize(); }

	inline Vector3f GetPosition() const { return position; }
	inline Vector3f GetForward() const { return forward; }
	inline Vector3f GetUp() const { return up; }

	inline Matrix4f GetViewMatrix() const { return viewMatrix; }
	inline Matrix4f GetProjectionMatrix() const { return projectionMatrix; }
	inline Matrix4f GetViewProjectionMatrix() const { return viewProjectionMatrix; }

    inline void SetSpeedControl(InputData data) { this->speedControl = data; }
private:
    std::vector<CameraInput*> inputs;
    InputData speedControl;

	Vector3f position;
	Vector3f previousPosition;
	Vector3f forward;
	Vector3f previousForward;
	Vector3f up;
    float movAmt;
    float rotAmt;
    Matrix4f viewMatrix;
    Matrix4f projectionMatrix;
    Matrix4f viewProjectionMatrix;
    Matrix4f previousViewMatrix;
    Matrix4f previousViewProjectionMatrix;
    bool cameraMoved;
    bool cameraRotated;

    float width;
    float height;
    float fovY;

    float rotYstride;
    float rotYamt;
    float rotYcounter;
    bool rotYInitiated = false;
    float rotXstride;
    float rotXamt;
    float rotXcounter;
    bool rotXInitiated = false;
    float mouseSensitivity;

    Vector4f* frustumPlanes;
    Vector3f* frustumCorners;
};

#include "engine/prehistoric/core/math/MathT.h"

#endif