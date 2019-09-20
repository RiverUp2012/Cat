
#pragma once

class glFile;
class glMemFile;
class glGameState;

//
// @brief ���ļ��ж�ȡ����
//
template <typename _U>
bool glReadFile(glFile & file, _U & value) {
	return file.read(&value, sizeof(_U));
}

//
// @brief ���ڴ��ļ���ȡ����
//
template <typename _U>
bool glReadMemFile(glMemFile & file, _U & value) {
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
// @brief ������д���ڴ��ļ�
//
template <typename _U>
bool glWriteMemFile(glMemFile & file, const _U & value) {
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
