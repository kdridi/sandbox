#pragma once

#include <filesystem>
#include <optional>

namespace arykow
{
    class PathSolver
    {
    private:
        std::optional<std::filesystem::path> m_execPath;

        PathSolver() = default;
        ~PathSolver();

    public:
        PathSolver(const PathSolver &) = delete;
        PathSolver &operator=(const PathSolver &) = delete;

        static PathSolver &GetInstance();

        void initialize(const std::string &_argv0);

        std::string solve(const std::string &_path);
    };
} // namespace arykow

#define ARYKOW_PATHSOLVER_INIT(argv0) arykow::PathSolver::GetInstance().initialize(argv0)
#define ARYKOW_PATHSOLVER_SOLVE(path) arykow::PathSolver::GetInstance().solve(path)
