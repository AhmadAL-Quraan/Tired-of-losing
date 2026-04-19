/************************************************************/
/* USER: AQORAAN                                            */
/* FILE: TiredOfLosing.cpp                                  */
/* DATE: 2026/04/19 21:11:30                                */
/************************************************************/

#include <bits/stdc++.h>

using namespace std;

struct Node {
  int value;
  Node *previous;
  Node *after;
  Node() : value(0), previous(nullptr), after(nullptr) {}
  Node(int value) : value(value), previous(nullptr), after(nullptr) {}
};

class LinkedList {

public:
  unordered_map<int, Node *> mp;
  Node *header = nullptr;
  Node *trailer = nullptr;

  void add(int value) {
    Node *new_node = new Node(value);
    new_node->previous = header;
    header->after = new_node;
    header = new_node;
    mp[value] = new_node;

    // Delete oldest node from memory

    delete_last();
  }
  void find(int value) {
    Node *node = mp[value];
    if (node && header != node) {
      if (mp[value]->previous) {
        mp[value]->previous->after = mp[value]->after;
      } else {
        trailer = mp[value]->after;
      }
      mp[value]->after->previous = mp[value]->previous;
      mp[value]->previous = header;
      mp[value]->previous->after = mp[value];
      mp[value]->after = nullptr;
      header = mp[value];
    }
  }
  void print_all() {
    Node *curr = trailer;
    while (curr) {
      printf("%d ", curr->value);
      curr = curr->after;
    }
    printf("\n");
  }
  void delete_last() {
    mp[trailer->value] = nullptr;
    Node *delete_last = trailer;
    trailer = trailer->after;
    trailer->previous = nullptr;
    delete delete_last;
  }
};

int main() {

  printf("Enter number of values: ");
  int num;
  cin >> num;
  int i;

  LinkedList *obj = new LinkedList();
  for (i = 0; i < num; ++i) {
    printf("Enter a value until %d is reached, currently %d: ", num, i + 1);
    int value;
    cin >> value;
    Node *new_node = new Node(value);
    if (obj->trailer == nullptr) {
      obj->trailer = new_node;
    } else {
      Node *find_last = obj->trailer;
      while (find_last->after != nullptr) {
        find_last = find_last->after;
      }
      find_last->after = new_node;
      new_node->previous = find_last;
    }
    obj->header = new_node;
    obj->mp[value] = new_node;
  }
  while (true) {
    int input;
    printf("(1) Add a value\n(2) Roll back to a previous "
           "position\n(3) print current values in the DS\n");
    printf("Enter number: ");
    scanf("%d", &input);
    int value_num;
    if (input == 1) {
      printf("Enter the value/ square you wanna add: ");
      scanf("%d", &value_num);
      obj->add(value_num);
    } else if (input == 2) {
      printf("Enter the value/sqaure you wanna roll back to: ");
      scanf("%d", &value_num);
      obj->find(value_num);
    } else if (input == 3) {
      obj->print_all();
    } else {
      printf("Please enter a valid option");
    }
  }
}
