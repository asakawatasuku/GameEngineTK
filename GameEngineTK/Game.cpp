//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include <time.h>



extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;


Game::Game() :
    m_window(0),
    m_outputWidth(800),
    m_outputHeight(600),
    m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_window = window;
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateDevice();

    CreateResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */


	// ����������

	srand(static_cast<unsigned int>(time(nullptr)));
	float x;
	float z;

	m_cnt = 0;
	m__cnt = 0;
	m_angule = 0;

	// �v���~�e�B�u�o�b�`
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionNormal>>(m_d3dContext.Get());

	// �x�[�V�b�N�G�t�F�N�g
	m_basicEffect = std::make_unique<BasicEffect>(m_d3dDevice.Get());

	m_basicEffect->SetProjection(XMMatrixOrthographicOffCenterRH(0, m_outputWidth, m_outputHeight, 0, 0, 1));
	m_basicEffect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// ���̓��C�A�E�g
	m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());

	// �R�����X�e�[�g�̐���
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	// �f�o�b�O�J��������
	m_debagCamera = std::make_unique<DebugCamera>(m_outputHeight, m_outputWidth);

	m_keyboard = std::make_unique<DirectX::Keyboard>();

	// �G�t�F�N�g�t�@�N�g������
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	// �e�N�X�`���̃p�X���w��
	m_factory->SetDirectory(L"Resources");

	// ���f���̐���
	m_modelSkydome = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources\\skydome.cmo", *m_factory);
	// ���f���̐���
	m_modelGround = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources\\ground200m.cmo", *m_factory);
	// ���f���̐���
	m_modelBall = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources\\ball.cmo", *m_factory);
	// ���f���̐���
	m_modelTeapot = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources\\teapot.cmo", *m_factory);
	// ���f���̐���
	m_modelhead = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources\\head.cmo", *m_factory);
	
	m_val = 0;
	m_time = 10;
	m_targetPosition = Vector3(0, 0, 0);
			
	//for (int i = 0; i < 20; i++)
	//{
	//	XMConvertToRadians(m_angule);
	//	m_angule = rand() % 360;
	//	m_distance = rand() % 100;
	//	x = cosf(m_angule) * m_distance;
	//	z = sinf(m_angule) * m_distance;	
	//	// �X�P�[�����O
	//	Matrix scalemat = Matrix::CreateScale(1.0f);
	//	// ���[��
	//	Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0));
	//	// �s�b�`
	//	Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0));
	//	// ���[
	//	Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(0));
	//	// ��]�s��̍���
	//	Matrix rotmat = (rotmatz * rotmatx * rotmaty);
	//	// ���s�ړ�
	//	m_transmat[i] = Matrix::CreateTranslation(x, 0.0f, z);
	//	m_startPosition[i] = Vector3(x, 0.0f, z);
	//	// ���[���h�s��̍���(SRT)
	//	m_worldTeapot[i] = scalemat * rotmat * m_transmat[i];
	//}

}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;


	// �}�C�t���[������

	// �f�o�b�O�J�����̍X�V
	m_debagCamera->Update();

	m_cnt += 0.036f;

	//for (int i = 0; i < 20; i++)
	//{
	//	if (i < 10)
	//	{			
	//		// ���[��
	//		Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(36 * i) + cnt);
	//		// �s�b�`
	//		Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0));
	//		// ���[
	//		Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(0));
	//		// ��]�s��̍���
	//		Matrix rotmat = (rotmatz * rotmatx * rotmaty);
	//		// ���s�ړ�
	//		Matrix transmat = Matrix::CreateTranslation(20.0f, 0.0f, 0.0f);
	//		// ���[���h�s��̍���(SRT)
	//		m_worldBall[i] = scalemat * transmat * rotmat;
	//	}
	//	else
	//	{
	//		// ���[��
	//		Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(36 * i) - cnt);
	//		// �s�b�`
	//		Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0));
	//		// ���[
	//		Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(0));
	//		// ��]�s��̍���
	//		Matrix rotmat = (rotmatz * rotmatx * rotmaty);
	//		// ���s�ړ�
	//		Matrix transmat = Matrix::CreateTranslation(40.0f, 0.0f, 0.0f);
	//		// ���[���h�s��̍���(SRT)
	//		m_worldBall[i] = scalemat * transmat * rotmat;
	//	}
	//}

	//for (i = 0; i < 200; i++)
	//{
	//	for (j = 0; j < 200; j++)
	//	{
	//		// ���[��
	//		Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0));
	//		// �s�b�`
	//		Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0));
	//		// ���[
	//		Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(0));
	//		// ��]�s��̍���
	//		Matrix rotmat = (rotmatz * rotmatx * rotmaty);
	//		// ���s�ړ�
	//		Matrix transmat = Matrix::CreateTranslation(1.0f*i-100, 0.0f, 1.0f*j-100);
	//		// ���[���h�s��̍���(SRT)
	//		m_worldGround[i][j] = scalemat *rotmat * transmat;
	//	}
	//}		
	
	//// �X�P�[�����O
	//for (int i = 0; i < 20; i++)
	//{	
	//	m__cnt += 5.0f/360.0f;
	//	m_val = sinf(XMConvertToRadians((m__cnt)+1.0f)*4.0f)+1.0f;
	//	m_val += 1.0f;
	//	// �X�P�[�����O
	//	Matrix scalemat = Matrix::CreateScale(m_val);
	//	// ���[��
	//	Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0));
	//	// �s�b�`
	//	Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0));
	//	// ���[
 //		Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(36*2)*m_cnt);
	//	// ��]�s��̍���
	//	Matrix rotmat = (rotmatz * rotmatx * rotmaty);
	//	// ���[���h�s��̍���(SRT)
	//	m_worldTeapot[i] = scalemat * rotmat * m_transmat[i];
	//	
	//}
	//for (int i = 0; i < 20; i++)
	//{
	//	m_pos = Lerp(m_startPosition[i], m_targetPosition, m_time);
	//	// �X�P�[�����O
	//	Matrix scalemat = Matrix::CreateScale(1.0f);
	//	// ���[��
	//	Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0));
	//	// �s�b�`
	//	Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0));
	//	// ���[
	//	Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(0));
	//	// ��]�s��̍���
	//	Matrix rotmat = (rotmatz * rotmatx * rotmaty);
	//	// ���s�ړ�
	//	m_transmat[i] = Matrix::CreateTranslation(m_pos);
	//	// ���[���h�s��̍���(SRT)
	//	m_worldTeapot[i] = scalemat * m_transmat[i] * rotmat;
	//}


	Keyboard::State kb = m_keyboard->GetState();


	// ���񏈗�
	if (kb.A)
	{
		m_angule += 0.01f;
	}
	if (kb.D)
	{
		m_angule -= 0.01f;
	}

	// �O�i����
	if (kb.W)
	{
		Vector3 moveV(0, 0, -0.1f);
		// �ړ��x�N�g������]
		moveV = Vector3::TransformNormal(moveV, m_worldhead);
		m_head_pos += moveV;
	}	
	// ��ޏ���
	if (kb.S)
	{
		Vector3 moveV(0, 0, -0.1f);
		// �ړ��x�N�g������]
		moveV = Vector3::TransformNormal(moveV, m_worldhead);
		m_head_pos -= moveV;
	}

	{// ���@�̃��[���h�s����쐬
		// ��]
		Matrix rotmat = Matrix::CreateRotationY(m_angule);
		// ���s�ړ�
		Matrix transmat = Matrix::CreateTranslation(m_head_pos);
		// ���s�ړ��s������[���h�s���
		m_worldhead = rotmat * transmat;
	}
}

