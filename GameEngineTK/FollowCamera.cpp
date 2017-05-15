#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float FollowCamera::m_camera_distance = 5.0f;

FollowCamera::FollowCamera(int width, int height)
	:Camera(width,height)
{

}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::update()
{
	// �J�����̎��_���W�A�Q�Ɠ_���W
	Vector3 eyepos, refpos;

	refpos = m_target_pos + Vector3(0, 2, 0);

	// ���@�ƃJ�����̍���
	Vector3 camera_v(0, 0, m_camera_distance);
	Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
	camera_v = Vector3::TransformNormal(camera_v, rotmat);
	eyepos = refpos + camera_v;

	set_eyepos(eyepos);
	set_refpos(refpos);

	// ���N���X�̍X�V
	Camera::update();
}

void FollowCamera::set_target_pos(const DirectX::SimpleMath::Vector3& target_pos)
{
	m_target_pos = target_pos;
}

void FollowCamera::set_target_angle(const float& target_angle)
{
	m_target_angle = target_angle;
}