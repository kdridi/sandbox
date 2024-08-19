#include "arykow/PathSolver.h"

#include <spdlog/spdlog.h>

namespace arykow
{
    PathSolver::~PathSolver()
    {
        if (m_execPath)
            m_execPath = {};
    }

    PathSolver &PathSolver::GetInstance()
    {
        static PathSolver instance;
        return instance;
    }

    void PathSolver::initialize(const std::string &_argv0)
    {
        assert(!m_execPath && "PathSolver::initialize() called twice");
        if (m_execPath)
        {
            spdlog::warn("PathSolver::initialize() called twice");
            return;
        }

        m_execPath = std::filesystem::absolute(_argv0).parent_path();
        spdlog::info("PathSolver::initialize() Executable path: {}", m_execPath->string());
    }

    std::string PathSolver::solve(const std::string &_path)
    {
        return (*m_execPath / _path).string();
    }
} // namespace arykow
