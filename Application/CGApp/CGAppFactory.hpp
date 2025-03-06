#pragma once
#include <string>
#include <memory>
#include "SimpleCGApp.hpp"

using std::make_unique;
using std::unique_ptr;
using std::string;

namespace jfj
{

    class CGAppFactory
    {
        public:
        static unique_ptr<CGApp> CreateCGApp(const string& app_name)
        {
            if (app_name.compare("simple") == 0)
            {
                return make_unique<SimpleCGApp>();
            }
            return nullptr;
        }
        CGAppFactory() = delete;
        ~CGAppFactory() = delete;
    }


} // end of namespace jfj
