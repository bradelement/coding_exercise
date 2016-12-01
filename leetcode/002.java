public class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        return addTwoNode(l1, l2, 0);
    }

    private ListNode addTwoNode(ListNode l1, ListNode l2, int carry)
    {
        if (l1 == null) {
            if (carry > 0) {
                return addTwoNode(new ListNode(carry), l2, 0);
            }
            return l2;
        }
        if (l2 == null) {
            if (carry > 0) {
                return addTwoNode(l1, new ListNode(carry), 0);
            }
            return l1;
        }

        int val = l1.val + l2.val + carry;
        if (val >= 10) {
            val -= 10;
            carry = 1;
        } else {
            carry = 0;
        }

        ListNode head = new ListNode(val);
        head.next = addTwoNode(l1.next, l2.next, carry);
        return head;
    }
}
