#include "raylib.h"
#define MAX_SYMBOLS 100

typedef struct
{
    Vector2 position;
    char symbol;
    Color color;
    float speed;
} Symbol;
void MostrarAutoguardado();

int main(void)
{
    // Inicializar la ventana
    const int ancho_pantalla = 1920;
    const int alto_pantalla = 1080;

    InitWindow(ancho_pantalla, alto_pantalla, "Ejemplo de imagen");

    // Cargar la imagen

    // Resto del código...

    // Bucle principal
    int contador_1 = 0;
    while (!WindowShouldClose())
    {
        // Resto del código...

        BeginDrawing();

        ClearBackground(BLACK);
        // Texture2D candados_de_niveles = LoadTexture("resources/candado.png");

        // Dibujar la imagen en la ventana
        DrawText(TextFormat("%d/5", contador_1), (ancho_pantalla / 2) - 643, (alto_pantalla / 2) - 435, 50, WHITE);

        DrawRectangle(235, 150, 256, 256, RED);
        DrawText("SUMAS", 310, 260, 30, BLACK);

        DrawRectangle(635, 150, 256, 256, YELLOW);
        DrawText("RESTAS", 698, 260, 30, BLACK);
        // DrawTexture(candados_de_niveles, 635, 150, BLACK);

        DrawRectangle(1035, 150, 256, 256, BLUE);
        DrawText("MULTIPLICACION", 1045, 260, 28, BLACK);
        // DrawTexture(candados_de_niveles, 1035, 150, BLACK);

        DrawRectangle(1435, 150, 256, 256, GREEN);
        DrawText("DIVISION", 1495, 260, 30, BLACK);
        // DrawTexture(candados_de_niveles, 1435, 150, BLACK);

        DrawRectangle(235, 600, 256, 256, PURPLE);
        DrawText("FRACCIONES", 260, 715, 30, BLACK);
        //  DrawTexture(candados_de_niveles, 235, 600, BLACK);

        DrawRectangle(635, 600, 256, 256, GRAY);
        DrawText("Proximamente!", 645, 715, 35, BLACK);
        MostrarAutoguardado();
        // Resto del código...

        EndDrawing();

        // Resto del código...
    }

    // Resto del código...

    // Descargar la textura al finalizar
    // Resto del código...

    CloseWindow();

    return 0;
}
void MostrarAutoguardado()
{
    const int ancho_pantalla = 1920;
    const int alto_pantalla = 1080;
    double tiempoInicial = GetTime();

    while (!WindowShouldClose())
    {
        double tiempoActual = GetTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (tiempoActual - tiempoInicial <= 3.0)
        {
            DrawText("Autoguardado", ancho_pantalla / 2 - MeasureText("Autoguardado", 40) / 2, alto_pantalla / 2 - 20, 40, BLACK);
        }
        else
        {
            break;
        }

        EndDrawing();
    }
}

/*
       Texture2D Fondo_1 = LoadTexture("resources/nivel1/nivel1_1.png");
       Texture2D Respuesta_Correcta = LoadTexture("resources/BIEN_MAL/respuesta_buena.png");
       Texture2D Respuesta_Incorrecta = LoadTexture("resources/BIEN_MAL/respuesta_mala.png");
       int contador = 0;
       ClearBackground(BLUE);
       DrawTexture(Fondo_1, 0, 0, WHITE);
       DrawTexture(Respuesta_Incorrecta, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
       DrawTexture(Respuesta_Correcta, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
       DrawTexture(Respuesta_Correcta, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
       DrawTexture(Respuesta_Incorrecta, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
       DrawTexture(Respuesta_Incorrecta, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
       DrawText(TextFormat("%d/5", contador), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);
       DrawRectangle(1266.3, 186.2, 151.1, 215.6, BLUE);
       DrawRectangle(1266.3, 433.6, 151.1, 215.6, RED);
       DrawRectangle(1263.4, 681, 151.1, 215.6, GREEN);
*/