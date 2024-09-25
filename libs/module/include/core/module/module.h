#pragma once

namespace core {
    class Modules;

    class Module {
    public:
        virtual void init(int argc, const char *argv[], const char *envp[]) = 0;

    private:
        class IRegisterer {
        public:
            IRegisterer(Module &_module);
        };

        friend class Modules;

    public:
        template <typename T>
        class Registerer : private IRegisterer {
        public:
            Registerer();
        };
    };

    class Modules {
    public:
        static bool Start(int argc, const char *argv[], const char *envp[]);

    private:
        static bool Register(Module &module);

        friend class Module::IRegisterer;
    };

    template <typename T>
    Module::Registerer<T>::Registerer()
        : IRegisterer(T::GetInstance())
    {
    }
} // namespace core

#define MODULES_START(argc, argv, envp) core::Modules::Start(argc, argv, envp)
