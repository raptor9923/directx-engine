#include"Camera.h"
using namespace DirectX;

void Camera::UpdateViewMatrix()   // calculate and update camera view
{
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(m_rot.x, m_rot.y, m_rot.z);
	XMVECTOR camTarget = XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, camRotationMatrix);
	camTarget += m_posVector;
	XMVECTOR upDirection = XMVector3TransformCoord(DEFAULT_UP_VECTOR, camRotationMatrix);
	m_viewMatrix = XMMatrixLookAtLH(m_posVector, camTarget, upDirection);
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, m_rot.y, 0.0f);
	m_vecForward= XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	m_vecBack = XMVector3TransformCoord(DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	m_vecLeft = XMVector3TransformCoord(DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	m_vecRight = XMVector3TransformCoord(DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
}
Camera::Camera()
{
	UpdateViewMatrix();
}
void Camera::setProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	float fovRadians = (fovDegrees / 360.0f) * XM_2PI;
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}
const XMMATRIX& Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}
const XMMATRIX& Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}
const XMVECTOR& Camera::GetPositionVector() const
{
	return m_posVector;
}
const XMFLOAT3& Camera::GetPositionFloat3() const
{
	return m_pos;
}
const XMVECTOR& Camera::GetRotationVector() const
{
	return m_rotVector;
}
const XMFLOAT3& Camera::GetRotationFloat3() const
{
	return m_rot;
}
void Camera::SetPosition(const XMVECTOR& pos)
{
	XMStoreFloat3(&m_pos, pos);
	m_posVector = pos;
	UpdateViewMatrix();
}
void Camera::SetPosition(float x, float y, float z)
{
	m_pos = XMFLOAT3(x, y, z);
	m_posVector = XMLoadFloat3(&m_pos);
	UpdateViewMatrix();
}
void Camera::AdjustPosition(const XMVECTOR& pos)
{
	m_posVector += pos;
	XMStoreFloat3(&m_pos, m_posVector);
	UpdateViewMatrix();
}
void Camera::AdjustPosition(float x, float y, float z)
{
	m_pos.x += x;
	m_pos.y += y;
	m_pos.z += z;
	m_posVector = XMLoadFloat3(&m_pos);
	UpdateViewMatrix();
}
void Camera::SetRotation(const XMVECTOR& rot)
{
	m_rotVector = rot;
	XMStoreFloat3(&m_rot, rot);
	UpdateViewMatrix();
}
void Camera::SetRotation(float x, float y, float z)
{
	m_rot = XMFLOAT3(x, y, z);
	m_rotVector = XMLoadFloat3(&m_rot);
	UpdateViewMatrix();
}
void Camera::AdjustRotation(const XMVECTOR& rot)
{
	m_rotVector += rot;
	XMStoreFloat3(&m_rot, m_rotVector);
	UpdateViewMatrix();
}
void Camera::AdjustRotation(float x, float y, float z)
{
	m_rot.x += x;
	m_rot.y += y;
	m_rot.z += z;
	if (m_rot.x > XM_2PI / 4.0f)
		m_rot.x = XM_2PI / 4.0f;
	if (m_rot.x < -XM_2PI / 4.0f)
		m_rot.x = -XM_2PI / 4.0f;
	m_rotVector = XMLoadFloat3(&m_rot);
	UpdateViewMatrix();
}
void Camera::SetLookAtPos(XMFLOAT3 lookAtPos)
{
	//check if not the same position as camera
	if (lookAtPos.x == m_pos.x && lookAtPos.y == m_pos.y && lookAtPos.z == m_pos.z)
		return;
	// calculate vector
	lookAtPos.x = m_pos.x - lookAtPos.x;
	lookAtPos.y = m_pos.y - lookAtPos.y;
	lookAtPos.z = m_pos.z - lookAtPos.z;
	//calculate pitch
	float pitch{ 0.0f };
	if (lookAtPos.y != 0.0f)
	{
		auto distance = (sqrtf(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z));
		pitch = (atanf(lookAtPos.y / distance));
	}
	//calculate yaw
	float yaw{ 0.0f };
	if (lookAtPos.x != 0.0f)
	{
		yaw = (atanf(lookAtPos.x / lookAtPos.z));
	}
	//rotate camera
	SetRotation(pitch, yaw, 0.0f);
}

const DirectX::XMVECTOR& Camera::GetForwardVector() const
{
	return m_vecForward;
}
const DirectX::XMVECTOR& Camera::GetBackwardVector() const
{
	return m_vecBack;
}
const DirectX::XMVECTOR& Camera::GetLeftVector() const
{
	return m_vecLeft;
}
const DirectX::XMVECTOR& Camera::GetRightVector() const
{
	return m_vecRight;
}