template <class I, class Less>
void NewSort(I l, I h, const Less& less)
{
	for(;;) {
		ptrdiff_t count = h - l;
		if(count < 2)
			return;
		if(count < 8) {                         // Final optimized SelectSort
			ForwardSort(l, h, less);
			return;
		}
	
		I lp = l + 1;
		I hp = h - 2;

		OrderIter2__(l, lp, less);
		OrderIter2__(hp, h - 1, less);
		if(less(*hp, *lp)) {
			OrderIter2__(lp, hp, less);
			OrderIter2__(l, lp, less);
			OrderIter2__(hp, h - 1, less);
			OrderIter2__(lp, hp, less);
		}
		
		I i = l + 2;
		I lt = lp;
		I gt = hp;
	
		while(i < gt)
			if(less(*i, *lp))
				IterSwap(i++, ++lt);
			else
			if(less(*hp, *i))
			    IterSwap(i, --gt);
			else
			    i++;
	
		IterSwap(lp, lt);
		IterSwap(hp, gt);

		ptrdiff_t lcount = lt - l;
		ptrdiff_t mcount = gt - lt - 1;
		ptrdiff_t hcount = h - gt - 1;
		
		if(lcount > hcount && lcount > mcount) {
		    NewSort(lt + 1, gt, less);
		    NewSort(gt + 1, h, less);
			h = lt;
		}
		else
		if(mcount > lcount && mcount > hcount) {
			NewSort(l, lt, less);
		    NewSort(gt + 1, h, less);
		    l = lt + 1;
		    h = gt;
		}
		else {
			NewSort(l, lt, less);
		    NewSort(lt + 1, gt, less);
		    l = gt + 1;
		}
	}
}

#if 0
template <class I, class Less>
void NewSort(I l, I h, const Less& less)
{
	for(;;) {
		ptrdiff_t count = h - l;
		if(count < 2)
			return;
		if(count < 8) {                         // Final optimized SelectSort
			ForwardSort(l, h, less);
			return;
		}
	
		I hi = h - 1;
	
		if(less(*hi, *l))
			IterSwap(hi, l);
	
		I i = l + 1;
		I lt = i;
		I gt = hi - 1;
	
		while(i <= gt)
			if(less(*i, *l))
				IterSwap(i++, lt++);
			else
			if(less(*hi, *i))
			    IterSwap(i, gt--);
			else
			    i++;
	
		IterSwap(l, --lt);
		IterSwap(h - 1, ++gt);

		ptrdiff_t lcount = lt - l;
		ptrdiff_t mcount = gt - lt - 1;
		ptrdiff_t hcount = h - gt - 1;
		
		if(lcount > hcount && lcount > mcount) {
		    NewSort(lt + 1, gt, less);
		    NewSort(gt + 1, h, less);
			h = lt;
		}
		else
		if(mcount > lcount && mcount > hcount) {
			NewSort(l, lt, less);
		    NewSort(gt + 1, h, less);
		    l = lt + 1;
		    h = gt;
		}
		else {
			NewSort(l, lt, less);
		    NewSort(lt + 1, gt, less);
		    l = gt + 1;
		}
	}
}
#endif