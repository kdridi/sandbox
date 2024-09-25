#pragma once

#include <core/module/module.h>

#include <optional>
#include <string>

namespace core {
    class EnvVars : public Module {
    public:
        static EnvVars &GetInstance();

        virtual std::optional<std::string> get(const std::string &_name) const = 0;
    };
} // namespace core

#define ENV_VARS_GET(name) core::EnvVars::GetInstance().get(name)
