#pragma once

#include <core/module/module.h>

#include <fmt/core.h>

#include <filesystem>
#include <string>

namespace core {
    class PathSolver : public Module {
    public:
        static PathSolver &GetInstance();

        virtual std::filesystem::path solve(const std::filesystem::path &_path) = 0;
    };
} // namespace core

#define PATH_SOLVER_SOLVE(...) core::PathSolver::GetInstance().solve(fmt::format(__VA_ARGS__))
