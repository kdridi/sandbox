#pragma once

#include <core/module/module.h>

#include <cstdint>
#include <string>
#include <vector>

namespace assets {
    class Loader : public core::Module {
    public:
        static Loader &GetInstance();

        virtual std::vector<uint8_t> getFileData(const std::string &_path) = 0;
    };
} // namespace assets

#define ASSETS_INIT(argc, argv) assets::Loader::GetInstance().initialize(argc, argv)
#define ASSETS_LOAD(path) assets::Loader::GetInstance().getFileData(path)