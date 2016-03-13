
#include "deps.hpp"
#include "vulkan_deps.hpp"
#include "window.hpp"

int main(const int argc, const char *argv[])
{
        feather::vulkan::Window* window = new feather::vulkan::Window();
        delete(window);
        return 0;
}
