# FUtrure annotations like making a class and it's memebers has the same type hint from it
from __future__ import annotations


# No method overloading in python
class Node:

    def __init__(
        self,
        value: int = 0,
        previous: Node | None = None,
        after: Node | None = None,
    ) -> None:
        self.value = value
        self.previous = previous
        self.after = after


class LinkedList:
    def __init__(self) -> None:
        self.mp: dict[int, Node] = {}
        self.head: Node
        self.tail: Node | None = None

    def add(self, value: int) -> None:
        new_node: Node = Node(value)
        if self.head != None:
            new_node.previous = self.head
            self.head.after = new_node

        self.head = new_node
        self.mp[value] = new_node

        self.delete_last()

    def delete_last(self):
        if self.tail != None:
            # deletes a reference, not the linkedListect itself
            del self.mp[self.tail.value]
            self.tail = self.tail.after
        if self.tail != None:
            self.tail.previous = None

    def find(self, value: int):
        node: Node = self.mp[value]
        if node and self.head != node:
            if node.previous != None:
                node.previous.after = node.after
            else:
                if self.tail != None:
                    self.tail = self.tail.after
                    if self.tail != None:
                        self.tail.previous = None

            node.previous = self.head
            self.head.after = node
            self.head = node
            node.after = None

    def print_all(self):
        curr: Node | None = self.tail
        while curr:
            print(curr.value)
            curr = curr.after

        print("\n")


if __name__ == "__main__":
    linkedList: LinkedList = LinkedList()
    n: int = int(input("Enter number on N: "))
    for i in range(n):
        print(f"Enter a value until {n} is reached, currently: {i+1}")
        value: int = int(input())
        node: Node = Node(value)
        if linkedList.tail == None:
            linkedList.tail = node
        else:
            copy_node: Node = linkedList.tail
            while copy_node.after:
                copy_node = copy_node.after

            copy_node.after = node
            node.previous = copy_node

        linkedList.head = node
        linkedList.mp[value] = node

    while True:
        print("(1) Add a value")
        print("(2) Roll back to a previous position")
        print("(3) print current values in the DS")

        try:
            input_choice = int(input("Enter number: "))
        except ValueError:
            print("Invalid input, please enter a number\n")
            continue
        print()

        if input_choice == 1:
            try:
                value_num = int(
                    input("Enter the value/square you wanna add: ")
                )
                linkedList.add(value_num)
            except ValueError:
                print("Invalid number")

        elif input_choice == 2:
            try:
                value_num = int(
                    input("Enter the value/square you wanna roll back to: ")
                )
                linkedList.find(value_num)
            except ValueError:
                print("Invalid number")

        elif input_choice == 3:
            linkedList.print_all()

        else:
            print("Please enter a valid option")

        print()
