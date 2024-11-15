#include <Novice.h>
#include <math/Vector3.h>
#include <math/Matrix4x4.h>
#include <math/CalculateMath.h>

#include <math/Quaternion.h>

const char kWindowTitle[] = "LE2B_07_カミジ_トモユキ";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix);
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);
void QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
	Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };

	Quaternion identity = Identity();
	Quaternion conj = Conjugate(q1);
	Quaternion inv = Inverse(q1);
	Quaternion normal = Normalize(q1);
	Quaternion mul1 = Multiply(q1, q2);
	Quaternion mul2 = Multiply(q2, q1);
	float norm = Norm(q1);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		QuaternionScreenPrintf(0, 0, identity, ": Identity");
		QuaternionScreenPrintf(0, kRowHeight, conj, ": Conjugate");
		QuaternionScreenPrintf(0, kRowHeight * 2, inv, ": Inverse");
		QuaternionScreenPrintf(0, kRowHeight * 3, normal, ": Normalize");
		QuaternionScreenPrintf(0, kRowHeight * 4, mul1, ": Multiply(q1,q2)");
		QuaternionScreenPrintf(0, kRowHeight * 5, mul2, ": Multiply(q2,q1)");
		Novice::ScreenPrintf(0, kRowHeight * 6, "%.2f : Norm", norm);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.03f", matrix.m[row][column]);
		}
	}
}
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}
void QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", quaternion.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", quaternion.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", quaternion.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%.02f", quaternion.w);
	Novice::ScreenPrintf(x + kColumnWidth * 4, y, "%s", label);
}


