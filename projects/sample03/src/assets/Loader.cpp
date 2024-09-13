#include "Loader.h"

#include <cassert>
#include <filesystem>
#include <fmt/core.h>
#include <physfs.h>

namespace arykow::assets {
    Loader::~Loader()
    {
        if (!m_initialized)
            return;

        PHYSFS_deinit();
    }

    Loader &Loader::GetInstance()
    {
        static Loader instance;
        return instance;
    }

    void Loader::initialize(int argc, const char *argv[])
    {
        assert(!m_initialized && "Already initialized");
        if (m_initialized) {
            fmt::print("Loader::initialize() Error -- Already initialized");
            return;
        }

        const char *const path{parsePath(argc, argv)};
        assert(path && "Bad Argument");
        if (!path) {
            fmt::print("Loader::initialize() Error -- Bad Argument");
            return;
        }

        if (!PHYSFS_init(path)) {
            fmt::print("Loader::initialize() Error initializing PhysFS: {}\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
            return;
        }

        std::filesystem::path execPath = std::filesystem::absolute(path).parent_path();
        fmt::print("Loader::initialize() Executable path: {}\n", execPath.string());

        std::string zipPath = (execPath / "assets.zip").string();
        fmt::print("Loader::initialize() ZIP file path: {}\n", zipPath);

        if (!PHYSFS_mount(zipPath.c_str(), nullptr, 1)) {
            fmt::print("Loader::initialize() Error while mounting ZIP file: {}\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
            return;
        }

        m_initialized = true;
    }

    std::vector<unsigned char> Loader::getFileData(const std::string &_path)
    {
        assert(m_initialized && "Not initialized");
        if (!m_initialized) {
            fmt::print("Loader::getFileData() Error -- Not initialized");
            return {};
        }

        PHYSFS_File *file = PHYSFS_openRead(_path.c_str());
        if (!file) {
            fmt::print("Loader::getFileData() Error while loading file '{}': {}\n", _path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
            return {};
        }

        const PHYSFS_sint64 length{PHYSFS_fileLength(file)};
        if (!(length <= UINT32_MAX)) {
            assert(false && "Bad file length");
            fmt::print("Loader::getFileData() Bad file length '{}': {}\n", _path, length);
            return {};
        }

        std::vector<unsigned char> bytes((unsigned int)length);
        PHYSFS_readBytes(file, bytes.data(), bytes.size());
        PHYSFS_close(file);

        return bytes;
    }

    const char *Loader::parsePath(int argc, const char *argv[])
    {
        if (argc == 0)
            return nullptr;
        return *argv;
    }
} // namespace arykow::assets
