//
// Created by derpa on 30.11.2022.
//

//Aliens(Gegner) Initialisieren
int alienPosX=10; //x-Position des Linken Oberen ALiens
int alienPosY=10; //y-Position des Linken Oberen ALiens
int aliens[10][4]; //Array von Aliens 10 Nebeneinander,4 Untereinander      Wert des Arrays: 1=Lebend 0=Tod
int aliensDirectionX=10;
Texture2D imgAlien[10][4];



//Alle Aliens auf Lebend setzen
void initAliens(int arr[10][4])

{
    for (int i=0;i<10;i++)
    {
        for(int j=0;j<4;j++)
        {
            arr[i][j]=1;
            //Wenn wir Zeit haben, können wir ja ein Instanz System aufbauen um nicht für jedes Alien eine eigene Textur
            //laden zu müssen. Aber nur wenn wir fertig sind und Zeit haben.
            imgAlien[i][j] = LoadTexture("assets/Aliens.png");
        }
    }
}

void drawAliens(int arr[10][4],int posx, int posy)
{
    BeginDrawing();
    for (int i=0;i<10;i++)
    {
        for(int j=0;j<4;j++)
        {
            DrawTextureEx(imgAlien[i][j],(Vector2){posx+(i*30),posy+(j*30)},0.0f,1.0f,WHITE);
        }
    }
    EndDrawing();    
}
int moveAliens(int Loopcounter,int screenWidth,int screenHeight)
{
    //jedes 10. Frame werden die Aliens bewegt
    if(Loopcounter%10==0)
    {
        //Falls Aliens Rand berührt Richtung invertieren und Y-Position verändern
        if(alienPosX<10 || alienPosX>screenWidth-300)
        {
            alienPosY+=10;
            aliensDirectionX*=-1;
        }
        alienPosX+=aliensDirectionX;
        Loopcounter=0;
    }
    return Loopcounter;
}
#ifndef MAIN_C_ENEMIES_H
#define MAIN_C_ENEMIES_H

#endif //MAIN_C_ENEMIES_H
