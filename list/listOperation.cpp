// leetcode:206，141，21，19，876
#include <stdio.h>
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};
// leetcode 206 单链反转
ListNode* reverseList(ListNode* head) {
    if (head == NULL) return NULL;
    if (head->next == NULL) return head;

    ListNode* prev   = NULL;
    ListNode* cur    = head;
    ListNode* behind = head->next;

    while (cur != NULL) {
        behind    = cur->next;
        cur->next = prev;

        prev = cur;
        cur  = behind;
    }

    return prev;
}
// 141 单链表有环
bool hasCycle(ListNode* head) {
    if (head == NULL || head->next == NULL) return false;

    ListNode* slow  = head;
    ListNode* quick = head;

    while (quick->next != NULL && quick->next->next != NULL) {
        quick = quick->next->next;
        slow  = slow->next;

        if (quick == slow) {
            return true;
        }
    }
    return false;
}

ListNode* mergeTwoLists(ListNode* s1, ListNode* s2) {
    if (s1 == NULL) return s2;
    if (s2 == NULL) return s1;

    if (s1->val <= s2->val) {
        s1->next = mergeTwoLists(s1->next, s2);
        return s1;
    } else {
        s2->next = mergeTwoLists(s1, s2->next);
        return s2;
    }
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (head == NULL) return NULL;
    if (head->next == NULL && n == 1) return NULL;

    ListNode dummy(-1);
    dummy.next     = head;
    ListNode* slow = &dummy;
    ListNode* fast = &dummy;

    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }

    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    ListNode* del = slow->next;
    slow->next    = del->next;

    return dummy.next;
}

ListNode* middleNode(ListNode* head) {
    if (head == NULL || head->next == NULL) return head;

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }

    if (fast->next == NULL) {
        return slow;
    }
    if (fast->next->next == NULL) {
        return slow->next;
    }
    return slow;
}
