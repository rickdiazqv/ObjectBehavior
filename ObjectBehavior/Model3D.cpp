#include "Model3D.h"

Model3D::Model3D(const char* const path) : Plane() {
	// �R�c���f���̓ǂݍ���
	modelHandle = MV1LoadModel(path);

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.1f, 1000.0f);

	//(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -100), VGet(0.0f, 10.0f, 0.0f));

	// �R�c���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
	attachIndex = MV1AttachAnim(modelHandle, 1, -1, FALSE);

	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);

	// �Đ����Ԃ̏�����
	playTime = 0.0f;
}

void Model3D::update() {
	Plane::update();

	// �Đ����Ԃ�i�߂�
	playTime += .4f;
	time += 1.f;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (playTime >= totalTime) {
		playTime = 0.0f;
	}

	if (time >= 360.f) {
		time = .0f;
	}

	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);

	SetCameraPositionAndTarget_UpVecY(
		VGet(
			40.f * sin(time * float(DX_PI) / 180.f), 10.f,
			40.f * sin((time - 90.f) * float(DX_PI) / 180.f)),
		VGet(0.0f, 10.0f, 0.0f));
}

void Model3D::draw() {
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);
}
