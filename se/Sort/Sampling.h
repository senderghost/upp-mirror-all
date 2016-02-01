template <class I, class Less>
void NewSort0(I l, I h, const Less& less, int nth_element = -1)
{
	for(;;) {
		int count = int(h - l);
		if(count < 8) {                         // Final optimized SelectSort
			if(count < 2)
				return;
			ForwardSort(l, h, less);
			return;
		}
		I pivot = l + 1;
		TEST(part_count += count);
		if(count > 40 || nth_element == -1)
			IterSwap(pivot, l + Random(count)); // Randomize!
		OrderIter2__(l, pivot, less);      // sort l, pivot, h-1 to find median of 3
		OrderIter2__(pivot, h - 1, less);
		OrderIter2__(l, pivot, less);
		LOG(*l << " " << *pivot << " " << *(h - 1));
		I ii = pivot;
		for(I i = pivot + 1; i != h - 1; ++i)   // do partitioning; already l <= pivot <= h - 1
			if(less(*i, *pivot))
				IterSwap(++ii, i);
		IterSwap(ii, pivot); // put pivot back in between partitions
		I iih = ii;
		while(iih + 1 != h && !less(*ii, *(iih + 1))) // Find middle range of elements equal to pivot
			++iih;
		TEST(misbalance += abs((ii - l) - (h - iih - 1)));
		LOG("=== " << count << " " << ii - l << ":" << h - iih - 1);
		if(nth_element >= 0) {
			int lh = ii - l; // end of left partition
			int hl = iih + 1 - l; // begin of right partition
			if(nth_element < lh) // nth_element is in the left partition
				h = ii;
			else
			if(nth_element >= hl) {
				l = iih + 1;
				nth_element -= hl;
			}
			else
				return;
		}
		else {
			if(ii - l < h - iih - 1) {       // recurse on smaller partition, tail on larger
				NewSort(l, ii, less, -2);
				l = iih + 1;
			}
			else {
				int n = h - iih - 1;
				NewSort(iih + 1, h, less, -2);
				h = ii;
			}
		}
	}
}

template <class I, class Less>
void NewSort(I l, I h, const Less& less, int nth_element = -1)
{
	for(;;) {
		int count = int(h - l);
		if(count < 8) {                         // Final optimized SelectSort
			if(count < 2)
				return;
			ForwardSort(l, h, less);
			return;
		}
		I pivot = l;
		TEST(part_count += count);
		if(count > 40 || nth_element == -1)
			IterSwap(l, l + Random(count)); // Randomize!
		LLOG(*pivot);
		I ii = pivot;
		for(I i = pivot + 1; i != h; ++i)
			if(less(*i, *pivot))
				IterSwap(++ii, i);
		IterSwap(ii, pivot); // put pivot back in between partitions
		I iih = ii;
		while(iih + 1 != h && !less(*ii, *(iih + 1))) // Find middle range of elements equal to pivot
			++iih;
		TEST(misbalance += abs((ii - l) - (h - iih - 1)));
		LLOG("=== " << count << " " << ii - l << ":" << h - iih - 1);
		if(nth_element >= 0) {
			int lh = ii - l; // end of left partition
			int hl = iih + 1 - l; // begin of right partition
			if(nth_element < lh) // nth_element is in the left partition
				h = ii;
			else
			if(nth_element >= hl) {
				l = iih + 1;
				nth_element -= hl;
			}
			else
				return;
		}
		else {
			if(ii - l < h - iih - 1) {       // recurse on smaller partition, tail on larger
				NewSort(l, ii, less, -2);
				l = iih + 1;
			}
			else {
				int n = h - iih - 1;
				NewSort(iih + 1, h, less, -2);
				h = ii;
			}
		}
	}
}
