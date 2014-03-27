/**
 * @file MMVAD_SHORT.hpp
 * @author created by: Peter Hlavaty
 */

#ifndef __MMVAD_SHORT_H__
#define __MMVAD_SHORT_H__

#include "UndocHolder.h"

struct MMVAD_SHORT :
	private CUndocHolder
{
	ULONG_PTR& StartingVpn();
	ULONG_PTR& EndingVpn();
	ULONG_PTR& Flags();
	EX_PUSH_LOCK& PushLock();
};

#endif //__MMVAD_SHORT_H__
