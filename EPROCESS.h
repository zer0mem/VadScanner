/**
 * @file EPROCESS.hpp
 * @author created by: Peter Hlavaty
 */

#ifndef __EPROCESS_H__
#define __EPROCESS_H__

#include "UndocHolder.h"
#include "Undoc.hpp"
#include "Vad.h"
//#include "VadNode.h"
//#include "MMVAD_SHORT.hpp"

struct EPROCESS :
	private CUndocHolder
{
	EX_PUSH_LOCK& AddressCreationLock();
	EX_PUSH_LOCK& WorkingSetMutex();
	VM_FLAGS& Flags();
	void*& VadRoot();
};

#endif //__EPROCESS_H__
