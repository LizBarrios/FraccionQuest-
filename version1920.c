#include "raylib.h"
#include <stdio.h>
#include <string.h>
#define MAX_SYMBOLS 100
// click para mutear y desmutear
const int click_sonido_x_inicial = 1770;
const int click_sonido_x_final = 2060;
const int click_sonido_y_inicial = 10;
const int click_sonido_y_final = 140;
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

    Texture2D sonido = LoadTexture("resources/sonido.png");
    Texture2D candados_de_niveles = LoadTexture("resources/candado.png");

    Music music = LoadMusicStream("resources/Nintendo 3DS Music - Mii Maker.mp3");
    music.looping = true;
    bool pause = false;

    PlayMusicStream(music);
    SetMusicVolume(music, 0.5); // Establecer el volumen al 50%
    // ==========      PANTALLA DE CARGA      ===============
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
        DrawTexture(sonido, 1770, 10, WHITE);

        switch (escenaActual)
        {
        case MENU:
        {
            int marginX = 10; // Margen horizontal
            int marginY = 10; // Margen vertical

            for (int i = 0; i < MAX_SYMBOLS; i++)
            {
                symbols[i].position.x = GetRandomValue(0, ancho_pantalla);
                symbols[i].position.y = -GetRandomValue(0, alto_pantalla);
                symbols[i].symbol = "+x-/"[GetRandomValue(0, 3)]; // Símbolos: suma, resta, multiplicación, fracción
                symbols[i].color = (Color){GetRandomValue(100, 255), GetRandomValue(100, 255), GetRandomValue(100, 255), 255};
                symbols[i].speed = (float)GetRandomValue(50, 1000) / 100.0f; // Velocidad aleatoria
            }

            while (escenaActual == MENU)
            {
                //******************************************************** MUSICA **********************************************************************************

                UpdateMusicStream(music);
                DrawTexture(sonido, 1770, 10, WHITE);

                //******************************************************** FONDO Y PANTALLA **********************************************************************************

                for (int i = 0; i < MAX_SYMBOLS; i++)
                {
                    symbols[i].position.y += symbols[i].speed;

                    // Si el símbolo llega al final de la pantalla, reiniciar su posición arriba
                    if (symbols[i].position.y > alto_pantalla)
                    {
                        symbols[i].position.y = -GetRandomValue(0, alto_pantalla);
                        symbols[i].position.x = GetRandomValue(0, ancho_pantalla);
                    }
                }

                if (IsKeyPressed(KEY_F11))
                { // Cambia a pantalla completa al presionar F11
                    ToggleFullscreen();
                }
                ClearBackground(BLACK);

                for (int i = 0; i < MAX_SYMBOLS; i++)
                {
                    char symbolStr[2] = {symbols[i].symbol, '\0'}; // Convertir el símbolo a una cadena de caracteres
                    DrawTextEx(GetFontDefault(), symbolStr, symbols[i].position, 40, 0, symbols[i].color);
                }

                //******************************************************** TITULO **********************************************************************************

                // DrawRectangle(345, 125, 1175, 175, WHITE);
                // DrawRectangle(350, 130, 1165, 165, BLACK);

                DrawText("FractionQuest!", ancho_pantalla / 2 - 450 - MeasureText("FractionQuest!", 40) / 2 + marginX + 10, alto_pantalla / 2 - 400 + marginY + 10, 150, GREEN);
                DrawText("FractionQuest!", ancho_pantalla / 2 - 450 - MeasureText("FractionQuest!", 40) / 2 + marginX, alto_pantalla / 2 - 400 + marginY, 150, BLUE);
                DrawText("FractionQuest!", ancho_pantalla / 2 - 450 - MeasureText("FractionQuest!", 40) / 2, alto_pantalla / 2 - 400, 150, YELLOW);

                //******************************************************** MENU **********************************************************************************

                DrawRectangle(500, 510, 800, 462, WHITE); // marco blanco
                DrawRectangle(505, 515, 790, 452, BLACK); // marco negro

                DrawRectangle((ancho_pantalla / 2) - 448, (alto_pantalla / 2) - 15, 775, 100, WHITE); // rectangulo del menu de opciones de iniciar
                DrawText("INICIAR", ancho_pantalla / 2 - 135, alto_pantalla / 2 + 10, 50, DARKGRAY);
                const int click_inicio_x_inicial = (ancho_pantalla / 2) - 448;
                const int click_inicio_x_final = (ancho_pantalla / 2) + 327;
                const int click_inicio_y_inicial = (alto_pantalla / 2) - 15;
                const int click_inicio_y_final = (alto_pantalla / 2) + 85;

                DrawRectangle((ancho_pantalla / 2) - 448, (alto_pantalla / 2) + 96, 775, 100, WHITE);
                DrawText("NIVELES", (ancho_pantalla / 2) - 155, (alto_pantalla / 2) + 130, 50, DARKGRAY);
                const int click_niveles_x_inicial = (ancho_pantalla / 2) - 440;
                const int click_niveles_x_final = (ancho_pantalla / 2) + 327;
                const int click_niveles_y_inicial = (alto_pantalla / 2) + 96;
                const int click_niveles_y_final = (alto_pantalla / 2) + 196;

                DrawRectangle((ancho_pantalla / 2) - 448, (alto_pantalla / 2) + 207, 775, 100, WHITE);
                DrawText("CARGAR PROGRESO", (ancho_pantalla / 2) - 280, (alto_pantalla / 2) + 240, 50, DARKGRAY);
                // const int click_CARGAR_PROGRESO_x_inicial = (ancho_pantalla / 2) - 460;
                // const int click_CARGAR_PROGRESO_x_final = (ancho_pantalla / 2) + 485;
                // const int click_CARGAR_PROGRESO_y_inicial = (alto_pantalla / 2) + 295;
                // const int click_CARGAR_PROGRESO_y_final = (alto_pantalla / 2) +405;

                DrawRectangle((ancho_pantalla / 2) - 448, (alto_pantalla / 2) + 317, 775, 100, WHITE);
                DrawText("SALIR", (ancho_pantalla / 2) - 120, (alto_pantalla / 2) + 350, 50, DARKGRAY);
                const int click_salir_x_inicial = (ancho_pantalla / 2) - 448;
                const int click_salir_x_final = (ancho_pantalla / 2) + 327;
                const int click_salir_y_inicial = (alto_pantalla / 2) + 317;
                const int click_salir_y_final = (alto_pantalla / 2) + 417;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_sonido_x_inicial && mousePosition.x <= click_sonido_x_final &&
                        mousePosition.y >= click_sonido_y_inicial && mousePosition.y <= click_sonido_y_final)
                    {
                        pause = !pause; // Cambia el estado de pausa al contrario de su estado actual

                        if (pause) // Si el estado es pausa (true)
                        {
                            PauseMusicStream(music); // Pausa la música

                            sonido = LoadTexture("resources/sonido_mute.png"); // Cambia el sonido a una versión silenciada
                        }
                        else // Si el estado es no pausa (false)
                        {
                            ResumeMusicStream(music);                     // Reanuda la música
                            sonido = LoadTexture("resources/sonido.png"); // Cambia el sonido a su versión normal
                        }
                    }
                    if (mousePosition.x >= click_inicio_x_inicial && mousePosition.x <= click_inicio_x_final &&
                        mousePosition.y >= click_inicio_y_inicial && mousePosition.y <= click_inicio_y_final)
                    {
                        escenaActual = INICIO;
                    }
                    if (mousePosition.x >= click_niveles_x_inicial && mousePosition.x <= click_niveles_x_final &&
                        mousePosition.y >= click_niveles_y_inicial && mousePosition.y <= click_niveles_y_final)
                    {
                        escenaActual = NIVELES;
                    }
                    if (mousePosition.x >= click_salir_x_inicial && mousePosition.x <= click_salir_x_final &&
                        mousePosition.y >= click_salir_y_inicial && mousePosition.y <= click_salir_y_final)
                    {

                        escenaActual = SALIR;
                    }
                }
                finalizar_juego();
                EndDrawing();
            }
        }
        break;
        case INICIO:
        {
            ClearBackground(BLACK);
            DrawRectangle(580, 280, 1600, 250, WHITE);
            finalizar_juego();
            if (IsKeyPressed(KEY_J))
            {
                escenaActual = MENU;
            }
            EndDrawing();
        }
        break;
        case NIVELES:
        {
            for (int i = 0; i < MAX_SYMBOLS; i++)
            {
                symbols[i].position.x = GetRandomValue(0, ancho_pantalla);
                symbols[i].position.y = -GetRandomValue(0, alto_pantalla);
                symbols[i].symbol = "+x-/"[GetRandomValue(0, 3)]; // Símbolos: suma, resta, multiplicación, fracción
                symbols[i].color = (Color){GetRandomValue(100, 255), GetRandomValue(100, 255), GetRandomValue(100, 255), 255};
                symbols[i].speed = (float)GetRandomValue(50, 1000) / 100.0f; // Velocidad aleatoria
            }
            while (escenaActual == NIVELES)
            {
                UpdateMusicStream(music);
                DrawTexture(sonido, 1770, 10, WHITE);
                for (int i = 0; i < MAX_SYMBOLS; i++)
                {
                    symbols[i].position.y += symbols[i].speed;

                    // Si el símbolo llega al final de la pantalla, reiniciar su posición arriba
                    if (symbols[i].position.y > alto_pantalla)
                    {
                        symbols[i].position.y = -GetRandomValue(0, alto_pantalla);
                        symbols[i].position.x = GetRandomValue(0, ancho_pantalla);
                    }
                }
                ClearBackground(BLACK);

                for (int i = 0; i < MAX_SYMBOLS; i++)
                {
                    char symbolStr[2] = {symbols[i].symbol, '\0'}; // Convertir el símbolo a una cadena de caracteres
                    DrawTextEx(GetFontDefault(), symbolStr, symbols[i].position, 40, 0, symbols[i].color);
                }

                ClearBackground(BLACK);
                DrawRectangle(235, 150, 256, 256, RED);
                DrawText("SUMAS", 310, 260, 30, BLACK);
                const int click_nivel1_x_inicial = 135;
                const int click_nivel1_x_final = 647;
                const int click_nivel1_y_inicial = 200;
                const int click_nivel1_y_final = 512;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel1_x_inicial && mousePosition.x <= click_nivel1_x_final &&
                        mousePosition.y >= click_nivel1_y_inicial && mousePosition.y <= click_nivel1_y_final)
                    {
                        escenaActual = NIVEL1;
                    }
                }
                if (currentLevel >= 1)
                {
                    DrawRectangle(635, 150, 256, 256, YELLOW);
                    DrawText("RESTAS", 698, 260, 30, BLACK);
                    const int click_nivel2_x_inicial = 735;
                    const int click_nivel2_x_final = 1247;
                    const int click_nivel2_y_inicial = 200;
                    const int click_nivel2_y_final = 512;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 mousePosition = GetMousePosition();
                        if (mousePosition.x >= click_nivel2_x_inicial && mousePosition.x <= click_nivel2_x_final &&
                            mousePosition.y >= click_nivel2_y_inicial && mousePosition.y <= click_nivel2_y_final)
                        {
                            escenaActual = NIVEL2;
                        }
                    }
                }
                else
                {
                    DrawRectangle(635, 150, 256, 256, YELLOW);
                    DrawText("RESTAS", 698, 260, 30, BLACK);
                    DrawTexture(candados_de_niveles, 635, 150, BLACK);
                }
                if (currentLevel >= 2)
                {
                    DrawRectangle(1035, 150, 256, 256, BLUE);
                    DrawText("MULTIPLICACION", 1045, 260, 28, BLACK);
                    const int click_nivel3_x_inicial = 1335;
                    const int click_nivel3_x_final = 1847;
                    const int click_nivel3_y_inicial = 200;
                    const int click_nivel3_y_final = 512;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 mousePosition = GetMousePosition();
                        if (mousePosition.x >= click_nivel3_x_inicial && mousePosition.x <= click_nivel3_x_final &&
                            mousePosition.y >= click_nivel3_y_inicial && mousePosition.y <= click_nivel3_y_final)
                        {
                            escenaActual = NIVEL3;
                        }
                    }
                }
                else
                {
                    DrawRectangle(1035, 150, 256, 256, BLUE);
                    DrawText("MULTIPLICACION", 1045, 260, 28, BLACK);
                    DrawTexture(candados_de_niveles, 1035, 150, BLACK);
                }
                if (currentLevel >= 3)
                {
                    DrawRectangle(1435, 150, 256, 256, GREEN);
                    DrawText("DIVISION", 1495, 260, 30, BLACK);
                    const int click_nivel4_x_inicial = 1935;
                    const int click_nivel4_x_final = 2447;
                    const int click_nivel4_y_inicial = 200;
                    const int click_nivel4_y_final = 512;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 mousePosition = GetMousePosition();
                        if (mousePosition.x >= click_nivel4_x_inicial && mousePosition.x <= click_nivel4_x_final &&
                            mousePosition.y >= click_nivel4_y_inicial && mousePosition.y <= click_nivel4_y_final)
                        {
                            escenaActual = NIVEL4;
                        }
                    }
                }
                else
                {
                    DrawRectangle(1435, 150, 256, 256, GREEN);
                    DrawText("DIVISION", 1495, 260, 30, BLACK);
                    DrawTexture(candados_de_niveles, 1435, 150, BLACK);
                }
                if (currentLevel >= 4)
                {
                    DrawRectangle(235, 600, 256, 256, PURPLE);
                    DrawText("FRACCIONES", 260, 715, 30, BLACK);

                    const int click_nivel5_x_inicial = 135;
                    const int click_nivel5_x_final = 647;
                    const int click_nivel5_y_inicial = 800;
                    const int click_nivel5_y_final = 1312;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 mousePosition = GetMousePosition();
                        if (mousePosition.x >= click_nivel5_x_inicial && mousePosition.x <= click_nivel5_x_final &&
                            mousePosition.y >= click_nivel5_y_inicial && mousePosition.y <= click_nivel5_y_final)
                        {
                            escenaActual = NIVEL5;
                        }
                    }
                }
                else
                {
                    DrawRectangle(235, 600, 256, 256, PURPLE);
                    DrawText("FRACCIONES", 260, 715, 30, BLACK);
                    DrawTexture(candados_de_niveles, 235, 600, BLACK);
                }
                DrawRectangle(635, 600, 256, 256, GRAY);
                DrawText("Proximamente!", 645, 715, 35, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_sonido_x_inicial && mousePosition.x <= click_sonido_x_final &&
                        mousePosition.y >= click_sonido_y_inicial && mousePosition.y <= click_sonido_y_final)
                    {
                        pause = !pause; // Cambia el estado de pausa al contrario de su estado actual

                        if (pause) // Si el estado es pausa (true)
                        {
                            PauseMusicStream(music); // Pausa la música

                            sonido = LoadTexture("resources/sonido_mute.png"); // Cambia el sonido a una versión silenciada
                        }
                        else // Si el estado es no pausa (false)
                        {
                            ResumeMusicStream(music);                     // Reanuda la música
                            sonido = LoadTexture("resources/sonido.png"); // Cambia el sonido a su versión normal
                        }
                    }
                }
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                finalizar_juego();
                EndDrawing();
            }
        }
        break;
        case SALIR:
        {
            int marginX = 3; // Margen horizontal
            int marginY = 3; // Margen vertical

            while (escenaActual == SALIR)
            {
                UpdateMusicStream(music);
                DrawTexture(sonido, 1770, 10, WHITE);
                if (IsKeyPressed(KEY_F11))
                { // Cambia a pantalla completa al presionar F11
                    ToggleFullscreen();
                }
                ClearBackground(BLACK);

                // const int click_CARGAR_PROGRESO_x_inicial = (ancho_pantalla / 2) - 460;
                // const int click_CARGAR_PROGRESO_x_final = (ancho_pantalla / 2) + 485;
                // const int click_CARGAR_PROGRESO_y_inicial = (alto_pantalla / 2) + 295;
                // const int click_CARGAR_PROGRESO_y_final = (alto_pantalla / 2) +405;
                DrawRectangle((ancho_pantalla / 2) - 515, (alto_pantalla / 2) - 205, 1010, 360, WHITE);
                DrawRectangle((ancho_pantalla / 2) - 510, (alto_pantalla / 2) - 200, 1000, 350, BLACK);
                DrawRectangle((ancho_pantalla / 2) - 498, (alto_pantalla / 2) - 150, 975, 120, WHITE);
                DrawText("Seguro que quiere salir del juego?", ((ancho_pantalla / 2) - 490) + marginX, ((alto_pantalla / 2) - 120) + marginY, 55, GRAY);
                DrawText("Seguro que quiere salir del juego?", (ancho_pantalla / 2) - 490, (alto_pantalla / 2) - 120, 55, BLACK);
                DrawRectangle((ancho_pantalla / 2) - 365, (alto_pantalla / 2) + 5, 200, 90, WHITE);
                DrawText("Si", ((ancho_pantalla / 2) - 290) + marginX, ((alto_pantalla / 2) + 25) + marginY, 55, GRAY);
                DrawText("Si", (ancho_pantalla / 2) - 290, (alto_pantalla / 2) + 25, 55, BLACK);
                DrawRectangle((ancho_pantalla / 2) + 125, (alto_pantalla / 2) + 5, 200, 90, WHITE);
                DrawText("NO", ((ancho_pantalla / 2)) + marginX + 190, ((alto_pantalla / 2) + 25) + marginY, 55, GRAY);
                DrawText("NO", (ancho_pantalla / 2) + 190, (alto_pantalla / 2) + 25, 55, BLACK);

                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_sonido_x_inicial && mousePosition.x <= click_sonido_x_final &&
                        mousePosition.y >= click_sonido_y_inicial && mousePosition.y <= click_sonido_y_final)
                    {
                        pause = !pause; // Cambia el estado de pausa al contrario de su estado actual

                        if (pause) // Si el estado es pausa (true)
                        {
                            PauseMusicStream(music); // Pausa la música

                            sonido = LoadTexture("resources/sonido_mute.png"); // Cambia el sonido a una versión silenciada
                        }
                        else // Si el estado es no pausa (false)
                        {
                            ResumeMusicStream(music);                     // Reanuda la música
                            sonido = LoadTexture("resources/sonido.png"); // Cambia el sonido a su versión normal
                        }
                    }
                }
                finalizar_juego();
                EndDrawing();
            }
        }
        break;
        case NIVEL1:
        {
            ClearBackground(BLUE);
            DrawRectangle(580, 280, 1600, 250, RED);
            DrawText("sumas", 1350, 420, 55, BLACK);

            finalizar_juego();
            currentLevel = 1;
            if (IsKeyPressed(KEY_J))
            {
                escenaActual = NIVELES;
            }
            EndDrawing();
        }
        break;
        case NIVEL2:
        {
            ClearBackground(BLUE);
            DrawRectangle(580, 280, 1600, 250, RED);
            DrawText("restas", 1350, 420, 55, BLACK);

            finalizar_juego();
            currentLevel = 2;
            if (IsKeyPressed(KEY_J))
            {
                escenaActual = NIVELES;
            }
            EndDrawing();
        }
        break;
        case NIVEL3:
        {
            ClearBackground(BLUE);
            DrawRectangle(580, 280, 1600, 250, RED);
            DrawText("MULTIPLICACION", 1350, 420, 55, BLACK);
            finalizar_juego();
            currentLevel = 3;
            if (IsKeyPressed(KEY_J))
            {
                escenaActual = NIVELES;
            }
            EndDrawing();
        }
        break;
        case NIVEL4:
        {
            ClearBackground(BLUE);
            DrawRectangle(580, 280, 1600, 250, RED);
            DrawText("DIVISION", 1350, 420, 55, BLACK);

            finalizar_juego();
            currentLevel = 4;
            if (IsKeyPressed(KEY_J))
            {
                escenaActual = NIVELES;
            }
            EndDrawing();
        }
        break;
        case NIVEL5:
        {
            ClearBackground(BLUE);
            DrawRectangle(580, 280, 1600, 250, RED);
            DrawText("fracciones", 1350, 420, 55, BLACK);

            finalizar_juego();
            currentLevel = 5;
            SaveProgress(currentLevel, currentScore);
            if (IsKeyPressed(KEY_J))
            {
                escenaActual = NIVELES;
            }
            EndDrawing();
        }
        break;
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();

            if (mousePosition.x >= click_sonido_x_inicial && mousePosition.x <= click_sonido_x_final &&
                mousePosition.y >= click_sonido_y_inicial && mousePosition.y <= click_sonido_y_final)
            {
                pause = !pause; // Cambia el estado de pausa al contrario de su estado actual

                if (pause) // Si el estado es pausa (true)
                {
                    PauseMusicStream(music); // Pausa la música

                    sonido = LoadTexture("resources/sonido_mute.png"); // Cambia el sonido a una versión silenciada
                }
                else // Si el estado es no pausa (false)
                {
                    ResumeMusicStream(music);                     // Reanuda la música
                    sonido = LoadTexture("resources/sonido.png"); // Cambia el sonido a su versión normal
                }
            }
        }
    }
    EndDrawing();

    UnloadTexture(sonido);
    StopMusicStream(music);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
