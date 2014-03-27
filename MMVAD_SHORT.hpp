/**
 * @file MMVAD_SHORT.hpp
 * @author created by: Peter Hlavaty
 */

#ifndef __MMVAD_SHORT_EXTENDED_H__
#define __MMVAD_SHORT_EXTENDED_H__

#include "MMVAD_SHORT.h"

#include <boost/intrusive/avltree.hpp>

using namespace boost::intrusive;

#define EXPAND(addr) reinterpret_cast<UCHAR*>(static_cast<ULONG_PTR>(addr) << PAGE_SHIFT)

struct CMMVadShort :
	private MMVAD_SHORT
{
public:
	avl_set_member_hook< optimize_size<true> > MMADDRESS_NODE;

	operator MMVAD_SHORT*()
	{
		return this;
	} // implicit conversion to MMVAD_SHORT*
	
	MMVAD_SHORT* operator->()
	{
		return this;
	} // implicit conversion to MMVAD_SHORT*

	friend bool operator<(
		__in const CMMVadShort& a, 
		__in const CMMVadShort& b
		)
	{
		CRange<ULONG_PTR> ar(((CMMVadShort&)a).StartingVpn(), ((CMMVadShort&)a).EndingVpn());
		CRange<ULONG_PTR> br(((CMMVadShort&)b).StartingVpn(), ((CMMVadShort&)b).EndingVpn());
		return  (ar < br);
	}
};

struct CMMVadShortCmp
{
	bool operator()(
		__in const CRange<void*> &range,
		__in const CMMVadShort &vad
		) const
	{
		MMVAD_SHORT* vs = ((CMMVadShort&)vad);
		CRange<void*> vad_range(EXPAND(vs->StartingVpn()), EXPAND(vs->EndingVpn()));
		return  (range < vad_range);
	}

	bool operator()(
		__in const CMMVadShort &vad,
		__in const CRange<void*> &range
		) const
	{
		MMVAD_SHORT* vs = ((CMMVadShort&)vad);
		CRange<void*> vad_range(EXPAND(vs->StartingVpn()), EXPAND(vs->EndingVpn()));
		return (vad_range < range);
	}
};

typedef member_hook< CMMVadShort, avl_set_member_hook< optimize_size<true> >, &CMMVadShort::MMADDRESS_NODE > VadMemberOption;
typedef avltree< CMMVadShort, VadMemberOption > VadTree;

#endif //__MMVAD_SHORT_EXTENDED_H__
