/// <summary>
/// �J�����𐧌䂷��N���X
/// </summary>
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

class Camera
{
protected:
	// ���_���W
	DirectX::SimpleMath::Vector3 m_eyepos;
	// �Q�Ɠ_
	DirectX::SimpleMath::Vector3 m_refpos;
	// ������x�N�g��
	DirectX::SimpleMath::Vector3 m_upvec;
	// ������������p
	float m_fovy;
	// �A�X�y�N�g��
	float m_aspect;
	// �j�A�N���b�v
	float m_nearclip;
	// �t�@�[�N���b�v
	float m_farclip;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_proj;

public:
	Camera(int width,int height);
	virtual ~Camera();
	void update();

	/// <summary>
	/// get�֐�
	/// </summary>
	const DirectX::SimpleMath::Matrix& get_view();
	const DirectX::SimpleMath::Matrix& get_proj();

	/// <summary>
	/// set�֐�
	/// </summary>
	void set_eyepos(const DirectX::SimpleMath::Vector3& eyepos);
	void set_refpos(const DirectX::SimpleMath::Vector3& refpos);
	void set_upvec(const DirectX::SimpleMath::Vector3& refpos);
	void set_fovy(const float& fovy);
	void set_aspct(const float& aspect);
	void set_nearclip(const float& nearclip);
	void set_farclip(const float& farclip);
};
