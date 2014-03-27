/**
 * @file DummeVad.hpp
 * @author created by: Peter Hlavaty
 */

#ifndef __DUMMEVAD_H__
#define __DUMMEVAD_H__

#include "MMVAD_SHORT.hpp"

#include <boost/intrusive/avltree.hpp>
#include <boost/noncopyable.hpp>

#include "EPROCESS.h"

class CDummyVad :
	public boost::noncopyable
{
public:
	CDummyVad()
	{
		CMMVadShort* dummy_vad = reinterpret_cast<CMMVadShort*>(&m_dummyStack);
		MMVAD_SHORT* vs = *dummy_vad;
		vs->StartingVpn() = NULL;
		vs->EndingVpn() = NULL;
		//set our decoy
		m_vadTree.insert_unique(*reinterpret_cast<CMMVadShort*>(m_dummyStack));
	}

	~CDummyVad()
	{
		CMMVadShort* dummy_vad = reinterpret_cast<CMMVadShort*>(&m_dummyStack);
		dummy_vad->MMADDRESS_NODE.right_ = nullptr;
		dummy_vad->MMADDRESS_NODE.parent_ = nullptr;
	}

	VadTree* operator->()
	{
		return &m_vadTree;
	}

	__checkReturn
	void RelinkToVadRoot(
		__in const CMMVadShort& vad_root
		)
	{
		CMMVadShort* dummy_vad = reinterpret_cast<CMMVadShort*>(&m_dummyStack);
		dummy_vad->MMADDRESS_NODE.right_ = vad_root.MMADDRESS_NODE.right_;
		dummy_vad->MMADDRESS_NODE.parent_ = vad_root.MMADDRESS_NODE.parent_;
	}

	__checkReturn
	bool RelinkToVadRoot()
	{
		EPROCESS* eprocess = reinterpret_cast<EPROCESS*>(PsGetCurrentProcess());
		CMMVadShort* vad_root = reinterpret_cast<CMMVadShort*>(eprocess->VadRoot());

		if (!vad_root)
			return false;

		RelinkToVadRoot(*vad_root);
		return true;
	}

private:
	void* m_dummyStack[0x10];
	VadTree m_vadTree;
};


#endif //__DUMMEVAD_H__
