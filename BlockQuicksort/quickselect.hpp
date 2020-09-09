
#include "partition.h"

namespace original_block {
    template<typename Iter, typename Comp>
    void nth_element(Iter begin, Iter end, Comp comparator, unsigned int nth_element) {
        while (true) {
            if (begin == end) return;


            if (nth_element == 0) {
                Iter min = begin;

                Iter it = begin + 1;

                while (it != end) {
                    if (comparator(*it, *min)) {
                        min = it;
                    }

                    ++it;
                }

                std::iter_swap(min, begin);

                return;
            } else if (nth_element == end - begin - 1) {
                Iter max = begin;

                Iter it = begin + 1;

                while (it != end) {
                    if (!comparator(*it, *max)) {
                        max = it;
                    }

                    ++it;
                }

                std::iter_swap(max, end - 1);
                return;
            }


            Iter pivot = partition::Hoare_block_partition_mosqrt<Iter, Comp>::partition(begin, end, comparator);

            if (pivot - begin == nth_element) return;

            else if (nth_element<pivot - begin) {
                end = pivot;
            } else {
                nth_element -= (pivot + 1 - begin);
                begin = pivot + 1;
            }
        }
    }
}
