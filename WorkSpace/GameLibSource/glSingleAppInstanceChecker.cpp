
#include "../GameLibInclude/glSingleAppInstanceChecker.h"

glSingleAppInstanceChecker::glSingleAppInstanceChecker() {

}

glSingleAppInstanceChecker::~glSingleAppInstanceChecker() {
	mEvent.destroy();
}

bool glSingleAppInstanceChecker::checkSingleAppInstanceW(const wchar_t * appInstanceName) {
	if (appInstanceName) {
		// ���Դ��¼������¼��Ѵ��ڣ�˵���Ѿ���Ӧ�ó���ʵ��������
		if (mEvent.openW(appInstanceName)) {
			return true;
		}
		// �����¼�
		if (!mEvent.createW(appInstanceName, true, false)) {
			return true;
		}
	}
	return false;
}
