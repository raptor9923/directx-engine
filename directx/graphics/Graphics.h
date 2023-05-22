#pragma once
#include"AdapterReader.h"
#include"Shaders.h"
#include<libloaderapi.h>
#include<iostream>
#include"Vertex.h"
#include<SpriteBatch.h>
#include<SpriteFont.h>
#include<WICTextureLoader.h>
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"ConstantBuferTypes.h"
#include"ConstantBuffer.h"
#include "Camera.h"
#include <array>
#include "../Timer.h"
#include"ImGui/imgui.h"
#include"ImGui/imgui_impl_win32.h"
#include"ImGui/imgui_impl_dx11.h"

class Graphics   // rendering class
{
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerStateCullFront;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_dephtStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture1;
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
	VertexBuffer<Vertex> m_vertexBuffer;
	IndexBuffer m_indicesBuffer;
	ConstantBuffer<CB_VS_vertexshader> m_CB_VS_VertexShader;
	ConstantBuffer<CB_PS_pixelshader> m_CB_PS_PixelShader;
	VertexShader m_vertexShader;
	PixelShader m_pixelShader;
	Camera m_camera;
	Timer m_timer;
	int m_windowWidth;
	int m_windowHeight;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	bool InitializeDirectX(HWND hwnd);
	bool InitializeShaders();
	bool InitializeScene();
public:
	bool Initialize(HWND hwnd, int width, int height);
	Camera* AccesCamera();
	void RenderFrame();
};
