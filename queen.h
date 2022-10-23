#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
class Queens
{
public:
    Queens()
    {
    }
    ~Queens()
    {
    }
    bool init(const char* title);
    void Try(int i);
    void res();
    void updateRender();
    void setRectPos(SDL_Rect& rect,int x = 0, int y = 0, int w = BlockW, int h = BlockH);
    void moveRectPos(SDL_Rect& rect,int x, int y);
    void loadFont(std::string text, SDL_Rect source, SDL_Rect destination);
    void clean();
private:
    enum {ScreenW = 1000, ScreenH = 1000};
    enum {BlockW = 125, BlockH = 125};
    enum {Line = 10, Column = 10};
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* background = NULL, *chess = NULL, *redQueen = NULL;
    SDL_Rect src_rec = {0,0,BlockW,BlockH}, dst_rec = {0,0,BlockW,BlockH};
    TTF_Font *Font = NULL;

    bool isBacktrack = false;
    int n,queen[10],cols[20],d1[20],d2[20];
    int des[10][10]={0};
    unsigned int delay = 500;
    int field[Line][Column] = {0};
};
