#include <Novice.h>
#include <math/Vector3.h>
#include <math/Matrix4x4.h>
#include <math/CalculateMath.h>

const char kWindowTitle[] = "LE2B_07_カミジ_トモユキ";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix);
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 axis = Normalize({ 1.0f,1.0f,1.0f });
	float angle = 0.44f;
	Matrix4x4 rotateMatrix = MakeRotateAxisAngle(axis, angle);
	
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

		MatrixScreenPrintf(0, 0, rotateMatrix);

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

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle)
{
	Vector3 normalizedAxis = axis;
	// 軸の正規化
	float length = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	if (length != 0.0f) {
		normalizedAxis.x /= length;
		normalizedAxis.y /= length;
		normalizedAxis.z /= length;
	}

	float c = std::cos(angle);
	float s = std::sin(angle);
	float oneMinusC = 1.0f - c;

	float x = normalizedAxis.x;
	float y = normalizedAxis.y;
	float z = normalizedAxis.z;

	Matrix4x4 rotationMatrix;

	rotationMatrix.m[0][0] = c + x * x * oneMinusC;
	rotationMatrix.m[0][1] = x * y * oneMinusC - z * s;
	rotationMatrix.m[0][2] = x * z * oneMinusC + y * s;
	rotationMatrix.m[0][3] = 0.0f;

	rotationMatrix.m[1][0] = y * x * oneMinusC + z * s;
	rotationMatrix.m[1][1] = c + y * y * oneMinusC;
	rotationMatrix.m[1][2] = y * z * oneMinusC - x * s;
	rotationMatrix.m[1][3] = 0.0f;

	rotationMatrix.m[2][0] = z * x * oneMinusC - y * s;
	rotationMatrix.m[2][1] = z * y * oneMinusC + x * s;
	rotationMatrix.m[2][2] = c + z * z * oneMinusC;
	rotationMatrix.m[2][3] = 0.0f;

	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;

	return rotationMatrix;
}
