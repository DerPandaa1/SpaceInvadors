#include "include/raylib.h"
#include "include/alien.h"
#include "include/window.h"
//#include "include/bullets.h"

void gameLoop();

//globale Variablen
int Loopcounter=0;
const int screenWidth = 800;
const int screenHeight = 800;
int difficulty=1;
/* 1=leicht
 * 2=mittel
 * 3=schwer
 */
int startGame = 0; //Hat 4 Zustände
/*  0=Hauptmenü
 *  1=Spiel am laufen
 *  2=Spiel wurde Gewonnen
 * 3=Spiel wurde Verloren
 */

int main(void)
{
    WindowInit(screenWidth,screenHeight);
    //Haupt Spiel Loop
//--------------------------------------------------------------------------------------------------------------------->
    //Fenster bleibt offen bis ESC gedrückt wird
    while (!WindowShouldClose())
    {
        ClearBackground(BLACK);

        //Ermöglicht es mit F11 Vollbildschirm zu öffnen
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }
        if(IsKeyPressed(KEY_N)&&startGame==0)
        {
            //DARF AUF KEINEN FALL GEÄNDERT WERDEN!!!! WICHTIG!:)
            OpenURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ");

        }
        if(startGame==0)
        {
            startGame=DrawMainScreen();
        }


        if(startGame==1)
            gameLoop();
        //Verloren Zustand
        if(startGame==2)
        {
            //Müssen wir noch schöner machens
            BeginDrawing();
            DrawText("Verloren",400,400,20,WHITE);
            EndDrawing();
        }
        //Gewonnen Zustand
        if(startGame==3)
        {

        }
        Loopcounter++;
    }
    //Speicher freigeben
    UnloadTexture(menuAnimTex);
    UnloadImage(menuAnim);
    CloseWindow();
//<---------------------------------------------------------------------------------------------------------------------
    return 0;
}

void gameLoop(){
    Loopcounter=moveAliens(Loopcounter,screenWidth,screenHeight,difficulty);
    moveBullets(screenWidth,screenHeight);
    if(Loopcounter<0){
        startGame=2;
        ClearBackground(BLACK);
        return;

    }
    drawAliens(aliens,alienPosX,alienPosY);
}
