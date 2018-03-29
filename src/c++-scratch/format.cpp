#include<iostream>

int main()
{
    std::cout << "True is ";
    std::ios_base::fmtflags f = std::cout.flags(std::ios_base::boolalpha);
    f = std::cout.setf(std::ios_base::hex);
    f = std::cout.setf(std::ios_base::showbase);
    f = std::cout.setf(std::ios_base::showpoint);
    std::cout << true << ' ' << 0xabcd << ' ' << 123.0 << '\n';
    return 0;
}
