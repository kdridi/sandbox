#include "Loader.h"

#include <physfs.h>
#include <filesystem>
#include <cassert>
#include <fmt/core.h>

namespace arykow::assets
{
    Loader::~Loader()
    {
        if (m_initialized)
        {
            PHYSFS_deinit();
        }
    }

    Loader &Loader::GetInstance()
    {
        static Loader instance;
        return instance;
    }

    void Loader::initialize(const std::string &_path)
    {
        assert(!m_initialized && "Loader::initialize() called twice");
        if (m_initialized)
        {
            fmt::print("Loader::initialize() called twice\n");
            return;
        }

        if (!PHYSFS_init(_path.c_str()))
        {
            fmt::print("Loader::initialize() Error initializing PhysFS: {}\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
            return;
        }

        std::filesystem::path execPath = std::filesystem::absolute(_path.c_str()).parent_path();
        fmt::print("Loader::initialize() Executable path: {}\n", execPath.string());

        std::string zipPath = (execPath / "assets.zip").string();
        fmt::print("Loader::initialize() ZIP file path: {}\n", zipPath);

        if (!PHYSFS_mount(zipPath.c_str(), nullptr, 1))
        {
            fmt::print("Loader::initialize() Error while mounting ZIP file: {}\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
            return;
        }

        m_initialized = true;
    }

    std::vector<unsigned char> Loader::getFileData(const std::string &_path)
    {
        PHYSFS_File *file = PHYSFS_openRead(_path.c_str());
        if (!file)
        {
            fmt::print("Loader::getFileData() Error while loading file '{}': {}\n", _path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
            return {};
        }

        std::vector<unsigned char> bytes(PHYSFS_fileLength(file));
        PHYSFS_readBytes(file, bytes.data(), bytes.size());
        PHYSFS_close(file);

        return bytes;
    }
} // namespace arykow
