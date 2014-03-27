/**
 * @file ETHREAD.hpp
 * @author created by: Peter Hlavaty
*/

#ifndef __ETHREAD_H__
#define __ETHREAD_H__

#include "UndocHolder.h"
#include "Undoc.hpp"
#include "Vad.h"

struct ETHREAD :
	private CUndocHolder
{
	SAME_THREAD_APC_FLAGS& SameThreadApcFlags();
};

#endif //__ETHREAD_H__
