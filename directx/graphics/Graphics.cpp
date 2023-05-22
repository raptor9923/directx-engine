#include "Graphics.h"
bool Graphics::InitializeDirectX(HWND hwnd)
{
	try
	{

	
	// get graphic adapter
	std::vector<AdapterData> adapters = AdapterReaders::GetAdapterData();
	if (adapters.size() < 1)
	{
		ErrorLogger::errorLog("NO DXGI Adapters found.");
		return false;
	}
	// set swap chain description
	DXGI_SWAP_CHAIN_DESC swapChainDescription;
	ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));
	// display description
	swapChainDescription.BufferDesc.Width = m_windowWidth;
	swapChainDescription.BufferDesc.Height = m_windowHeight;
	swapChainDescription.BufferDesc.RefreshRate.Numerator = 60;   
	swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   // data format (8  bits per channel and alpha)
	swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;   // unspecified pixel ordering
	swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;   // scaling of image 
	//sampler description
	swapChainDescription.SampleDesc.Count = 1;   // amount of samples
	swapChainDescription.SampleDesc.Quality = 0;  // lowest quality
	// swapchain settings
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // set the usage for rendering 
	swapChainDescription.BufferCount = 1;   // only one buffer
	swapChainDescription.OutputWindow = hwnd;   // handle to process window
	swapChainDescription.Windowed = true;   // if windowed
	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;   // swap buffer opitons
	swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;   // options for swap chain behavior (allow switching to full screen)
	HRESULT hr;
	//create swap chain with chosen graphics adapter
	hr = D3D11CreateDeviceAndSwapChain(adapters[0].GetAdapter(), D3D_DRIVER_TYPE_UNKNOWN, nullptr, NULL, nullptr, 0, D3D11_SDK_VERSION, &swapChainDescription, m_swapchain.GetAddressOf(), m_device.GetAddressOf(), nullptr, m_deviceContext.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to D3D11CreatDeviceAndSwapChain");
	//create back buffer for swapchain 
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	hr = m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), std::bit_cast<void**>(backBuffer.GetAddressOf()));   // (only one buffer so first argument is 0)
	COM_ERROR_IF_FAILED(hr, "Failed to GetBuffer");
	// create RenderTargetView for swapchain
	hr = m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to create Render Target view");
	// create depth buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc2d;
	ZeroMemory(&depthStencilDesc2d, sizeof(D3D11_TEXTURE2D_DESC));
	// size of window
	depthStencilDesc2d.Width = m_windowWidth;
	depthStencilDesc2d.Height = m_windowHeight;
	depthStencilDesc2d.MipLevels = 1;   // amount of additional down sampled versions of textures, (none)
	depthStencilDesc2d.ArraySize = 1;   // single buffer
	depthStencilDesc2d.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;   // format for depth buffer
	//sampler description
	depthStencilDesc2d.SampleDesc.Count = 1;
	depthStencilDesc2d.SampleDesc.Quality = 0;
	// depth buffer settings
	depthStencilDesc2d.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc2d.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc2d.CPUAccessFlags = 0;
	depthStencilDesc2d.MiscFlags = 0;
	hr = m_device->CreateTexture2D(&depthStencilDesc2d, nullptr, m_dephtStencilBuffer.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to create texture 2d for depth buffer");
	// create depth buffer view for graphic pipeline
	hr = m_device->CreateDepthStencilView(m_dephtStencilBuffer.Get(), nullptr, m_depthStencilView.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil view");
	// set render target and depth buffer views  for output merger
	m_deviceContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

	// set depth buffer settings
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = true;   // enable depth testing
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // allow writing to depth buffer
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;   //  pixel comparison function
	hr = m_device->CreateDepthStencilState(&depthStencilDesc, m_depthStencilState.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil state");
	//Create the Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(m_windowWidth);
	viewport.Height = static_cast<float>(m_windowHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	m_deviceContext->RSSetViewports(1, &viewport);

	// Set rasterizer settings
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;   // fill areas between verticies
	rasterizerDesc.CullMode = D3D11_CULL_BACK;   // draw triangles facing particular direction
	hr = m_device->CreateRasterizerState(&rasterizerDesc, m_rasterizerState.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to create rasterizer state");

	D3D11_RASTERIZER_DESC rasterizerCullFrontDesc;
	ZeroMemory(&rasterizerCullFrontDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerCullFrontDesc.FillMode = D3D11_FILL_SOLID;   // fill areas between verticies
	rasterizerCullFrontDesc.CullMode = D3D11_CULL_FRONT;   // draw triangles facing particular direction
	hr = m_device->CreateRasterizerState(&rasterizerCullFrontDesc, m_rasterizerStateCullFront.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to create rasterizer state (cull front)");
	//set blend state
	D3D11_BLEND_DESC blendDescription;
	ZeroMemory(&blendDescription, sizeof(D3D11_BLEND_DESC));
	D3D11_RENDER_TARGET_BLEND_DESC renderTargetBlendDescription;
	ZeroMemory(&renderTargetBlendDescription, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));
	renderTargetBlendDescription.BlendEnable = true;
	renderTargetBlendDescription.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	renderTargetBlendDescription.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	renderTargetBlendDescription.BlendOp = D3D11_BLEND_OP_ADD;
	renderTargetBlendDescription.SrcBlendAlpha = D3D11_BLEND_ONE;
	renderTargetBlendDescription.DestBlendAlpha = D3D11_BLEND_ZERO;
	renderTargetBlendDescription.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	renderTargetBlendDescription.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDescription.RenderTarget[0] = renderTargetBlendDescription;
	hr = m_device->CreateBlendState(&blendDescription, m_blendState.ReleaseAndGetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to create Blend state");
	//set font 
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_deviceContext.Get());
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_device.Get(), L"Data\\Fonts\\comic_sans_ms_16.spritefont");

	// set texture sampler settings
	D3D11_SAMPLER_DESC samplerStateDesc;
	ZeroMemory(&samplerStateDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;   // filter settings
	// texture coordinate settings
	samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;   // comparison sampler
	// level of detail settings
	samplerStateDesc.MinLOD = 0;
	samplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = m_device->CreateSamplerState(&samplerStateDesc, m_samplerState.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to create sampler state");
	}
	catch (COMException exception)
	{
		ErrorLogger::errorLog(exception);
		return false;
	}

	return true;
}

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
	m_windowWidth = width;
	m_windowHeight = height;
	m_timer.Start();
	if (!InitializeDirectX(hwnd))
		return false;
	if (!InitializeShaders())
		return false;

	if (!InitializeScene())
		return false;
	//Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(m_device.Get(), m_deviceContext.Get());
	ImGui::StyleColorsDark();
	return true;
}

void Graphics::RenderFrame()
{
	std::array<float, 4> backgroundColor{ 0.0f,0.0f,0.0f,1.0f }; 
	m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), backgroundColor.data());    // set whole screen to one color
	m_deviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);   // clear depth buffer
	m_deviceContext->IASetInputLayout(m_vertexShader.GetInputLayout());
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);   // interpret verticies as triangles
	m_deviceContext->RSSetState(m_rasterizerState.Get());   // set rasterizer options
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState.Get(), 0);  // set depth buffer settings
	m_deviceContext->OMSetBlendState(m_blendState.Get(), nullptr,0xFFFFFFFF );   // set blend state
	m_deviceContext->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());   // set sampler settings
	m_deviceContext->VSSetShader(m_vertexShader.GetShader(), nullptr, 0);   // set vertex shader
	m_deviceContext->PSSetShader(m_pixelShader.GetShader(), nullptr, 0);   // set pixel shader
	
	UINT offset = 0;

	static float alpha{ 1.0f };
	//grass
	static float translation[3] = { 0,0,0.0f };
	DirectX::XMMATRIX world = DirectX::XMMatrixScaling(5.0f, 5.0f, 5.0f) * DirectX::XMMatrixTranslation(translation[0], translation[1], translation[2]);
	m_CB_VS_VertexShader.AccessDataMembers()->mat = (world * m_camera.GetViewMatrix()) * m_camera.GetProjectionMatrix();
	m_CB_VS_VertexShader.AccessDataMembers()->mat = DirectX::XMMatrixTranspose(m_CB_VS_VertexShader.AccessDataMembers()->mat);
	//set constant buffer
	if (!m_CB_VS_VertexShader.ApplyChanges())
		return;
	m_deviceContext->VSSetConstantBuffers(0, 1, m_CB_VS_VertexShader.GetAddressOf());


	m_CB_PS_PixelShader.AccessDataMembers()->alpha = alpha;
	m_CB_PS_PixelShader.ApplyChanges();
	m_deviceContext->PSSetConstantBuffers(0, 1, m_CB_PS_PixelShader.GetAddressOf());
	//draw square
	m_deviceContext->PSSetShaderResources(0, 1, m_Texture1.GetAddressOf());   // get texture
	m_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), m_vertexBuffer.StridePtr(), &offset);   // get verticies
	m_deviceContext->IASetIndexBuffer(m_indicesBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);   // get verticies list
	m_deviceContext->DrawIndexed(m_indicesBuffer.BufferSize(), 0, 0);    // draw indexed verticies


	//draw text
	static int fpsCounter = 0;
	fpsCounter += 1;
	static std::wstring fpsString= L"Fps: 0";
	if (m_timer.GetMilisecondsElapsed() > 1000.0)
	{
		m_timer.Restart();
		fpsString = std::format(L"Fps: {}", fpsCounter);
		fpsCounter = 0;
	}
	m_spriteBatch->Begin();
	m_spriteFont->DrawString(m_spriteBatch.get(), fpsString.c_str(), DirectX::XMFLOAT2(0, 0), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
	m_spriteBatch->End();
	//ImGui
	static int counter = 0;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Test");
	ImGui::DragFloat("ALPHA", &alpha, 0.05f, 0.0f, 1.0f);
	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	//swap buffer to screen
	m_swapchain->Present(1, 0);
}

