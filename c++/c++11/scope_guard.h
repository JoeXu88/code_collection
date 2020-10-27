#pragma once

#include <functional>


class scope_guard
{
    private:
    std::function<void()> _exit_func;

    public:
    scope_guard(const std::function<void()>& f): _exit_func(f) {}
    ~scope_guard() { _exit_func(); }
};


#define nametify(x, y)  x##y
#define scope_name(x, y) nametify(x, y)
#define SCOPE_GUARD(f) scope_guard scope_name(scope_guard_, __LINE__)(f)
