#include <core/pathSolver/pathSolver.h>

#include <spdlog/spdlog.h>

namespace core {

    class PathSolverImpl : public PathSolver {
    private:
        std::optional<std::filesystem::path> m_execPath;

    public:
        PathSolverImpl() = default;
        ~PathSolverImpl();

        void initialize(int argc, const char *argv[]) override final;
        std::string solve(const std::string &_path) override final;

    private:
        const char *parsePath(int argc, const char *argv[]);
    };

    PathSolver &PathSolver::GetInstance()
    {
        static PathSolverImpl instance;
        return instance;
    }

    PathSolverImpl::~PathSolverImpl()
    {
        if (m_execPath)
            m_execPath = {};
    }

    void PathSolverImpl::initialize(int argc, const char *argv[])
    {
        assert(!m_execPath && "Called twice");
        if (m_execPath) {
            spdlog::warn("PathSolver::initialize() Error -- Called twice");
            return;
        }

        const char *path = parsePath(argc, argv);
        assert(path != nullptr && "Bad Argument");
        if (path == nullptr) {

            spdlog::warn("PathSolver::initialize() Error -- Bad Argument");
            return;
        }

        m_execPath = std::filesystem::absolute(path).parent_path();
        spdlog::info("PathSolver::initialize() Executable path: {}", m_execPath->string());
    }

    std::string PathSolverImpl::solve(const std::string &_path)
    {
        return (*m_execPath / _path).string();
    }

    const char *PathSolverImpl::parsePath(int argc, const char *argv[])
    {
        if (argc == 0)
            return nullptr;
        return *argv;
    }
} // namespace core
