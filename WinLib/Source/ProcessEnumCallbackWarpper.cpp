
#include "../Include/WinLib.h"

namespace wl {

	ProcessEnumCallbackWarpper::ProcessEnumCallbackWarpper() {

	}

	ProcessEnumCallbackWarpper::~ProcessEnumCallbackWarpper() {

	}

	void ProcessEnumCallbackWarpper::enumProcess(void) {
		mProcessIDList.clear();
		ProcessHelper::enumProcess(this);
	}

	const std::list<DWORD> & ProcessEnumCallbackWarpper::getProcessIDList(void) const {
		return mProcessIDList;
	}

	bool ProcessEnumCallbackWarpper::onEnumProcess(const DWORD processID) {
		mProcessIDList.push_back(processID);
		return true;
	}

} // namespace wl
