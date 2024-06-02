#pragma once
#include"head.h"
#include"include.h"

int main() {//¼ÓµÇÂ¼¿ØÖÆ£¬ÊäÈë¼ì²â
    Login logorregister;
    
    switch (stoi((logorregister.returnuser())->returntype())) {
        case 1: {            
            Server server(logorregister.returnuser());
            server.menu();
            break;
        }
        case 2: {
            Backend bk(logorregister.returnuser(), logorregister.returnToken());
            break;
        }           
        case 3: {
            Backend bk(logorregister.returnuser(), logorregister.returnToken());
            break;
        }
    }
    cout << endl;
    cout << "program end successfully " << endl;
    return 0;
}