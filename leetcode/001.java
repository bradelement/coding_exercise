public class Solution {
    public int[] twoSum(int[] nums, int target) {
        HashMap<Integer, Integer> m = new HashMap<Integer, Integer>();
        for (int i=0; i<nums.length; i++) {
            m.put(nums[i], i);
        }

        int[] ret = new int[2];
        for (int i=0; i<nums.length; i++) {
            int another = target - nums[i];
            if (m.containsKey(another)) {
                ret[0] = i;
                ret[1] = m.get(another);
                if (ret[0] == ret[1]) continue;
                break;
            }
        }
        return ret;
    }
}
