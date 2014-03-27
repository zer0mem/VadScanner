#include "MMVAD_SHORT.h"
#include "Undoc.hpp"

ULONG_PTR& MMVAD_SHORT::StartingVpn()
{
	return *CUndoc::GetInstance().StartingVpn(this);
}

ULONG_PTR& MMVAD_SHORT::EndingVpn()
{
	return *CUndoc::GetInstance().EndingVpn(this);
}

ULONG_PTR& MMVAD_SHORT::Flags()
{
	return *CUndoc::GetInstance().Flags(this);
}

EX_PUSH_LOCK& MMVAD_SHORT::PushLock()
{
	return *CUndoc::GetInstance().PushLock(this);
}
