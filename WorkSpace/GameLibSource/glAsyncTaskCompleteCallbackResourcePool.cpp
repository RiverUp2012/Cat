
#include "../GameLib.h"

namespace {
	static glResourcePool<glAsyncTaskCompleteCallback *> gResourcePool;
	static glMutex gResourcePoolLock;
}

bool glAsyncTaskCompleteCallbackResourcePool::insertResource(
	glAsyncTaskCompleteCallback * const & resource,
	int & id) {
	glMutexGuard mutexGuard(&gResourcePoolLock);
	return gResourcePool.insertResource(resource, id);
}

bool glAsyncTaskCompleteCallbackResourcePool::getResource(
	const int id,
	glAsyncTaskCompleteCallback * & resource,
	const bool markResourceUnuse) {
	glMutexGuard mutexGuard(&gResourcePoolLock);
	return gResourcePool.getResource(id, resource, markResourceUnuse);
}

bool glAsyncTaskCompleteCallbackResourcePool::markResourceUnuse(
	glAsyncTaskCompleteCallback * const & resource) {
	glMutexGuard mutexGuard(&gResourcePoolLock);
	return gResourcePool.markResourceUnuseByID(resource);
}
