#include "Undoc.hpp"
#include "ETHREAD.h"

SAME_THREAD_APC_FLAGS& ETHREAD::SameThreadApcFlags()
{
	return *CUndoc::GetInstance().SameThreadApcFlags(this);
}
