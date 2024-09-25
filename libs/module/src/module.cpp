#include <core/module/module.h>

#include <spdlog/spdlog.h>

#include <vector>

namespace core {
    std::vector<Module *> &GetModules()
    {
        static std::vector<Module *> modules;
        return modules;
    }

    Module::IRegisterer::IRegisterer(Module &_module)
    {
        Modules::Register(_module);
    }

    bool Modules::Start(int argc, const char *argv[], const char *envp[])
    {
        spdlog::info("Starting modules");

        for (auto &module : GetModules()) {
            module->init(argc, argv, envp);
        }

        return true;
    }

    bool Modules::Register(Module &module)
    {
        GetModules().push_back(&module);
        return true;
    }
} // namespace core
