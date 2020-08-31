#pragma once

#include <memory.h>

namespace corgi
{
    template<class T>
    using UniquePtr = std::unique_ptr<T>;
}