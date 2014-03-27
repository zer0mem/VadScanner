/**
 * @file VadScanner.hpp
 * @author created by: Peter Hlavaty
 */

#ifndef __VADSCANNER_H__
#define __VADSCANNER_H__

#include "Lock.hpp"
#include "VadNode.h"
#include "VadLock.h"
#include "MMVAD_SHORT.hpp"
#include "DummeVad.hpp"

#include <boost/intrusive/avltree.hpp>
#include <boost/noncopyable.hpp>

#include <memory>

class CVAdScanner :
	public boost::noncopyable
{
public:
	static
	__checkReturn
	bool Contains(
		__in const CRange<void*>& mem
		)
	{
		CDummyVad dummy_vad;

		CVADLock<CSharedLockWorker> lock;
		if (!lock.IsLocked())
			return false;

		if (!dummy_vad.RelinkToVadRoot())
			return false;

		VadTree::iterator it = dummy_vad->find(mem, CMMVadShortCmp());
		return it != dummy_vad->end();
	}

	static
	__checkReturn
	bool GetMemory(
		__in const CRange<void*>& mem,
		__inout CRange<void*>* out
		)
	{
		CDummyVad dummy_vad;

		CVADLock<CSharedLockWorker> lock;
		if (!lock.IsLocked())
			return false;

		if (!dummy_vad.RelinkToVadRoot())
			return false;

		VadTree::iterator it = dummy_vad->find(mem, CMMVadShortCmp());
		if (dummy_vad->end() == it)
			return false;

		MMVAD_SHORT* vad = *it;
		out->Begin() = EXPAND(vad->StartingVpn());
		out->End() = EXPAND(vad->EndingVpn()) - 1;
		return true;
	}
	
	static
	__checkReturn
	bool Find(
		__in const CRange<void*>& mem,
		__inout std::shared_ptr<CVadNode>* out
		)
	{
		CDummyVad dummy_vad;

		CVadNode* out_vadnode = nullptr;

		{
			CVADLock<CSharedLockWorker> lock;
			if (!lock.IsLocked())
				return false;

			if (!dummy_vad.RelinkToVadRoot())
				return false;

			VadTree::iterator it = dummy_vad->find(mem, CMMVadShortCmp());
			if (dummy_vad->end() == it)
				return false;
			MMVAD_SHORT* c_mmvad = *it;
			out_vadnode = new CVadNode(*it);
		}

		//outside of spinlock playing with std::shared_ptr
		if (!out_vadnode)
			return false;

		*out = std::shared_ptr<CVadNode>(out_vadnode);
		return true;
	}
};

#endif //__VADSCANNER_H__
