#include "stdio.h"
#include "include/raylib.h"
#include "math.h"
#include "include/bullets.h"
#include "include/alien.h"
#include "include/spaceFighter.h"
#include "include/window.h"

void gameLoop();
void setHighscore();
void getHighscore();

//globale Variablen
float upperBound = 360;
unsigned int highscore = 0;
unsigned int score=0;
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

    //Highscore aus der Datei auslesen
    getHighscore();

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
                resetEnergy();
                resetFighterPos();
                if(startGame==2){
                    score=0;
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
                Vector2 PlayerPos;
                PlayerPos=getMidPos();
                DrawLine(400,1,400,799,RED);
                DrawLine(1,400,800,400,RED);
                DrawText("Press D to Reset the Aliens",10,5,15,WHITE);
                DrawText("Press A to Win instantly",10,20,15,WHITE);
                DrawText("Press S to Lose instantly",10,35,15,WHITE);
                DrawText(TextFormat("Bullets: %i",getCurrentBullets()),10,50,15,WHITE);
                DrawText(TextFormat("Aliens: %i",getAliveAliens()),10,65,15,WHITE);
                DrawText(TextFormat("PlayerPos x: %.2f",PlayerPos.x),10,80,15,WHITE);
                DrawText(TextFormat("PlayerPos y: %.2f",PlayerPos.y),10,95,15,WHITE);
                DrawText(TextFormat("Frametime: %f",GetFrameTime()),10,110,15,WHITE);
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
                startGame = DrawMainScreen(highscore);
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
                DrawText(TextFormat("Aktueller Score: %8d",score),50,40,40,RED);
                DrawText(TextFormat("Highscore: %8d",highscore),176,90,40,RED);
                DrawText("You Lose", 255, 370, 60, GREEN);
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
                DrawText(TextFormat("Aktueller Score: %8d",score),50,40,40,GREEN);
                DrawText(TextFormat("Highscore: %8d",highscore),176,90,40,YELLOW);
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
void setHighscore()
{
    FILE *fp;
    fp = fopen("highscore.txt","w+");
    if(fp!=NULL)
    {
        fprintf(fp,"%d",highscore);
    }
    else
    {
        printf("Fehler\n");
    }
    fclose(fp);
}
void getHighscore()
{
    FILE *fp;
    fp = fopen("highscore.txt","r");
    if(fp==0)
    {
        highscore=0;
        fclose(fp);
        return;
    }
    fscanf(fp,"%d",&highscore);
    fclose(fp);
}

void gameLoop()
{
    difficulty=getCurrentDifficulty();
    Loopcounter=moveAliens(Loopcounter,screenWidth,screenHeight,difficulty);
    moveBullets(screenWidth,screenHeight);
    BeginDrawing();

    //score berechnung sowie zeichnen des Textes
    if (hit==1)
    {
        score=score+(250*(Difficulty+1)); //250 pro Alien mal Difficulty+1 für rundere Nummern
    }
    if(score>0&&score<100000) //Den Text mittig halten
    {
        DrawText(TextFormat("%i",score),345,10,50,GREEN);
    }
    if(score==0)
    {
        DrawText(TextFormat("%i",score),387,10,50,GREEN);
    }
    if(highscore>100000)
    {
        DrawText(TextFormat("%i",score),340,10,50,GREEN);
    }
    //Bestimmt wie tief die Aliens sind und begrentzt demenstprechent die bewegung des Players
    Vector2 lowestAlien=getAlienPos(3,9);
    if (lowestAlien.y>=662)
    {
        upperBound=485;
    }
    moveFighter(screenWidth,screenHeight,upperBound);
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
        //Highscore setzten falls nötig und Score auf 0 setzten
        if(score>highscore){
            highscore=score;
            setHighscore();
        }

        ClearBackground(BLACK);
        return;
    }
}
