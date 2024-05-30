#include"head.h"
#include"include.h"

int main() {
    Login logorregister;
    //cout << "the token is " << logorregister.returnToken() << endl;
    //cout << "the id is " << (logorregister.returnuser())->returnid() << endl;
    File file;
    switch (stoi((logorregister.returnuser())->returntype())) {
    case 1:

        break;
    case 2:
        break;
    case 3:
        Backend bk(logorregister.returnuser());
        cout << bk.returnuser().returnid() << endl;
        break;

    }
    return 0;
}