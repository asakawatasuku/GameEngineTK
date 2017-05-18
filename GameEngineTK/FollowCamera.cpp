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
	// �L�[�{�[�h�̎擾
	Keyboard::State keystate = m_keyboad->GetState();
	m_keyboad_tracker.Update(keystate);

	// C�L�[�������ꂽ��
	if (m_keyboad_tracker.IsKeyPressed(Keyboard::C) && m_isFlag == false)
	{
		m_isFlag = true;
	}
	else if (m_keyboad_tracker.IsKeyPressed(Keyboard::C) && m_isFlag == true)
	{
		m_isFlag = false;
	}

	// �J�����̎��_���W�A�Q�Ɠ_���W
	Vector3 eyepos, refpos;

	if (m_isFlag == false)
	{
		{// TPS�J����
			refpos = m_target_pos + Vector3(0, 1.0f, 0);
			// ���@�ƃJ�����̍���
			Vector3 camera_v(0, 0, m_camera_distance);
			// ���@�̌��ɉ�肱�ނ��߂̉�]�s��
			Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
			// �J�����ւ̃x�N�g������]
			camera_v = Vector3::TransformNormal(camera_v, rotmat);
			// �J�������W���v�Z
			eyepos = refpos + camera_v;
		}
	}
	else if (m_isFlag == true)
	{
		{// FPS�J����
			Vector3 position;
			// �J�������^�[�Q�b�g�̈ʒu��
			position = m_target_pos + Vector3(0, 1.0f, 0);
			// ���@�ƃJ�����̍���
			Vector3 camera_v(0, 0, -m_camera_distance);
			// ���@�̌��ɉ�肱�ނ��߂̉�]�s��
			Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
			// �J�����ւ̃x�N�g������]
			camera_v = Vector3::TransformNormal(camera_v, rotmat);

			eyepos = position + camera_v * 0.1f;
			refpos = position + camera_v;
		}
	}

	// ���_�����݈ʒu������
	eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;
	// �Q�Ɠ_�����݈ʒu������
	refpos = m_refpos + (refpos - m_refpos) * 0.2f;

	// �O�̍��W�Ɍ��݂̍��W���Z�b�g
	set_eyepos(eyepos);
	set_refpos(refpos);

	// ���N���X�̍X�V
	Camera::update();
}

// set�֐�
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
