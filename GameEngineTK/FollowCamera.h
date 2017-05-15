/// <summary>
/// ���@�Ǐ]�J����
/// </summary>
#pragma once

#include "Camera.h"

class FollowCamera : public Camera
{
protected:
	// �^�[�Q�b�g�̍��W
	DirectX::SimpleMath::Vector3 m_target_pos;
	// �^�[�Q�b�g�̉�]�p
	float m_target_angle;

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
};

