#include <gtest/gtest.h>

#include "auto_system_api/backend/ipc_backend.hpp"

namespace ipc_backend = auto_system_api::ipc::backend;

TEST(IPC_Test, SimpleShardMemoryCheck) {
    int before, after;

    {    
        const std::string shm_name = "autosystem_lidarpoints";
        ipc_backend::posix_shm_allocate(shm_name, 4096);
        const auto [ptr, fd] = ipc_backend::posix_shm_get_addr(shm_name, 4096, true);

        int * memptr = static_cast<int *>(ptr);
        *memptr = 10;
        before = *memptr;
        printf("[Writer] Wrote message: %d\n", *memptr);

        ipc_backend::posix_shm_close(ptr, 4096, fd);

    }

    {
        const std::string shm_name = "autosystem_lidarpoints";
        const auto [ptr, fd] = ipc_backend::posix_shm_get_addr(shm_name, 4096);

        after = *static_cast<int *>(ptr);
        printf("[Reader] Read message: %d\n", *static_cast<int *>(ptr));


        ipc_backend::posix_shm_close(ptr, 4096, fd);
        ipc_backend::posix_shm_remove(shm_name);
    }

    EXPECT_EQ(before, after);
}
