#include <iostream>
#include <memory>
#include "Application/CGApp/CGAppFactory.hpp"

using std::unique_ptr;
using std::make_unique;


unique_ptr<jfj::CGApp> CreateCGApp(void)
{
	return make_unique<jfj::SimpleCGApp>();
}

int main() {
	
	unique_ptr<jfj::CGApp> cg_app = jfj::CGAppFactory::CreateCGApp("simple");
	if (cg_app)
	{
		cg_app->init();
		cg_app->exec();
	}

	return 0;
}
