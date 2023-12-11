#include "raylib.h"

// Variables globales para las dimensiones de la pantalla
const int ancho_pantalla = 1920;
const int alto_pantalla = 1080;

// Función para aplicar el efecto de desenfoque al fondo
void applyBlurEffect()
{
    const char *backgroundPath = "resources/background.png";
    Texture2D background = LoadTexture(backgroundPath);
    Shader shaderBlur = LoadShader(0, "resources/shaders/blur.fs");

    // Modifica el shader para el nivel de desenfoque deseado
    SetShaderValue(shaderBlur, GetShaderLocation(shaderBlur, "ancho_pantalla"), &ancho_pantalla, SHADER_UNIFORM_INT);
    SetShaderValue(shaderBlur, GetShaderLocation(shaderBlur, "alto_pantalla"), &alto_pantalla, SHADER_UNIFORM_INT);
    SetShaderValue(shaderBlur, GetShaderLocation(shaderBlur, "radius"), &(float){10.0f}, SHADER_UNIFORM_FLOAT);

    int marginX = 3; // Margen horizontal
    int marginY = 3; // Margen vertical

    BeginShaderMode(shaderBlur);
    DrawTexture(background, 0, 0, WHITE);
    DrawRectangle((ancho_pantalla / 2) - 525, (alto_pantalla / 2) - 205, 1010, 360, WHITE);
    DrawRectangle((ancho_pantalla / 2) - 520, (alto_pantalla / 2) - 200, 1000, 350, BLACK);
    DrawRectangle((ancho_pantalla / 2) - 508, (alto_pantalla / 2) - 150, 975, 120, WHITE);
    DrawText("Seguro que quiere salir del juego?", ((ancho_pantalla / 2) - 500) + marginX, ((alto_pantalla / 2) - 120) + marginY, 55, GRAY);
    DrawText("Seguro que quiere salir del juego?", (ancho_pantalla / 2) - 500, (alto_pantalla / 2) - 120, 55, BLACK);
    DrawRectangle((ancho_pantalla / 2) - 375, (alto_pantalla / 2) + 5, 200, 90, WHITE);
    DrawText("Si", ((ancho_pantalla / 2) - 300) + marginX, ((alto_pantalla / 2) + 25) + marginY, 55, GRAY);
    DrawText("Si", (ancho_pantalla / 2) - 300, (alto_pantalla / 2) + 25, 55, BLACK);
    DrawRectangle((ancho_pantalla / 2) + 135, (alto_pantalla / 2) + 5, 200, 90, WHITE);
    DrawText("NO", ((ancho_pantalla / 2)) + marginX + 200, ((alto_pantalla / 2) + 25) + marginY, 55, GRAY);
    DrawText("NO", (ancho_pantalla / 2) + 200, (alto_pantalla / 2) + 25, 55, BLACK);

    EndShaderMode();
    UnloadShader(shaderBlur);
    UnloadTexture(background);
}

int main(void)
{
    InitWindow(ancho_pantalla, alto_pantalla, "Blur Effect - Raylib");

    // Carga de la imagen de fondo

    // Carga del shader de desenfoque

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(575, 275, 1610, 260, WHITE);
        DrawRectangle(580, 280, 1600, 250, BLACK);
        DrawRectangle(550, 250, 1570, 220, LIGHTGRAY);

        DrawRectangle(795, 745, 1010, 680, WHITE);
        DrawRectangle(800, 750, 1000, 670, BLACK);

        applyBlurEffect();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
