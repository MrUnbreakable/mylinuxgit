#define FMT_STRING_ALIAS 1
#include "fmt/format.h"
#include "fmt/fmtchrono.h"
//#include "fmt/core.h"
//#include "fmt/compile.h"
#include "fmt/fmtprintf.h"
//#include "fmt/posix.h"
//#include "fmt/ranges.h"
#include "fmt/fmtcolor.h"
#include <iostream>
#include <ctime>
int main()
{
    std::string ns = "world";
    fmt::printf("Hello,%s\n",ns);
    
    fmt::print("Hello, {}!\n", "world");  // Python-like format string syntax
    
    std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
    std::cout << s << std::endl;
    fmt::print(stderr, "Don't {}!\n", "panic");
    fmt::print("Elapsed time: {s:.2f} seconds\n", fmt::arg("s", 1.23));
    std::vector<int> v = {1, 2, 3};
    fmt::print("{}\n", fmt::join(v, ", "));
    fmt::memory_buffer buf;
    fmt::format_to(buf, "{}", 42);
    fmt::format_to(buf, "{:x}", 42); // 十六进制表示
    std::cout << buf.data() << std::endl;
    std::time_t t = std::time(nullptr);
    fmt::print("The date is {:%Y-%m-%d}.\n", *std::localtime(&t));    
    fmt::print(fg(fmt::color::red),"Elapsed time: {0:.2f} seconds\n", 1.23);
    std::string message = fmt::sprintf("The answer is %d", 42);
    std::cout << message << std::endl;
}

