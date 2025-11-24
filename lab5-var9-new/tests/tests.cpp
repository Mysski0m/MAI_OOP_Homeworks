#include "list.hpp"
#include "memory_resource.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

class ListTest : public ::testing::Test {
protected:
  void SetUp() override { resource = new FixedBlockMemoryResource(1024); }

  void TearDown() override { delete resource; }

  FixedBlockMemoryResource *resource;
};

// Базовые тесты конструкторов
TEST_F(ListTest, DefaultConstructor) {
  List<int> list(resource);
  EXPECT_TRUE(list.IsEmpty());
  EXPECT_EQ(list.Size(), 0U);
}

TEST_F(ListTest, SizeConstructor) {
  List<int> list(3, resource);
  EXPECT_EQ(list.Size(), 3U);
  EXPECT_FALSE(list.IsEmpty());
}

TEST_F(ListTest, InitializerListConstructor) {
  List<int> list({1, 2, 3, 4, 5}, resource);
  EXPECT_EQ(list.Size(), 5U);

  std::vector<int> values;
  for (auto it = list.Begin(); it != list.End(); ++it) {
    values.push_back(*it);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3, 4, 5}));
}

// Тесты добавления элементов
TEST_F(ListTest, PushBack) {
  List<int> list(resource);
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  EXPECT_EQ(list.Size(), 3U);
  EXPECT_EQ(list.Front(), 1);
  EXPECT_EQ(list.Back(), 3);
}

TEST_F(ListTest, PushFront) {
  List<int> list(resource);
  list.PushFront(3);
  list.PushFront(2);
  list.PushFront(1);

  EXPECT_EQ(list.Size(), 3U);
  EXPECT_EQ(list.Front(), 1);
  EXPECT_EQ(list.Back(), 3);
}

TEST_F(ListTest, PushBackAndFrontMixed) {
  List<int> list(resource);
  list.PushBack(2);
  list.PushFront(1);
  list.PushBack(3);
  list.PushFront(0);

  EXPECT_EQ(list.Size(), 4U);
  EXPECT_EQ(list.Front(), 0);
  EXPECT_EQ(list.Back(), 3);
}

// Тесты удаления элементов
TEST_F(ListTest, PopBack) {
  List<int> list({1, 2, 3}, resource);

  list.PopBack();
  EXPECT_EQ(list.Size(), 2U);
  EXPECT_EQ(list.Back(), 2);

  list.PopBack();
  EXPECT_EQ(list.Size(), 1U);
  EXPECT_EQ(list.Back(), 1);

  list.PopBack();
  EXPECT_TRUE(list.IsEmpty());
}

TEST_F(ListTest, PopFront) {
  List<int> list({1, 2, 3}, resource);

  list.PopFront();
  EXPECT_EQ(list.Size(), 2U);
  EXPECT_EQ(list.Front(), 2);

  list.PopFront();
  EXPECT_EQ(list.Size(), 1U);
  EXPECT_EQ(list.Front(), 3);

  list.PopFront();
  EXPECT_TRUE(list.IsEmpty());
}

TEST_F(ListTest, PopBackAndFrontMixed) {
  List<int> list({1, 2, 3, 4, 5}, resource);

  list.PopFront();
  list.PopBack();
  EXPECT_EQ(list.Size(), 3U);
  EXPECT_EQ(list.Front(), 2);
  EXPECT_EQ(list.Back(), 4);

  list.PopFront();
  list.PopBack();
  EXPECT_EQ(list.Size(), 1U);
  EXPECT_EQ(list.Front(), 3);
  EXPECT_EQ(list.Back(), 3);
}

// Тесты итераторов
TEST_F(ListTest, IteratorTraversal) {
  List<int> list({1, 2, 3, 4, 5}, resource);

  std::vector<int> values;
  for (auto it = list.Begin(); it != list.End(); ++it) {
    values.push_back(*it);
  }

  EXPECT_EQ(values, std::vector<int>({1, 2, 3, 4, 5}));
}

TEST_F(ListTest, ConstIterator) {
  const List<int> list({1, 2, 3}, resource);

  std::vector<int> values;
  for (auto it = list.Begin(); it != list.End(); ++it) {
    values.push_back(*it);
  }

  EXPECT_EQ(values, std::vector<int>({1, 2, 3}));
}

TEST_F(ListTest, IteratorPostIncrement) {
  List<int> list({1, 2, 3}, resource);
  auto it = list.Begin();

  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(it++), 1);
  EXPECT_EQ(*it, 2);
}

TEST_F(ListTest, IteratorPreIncrement) {
  List<int> list({1, 2, 3}, resource);
  auto it = list.Begin();

  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*it, 2);
}

