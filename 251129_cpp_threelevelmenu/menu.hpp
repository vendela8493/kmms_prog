#pragma once

namespace rva {
    struct MenuItem {
        const char* const title;
        const MenuItem* (*func)(const MenuItem*);
        const MenuItem* parent;
        const MenuItem* const* children;
        const int children_count;
    };
}