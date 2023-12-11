#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Inicializar raylib
    InitWindow(screenWidth, screenHeight, "Imagen siguiendo el mouse");
    SetTargetFPS(60);

    // Cargar la imagen desde la ruta adecuada
    Texture2D image = LoadTexture("resources/raton.png");
    Texture2D image1 = LoadTexture("resources/raton.png");
    Texture2D image2 = LoadTexture("resources/raton3.png");

    // Ocultar el cursor predeterminado
    HideCursor();

    while (!WindowShouldClose())
    {
        // Detectar la posición del cursor del mouse
        Vector2 mouse = GetMousePosition();

        // Iniciar el dibujo
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dibujar la imagen en la posición del cursor
        DrawTexture(image, mouse.x, mouse.y, WHITE);
    if (IsKeyDown(KEY_A))
        {
            image = image2;
        }
        if (IsKeyDown(KEY_D))
        {
            image = image1;
        }
        // Finalizar el dibujo
        EndDrawing();
    }

    // Liberar la textura al salir
    UnloadTexture(image);

    // Mostrar el cursor antes de cerrar
    ShowCursor();

    // Cerrar raylib
    CloseWindow();

    return 0;
}
