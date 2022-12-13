//
// Created by ezgiu on 13.12.2022.
//
Texture spaceFighterImg;
Vector2 spacefighterPos;

void initFighter()
{
    spaceFighterImg= LoadTexture("assets/SpaceFighter.png");
    spacefighterPos.y=600;
    spacefighterPos.x=400;
}
void moveFighter(int screenWidth, int screenHeigth)
{


    // Update
    //----------------------------------------------------------------------------------
    if (IsKeyDown(KEY_LEFT)) spacefighterPos.x -= 2.0f;
    if (IsKeyDown(KEY_RIGHT)) spacefighterPos.x += 2.0f;
    if (IsKeyDown(KEY_SPACE))
    {
        addBullet(-1,spacefighterPos.x,spacefighterPos.y);
    }
    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    DrawTextureEx(spaceFighterImg, spacefighterPos, 0, 1,WHITE);
    EndDrawing();
}

#ifndef MAIN_C_SPACEFIGHTER_H
#define MAIN_C_SPACEFIGHTER_H

#endif //MAIN_C_SPACEFIGHTER_H
