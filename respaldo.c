#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAX_SYMBOLS 100

int nivel_del_usuario = 0;
int contador_1 = 0;
int contador_2 = 0;
int contador_3 = 0;
int contador_4 = 0;
int contador_5 = 0;
const int ancho_pantalla = 1920;
const int alto_pantalla = 1080;
// click para mutear y desmutear
const int click_sonido_x_inicial = 1770;
const int click_sonido_x_final = 2060;
const int click_sonido_y_inicial = 10;
const int click_sonido_y_final = 140;
Texture2D sonido;
bool pause;
Music music;
Music respuesta_correcta;
Music respuesta_incorecta;

typedef enum
{
    MENU,
    INICIO,
    CARGAR_PROGRESO,
    NIVELES,
    SALIR,
    NIVEL1,
    ejercicio2_nivel1,
    ejercicio3_nivel1,
    ejercicio4_nivel1,
    ejercicio5_nivel1,
    NIVEL2,
    ejercicio2_nivel2,
    ejercicio3_nivel2,
    ejercicio4_nivel2,
    ejercicio5_nivel2,
    NIVEL3,
    ejercicio2_nivel3,
    ejercicio3_nivel3,
    ejercicio4_nivel3,
    ejercicio5_nivel3,
    NIVEL4,
    ejercicio2_nivel4,
    ejercicio3_nivel4,
    ejercicio4_nivel4,
    ejercicio5_nivel4

} Escena;

typedef struct
{
    Vector2 position;
    char symbol;
    Color color;
    float speed;
} Symbol;
void Mostrarguardado();
void MostrarAutoguardado();
void musica_mutear_desmutear();
void sonido_de_respuesta_correcta();
void sonido_de_respuesta_incorecta();

