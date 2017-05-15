#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera(int width, int height)
{
	// 初期化処理
	// カメラの視点座標
	m_eyepos = Vector3(0, 0, 5);
	// カメラの注視点(参照点)
	m_refpos = Vector3(0, 0, 0);
	// カメラの上方向ベクトル
	m_upvec = Vector3(0, 1, 0);
	m_upvec.Normalize();

	// 垂直方向視野
	m_fovy = XMConvertToRadians(60.0f);
	// アスペクト比(縦横の比率)
	m_aspect = (float)width / height;
	// ニアクリップ(手前の表示限界)
	m_nearclip = 1.0f;
	// ファークリップ(奥の表示限界)
	m_farclip = 1000.0f;

	// ビュー行列の生成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	// プロジェクション行列の作成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovy, m_aspect, m_nearclip, m_farclip);
}

Camera::~Camera()
{
}

// 更新
void Camera::update()
{
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovy, m_aspect, m_nearclip, m_farclip);
}

// get関数
const DirectX::SimpleMath::Matrix& Camera::get_view()
{
	return m_view;
}
const DirectX::SimpleMath::Matrix& Camera::get_proj()
{
	return m_proj;
}

// set関数
void Camera::set_eyepos(const DirectX::SimpleMath::Vector3& eyepos)
{
	m_eyepos = eyepos;
}
void Camera::set_refpos(const DirectX::SimpleMath::Vector3& refpos)
{
	m_refpos = refpos;
}
void Camera::set_upvec(const DirectX::SimpleMath::Vector3& upvec)
{
	m_upvec = upvec;
}
void Camera::set_fovy(const float& fovy)
{
	m_fovy = fovy;
}
void Camera::set_aspct(const float& aspect)
{
	m_aspect = aspect;
}
void Camera::set_nearclip(const float& nearclip)
{
	m_nearclip = nearclip;
}
void Camera::set_farclip(const float& farclip)
{
	m_farclip = farclip;
}