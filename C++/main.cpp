#include"head.h"
#include"include.h"

int main() {
    Login logorregister;
    cout << logorregister.returnToken();
    cout << (logorregister.returnuser())->id()<<endl;
    cout << (logorregister.returnuser())->returnname() << endl;
    return 0;
}