#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace arykow::assets {
    class Loader {
    private:
        bool m_initialized{false};

        Loader() = default;
        ~Loader();

    public:
        Loader(const Loader &) = delete;
        Loader &operator=(const Loader &) = delete;

        static Loader &GetInstance();

        void initialize(int argc, const char *argv[]);

        std::vector<uint8_t> getFileData(const std::string &_path);

    private:
        const char *parsePath(int argc, const char *argv[]);
    };
} // namespace arykow::assets

#define ARYKOW_ASSETS_INIT(argc, argv) arykow::assets::Loader::GetInstance().initialize(argc, argv)
#define ARYKOW_ASSETS_LOAD(path) arykow::assets::Loader::GetInstance().getFileData(path)