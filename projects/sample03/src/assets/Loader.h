#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace assets {
    class Loader {
    public:
        static Loader &GetInstance();

        virtual void initialize(int argc, const char *argv[]) = 0;
        virtual std::vector<uint8_t> getFileData(const std::string &_path) = 0;
    };
} // namespace assets

#define ASSETS_INIT(argc, argv) assets::Loader::GetInstance().initialize(argc, argv)
#define ASSETS_LOAD(path) assets::Loader::GetInstance().getFileData(path)