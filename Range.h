/**
 * @file Range.h
 * @author created by: Peter Hlavaty
 */

#ifndef __RANGE_H__
#define __RANGE_H__

#include "ntifs.h"

template<class TYPE>
struct CRange
{
	//implicit
	CRange(
		__in const TYPE begin, 
		__in const TYPE end = NULL
		) : m_begin((ULONG_PTR)(begin)), m_end((ULONG_PTR)(end ? end : begin)) { };

public:
	bool IsInRange(
		__in const TYPE address
		) const
	{
		return IsInRange(reinterpret_cast<ULONG_PTR>(address));
	};

	void SetSize(
		__in size_t size
		)
	{ 
		m_end = max(m_begin + size - 1, m_end); 
	};

	size_t GetSize()
	{ 
		return (m_end - m_begin + 1); 
	};

	void Reset(
		__in const TYPE begin
		)
	{
		Set(begin, begin);
	};

	TYPE& Begin() const
	{
		return (TYPE&)(m_begin);
	};

	TYPE& End() const
	{
		return (TYPE&)(m_end);
	};

protected:
	ULONG_PTR m_begin;
	ULONG_PTR m_end;

	static 
	inline 
	bool IsOverlaping(
		__in const CRange &left, 
		__in const CRange &right
		)
	{
		return !(left.Begin() > right.End() || right.Begin() > left.End());
	}

	friend
	bool operator>(
		__in const CRange &left, 
		__in const CRange &right
		)
	{
		if (IsOverlaping(left, right))
			return false;
		
		return (left.m_begin > right.m_begin);
	}
	
	friend
	bool operator<(
		__in const CRange &left, 
		__in const CRange &right
		)
	{
		return (right > left);
	}

	friend
	bool operator==(
		__in const CRange &left, 
		__in const CRange &right
		)
	{
		return IsOverlaping(left, right);
	}
};

#endif //__RANGE_H__
