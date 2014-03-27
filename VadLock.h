/**
 * @file VadHelper.h
 * @author created by: Peter Hlavaty
 */

#ifndef __VADHELPER_H__
#define __VADHELPER_H__

#include "ntifs.h"

#include "Vad.h"
#include "Lock.hpp"

//------------------------------------------------------------------
// ****************** VAD_ROOT ADDRESS SPACE LOCK ******************
//------------------------------------------------------------------ 

template<class WORKER>
class CVADLock
{
public:
	CVADLock() :
		m_addressSpaceLock(&reinterpret_cast<EPROCESS*>(PsGetCurrentProcess())->AddressCreationLock()),
		m_workingSetLock(&reinterpret_cast<EPROCESS*>(PsGetCurrentProcess())->WorkingSetMutex()),
		m_locked(false)
	{
		ETHREAD* ethread = reinterpret_cast<ETHREAD*>(PsGetCurrentThread());
		ethread->SameThreadApcFlags().OwnsProcessAddressSpaceExclusive = TRUE;
		m_addressSpaceLock.Lock();

		EPROCESS* eprocess = reinterpret_cast<EPROCESS*>(PsGetCurrentProcess());
		if (eprocess->Flags().VmDeleted)
			return;

		m_locked = true;
		ethread->SameThreadApcFlags().OwnsProcessWorkingSetExclusive = TRUE;
		m_workingSetLock.Lock();
	}

	~CVADLock()
	{
		ETHREAD* ethread = reinterpret_cast<ETHREAD*>(PsGetCurrentThread());
		if (m_locked)
		{
			m_workingSetLock.Unlock();
			ethread->SameThreadApcFlags().OwnsProcessWorkingSetExclusive = FALSE;
		}

		m_addressSpaceLock.Unlock();
		ethread->SameThreadApcFlags().OwnsProcessAddressSpaceExclusive = FALSE;
	}

	__checkReturn 
	bool IsLocked()
	{
		return m_locked;
	}

protected:
	bool m_locked;

	WORKER m_addressSpaceLock;
	CExclusiveLockWorker m_workingSetLock;
};

class CVADScanLock :
	public CVADLock<CSharedLockWorker>
{
public:
	CVADScanLock() :
		CVADLock()
	{
	}
};

class CVADWriteLock :
	public CVADLock<CExclusiveLockWorker>
{
public:
	CVADWriteLock() :
		CVADLock()
	{
	}
};

#endif //__VADHELPER_H__
