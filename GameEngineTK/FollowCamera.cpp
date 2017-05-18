#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float FollowCamera::m_camera_distance = 5.0f;

FollowCamera::FollowCamera(int width, int height)
	:Camera(width,height)
	, m_keyboad(nullptr)
	, m_target_pos(0,0,0)
	, m_target_angle(0)
	, m_isFlag(false)
{
}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::update()
{
	// キーボードの取得
	Keyboard::State keystate = m_keyboad->GetState();
	m_keyboad_tracker.Update(keystate);

	// Cキーが押されたら
	if (m_keyboad_tracker.IsKeyPressed(Keyboard::C) && m_isFlag == false)
	{
		m_isFlag = true;
	}
	else if (m_keyboad_tracker.IsKeyPressed(Keyboard::C) && m_isFlag == true)
	{
		m_isFlag = false;
	}

	// カメラの視点座標、参照点座標
	Vector3 eyepos, refpos;

	if (m_isFlag == false)
	{
		{// TPSカメラ
			refpos = m_target_pos + Vector3(0, 1.0f, 0);
			// 自機とカメラの差分
			Vector3 camera_v(0, 0, m_camera_distance);
			// 自機の後ろに回りこむための回転行列
			Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
			// カメラへのベクトルを回転
			camera_v = Vector3::TransformNormal(camera_v, rotmat);
			// カメラ座標を計算
			eyepos = refpos + camera_v;
		}
	}
	else if (m_isFlag == true)
	{
		{// FPSカメラ
			Vector3 position;
			// カメラをターゲットの位置に
			position = m_target_pos + Vector3(0, 1.0f, 0);
			// 自機とカメラの差分
			Vector3 camera_v(0, 0, -m_camera_distance);
			// 自機の後ろに回りこむための回転行列
			Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
			// カメラへのベクトルを回転
			camera_v = Vector3::TransformNormal(camera_v, rotmat);

			eyepos = position + camera_v * 0.1f;
			refpos = position + camera_v;
		}
	}

	// 視点を現在位置から補間
	eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;
	// 参照点を現在位置から補間
	refpos = m_refpos + (refpos - m_refpos) * 0.2f;

	// 前の座標に現在の座標をセット
	set_eyepos(eyepos);
	set_refpos(refpos);

	// 基底クラスの更新
	Camera::update();
}

// set関数
void FollowCamera::set_target_pos(const DirectX::SimpleMath::Vector3& target_pos)
{
	m_target_pos = target_pos;
}
void FollowCamera::set_target_angle(const float& target_angle)
{
	m_target_angle = target_angle;
}

void FollowCamera::set_keyboard( DirectX::Keyboard* keyboard)
{
	m_keyboad = keyboard;
}
