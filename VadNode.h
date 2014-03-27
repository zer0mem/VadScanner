/**
 * @file VADWalker.h
 * @author created by: Peter Hlavaty
 */

#ifndef __VADWALKER_H__
#define __VADWALKER_H__

#include "ntifs.h"
#include "Range.h"
#include "Lock.hpp"

#include "MMVAD_SHORT.h"

#include "VadLock.h"
#include "DummeVad.hpp"
#include "MMVAD_SHORT.hpp"
#include <boost/noncopyable.hpp>

//------------------------------------------------------------
// ****************** VAD_NODE MEMORY RANGE ****************** 
//------------------------------------------------------------

class CVadNode :
	public boost::noncopyable,
	private CSharedLockWorker
{
public:
	CVadNode(
		__in CMMVadShort& vadNode
		) : m_vad(&vadNode),
			CSharedLockWorker(&(vadNode->PushLock()))
	{
		Lock();
	}

	~CVadNode()
	{
		Unlock();
	}

	const MMVAD_SHORT* operator->() const
	{
		return *m_vad;
	}

	CVadNode* operator++()
	{
		CDummyVad dummy_vad;

		CVADScanLock lock;
		if (lock.IsLocked())
		{
			dummy_vad.RelinkToVadRoot(*m_vad);

			VadTree::iterator it = dummy_vad->begin();
			++it;
			
			CMMVadShort& vad = *it;

			Unlock();
			m_tLock = &vad->PushLock();
			Lock();

			m_vad = &vad;
		}
		return this;
	}

	void* Begin()
	{
		return EXPAND((*m_vad)->StartingVpn());
	}
	void* End()
	{
		return EXPAND((*m_vad)->EndingVpn()) - 1;
	}

private:
	CMMVadShort* m_vad;
};

#endif //__VADWALKER_H__
