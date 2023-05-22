#pragma once
#include <DirectXMath.h>

class Camera   //
{
	// camera data
	DirectX::XMFLOAT3 m_pos{ DirectX::XMFLOAT3(0.0f,0.0f,0.0f) };
	DirectX::XMFLOAT3 m_rot{ DirectX::XMFLOAT3(0.0f,0.0f,0.0f) };
	DirectX::XMVECTOR m_posVector{ DirectX::XMLoadFloat3(&m_pos) };
	DirectX::XMVECTOR m_rotVector{ DirectX::XMLoadFloat3(&m_rot) };
	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMMATRIX m_projectionMatrix;

	DirectX::XMVECTOR m_vecForward;
	DirectX::XMVECTOR m_vecLeft;
	DirectX::XMVECTOR m_vecRight;
	DirectX::XMVECTOR m_vecBack;

	//constant vectors
	const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR{ DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) };
	const DirectX::XMVECTOR DEFAULT_UP_VECTOR{ DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
	const DirectX::XMVECTOR DEFAULT_BACKWARD_VECTOR{ DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f) };
	const DirectX::XMVECTOR DEFAULT_LEFT_VECTOR{ DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f) };
	const DirectX::XMVECTOR DEFAULT_RIGHT_VECTOR{ DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) };
	void UpdateViewMatrix();

public:

	Camera();
	void setProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);
	const DirectX::XMMATRIX& GetViewMatrix() const;
	const DirectX::XMMATRIX& GetProjectionMatrix() const;
	const DirectX::XMVECTOR& GetPositionVector() const;
	const DirectX::XMFLOAT3& GetPositionFloat3() const;
	const DirectX::XMVECTOR& GetRotationVector() const;
	const DirectX::XMFLOAT3& GetRotationFloat3() const;
	const DirectX::XMVECTOR& GetForwardVector() const;
	const DirectX::XMVECTOR& GetBackwardVector() const;
	const DirectX::XMVECTOR& GetLeftVector() const;
	const DirectX::XMVECTOR& GetRightVector() const;
	void SetPosition(const DirectX::XMVECTOR& pos);
	void SetPosition(float x, float y, float z);
	void AdjustPosition(const DirectX::XMVECTOR& pos);
	void AdjustPosition(float x, float y, float z);
	void SetRotation(const DirectX::XMVECTOR& pos);
	void SetRotation(float x, float y, float z);
	void AdjustRotation(const DirectX::XMVECTOR& pos);
	void AdjustRotation(float x, float y, float z);
	void SetLookAtPos(DirectX::XMFLOAT3 lookAtPos);
};