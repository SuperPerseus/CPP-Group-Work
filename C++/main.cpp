#pragma once
#include"head.h"
#include"include.h"
#include "backend.h"

int main() {//¼ÓµÇÂ¼¿ØÖÆ£¬ÊäÈë¼ì²â
    cout << errorcode << endl;
    cout << endl;
    cout << endl;
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
            bool modechoose = false;
            while (!modechoose) {
                cout << "if you want to register a new manager ,please enter 1" << endl;
                cout << "if you want to get in the backend ,please enter 2" << endl;
                int a = getValidInt();
                switch (a) {
                    case 1: {
                        logorregister.managermode();                        
                        break;
                    }
                    case 2: {
                        modechoose = true;
                        break;
                    }
                    default:
                        cout << "invalid input ,try again " << endl;
                }
            }           
            Backend bk(logorregister.returnuser(), logorregister.returnToken());
            break;
        }
    }
    cout << endl;
    cout << "program end successfully " << endl;
    return 0;
}