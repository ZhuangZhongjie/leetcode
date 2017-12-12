#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode * result = new ListNode(0);
		ListNode * last = result;
		ListNode * prev = NULL;
		int s = 0;

		while (l1 || l2) {
			s = last->val;
			if (l1) {
				s += l1->val;
				l1 = l1->next;
			}
			if (l2) {
				s += l2->val;
				l2 = l2->next;
			}

			last->val = s % 10;
			last->next = new ListNode(s / 10);
			prev = last;
			last = last->next;

		}

		if (last->val == 0) {
			delete last;
			last = NULL;
			prev->next = NULL;
		}

		return result;
	}
};


int main(int argc, char** argv)
{
	auto sol = Solution();

	// a = 1->3->5, 531
	ListNode * a = new ListNode(1);
	a->next = new ListNode(6);
	a->next->next = new ListNode(5);

	// b = 2->4, 42
	ListNode * b = new ListNode(2);
	b->next = new ListNode(4);

	auto res = sol.addTwoNumbers(a, b);
	for(auto i = res; i; i = i->next) {
		std::cout << i->val << ", ";
	}
	std::cout << std::endl;

	return 0;
}