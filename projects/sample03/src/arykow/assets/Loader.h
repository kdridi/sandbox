#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace arykow::assets
{
    class Loader
    {
    private:
        bool m_initialized{false};

        Loader() = default;
        ~Loader();

    public:
        Loader(const Loader &) = delete;
        Loader &operator=(const Loader &) = delete;

        static Loader &GetInstance();

        void initialize(const std::string &_path);

        std::vector<uint8_t> getFileData(const std::string &_path);
    };
} // namespace arykow::assets

#define ARYKOW_ASSETS_INIT(zipFile) arykow::assets::Loader::GetInstance().initialize(zipFile)
#define ARYKOW_ASSETS_LOAD(path) arykow::assets::Loader::GetInstance().getFileData(path)