bool Graphics::InitializeScene()
{
	try
	{

	
	// set verticies
	std::array  v =
	{
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f), //FRONT Bottom Left -0
		Vertex(-0.5f,  0.5f, -0.5f, 0.0f, 0.0f), //FRONT Top Left -1
		Vertex(0.5f,  0.5f, -0.5f, 1.0f, 0.0f), //FRONT Top Right -2
		Vertex(0.5f, -0.5f, -0.5f, 1.0f, 1.0f), //FRONT Bottom Right -3
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 1.0f), //BACK Bottom Left -4
		Vertex(-0.5f,  0.5f, 0.5f, 0.0f, 0.0f), //BACK Top Left -5
		Vertex(0.5f,  0.5f, 0.5f, 1.0f, 0.0f), //BACK Top Right -6
		Vertex(0.5f, -0.5f, 0.5f, 1.0f, 1.0f), //BACK Bottom Right -7
	};

	//set verticies list
	std::vector<DWORD> indices =
	{
		0,1,2,
		0,2,3,
		4,7,6,
		4,6,5,
		3,2,6,
		3,6,7,
		4,5,1,
		4,1,0,
		1,5,6,
		1,6,2,
		0,3,7,
		0,7,4,
	};
	//vertex buffer
	HRESULT hr = m_vertexBuffer.Initialize(m_device.Get(), v.data(), static_cast<UINT>(v.size()));
	COM_ERROR_IF_FAILED(hr, "Failed to create vertex Buffer");
	
	//index buffer
	hr = m_indicesBuffer.Initialize(m_device.Get(), indices.data(), static_cast<UINT>(indices.size()));
	COM_ERROR_IF_FAILED(hr, "Failed to create index Buffer");
	//load texture
	hr = DirectX::CreateWICTextureFromFile(m_device.Get(), L"data\\Textures\\seamless_pavement.jpg", nullptr, m_Texture1.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to load texture");
	// constant buffers
	hr = m_CB_VS_VertexShader.Initialize(m_device.Get(), m_deviceContext.Get());
	COM_ERROR_IF_FAILED(hr, "Failed to create constant Buffer");
	hr = m_CB_PS_PixelShader.Initialize(m_device.Get(), m_deviceContext.Get());
	COM_ERROR_IF_FAILED(hr, "Failed to create constant Buffer");
	// set camera
	m_camera.SetPosition(0.0f, 0.0f, -2.0f);
	m_camera.setProjectionValues(90.0f, static_cast<float>(m_windowWidth) / static_cast<float>(m_windowHeight), 0.1f, 1000.0f);
	}
	catch (COMException& exception)
	{
		ErrorLogger::errorLog(exception);
		return false;
	}
	return true;
}

bool Graphics::InitializeShaders()
{
	// get path to exe file
	std::wstring path;
	path.resize(MAX_PATH);
	if (!GetModuleFileNameW(nullptr, &path[0], MAX_PATH))
	{
		ErrorLogger::errorLog("Failed to process path");
	}
	// get rid of exe file name
	size_t lastSlash;
	lastSlash = path.find_last_of(L'\\');
	path.erase(path.begin() + lastSlash, path.end());
	// add shader files to path
	std::wstring vertexShaderPath = path + L"\\VertexShader.cso";
	std::wstring pixelShaderPath = path + L"\\PixelShader.cso";
	// set input layout
	std::array <D3D11_INPUT_ELEMENT_DESC, 2> layout =
	{
		{
			{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0},   // vertex coordinates
			{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0}   // texture coordinates
		}
	};
	auto numElements = static_cast<UINT>(layout.size());
	// initialize shaders
	if (!m_vertexShader.Initialize(m_device, vertexShaderPath, layout.data(), numElements))
		return false;
	if (!m_pixelShader.Initialize(m_device, pixelShaderPath))
		return false;
	return true;
}

Camera* Graphics::AccesCamera()
{
	return &m_camera;
}