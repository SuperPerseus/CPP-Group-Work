#include"head.h"
#include"include.h"

int main() {//�ӵ�¼���ƣ�������
    Login logorregister;
    
    switch (stoi((logorregister.returnuser())->returntype())) {
        case 1: {
            
            Server server(logorregister.returnuser());
            server.menu();
            break;
        }
        case 2: {
            Backend bk(logorregister.returnuser());
            break;
        }           
        case 3: {
            Backend bk(logorregister.returnuser());
            break;
        }
    }
    return 0;
}