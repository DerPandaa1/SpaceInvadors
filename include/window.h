//
// Created by derpa on 07.12.2022.
//
int currentMonitor;
int fps;
int animFrames = 0;
int frameDelay = 20;            // Zeit in frames zwischen Animation schritten
int currentAnimFrame = 0;       // Momentaner Frame der Animation
int frameCounter = 0;
Image menuAnim;
Texture2D menuAnimTex;
unsigned int nextFrameDataOffset = 0;
int currentMenuObject=0;
int Difficulty = 1;

int getCurrentDifficulty()
{
    return Difficulty;
}

void loadTextures(){
    menuAnim = LoadImageAnim("assets/MainMenu.gif", &animFrames);
    menuAnimTex = LoadTextureFromImage(menuAnim);
}

void WindowInit(int screenWidth,int screenHeight){
    //Schaltet MSAA und VSYNC ein
    SetConfigFlags(FLAG_MSAA_4X_HINT  | FLAG_VSYNC_HINT);
    //Initialisiert und öffnet das Fenster
    InitWindow(screenWidth, screenHeight, "Space Invaders");
    //Setzt ein Icon für das Fenster
    SetWindowIcon(LoadImage("assets/InvadersIcon.png"));

    EnableCursor();

    //Fragt ab wie viel Herz der Hauptbildschirm hat und setzt die Target FPS
    currentMonitor=GetCurrentMonitor();
    fps=GetMonitorRefreshRate(currentMonitor);
    SetTargetFPS(60);
    /*  Momentan laufen Animationen anhand der Framerate
     *  Bedeutet das Animationen schneller laufen bei einer hohen Framerate
     *  Ich werde das bald ändern auf ein Frametime basiertes System
     *  Bis dahin werden die FPS auf 60 gekappt
     */
    loadTextures();
}

void UpdateMenuGIF(){
    //Frame basierter (leider) GIF Playback
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
}

int DrawMainScreen(){
    UpdateMenuGIF();
    BeginDrawing();
    DrawTexture(menuAnimTex, GetScreenWidth()/2 - menuAnimTex.width/2, 400, WHITE);

    //Zeichnet den Hauptbildschirm
    DrawText("Space", 275, 80, 90, GREEN);
    DrawText("Invaders", 210, 155, 90, GREEN);
    //DrawText("H", 400, 380, 20, YELLOW);      //Nur zum Testen notwendig
    DrawRectangle(325, 260, 160, 60, GREEN);    //Grüne Boxen und Titel Texte
    DrawText("PLAY!", 335, 270, 50, BLACK);
    DrawRectangle(325, 405, 160, 60, GREEN);
    DrawText("Quit", 360, 412, 50, BLACK);
    DrawText("Press N for a secret", 640, 775, 15, NEAR_BLACK); //Sehr Wichtig!
    switch (Difficulty) {
        case 1: DrawRectangle(325, 333, 160, 60, GREEN); break;
        case 2: DrawRectangle(325, 333, 160, 60, YELLOW); break;
        case 3: DrawRectangle(325, 333, 160, 60, RED); break;
    }
    DrawText("Difficulty",330,343,33,BLACK);

    DrawFPS(715, 7);
    //Zeichnet den Grauen AuswahlKasten
    if (IsWindowFocused() == true && currentMenuObject == 0) {
        DrawRectangle(330, 265, 150, 50, TRANS_GRAY);
    }
    //Zeichnet den Grauen Kasten auf den Auswahlelementen
    if (IsKeyPressed(KEY_DOWN)) {
        currentMenuObject++;
    }
    if (IsKeyPressed(KEY_UP)) {
        currentMenuObject--;
    }
    if(currentMenuObject==1)
    {
        DrawRectangle(330,338,150,50,TRANS_GRAY);
    }
    if(currentMenuObject==2)
    {
        DrawRectangle(330,410,150,50,TRANS_GRAY);
    }
    //Darf nicht größer als 3 oder kleiner als 0 sein
    if(currentMenuObject>=3)
    {
        currentMenuObject=2;
    }
    if(currentMenuObject<0)
    {
        currentMenuObject=0;
    }

    //Falls Play gedrückt wird
    if(IsKeyPressed(KEY_ENTER)&&currentMenuObject==0)
    {
        ClearBackground(BLACK);
        UnloadTexture(menuAnimTex); //löscht das GIF aus
        UnloadImage(menuAnim);      //dem Speicher

        return 1;                //startet das Spiel
    }
    //Falls Difficulty gedrückt wird
    if(IsKeyPressed(KEY_ENTER)&&currentMenuObject==1)
    {
        if(Difficulty==3)
        {
            Difficulty=1;
        }
        else
            Difficulty++;
    }
    //Falls Quit gedrückt wird
    if(IsKeyPressed(KEY_ENTER)&&currentMenuObject==2)
    {
        CloseWindow();
    }
    EndDrawing();
    return 0;
}

#ifndef MAIN_C_WINDOW_H
#define MAIN_C_WINDOW_H

#endif //MAIN_C_WINDOW_H
