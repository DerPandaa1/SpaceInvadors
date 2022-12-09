#include "include/raylib.h"
#include "include/alien.h"
#include "include/window.h"

void gameLoop();

//globale Variablen
int Loopcounter=0;
const int screenWidth = 800;
const int screenHeight = 800;
int startGame = 0; //Hat 4 Zustände
/*  0=Hauptmenü
 *  1=Spiel am laufen
 *  2=Spiel wurde Gewonnen
 * 3=Spiel wurde Verloren
 */

int main(void)
{
    WindowInit(screenWidth,screenHeight);

    //Space Invaders einlesen in RAM und danach in Textur auf die GPU schicken

    /*
    Image menuAnim = LoadImageAnim("assets/MainMenu.gif", &animFrames);
    Texture2D menuAnimTex = LoadTextureFromImage(menuAnim);
    unsigned int nextFrameDataOffset = 0;
    int currentAnimFrame = 0;       // Momentaner Frame der Animation
    int frameDelay = 20;            // Zeit in frames zwischen Animation schritten
    int frameCounter = 0;
     */

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
        ////fdhiahfafsaljfkafsjllka
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
    Loopcounter=moveAliens(Loopcounter,screenWidth,screenHeight);
    drawAliens(aliens,alienPosX,alienPosY);
}
