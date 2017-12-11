#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode * result = new ListNode(0);
		ListNode * last = result;

		while (l1 || l2) {
			int s = last->val;
			if (l1) {
				s += l1->val;
				l1 = l1->next;
			}
			if (l2) {
				s += l2->val;
				l2 = l2->next;
			}

			if (s > 10) {
				last->val = s - 10;
				last->next = new ListNode(1);
			} else {
				last->val = s;
				last->next = new ListNode(0);
			}

			last = last->next;

		}

		return result;
	}
};


int main(int argc, char** argv)
{
	return 0;
}