#include "raylib.h"
#include<iostream>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include<cmath>
#include<bits/stdc++.h>
#define GUI_TEST_IMPLEMENTATION
#include "gui_TEST.h"
#include "Evaluator.hpp"
using namespace std;
const int screenWidth = 800;
const int screenHeight = 800;
const double xOrigin = screenWidth/2;
const double yOrigin = screenHeight/2;
double scale = 0.01;
double scrollSpeed = 1.1;
double offsetX = 0;
double offsetY = 0;
double totalDt = 0;
string functionString = "x*x";
double f(double x){
    return sin(x+totalDt);
}
void drawFunction(){
    double lastX;
    double lastY;
    bool flag = false;
    for(double x = -xOrigin-offsetX;x<xOrigin-offsetX;x+=0.1){
        double xVal = xOrigin+offsetX+x;
        double functionValue = (yOrigin+offsetY)-(eval(functionString,x*scale)/scale);
        if(functionValue!=functionValue){
            flag = false;
            continue;
        }
        DrawRectangle(xVal, functionValue, 1, 1, DARKGRAY);
        if(flag){
            DrawLine(lastX, lastY,xVal, functionValue, DARKGRAY);
        }
        else{
            flag = true;
        }
        lastX = xVal;
        lastY = functionValue;
    }
}
void drawAxes(){
    DrawLine(0,  yOrigin+offsetY, screenWidth, yOrigin+offsetY, WHITE);
    DrawLine(xOrigin+offsetX, 0, xOrigin+offsetX, screenHeight, WHITE);
    DrawText(TextFormat("%00.00f",0),xOrigin+offsetX,yOrigin+offsetY,20,WHITE);
}
void drawGridLine(){
    double highestY = (-offsetY*scale)+(yOrigin*scale);
    double lowestY = (-offsetY*scale)-(yOrigin*scale);
    double diffY = screenHeight*scale;
    int count =  (diffY*(1.0/0.5))/10.0;
    double intervalY = ((double)count+1.0)*0.5;
    for(double y = floor(lowestY/intervalY)*intervalY;y<=floor(highestY/intervalY)*intervalY;y+=intervalY){
        if(y==0){
            continue;
        }
        DrawLine(0,  yOrigin+offsetY+(y/scale), screenWidth, yOrigin+offsetY+(y/scale), RED);
        DrawText(TextFormat("%02.02f",-y),(xOrigin+offsetX),yOrigin+offsetY+(y/scale),20,WHITE);
    }
    double highestX = (-offsetX*scale)+(xOrigin*scale);
    double lowestX = (-offsetX*scale)-(xOrigin*scale);
    double diffX = screenHeight*scale;
    int countX =  (diffX*(1.0/0.5))/10.0;
    double intervalX = ((double)countX+1.0)*0.5;
    for(double x = floor(lowestX/intervalX)*intervalX;x<=floor(highestX/intervalX)*intervalX;x+=intervalX){
        if(x==0){
            continue;
        }
        DrawLine(xOrigin+offsetX+(x/scale), 0, xOrigin+offsetX+(x/scale), screenHeight, GREEN);
        DrawText(TextFormat("%02.02f",x),xOrigin+offsetX+(x/scale),yOrigin+offsetY,20,WHITE);
    }
}
int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    Vector2 lastPos = GetMousePosition();
    SetTargetFPS(60);
    GuiTESTState state = InitGuiTEST();
    //eptr->parse(5);
    //int result = eptr->solve();
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        totalDt += GetFrameTime();
        int v = GetMouseWheelMove(); 
        if(v==1){
            scale/=scrollSpeed;
        }
        else if(v==-1){
            scale*=scrollSpeed;
        }
        Vector2 mousePos = GetMousePosition();
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            offsetX += mousePos.x-lastPos.x;
            offsetY += mousePos.y-lastPos.y;
        }
        lastPos = mousePos;
        BeginDrawing();
        ClearBackground(BLACK);
        //DrawText(TextFormat("%d",result),0,0,20,WHITE);
        drawFunction();
        drawAxes();
        drawGridLine();
        bool enterPressed = GuiTEST(&state);
        if(enterPressed){
            functionString = state.TextBox000Text;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}