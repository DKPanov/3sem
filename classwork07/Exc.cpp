
#include<iostream>
#include<exception>
#include<string>

struct base_exception : public std::exception {}; //метод what уже есть в std::exception

struct math_exception final : public base_exception{
    static const char WHAT[];
    const char* what() const noexcept override { //метод what в std::exception описан как const
        return WHAT;                             //noexcept - значит мы в методе what не будем кидать исключкния 
    }
};
const char math_exception::WHAT[] = "Divided by zero";

struct invalid_argument final : public base_exception{
    static const char WHAT[];
    const char* what() const noexcept override { //метод what в std::exception описан как const
        return WHAT;                             //noexcept - значит мы в методе what не будем кидать исключкния 
    }
};
const char invalid_argument::WHAT[] = "Less than zero";

double inverse(double x) {
    if (x == 0)
        throw math_exception();
    return 1. / x;
}

double root(double x) {
    if (x < 0)
        throw invalid_argument();
    return std::sqrt(x);
}

int main(){
    try {
        inverse(0);
    }
    catch(const base_exception& exc) {
        std::cout << exc.what() << std::endl;           //в std::exception метод what() виртуальный
        //throw;
    }

    try {
        root(-4);
    }
    catch (const invalid_argument& exc) {
        std::cout << exc.what();
    }

    return 0;
}
