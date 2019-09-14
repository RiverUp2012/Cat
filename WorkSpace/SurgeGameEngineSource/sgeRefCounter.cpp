
#include "../SurgeGameEngine.h"

sgeRefCounter::sgeRefCounter()
{
	mRefCount = 1;
}

sgeRefCounter::~sgeRefCounter()
{

}

void sgeRefCounter::addRef(void)
{
	++mRefCount;
}

bool sgeRefCounter::release(void)
{
	--mRefCount;

	if (mRefCount <= 0)
	{
		delete this;
		return true;
	}

	return false;
}

int sgeRefCounter::getRefCount(void) const
{
	return mRefCount;
}
