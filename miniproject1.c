#include <stdio.h>

#define ROWS 20
#define COLS 50

char canvas[ROWS][COLS];

void clearCanvas() {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            canvas[i][j] = ' ';
        }
    }
}

void displayCanvas() {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void drawLine(int row,int colStart, int colEnd){
    for(int j = colStart; j <= colEnd; j++){
        canvas[row][j]= '*';
    }
}


void drawRectangle(int x1, int y1, int x2, int y2) {
    // Top and bottom horizontal lines
    for (int x = x1; x <= x2; x++) {
        if (x >= 0 && x < COLS) {
            if (y1 >= 0 && y1 < ROWS) canvas[y1][x] = '*'; 
            if (y2 >= 0 && y2 < ROWS) canvas[y2][x] = '*'; 
        }
    }

    // Left and right vertical lines
    for (int y = y1; y <= y2; y++) {
        if (y >= 0 && y < ROWS) {
            if (x1 >= 0 && x1 < COLS) canvas[y][x1] = '*';
            if (x2 >= 0 && x2 < COLS) canvas[y][x2] = '*';
        }
    }
}

void drawTriangle(int topX, int topY, int height) {
    int leftX = topX;
    int rightX = topX;

    for (int i = 0; i < height; i++) {
        int currentY = topY + i;

        if (currentY >= 0 && currentY < ROWS) {
            if (leftX >= 0 && leftX < COLS) canvas[currentY][leftX] = '*';
            if (rightX >= 0 && rightX < COLS) canvas[currentY][rightX] = '*';

            // This fixes the bottom line so it connects the sides perfectly
            if (i == height - 1) {
                for (int x = leftX; x <= rightX; x++) {
                    if (x >= 0 && x < COLS) {
                        canvas[currentY][x] = '*'; 
                    }
                }
            }
        }
        leftX--;
        rightX++;
    }
}
int main() {
    clearCanvas();      
    
    drawRectangle(5, 4, 18, 14);
    drawTriangle(35, 3, 10);
    
    displayCanvas();
    return 0;
}