#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera(int width, int height)
{
	// ����������
	// �J�����̎��_���W
	m_eyepos = Vector3(0, 0, 5);
	// �J�����̒����_(�Q�Ɠ_)
	m_refpos = Vector3(0, 0, 0);
	// �J�����̏�����x�N�g��
	m_upvec = Vector3(0, 1, 0);
	m_upvec.Normalize();

	// ������������
	m_fovy = XMConvertToRadians(60.0f);
	// �A�X�y�N�g��(�c���̔䗦)
	m_aspect = (float)width / height;
	// �j�A�N���b�v(��O�̕\�����E)
	m_nearclip = 1.0f;
	// �t�@�[�N���b�v(���̕\�����E)
	m_farclip = 1000.0f;

	// �r���[�s��̐���
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	// �v���W�F�N�V�����s��̍쐬
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovy, m_aspect, m_nearclip, m_farclip);
}

Camera::~Camera()
{
}

// �X�V
void Camera::update()
{
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovy, m_aspect, m_nearclip, m_farclip);
}

// get�֐�
const DirectX::SimpleMath::Matrix& Camera::get_view()
{
	return m_view;
}
const DirectX::SimpleMath::Matrix& Camera::get_proj()
{
	return m_proj;
}

// set�֐�
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