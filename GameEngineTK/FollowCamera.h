/// <summary>
/// ���@�Ǐ]�J����
/// </summary>
#pragma once

#include <windows.h>
#include <Keyboard.h>
#include "Camera.h"

class FollowCamera : public Camera
{
protected:
	// �^�[�Q�b�g�̍��W
	DirectX::SimpleMath::Vector3 m_target_pos;
	// �^�[�Q�b�g�̉�]�p
	float m_target_angle;
	// �L�[�{�[�h
	DirectX::Keyboard* m_keyboad;
	DirectX::Keyboard::KeyboardStateTracker m_keyboad_tracker;
	// fps�t���O
	bool m_isFlag;

public:
	// ���@�ƃJ�����̋���
	static const float m_camera_distance; 

public:
	FollowCamera(int width, int height);
	~FollowCamera();
	void update() override;

	/// <summary>
	/// set�֐�
	/// </summary>
	void set_target_pos(const DirectX::SimpleMath::Vector3& target_pos);
	void set_target_angle(const float& camera_distance);
	void set_keyboard(DirectX::Keyboard* keyboard);
};

