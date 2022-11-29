#include "include/raylib.h"

int main(void)
{
    int fps;
    int currentMonitor;
    int screenWidth = 800;
    int screenHeight = 800;
    int currentMenuObject=0;
    int animFrames = 0;
    int startGame = 0; //Hat 4 Zustände
    /*  0=Hauptmenü
     *  1=Spiel am laufen
     *  2=Spiel wurde Gewonnen
     *  3=Spiel wurde Verloren
     */

    //Schaltet MSAA und VSYNC ein
    SetConfigFlags(FLAG_MSAA_4X_HINT  | FLAG_VSYNC_HINT);
    //Initialisiert und öffnet das Fenster
    InitWindow(screenWidth, screenHeight, "Space Invaders");
    //Setzt ein Icon für das Fenster
    SetWindowIcon(LoadImage("assets/InvadersIcon.png"));

    //Fragt ab wie viel Herz der Hauptbildschirm hat und setzt die Target FPS
    currentMonitor=GetCurrentMonitor();
    fps=GetMonitorRefreshRate(currentMonitor);
    SetTargetFPS(60);
    /*  Momentan laufen Animationen anhand der Framerate
     *  Bedeutet das Animationen schneller laufen bei einer hohen Framerate
     *  Ich werde das bald ändern auf ein Frametime basiertes System
     *  Bis dahin werden die FPS auf 60 gekappt
     */

    EnableCursor();
    //Space Invaders einlesen in RAM und danach in Textur auf die GPU schicken
    Image menuAnim = LoadImageAnim("assets/MainMenu.gif", &animFrames);
    Texture2D menuAnimTex = LoadTextureFromImage(menuAnim);
    unsigned int nextFrameDataOffset = 0;
    int currentAnimFrame = 0;       // Momentaner Frame der Animation
    int frameDelay = 20;            // Zeit in frames zwischen Animation schritten
    int frameCounter = 0;

    //Haupt Spiel Loop
//--------------------------------------------------------------------------------------------------------------------->
    //Fenster bleibt offen bis ESC gedrückt wird
    while (!WindowShouldClose())
    {
        frameCounter++;
        if (frameCounter >= frameDelay)
        {
            //Zum nächsten Frame iterieren
            currentAnimFrame++;
            if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

            //MemoryOffset für den Playback
            nextFrameDataOffset = menuAnim.width*menuAnim.height*4*currentAnimFrame;

            // Der GPU die Daten für den nächsten Frame zu liefern
            UpdateTexture(menuAnimTex, ((unsigned char *)menuAnim.data) + nextFrameDataOffset);

            frameCounter = 0;
        }
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(menuAnimTex, GetScreenWidth()/2 - menuAnimTex.width/2, 400, WHITE);

        //Ermöglicht es mit F11 Vollbildschirm zu öffnen
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }
        if(IsKeyPressed(KEY_N))
        {
            //DARF AUF KEINEN FALL GEÄNDERT WERDEN!!!! WICHTIG!
            OpenURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
        }
            if(startGame==0) {
                //Zeichnet den Hauptbildschirm
                DrawText("Space", 275, 80, 90, GREEN);
                DrawText("Invaders", 210, 155, 90, GREEN);
                //DrawText("H", 400, 380, 20, YELLOW); //Nur zum Testen notwendig
                DrawRectangle(325, 330, 160, 60, GREEN);    //Grüne Boxen und Titel Texte
                DrawText("PLAY!", 335, 340, 50, BLACK);
                DrawRectangle(325, 405, 160, 60, GREEN);
                DrawText("Quit", 360, 412, 50, BLACK);
                DrawText("Press N for a secret", 640, 775, 15, NEAR_BLACK); //Sehr Wichtig!
                DrawFPS(715, 7);

                //Zeichnet den Grauen AuswahlKasten
                if (IsWindowFocused() == true && currentMenuObject == 0) {
                    DrawRectangle(330, 335, 150, 50, TRANS_GRAY);
                }
                //Zeichnet den Grauen Kasten auf den Auswahlelementen
                if (IsKeyPressed(KEY_DOWN)) {
                    currentMenuObject = 1;
                }
                if (IsKeyPressed(KEY_UP)) {
                    currentMenuObject = 0;
                }
                if(currentMenuObject==1)
                {
                    DrawRectangle(330,410,150,50,TRANS_GRAY);
                }
            }
            if(IsKeyPressed(KEY_ENTER)&&currentMenuObject==0)
            {
                ClearBackground(BLACK);
                startGame=1;
                UnloadTexture(menuAnimTex);
                UnloadImage(menuAnim);
            }
            if(IsKeyPressed(KEY_ENTER)&&currentMenuObject==1)
            {
                CloseWindow();
            }


            //HIER KOMMT DAS EIGENTLICHE LAUFENDE SPIEL REIN
            if(startGame==1)
            {
                DrawText("Hier kommt das Spiel hin",150,400,40,RED);
            }
            //Verloren Zustand
            if(startGame==2)
            {

            }
            //Gewonnen Zustand
            if(startGame==3)
            {

            }

            EndDrawing();
    }
    //Speicher freigeben
    UnloadTexture(menuAnimTex);
    UnloadImage(menuAnim);
    CloseWindow();
//<---------------------------------------------------------------------------------------------------------------------
    return 0;
}