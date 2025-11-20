#pragma once

#include "list.hpp"

template <typename T>
List<T>::List(std::pmr::memory_resource *mr) : allocator_(mr) {
  barrier_elem_ = AllocateNode(T{});
  barrier_elem_->next_ = barrier_elem_;
  barrier_elem_->prev_ = barrier_elem_;
  size_ = 0;
}

template <typename T>
List<T>::List(size_t size, std::pmr::memory_resource *mr) : List(mr) {
  for (size_t i = 0; i < size; ++i) {
    PushFront(T{});
  }
}

template <typename T>
List<T>::List(const std::initializer_list<T> &values,
              std::pmr::memory_resource *mr)
    : List(mr) {
  for (const auto &value : values) {
    PushBack(value);
  }
}

template <typename T>
List<T>::List(const List &other) : List(other.allocator_.resource()) {
  for (auto it = other.Begin(); it != other.End(); ++it) {
    PushBack(*it);
  }
}

template <typename T> List<T> &List<T>::operator=(const List &other) {
  if (this != &other) {
    Clear();
    for (auto it = other.Begin(); it != other.End(); ++it) {
      PushBack(*it);
    }
  }
  return *this;
}

template <typename T>
typename List<T>::ListIterator List<T>::Begin() const noexcept {
  if (head_ == nullptr) {
    return End();
  }
  ListIterator it(head_);
  it.SetBarrier(barrier_elem_);
  return it;
}

template <typename T>
typename List<T>::ListIterator List<T>::End() const noexcept {
  ListIterator it(barrier_elem_);
  it.SetBarrier(barrier_elem_);
  return it;
}

template <typename T> inline T &List<T>::Front() const {
  if (head_ != nullptr) {
    return head_->data_;
  }
  throw ListIsEmptyException("Front error");
}

template <typename T> inline T &List<T>::Back() const {
  if (tail_ != nullptr) {
    return tail_->data_;
  }
  throw ListIsEmptyException("Back error");
}

template <typename T> inline bool List<T>::IsEmpty() const noexcept {
  return size_ == 0;
}

template <typename T> inline size_t List<T>::Size() const noexcept {
  return size_;
}

template <typename T> void List<T>::Swap(List &a) {
  std::swap(head_, a.head_);
  std::swap(tail_, a.tail_);
  std::swap(barrier_elem_, a.barrier_elem_);
  std::swap(size_, a.size_);
  std::swap(allocator_, a.allocator_);
}

template <typename T>
typename List<T>::ListIterator List<T>::Find(const T &value) const {
  for (auto it = Begin(); it != End(); ++it) {
    if (*it == value) {
      return it;
    }
  }
  return End();
}

template <typename T> void List<T>::Erase(ListIterator pos) {
  Node *node = pos.current_;

  if (node == nullptr || head_ == nullptr) {
    throw ListIsEmptyException("List is empty. Erase is impossible");
  }

  if (node->prev_ != barrier_elem_) {
    node->prev_->next_ = node->next_;
    node->next_->prev_ = node->prev_;
  } else {
    barrier_elem_->next_ = node->next_;
    node->next_->prev_ = barrier_elem_;
    head_ = node->next_;
  }

  if (node->next_ != barrier_elem_) {
    node->next_->prev_ = node->prev_;
    node->prev_->next_ = node->next_;
  } else {
    barrier_elem_->prev_ = node->prev_;
    node->prev_->next_ = barrier_elem_;
    tail_ = node->prev_;
  }

  DeallocateNode(node);
  --size_;

  if (size_ == 0) {
    head_ = nullptr;
    tail_ = nullptr;
    barrier_elem_->next_ = barrier_elem_;
    barrier_elem_->prev_ = barrier_elem_;
  }
}

