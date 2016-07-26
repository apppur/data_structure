#include <iostream>
#include "kmp.h"

int main(int argc, char ** argv) {
    KMP kmp("apple purple love you!", "purpur");
    //kmp.InitNext();
    kmp.Next();
    int result = kmp.Search();
    std::cout << result << std::endl;
    return 0;
}
