#include "stdio.h"
#include "include/raylib.h"
#include "math.h"
#include "include/bullets.h"
#include "include/alien.h"
#include "include/spaceFighter.h"
#include "include/window.h"

void gameLoop();

//globale Variablen
unsigned int highscore = 0;
int hit;
int Loopcounter=0;
int temp = 1;
const int screenWidth = 800;
const int screenHeight = 800;
int difficulty;
int debugMode=0;
/* 1=leicht
 * 2=mittel
 * 3=schwer
 */

int startGame = 0; //Hat 4 Zustände
/*  0=Hauptmenü
 *  1=Spiel am laufen
 *  2=Spiel wurde Verloren
 *  3=Spiel wurde Gewonnen
 */

int main(void)
{
    //Ich wollte Sounds spielen, aber dies funktioniert noch nicht ganz daher auskommentiert
    //Sound Dateien Laden
    InitAudioDevice();
    //Sound victorySound = LoadSound("assets/Victory_Sound.mp3");
    WindowInit(screenWidth,screenHeight);
    //Haupt Spiel Loop
//--------------------------------------------------------------------------------------------------------------------->
    //Fenster bleibt offen bis ESC gedrückt wird
    while (!WindowShouldClose())
    {
            if (startGame > 1) {
                DrawText("Press CTRL to Main Menu", 10, 10, 20, GREEN);
            }
            //Zurück ins Hauptmenü
            if ((IsKeyPressed(KEY_RIGHT_CONTROL) && startGame > 1) ||
                (IsKeyPressed(KEY_LEFT_CONTROL) && startGame > 1)) {
                startGame = 0;
                loadTextures();
            }

            //Spiel erneut spielen falls man gewonnen oder verloren hat
            if ((IsKeyPressed(KEY_ENTER) && startGame == 3) || (IsKeyPressed(KEY_ENTER) && startGame == 2)) {
                resetBullets();
                if(startGame==2)
                {
                    highscore=0;
                }
                startGame = 1;
                resetAlienPos();
                initAliens();
            }

            //DEBUG OPTIONEN For Devs
            if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_E)) {
                    debugMode = 1;
            }
            if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_R)) {
            debugMode = 0;
            }
            if (IsKeyPressed(KEY_D) && debugMode == 1) {
                initAliens();
                resetAlienPos();
            }
            if (IsKeyPressed(KEY_A) && debugMode == 1) {
                startGame = 3;
            }
            if (IsKeyPressed(KEY_S) && debugMode == 1) {
            startGame = 2;
            }
            if(debugMode==1)
            {
                DrawLine(400,1,400,799,RED);
                DrawLine(1,400,800,400,RED);
                DrawText("Press D to Reset the Aliens",10,5,15,WHITE);
                DrawText("Press A to Win instantly",10,20,15,WHITE);
                DrawText("Press S to Loose instantly",10,35,15,WHITE);
                DrawText(TextFormat("Bullets: %i",getCurrentBullets()),10,50,15,WHITE);
                DrawText(TextFormat("Aliens: %i",getAliveAliens()),10,65,15,WHITE);
                DrawText(TextFormat("Frametime: %f",GetFrameTime()),10,80,15,WHITE);
                DrawText(TextFormat("Monitor Refreshrate: %i",GetMonitorRefreshRate(GetCurrentMonitor())),605,40,15,WHITE);
                DrawFPS(715,7);
            }

//-------------------<DebugOptionen enden hier
            ClearBackground(BLACK);

            //Ermöglicht es mit F11 Vollbildschirm zu öffnen
            if (IsKeyPressed(KEY_F11)) {
                ToggleFullscreen();
            }
            if (IsKeyPressed(KEY_N) && startGame == 0) {
                //DARF AUF KEINEN FALL GEÄNDERT WERDEN!!!! WICHTIG!:)
                OpenURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
            }
            if (startGame == 0) {
                startGame = DrawMainScreen();
                UpdateMenuGIF(Difficulty);
                if (startGame == 1) {
                    LoadBulletTex();
                    initAliens();
                    initFighter();
                    resetBullets();
                    resetAlienPos();
                }
            }

            if (startGame == 1)
                gameLoop();
            //Verloren Zustand
            if (startGame == 2) {
                //Müssen wir noch schöner machen
                BeginDrawing();
                DrawText(TextFormat("%i",highscore),335,10,50,RED);
                DrawText("You Loose", 250, 370, 60, GREEN);
                if (Loopcounter % 60 == 0) {
                    temp++;
                }
                if (temp % 2 == 0) {
                    DrawText("Press Enter to try again", 75, 450, 50, RED);
                }
                EndDrawing();
            }
            //Gewonnen Zustand
            if (startGame == 3) {
                //Müssen wir noch schöner machen
                BeginDrawing();
                DrawText(TextFormat("%i",highscore),335,280,60,YELLOW);
                DrawFPS(715, 7);
                //PlaySound(victorySound);
                DrawText("YOU WIN!", 280, 370, 60, GREEN);
                if (Loopcounter % 30 == 0) {
                    temp++;
                }
                if (temp % 2 == 0) {
                    DrawText("Press Enter to try again", 75, 450, 50, RED);
                }
                EndDrawing();
            }
            Loopcounter++;
    }
    //Speicher freigeben
    UnloadTexture(menuAnimTex);
    UnloadImage(menuAnim);
    UnloadBulletsTex();
    CloseWindow();
//<---------------------------------------------------------------------------------------------------------------------
    return 0;
}

void gameLoop()
{
    difficulty=getCurrentDifficulty();
    Loopcounter=moveAliens(Loopcounter,screenWidth,screenHeight,difficulty);
    moveBullets(screenWidth,screenHeight);
    BeginDrawing();
    //Highscore berechnung sowie zeichnen des Textes
    if (hit==1)
    {
        highscore=highscore+(250*(Difficulty+1)); //250 pro Alien mal Difficulty+1 für rundere Nummern
    }
    if(highscore>0&&highscore<100000) //Den Text mittig halten
    {
        DrawText(TextFormat("%i",highscore),345,10,50,GREEN);
    }
    if(highscore==0)
    {
        DrawText(TextFormat("%i",highscore),387,10,50,GREEN);
    }
    if(highscore>100000)
    {
        DrawText(TextFormat("%i",highscore),340,10,50,GREEN);
    }
    moveFighter(screenWidth,screenHeight);
    drawAliens(aliens);
    EndDrawing();
    startGame = checkFighterCollision(startGame);
    hit=checkAlienCollision();
    if(getAliveAliens()==0)
    {
        startGame=3;
        startGame=3;
    }
    if(Loopcounter<0){
        startGame=2;
    }
    if(startGame!=1)
    {
        ClearBackground(BLACK);
        return;
    }
}