template <typename T> void List<T>::Insert(ListIterator pos, const T &value) {
  if (pos.current_ == nullptr || pos.current_ == barrier_elem_) {
    PushBack(value);
    return;
  }

  Node *new_node = AllocateNode(value);

  if (pos.current_->prev_ != barrier_elem_) {
    pos.current_->prev_->next_ = new_node;
    new_node->prev_ = pos.current_->prev_;
  } else {
    head_->prev_ = new_node;
    new_node->next_ = head_;
    new_node->prev_ = barrier_elem_;
    barrier_elem_->next_ = new_node;
    head_ = new_node;
  }

  if (pos.current_->next_ != barrier_elem_) {
    new_node->next_ = pos.current_;
    pos.current_->prev_ = new_node;
  } else if (pos.current_ == barrier_elem_) {
    tail_->next_ = new_node;
    new_node->prev_ = tail_;
    new_node->next_ = barrier_elem_;
    barrier_elem_->prev_ = new_node;
    tail_ = new_node;
  } else {
    pos.current_->prev_ = new_node;
    new_node->next_ = tail_;
  }

  ++size_;
}

template <typename T> void List<T>::Clear() noexcept {
  while (!IsEmpty()) {
    PopFront();
  }
}

template <typename T> void List<T>::PushBack(const T &value) {
  Node *new_node = AllocateNode(value);

  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
    new_node->next_ = barrier_elem_;
    new_node->prev_ = barrier_elem_;
    barrier_elem_->next_ = new_node;
    barrier_elem_->prev_ = new_node;
  } else {
    tail_->next_ = new_node;
    new_node->prev_ = tail_;
    new_node->next_ = barrier_elem_;
    barrier_elem_->prev_ = new_node;
    tail_ = new_node;
  }

  ++size_;
}

template <typename T> void List<T>::PushFront(const T &value) {
  Node *new_node = AllocateNode(value);

  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
    new_node->next_ = barrier_elem_;
    new_node->prev_ = barrier_elem_;
    barrier_elem_->next_ = new_node;
    barrier_elem_->prev_ = new_node;
  } else {
    head_->prev_ = new_node;
    barrier_elem_->next_ = new_node;
    new_node->prev_ = barrier_elem_;
    new_node->next_ = head_;
    head_ = new_node;
  }

  ++size_;
}

template <typename T> void List<T>::PopBack() {
  if (tail_ == nullptr) {
    throw ListIsEmptyException("PopBack is impossible");
  }

  Node *node_to_del = tail_;

  if (tail_ == head_) {
    head_ = nullptr;
    tail_ = nullptr;
    barrier_elem_->next_ = barrier_elem_;
    barrier_elem_->prev_ = barrier_elem_;
  } else {
    tail_ = tail_->prev_;
    tail_->next_ = barrier_elem_;
    barrier_elem_->prev_ = tail_;
  }

  DeallocateNode(node_to_del);

  --size_;
}

template <typename T> void List<T>::PopFront() {
  if (head_ == nullptr) {
    throw ListIsEmptyException("PopFront is impossible");
  }

  Node *node_to_del = head_;

  if (head_ == tail_) {
    head_ = nullptr;
    tail_ = nullptr;
    barrier_elem_->next_ = barrier_elem_;
    barrier_elem_->prev_ = barrier_elem_;
  } else {
    head_ = head_->next_;
    head_->prev_ = barrier_elem_;
    barrier_elem_->next_ = head_;
  }

  DeallocateNode(node_to_del);
  --size_;
}

template <typename T> List<T>::~List() {
  Clear();
  DeallocateNode(barrier_elem_);
}

template <typename T>
typename List<T>::Node *List<T>::AllocateNode(const T &value) {
  Node *node = allocator_.allocate(1);
  try {
    std::construct_at(node, value);
  } catch (...) {
    allocator_.deallocate(node, 1);
    throw;
  }
  return node;
}

template <typename T> void List<T>::DeallocateNode(Node *node) {
  if (node) {
    std::destroy_at(node);
    allocator_.deallocate(node, 1);
  }
}

namespace std {
template <typename T> void swap(List<T> &a, List<T> &b) { a.Swap(b); }
} // namespace std