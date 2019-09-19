
#include "../GameLibInclude/glSingleAppInstanceChecker.h"

glSingleAppInstanceChecker::glSingleAppInstanceChecker() {

}

glSingleAppInstanceChecker::~glSingleAppInstanceChecker() {
	mEvent.destroy();
}

bool glSingleAppInstanceChecker::checkSingleAppInstanceW(const wchar_t * appInstanceName) {
	if (appInstanceName) {
		// 尝试打开事件，若事件已存在，说明已经有应用程序实例在运行
		if (mEvent.openW(appInstanceName)) {
			return true;
		}
		// 创建事件
		if (!mEvent.createW(appInstanceName, true, false)) {
			return true;
		}
	}
	return false;
}
