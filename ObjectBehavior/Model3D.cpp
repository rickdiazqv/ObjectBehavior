#include "Model3D.h"

Model3D::Model3D(const char* path) : Plane() {
    // ３Ｄモデルの読み込み
    modelHandle = MV1LoadModel(path);

    //奥行0.1〜1000までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 1000.0f);

    //(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
    SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));

    // ３Ｄモデルの1番目のアニメーションをアタッチする
    attachIndex = MV1AttachAnim(modelHandle, 1, -1, FALSE);

    // アタッチしたアニメーションの総再生時間を取得する
    totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);

    // 再生時間の初期化
    playTime = 0.0f;
}

void Model3D::update() {
	Plane::update();

    // 再生時間を進める
    playTime += 0.2f;

    // 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
    if (playTime >= totalTime) {
        playTime = 0.0f;
    }

    // 再生時間をセットする
    MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);
}

void Model3D::draw() {
    // ３Ｄモデルの描画
    MV1DrawModel(modelHandle);
}