TEST_F(ListTest, IteratorEquality) {
  List<int> list({1, 2, 3}, resource);
  auto it1 = list.Begin();
  auto it2 = list.Begin();

  EXPECT_EQ(it1, it2);
  ++it1;
  EXPECT_NE(it1, it2);
}

// Тесты поиска
TEST_F(ListTest, FindExistingElement) {
  List<int> list({1, 2, 3, 4, 5}, resource);

  auto it = list.Find(3);
  EXPECT_NE(it, list.End());
  EXPECT_EQ(*it, 3);

  it = list.Find(1);
  EXPECT_NE(it, list.End());
  EXPECT_EQ(*it, 1);

  it = list.Find(5);
  EXPECT_NE(it, list.End());
  EXPECT_EQ(*it, 5);
}

TEST_F(ListTest, FindNonExistingElement) {
  List<int> list({1, 2, 3, 4, 5}, resource);

  auto it = list.Find(100);
  EXPECT_EQ(it, list.End());

  it = list.Find(-1);
  EXPECT_EQ(it, list.End());
}

TEST_F(ListTest, FindInEmptyList) {
  List<int> list(resource);

  auto it = list.Find(1);
  EXPECT_EQ(it, list.End());
}

// Тесты вставки и удаления
TEST_F(ListTest, InsertAtBeginning) {
  List<int> list({2, 3, 4}, resource);
  auto it = list.Begin();

  list.Insert(it, 1);
  EXPECT_EQ(list.Size(), 4U);
  EXPECT_EQ(list.Front(), 1);

  std::vector<int> values;
  for (auto it = list.Begin(); it != list.End(); ++it) {
    values.push_back(*it);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3, 4}));
}

TEST_F(ListTest, InsertInMiddle) {
  List<int> list({1, 3, 4}, resource);
  auto it = list.Begin();
  ++it; // переходим к элементу 3

  list.Insert(it, 2);
  EXPECT_EQ(list.Size(), 4U);

  std::vector<int> values;
  for (auto it = list.Begin(); it != list.End(); ++it) {
    values.push_back(*it);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3, 4}));
}

TEST_F(ListTest, InsertAtEnd) {
  List<int> list({1, 2, 3}, resource);
  auto it = list.End();

  list.Insert(it, 4);
  EXPECT_EQ(list.Size(), 4U);
  EXPECT_EQ(list.Back(), 4);

  std::vector<int> values;
  for (auto it = list.Begin(); it != list.End(); ++it) {
    values.push_back(*it);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3, 4}));
}

TEST_F(ListTest, EraseAtBeginning) {
  List<int> list({1, 2, 3, 4}, resource);
  auto it = list.Begin();

  list.Erase(it);
  EXPECT_EQ(list.Size(), 3U);
  EXPECT_EQ(list.Front(), 2);

  std::vector<int> values;
  for (auto it = list.Begin(); it != list.End(); ++it) {
    values.push_back(*it);
  }
  EXPECT_EQ(values, std::vector<int>({2, 3, 4}));
}

TEST_F(ListTest, EraseInMiddle) {
  List<int> list({1, 2, 3, 4}, resource);
  auto it = list.Begin();
  ++it; // переходим к элементу 2
  ++it; // переходим к элементу 3

  list.Erase(it);
  EXPECT_EQ(list.Size(), 3U);

  std::vector<int> values;
  for (auto it = list.Begin(); it != list.End(); ++it) {
    values.push_back(*it);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 4}));
}

TEST_F(ListTest, EraseAtEnd) {
  List<int> list({1, 2, 3, 4}, resource);
  auto it = list.Begin();
  ++it;
  ++it;
  ++it; // переходим к последнему элементу 4

  list.Erase(it);
  EXPECT_EQ(list.Size(), 3U);
  EXPECT_EQ(list.Back(), 3);

  std::vector<int> values;
  for (auto it = list.Begin(); it != list.End(); ++it) {
    values.push_back(*it);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3}));
}

TEST_F(ListTest, EraseSingleElement) {
  List<int> list({42}, resource);
  auto it = list.Begin();

  list.Erase(it);
  EXPECT_TRUE(list.IsEmpty());
  EXPECT_EQ(list.Size(), 0U);
}

// Тесты копирования
TEST_F(ListTest, CopyConstructor) {
  List<int> original({1, 2, 3, 4}, resource);
  List<int> copy(original);

  EXPECT_EQ(original.Size(), copy.Size());

  auto orig_it = original.Begin();
  auto copy_it = copy.Begin();
  while (orig_it != original.End() && copy_it != copy.End()) {
    EXPECT_EQ(*orig_it, *copy_it);
    ++orig_it;
    ++copy_it;
  }
}

