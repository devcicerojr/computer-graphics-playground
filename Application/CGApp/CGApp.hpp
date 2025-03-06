#pragma once

namespace jfj
{

class CGApp
{
private:
public:
    CGApp() = default;
    virtual ~CGApp() = default;
    virtual void init(void) = 0;
    virtual void exec(void) = 0;
};
    
} // end of namespace jfj
