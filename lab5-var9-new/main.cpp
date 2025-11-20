#include "list.hpp"
#include <iostream>

int main() {
  List<int> list;

  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);
  list.PushFront(0);

  std::cout << "List: ";
  for (auto it = list.Begin(); it != list.End(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  std::cout << "Size: " << list.Size() << std::endl;
  std::cout << "Front: " << list.Front() << std::endl;
  std::cout << "Back: " << list.Back() << std::endl;

  auto found = list.Find(2);
  if (found != list.End()) {
    std::cout << "Found element: " << *found << std::endl;
  }

  return 0;
}