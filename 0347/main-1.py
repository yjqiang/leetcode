from typing import List


class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        counts = {}
        for num in nums:
            counts[num] = counts.get(num, 0) + 1

        buckets = [[] for _ in range(len(nums)+1)]
        for num, count in counts.items():
            buckets[count].append(num)

        # collect from right to left
        flat_list = []
        for i in range(len(buckets) - 1, -1, -1):
            bucket = buckets[i]
            if bucket:
                flat_list += bucket
        return flat_list[:k]


print(Solution().topKFrequent([1], 1))