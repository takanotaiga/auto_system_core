#pragma once

#include <fcntl.h>
#include <mqueue.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstring>
#include <stdexcept>
#include <string>

namespace auto_system_api
{
namespace ipc
{
namespace backend
{
void posix_shm_close(void * ptr, int64_t size, int fd);

void posix_shm_allocate(const std::string & name, int64_t size);

auto posix_shm_get_addr(const std::string & name, int64_t size, bool is_write = false)
  -> std::pair<void *, int>;

void posix_shm_dispose(const std::string & name);

void posix_shm_name_check(const std::string & name);

void posix_mq_create(const std::string & name);

void posix_mq_send(const std::string & name, const void * payload, int64_t size);

void posix_mq_dispose(const std::string & name);

}  // namespace backend
}  // namespace ipc
}  // namespace auto_system_api
