#ifndef _Sort_other_h_
#define _Sort_other_h_

template <class I, class Less>
void NewSort2(I lo, I h, const Less& less)
{
	I hi = h - 1;

	if (hi <= lo) return;

    if (less(*hi, *lo)) IterSwap(lo, hi);

    I lt = lo + 1, gt = hi - 1;
    I i = lo + 1;
    while (i <= gt) {
        if       (less(*i, *lo)) IterSwap(lt++, i++);
        else if  (less(*hi, *i)) IterSwap(i, gt--);
        else                     i++;
    }
    
    IterSwap(lo, --lt);
    IterSwap(hi, ++gt);

    // recursively sort three subarrays
    NewSort(lo, lt - 1 + 1, less);
    if(less(*lt, *gt))
		NewSort(lt + 1, gt - 1 + 1, less);
    NewSort(gt+1, hi + 1, less);
}



#endif
