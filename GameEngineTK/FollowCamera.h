/// <summary>
/// 自機追従カメラ
/// </summary>
#pragma once

#include <windows.h>
#include <Keyboard.h>
#include "Camera.h"

class FollowCamera : public Camera
{
protected:
	// ターゲットの座標
	DirectX::SimpleMath::Vector3 m_target_pos;
	// ターゲットの回転角
	float m_target_angle;
	// キーボード
	DirectX::Keyboard* m_keyboad;
	DirectX::Keyboard::KeyboardStateTracker m_keyboad_tracker;
	// fpsフラグ
	bool m_isFlag;

public:
	// 自機とカメラの距離
	static const float m_camera_distance; 

public:
	FollowCamera(int width, int height);
	~FollowCamera();
	void update() override;

	/// <summary>
	/// set関数
	/// </summary>
	void set_target_pos(const DirectX::SimpleMath::Vector3& target_pos);
	void set_target_angle(const float& camera_distance);
	void set_keyboard(DirectX::Keyboard* keyboard);
};

