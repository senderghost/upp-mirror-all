#ifndef _Sort_FwSort_h_
#define _Sort_FwSort_h_


template <class I>
String RangeA(I l, int n)
{
	String r;
	for(int i = 0; i < n; i++)
		MergeWith(r, ", ", AsString(l[i]));
	return r;
}

template <class I>
String RangeA(I l, I h)
{
	return RangeA(l, h - l);
}

template <class I, class Less>
void SmallSort2(I begin, I end, const Less& less)
{
	if(begin == end)
		return;
	I last = end;
	--last;
	LOG(RangeA(begin, end));
	while(!(begin == last)) {
		I best = last;
		I next = last;
		I ptr = last;
		for(;;) {
			if(less(*best, *--ptr)) {  // best holds, scan for better candidate
				do
					if(ptr == begin) { // best is the final minimum
						IterSwap(begin, best);
						++begin;
						LOG("Best is min " << RangeA(begin, end));
						goto NEXT_ITEM;
					}
				while(less(*best, *--ptr));
				if(ptr == begin) { // begin is the final minimum, best is 2nd least
					IterSwap(++begin, best);
					++begin;
					LOG("Begin is min " << RangeA(begin, end));
					break;
				}
				next = ptr; // mark position after new best as the new end of sorted array
				++next;     // it will hold only if all subseqent iterations define new best (descending order)
			}
			else
			if(ptr == begin) { // begin is the final minimum
				begin = next;  // and everything is sorted up to next
				LOG("Skip " << RangeA(begin, end));
				break;
			}
			best = ptr;
		}
	NEXT_ITEM:
		;
	}
}

template <typename I, typename Less>
void SmallSort3(I begin, I end, const Less& less)
{
	if(begin == end)
		return;
	I last = end - 1;
	while(begin + 1 != last) {
		I mini = last;
		for(I i = last - 1; i != begin; --i)
			if(less(*i, *mini))
				mini = i;
		if(less(*begin, *mini)) {
			++begin;
			if(begin + 1 == last)
				break;
		}
		IterSwap(begin++, mini);
	}
	if(less(*last, *begin))
		IterSwap(last, begin);
}

template <typename I, typename Less>
void SmallSort(I begin, I end, const Less& less)
{
	if(begin == end)
		return;
	I last = end - 1;
	while(begin + 1 != last) {
		I mini = last;
		I i = last--;
		for(;;) {
			while(less(*mini, *i))
				if(i == begin + 1)
					
			for(I i = last - 1; i != begin; --i)
				if(less(*i, *mini))
					mini = i;
		}
		if(less(*begin, *mini)) {
			++begin;
			if(begin + 1 == last)
				break;
		}
		IterSwap(begin++, mini);
	}
	if(less(*last, *begin))
		IterSwap(last, begin);
}

#endif
