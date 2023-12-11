#include "raylib.h"
#define MAX_SYMBOLS 100

typedef struct
{
    Vector2 position;
    char symbol;
    Color color;
    float speed;
} Symbol;

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;


    while (!WindowShouldClose())
    {
        Texture2D Fondo_1 = LoadTexture("resources/nivel1/nivel1_1.png");
        Texture2D Respuesta_Correcta = LoadTexture("resources/BIEN\MAL/respuesta_buena.png");
        Texture2D Respuesta_Incorrecta = LoadTexture("resources/BIEN\MAL/respuesta_mala.png");

        ClearBackground(BLUE);
        DrawTexture(Fondo_1, 0, 0, WHITE);
        DrawTexture(Respuesta_Correcta, 1800, 1000, WHITE);

        finalizar_juego();
       
        EndDrawing();

      
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
