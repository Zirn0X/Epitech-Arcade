/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** DyLib
*/

#include <dlfcn.h>
#include "Exception.hpp"

template <typename T>
class DLLoader {
    public:
        T *getInstance() {
            return _lib;
        }
        void setInstance(std::string nameLib) {
            _handle = dlopen(nameLib.c_str(), RTLD_LAZY);
            if (!_handle) {
                throw Error(dlerror());
            }
            void *(*entrypoint)() = (void*(*)())(dlsym(_handle, "entryPoint"));
            if (!entrypoint)
                throw Error(dlerror());
            _lib = static_cast<T*>(entrypoint());
        }
        void unload() {
            if (_lib)
                delete _lib;
            if (_handle)
                dlclose(_handle);
            _lib = nullptr;
            _handle = nullptr;
        }
    protected:
    private:
        T *_lib;
        void *_handle;
};