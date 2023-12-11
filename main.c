#include "raylib.h"
#define MAX_SYMBOLS 100

void applyBlurEffect()
{
    const int ancho_pantalla = 1920;
    const int alto_pantalla = 1080;
    const char *backgroundPath = "resources/background.png";
    const char *shaderPath = "resources/shaders/blur.fs";
    const float blurRadius = 10.0f;
    int marginX = 3; // Margen horizontal
    int marginY = 3; // Margen vertical

    InitWindow(ancho_pantalla, alto_pantalla, "Blur Effect - Raylib");

    // Carga de la imagen de fondo
    Texture2D background = LoadTexture(backgroundPath);

    // Carga del shader de desenfoque
    Shader shaderBlur = LoadShader(0, shaderPath);

    // Modifica el shader para el nivel de desenfoque deseado
    SetShaderValue(shaderBlur, GetShaderLocation(shaderBlur, "screenWidth"), &ancho_pantalla, SHADER_UNIFORM_INT);
    SetShaderValue(shaderBlur, GetShaderLocation(shaderBlur, "screenHeight"), &alto_pantalla, SHADER_UNIFORM_INT);
    SetShaderValue(shaderBlur, GetShaderLocation(shaderBlur, "radius"), &blurRadius, SHADER_UNIFORM_FLOAT);

    // Aplicar desenfoque al fondo antes de entrar al bucle principal
    BeginShaderMode(shaderBlur);
    DrawTexture(background, 0, 0, WHITE);
    EndShaderMode();

    // Bucle principal del programa
    while (!WindowShouldClose())
    {
        // Resto del código para mostrar la interfaz de confirmación de salida
        // ...

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

        EndDrawing();
    }

    UnloadShader(shaderBlur);
    UnloadTexture(background);
    CloseWindow();
}

int main(void)
{
    // Inicializar la ventana
    const int ancho_pantalla = 1920;
    const int alto_pantalla = 1080;

    InitWindow(ancho_pantalla, alto_pantalla, "Ejemplo de imagen");
    while (!WindowShouldClose())
    {
        // Resto del código...
        UpdateMusicStream(music);
        // DrawTexture(Fondo_de_menu, 0, 0, WHITE);
        Mostrarguardado();
        DrawTexture(sonido, 1770, 10, WHITE);
        DrawRectangle(235, 150, 256, 256, RED);
        DrawText("inicio", 310, 260, 30, BLACK);
        finalizar_juego();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