TEST_F(ListTest, CopyAssignment) {
  List<int> original({1, 2, 3, 4}, resource);
  List<int> copy(resource);
  copy = original;

  EXPECT_EQ(original.Size(), copy.Size());

  auto orig_it = original.Begin();
  auto copy_it = copy.Begin();
  while (orig_it != original.End() && copy_it != copy.End()) {
    EXPECT_EQ(*orig_it, *copy_it);
    ++orig_it;
    ++copy_it;
  }
}

TEST_F(ListTest, SelfAssignment) {
  List<int> list({1, 2, 3}, resource);
  list = list; // self-assignment

  EXPECT_EQ(list.Size(), 3U);
  std::vector<int> values;
  for (auto it = list.Begin(); it != list.End(); ++it) {
    values.push_back(*it);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3}));
}

// Тесты очистки
TEST_F(ListTest, Clear) {
  List<int> list({1, 2, 3, 4, 5}, resource);

  EXPECT_FALSE(list.IsEmpty());
  list.Clear();
  EXPECT_TRUE(list.IsEmpty());
  EXPECT_EQ(list.Size(), 0U);
}

TEST_F(ListTest, ClearEmptyList) {
  List<int> list(resource);

  list.Clear();
  EXPECT_TRUE(list.IsEmpty());
  EXPECT_EQ(list.Size(), 0U);
}

// Тесты исключений
TEST_F(ListTest, FrontOnEmptyList) {
  List<int> list(resource);

  EXPECT_THROW(list.Front(), ListIsEmptyException);
}

TEST_F(ListTest, BackOnEmptyList) {
  List<int> list(resource);

  EXPECT_THROW(list.Back(), ListIsEmptyException);
}

TEST_F(ListTest, PopBackOnEmptyList) {
  List<int> list(resource);

  EXPECT_THROW(list.PopBack(), ListIsEmptyException);
}

TEST_F(ListTest, PopFrontOnEmptyList) {
  List<int> list(resource);

  EXPECT_THROW(list.PopFront(), ListIsEmptyException);
}

TEST_F(ListTest, EraseOnEmptyList) {
  List<int> list(resource);
  auto it = list.Begin();

  EXPECT_THROW(list.Erase(it), ListIsEmptyException);
}

TEST_F(ListTest, IteratorDereferenceEnd) {
  List<int> list(resource);
  auto it = list.End();

  EXPECT_THROW(*it, ListIsEmptyException);
}

TEST_F(ListTest, IteratorArrowEnd) {
  List<int> list(resource);
  auto it = list.End();

  EXPECT_THROW(it.operator->(), ListIsEmptyException);
}

// Тесты с пользовательскими типами
struct Point {
  int x, y;
  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}
  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
};

TEST_F(ListTest, CustomType) {
  List<Point> list(resource);
  list.PushBack(Point(1, 2));
  list.PushBack(Point(3, 4));
  list.PushFront(Point(0, 0));

  EXPECT_EQ(list.Size(), 3U);
  EXPECT_EQ(list.Front(), Point(0, 0));
  EXPECT_EQ(list.Back(), Point(3, 4));

  auto it = list.Find(Point(1, 2));
  EXPECT_NE(it, list.End());
  EXPECT_EQ(*it, Point(1, 2));
}

// Тесты с памятью
TEST_F(ListTest, MemoryResourceUsage) {
  FixedBlockMemoryResource small_resource(64); // маленький блок
  List<int> list(&small_resource);

  // Добавляем элементы, пока не исчерпаем память
  bool exception_thrown = false;
  try {
    for (int i = 0; i < 100; ++i) {
      list.PushBack(i);
    }
  } catch (const ListIsEmptyException &) {
    exception_thrown = true;
  }

  // Ожидаем, что память закончится
  EXPECT_TRUE(exception_thrown || list.Size() < 100);
}

// Тесты на граничные случаи
TEST_F(ListTest, SingleElementList) {
  List<int> list({42}, resource);

  EXPECT_EQ(list.Size(), 1U);
  EXPECT_EQ(list.Front(), 42);
  EXPECT_EQ(list.Back(), 42);
  EXPECT_FALSE(list.IsEmpty());

  auto it = list.Begin();
  EXPECT_EQ(*it, 42);
  ++it;
  EXPECT_EQ(it, list.End());
}

TEST_F(ListTest, LargeList) {
  FixedBlockMemoryResource large_resource(1024 * 1024);
  List<int> list(&large_resource);
  const int N = 1000;

  for (int i = 0; i < N; ++i) {
    list.PushBack(i);
  }

  EXPECT_EQ(list.Size(), N);
  EXPECT_EQ(list.Front(), 0);
  EXPECT_EQ(list.Back(), N - 1);

  int count = 0;
  for (auto it = list.Begin(); it != list.End(); ++it) {
    EXPECT_EQ(*it, count);
    ++count;
  }
  EXPECT_EQ(count, N);
}