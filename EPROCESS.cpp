#include "Undoc.hpp"
#include "EPROCESS.h"

EX_PUSH_LOCK& EPROCESS::AddressCreationLock()
{
	return *CUndoc::GetInstance().AddressCreationLock(this);
}

EX_PUSH_LOCK& EPROCESS::WorkingSetMutex()
{
	return *CUndoc::GetInstance().WorkingSetMutex(this);
}

VM_FLAGS& EPROCESS::Flags()
{
	return *CUndoc::GetInstance().Flags(this);
}

void*& EPROCESS::VadRoot()
{
	return *CUndoc::GetInstance().VadRoot(this);
}
