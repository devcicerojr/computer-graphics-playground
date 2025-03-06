#pragma once
#include "CGApp.hpp"

namespace jfj
{

class SimpleCGApp : public CGApp
{
private:
public:
    SimpleCGApp() = default;
    ~SimpleCGApp() = default;
    void init(void) override;
    void exec(void) override;

};

} // end of namespace jfj
