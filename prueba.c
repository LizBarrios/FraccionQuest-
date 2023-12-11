#include "raylib.h"
#include <stdio.h>
#include <string.h>
#define MAX_SYMBOLS 100
// click para mutear y desmutear
const int click_sonido_x_inicial = 1290;
const int click_sonido_x_final = 1356;
const int click_sonido_y_inicial = 0;
const int click_sonido_y_final = 60;
typedef enum
{
    MENU,
    INICIO,
    NIVELES,
    SALIR,
    NIVEL1,
    NIVEL2,
    NIVEL3,
    NIVEL4,
    NIVEL5

} Escena;

typedef struct
{
    Vector2 position;
    char symbol;
    Color color;
    float speed;
} Symbol;

// Función para guardar el progreso en un archivo de texto
void SaveProgress(int level, int score)
{
    FILE *file = fopen("progress.txt", "w"); // Abre el archivo para escritura

    if (file != NULL)
    {
        fprintf(file, "%d %d", level, score); // Escribe los datos en el archivo
        fclose(file);                         // Cierra el archivo
    }
}

// Función para cargar el progreso desde un archivo de texto
void LoadProgress(int *level, int *score)
{
    FILE *file = fopen("progress.txt", "r"); // Abre el archivo para lectura

    if (file != NULL)
    {
        fscanf(file, "%d %d", level, score); // Lee los datos del archivo
        fclose(file);                        // Cierra el archivo
    }
}

void finalizar_juego()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        CloseWindow(); // Cierra la ventana y finaliza el juego
    }
}
int main(void)
{
    const int ancho_pantalla = 1920;
    const int alto_pantalla = 1080;
    InitWindow(ancho_pantalla, alto_pantalla, "FractionQuest");
    InitAudioDevice();
    SetTargetFPS(30);
    //=========================
    // fuardado y cargado del proceso
    int currentLevel = 0;
    int currentScore = 0;
    LoadProgress(&currentLevel, &currentScore);

    // Al terminar un nivel o actualizar la puntuación, guardar el progreso
    currentScore += 1000; // Por ejemplo, agregar 1000 puntos

    SaveProgress(currentLevel, currentScore); // Guardar el progreso actualizado
    //=============================

    Escena escenaActual = MENU; // Inicialmente, se comienza en la escena de menú

    Texture2D sonido = LoadTexture("C:/Users/danie/OneDrive/Desktop/juego/resources/sonido.png");
    Texture2D tacha_niveles = LoadTexture("C:/Users/danie/OneDrive/Desktop/juego/resources/cerrar.png");

    Music music = LoadMusicStream("resources/Nintendo 3DS Music - Mii Maker.mp3");
    music.looping = true;
    bool pause = false;

    PlayMusicStream(music);
    SetMusicVolume(music, 0.5); // Establecer el volumen al 50%
    float contador_segundos = 0.0f;

    while (contador_segundos < 4.0f && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Dibuja el texto de "Cargando..."
        DrawText("Cargando...", ancho_pantalla / 2 - MeasureText("Cargando...", 40) / 2, alto_pantalla / 2 - 40, 40, WHITE);

        EndDrawing();

        // Incrementa el contador con el tiempo transcurrido en cada fotograma
        contador_segundos += GetFrameTime();
    }
    Symbol symbols[MAX_SYMBOLS];
    while (!WindowShouldClose())
    {
        BeginDrawing();
        UpdateMusicStream(music); // Actualiza la música si es necesario
        DrawTexture(sonido, 1290, 0, WHITE);

        switch (escenaActual)
        {
        case MENU:
  for (int i = 0; i < MAX_SYMBOLS; i++)
    {
        symbols[i].position.x = GetRandomValue(0, screenWidth);
        symbols[i].position.y = -GetRandomValue(0, screenHeight);
        symbols[i].symbol = "+x-/"[GetRandomValue(0, 3)]; // Símbolos: suma, resta, multiplicación, fracción
        symbols[i].color = (Color){GetRandomValue(100, 255), GetRandomValue(100, 255), GetRandomValue(100, 255), 255};
        symbols[i].speed = (float)GetRandomValue(50, 1000) / 100.0f; // Velocidad aleatoria
    }
    while (escenaActual == MENU)
    {
        UpdateMusicStream(music); // Actualiza la música si es necesario
        DrawTexture(sonido, 1792, 0, WHITE); // Ajuste de posición del botón de sonido
        for (int i = 0; i < MAX_SYMBOLS; i++)
        {
            symbols[i].position.y += symbols[i].speed;

            // Si el símbolo llega al final de la pantalla, reiniciar su posición arriba
            if (symbols[i].position.y > screenHeight)
            {
                symbols[i].position.y = -GetRandomValue(0, screenHeight);
                symbols[i].position.x = GetRandomValue(0, screenWidth);
            }
        }

        ClearBackground(BLACK);

        // Código para dibujar los símbolos, rectángulos y textos...

        // Aquí se ajustan las coordenadas y los tamaños de los elementos según la resolución 1920x1080

        // ...

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();

            // Manejo de clics en diferentes áreas según la resolución

            // ...
        }
        finalizar_juego();
        EndDrawing();
    }
}
break;            break;

        case INICIO:
            // Lógica y dibujado para la escena de inicio
            break;

        case NIVELES:
            // Lógica y dibujado para la escena de selección de niveles
            break;

        case SALIR:
            // Lógica para salir del juego
            break;

        case NIVEL1:
            // Lógica y dibujado para el nivel 1
            break;

        case NIVEL2:
            // Lógica y dibujado para el nivel 2
            break;

        case NIVEL3:
            // Lógica y dibujado para el nivel 3
            break;

        case NIVEL4:
            // Lógica y dibujado para el nivel 4
            break;

        case NIVEL5:
            // Lógica y dibujado para el nivel 5
            break;

        default:
            break;
        }

        finalizar_juego(); // Función para finalizar el juego si se presiona la tecla ESC

        EndDrawing();
    }

    UnloadTexture(sonido);
    StopMusicStream(music);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
