#include "auto_system_api/backend/ipc_backend.hpp"

#include <gtest/gtest.h>

namespace ipc_backend = auto_system_api::ipc::backend;

TEST(PosixShmLifecycle, SimpleShardMemoryCheck)
{
  int before, after;

  {
    const std::string shm_name = "autosystem_lidarpoints";
    ipc_backend::posix_shm_allocate(shm_name, 4096);
    const auto [ptr, fd] = ipc_backend::posix_shm_get_addr(shm_name, 4096, true);

    int & memptr = *static_cast<int *>(ptr);
    memptr = 10;
    before = memptr;
    ipc_backend::posix_shm_close(ptr, 4096, fd);
  }

  {
    const std::string shm_name = "autosystem_lidarpoints";
    const auto [ptr, fd] = ipc_backend::posix_shm_get_addr(shm_name, 4096);

    after = *static_cast<int *>(ptr);
    ipc_backend::posix_shm_close(ptr, 4096, fd);
    ipc_backend::posix_shm_dispose(shm_name);
  }

  EXPECT_EQ(before, after);
}

TEST(PosixShmGetAddr, NonexistentNameThrows)
{
  EXPECT_THROW(
    ipc_backend::posix_shm_get_addr("nonexistent_shm_name", 512, /*is_write=*/false),
    std::runtime_error);
}

TEST(PosixShmNameCheck, ValidNames)
{
  EXPECT_NO_THROW(ipc_backend::posix_shm_name_check("valid_name"));
  EXPECT_NO_THROW(ipc_backend::posix_shm_name_check("a"));
  EXPECT_NO_THROW(ipc_backend::posix_shm_name_check(std::string(128, 'a')));
}

TEST(PosixShmNameCheck, TooLongName)
{
  std::string too_long(129, 'a');
  EXPECT_THROW(ipc_backend::posix_shm_name_check(too_long), std::runtime_error);
}

TEST(PosixShmNameCheck, InvalidCharacters)
{
  EXPECT_THROW(ipc_backend::posix_shm_name_check("_start_underscore"), std::runtime_error);
  EXPECT_THROW(ipc_backend::posix_shm_name_check("end_underscore_"), std::runtime_error);
  EXPECT_THROW(ipc_backend::posix_shm_name_check("double__underscore"), std::runtime_error);
  EXPECT_THROW(ipc_backend::posix_shm_name_check("HasUpperCase"), std::runtime_error);
}

TEST(PosixMQLifecycle, SimpleMQCheck)
{
  const auto mq_name = "/autosystem_mq";
  EXPECT_NO_THROW(ipc_backend::posix_mq_create(mq_name));
  EXPECT_THROW(ipc_backend::posix_mq_create(mq_name), std::runtime_error);
  EXPECT_NO_THROW(ipc_backend::posix_mq_dispose(mq_name));
  EXPECT_THROW(ipc_backend::posix_mq_dispose(mq_name), std::runtime_error);
}