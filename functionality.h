/* Rida Fatima, Maneha Bint E Tariq
2503567, 2503565
PF Project*/

#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include "utils.h"
#include "pieces.h"
#include <fstream>
#include <algorithm>


void clearLines();
void restartGame();
void loadHighScores();
void saveHighScores();




int getColorByShape(int shapeIndex)
{
    int shapeColor[7] = {
        6, // I - light blue
        2, // J - dark blue
        7, // L - orange
        3, // O - yellow
        4, // S - green
        5, // Z - red
        1  // T - magenta
    };
    return shapeColor[shapeIndex];
}

/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
/*void fallingPiece(float& timer, float& delay){
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        if (!anamoly()){
            int n=rand()%7;
            //--- Un-Comment this Part When You Make BLOCKS array---//
            /*
                for (int i=0;i<4;i++){
                    point_1[i][0] = BLOCKS[n][i] % 2;
                    point_1[i][1] = BLOCKS[n][i] / 2;
                }
            *//*
        }
        timer=0;
    }
}*/



void fallingPiece(float& timer, float& delay)
{
    if (timer > delay)
    {
        for (int i = 0; i < 4; i++)
        {
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];
            point_1[i][1] += 1;
        }

        if (!anamoly())
        {
            // LOCK piece
            for (int i = 0; i < 4; i++)
                gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;

            clearLines();

            // GAME OVER CHECK
                for (int i = 0; i < 4; i++)
                {
                    if (gameGrid[point_2[i][1]][point_2[i][0]] && point_2[i][1] == 0)
                    {
                        gameOver = true;
                        return;
                    }
                }

            // NEW piece
            int n = rand() % 7;
            colorNum = getColorByShape(n);
            for (int i = 0; i < 4; i++)
            {
                point_1[i][0] = BLOCKS[n][i] % 2 + N / 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
            }
        }
        timer = 0;
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
#pragma once
#include "utils.h"
#include "pieces.h"

// Global score
int score = 0;

// --- Move Piece Left / Right ---
void movePiece(int dx)
{
    for (int i = 0; i < 4; i++)
    {
        point_2[i][0] = point_1[i][0];
        point_2[i][1] = point_1[i][1];
        point_1[i][0] += dx;
    }

    if (!anamoly())
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][0] = point_2[i][0];
            point_1[i][1] = point_2[i][1];
        }
    }
}

// --- Rotate Piece ---
void rotatePiece()
{
    int cx = point_1[1][0]; // pivot
    int cy = point_1[1][1];

    for (int i = 0; i < 4; i++)
    {
        int x = point_1[i][1] - cy;
        int y = point_1[i][0] - cx;
        point_1[i][0] = cx - x;
        point_1[i][1] = cy + y;
    }

    if (!anamoly())
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][0] = point_2[i][0];
            point_1[i][1] = point_2[i][1];
        }
    }
}

// --- Lock Piece & Generate New ---
void lockPiece()
{
    for (int i = 0; i < 4; i++)
        gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;


    int n = rand() % 7;
    colorNum = getColorByShape(n);
    for (int i = 0; i < 4; i++)
    {
        point_1[i][0] = BLOCKS[n][i] % 2 + N / 2;
        point_1[i][1] = BLOCKS[n][i] / 2;
    }

    // 🔥 GAME OVER CHECK (CORRECT PLACE)
    for (int i = 0; i < 4; i++)
    {
        if (gameGrid[point_1[i][1]][point_1[i][0]])
        {
            gameOver = true;
            return;
        }
    }
}


// --- Clear Lines ---
void clearLines()
{
    int k = M - 1;
    int linesCleared = 0;

    for (int i = M - 1; i >= 0; i--)
    {
        int count = 0;
        for (int j = 0; j < N; j++)
        {
            if (gameGrid[i][j])
                count++;
            gameGrid[k][j] = gameGrid[i][j];
        }

        if (count < N)
            k--;
        else
            linesCleared++;
    }

    if (linesCleared == 1)
        score += 10 * currentLevel;
    else if (linesCleared == 2)
        score += 30 * currentLevel;
    else if (linesCleared == 3)
        score += 60 * currentLevel;
    else if (linesCleared >= 4)
        score += 100 * currentLevel;
}


void restartGame()
{
    // Clear grid
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            gameGrid[i][j] = 0;

    // Reset score
    score = 0;

    // Reset game over flag
    gameOver = false;

    // Generate new piece
    int n = rand() % 7;
    colorNum = getColorByShape(n);

    for (int i = 0; i < 4; i++)
    {
        point_1[i][0] = BLOCKS[n][i] % 2 + N / 2;
        point_1[i][1] = BLOCKS[n][i] / 2;
    }
}
void loadHighScores()
{
    std::ifstream file("highscores.txt");

    for (int i = 0; i < 10; i++)
    {
        if (!(file >> highScores[i]))
            highScores[i] = 0;
    }

    file.close();
}
void saveHighScores()
{
    std::ofstream file("highscores.txt");

    for (int i = 0; i < 10; i++)
        file << highScores[i] << std::endl;

    file.close();
}

// --- Falling Piece ---


///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////

#endif