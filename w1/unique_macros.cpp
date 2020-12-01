#include <iostream>
using namespace std;
#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID_IMPL_TMP(lineno) UNIQ_ID_IMPL(lineno)
#define UNIQ_ID UNIQ_ID_IMPL_TMP(__LINE__)

int main() {
    int UNIQ_ID = 5;
    string UNIQ_ID = "hello!";
}