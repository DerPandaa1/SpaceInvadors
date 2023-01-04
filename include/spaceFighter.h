    //
// Created by ezgiu on 13.12.2022.
//
Texture spaceFighterImg;
Vector2 spacefighterPos;
int shootCooldown=0;

void initFighter()
{
    spaceFighterImg= LoadTexture("assets/SpaceFighter.png");
    spacefighterPos.y=600;
    spacefighterPos.x=400;
}
//Gibt den Mittelpunkt des Raumschiffes zurück
Vector2 getMidPos()
{
    Vector2 vector;
    vector.x=spacefighterPos.x+(spaceFighterImg.height/2);
    vector.y=spacefighterPos.y+(spaceFighterImg.width/2);
    return vector;
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
    else if (IsKeyDown(KEY_RIGHT)&&spacefighterPos.x<750)
    {
        spacefighterPos.x += 4.0f;
        fighterRot=3;
    }
    if (IsKeyDown(KEY_SPACE)&&shootCooldown<=0)
    {
        Vector2 fighterPos=getMidPos();
        addBullet(-1,fighterPos.x,fighterPos.y);
        shootCooldown=10;
    }
    //Malen
    DrawTextureEx(spaceFighterImg, spacefighterPos, fighterRot, 1,WHITE);

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
