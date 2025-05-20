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
  const auto shm_fd = shm_open(name.c_str(), O_RDWR | O_CREAT, S_IRWXU);
  if (shm_fd == -1) {
    throw std::runtime_error("Failed to open shared memory(" + name + "):" + std::strerror(errno));
  }

  if (ftruncate(shm_fd, size) == -1) {
    shm_unlink(name.c_str());
    throw std::runtime_error(
      "Failed to set size for shared memory(" + name + "):" + std::strerror(errno));
  }

  const auto ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    shm_unlink(name.c_str());
    throw std::runtime_error("Failed to map shared memory(" + name + "):" + std::strerror(errno));
  }

  std::fill_n(static_cast<char *>(ptr), size, 0);
  posix_shm_close(ptr, size, shm_fd);
}

auto posix_shm_get_addr(const std::string & name, int64_t size, bool is_write)
  -> std::pair<void *, int>
{
  const auto shm_fd = shm_open(name.c_str(), is_write ? O_RDWR : O_RDONLY, S_IRWXU);
  if (shm_fd == -1) {
    throw std::runtime_error("Failed to open shared memory(" + name + "):" + std::strerror(errno));
  }

  const auto ptr = mmap(0, size, is_write ? PROT_WRITE : PROT_READ, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    shm_unlink(name.c_str());
    throw std::runtime_error("Failed to map shared memory(" + name + "):" + std::strerror(errno));
  }

  return std::make_pair(ptr, shm_fd);
}

void posix_shm_dispose(const std::string & name)
{
  if (shm_unlink(name.c_str()) == -1) {
    throw std::runtime_error(
      "Failed to dispose shared memory(" + name + "):" + std::strerror(errno));
  }
}

void posix_shm_name_check(const std::string & name)
{
  const auto isLowerSnakeCase = [](const std::string & name) {
    if (name.empty() || name.front() == '_' || name.back() == '_') {
      return false;
    }

    bool prevUnderscore = false;
    for (char ch : name) {
      if (ch == '_') {
        if (prevUnderscore) return false;
        prevUnderscore = true;
      } else {
        if (!std::isalpha(ch) || !std::islower(ch)) return false;
        prevUnderscore = false;
      }
    }
    return true;
  };

  if (name.length() > 128) {
    throw std::runtime_error(name + " is too long.");
  }

  if (!isLowerSnakeCase(name)) {
    throw std::runtime_error(
      name + " is not in lower_snake_case. SHM names must be in lower_snake_case.");
  }
}

void posix_mq_create(const std::string & name)
{
  const auto queue = mq_open(name.c_str(), O_CREAT | O_EXCL | O_RDONLY, S_IRWXU, NULL);
  if (queue == -1) {
    throw std::runtime_error(
      "Failed to create message queue(" + name + "):" + std::strerror(errno));
  }
  mq_close(queue);
}

void posix_mq_send(const std::string & name, const void * payload, int64_t size)
{
  const auto payload_ptr = static_cast<const char *>(payload);

  const auto queue = mq_open(name.c_str(), O_WRONLY | O_EXCL, S_IRWXU, NULL);
  if (queue == -1) {
    throw std::runtime_error("Failed to open message queue(" + name + "):" + std::strerror(errno));
  }
  if (mq_send(queue, payload_ptr, size, 0) == -1) {
    throw std::runtime_error("Failed to send message queue(" + name + "):" + std::strerror(errno));
  }
  mq_close(queue);
}

void posix_mq_dispose(const std::string & name)
{
  if (mq_unlink(name.c_str()) == -1) {
    throw std::runtime_error(
      "Failed to dispose message queue (" + name + "):" + std::strerror(errno));
  }
}
}  // namespace backend
}  // namespace ipc
}  // namespace auto_system_api
