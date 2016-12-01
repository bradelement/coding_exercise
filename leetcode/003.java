public class Solution {
    public int lengthOfLongestSubstring(String s) {
        Map m = new HashMap<String, Integer>();
        int ret = 0;
        int head = 0;
        for (int i=0; i<s.length(); i++) {
            char c = s.charAt(i);
            if (m.containsKey(c)) {
                int pos = (Integer) m.get(c);
                head = Math.max(head, pos+1);
            }
            ret = Math.max(ret, i-head+1);
            m.put(c, i);
        }
        return ret;
    }
}
