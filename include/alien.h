//
// Created by derpa on 30.11.2022.
//
#include "stdlib.h"
#include "time.h"
#include "raylib.h"
//#include "bullets.h"
//Aliens(Gegner) Initialisieren
int alienPosX=10; //x-Position des Linken Oberen ALiens
int alienPosY=60; //y-Position des Linken Oberen ALiens
int aliens[10][4]; //Array von Aliens 10 Nebeneinander,4 Untereinander      Wert des Arrays: 1=Lebend 0=Tod
int aliensDirectionX=10;
Texture imgAlien;

//Setzt die Aliens auf Anfang
void resetAlienPos()
{
    alienPosX=10;
    alienPosY=60;
}

//Alle Aliens auf Lebend setzen
void initAliens()
{
    for (int i=0;i<10;i++)
    {
        for(int j=0;j<4;j++)
        {
            aliens[i][j]=1;
        }
    }
    imgAlien=LoadTexture("assets/Aliens.png");
}
//Gibt den Mittelpunkt des angefragten Alien zurück
Vector2 getAlienPos(int index1,int index2)
{
    Vector2 vector;
    vector.x=alienPosX+(index1*45)+(imgAlien.height/2);
    vector.y=alienPosY+(index2*45)+(imgAlien.width/2);
    return vector;
}
int AliensOutOfWindow(int screenWidth){
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<4;j++){
            if(aliens[i][j]==1)
            {
                Vector2 currentAlienVector = getAlienPos(i,j);
                if(currentAlienVector.x<20 || currentAlienVector.x>(screenWidth-20))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

//Aktuell lebende Aliens
int getAliveAliens()
{
    int counter=0;
    for (int i=0;i<10;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(aliens[i][j]==1)counter++;
        }
    }
    return counter;
}
//Kollisionsabfrage Schüsse-Alien
int checkAlienCollision()
{
    int Hit =0;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(aliens[i][j]==0)continue;
            Vector2 AlienPos=getAlienPos(i,j);
            int currentBullets=getCurrentBullets();
            for(int k=0;k<currentBullets;k++)
            {
                bullet bullet1=getBullet(k);

                //Falls der Schuss sich nach unten bewegt wird er ignoriert
                if(bullet1.direction>0) continue;

                //x-/y-Differenz berechnen um Abstand zum Schuss mit Satz des Pythagoras
                float xDiff = AlienPos.x-bullet1.x;
                float yDiff = AlienPos.y-bullet1.y;
                float Diff = sqrt((xDiff*xDiff)+(yDiff*yDiff));

                if(Diff<=20)
                {
                    removeBullet(k);
                    Hit=1;
                    currentBullets=getCurrentBullets();
                    aliens[i][j]=0;
                    break;
                }
            }
        }
    }
    return Hit;
}
//Aliens Malen
void drawAliens()
{
    for (int i=0;i<10;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(aliens[i][j]==1)
            {
                DrawTextureEx(imgAlien,(Vector2){alienPosX+(i*45),alienPosY+(j*45)},0.0f,1.0f,WHITE);
            }
        }
    }
}
//Alien Schüsse generieren
void generateABullets(int difficulty)
{
    srand(time(NULL));
    for (int i=0;i<10;i++)
    {
        for (int j=0;j<4;j++){
            if(aliens[i][j]==0)break;
            int rdm = rand();
            if(rdm%(100/difficulty)==0){
                addBullet(1,alienPosX+(i*45),alienPosY+(j*45));
            }
        }
    }
}
//Aliens bewegen
int moveAliens(int Loopcounter,int screenWidth,int screenHeight,int difficulty)
{
    //jedes 10/5/3 Frame werden die Aliens bewegt (Kommt auf die Schwierigkeit an)
    if(Loopcounter%(20/difficulty)==0)
    {
        generateABullets(difficulty);
        //Falls Aliens Rand berührt Richtung invertieren und Y-Position verändern
        if(AliensOutOfWindow(screenWidth)>0)
        {
            alienPosY+=60;
            aliensDirectionX*=-1;
        }
        alienPosX+=aliensDirectionX;
        Loopcounter=0;
        if(alienPosY>(screenHeight-500)){
            return -1;
        }
    }
    return Loopcounter;
}


#ifndef MAIN_C_ENEMIES_H
#define MAIN_C_ENEMIES_H

#endif //MAIN_C_ENEMIES_H
