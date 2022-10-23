#include <iostream>
#include <ctime>
#include <cstdlib>
#include "queen.h"
using namespace std;
bool Queens::init(const char* title)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenW, ScreenH, SDL_WINDOW_SHOWN);
        if(window != NULL)
        {
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer != NULL)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                int initted = IMG_Init(imgFlags);
                if((initted & imgFlags) != imgFlags)
                    std::cout << "Error" << IMG_GetError() << '\n';
                SDL_Surface* loadSurf = IMG_Load("banco.png");
                background = SDL_CreateTextureFromSurface(renderer,loadSurf);
                SDL_FreeSurface(loadSurf);
                loadSurf = IMG_Load("Queens2.png");
                chess = SDL_CreateTextureFromSurface(renderer,loadSurf);
                SDL_FreeSurface(loadSurf);
                loadSurf = IMG_Load("redQueen.png");
                redQueen = SDL_CreateTextureFromSurface(renderer,loadSurf);
                SDL_FreeSurface(loadSurf);
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
     //Initialize SDL_ttf
    if (TTF_Init() < 0)
    {
        SDL_Log("%s", TTF_GetError());
        return -1;
    }
    Font = TTF_OpenFont("Font2.ttf",35);
    n = 4;
    for(int q=0; q<=20; q++)
        cols[q] = d1[q] = d2[q] = 1;
    return true;
}
void Queens::setRectPos(SDL_Rect& rect, int x, int y, int w, int h)
{
    rect = {x,y,w,h};
}
void Queens::moveRectPos(SDL_Rect& rect,int x, int y)
{
    rect.x+=x;
    rect.y+=y;
}
 void Queens::res()
{
    SDL_RenderCopy(renderer,background,NULL,NULL);
    for(int i=1; i<=n; i++){
        des[i][queen[i]] = 1;
        setRectPos(dst_rec,(queen[i]-1)*BlockH,(i-1)*BlockH);
        SDL_RenderCopy(renderer,chess,NULL,&dst_rec);
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(des[i][j] == 0) cout << ".";
            else cout <<"*";
        }
        cout << endl;
    }
    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
            des[i][j] = 0;
    cout << endl;
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
}
void Queens::Try(int i)
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            SDL_Quit();
            break;
        case SDL_KEYDOWN:
            SDL_Quit();
            break;
        default:
            break;
        }
    }
    for(int j=1; j<=n; j++)
    {
        //render background
        SDL_RenderCopy(renderer,background,NULL,NULL);
        for(int m=1; m<=n; m++)
        for(int k=1; k<=n; k++)
        {
            if(field[m][k] == 1){
            setRectPos(dst_rec,(k-1)*BlockH,(m-1)*BlockH);
            SDL_RenderCopy(renderer,chess,NULL,&dst_rec);
            }
        }
        // render current chess
        if(cols[j] == 1 && d1[i-j+n] == 1 && d2[i+j-1] == 1){
            setRectPos(dst_rec,(j-1)*BlockH,(i-1)*BlockH);
            SDL_RenderCopy(renderer,chess,NULL,&dst_rec);
        } else {
            setRectPos(dst_rec,(j-1)*BlockH,(i-1)*BlockH);
            SDL_RenderCopy(renderer,redQueen,NULL,&dst_rec);
        }
        // render Backtrack message
         if (isBacktrack) {
                setRectPos(src_rec,0,0);
                setRectPos(dst_rec,(j-1)*BlockH,(i-1)*BlockH - 85);
                loadFont("BACKTRACKING", src_rec, dst_rec);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        if (isBacktrack) {
            isBacktrack = false;
            SDL_Delay(1500);
        }
        if(cols[j] == 1 && d1[i-j+n] == 1 && d2[i+j-1] == 1)
        {
            cols[j] = d1[i-j+n] = d2[i+j-1] = 0;
            field[i][j] = 1;
            queen[i] = j;
            if(i == n) res();
            else Try(i+1);
            cols[j] = d1[i-j+n] = d2[i+j-1] = 1;
            field[i][j] = 0;
        }
        if (j == n) isBacktrack = true;
    }
}
void Queens::loadFont(string text, SDL_Rect source, SDL_Rect destination)
{
	SDL_Color fg = { 204, 0, 204 };

	SDL_Surface *surface = TTF_RenderText_Blended(Font, text.c_str(), fg);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	TTF_SizeText(Font, text.c_str(), &source.w, &destination.h);

	destination.w = source.w;
	destination.h = source.h;
	SDL_RenderCopy(renderer, texture, &source, &destination);

}
void Queens::clean()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(chess);
    SDL_DestroyTexture(redQueen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
