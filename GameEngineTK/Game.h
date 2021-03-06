//
// Game.h
//

#pragma once

#include "StepTimer.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include <Keyboard.h>

#include "DebugCamera.h"
#include "FollowCamera.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

private:
	// プリミティブバッチ
	//std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_primitiveBatch;

	// ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	
	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	
	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_proj;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debagCamera;

	// エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> m_factory;
	
	// 天球モデル
	std::unique_ptr<DirectX::Model> m_modelSkydome;
	// 地面モデル
	std::unique_ptr<DirectX::Model> m_modelGround;
	// ボールモデル
	std::unique_ptr<DirectX::Model> m_modelBall;
	// ティーポットモデル
	std::unique_ptr<DirectX::Model> m_modelTeapot;
	// 頭モデル
	std::unique_ptr<DirectX::Model> m_modelhead;

	// ティーポットのワールド行列
	DirectX::SimpleMath::Matrix m_worldTeapot[20];
		
	// 平行移動
	DirectX::SimpleMath::Matrix m_transmat[20];

	// 球のワールド行列
	//DirectX::SimpleMath::Matrix m_worldBall;
	//DirectX::SimpleMath::Matrix m_worldBall[20];

	// 地面の行列
	//DirectX::SimpleMath::Matrix m_worldGround[200][200];
	DirectX::SimpleMath::Matrix m_worldhead;

	// キーボードの取得
	std::unique_ptr<DirectX::Keyboard> m_keyboard;

	// 頭の座標
	DirectX::SimpleMath::Vector3 m_head_pos;

	float m_cnt;
	float m_angule;
	float m_distance;
	float m_val;
	float m__cnt;
	DirectX::SimpleMath::Vector3 m_startPosition[20];
	DirectX::SimpleMath::Vector3 m_targetPosition;
	DirectX::SimpleMath::Vector3 m_pos;
	float m_time;

	std::unique_ptr<FollowCamera> m_camera;

public:
	DirectX::SimpleMath::Vector3 Lerp(DirectX::SimpleMath::Vector3 startPosition, DirectX::SimpleMath::Vector3 targetPosition, float t);

};