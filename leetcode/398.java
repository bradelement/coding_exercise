public class Solution {

    private HashMap<Integer, ArrayList<Integer>> hm = new HashMap<Integer, ArrayList<Integer>>();
    Random ra = new Random();

    public Solution(int[] nums) {
        ArrayList<Integer> al;
        for (int i=0; i<nums.length; i++) {
            if (hm.containsKey(nums[i])) {
                al = hm.get(nums[i]);
            } else {
                al = new ArrayList<Integer>();
            }
            al.add(i);
            hm.put(nums[i], al);
        }
    }

    public int pick(int target) {
        ArrayList<Integer> al = hm.get(target);
        if (al.size() == 1) {
            return al.get(0);
        }
        int index = ra.nextInt(al.size());
        return al.get(index);
    }
}
