
#pragma once

class glFile;
class glGameState;

//
// @brief 从文件中读取数据
//
template <typename _U>
bool glReadFile(glFile & file, _U & value) {
	return file.read(&value, sizeof(_U));
}

//
// @brief 将数据写入文件
//
template <typename _U>
bool glWriteFile(glFile & file, const _U & value) {
	return file.write(&value, sizeof(_U));
}

//
// @brief 压入新的游戏状态
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
