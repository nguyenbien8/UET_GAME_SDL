#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "TextureManager.h"
#include "Coin.h"
#include "Trap.h"
#include "TextManager.h"

Game::Game(){}
Game::~Game(){}
SDL_Renderer* Game::gRenderer = nullptr;
SDL_Texture* background;
Mix_Music* gMusic = NULL;
TextManager* text;

Map* map;
Player* player;
Coin* coin[50];
Trap* trap[65];
SDL_Rect camera;

void Game::handleEvent(){
    SDL_Event gEvent;
    SDL_PollEvent(&gEvent);
	if(gEvent.type == SDL_QUIT) isRunning = false;
	int x, y;
	if(isPause)
    {
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            //getmousestate: dung de lay trang thai cua chuot
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,370,495,402,525)) // Return //
            {
                //channel/chunk: am thanh/loop
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(gState);
                isPause = false;
            }
            if(isInside(x,y,567,698,400,528))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                isPause = false;
            } // Continue //
            if(isInside(x,y,766,904,393,530)) // Quit //
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(SELECTMAP);
                isPause = false;
            }
            break;
        default:
            break;
        }
        return;
    }
    //CHANGE STATE
	switch(gState)
	{
    case LEVEL1:
    case LEVEL2:
        //this: con tro den doi tuong hien tai
        if(gEvent.type == SDL_KEYDOWN) player->Handle(gEvent, this, map);
        break;
    case GUIDE:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,880,965,25,108)) //SELECTMAP
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(SELECTMAP);
            }
            break;
        default:
            break;
        }
        break;
    case HIGHSCORE:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,875,973,16,115))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(SELECTMAP);
            }
            break;
        default:
            break;
        }
        break;
    case LOSE:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if (isInside(x,y,655,795,333,470))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(SELECTMAP);
            }
            if (isInside(x,y,445,568,340,462))
            {
                if(currentLevel == 1)
                {
                    Mix_PlayChannel(-1,gChunk1,0);
                    switchState(LEVEL1);
                }
                else if(currentLevel == 2)
                {
                    Mix_PlayChannel(-1,gChunk1,0);
                    switchState(LEVEL2);
                }
            }
            break;
        default:
            break;
        }
        break;
    case WIN:
        if (maxLevel < currentLevel + 1) maxLevel = currentLevel + 1;
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if (isInside(x,y,655,795,336,470))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(SELECTMAP);
            }
            if (isInside(x,y,415,550,333,469))
            {
                if(currentLevel == 1)
                {
                    Mix_PlayChannel(-1,gChunk1,0);
                    switchState(LEVEL2);
                }
                else
                {
                    Mix_PlayChannel(-1,gChunk1,0);
                    switchState(SELECTMAP);
                }
            }
            break;
        default:
            break;
        }
        break;
    case MENU:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,321,466,390,537))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(SELECTMAP);
            }
            if(isInside(x,y,550,695,392,535))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(SETTING);
            }
            if(isInside(x,y,778,925,390,535))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                isRunning = false;
            }
            break;
        default:
            break;
        }
        break;
    case SELECTMAP:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,421,497,385,471))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(LEVEL1);
            }
            if(isInside(x,y,488,560,270,340) && maxLevel >= 2)
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(LEVEL2);
            }
            if(isInside(x,y,872,965,20,112))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(MENU);
            }
            if(isInside(x,y,640,790,600,651))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(GUIDE);
            }
            if(isInside(x,y,202,477,600,650))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(HIGHSCORE);
            }
            break;
        default:
            break;
        }
        break;
    case SETTING:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,875,973,19,114))
            {
                Mix_PlayChannel(-1,gChunk1,0);
                switchState(MENU);
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void Game::renderGame(){
    SDL_RenderClear(gRenderer);
    if(isPause)
    {
        background = TextureManager::LoadTexture("Assets/State/pausee.png");
        //sao chep noi dung va ve len man hinh
        SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
        SDL_RenderPresent(gRenderer);
        return;
    }
    switch(gState)
    {
    case HIGHSCORE:
    case MENU:
    case SELECTMAP:
    case GUIDE:
    case SETTING:
        SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
        break;
    case WIN:
        {
            SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
            std::string temp = "FINISHED LEVEL " + std::to_string(currentLevel);
            text->Render(temp.c_str(), 420, 100, 1);
            temp = "Your time: " + std::to_string(tempScore);
            text->Render(temp.c_str(), 420, 160, 1);
            temp = "Min time: " + std::to_string(highScore[currentLevel-1]);
            text->Render(temp.c_str(), 420, 220, 1);
        }
        break;
    case LOSE:
        {
            SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
            text->Render("You die....", 420, 100, 1);
            text->Render("You die....", 420, 160, 1);
            text->Render("You die....", 420, 220, 1);
        }
        break;
    case LEVEL1:
    case LEVEL2:
        //
        map->DrawMap(camera);
        player->Render();
        for (int i = 0; i < 50; i++)
        {
            if(coin[i] == nullptr) break;
            coin[i]->Render(player->xpos, player->ypos);
        }
        for (int i = 0; i < 65; i++)
        {
            if(trap[i] == nullptr) break;
            trap[i]->Render(player->xpos, player->ypos);
        }
        break;
    default:
        break;
    }
    SDL_RenderPresent(gRenderer);
}

void Game::enterState(State id){
    switch(id)
    {
    case LOSE:
        text = new TextManager(37);
        background = TextureManager::LoadTexture("Assets/State/losee.png");
        break;
    case WIN:
        text = new TextManager(37);
        background = TextureManager::LoadTexture("Assets/State/winn.png");
        break;
    case MENU:
        background = TextureManager::LoadTexture("Assets/State/menuu.png");
        break;
    case SELECTMAP:
        background = TextureManager::LoadTexture("Assets/State/selectmapp.png");
        break;
    case SETTING:
        background = TextureManager::LoadTexture("Assets/State/settingg.png");
        break;
    case HIGHSCORE:
        background = TextureManager::LoadTexture("Assets/State/highscoree.png");
        break;
    case GUIDE:
        background = TextureManager::LoadTexture("Assets/State/guidee.png");
        break;
    case LEVEL1:
        currentLevel = 1;
        startTime = SDL_GetTicks();
        player = new Player("Assets/Character/spider.png",25,12);
        map = new Map(currentLevel);
        camera = {player->xpos-480, player->ypos-320, 992, 672};

        coin[0] = new Coin(23, 10); coin[1] = new Coin(25, 10);
        coin[2] = new Coin(33, 10); coin[3] = new Coin(29, 19);
        coin[4] = new Coin(29, 20); coin[5] = new Coin(27, 24);
        coin[6] = new Coin(25, 22); coin[7] = new Coin(20, 22);
        coin[8] = new Coin(15, 24); coin[9] = new Coin(20, 33);
        coin[10] = new Coin(28, 32); coin[11] = new Coin(31, 37);
        coin[12] = new Coin(25, 40); coin[13] = new Coin(25, 47);
        coin[14] = new Coin(35, 50); coin[15] = new Coin(34, 59);
        coin[16] = new Coin(34, 60);

        trap[0] = new Trap (19,33,1); trap[1] = new Trap (17,33,2);
        trap[2] = new Trap (18,34,3); trap[3] = new Trap (18,32,4);
        trap[4] = new Trap (20,39,1); trap[5] = new Trap (20,40,1);
        trap[6] = new Trap (20,41,1); trap[7] = new Trap (21,42,4);
        trap[8] = new Trap (22,42,4); trap[9] = new Trap (23,42,4);

        break;
    case LEVEL2:
        startTime = SDL_GetTicks();
        currentLevel = 2;
        player = new Player("Assets/Character/spider.png",42,97);
        map = new Map(currentLevel);
        camera = {player->xpos-480, player->ypos-320, 992, 672};
        coin[0] = new Coin (42,96); coin[1] = new Coin (34,97);
        coin[2] = new Coin (30,93); coin[3] = new Coin (36,89);
        coin[4] = new Coin (41,86); coin[5] = new Coin (41,82);
        coin[6] = new Coin (37,81); coin[7] = new Coin (40,79);
        coin[8] = new Coin (48,78); coin[9] = new Coin (48,72);
        coin[10] = new Coin (37,72); coin[11] = new Coin (40,65);
        coin[12] = new Coin (35,60); coin[13] = new Coin (35,59);
        coin[14] = new Coin (35,58); coin[15] = new Coin (40,46);
        coin[16] = new Coin (37,42); coin[17] = new Coin (31,36);
        coin[18] = new Coin (49,30); coin[19] = new Coin (39,24);

        trap[0] = new Trap (37,96,1); trap[1] = new Trap (30,93,1);
        trap[2] = new Trap (30,92,1); trap[3] = new Trap (30,91,1);
        trap[4] = new Trap (41,83,1); trap[5] = new Trap (40,82,4);
        trap[6] = new Trap (40,84,3); trap[7] = new Trap (39,83,2);
        trap[8] = new Trap (37,72,1); trap[9] = new Trap (37,71,1);
        trap[10] = new Trap (37,70,1); trap[11] = new Trap (36,68,2);
        trap[12] = new Trap (36,67,2); trap[13] = new Trap (36,66,2);
        trap[14] = new Trap (39,48,3); trap[15] = new Trap (39,34,4);
        trap[16] = new Trap (40,34,4); trap[17] = new Trap (41,34,4);
        trap[18] = new Trap (42,34,4); trap[19] = new Trap (39,22,1);
        trap[20] = new Trap (39,23,1); trap[21] = new Trap (39,24,1);
        trap[22] = new Trap (39,25,1); trap[23] = new Trap (32,35,2);
        trap[24] = new Trap (32,36,2); trap[25] = new Trap (48,25,2);
        trap[26] = new Trap (49,24,4); trap[27] = new Trap (49,11,3);
        break;

    default:
        break;
    }
}

void Game::exitState(State id){
    switch(id)
    {
    case MENU:
    case SELECTMAP:
    case GUIDE:
    case SETTING:
        SDL_DestroyTexture(background);
        background = nullptr;
        break;
    case WIN:
    case LOSE:
    case HIGHSCORE:
        SDL_DestroyTexture(background);
        background = nullptr;
        delete text;
        text = nullptr;
        break;
    case LEVEL1:
    case LEVEL2:
        //gMusic/loop(-1: lap vo han)/change
        Mix_FadeInMusic(gMusic,-1,500);
        delete text;
        player = nullptr;
        map = nullptr;
        for (int i = 0; i < 50; i++) coin[i] = nullptr;
        for (int i = 0; i < 65; i++) trap[i] = nullptr;
        break;
    default:
        break;
    }
}

void Game::updateGame(int x){
    if(isPause) return;
    switch(gState)
    {
    case LEVEL1:
    case LEVEL2:
        player->Update(camera, player->xpos, player->ypos);
        /// Update objects ///
        if(!x)
        {
            for (int i = 0; i < 30; i++)
            {
                if(coin[i] == nullptr) break;
                coin[i]->Update();
            }
            for (int i = 0; i < 60; i++)
            {
                if(trap[i] == nullptr) break;
                trap[i]->Update();
            }
        }
        ///Collision objects///
        for (int i = 0; i < 50; i++)
        {
            if(coin[i] == nullptr) break;
            if(player->Collision(coin[i]->hitbox) && !coin[i]->collected)
            {
                Mix_PlayChannel(-1,gChunk3,0);
                coin[i]->collected = true;
                gCoin++;
            }
        }
        for(int i = 0; i < 65; i++)
        {
            if(trap[i] == nullptr) break;
            if(player->Collision(trap[i]->hitbox))
            {
                if(trap[i]->activated && SDL_GetTicks() - trap[i]->activatedTime > 400)
                {
                    Mix_PlayChannel(-1,gChunk6,0);
                    isLose = true;
                    break;
                }
                else if (!trap[i]->activated)
                {
                    trap[i]->activatedTime = SDL_GetTicks();
                    trap[i]->activated = true;
                }
            }
        }

        break;
    default:
        break;
    }
    if(isLose) {switchState(LOSE); isLose = false;}
    if(isWin)
    {
        tempScore = SDL_GetTicks() - startTime;
        if(tempScore < highScore[currentLevel-1])
        {
            highScore[currentLevel-1] = tempScore;
        }
            isWin = false;
            switchState(WIN);
    }
}

bool Game::isInside(int x, int y, int x1, int x2, int y1, int y2)
{
    return (x1 <= x && x <= x2 && y1 <= y && y <= y2);
}
void Game::switchState(State id)
{
    Game::exitState(gState);
    Game::enterState(id);
    gState = id;
    changeState = true;
    SDL_Delay(75);
}

void Game::initGame()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "Openning." << std:: endl;
    TTF_Init();
    gWindow = SDL_CreateWindow("A WAY OUT",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 992, 672, 0);

    Mix_OpenAudio( 30000, MIX_DEFAULT_FORMAT, 2, 2048 );
    gMusic = Mix_LoadMUS("Assets/Sound/musicc.mp3");
    gChunk1 = Mix_LoadWAV("Assets/Sound/chunk2.wav");
    gChunk3 = Mix_LoadWAV("Assets/Sound/PickupCoin.mp3");
    gChunk4 = Mix_LoadWAV("Assets/Sound/win2.wav");
    gChunk6 = Mix_LoadWAV("Assets/Sound/Spike.wav");
    Mix_PlayMusic(gMusic,-1);

    gRenderer = SDL_CreateRenderer(gWindow,-1,0);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    // Export save game file //
    std::ifstream file("Assets/savegame.txt");
    file >> maxLevel;
    file >> gCoin;
    for (int i = 0; i < 9; i++) file >> highScore[i];
    file.close();
    enterState(gState);
}
void Game::closeGame()
{
	// Import save game file //
    std::ofstream file("Assets/savegame.txt");
    file << " ";
    file << maxLevel;
    file << " ";
    file << gCoin;
    for (int i = 0; i < 9; i++)
    {
        file << " ";
        file << highScore[i];
    }
    file.close();
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	Mix_FreeChunk(gChunk1);
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	std::cout << "Closed..." << std::endl;
}
