
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

namespace {
	class glAsyncTaskThread : public glThread {
	public:
		glAsyncTaskThread() {
			mQuitFlag = false;
		}
	public:
		void postTask(glAsyncTask * task) {
			glMutexGuard mutexGuard(&mAsyncTaskListLock);
			if (task) {
				task->addRef();
				mAsyncTaskList.pushBack(task);
				mQuitFlag = false;
				if (!isAlready()) {
					create(true);
				}
			}
		}
		void quit(void) {
			glMutexGuard mutexGuard(&mAsyncTaskListLock);
			mQuitFlag = true;
			wait(1000);
			for (glList<glAsyncTask *>::glIterator iter = mAsyncTaskList.begin();
				iter.isValid();
				iter.moveNext()) {
				glAsyncTask * task = iter.getData();
				if (task) {
					task->release();
					task = 0;
				}
			}
			mAsyncTaskList.clear();
			destroy();
		}
	private:
		virtual void onThreadRun(void) override {
			while (!mQuitFlag) {
				glAsyncTask * task = popAsyncTask();
				if (task) {
					task->onAsyncTaskRun();
					task->release();
					task = 0;
				}
				else {
					sleep(1);
				}
			}
		}
	private:
		glAsyncTask * popAsyncTask(void) {
			glMutexGuard mutexGuard(&mAsyncTaskListLock);
			glList<glAsyncTask *>::glIterator iter = mAsyncTaskList.begin();
			if (iter.isValid()) {
				glAsyncTask * task = iter.getData();
				mAsyncTaskList.remove(iter);
				return task;
			}
			return 0;
		}
	private:
		glList<glAsyncTask *> mAsyncTaskList;
		glMutex mAsyncTaskListLock;
		bool mQuitFlag;
	};

	static glAsyncTaskThread gAsyncTaskThread;
}

void glAsyncTaskQueue::postTask(glAsyncTask * task) {
	gAsyncTaskThread.postTask(task);
}

void glAsyncTaskQueue::quit(void) {
	gAsyncTaskThread.quit();
}