// Draws the scene.
void Game::Render()
{

	uint16_t indices[] =
	{
		0,1,2,
		2,1,3,
	};

	VertexPositionNormal vertices[] =
	{
		{ Vector3(-1.0f,+1.0f,0.0f),Vector3(0.0f,0.0f,+1.0f) },
		{ Vector3(-1.0f,-1.0f,0.0f),Vector3(0.0f,0.0f,+1.0f) },
		{ Vector3(+1.0f,+1.0f,0.0f),Vector3(0.0f,0.0f,+1.0f) },
		{ Vector3(+1.0f,-1.0f,0.0f),Vector3(0.0f,0.0f,+1.0f) },
	};

    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    // TODO: Add your rendering code here.

	// �`�揈��
	// �r���[�s����쐬
	//m_view = Matrix::CreateLookAt(Vector3(2.f, 2.f, 2.f), /*�J�������_*/
	//	Vector3::Zero /*�J�����Q�Ɠ_*/,
	//	Vector3::UnitY/*Vector3(0, 0, 0)*//*������x�N�g��*/);

	// debagcamera����r���[�s����擾
	m_view = m_debagCamera->GetCameraMatrix();

	// �v���W�F�N�V�����s����쐬
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f /*����p(�㉺����)*/,
		float(m_outputWidth) / float(m_outputHeight) /*�A�X�y�N�g��*/, 
		0.1f /*�j�A�N���b�v*/,
		500.f /*�t�@�[�N���b�v*/);

	m_basicEffect->SetView(m_view);
	m_basicEffect->SetProjection(m_proj);


	m_d3dContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	m_d3dContext->OMSetDepthStencilState(m_states->DepthNone(), 0);
	m_d3dContext->RSSetState(m_states->CullNone());

	m_basicEffect->Apply(m_d3dContext.Get());
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	// ���f���̕`��
	// �V��
	m_modelSkydome->Draw(m_d3dContext.Get(), *m_states.get(), m_world, m_view, m_proj);
	
	// �n��
	/*for (i = 0; i < 200; i++)
	{
		for (j = 0; j < 200; j++)
		{
			m_modelGround->Draw(m_d3dContext.Get(), *m_states.get(), m_worldGround[i][j], m_view, m_proj);
		}
	}*/
	m_modelGround->Draw(m_d3dContext.Get(), *m_states.get(), Matrix::Identity, m_view, m_proj);
	
	// �{�[��
	//for (int i = 0; i < 20; i++)
	//{
	//	m_modelBall->Draw(m_d3dContext.Get(), *m_states.get(), m_worldBall[i], m_view, m_proj);
	//}


	// �e�B�[�|�b�g
	/*for (int i = 0; i < 20; i++)
	{
		m_modelTeapot->Draw(m_d3dContext.Get(), *m_states.get(), m_worldTeapot[i], m_view, m_proj);
	}*/

	// ��
	m_modelhead->Draw(m_d3dContext.Get(), *m_states.get(), m_worldhead, m_view, m_proj);
	


	m_primitiveBatch->Begin();
	//m_primitiveBatch->DrawLine(VertexPositionColor(Vector3(0,0,0),Color(1,1,0)), VertexPositionColor(Vector3(800, 600, 0), Color(1, 1, 1)));
	m_primitiveBatch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indices, 6, vertices, 4);

	// 3D
	//VertexPositionColor v1(Vector3(0.f, 0.5f, 0.5f), Colors::Yellow);
	//VertexPositionColor v2(Vector3(0.5f, -0.5f, 0.5f), Colors::Yellow);
	//VertexPositionColor v3(Vector3(-0.5f, -0.5f, 0.5f), Colors::Yellow);
	
	// 2D
	//VertexPositionColor v1(Vector3(400.f, 150.f, 0.f), Colors::Red);
	//VertexPositionColor v2(Vector3(600.f, 450.f, 0.f), Colors::Blue);
	//VertexPositionColor v3(Vector3(200.f, 450.f, 0.f), Colors::Green);
	
	//m_primitiveBatch->DrawTriangle(v1, v2, v3);

	m_primitiveBatch->End();

    Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it.
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}

Vector3 Game::Lerp(Vector3 startPosition, Vector3 targetPosition, float t)
{
	Vector3 lerpPosition = Vector3(0,0,0);

	lerpPosition = (1 - t) * startPosition + t * targetPosition;

	return lerpPosition;
}