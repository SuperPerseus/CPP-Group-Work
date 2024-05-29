#include"head.h"
#include"include.h"

using namespace std;

int main() {
    User u("tom","123","customer");
    Login log(u);
    u = log.returnU();
    cout << u.username << endl;
}