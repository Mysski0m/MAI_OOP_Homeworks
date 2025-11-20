#pragma once

#include "exceptions.hpp"
#include "memory_resource.hpp"

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iterator>
#include <memory>
#include <memory_resource>
#include <stdexcept>
#include <string>
#include <utility>

template <typename T> class List {
  friend class ListIsEmptyException;

private:
  class Node {
    friend class ListIterator;
    friend class List;

  private:
    T data_;
    Node *prev_;
    Node *next_;

  public:
    explicit Node(const T value) {
      data_ = value;
      prev_ = nullptr;
      next_ = nullptr;
    }
  };

public:
  class ListIterator {
    friend class List;

  public:
    using value_type = T;
    using reference_type = value_type &;
    using pointer_type = value_type *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    inline bool operator==(const ListIterator &other_it) const {
      return current_ == other_it.current_;
    };

    inline bool operator!=(const ListIterator &other_it) const {
      return current_ != other_it.current_;
    }

    inline reference_type operator*() const {
      if (current_ == nullptr || current_ == barrier_elem_for_iter_) {
        throw ListIsEmptyException("Iterator is at end!\n");
      }
      return current_->data_;
    };

    ListIterator &operator++() {
      if (current_ != nullptr && current_ != barrier_elem_for_iter_) {
        current_ = current_->next_;
      }
      return *this;
    };

    ListIterator operator++(int) {
      ListIterator tmp = *this;
      if (current_ != nullptr && current_ != barrier_elem_for_iter_) {
        current_ = current_->next_;
      }
      return tmp;
    };

    inline pointer_type operator->() const {
      if (current_ == nullptr || current_ == barrier_elem_for_iter_) {
        throw ListIsEmptyException("Iterator is at end!\n");
      }
      return &(current_->data_);
    };

    explicit ListIterator(Node *node) { current_ = node; }

  private:
    Node *current_;
    Node *barrier_elem_for_iter_ = nullptr;
    void SetBarrier(Node *barrier) { barrier_elem_for_iter_ = barrier; }
  };

public:
  explicit List(
      std::pmr::memory_resource *mr = std::pmr::new_delete_resource());

  explicit List(size_t size, std::pmr::memory_resource *mr =
                                 std::pmr::new_delete_resource());
  List(const std::initializer_list<T> &values,
       std::pmr::memory_resource *mr = std::pmr::new_delete_resource());
  List(const List &other);
  List &operator=(const List &other);

  ListIterator Begin() const noexcept;
  ListIterator End() const noexcept;

  inline T &Front() const;
  inline T &Back() const;
  inline bool IsEmpty() const noexcept;
  inline size_t Size() const noexcept;
  void Swap(List &a);
  ListIterator Find(const T &value) const;
  void Erase(ListIterator pos);
  void Insert(ListIterator pos, const T &value);
  void Clear() noexcept;
  void PushBack(const T &value);
  void PushFront(const T &value);
  void PopBack();
  void PopFront();

  ~List();

private:
  Node *head_ = nullptr;
  Node *tail_ = nullptr;
  Node *barrier_elem_ = nullptr;
  size_t size_ = 0;
  std::pmr::polymorphic_allocator<Node> allocator_;

  Node *AllocateNode(const T &value);
  void DeallocateNode(Node *node);
};

namespace std {
template <typename T> void swap(List<T> &a, List<T> &b);
}

#include "list.ipp"