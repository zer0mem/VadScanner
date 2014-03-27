/**
* @file Undoc.hpp
* @author created by: Peter Hlavaty
*/

#ifndef __UNDOC_H__
#define __UNDOC_H__

#include "ntifs.h"
#include "Singleton.hpp"

#include "MMVAD_SHORT.h"
#include "ETHREAD.h"
#include "EPROCESS.h"

struct OS_CONSTANTS
{
	size_t MMVAD_SHORT_StartingVpn;
	size_t MMVAD_SHORT_EndingVpn;
	size_t MMVAD_SHORT_Flags;//MMVAD_SHORT.u1
	size_t MMVAD_SHORT_PushLock;

	size_t ETHREAD_SameThreadApcFlags;

	size_t EPROCESS_AddressCreationLock;
	size_t EPROCESS_WorkingSetMutex;//EPROCESS.Vm.WorkingSetMutex
	size_t EPROCESS_Flags;//EPROCESS.Flags, included VmDeleted, ...
	size_t EPROCESS_VadRoot;
};

class CUndoc :
	public CSingleton<CUndoc>
{
	static CUndoc m_instance;
	CUndoc() :
		CSingleton(m_instance)
	{
	}
#define UNDOC_MEMBER(addr, type, member_offset) reinterpret_cast<type*>(reinterpret_cast<ULONG_PTR>(addr) + (member_offset))
public:
	ULONG_PTR* StartingVpn(
		__in const MMVAD_SHORT* vad
		)
	{
		return UNDOC_MEMBER(vad, ULONG_PTR, m_sConsts.MMVAD_SHORT_StartingVpn);
	}

	ULONG_PTR* EndingVpn(
		__in MMVAD_SHORT const* vad
		)
	{
		return UNDOC_MEMBER(vad, ULONG_PTR, m_sConsts.MMVAD_SHORT_EndingVpn);
	}

	ULONG_PTR* Flags(
		__in MMVAD_SHORT const* vad
		)
	{
		return UNDOC_MEMBER(vad, ULONG_PTR, m_sConsts.MMVAD_SHORT_Flags);
	}

	EX_PUSH_LOCK* PushLock(
		__in MMVAD_SHORT const* vad
		)
	{
		return UNDOC_MEMBER(vad, EX_PUSH_LOCK, m_sConsts.MMVAD_SHORT_PushLock);
	}

	SAME_THREAD_APC_FLAGS* SameThreadApcFlags(
		__in ETHREAD const* ethread
		)
	{
		return UNDOC_MEMBER(ethread, SAME_THREAD_APC_FLAGS, m_sConsts.ETHREAD_SameThreadApcFlags);
	}

	EX_PUSH_LOCK* AddressCreationLock(
		__in EPROCESS* eproc
		)
	{
		return UNDOC_MEMBER(eproc, EX_PUSH_LOCK, m_sConsts.EPROCESS_AddressCreationLock);
	}

	EX_PUSH_LOCK* WorkingSetMutex(
		__in EPROCESS const* eproc
		)
	{
		return UNDOC_MEMBER(eproc, EX_PUSH_LOCK, m_sConsts.EPROCESS_WorkingSetMutex);
	}

	VM_FLAGS* Flags(
		__in EPROCESS const* eproc
		)
	{
		return UNDOC_MEMBER(eproc, VM_FLAGS, m_sConsts.EPROCESS_Flags);
	}

	/*CMMVadShort**/void** VadRoot(
		__in EPROCESS const* eproc
		)
	{
		return UNDOC_MEMBER(eproc, /*CMMVadShort*/void*, m_sConsts.EPROCESS_VadRoot);
	}

private:
	static OS_CONSTANTS m_sConsts;
};

__declspec(selectany) CUndoc CUndoc::m_instance;
__declspec(selectany) OS_CONSTANTS CUndoc::m_sConsts = { 0x018, 0x020, 0x028, 0x038, 0x450, 0x218, 0x390, 0x438, 0x448 }; //win7 x64, sp?

#endif //__UNDOC_H__
