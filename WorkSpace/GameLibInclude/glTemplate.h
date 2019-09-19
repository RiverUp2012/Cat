
#pragma once

class glFile;
class glGameState;

//
// @brief ���ļ��ж�ȡ����
//
template <typename _U>
bool glReadFile(glFile & file, _U & value) {
	return file.read(&value, sizeof(_U));
}

//
// @brief ������д���ļ�
//
template <typename _U>
bool glWriteFile(glFile & file, const _U & value) {
	return file.write(&value, sizeof(_U));
}

//
// @brief ѹ���µ���Ϸ״̬
//
template <typename _U>
void glPushNewGameState(void) {
	glEngine * engine = glEngine::get();
	if (engine) {
		glGameState * gameState = new _U();
		if (gameState) {
			engine->pushGameState(gameState);
			gameState->release();
			gameState = 0;
		}
	}
}
