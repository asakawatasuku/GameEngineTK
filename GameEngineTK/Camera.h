/// <summary>
/// カメラを制御するクラス
/// </summary>
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

class Camera
{
protected:
	// 視点座標
	DirectX::SimpleMath::Vector3 m_eyepos;
	// 参照点
	DirectX::SimpleMath::Vector3 m_refpos;
	// 上方向ベクトル
	DirectX::SimpleMath::Vector3 m_upvec;
	// 垂直方向視野角
	float m_fovy;
	// アスペクト比
	float m_aspect;
	// ニアクリップ
	float m_nearclip;
	// ファークリップ
	float m_farclip;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_proj;

public:
	Camera(int width,int height);
	virtual ~Camera();
	void update();

	/// <summary>
	/// get関数
	/// </summary>
	const DirectX::SimpleMath::Matrix& get_view();
	const DirectX::SimpleMath::Matrix& get_proj();

	/// <summary>
	/// set関数
	/// </summary>
	void set_eyepos(const DirectX::SimpleMath::Vector3& eyepos);
	void set_refpos(const DirectX::SimpleMath::Vector3& refpos);
	void set_upvec(const DirectX::SimpleMath::Vector3& refpos);
	void set_fovy(const float& fovy);
	void set_aspct(const float& aspect);
	void set_nearclip(const float& nearclip);
	void set_farclip(const float& farclip);
};
