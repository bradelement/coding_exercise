public class Solution {
    public boolean isPalindrome(int x) {
        if (x < 0) return false;

        int y = 0, tmp = x;
        while (tmp != 0) {
            y = y * 10 + tmp % 10;
            tmp /= 10;
        }
        return x == y;
    }
}
