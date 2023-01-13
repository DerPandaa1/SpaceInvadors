    //
// Created by ezgiu on 13.12.2022.
//
Texture spaceFighterImg;
Vector2 spacefighterPos;
int shootCooldown=0;
int counter=0;
int cooldown = 0 ;
Texture exhaust;
Vector2 exhaustPos;
float energy = 499;
void initFighter()
{
    exhaust = LoadTexture("assets/exhaust.png");
    spaceFighterImg= LoadTexture("assets/SpaceFighter.png");
    spacefighterPos.y=550;
    spacefighterPos.x=350;
}
//Gibt den Mittelpunkt des Raumschiffes zurück
Vector2 getMidPos()
{
    Vector2 vector;
    vector.x=spacefighterPos.x+(spaceFighterImg.height/2);
    vector.y=spacefighterPos.y+(spaceFighterImg.width/2);
    return vector;
}
void resetEnergy()
{
    energy=499;
}
void moveFighter(int screenWidth, int screenHeigth)
{
    int fighterRot=0; // Rotation des Raumschiffes
    //Bewegung
    if (IsKeyDown(KEY_LEFT)&&spacefighterPos.x>0)
    {
        spacefighterPos.x -= 4.0f;
        fighterRot=-3;
    }
    if (IsKeyDown(KEY_DOWN)&&spacefighterPos.y<720)
    {
        spacefighterPos.y += 4.0f;
    }
    if (IsKeyDown(KEY_UP)&&spacefighterPos.y>360)
    {
        //Zeigt einen Antrieb am Raumschiff
        spacefighterPos.y -= 4.0f;
        exhaustPos.x = spacefighterPos.x+40.7;
        exhaustPos.y = spacefighterPos.y+68;
        if(IsKeyDown(KEY_DOWN)!=true)   //Damit der Antrieb nur beim "hoch" bewegen kommt
        DrawTextureV(exhaust,exhaustPos,WHITE);
    }
    if (IsKeyDown(KEY_RIGHT)&&spacefighterPos.x<700)
    {
        spacefighterPos.x += 4.0f;
        fighterRot=3;
    }
//Zeile 59 bis 84 ist Logik um zu berechnen wann der Spieler schießen darf
    if (energy > 0 && cooldown==0) {
        if (IsKeyDown(KEY_SPACE) && shootCooldown <= 0) {
            Vector2 fighterPos = getMidPos();
            addBullet(-1, fighterPos.x, fighterPos.y);
            shootCooldown = 10;
            energy = energy - 35;
            cooldown=0;
        }
    }
//Shootcooldown ist für den Cooldown zwischen jedem Schuss und
//cooldown ist für den cooldown wenn die energybar leer geht
    if(energy<0) {
        cooldown = 1;
    }
    if(cooldown==1)
    {
        counter++;
        if(counter>160) //160 Frames werden gewartet bevor man wieder schießen darf
        {
            cooldown=0;
            counter=0;
        }
    }
    if(energy<500)
    {
        energy=energy+1.6;
    }
    //Die Energybar zeichnen
    Rectangle outline;
    outline.x=270;
    outline.y=750;
    outline.width=250;
    outline.height=20;

    Rectangle bar;
    bar.x=271;
    bar.y=751;
    bar.width=energy/2;
    bar.height=19;

    DrawTextureEx(spaceFighterImg, spacefighterPos, fighterRot, 1,WHITE);
    DrawRectangleRounded(bar,0.9,10,GREEN);
    DrawRectangleRoundedLines(outline,0.9,10,6,RED);

    //shootCooldown erniedrigen
    if(shootCooldown>0) shootCooldown--;
}
//Kollisionsabfrage Schüsse-Raumschiff
int checkFighterCollision(int startGame)
{
    Vector2 fighterPos=getMidPos();
    int currentBullets=getCurrentBullets();
    for(int i=0;i<currentBullets;i++)
    {
        bullet bullet1=getBullet(i);

        //Falls der Schuss sich nach oben bewegt wird er ignoriert
        if(bullet1.direction<0) continue;

        //x-/y-Differenz berechnen um Abstand zum Schuss mit Satz des Pythagoras
        float xDiff = fighterPos.x-bullet1.x;
        float yDiff = fighterPos.y-bullet1.y;
        float Diff = sqrt((xDiff*xDiff)+(yDiff*yDiff));

        if(Diff<=30)
        {
            removeBullet(i);
            currentBullets=getCurrentBullets();
            return 2;
        }
    }
    return startGame;
}


#ifndef MAIN_C_SPACEFIGHTER_H
#define MAIN_C_SPACEFIGHTER_H

#endif //MAIN_C_SPACEFIGHTER_H
