#include <greet2/greet2.h>

#include <fmt/core.h>

std::string greet(const std::string& name) {
    return fmt::format("Hello World: {}\n", name);
}
