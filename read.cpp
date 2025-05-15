#include "ipc.hpp"

namespace ipc_backend = auto_system_api::ipc::backend;

int main()
{
  const std::string shm_name = "autosystem_lidarpoints";
  const auto [ptr, fd] = ipc_backend::posix_shm_get_addr(shm_name, 4096);

  printf("[Reader] Read message: %s\n", static_cast<char *>(ptr));

  ipc_backend::posix_shm_close(ptr, 4096, fd);
  ipc_backend::posix_shm_remove(shm_name);

  return 0;
}
