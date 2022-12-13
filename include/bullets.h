//
// Created by derpa on 10.12.2022.
//

//Erstellt ein "Objekt" mit x/y-Koordinaten und der Richtung
typedef struct bullet{
    int x;
    int y;
    int direction; //1=bewegung nach unten   -1=bewegung nach oben
}bullet;

//Maximal 1000 Schüsse
const int maxBullets=1000;
bullet bulletList[1000];
int currentBullets=0;

//Gibt die Anzahl der aktuellen Schüsse zurück
int getCurrentBullets()
{
    return currentBullets;
}
//Gibt den Schuss an dem index im Array zurück
bullet getBullet(int index){
    return bulletList[index];
}
//Entfernt den Schuss am Index
void removeBullet(int index){
    //Alle Schüsse nach dem Index ein nach vorne rücken lassen
    for (int i=index;i<currentBullets;i++)
    {
        bulletList[i]=bulletList[i+1];
    }
    currentBullets--;
}
//Fügt ein Schuss an den Koordinaten zu
void addBullet(int direction, int x, int y){
    if(currentBullets<maxBullets)//Falls noch Platz in der Liste ist
   {
       //Schuss an der Stelle erstellen
       bullet bullet1;
       bullet1.direction=direction;
       bullet1.x=x; bullet1.y=y;

       //Schuss zur Liste hinzufügen
       bulletList[currentBullets]=bullet1;
       currentBullets++;
   }
}
//Malt die Schüsse
void drawBullets()
{
    for (int i=0;i<currentBullets;i++)
    {
        DrawRectangle(bulletList[i].x,bulletList[i].y,2,5,WHITE);
    }
}
//Bewegt die Schüsse
void moveBullets(int screenWidth, int screenHeigth){
    for (int i=0;i<currentBullets;i++)
    {
        int currentY=bulletList[i].y;
        if(currentY>screenHeigth||currentY<0){
            removeBullet(i);
        }else{
            bulletList[i].y+=bulletList[i].direction*10;
        }
    }
    drawBullets();
}




#ifndef MAIN_C_BULLETS_H
#define MAIN_C_BULLETS_H

#endif //MAIN_C_BULLETS_H
