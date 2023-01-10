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
                startGame = 1;
                resetAlienPos();
                initAliens();
            }
            //DEBUG OPTIONEN
            if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_P)) {
                debugMode = 1;
            }
            if (IsKeyPressed(KEY_D) && debugMode == 1) {
                initAliens();
                resetAlienPos();
            }
            if (IsKeyPressed(KEY_A) && debugMode == 1) {
                startGame = 3;
            }
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
                DrawText("You Loose", 250, 370, 60, GREEN);
                if (Loopcounter % 60 == 0) {
                    temp++;
                }
                if (temp % 2 == 0) {
                    DrawText("Press Enter to try again", 75, 450, 50, RED);
                }
                EndDrawing();
                highscore=0;
            }
            //Gewonnen Zustand
            if (startGame == 3) {
                //Müssen wir noch schöner machen
                BeginDrawing();
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
    if (hit==1)
    {
        highscore=highscore+1000;
    }
    DrawText(TextFormat("%i",highscore),400,10,50,RED);
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
