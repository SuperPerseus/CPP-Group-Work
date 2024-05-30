#include"head.h"
#include"include.h"

int main() {
    Login logorregister;
    cout << logorregister.returnToken() << endl;
    cout << (logorregister.returnuser())->id()<<endl;
    cout << (logorregister.returnuser())->returnname() << endl;
    return 0;
}