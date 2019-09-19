
#include "../GameLibInclude/glTimerSystem.h"
#include "../GameLibInclude/glThread.h"
#include "../GameLibInclude/glMutex.h"
#include "../GameLibInclude/glMutexGuard.h"
#include "../GameLibInclude/glList.h"
#include "../GameLibInclude/glTimer.h"
#include "../GameLibInclude/glWaitableTimer.h"

namespace {
	class glTimerThread : public glThread {
	private:
		class glTimerInfo {
		public:
			bool operator == (const glTimerInfo & other) const {
				return mTimer == other.mTimer &&
					mTimerID == other.mTimerID &&
					mDuration == other.mDuration &&
					mElapse == other.mElapse;
			}
		public:
			glTimer * mTimer;
			int mTimerID;
			int mDuration;
			int mElapse;
		};
	public:
		glTimerThread() {
			mQuitFlag = false;
		}
	public:
		bool registerTimer(glTimer * timer, const int timerID, const int duration) {
			glMutexGuard mutexGuard(&mTimerInfoListLock);
			glTimerInfo timerInfo = { 0 };
			if (timer) {
				timerInfo.mTimer = timer;
				timerInfo.mTimerID = timerID;
				timerInfo.mDuration = duration;
				mTimerInfoList.pushBack(timerInfo);
				mQuitFlag = false;
				if (!mWaitableTimer.isAlready()) {
					if (!mWaitableTimer.create()) {
						return false;
					}
				}
				if (!isAlready()) {
					if (!create(true)) {
						return false;
					}
				}
				return true;
			}
			return false;
		}
		bool unregisterTimer(glTimer * timer, const int timerID) {
			bool ret = false;
			glMutexGuard mutexGuard(&mTimerInfoListLock);
			if (timer) {
				glList<glTimerInfo>::glIterator iter = mTimerInfoList.begin();
				while (iter.isValid()) {
					const glTimerInfo & timerInfo = iter.getData();
					if (timer == timerInfo.mTimer && timerID == timerInfo.mTimerID) {
						mTimerInfoList.remove(iter);
						ret = true;
						continue;
					}
					iter.moveNext();
				}
			}
			return ret;
		}
		bool unregisterTimer(glTimer * timer) {
			bool ret = false;
			glMutexGuard mutexGuard(&mTimerInfoListLock);
			if (timer) {
				glList<glTimerInfo>::glIterator iter = mTimerInfoList.begin();
				while (iter.isValid()) {
					const glTimerInfo & timerInfo = iter.getData();
					if (timer == timerInfo.mTimer) {
						mTimerInfoList.remove(iter);
						ret = true;
						continue;
					}
					iter.moveNext();
				}
			}
			return ret;
		}
		void quit(void) {
			glMutexGuard mutexGuard(&mTimerInfoListLock);
			mQuitFlag = true;
			mWaitableTimer.destroy();
			wait(1000);
			mTimerInfoList.clear();
			destroy();
		}
	private:
		virtual void onThreadRun(void) override {
			while (!mQuitFlag) {
				if (!mWaitableTimer.wait(10)) {
					break;
				}
				glMutexGuard mutexGuard(&mTimerInfoListLock);
				for (glList<glTimerInfo>::glIterator iter = mTimerInfoList.begin();
					iter.isValid();
					iter.moveNext()) {
					glTimerInfo & timerInfo = iter.getDataRef();
					if (timerInfo.mTimer) {
						timerInfo.mElapse += 10;
						if (timerInfo.mElapse >= timerInfo.mDuration) {
							timerInfo.mElapse -= timerInfo.mDuration;
							timerInfo.mTimer->onTimer(timerInfo.mTimerID);
						}
					}
				}
			}
		}
	private:
		glWaitableTimer mWaitableTimer;
		glList<glTimerInfo> mTimerInfoList;
		glMutex mTimerInfoListLock;
		bool mQuitFlag;
	};

	static glTimerThread gTimerThread;
}

bool glTimerSystem::registerTimer(glTimer * timer, const int timerID, const int duration) {
	return gTimerThread.registerTimer(timer, timerID, duration);
}

bool glTimerSystem::unregisterTimer(glTimer * timer, const int timerID) {
	return gTimerThread.unregisterTimer(timer, timerID);
}

bool glTimerSystem::unregisterTimer(glTimer * timer) {
	return gTimerThread.unregisterTimer(timer);
}

void glTimerSystem::quit(void) {
	gTimerThread.quit();
}
