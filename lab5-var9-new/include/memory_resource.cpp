#include "memory_resource.hpp"

void *FixedBlockMemoryResource::FindBestFit(size_t bytes) {
  auto it = free_blocks_by_size_.lower_bound(bytes);
  if (it != free_blocks_by_size_.end()) {
    auto &free_map = it->second;
    auto free_it = free_map.begin();
    if (free_it != free_map.end() && !free_it->second) {
      void *ptr = free_it->first;
      free_it->second = true;
      if (free_map.size() == 1) {
        free_blocks_by_size_.erase(it);
      } else {
        free_map.erase(free_it);
      }
      return ptr;
    }
  }
  return nullptr;
}

void FixedBlockMemoryResource::AddFreeBlock(void *ptr, size_t bytes) {
  if (bytes == 0)
    return;
  auto &free_map = free_blocks_by_size_[bytes];
  free_map[ptr] = false;
}

void *FixedBlockMemoryResource::do_allocate(size_t bytes, size_t alignment) {
  if (bytes == 0) {
    return nullptr;
  }

  size_t aligned_bytes = (bytes + alignment - 1) / alignment * alignment;

  void *ptr = FindBestFit(aligned_bytes);
  if (ptr) {
    allocated_blocks_[ptr] = aligned_bytes;
    return ptr;
  }

  size_t required_space = current_allocated_size_ + aligned_bytes;
  if (required_space > block_size_) {
    throw ListIsEmptyException("FixedBlockMemoryResource: Out of memory");
  }

  void *new_ptr = memory_block_ + current_allocated_size_;
  current_allocated_size_ += aligned_bytes;

  allocated_blocks_[new_ptr] = aligned_bytes;
  return new_ptr;
}

void FixedBlockMemoryResource::do_deallocate(void *ptr, size_t bytes,
                                             size_t alignment) {
  if (ptr == nullptr || bytes == 0) {
    return;
  }

  if (ptr < memory_block_ || ptr >= memory_block_ + block_size_) {
    return;
  }

  auto it = allocated_blocks_.find(ptr);
  if (it != allocated_blocks_.end() && it->second == bytes) {
    allocated_blocks_.erase(it);
    AddFreeBlock(ptr, bytes);
  }
}

bool FixedBlockMemoryResource::do_is_equal(
    const std::pmr::memory_resource &other) const noexcept {
  return this == &other;
}

FixedBlockMemoryResource::FixedBlockMemoryResource(size_t pool_size)
    : block_size_(pool_size) {
  memory_block_ = static_cast<char *>(std::malloc(block_size_));
  if (!memory_block_) {
    throw ListIsEmptyException("Failed to allocate fixed memory block\n");
  }
}

FixedBlockMemoryResource::~FixedBlockMemoryResource() {
  std::free(memory_block_);
  memory_block_ = nullptr;
}