void guardarprogreso(int nivel_del_usuario, int nivel1, int nivel2, int nivel3, int nivel4, int nivel5)
{
    FILE *file = fopen("progreso.txt", "w"); // Abre el archivo para escritura

    if (file != NULL)
    {
        fprintf(file, "%d %d %d %d %d %d", nivel_del_usuario, nivel1, nivel2, nivel3, nivel4, nivel5); // Escribe los datos en el archivo
        fclose(file);                                                                                  // Cierra el archivo
    }
}
void cargarprogresi(int *nivel_del_usuario, int *nivel1, int *nivel2, int *nivel3, int *nivel4, int *nivel5)
{
    FILE *file = fopen("progreso.txt", "r"); // Abre el archivo para lectura

    if (file != NULL)
    {
        fscanf(file, "%d %d %d %d %d %d", nivel_del_usuario, nivel1, nivel2, nivel3, nivel4, nivel5); // Lee los datos del archivo
        fclose(file);                                                                                 // Cierra el archivo
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
    // borrar esto
    cargarprogresi(&nivel_del_usuario, &contador_1, &contador_2, &contador_3, &contador_4, &contador_5);

    InitWindow(ancho_pantalla, alto_pantalla, "FractionQuest");
    InitAudioDevice();
    SetTargetFPS(30);

    Escena escenaActual = MENU;
    Escena escenaAnterior = MENU;
    sonido = LoadTexture("resources/sonido.png");
    Texture2D candados_de_niveles = LoadTexture("resources/candado.png");
    music = LoadMusicStream("resources/Nintendo 3DS Music - Mii Maker.mp3");
    respuesta_correcta = LoadMusicStream("resources/BIEN_MAL/respuesta_correcta.mp3");
    respuesta_incorecta = LoadMusicStream("resources/BIEN_MAL/respuesta_incorecta.mp3");
    //  MENU SALIDA NIVELES
    Texture2D Fondo_de_salida = LoadTexture("resources/fondodesalida.png");
    Texture2D Fondo_de_cargando = LoadTexture("resources/CARGANDO_INICIO_DE_JUEGO.png");
    Texture2D Fondo_de_cargando_progreso = LoadTexture("resources/CARGANDO_PROGRESO.png");
    Texture2D Fondo_de_niveles = LoadTexture("resources/niveles.png");
    Texture2D Fondo_de_finaldeljuego = LoadTexture("resources/final_del_juego.png");

    Texture2D Respuestas_Vacias1 = LoadTexture("resources/BIEN_MAL/vacio.png");
    Texture2D Respuestas_Vacias2 = LoadTexture("resources/BIEN_MAL/vacio.png");
    Texture2D Respuestas_Vacias3 = LoadTexture("resources/BIEN_MAL/vacio.png");
    Texture2D Respuestas_Vacias4 = LoadTexture("resources/BIEN_MAL/vacio.png");
    Texture2D Respuestas_Vacias5 = LoadTexture("resources/BIEN_MAL/vacio.png");
    Texture2D Respuesta_Correcta = LoadTexture("resources/BIEN_MAL/respuesta_buena.png");
    Texture2D Respuesta_Incorrecta = LoadTexture("resources/BIEN_MAL/respuesta_mala.png");

    // nivel 1
    Texture2D Fondo_1_1 = LoadTexture("resources/nivel1/nivel1_1.png");
    Texture2D Fondo_1_2 = LoadTexture("resources/nivel1/nivel1_2.png");
    Texture2D Fondo_1_3 = LoadTexture("resources/nivel1/nivel1_3.png");
    Texture2D Fondo_1_4 = LoadTexture("resources/nivel1/nivel1_4.png");
    Texture2D Fondo_1_5 = LoadTexture("resources/nivel1/nivel1_5.png");
    Texture2D Fondo_de_perdiste_1 = LoadTexture("resources/nivel1/Fondo_de_perdiste.png");
    Texture2D Fondo_de_ganaste_1 = LoadTexture("resources/nivel1/Fondo_de_ganaste.png");
    // nivel 2
    Texture2D Fondo_2_1 = LoadTexture("resources/nivel2/nivel2_1.png");
    Texture2D Fondo_2_2 = LoadTexture("resources/nivel2/nivel2_2.png");
    Texture2D Fondo_2_3 = LoadTexture("resources/nivel2/nivel2_3.png");
    Texture2D Fondo_2_4 = LoadTexture("resources/nivel2/nivel2_4.png");
    Texture2D Fondo_2_5 = LoadTexture("resources/nivel2/nivel2_5.png");
    Texture2D Fondo_de_perdiste_2 = LoadTexture("resources/nivel2/Fondo_de_perdiste_2.png");
    Texture2D Fondo_de_ganaste_2 = LoadTexture("resources/nivel2/Fondo_de_ganaste_2.png");
    // nivel 3
    Texture2D Fondo_3_1 = LoadTexture("resources/nivel3/nivel3_1.png");
    Texture2D Fondo_3_2 = LoadTexture("resources/nivel3/nivel3_2.png");
    Texture2D Fondo_3_3 = LoadTexture("resources/nivel3/nivel3_3.png");
    Texture2D Fondo_3_4 = LoadTexture("resources/nivel3/nivel3_4.png");
    Texture2D Fondo_3_5 = LoadTexture("resources/nivel3/nivel3_5.png");
    Texture2D Fondo_de_perdiste_3 = LoadTexture("resources/nivel3/Fondo_de_perdiste_3.png");
    Texture2D Fondo_de_ganaste_3 = LoadTexture("resources/nivel3/Fondo_de_ganaste_3.png");
    // nivel 4 modificar
    Texture2D Fondo_4_1 = LoadTexture("resources/nivel4/nivel4_1.png");
    Texture2D Fondo_4_2 = LoadTexture("resources/nivel4/nivel4_2.png");
    Texture2D Fondo_4_3 = LoadTexture("resources/nivel4/nivel4_3.png");
    Texture2D Fondo_4_4 = LoadTexture("resources/nivel4/nivel4_4.png");
    Texture2D Fondo_4_5 = LoadTexture("resources/nivel4/nivel4_5.png");
    Texture2D Fondo_de_perdiste_4 = LoadTexture("resources/nivel4/Fondo_de_perdiste_4.png");
    Texture2D Fondo_de_ganaste_4 = LoadTexture("resources/nivel4/Fondo_de_ganaste_4.png");
    /////////////////////////////////////////////////////////////////////////////////////////////
    music.looping = true;
    respuesta_correcta.looping = true;
    respuesta_incorecta.looping = true;
    pause = false;

    PlayMusicStream(music);
    SetMusicVolume(music, 0.5); // Establecer el volumen al 50%
    /* ==========      PANTALLA DE CARGA      ===============
    float contador_segundos = 0.0f;
    while (contador_segundos < 4.0f && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(Fondo_de_cargando, 0, 0, WHITE);
        EndDrawing();
        contador_segundos += GetFrameTime();
    }
    */
    Symbol symbols[MAX_SYMBOLS];
    while (!WindowShouldClose())
    {
        BeginDrawing();
        Mostrarguardado();
        UpdateMusicStream(music);
        Mostrarguardado(); // Actualiza la música si es necesario
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
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, WHITE);
                Mostrarguardado();

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
                const int click_niveles_x_inicial = (ancho_pantalla / 2) - 448;
                const int click_niveles_x_final = (ancho_pantalla / 2) + 327;
                const int click_niveles_y_inicial = (alto_pantalla / 2) + 96;
                const int click_niveles_y_final = (alto_pantalla / 2) + 196;

                DrawRectangle((ancho_pantalla / 2) - 448, (alto_pantalla / 2) + 207, 775, 100, WHITE);
                DrawText("CARGAR PROGRESO", (ancho_pantalla / 2) - 280, (alto_pantalla / 2) + 240, 50, DARKGRAY);
                const int click_CARGAR_PROGRESO_x_inicial = (ancho_pantalla / 2) - 448;
                const int click_CARGAR_PROGRESO_x_final = (ancho_pantalla / 2) + 327;
                const int click_CARGAR_PROGRESO_y_inicial = (alto_pantalla / 2) + 207;
                const int click_CARGAR_PROGRESO_y_final = (alto_pantalla / 2) + 307;

                DrawRectangle((ancho_pantalla / 2) - 448, (alto_pantalla / 2) + 317, 775, 100, WHITE);
                DrawText("SALIR", (ancho_pantalla / 2) - 120, (alto_pantalla / 2) + 350, 50, DARKGRAY);
                const int click_salir_x_inicial = (ancho_pantalla / 2) - 448;
                const int click_salir_x_final = (ancho_pantalla / 2) + 327;
                const int click_salir_y_inicial = (alto_pantalla / 2) + 317;
                const int click_salir_y_final = (alto_pantalla / 2) + 417;
                musica_mutear_desmutear();
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

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
                        escenaAnterior = escenaActual;
                        escenaActual = SALIR;
                    }
                    if (mousePosition.x >= click_CARGAR_PROGRESO_x_inicial && mousePosition.x <= click_CARGAR_PROGRESO_x_final &&
                        mousePosition.y >= click_CARGAR_PROGRESO_y_inicial && mousePosition.y <= click_CARGAR_PROGRESO_y_final)
                    {
                        escenaActual = CARGAR_PROGRESO;
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
        case CARGAR_PROGRESO:
        {
            float contador_segundos = 0.0f;

            while (contador_segundos < 3.0f && !WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(BLACK);

                // Dibuja el texto de "Cargando..."
                DrawTexture(Fondo_de_cargando_progreso, 0, 0, WHITE);

                EndDrawing();

                // Incrementa el contador con el tiempo transcurrido en cada fotograma
                contador_segundos += GetFrameTime();
            }
            cargarprogresi(&nivel_del_usuario, &contador_1, &contador_2, &contador_3, &contador_4, &contador_5);
            escenaActual = MENU;
        }
        break;
        case NIVELES:
        {

            while (escenaActual == NIVELES)
            {
                ClearBackground(BLACK);
                DrawTexture(Fondo_de_niveles, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, WHITE);
                Mostrarguardado();
                DrawText(TextFormat("%d/5", contador_1), (ancho_pantalla / 2) - 738, (alto_pantalla / 2) - 212, 50, WHITE);
                const int click_nivel1_x_inicial = 139.5;
                const int click_nivel1_x_final = 395.5;
                const int click_nivel1_y_inicial = 378;
                const int click_nivel1_y_final = 634;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel1_x_inicial && mousePosition.x <= click_nivel1_x_final &&
                        mousePosition.y >= click_nivel1_y_inicial && mousePosition.y <= click_nivel1_y_final)
                    {
                        escenaActual = NIVEL1;
                    }
                }
                if (nivel_del_usuario >= 1)
                {
                    DrawText(TextFormat("%d/5", contador_2), (ancho_pantalla / 2) - 300, (alto_pantalla / 2) - 212, 50, WHITE);
                    const int click_nivel2_x_inicial = 578.5;
                    const int click_nivel2_x_final = 834.5;
                    const int click_nivel2_y_inicial = 378;
                    const int click_nivel2_y_final = 634;
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
                    if (nivel_del_usuario == 0)
                    {
                        DrawText("Se desbloquea completando\n\n      el %80 del nivel 1", 530, 289.4, 30, WHITE);
                    }
                    DrawTexture(candados_de_niveles, 626, 397.6, BLACK);
                }
                if (nivel_del_usuario >= 2)
                {
                    DrawText(TextFormat("%d/5", contador_3), (ancho_pantalla / 2) + 140, (alto_pantalla / 2) - 212, 50, WHITE);
                    const int click_nivel3_x_inicial = 1017.5;
                    const int click_nivel3_x_final = 1273.5;
                    const int click_nivel3_y_inicial = 378;
                    const int click_nivel3_y_final = 634;
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
                    if (nivel_del_usuario == 1)
                    {
                        DrawText("Se desbloquea completando\n\n       el %80 del nivel 2", 930, 289.4, 30, WHITE);
                    }
                    DrawTexture(candados_de_niveles, 1065.5, 397.6, BLACK);
                }
                if (nivel_del_usuario >= 3)
                {
                    DrawText(TextFormat("%d/5", contador_4), (ancho_pantalla / 2) + 582, (alto_pantalla / 2) - 212, 50, WHITE);
                    const int click_nivel4_x_inicial = 1456.5;
                    const int click_nivel4_x_final = 1712.5;
                    const int click_nivel4_y_inicial = 378;
                    const int click_nivel4_y_final = 634;
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
                    if (nivel_del_usuario == 2)
                    {
                        DrawText("Se desbloquea completando\n\n       el %80 del nivel 3", 1370, 289.4, 30, WHITE);
                    }
                    DrawTexture(candados_de_niveles, 1507.8, 397.6, BLACK);
                }

                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                musica_mutear_desmutear();
                finalizar_juego();
                EndDrawing();
            }
        }
        break;
        case SALIR:
        {

            while (escenaActual == SALIR)
            {
                UpdateMusicStream(music);
                Mostrarguardado();
                ClearBackground(BLUE);
                DrawTexture(Fondo_de_salida, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);

                const int click_menudesalida_si_x_inicial = 680.9;
                const int click_menudesalida_si_x_final = 875.9;
                const int click_menudesalida_si_y_inicial = 591.7;
                const int click_menudesalida_si_y_final = 792.1;

                const int click_menudesalida_no_x_inicial = 1037;
                const int click_menudesalida_no_x_final = 1232;
                const int click_menudesalida_no_y_inicial = 591.7;
                const int click_menudesalida_no_y_final = 787.7;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_menudesalida_si_x_inicial && mousePosition.x <= click_menudesalida_si_x_final &&
                        mousePosition.y >= click_menudesalida_si_y_inicial && mousePosition.y <= click_menudesalida_si_y_final)
                    {
                        CloseWindow(); // Cierra la ventana y finaliza el juego
                    }
                    if (mousePosition.x >= click_menudesalida_no_x_inicial && mousePosition.x <= click_menudesalida_no_x_final &&
                        mousePosition.y >= click_menudesalida_no_y_inicial && mousePosition.y <= click_menudesalida_no_y_final)
                    {
                        escenaActual = escenaAnterior;
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                EndDrawing();
            }
        }
        break;
        case NIVEL1:
        {

            contador_1 = 0;
            Respuestas_Vacias1 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias2 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias3 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias4 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias5 = LoadTexture("resources/BIEN_MAL/vacio.png");

            while (escenaActual == NIVEL1)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_1_1, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Correcta;
                        contador_1++;
                        escenaActual = ejercicio2_nivel1;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Incorrecta;
                        escenaActual = ejercicio2_nivel1;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Incorrecta;
                        escenaActual = ejercicio2_nivel1;
                        sonido_de_respuesta_incorecta();
                    }
                }
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_1), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                finalizar_juego();
                musica_mutear_desmutear();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio2_nivel1:
        {

            while (escenaActual == ejercicio2_nivel1)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_1_2, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_1), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias2 = Respuesta_Incorrecta;
                        escenaActual = ejercicio3_nivel1;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {

                        Respuestas_Vacias2 = Respuesta_Correcta;
                        contador_1++;
                        escenaActual = ejercicio3_nivel1;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias2 = Respuesta_Incorrecta;
                        escenaActual = ejercicio3_nivel1;
                        sonido_de_respuesta_incorecta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio3_nivel1:
        {
            while (escenaActual == ejercicio3_nivel1)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_1_3, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_1), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_2_1_x_inicial = 1266.3;
                const int click_nivel1_2_1_x_final = 1417.4;
                const int click_nivel1_2_1_y_inicial = 186.2;
                const int click_nivel1_2_1_y_final = 401.8;
                //=========
                const int click_nivel1_2_2_x_inicial = 1266.3;
                const int click_nivel1_2_2_x_final = 1417.4;
                const int click_nivel1_2_2_y_inicial = 433.6;
                const int click_nivel1_2_2_y_final = 649.2;
                //=========
                const int click_nivel1_2_3_x_inicial = 1266.3;
                const int click_nivel1_2_3_x_final = 1417.4;
                const int click_nivel1_2_3_y_inicial = 681;
                const int click_nivel1_2_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_2_1_x_inicial && mousePosition.x <= click_nivel1_2_1_x_final &&
                        mousePosition.y >= click_nivel1_2_1_y_inicial && mousePosition.y <= click_nivel1_2_1_y_final)
                    {
                        Respuestas_Vacias3 = Respuesta_Correcta;
                        contador_1++;
                        escenaActual = ejercicio4_nivel1;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_2_2_x_inicial && mousePosition.x <= click_nivel1_2_2_x_final &&
                        mousePosition.y >= click_nivel1_2_2_y_inicial && mousePosition.y <= click_nivel1_2_2_y_final)
                    {
                        Respuestas_Vacias3 = Respuesta_Incorrecta;
                        escenaActual = ejercicio4_nivel1;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_2_3_x_inicial && mousePosition.x <= click_nivel1_2_3_x_final &&
                        mousePosition.y >= click_nivel1_2_3_y_inicial && mousePosition.y <= click_nivel1_2_3_y_final)
                    {
                        Respuestas_Vacias3 = Respuesta_Incorrecta;
                        escenaActual = ejercicio4_nivel1;
                        sonido_de_respuesta_incorecta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio4_nivel1:
        {
            while (escenaActual == ejercicio4_nivel1)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_1_4, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_1), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_2_1_x_inicial = 1266.3;
                const int click_nivel1_2_1_x_final = 1417.4;
                const int click_nivel1_2_1_y_inicial = 186.2;
                const int click_nivel1_2_1_y_final = 401.8;
                //=========
                const int click_nivel1_2_2_x_inicial = 1266.3;
                const int click_nivel1_2_2_x_final = 1417.4;
                const int click_nivel1_2_2_y_inicial = 433.6;
                const int click_nivel1_2_2_y_final = 649.2;
                //=========
                const int click_nivel1_2_3_x_inicial = 1266.3;
                const int click_nivel1_2_3_x_final = 1417.4;
                const int click_nivel1_2_3_y_inicial = 681;
                const int click_nivel1_2_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel1_2_1_x_inicial && mousePosition.x <= click_nivel1_2_1_x_final &&
                        mousePosition.y >= click_nivel1_2_1_y_inicial && mousePosition.y <= click_nivel1_2_1_y_final)
                    {
                        Respuestas_Vacias4 = Respuesta_Incorrecta;
                        escenaActual = ejercicio5_nivel1;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_2_2_x_inicial && mousePosition.x <= click_nivel1_2_2_x_final &&
                        mousePosition.y >= click_nivel1_2_2_y_inicial && mousePosition.y <= click_nivel1_2_2_y_final)
                    {
                        Respuestas_Vacias4 = Respuesta_Incorrecta;
                        escenaActual = ejercicio5_nivel1;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_2_3_x_inicial && mousePosition.x <= click_nivel1_2_3_x_final &&
                        mousePosition.y >= click_nivel1_2_3_y_inicial && mousePosition.y <= click_nivel1_2_3_y_final)
                    {
                        Respuestas_Vacias4 = Respuesta_Correcta;
                        contador_1++;
                        escenaActual = ejercicio5_nivel1;
                        sonido_de_respuesta_correcta();
                    }
                }
                finalizar_juego();
                musica_mutear_desmutear();

                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio5_nivel1:
        {
            while (escenaActual == ejercicio5_nivel1)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_1_5, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);

                const int click_nivel1_2_1_x_inicial = 1266.3;
                const int click_nivel1_2_1_x_final = 1417.4;
                const int click_nivel1_2_1_y_inicial = 186.2;
                const int click_nivel1_2_1_y_final = 401.8;
                //=========
                const int click_nivel1_2_2_x_inicial = 1266.3;
                const int click_nivel1_2_2_x_final = 1417.4;
                const int click_nivel1_2_2_y_inicial = 433.6;
                const int click_nivel1_2_2_y_final = 649.2;
                //=========
                const int click_nivel1_2_3_x_inicial = 1266.3;
                const int click_nivel1_2_3_x_final = 1417.4;
                const int click_nivel1_2_3_y_inicial = 681;
                const int click_nivel1_2_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel1_2_1_x_inicial && mousePosition.x <= click_nivel1_2_1_x_final &&
                        mousePosition.y >= click_nivel1_2_1_y_inicial && mousePosition.y <= click_nivel1_2_1_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Correcta;
                        contador_1++;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_2_2_x_inicial && mousePosition.x <= click_nivel1_2_2_x_final &&
                        mousePosition.y >= click_nivel1_2_2_y_inicial && mousePosition.y <= click_nivel1_2_2_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Incorrecta;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_2_3_x_inicial && mousePosition.x <= click_nivel1_2_3_x_final &&
                        mousePosition.y >= click_nivel1_2_3_y_inicial && mousePosition.y <= click_nivel1_2_3_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Incorrecta;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_incorecta();
                    }
                }
                if (contador_1 > 3)
                {
                    nivel_del_usuario = 1;
                }

                musica_mutear_desmutear();
                finalizar_juego();
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_1), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                EndDrawing();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
            }

            sleep(1);
            if (contador_1 < 4)
            {
                double tiempoInicial = GetTime();
                while (!WindowShouldClose())
                {
                    double tiempoActual = GetTime();

                    BeginDrawing();
                    ClearBackground(BLACK);

                    if (tiempoActual - tiempoInicial <= 5.0)
                    {

                        ClearBackground(BLUE);
                        DrawTexture(Fondo_de_perdiste_1, 0, 0, WHITE);
                        DrawTexture(Respuestas_Vacias1, 932.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias2, 1010, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias3, 1087.8, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias4, 1164.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias5, 1241.4, 322.1, WHITE);
                        DrawText(TextFormat("%d/5", contador_1), 1342, 330, 50, BLACK);
                    }
                    else
                    {
                        break;
                    }

                    EndDrawing();
                }
            }
            else
            {
                double tiempoInicial = GetTime();
                while (!WindowShouldClose())
                {
                    double tiempoActual = GetTime();

                    BeginDrawing();
                    ClearBackground(BLACK);

                    if (tiempoActual - tiempoInicial <= 5.0)
                    {

                        ClearBackground(BLUE);
                        DrawTexture(Fondo_de_ganaste_1, 0, 0, WHITE);
                        DrawTexture(Respuestas_Vacias1, 932.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias2, 1010, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias3, 1087.8, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias4, 1164.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias5, 1241.4, 322.1, WHITE);
                        DrawText(TextFormat("%d/5", contador_1), 1342, 330, 50, BLACK);
                    }
                    else
                    {
                        break;
                    }

                    EndDrawing();
                }
            }
            MostrarAutoguardado();
            guardarprogreso(nivel_del_usuario, contador_1, contador_2, contador_3, contador_4, contador_5); // Guardar el progreso actualizado
        }
        break;
        case NIVEL2:
        {

            contador_2 = 0;
            Respuestas_Vacias1 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias2 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias3 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias4 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias5 = LoadTexture("resources/BIEN_MAL/vacio.png");

            while (escenaActual == NIVEL2)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_2_1, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Correcta;
                        contador_2++;
                        escenaActual = ejercicio2_nivel2;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Incorrecta;
                        escenaActual = ejercicio2_nivel2;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Incorrecta;
                        escenaActual = ejercicio2_nivel2;
                        sonido_de_respuesta_incorecta();
                    }
                }
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_2), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                finalizar_juego();
                musica_mutear_desmutear();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio2_nivel2:
        {

            while (escenaActual == ejercicio2_nivel2)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_2_2, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_2), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias2 = Respuesta_Incorrecta;
                        escenaActual = ejercicio3_nivel2;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {

                        Respuestas_Vacias2 = Respuesta_Correcta;
                        contador_2++;
                        escenaActual = ejercicio3_nivel2;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias2 = Respuesta_Incorrecta;
                        escenaActual = ejercicio3_nivel2;
                        sonido_de_respuesta_incorecta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio3_nivel2:
        {

            while (escenaActual == ejercicio3_nivel2)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_2_3, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_2), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias3 = Respuesta_Incorrecta;
                        escenaActual = ejercicio4_nivel2;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {

                        Respuestas_Vacias3 = Respuesta_Correcta;
                        contador_2++;
                        escenaActual = ejercicio4_nivel2;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias3 = Respuesta_Incorrecta;
                        escenaActual = ejercicio4_nivel2;
                        sonido_de_respuesta_incorecta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio4_nivel2:
        {

            while (escenaActual == ejercicio4_nivel2)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_2_4, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_2), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias4 = Respuesta_Correcta;
                        contador_2++;
                        escenaActual = ejercicio5_nivel2;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {

                        Respuestas_Vacias4 = Respuesta_Incorrecta;
                        escenaActual = ejercicio5_nivel2;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias4 = Respuesta_Incorrecta;
                        escenaActual = ejercicio5_nivel2;
                        sonido_de_respuesta_incorecta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio5_nivel2:
        {
            while (escenaActual == ejercicio5_nivel2)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_2_5, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);

                const int click_nivel1_2_1_x_inicial = 1266.3;
                const int click_nivel1_2_1_x_final = 1417.4;
                const int click_nivel1_2_1_y_inicial = 186.2;
                const int click_nivel1_2_1_y_final = 401.8;
                //=========
                const int click_nivel1_2_2_x_inicial = 1266.3;
                const int click_nivel1_2_2_x_final = 1417.4;
                const int click_nivel1_2_2_y_inicial = 433.6;
                const int click_nivel1_2_2_y_final = 649.2;
                //=========
                const int click_nivel1_2_3_x_inicial = 1266.3;
                const int click_nivel1_2_3_x_final = 1417.4;
                const int click_nivel1_2_3_y_inicial = 681;
                const int click_nivel1_2_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel1_2_1_x_inicial && mousePosition.x <= click_nivel1_2_1_x_final &&
                        mousePosition.y >= click_nivel1_2_1_y_inicial && mousePosition.y <= click_nivel1_2_1_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Incorrecta;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_2_2_x_inicial && mousePosition.x <= click_nivel1_2_2_x_final &&
                        mousePosition.y >= click_nivel1_2_2_y_inicial && mousePosition.y <= click_nivel1_2_2_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Incorrecta;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_2_3_x_inicial && mousePosition.x <= click_nivel1_2_3_x_final &&
                        mousePosition.y >= click_nivel1_2_3_y_inicial && mousePosition.y <= click_nivel1_2_3_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Correcta;
                        contador_2++;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_correcta();
                    }
                }
                if (contador_2 > 3)
                {
                    nivel_del_usuario = 2;
                }

                musica_mutear_desmutear();
                finalizar_juego();
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_2), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                EndDrawing();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
            }

            sleep(1);
            if (contador_2 < 4)
            {
                double tiempoInicial = GetTime();
                while (!WindowShouldClose())
                {
                    double tiempoActual = GetTime();
                    BeginDrawing();
                    ClearBackground(BLACK);

                    if (tiempoActual - tiempoInicial <= 5.0)
                    {

                        ClearBackground(BLUE);
                        DrawTexture(Fondo_de_perdiste_2, 0, 0, WHITE);
                        DrawTexture(Respuestas_Vacias1, 932.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias2, 1010, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias3, 1087.8, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias4, 1164.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias5, 1241.4, 322.1, WHITE);
                        DrawText(TextFormat("%d/5", contador_2), 1342, 330, 50, BLACK);
                    }
                    else
                    {
                        break;
                    }

                    EndDrawing();
                }
            }
            else
            {
                double tiempoInicial = GetTime();
                while (!WindowShouldClose())
                {
                    double tiempoActual = GetTime();

                    BeginDrawing();
                    ClearBackground(BLACK);

                    if (tiempoActual - tiempoInicial <= 5.0)
                    {

                        ClearBackground(BLUE);
                        DrawTexture(Fondo_de_ganaste_2, 0, 0, WHITE);
                        DrawTexture(Respuestas_Vacias1, 932.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias2, 1010, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias3, 1087.8, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias4, 1164.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias5, 1241.4, 322.1, WHITE);
                        DrawText(TextFormat("%d/5", contador_2), 1342, 330, 50, BLACK);
                    }
                    else
                    {
                        break;
                    }

                    EndDrawing();
                }
            }
            MostrarAutoguardado();
            guardarprogreso(nivel_del_usuario, contador_1, contador_2, contador_3, contador_4, contador_5); // Guardar el progreso actualizado
        }
        break;
        case NIVEL3:
        {

            contador_3 = 0;
            Respuestas_Vacias1 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias2 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias3 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias4 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias5 = LoadTexture("resources/BIEN_MAL/vacio.png");

            while (escenaActual == NIVEL3)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_3_1, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Incorrecta;
                        escenaActual = ejercicio2_nivel3;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Incorrecta;
                        escenaActual = ejercicio2_nivel3;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Correcta;
                        contador_3++;
                        escenaActual = ejercicio2_nivel3;
                        sonido_de_respuesta_correcta();
                    }
                }
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_3), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                finalizar_juego();
                musica_mutear_desmutear();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio2_nivel3:
        {

            while (escenaActual == ejercicio2_nivel3)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_3_2, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_3), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias2 = Respuesta_Correcta;
                        contador_3++;
                        escenaActual = ejercicio3_nivel3;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {

                        Respuestas_Vacias2 = Respuesta_Incorrecta;
                        escenaActual = ejercicio3_nivel3;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias2 = Respuesta_Incorrecta;
                        escenaActual = ejercicio3_nivel3;
                        sonido_de_respuesta_incorecta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio3_nivel3:
        {

            while (escenaActual == ejercicio3_nivel3)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_3_3, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_3), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias3 = Respuesta_Correcta;
                        contador_3++;
                        escenaActual = ejercicio4_nivel3;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {
                        Respuestas_Vacias3 = Respuesta_Incorrecta;
                        escenaActual = ejercicio4_nivel3;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias3 = Respuesta_Incorrecta;
                        escenaActual = ejercicio4_nivel3;
                        sonido_de_respuesta_incorecta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio4_nivel3:
        {

            while (escenaActual == ejercicio4_nivel3)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_3_4, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_3), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias4 = Respuesta_Incorrecta;
                        escenaActual = ejercicio5_nivel3;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {

                        Respuestas_Vacias4 = Respuesta_Incorrecta;
                        escenaActual = ejercicio5_nivel3;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias4 = Respuesta_Correcta;
                        contador_3++;
                        escenaActual = ejercicio5_nivel3;
                        sonido_de_respuesta_correcta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio5_nivel3:
        {
            while (escenaActual == ejercicio5_nivel3)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_3_5, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);

                const int click_nivel1_2_1_x_inicial = 1266.3;
                const int click_nivel1_2_1_x_final = 1417.4;
                const int click_nivel1_2_1_y_inicial = 186.2;
                const int click_nivel1_2_1_y_final = 401.8;
                //=========
                const int click_nivel1_2_2_x_inicial = 1266.3;
                const int click_nivel1_2_2_x_final = 1417.4;
                const int click_nivel1_2_2_y_inicial = 433.6;
                const int click_nivel1_2_2_y_final = 649.2;
                //=========
                const int click_nivel1_2_3_x_inicial = 1266.3;
                const int click_nivel1_2_3_x_final = 1417.4;
                const int click_nivel1_2_3_y_inicial = 681;
                const int click_nivel1_2_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel1_2_1_x_inicial && mousePosition.x <= click_nivel1_2_1_x_final &&
                        mousePosition.y >= click_nivel1_2_1_y_inicial && mousePosition.y <= click_nivel1_2_1_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Incorrecta;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_2_2_x_inicial && mousePosition.x <= click_nivel1_2_2_x_final &&
                        mousePosition.y >= click_nivel1_2_2_y_inicial && mousePosition.y <= click_nivel1_2_2_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Correcta;
                        contador_3++;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_2_3_x_inicial && mousePosition.x <= click_nivel1_2_3_x_final &&
                        mousePosition.y >= click_nivel1_2_3_y_inicial && mousePosition.y <= click_nivel1_2_3_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Incorrecta;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_incorecta();
                    }
                }
                if (contador_3 > 3)
                {
                    nivel_del_usuario = 3;
                }

                musica_mutear_desmutear();
                finalizar_juego();
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_3), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                EndDrawing();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
            }

            sleep(1);
            if (contador_3 < 4)
            {
                double tiempoInicial = GetTime();
                while (!WindowShouldClose())
                {
                    double tiempoActual = GetTime();
                    BeginDrawing();
                    ClearBackground(BLACK);

                    if (tiempoActual - tiempoInicial <= 5.0)
                    {

                        ClearBackground(BLUE);
                        DrawTexture(Fondo_de_perdiste_3, 0, 0, WHITE);
                        DrawTexture(Respuestas_Vacias1, 932.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias2, 1010, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias3, 1087.8, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias4, 1164.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias5, 1241.4, 322.1, WHITE);
                        DrawText(TextFormat("%d/5", contador_3), 1342, 330, 50, BLACK);
                    }
                    else
                    {
                        break;
                    }

                    EndDrawing();
                }
            }
            else
            {
                double tiempoInicial = GetTime();
                while (!WindowShouldClose())
                {
                    double tiempoActual = GetTime();

                    BeginDrawing();
                    ClearBackground(BLACK);

                    if (tiempoActual - tiempoInicial <= 5.0)
                    {

                        ClearBackground(BLUE);
                        DrawTexture(Fondo_de_ganaste_3, 0, 0, WHITE);
                        DrawTexture(Respuestas_Vacias1, 932.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias2, 1010, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias3, 1087.8, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias4, 1164.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias5, 1241.4, 322.1, WHITE);
                        DrawText(TextFormat("%d/5", contador_3), 1342, 330, 50, BLACK);
                    }
                    else
                    {
                        break;
                    }

                    EndDrawing();
                }
            }
            MostrarAutoguardado();
            guardarprogreso(nivel_del_usuario, contador_1, contador_2, contador_3, contador_4, contador_5); // Guardar el progreso actualizado
        }
        break;
        case NIVEL4:
        {

            contador_4 = 0;
            Respuestas_Vacias1 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias2 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias3 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias4 = LoadTexture("resources/BIEN_MAL/vacio.png");
            Respuestas_Vacias5 = LoadTexture("resources/BIEN_MAL/vacio.png");

            while (escenaActual == NIVEL4)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_4_1, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Incorrecta;
                        escenaActual = ejercicio2_nivel4;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Correcta;
                        contador_4++;
                        escenaActual = ejercicio2_nivel4;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Incorrecta;
                        escenaActual = ejercicio2_nivel4;
                        sonido_de_respuesta_incorecta();
                    }
                }
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_4), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                finalizar_juego();
                musica_mutear_desmutear();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio2_nivel4:
        {

            while (escenaActual == ejercicio2_nivel4)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_4_2, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_4), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias2 = Respuesta_Incorrecta;
                        escenaActual = ejercicio3_nivel4;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {

                        Respuestas_Vacias2 = Respuesta_Incorrecta;
                        escenaActual = ejercicio3_nivel4;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias2 = Respuesta_Correcta;
                        contador_4++;
                        escenaActual = ejercicio3_nivel4;
                        sonido_de_respuesta_correcta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio3_nivel4:
        {

            while (escenaActual == ejercicio3_nivel4)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_4_3, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_4), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias3 = Respuesta_Incorrecta;
                        escenaActual = ejercicio4_nivel4;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {

                        Respuestas_Vacias3 = Respuesta_Correcta;
                        contador_4++;
                        escenaActual = ejercicio4_nivel4;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias3 = Respuesta_Incorrecta;
                        escenaActual = ejercicio4_nivel4;
                        sonido_de_respuesta_incorecta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio4_nivel4:
        {

            while (escenaActual == ejercicio4_nivel4)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_4_4, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_4), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                const int click_nivel1_1_1_x_inicial = 1266.3;
                const int click_nivel1_1_1_x_final = 1417.4;
                const int click_nivel1_1_1_y_inicial = 186.2;
                const int click_nivel1_1_1_y_final = 401.8;
                //=========
                const int click_nivel1_1_2_x_inicial = 1266.3;
                const int click_nivel1_1_2_x_final = 1417.4;
                const int click_nivel1_1_2_y_inicial = 433.6;
                const int click_nivel1_1_2_y_final = 649.2;
                //=========
                const int click_nivel1_1_3_x_inicial = 1266.3;
                const int click_nivel1_1_3_x_final = 1417.4;
                const int click_nivel1_1_3_y_inicial = 681;
                const int click_nivel1_1_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_nivel1_1_1_x_inicial && mousePosition.x <= click_nivel1_1_1_x_final &&
                        mousePosition.y >= click_nivel1_1_1_y_inicial && mousePosition.y <= click_nivel1_1_1_y_final)
                    {
                        Respuestas_Vacias4 = Respuesta_Correcta;
                        contador_4++;
                        escenaActual = ejercicio5_nivel4;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_2_x_inicial && mousePosition.x <= click_nivel1_1_2_x_final &&
                        mousePosition.y >= click_nivel1_1_2_y_inicial && mousePosition.y <= click_nivel1_1_2_y_final)
                    {

                        Respuestas_Vacias4 = Respuesta_Incorrecta;
                        escenaActual = ejercicio5_nivel4;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias4 = Respuesta_Incorrecta;
                        escenaActual = ejercicio5_nivel4;
                        sonido_de_respuesta_incorecta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
                EndDrawing();
            }
        }
        break;
        case ejercicio5_nivel4:
        {
            while (escenaActual == ejercicio5_nivel4)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_4_5, 0, 0, WHITE);
                UpdateMusicStream(music);
                Mostrarguardado();
                DrawTexture(sonido, 1770, 10, BLACK);
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);

                const int click_nivel1_2_1_x_inicial = 1266.3;
                const int click_nivel1_2_1_x_final = 1417.4;
                const int click_nivel1_2_1_y_inicial = 186.2;
                const int click_nivel1_2_1_y_final = 401.8;
                //=========
                const int click_nivel1_2_2_x_inicial = 1266.3;
                const int click_nivel1_2_2_x_final = 1417.4;
                const int click_nivel1_2_2_y_inicial = 433.6;
                const int click_nivel1_2_2_y_final = 649.2;
                //=========
                const int click_nivel1_2_3_x_inicial = 1266.3;
                const int click_nivel1_2_3_x_final = 1417.4;
                const int click_nivel1_2_3_y_inicial = 681;
                const int click_nivel1_2_3_y_final = 896.6;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel1_2_1_x_inicial && mousePosition.x <= click_nivel1_2_1_x_final &&
                        mousePosition.y >= click_nivel1_2_1_y_inicial && mousePosition.y <= click_nivel1_2_1_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Incorrecta;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_2_2_x_inicial && mousePosition.x <= click_nivel1_2_2_x_final &&
                        mousePosition.y >= click_nivel1_2_2_y_inicial && mousePosition.y <= click_nivel1_2_2_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Incorrecta;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_2_3_x_inicial && mousePosition.x <= click_nivel1_2_3_x_final &&
                        mousePosition.y >= click_nivel1_2_3_y_inicial && mousePosition.y <= click_nivel1_2_3_y_final)
                    {
                        Respuestas_Vacias5 = Respuesta_Correcta;
                        contador_4++;
                        escenaActual = NIVELES;
                        sonido_de_respuesta_correcta();
                    }
                }
                if (contador_4 > 3)
                {
                    nivel_del_usuario = 3;
                }

                musica_mutear_desmutear();
                finalizar_juego();
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_4), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                EndDrawing();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = NIVELES;
                }
            }

            sleep(1);
            if (contador_4 < 4)
            {
                double tiempoInicial = GetTime();
                while (!WindowShouldClose())
                {
                    double tiempoActual = GetTime();
                    BeginDrawing();
                    ClearBackground(BLACK);

                    if (tiempoActual - tiempoInicial <= 5.0)
                    {

                        ClearBackground(BLUE);
                        DrawTexture(Fondo_de_perdiste_4, 0, 0, WHITE);
                        DrawTexture(Respuestas_Vacias1, 932.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias2, 1010, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias3, 1087.8, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias4, 1164.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias5, 1241.4, 322.1, WHITE);
                        DrawText(TextFormat("%d/5", contador_4), 1342, 330, 50, BLACK);
                    }
                    else
                    {
                        break;
                    }

                    EndDrawing();
                }
            }
            else
            {
                double tiempoInicial = GetTime();
                while (!WindowShouldClose())
                {
                    double tiempoActual = GetTime();

                    BeginDrawing();
                    ClearBackground(BLACK);

                    if (tiempoActual - tiempoInicial <= 5.0)
                    {

                        ClearBackground(BLUE);
                        DrawTexture(Fondo_de_finaldeljuego, 0, 0, WHITE);
                        /*
                        DrawTexture(Respuestas_Vacias1, 932.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias2, 1010, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias3, 1087.8, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias4, 1164.6, 322.1, WHITE);
                        DrawTexture(Respuestas_Vacias5, 1241.4, 322.1, WHITE);
                        DrawText(TextFormat("%d/5", contador_4), 1342, 330, 50, BLACK);
                        */
                    }
                    else
                    {
                        break;
                    }

                    EndDrawing();
                }
            }
            MostrarAutoguardado();
            guardarprogreso(nivel_del_usuario, contador_1, contador_2, contador_3, contador_4, contador_5); // Guardar el progreso actualizado
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
void Mostrarguardado()
{
    double tiempoInicial = GetTime();
    Texture2D guardado = LoadTexture("resources/guardando.png");
    if (IsKeyPressed(KEY_G))
    {
        while (!WindowShouldClose())
        {
            double tiempoActual = GetTime();

            BeginDrawing();
            ClearBackground(BLACK);

            if (tiempoActual - tiempoInicial <= 1.0)
            {
                DrawTexture(guardado, 0, 0, WHITE);
                guardarprogreso(nivel_del_usuario, contador_1, contador_2, contador_3, contador_4, contador_5); // Guardar el progreso actualizado
            }
            else
            {
                break;
            }

            EndDrawing();
        }
    }
}
void MostrarAutoguardado()
{
    double tiempoInicial = GetTime();
    Texture2D autoguardado = LoadTexture("resources/AUTOGUARDADO.png");

    while (!WindowShouldClose())
    {
        double tiempoActual = GetTime();

        BeginDrawing();
        ClearBackground(BLACK);

        if (tiempoActual - tiempoInicial <= 1.0)
        {
            DrawTexture(autoguardado, 0, 0, WHITE);
        }
        else
        {
            break;
        }

        EndDrawing();
    }
}
void musica_mutear_desmutear()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_S))
    {
        Vector2 mousePosition = GetMousePosition();

        if (mousePosition.x >= click_sonido_x_inicial && mousePosition.x <= click_sonido_x_final &&
            mousePosition.y >= click_sonido_y_inicial && mousePosition.y <= click_sonido_y_final)
        {
            pause = !pause;

            if (pause)
            {
                PauseMusicStream(music);

                sonido = LoadTexture("resources/sonido_mute.png");
            }
            else
            {
                ResumeMusicStream(music);
                sonido = LoadTexture("resources/sonido.png");
            }
        }
        if (IsKeyPressed(KEY_S))
        {
            pause = !pause;

            if (pause)
            {
                PauseMusicStream(music);

                sonido = LoadTexture("resources/sonido_mute.png");
            }
            else // Si el estado es no pausa (false)
            {
                ResumeMusicStream(music);
                sonido = LoadTexture("resources/sonido.png");
            }
        }
    }
}
void sonido_de_respuesta_correcta()
{
    double tiempoInicial = GetTime();
    PlayMusicStream(respuesta_correcta);
    SetMusicVolume(respuesta_correcta, 0.6);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(respuesta_correcta);

        double tiempoActual = GetTime();

        // Verificar si han pasado 1.5 segundos
        if (tiempoActual - tiempoInicial > 1.5)
        {
            StopMusicStream(respuesta_correcta);
            break;
        }

        const double tiempo_extra = 0.01; // tiempo para que no se escuche cortado el audio
        while (GetTime() - tiempoActual < tiempo_extra)
        {
        }
    }
}
void sonido_de_respuesta_incorecta()
{
    double tiempoInicial = GetTime();
    PlayMusicStream(respuesta_incorecta);
    SetMusicVolume(respuesta_incorecta, 0.3);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(respuesta_incorecta);

        double tiempoActual = GetTime();

        // Verificar si han pasado 1.5 segundos
        if (tiempoActual - tiempoInicial > 1)
        {
            StopMusicStream(respuesta_incorecta);
            break;
        }

        const double tiempo_extra = 0.01; // tiempo para que no se escuche cortado el audio
        while (GetTime() - tiempoActual < tiempo_extra)
        {
        }
    }
}
