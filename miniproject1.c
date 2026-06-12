#include <stdio.h>
#include <stdlib.h> // Required for abs()
#include <math.h>   // Required for sqrt() and round()

#define ROWS 20
#define COLS 50

char canvas[ROWS][COLS];

// --- 1. EXTERNAL FUNCTION PROTOTYPES (All standardized to 4 arguments) ---
void clearCanvas();
void displayCanvas();
void drawLine(int x1, int y1, int x2, int y2);
void drawRectangle(int x1, int y1, int x2, int y2);
void drawTriangle(int topX, int topY, int height, int dummy);
void drawCircle(int cx, int cy, int radius, int dummy);

// --- 2. OBJECT MANAGEMENT DATA STRUCTURES ---
typedef enum { LINE, RECTANGLE, TRIANGLE, CIRCLE } ShapeType;

typedef struct {
    ShapeType type;
    int p1, p2, p3, p4; // Every shape gets exactly 4 parameter slots
    int active;         // 1 = Visible, 0 = Deleted
} Shape;

#define MAX_SHAPES 50
Shape shapeList[MAX_SHAPES];
int shapeCount = 0;


// --- 3. CANVAS BASIC UTILITIES ---
void clearCanvas() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            canvas[r][c] = ' '; 
        }
    }
}

void displayCanvas() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            printf("%c", canvas[r][c]);
        }
        printf("\n");
    }
}


// --- 4. CORE SHAPE DRAWING FUNCTIONS ---

void drawLine(int x1, int y1, int x2, int y2) {
    int steps = abs(x2 - x1) > abs(y2 - y1) ? abs(x2 - x1) : abs(y2 - y1);
    if (steps == 0) steps = 1;
    float xInc = (float)(x2 - x1) / steps;
    float yInc = (float)(y2 - y1) / steps;
    
    float currentX = x1;
    float currentY = y1;
    for (int step = 0; step <= steps; step++) {
        int ix = (int)round(currentX);
        int iy = (int)round(currentY);
        if (ix >= 0 && ix < COLS && iy >= 0 && iy < ROWS) {
            canvas[iy][ix] = '*';
        }
        currentX += xInc;
        currentY += yInc;
    }
}

void drawRectangle(int x1, int y1, int x2, int y2) {
    for (int x = x1; x <= x2; x++) {
        if (x >= 0 && x < COLS) {
            if (y1 >= 0 && y1 < ROWS) canvas[y1][x] = '*';
            if (y2 >= 0 && y2 < ROWS) canvas[y2][x] = '*';
        }
    }
    for (int y = y1; y <= y2; y++) {
        if (y >= 0 && y < ROWS) {
            if (x1 >= 0 && x1 < COLS) canvas[y][x1] = '*';
            if (x2 >= 0 && x2 < COLS) canvas[y][x2] = '*';
        }
    }
}

void drawTriangle(int topX, int topY, int height, int dummy) {
    int leftX = topX;
    int rightX = topX;
    for (int level = 0; level < height; level++) {
        int currentY = topY + level;
        if (currentY >= 0 && currentY < ROWS) {
            if (leftX >= 0 && leftX < COLS) canvas[currentY][leftX] = '*';
            if (rightX >= 0 && rightX < COLS) canvas[currentY][rightX] = '*';
            if (level == height - 1) {
                for (int x = leftX; x <= rightX; x++) {
                    if (x >= 0 && x < COLS) canvas[currentY][x] = '*';
                }
            }
        }
        leftX--;
        rightX++;
    }
}

void drawCircle(int cx, int cy, int radius, int dummy) {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            double dx = (x - cx) / 1.5; 
            double dy = y - cy;
            double distance = sqrt(dx * dx + dy * dy);

            if (round(distance) == radius) {
                if (y >= 0 && y < ROWS && x >= 0 && x < COLS) {
                    canvas[y][x] = '*';
                }
            }
        }
    }
}


// --- 5. OBJECT MANAGEMENT DATABASE SYSTEM ---

void addObject(ShapeType type, int p1, int p2, int p3, int p4) {
    if (shapeCount < MAX_SHAPES) {
        shapeList[shapeCount].type = type;
        shapeList[shapeCount].p1 = p1;
        shapeList[shapeCount].p2 = p2;
        shapeList[shapeCount].p3 = p3;
        shapeList[shapeCount].p4 = p4;
        shapeList[shapeCount].active = 1;
        shapeCount++;
    }
}

void deleteObject(int index) {
    if (index >= 0 && index < shapeCount) {
        shapeList[index].active = 0;
    }
}

void modifyObject(int index, int p1, int p2, int p3, int p4) {
    if (index >= 0 && index < shapeCount && shapeList[index].active) {
        shapeList[index].p1 = p1;
        shapeList[index].p2 = p2;
        shapeList[index].p3 = p3;
        shapeList[index].p4 = p4;
    }
}

void renderScene() {
    clearCanvas();
    for (int i = 0; i < shapeCount; i++) {
        if (shapeList[i].active) {
            // Every single function call below takes exactly 4 struct attributes!
            if (shapeList[i].type == LINE) {
                drawLine(shapeList[i].p1, shapeList[i].p2, shapeList[i].p3, shapeList[i].p4);
            } 
            else if (shapeList[i].type == RECTANGLE) {
                drawRectangle(shapeList[i].p1, shapeList[i].p2, shapeList[i].p3, shapeList[i].p4);
            } 
            else if (shapeList[i].type == TRIANGLE) {
                drawTriangle(shapeList[i].p1, shapeList[i].p2, shapeList[i].p3, shapeList[i].p4);
            } 
            else if (shapeList[i].type == CIRCLE) {
                drawCircle(shapeList[i].p1, shapeList[i].p2, shapeList[i].p3, shapeList[i].p4);
            }
        }
    }
}


// --- 6. DISPLAY CONTROLLER MAIN ---
int main() {
    shapeCount = 0; 

    // Add all 4 shapes systematically side-by-side
    addObject(LINE, 1, 2, 8, 9);         // Object 0
    addObject(RECTANGLE, 12, 2, 22, 10); // Object 1
    addObject(TRIANGLE, 31, 2, 6, 0);    // Object 2
    addObject(CIRCLE, 43, 7, 4, 0);      // Object 3

    renderScene();
    displayCanvas();

    return 0;
}