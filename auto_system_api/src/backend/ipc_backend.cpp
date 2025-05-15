#include "auto_system_api/backend/ipc_backend.hpp"

namespace auto_system_api
{
namespace ipc
{
namespace backend
{
void posix_shm_close(void * ptr, int64_t size, int fd)
{
  munmap(ptr, size);
  close(fd);
}

void posix_shm_allocate(const std::string & name, int64_t size)
{
  const auto shm_fd = shm_open(name.c_str(), O_RDWR | O_CREAT, 0666);
  if (shm_fd == -1) {
    throw std::runtime_error("Failed to open shared memory: " + name);
  }

  if (ftruncate(shm_fd, size) == -1) {
    shm_unlink(name.c_str());
    throw std::runtime_error("Failed to set size for shared memory: " + name);
  }

  const auto ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    shm_unlink(name.c_str());
    throw std::runtime_error("Failed to map shared memory: " + name);
  }

  std::fill_n(static_cast<char *>(ptr), size, 0);
  posix_shm_close(ptr, size, shm_fd);
}

auto posix_shm_get_addr(const std::string & name, int64_t size, bool is_write)
  -> std::pair<void *, int>
{
  const auto shm_fd = shm_open(name.c_str(), is_write ? O_RDWR : O_RDONLY, 0666);
  if (shm_fd == -1) {
    throw std::runtime_error("Failed to open shared memory: " + name);
  }

  const auto ptr = mmap(0, size, is_write ? PROT_WRITE : PROT_READ, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    shm_unlink(name.c_str());
    throw std::runtime_error("Failed to map shared memory: " + name);
  }

  return std::make_pair(ptr, shm_fd);
}

void posix_shm_remove(const std::string & name)
{
  if (shm_unlink(name.c_str()) == -1) {
    throw std::runtime_error("Failed to unlink shared memory: " + name);
  }
}
}  // namespace backend
}  // namespace ipc
}  // namespace auto_system_api