#include <iostream>
#include <raylib.h>
#include "csv.hpp"
#include "config.h"

#define SIZE 20
#define W 500

using namespace std;
using namespace csv;

void print(int m[SIZE][SIZE]){
    cout << "\n\n";
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            cout << m[i][j] << " ";
        }
        cout << '\n';
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
    CSVFormat format;
    format.delimiter(',').no_header();
    int m[SIZE][SIZE];

    CSVReader reader("starter", format);
    int i = 0;
    int j = 0;
    for (CSVRow &row: reader){
        for (CSVField &field: row){
            m[i][j] = stoi(field.get<>());
            j++;   
        }
        i++;
        j=0;
    }


    SetTargetFPS(10);
    InitWindow(W, W, "Conway's Game of Life");
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(GetColor(0x181818AA));
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                if (m[i][j] == 1){
                    DrawRectangle(i*W/SIZE, j*W/SIZE, W/SIZE, W/SIZE, RED);
                }
            }
        }
        EndDrawing();
        update(m);
    }
}
