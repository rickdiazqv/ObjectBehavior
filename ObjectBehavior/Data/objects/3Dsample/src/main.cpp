#include <DxLib.h>

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK );

	//3D���f���̓ǂݍ���
	int ModelHandle = MV1LoadModel( "dat/Lat���~�N/Lat���~�NVer2.3_Normal.pmd" ) ;

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar( 0.1f, 1000.0f ) ;

	//(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY( VGet( 0, 10, -20 ), VGet( 0.0f, 10.0f, 0.0f ) ) ;

	while(!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen()){

		// �R�c���f���̕`��
		MV1DrawModel( ModelHandle ) ;

	}

	DxLib_End();
	return 0;
} 