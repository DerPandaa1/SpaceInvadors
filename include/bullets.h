//
// Created by derpa on 10.12.2022.
//

//Erstellt ein "Objekt" mit x/y-Koordinaten und der Richtung
typedef struct bullet{
    int x;
    int y;
    int direction; //1=bewegung nach unten   -1=bewegung nach oben
}bullet;
Texture bulletTexture;
//Maximal 1000 Schüsse
const int maxBullets=1000;
bullet bulletList[1000];
int currentBullets=0;

//Resettet alle Schüsse
void resetBullets(){
    for (int i=0;i<maxBullets;i++){
        bulletList[i].x=0;
        bulletList[i].y=0;
        bulletList[i].direction=0;
    }
    currentBullets=0;
}

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
        //Die momentane Position in einen Vektor übertragen
        Vector2 bulletPos;
        bulletPos.x=bulletList[i].x;
        bulletPos.y=bulletList[i].y;
        if(bulletList[i].direction==-1)
        {
            DrawTextureEx(bulletTexture,bulletPos,-90.0,0.15,WHITE);
        }
        else
        {
            DrawTextureEx(bulletTexture,bulletPos,90.0,0.15,WHITE);
        }
    }
}
//Die Torpedos in den Speicher rein und rausladen
void LoadBulletTex(){
    bulletTexture = LoadTexture("assets/Torpedo.png");
}
void UnloadBulletsTex(){
    UnloadTexture(bulletTexture);
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
