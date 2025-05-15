#include "ipc.hpp"

#include <string.h>

namespace ipc_backend = auto_system_api::ipc::backend;

int main()
{
  const std::string shm_name = "autosystem_lidarpoints";
  ipc_backend::posix_shm_allocate(shm_name, 4096);
  const auto [ptr, fd] = ipc_backend::posix_shm_get_addr(shm_name, 4096, true);

  char * memptr = static_cast<char *>(ptr);
  strcpy(memptr, "HelloWorld");
  printf("[Writer] Wrote message: %s\n", memptr);

  ipc_backend::posix_shm_close(ptr, 4096, fd);
  return 0;
}
