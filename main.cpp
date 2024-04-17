/*
MIT License

Copyright (c) 2024 Luka Jovanovic

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <iostream>
#include "raylib.h"
#include <fstream>
#include "config.h"
#include <cmath>

using namespace std;

void empty(int m[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            m[i][j] = 0;
        }
    }
}

void update(int m[SIZE][SIZE]){
    int pm[SIZE][SIZE];
    copy(&m[0][0], &m[0][0]+SIZE*SIZE, &pm[0][0]);
    int n; 
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            n = 0;

            if (pm[i][j-1] == 1 && j-1 >= 0) n++;
            if (pm[i][j+1] == 1 && j+1 < SIZE) n++;
            if (pm[i-1][j] == 1 && i-1 >= 0) n++;
            if (pm[i+1][j] == 1 && i+1 < SIZE) n++;
            if (pm[i+1][j+1] == 1 && j+1 < SIZE && i+1 < SIZE) n++;
            if (pm[i-1][j-1] == 1 && i-1 >= 0 && j-1 >= 0) n++;
            if (pm[i-1][j+1] == 1 && j+1 < SIZE && i-1 >= 0) n++;
            if (pm[i+1][j-1] == 1 && i+1 < SIZE && j-1 >= 0) n++;

            if (n < 2 || n > 3){ 
                m[i][j] = 0;
            }
            else if (n == 3 && pm[i][j] == 0){
                m[i][j] = 1;
            }
        }
    }
}

int main(){
    int m[SIZE][SIZE];
    empty(m);
    bool run = false;
    SetTargetFPS(10);
    InitWindow(W, W, "Conway's Game of Life");
    int x, y;
    while (!WindowShouldClose()){
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            x = (int)ceil(GetMouseX()/(W/SIZE));
            y = (int)ceil(GetMouseY()/(W/SIZE));
            if (m[x][y] == 1) m[x][y] = 0;
            else if (m[x][y] == 0) m[x][y] = 1;
        }
        if (IsKeyPressed(KEY_SPACE)) run = !run;
        if (IsKeyPressed(KEY_R)) empty(m);

        BeginDrawing();
        ClearBackground(GetColor(0x181818AA));
        for (int i = 0; i < W; i+=(W/SIZE)){
            DrawLine(i, 0, i, W, WHITE);
            DrawLine(0, i, W, i, WHITE);
        }
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                if (m[i][j] == 1){
                    DrawRectangle(i*W/SIZE, j*W/SIZE, W/SIZE, W/SIZE, RED);
                }
            }
        }
        EndDrawing();
        if (run){
            update(m);
        }
    }
}
