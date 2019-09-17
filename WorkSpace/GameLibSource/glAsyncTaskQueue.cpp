
#include "../GameLib.h"

namespace {
	static glList<glAsyncTask *> gAsyncTaskList;
	static glMutex gAsyncTaskListLock;
	static bool gQuitFlag = false;

	class glAsyncTaskThread : public glThread {
	public:
		virtual void onThreadRun(void) override {
			while (!gQuitFlag) {
				glAsyncTask * task = popAsyncTask();
				if (task) {
					task->onAsyncTaskRun();
					task->release();
					task = 0;
				}
			}
		}
	private:
		glAsyncTask * popAsyncTask(void) {
			glMutexGuard mutexGuard(&gAsyncTaskListLock);
			glList<glAsyncTask *>::glIterator iter = gAsyncTaskList.begin();
			if (iter.isValid()) {
				glAsyncTask * task = iter.getData();
				gAsyncTaskList.remove(iter);
				return task;
			}
			return 0;
		}
	};

	static glAsyncTaskThread gAsyncTaskThread;
}

void glAsyncTaskQueue::postTask(glAsyncTask * task) {
	glMutexGuard mutexGuard(&gAsyncTaskListLock);
	if (task) {
		task->addRef();
		gAsyncTaskList.pushBack(task);
		gQuitFlag = false;
		if (!gAsyncTaskThread.isAlready()) {
			gAsyncTaskThread.create(true);
		}
	}
}

void glAsyncTaskQueue::quit(void) {
	glMutexGuard mutexGuard(&gAsyncTaskListLock);
	gQuitFlag = true;
	gAsyncTaskThread.destroy(-1);
	for (glList<glAsyncTask *>::glIterator iter = gAsyncTaskList.begin();
		iter.isValid();
		iter.moveNext()) {
		glAsyncTask * task = iter.getData();
		if (task) {
			task->release();
			task = 0;
		}
	}
	gAsyncTaskList.clear();
}
