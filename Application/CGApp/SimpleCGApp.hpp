#pragma once
#include "CGApp.hpp"
#include <memory>


class WindowHandler;
using std::unique_ptr;

namespace jfj
{

class SimpleCGApp : public CGApp
{
private:
    unique_ptr<WindowHandler> window_handler_;
    void theLoop(void);
    void createWindow(void);
public:
    SimpleCGApp() = default;
    ~SimpleCGApp() = default;
    void init(void) override;
    void exec(void) override;

};

} // end of namespace jfj
