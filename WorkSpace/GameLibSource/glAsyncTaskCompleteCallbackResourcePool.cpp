
#include "../GameLib.h"

namespace {
	static glResourcePool<glAsyncTaskCompleteCallback *> gResourcePool;
}

bool glAsyncTaskCompleteCallbackResourcePool::insertResource(
	glAsyncTaskCompleteCallback * const & resource,
	int & id) {
	return gResourcePool.insertResource(resource, id);
}

bool glAsyncTaskCompleteCallbackResourcePool::getResource(
	const int id,
	glAsyncTaskCompleteCallback * & resource,
	const bool markResourceUnuse) {
	return gResourcePool.getResource(id, resource, markResourceUnuse);
}

bool glAsyncTaskCompleteCallbackResourcePool::markResourceUnuse(
	glAsyncTaskCompleteCallback * const & resource) {
	return gResourcePool.markResourceUnuse(resource);
}
