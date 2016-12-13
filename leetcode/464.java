import javafx.util.Pair;

import java.util.ArrayList;
import java.util.HashMap;

public class Solution
{
    private static HashMap<Pair<Integer, Integer>, Boolean> hs = new HashMap<Pair<Integer, Integer>, Boolean>();

    public boolean canIWin(int maxChoosableInteger, int desiredTotal)
    {
        int sum = maxChoosableInteger * (maxChoosableInteger+1) / 2;
        if (sum < desiredTotal) return false;

        int mark = (1 << maxChoosableInteger) - 1;
        ArrayList<Integer> ava = available(mark, maxChoosableInteger);
        boolean ret = false;
        for (int i: ava) {
            int nmark = mark & (~(1<<(i-1)));
            if (!canWinOnce(desiredTotal-i, nmark, maxChoosableInteger)) {
                ret = true;
                break;
            }
        }
        return ret;
    }

    private boolean canWinOnce(int total, int mark, int maxChoosableInteger)
    {
        if (total <= 0) return false;
        Pair<Integer, Integer> pair = new Pair<Integer, Integer>(total, mark);
        if (hs.containsKey(pair)) {
            return hs.get(pair);
        }
        ArrayList<Integer> ava = available(mark, maxChoosableInteger);
        boolean ret = false;
        for (int i: ava) {
            if (i >= total) {
                ret = true;
                break;
            }
            int nmark = mark & (~(1<<(i-1)));
            if (!canWinOnce(total-i, nmark, maxChoosableInteger)) {
                ret = true;
                break;
            }
        }
        hs.put(pair, ret);
        return ret;
    }

    private ArrayList<Integer> available(int mark, int maxChoosableInteger)
    {
        ArrayList<Integer> ret = new ArrayList<Integer>();
        for (int i=maxChoosableInteger-1; i>=0; i--) {
            int t = 1<<i;
            if ((mark & t) != 0) {
                ret.add(i+1);
            }
        }
        return ret;
    }
}
