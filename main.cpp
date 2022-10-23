#include <iostream>
#include "queen.h"

using namespace std;
int main(int argc, char* args[])
{
    Queens *queens = new Queens();
    const char* title = "Minhwang";
    if(queens->init(title)) {
        queens->Try(1);
    }
    else cout << "Error";
    queens->clean();
    SDL_Quit();
	return 0;
}
