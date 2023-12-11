#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int nivel_del_usuario = 0;
int contador_1 = 0;
int contador_2 = 0;
int contador_3 = 0;
int contador_4 = 0;
int contador_1_skin = 0;
int contador_2_skin = 0;
int contador_3_skin = 0;
int contador_4_skin = 0;
int cursor_final = 0;

int tutorial = 0;
Texture2D cursor;

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
    GUARDARPARTIDA,
    SELECCION_DE_CURSOR,
    TUTORIAL,
    INICIO,
    BOTONES,
    SUMAS,
    RESTAS,
    MULTIPLICACION,
    DIVISON,
    CARGAR_PROGRESO,
    NIVELES,
    PREGUNTA_SI_QUIERE_TUTORIAL,
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
void musica_mutear_desmutear();
void sonido_de_respuesta_correcta();
void sonido_de_respuesta_incorecta();
void Mostrarguardado();
void MostrarCargandoProgreso();

void guardarprogreso(char *nombre_archivo, int nivel_del_usuario, int nivel1, int nivel1_skin, int nivel2, int nivel2_skin, int nivel3, int nivel3_skin, int nivel4, int nivel4_skin, int tutorial, int cursor_final)
{
    FILE *file = fopen(nombre_archivo, "w");

    if (file != NULL)
    {
        fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d", nivel_del_usuario, nivel1, nivel1_skin, nivel2, nivel2_skin, nivel3, nivel3_skin, nivel4, nivel4_skin, cursor_final, tutorial);
        fclose(file);
    }
}

void cargarprogreso(char *nombre_archivo, int *nivel_del_usuario, int *nivel1, int *nivel1_skin, int *nivel2, int *nivel2_skin, int *nivel3, int *nivel3_skin, int *nivel4, int *nivel4_skin, int *tutorial, int *cursor_final)
{
    FILE *file = fopen(nombre_archivo, "r");

    if (file != NULL)
    {
        fscanf(file, "%d %d %d %d %d %d %d %d %d %d %d", nivel_del_usuario, nivel1, nivel1_skin, nivel2, nivel2_skin, nivel3, nivel3_skin, nivel4, nivel4_skin, cursor_final, tutorial);
        fclose(file);
    }
}

void finalizar_juego()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        CloseWindow();
    }
}

int main(void)
{
    Image icono = LoadImage("resources/icono.png");

    InitWindow(ancho_pantalla, alto_pantalla, "FractionQuest");
    SetWindowIcon(icono);
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
    Texture2D Fondo_de_perfiles_guardar = LoadTexture("resources/fondo_de_perfiles_guardar.png");
    Texture2D Fondo_de_perfiles_cargar = LoadTexture("resources/fondo_de_perfiles_cargar.png");

    Texture2D Fondo_de_niveles = LoadTexture("resources/niveles.png");
    Texture2D Fondo_de_finaldeljuego = LoadTexture("resources/final_del_juego.png");
    Texture2D Fondo_de_cursores = LoadTexture("resources/fondo_de_cursores.png");

    Texture2D Fondo_de_menu = LoadTexture("resources/menu.png");
    cursor = LoadTexture("resources/cursores/raton.png");
    Texture2D cursor1 = LoadTexture("resources/cursores/raton.png");
    Texture2D cursor2 = LoadTexture("resources/cursores/raton2.png");
    Texture2D cursor3 = LoadTexture("resources/cursores/raton3.png");
    Texture2D cursor4 = LoadTexture("resources/cursores/raton4.png");
    Texture2D cursor5 = LoadTexture("resources/cursores/raton5.png");
    Texture2D cursor6 = LoadTexture("resources/cursores/raton6.png");
    Texture2D bloqueo_de_cursores = LoadTexture("resources/cursores/bloqueo_de_cursores.png");
    Texture2D icono_para_skins_cursores = LoadTexture("resources/cursores/icono_para_skins_cursores.png");

    HideCursor();

    Texture2D Respuestas_Vacias1 = LoadTexture("resources/BIEN_MAL/vacio.png");
    Texture2D Respuestas_Vacias2 = LoadTexture("resources/BIEN_MAL/vacio.png");
    Texture2D Respuestas_Vacias3 = LoadTexture("resources/BIEN_MAL/vacio.png");
    Texture2D Respuestas_Vacias4 = LoadTexture("resources/BIEN_MAL/vacio.png");
    Texture2D Respuestas_Vacias5 = LoadTexture("resources/BIEN_MAL/vacio.png");
    Texture2D Respuesta_Correcta = LoadTexture("resources/BIEN_MAL/respuesta_buena.png");
    Texture2D Respuesta_Incorrecta = LoadTexture("resources/BIEN_MAL/respuesta_mala.png");
    // tutorial
    Texture2D Fondo_de_tutorial = LoadTexture("resources/tutorial/tutorial.png");
    Texture2D Fondo_de_pregunta_tutorial = LoadTexture("resources/tutorial/pregunta_de_tutorial.png");
    Texture2D fondo_de_inicio = LoadTexture("resources/tutorial/inicio_1.png");
    Texture2D Fondo_de_inicio_1 = LoadTexture("resources/tutorial/inicio_1.png");
    Texture2D Fondo_de_inicio_2 = LoadTexture("resources/tutorial/inicio_2.png");
    Texture2D Fondo_de_botones = LoadTexture("resources/tutorial/botones_2.png");
    Texture2D Fondo_de_botones_1 = LoadTexture("resources/tutorial/botones_2.png");
    Texture2D Fondo_de_botones_2 = LoadTexture("resources/tutorial/botones_1.png");
    Texture2D Fondo_de_sumas = LoadTexture("resources/tutorial/sumas_1.png");
    Texture2D Fondo_de_sumas_l = LoadTexture("resources/tutorial/sumas_1.png");
    Texture2D Fondo_de_sumas_2 = LoadTexture("resources/tutorial/sumas_2.png");
    Texture2D Fondo_de_restas = LoadTexture("resources/tutorial/restas_1.png");
    Texture2D Fondo_de_restas_l = LoadTexture("resources/tutorial/restas_1.png");
    Texture2D Fondo_de_restas_2 = LoadTexture("resources/tutorial/restas_2.png");
    Texture2D Fondo_de_multiplicacion = LoadTexture("resources/tutorial/multiplicacion_1.png");
    Texture2D Fondo_de_division = LoadTexture("resources/tutorial/division_1.png");
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
    // nivel 4
    Texture2D Fondo_4_1 = LoadTexture("resources/nivel4/nivel4_1.png");
    Texture2D Fondo_4_2 = LoadTexture("resources/nivel4/nivel4_2.png");
    Texture2D Fondo_4_3 = LoadTexture("resources/nivel4/nivel4_3.png");
    Texture2D Fondo_4_4 = LoadTexture("resources/nivel4/nivel4_4.png");
    Texture2D Fondo_4_5 = LoadTexture("resources/nivel4/nivel4_5.png");
    Texture2D Fondo_de_perdiste_4 = LoadTexture("resources/nivel4/Fondo_de_perdiste_4.png");
    /////////////////////////////////////////////////////////////////////////////////////////////
    music.looping = true;
    respuesta_correcta.looping = true;
    respuesta_incorecta.looping = true;
    pause = false;

    PlayMusicStream(music);
    SetMusicVolume(music, 0.5); // Establecer el volumen al 50%
    // ==========      PANTALLA DE CARGA      ===============
    float contador_segundos = 0.0f;
    while (contador_segundos < 4.0f && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(Fondo_de_cargando, 0, 0, WHITE);
        DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
        EndDrawing();
        contador_segundos += GetFrameTime();
    }
    //
    while (!WindowShouldClose())
    {
        BeginDrawing();

        UpdateMusicStream(music);
        DrawTexture(sonido, 1770, 10, WHITE);

        switch (escenaActual)
        {
        case MENU:
        {

            while (escenaActual == MENU)
            {
                UpdateMusicStream(music);
                DrawTexture(Fondo_de_menu, 0, 0, WHITE);

                DrawTexture(sonido, 1770, 10, WHITE);

                if (IsKeyPressed(KEY_F11))
                {
                    ToggleFullscreen();
                }
                // tutorial
                const int click_inicio_x_inicial = 556.1;
                const int click_inicio_x_final = 1339.7;
                const int click_inicio_y_inicial = 494.8;
                const int click_inicio_y_final = 594.5;
                // guardar progreso
                const int click_guardar_x_inicial = 556.1;
                const int click_guardar_x_final = 1339.7;
                const int click_guardar_y_inicial = 376.1;
                const int click_guardar_y_final = 475.8;
                // niveles
                const int click_niveles_x_inicial = 556.1;
                const int click_niveles_x_final = 1339.7;
                const int click_niveles_y_inicial = 613.9;
                const int click_niveles_y_final = 713.6;
                // cargar progreso
                const int click_CARGAR_PROGRESO_x_inicial = 556.1;
                const int click_CARGAR_PROGRESO_x_final = 1339.7;
                const int click_CARGAR_PROGRESO_y_inicial = 732.6;
                const int click_CARGAR_PROGRESO_y_final = 832.3;
                // salir
                const int click_salir_x_inicial = 556.1;
                const int click_salir_x_final = 1339.7;
                const int click_salir_y_inicial = 851.3;
                const int click_salir_y_final = 951;
                DrawTexture(icono_para_skins_cursores, 1680, 840, WHITE);

                const int click_cursor_x_inicial = 1766;
                const int click_cursor_x_final = 1894;
                const int click_cursor_y_inicial = 900;
                const int click_cursor_y_final = 1054;

                musica_mutear_desmutear();
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();

                    if (mousePosition.x >= click_inicio_x_inicial && mousePosition.x <= click_inicio_x_final &&
                        mousePosition.y >= click_inicio_y_inicial && mousePosition.y <= click_inicio_y_final)
                    {
                        escenaActual = TUTORIAL;
                    }
                    if (mousePosition.x >= click_guardar_x_inicial && mousePosition.x <= click_guardar_x_final &&
                        mousePosition.y >= click_guardar_y_inicial && mousePosition.y <= click_guardar_y_final)
                    {
                        escenaActual = GUARDARPARTIDA;
                    }
                    if (mousePosition.x >= click_niveles_x_inicial && mousePosition.x <= click_niveles_x_final &&
                        mousePosition.y >= click_niveles_y_inicial && mousePosition.y <= click_niveles_y_final)
                    {
                        if (tutorial == 0)
                        {
                            escenaActual = PREGUNTA_SI_QUIERE_TUTORIAL;
                        }
                        else
                        {
                            escenaActual = NIVELES;
                        }
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
                    if (mousePosition.x >= click_cursor_x_inicial && mousePosition.x <= click_cursor_x_final &&
                        mousePosition.y >= click_cursor_y_inicial && mousePosition.y <= click_cursor_y_final)
                    {
                        escenaActual = SELECCION_DE_CURSOR;
                    }
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);

                finalizar_juego();
                EndDrawing();
            }
        }
        break;
        case GUARDARPARTIDA:
        {

            while (escenaActual == GUARDARPARTIDA)
            {
                ClearBackground(BLACK);
                DrawTexture(Fondo_de_perfiles_guardar, 0, 0, WHITE);
                UpdateMusicStream(music);
                DrawTexture(sonido, 1770, 10, WHITE);

                const int click_nivel1_x_inicial = 230;
                const int click_nivel1_x_final = 554;
                const int click_nivel1_y_inicial = 550.2;
                const int click_nivel1_y_final = 874.2;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel1_x_inicial && mousePosition.x <= click_nivel1_x_final &&
                        mousePosition.y >= click_nivel1_y_inicial && mousePosition.y <= click_nivel1_y_final)
                    {
                        guardarprogreso("partida1.txt", nivel_del_usuario, contador_1, contador_1_skin, contador_2, contador_2_skin, contador_3, contador_3_skin, contador_4, contador_4_skin, cursor_final, tutorial);
                        Mostrarguardado();
                    }
                }
                const int click_nivel2_x_inicial = 798;
                const int click_nivel2_x_final = 1122;
                const int click_nivel2_y_inicial = 550.2;
                const int click_nivel2_y_final = 874.2;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel2_x_inicial && mousePosition.x <= click_nivel2_x_final &&
                        mousePosition.y >= click_nivel2_y_inicial && mousePosition.y <= click_nivel2_y_final)
                    {
                        guardarprogreso("partida2.txt", nivel_del_usuario, contador_1, contador_1_skin, contador_2, contador_2_skin, contador_3, contador_3_skin, contador_4, contador_4_skin, cursor_final, tutorial);
                        Mostrarguardado();
                    }
                }
                const int click_nivel3_x_inicial = 1366;
                const int click_nivel3_x_final = 1690;
                const int click_nivel3_y_inicial = 550.2;
                const int click_nivel3_y_final = 874.2;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel3_x_inicial && mousePosition.x <= click_nivel3_x_final &&
                        mousePosition.y >= click_nivel3_y_inicial && mousePosition.y <= click_nivel3_y_final)
                    {
                        guardarprogreso("partida3.txt", nivel_del_usuario, contador_1, contador_1_skin, contador_2, contador_2_skin, contador_3, contador_3_skin, contador_4, contador_4_skin, cursor_final, tutorial);
                        Mostrarguardado();
                    }
                }
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                const int click_home_x_inicial = 21.3;
                const int click_home_x_final = 149.3;
                const int click_home_y_inicial = 24;
                const int click_home_y_final = 140.3;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_home_x_inicial && mousePosition.x <= click_home_x_final &&
                        mousePosition.y >= click_home_y_inicial && mousePosition.y <= click_home_y_final)
                    {
                        escenaActual = MENU;
                    }
                }
                musica_mutear_desmutear();
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                finalizar_juego();
                EndDrawing();
            }
        }
        break;
        case SELECCION_DE_CURSOR:
        {
            while (escenaActual == SELECCION_DE_CURSOR)
            {
                ClearBackground(BLACK);
                DrawTexture(Fondo_de_cursores, 0, 0, WHITE);
                UpdateMusicStream(music);

                DrawTexture(sonido, 1770, 10, WHITE);

                const int click_nivel1_x_inicial = 202.5;
                const int click_nivel1_x_final = 458.5;
                const int click_nivel1_y_inicial = 72.9;
                const int click_nivel1_y_final = 328.9;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel1_x_inicial && mousePosition.x <= click_nivel1_x_final &&
                        mousePosition.y >= click_nivel1_y_inicial && mousePosition.y <= click_nivel1_y_final)
                    {
                        cursor = cursor1;
                    }
                }
                if (contador_1_skin == 1)
                {
                    const int click_nivel2_x_inicial = 647.8;
                    const int click_nivel2_x_final = 903.8;
                    const int click_nivel2_y_inicial = 72.9;
                    const int click_nivel2_y_final = 328.9;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 mousePosition = GetMousePosition();
                        if (mousePosition.x >= click_nivel2_x_inicial && mousePosition.x <= click_nivel2_x_final &&
                            mousePosition.y >= click_nivel2_y_inicial && mousePosition.y <= click_nivel2_y_final)
                        {
                            cursor = cursor2;
                        }
                    }
                }
                else
                {
                    DrawTexture(bloqueo_de_cursores, 648.8, 73.9, BLACK);
                    DrawText("Se desbloquea completando\n\n      el %100 del nivel 1", 643, 163, 20, WHITE);
                }
                if (contador_2_skin == 1)
                {
                    const int click_nivel3_x_inicial = 202.5;
                    const int click_nivel3_x_final = 458.5;
                    const int click_nivel3_y_inicial = 412.1;
                    const int click_nivel3_y_final = 668.1;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 mousePosition = GetMousePosition();
                        if (mousePosition.x >= click_nivel3_x_inicial && mousePosition.x <= click_nivel3_x_final &&
                            mousePosition.y >= click_nivel3_y_inicial && mousePosition.y <= click_nivel3_y_final)
                        {
                            cursor = cursor3;
                        }
                    }
                }
                else
                {

                    DrawTexture(bloqueo_de_cursores, 203.5, 412.1, BLACK);
                    DrawText("Se desbloquea completando\n\n       el %100 del nivel 2", 189, 508, 20, WHITE);
                }
                if (contador_3_skin == 1)
                {
                    const int click_nivel4_x_inicial = 647.8;
                    const int click_nivel4_x_final = 903.8;
                    const int click_nivel4_y_inicial = 412.1;
                    const int click_nivel4_y_final = 668.1;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 mousePosition = GetMousePosition();
                        if (mousePosition.x >= click_nivel4_x_inicial && mousePosition.x <= click_nivel4_x_final &&
                            mousePosition.y >= click_nivel4_y_inicial && mousePosition.y <= click_nivel4_y_final)
                        {
                            cursor = cursor4;
                        }
                    }
                }
                else
                {
                    DrawTexture(bloqueo_de_cursores, 648.8, 412.1, BLACK);

                    DrawText("Se desbloquea completando\n\n       el %100 del nivel 3", 643, 508, 20, WHITE);
                }
                if (contador_4_skin == 1)
                {
                    const int click_nivel5_x_inicial = 202.5;
                    const int click_nivel5_x_final = 458.5;
                    const int click_nivel5_y_inicial = 751.1;
                    const int click_nivel5_y_final = 1007.1;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 mousePosition = GetMousePosition();
                        if (mousePosition.x >= click_nivel5_x_inicial && mousePosition.x <= click_nivel5_x_final &&
                            mousePosition.y >= click_nivel5_y_inicial && mousePosition.y <= click_nivel5_y_final)
                        {
                            cursor = cursor5;
                        }
                    }
                }
                else
                {
                    DrawTexture(bloqueo_de_cursores, 202.5, 751.1, BLACK);

                    DrawText("Se desbloquea completando\n\n       el %100 del nivel 4", 194.5, 851.1, 20, WHITE);
                }
                cursor_final = contador_1_skin + contador_2_skin + contador_3_skin + contador_4_skin;
                if (cursor_final == 4)
                {
                    const int click_nivel6_x_inicial = 1301.9;
                    const int click_nivel6_x_final = 1558.9;
                    const int click_nivel6_y_inicial = 412;
                    const int click_nivel6_y_final = 668;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 mousePosition = GetMousePosition();
                        if (mousePosition.x >= click_nivel6_x_inicial && mousePosition.x <= click_nivel6_x_final &&
                            mousePosition.y >= click_nivel6_y_inicial && mousePosition.y <= click_nivel6_y_final)
                        {
                            cursor = cursor6;
                        }
                    }
                }
                else
                {
                    DrawTexture(bloqueo_de_cursores, 1302.8, 412, BLACK);
                    DrawText("Se desbloquea completando\n\n al %100 todos los niveles", 1296.8, 512, 20, WHITE);
                }
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                const int click_home_x_inicial = 21.3;
                const int click_home_x_final = 149.3;
                const int click_home_y_inicial = 24;
                const int click_home_y_final = 140.3;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_home_x_inicial && mousePosition.x <= click_home_x_final &&
                        mousePosition.y >= click_home_y_inicial && mousePosition.y <= click_home_y_final)
                    {
                        escenaActual = MENU;
                    }
                }
                musica_mutear_desmutear();
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                finalizar_juego();
                EndDrawing();
            }
        }
        break;
        case TUTORIAL:
        {

            while (escenaActual == TUTORIAL)
            {
                ClearBackground(BLACK);
                DrawTexture(Fondo_de_tutorial, 0, 0, WHITE);
                UpdateMusicStream(music);

                DrawTexture(sonido, 1770, 10, WHITE);

                // botones

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
                        escenaActual = BOTONES;
                    }
                }
                // sumas
                if (tutorial == 1)
                {
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
                            escenaActual = SUMAS;
                        }
                    }
                }
                else
                {
                    DrawTexture(candados_de_niveles, 1079.5, 417.5, BLACK);
                }
                // restas
                if (tutorial == 1)
                {
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
                            escenaActual = RESTAS;
                        }
                    }
                }
                else
                {
                    DrawTexture(candados_de_niveles, 1518.5, 397.6, BLACK);
                }

                // multiplicacion
                if (tutorial == 1)
                {
                    const int click_nivel3_x_inicial = 155.5;
                    const int click_nivel3_x_final = 411.5;
                    const int click_nivel3_y_inicial = 716;
                    const int click_nivel3_y_final = 932;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 mousePosition = GetMousePosition();
                        if (mousePosition.x >= click_nivel3_x_inicial && mousePosition.x <= click_nivel3_x_final &&
                            mousePosition.y >= click_nivel3_y_inicial && mousePosition.y <= click_nivel3_y_final)
                        {
                            escenaActual = MULTIPLICACION;
                        }
                    }
                }
                else
                {
                    DrawTexture(candados_de_niveles, 201.3, 739.5, BLACK);
                }
                // division
                if (tutorial == 1)
                {
                    const int click_nivel3_x_inicial = 594.5;
                    const int click_nivel3_x_final = 850.5;
                    const int click_nivel3_y_inicial = 716;
                    const int click_nivel3_y_final = 932;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 mousePosition = GetMousePosition();
                        if (mousePosition.x >= click_nivel3_x_inicial && mousePosition.x <= click_nivel3_x_final &&
                            mousePosition.y >= click_nivel3_y_inicial && mousePosition.y <= click_nivel3_y_final)
                        {
                            escenaActual = DIVISON;
                        }
                    }
                }
                else
                {
                    DrawTexture(candados_de_niveles, 640.3, 739.5, BLACK);
                }
                // inicio
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
                        escenaActual = INICIO;
                        tutorial = 1;
                    }
                }
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                const int click_home_x_inicial = 21.3;
                const int click_home_x_final = 149.3;
                const int click_home_y_inicial = 24;
                const int click_home_y_final = 140.3;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_home_x_inicial && mousePosition.x <= click_home_x_final &&
                        mousePosition.y >= click_home_y_inicial && mousePosition.y <= click_home_y_final)
                    {
                        escenaActual = MENU;
                    }
                }
                musica_mutear_desmutear();
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                finalizar_juego();
                EndDrawing();
            }
        }
        break;
        case INICIO:
        {
            while (escenaActual == INICIO)
            {

                ClearBackground(BLUE);
                DrawTexture(fondo_de_inicio, 0, 0, WHITE);

                if (IsKeyPressed(KEY_RIGHT))
                {

                    fondo_de_inicio = Fondo_de_inicio_2;
                }

                if (IsKeyPressed(KEY_LEFT))
                {
                    fondo_de_inicio = Fondo_de_inicio_1;
                }

                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                EndDrawing();
                const int click_menudesalida_no_x_inicial = 1742.6;
                const int click_menudesalida_no_x_final = 1880.8;
                const int click_menudesalida_no_y_inicial = 37;
                const int click_menudesalida_no_y_final = 165;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_menudesalida_no_x_inicial && mousePosition.x <= click_menudesalida_no_x_final &&
                        mousePosition.y >= click_menudesalida_no_y_inicial && mousePosition.y <= click_menudesalida_no_y_final)
                    {
                        escenaActual = TUTORIAL;
                    }
                }
            }
            fondo_de_inicio = LoadTexture("resources/tutorial/inicio_1.png");
        }
        break;
        case BOTONES:
        {
            while (escenaActual == BOTONES)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_de_botones, 0, 0, WHITE);

                if (IsKeyPressed(KEY_RIGHT))
                {
                    Fondo_de_botones = Fondo_de_botones_2;
                }

                if (IsKeyPressed(KEY_LEFT))
                {
                    Fondo_de_botones = Fondo_de_botones_1;
                }

                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                EndDrawing();
                const int click_menudesalida_no_x_inicial = 1742.6;
                const int click_menudesalida_no_x_final = 1880.8;
                const int click_menudesalida_no_y_inicial = 37;
                const int click_menudesalida_no_y_final = 165;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_menudesalida_no_x_inicial && mousePosition.x <= click_menudesalida_no_x_final &&
                        mousePosition.y >= click_menudesalida_no_y_inicial && mousePosition.y <= click_menudesalida_no_y_final)
                    {
                        escenaActual = TUTORIAL;
                    }
                }
            }
            Fondo_de_botones = LoadTexture("resources/tutorial/botones_2.png");
        }
        break;
        case SUMAS:
        {
            while (escenaActual == SUMAS)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_de_sumas, 0, 0, WHITE);

                if (IsKeyPressed(KEY_RIGHT))
                {
                    Fondo_de_sumas = Fondo_de_sumas_2;
                }

                if (IsKeyPressed(KEY_LEFT))
                {
                    Fondo_de_sumas = Fondo_de_sumas_l;
                }

                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                EndDrawing();
                const int click_menudesalida_no_x_inicial = 1742.6;
                const int click_menudesalida_no_x_final = 1880.8;
                const int click_menudesalida_no_y_inicial = 37;
                const int click_menudesalida_no_y_final = 165;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_menudesalida_no_x_inicial && mousePosition.x <= click_menudesalida_no_x_final &&
                        mousePosition.y >= click_menudesalida_no_y_inicial && mousePosition.y <= click_menudesalida_no_y_final)
                    {
                        escenaActual = TUTORIAL;
                    }
                }
            }
            Fondo_de_sumas = LoadTexture("resources/tutorial/sumas_1.png");
        }
        break;
        case RESTAS:
        {
            while (escenaActual == RESTAS)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_de_restas, 0, 0, WHITE);

                if (IsKeyPressed(KEY_RIGHT))
                {

                    Fondo_de_restas = Fondo_de_restas_2;
                }

                if (IsKeyPressed(KEY_LEFT))
                {
                    Fondo_de_restas = Fondo_de_restas_l;
                }

                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                EndDrawing();
                const int click_menudesalida_no_x_inicial = 1742.6;
                const int click_menudesalida_no_x_final = 1880.8;
                const int click_menudesalida_no_y_inicial = 37;
                const int click_menudesalida_no_y_final = 165;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_menudesalida_no_x_inicial && mousePosition.x <= click_menudesalida_no_x_final &&
                        mousePosition.y >= click_menudesalida_no_y_inicial && mousePosition.y <= click_menudesalida_no_y_final)
                    {
                        escenaActual = TUTORIAL;
                    }
                }
            }
            Fondo_de_restas = LoadTexture("resources/tutorial/restas_1.png");
        }
        break;
        case MULTIPLICACION:
        {
            while (escenaActual == MULTIPLICACION)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_de_multiplicacion, 0, 0, WHITE);

                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                EndDrawing();
                const int click_menudesalida_no_x_inicial = 1742.6;
                const int click_menudesalida_no_x_final = 1880.8;
                const int click_menudesalida_no_y_inicial = 37;
                const int click_menudesalida_no_y_final = 165;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_menudesalida_no_x_inicial && mousePosition.x <= click_menudesalida_no_x_final &&
                        mousePosition.y >= click_menudesalida_no_y_inicial && mousePosition.y <= click_menudesalida_no_y_final)
                    {
                        escenaActual = TUTORIAL;
                    }
                }
            }
            Fondo_de_multiplicacion = LoadTexture("resources/tutorial/multiplicacion_1.png");
        }
        break;
        case DIVISON:
        {
            while (escenaActual == DIVISON)
            {

                ClearBackground(BLUE);
                DrawTexture(Fondo_de_division, 0, 0, WHITE);

                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                const int click_menudesalida_no_x_inicial = 1742.6;
                const int click_menudesalida_no_x_final = 1880.8;
                const int click_menudesalida_no_y_inicial = 37;
                const int click_menudesalida_no_y_final = 165;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_menudesalida_no_x_inicial && mousePosition.x <= click_menudesalida_no_x_final &&
                        mousePosition.y >= click_menudesalida_no_y_inicial && mousePosition.y <= click_menudesalida_no_y_final)
                    {
                        escenaActual = TUTORIAL;
                    }
                }
                EndDrawing();
                finalizar_juego();
            }
            Fondo_de_division = LoadTexture("resources/tutorial/division_1.png");
        }
        break;
        case CARGAR_PROGRESO:
        {

            while (escenaActual == CARGAR_PROGRESO)
            {
                ClearBackground(BLACK);
                DrawTexture(Fondo_de_perfiles_cargar, 0, 0, WHITE);
                UpdateMusicStream(music);
                DrawTexture(sonido, 1770, 10, WHITE);

                const int click_nivel1_x_inicial = 230;
                const int click_nivel1_x_final = 554;
                const int click_nivel1_y_inicial = 550.2;
                const int click_nivel1_y_final = 874.2;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel1_x_inicial && mousePosition.x <= click_nivel1_x_final &&
                        mousePosition.y >= click_nivel1_y_inicial && mousePosition.y <= click_nivel1_y_final)
                    {
                        cargarprogreso("partida1.txt", &nivel_del_usuario, &contador_1, &contador_1_skin, &contador_2, &contador_2_skin, &contador_3, &contador_3_skin, &contador_4, &contador_4_skin, &cursor_final, &tutorial);
                        MostrarCargandoProgreso();
                    }
                }
                const int click_nivel2_x_inicial = 798;
                const int click_nivel2_x_final = 1122;
                const int click_nivel2_y_inicial = 550.2;
                const int click_nivel2_y_final = 874.2;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel2_x_inicial && mousePosition.x <= click_nivel2_x_final &&
                        mousePosition.y >= click_nivel2_y_inicial && mousePosition.y <= click_nivel2_y_final)
                    {
                        cargarprogreso("partida2.txt", &nivel_del_usuario, &contador_1, &contador_1_skin, &contador_2, &contador_2_skin, &contador_3, &contador_3_skin, &contador_4, &contador_4_skin, &cursor_final, &tutorial);
                        MostrarCargandoProgreso();
                    }
                }
                const int click_nivel3_x_inicial = 1366;
                const int click_nivel3_x_final = 1690;
                const int click_nivel3_y_inicial = 550.2;
                const int click_nivel3_y_final = 874.2;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_nivel3_x_inicial && mousePosition.x <= click_nivel3_x_final &&
                        mousePosition.y >= click_nivel3_y_inicial && mousePosition.y <= click_nivel3_y_final)
                    {
                        cargarprogreso("partida3.txt", &nivel_del_usuario, &contador_1, &contador_1_skin, &contador_2, &contador_2_skin, &contador_3, &contador_3_skin, &contador_4, &contador_4_skin, &cursor_final, &tutorial);
                        MostrarCargandoProgreso();
                    }
                }
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                const int click_home_x_inicial = 21.3;
                const int click_home_x_final = 149.3;
                const int click_home_y_inicial = 24;
                const int click_home_y_final = 140.3;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_home_x_inicial && mousePosition.x <= click_home_x_final &&
                        mousePosition.y >= click_home_y_inicial && mousePosition.y <= click_home_y_final)
                    {
                        escenaActual = MENU;
                    }
                }
                musica_mutear_desmutear();
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                finalizar_juego();
                EndDrawing();
            }
        }
        break;
        case PREGUNTA_SI_QUIERE_TUTORIAL:
        {

            while (escenaActual == PREGUNTA_SI_QUIERE_TUTORIAL)
            {
                UpdateMusicStream(music);

                ClearBackground(BLUE);
                DrawTexture(Fondo_de_pregunta_tutorial, 0, 0, WHITE);

                UpdateMusicStream(music);
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
                        escenaActual = TUTORIAL;
                        tutorial = 1;
                    }
                    if (mousePosition.x >= click_menudesalida_no_x_inicial && mousePosition.x <= click_menudesalida_no_x_final &&
                        mousePosition.y >= click_menudesalida_no_y_inicial && mousePosition.y <= click_menudesalida_no_y_final)
                    {
                        escenaActual = NIVELES;
                        tutorial = 1;
                    }
                }
                musica_mutear_desmutear();
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                finalizar_juego();
                EndDrawing();
            }
            // Guardar el progreso actualizado
        }
        break;
        case NIVELES:
        {

            while (escenaActual == NIVELES)
            {
                ClearBackground(BLACK);
                DrawTexture(Fondo_de_niveles, 0, 0, WHITE);
                UpdateMusicStream(music);

                DrawTexture(sonido, 1770, 10, WHITE);

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
                const int click_home_x_inicial = 21.3;
                const int click_home_x_final = 149.3;
                const int click_home_y_inicial = 24;
                const int click_home_y_final = 140.3;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePosition = GetMousePosition();
                    if (mousePosition.x >= click_home_x_inicial && mousePosition.x <= click_home_x_final &&
                        mousePosition.y >= click_home_y_inicial && mousePosition.y <= click_home_y_final)
                    {
                        escenaActual = MENU;
                    }
                }
                musica_mutear_desmutear();
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);

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

                ClearBackground(BLUE);
                DrawTexture(Fondo_de_salida, 0, 0, WHITE);
                UpdateMusicStream(music);
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
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
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
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);

                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
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
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);

                finalizar_juego();
                musica_mutear_desmutear();

                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
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

                DrawTexture(sonido, 1770, 10, BLACK);

                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);

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
                if (contador_1 == 5)
                {
                    contador_1_skin = 1;
                }
                musica_mutear_desmutear();
                finalizar_juego();
                DrawText(TextFormat("%d/5", contador_1), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                EndDrawing();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
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

                    DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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

                    DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                    EndDrawing();
                }
            }
            // Guardar el progreso actualizado
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
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);

                finalizar_juego();
                musica_mutear_desmutear();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
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
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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

                DrawTexture(sonido, 1770, 10, BLACK);

                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);

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
                if (contador_2 == 5)
                {
                    contador_2_skin = 1;
                }
                musica_mutear_desmutear();
                finalizar_juego();
                DrawText(TextFormat("%d/5", contador_2), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                EndDrawing();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
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

                    DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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

                    DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                    EndDrawing();
                }
            }
            // Guardar el progreso actualizado
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
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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

                DrawTexture(sonido, 1770, 10, BLACK);

                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);

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
                if (contador_3 == 5)
                {
                    contador_3_skin = 1;
                }
                musica_mutear_desmutear();
                finalizar_juego();
                DrawText(TextFormat("%d/5", contador_3), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                EndDrawing();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
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

                    DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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

                    DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                    EndDrawing();
                }
            }
            // Guardar el progreso actualizado
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
                        Respuestas_Vacias1 = Respuesta_Incorrecta;
                        escenaActual = ejercicio2_nivel4;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias1 = Respuesta_Correcta;
                        contador_4++;
                        escenaActual = ejercicio2_nivel4;
                        sonido_de_respuesta_correcta();
                    }
                }
                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawText(TextFormat("%d/5", contador_4), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                finalizar_juego();
                musica_mutear_desmutear();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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

                        Respuestas_Vacias2 = Respuesta_Correcta;
                        contador_4++;
                        escenaActual = ejercicio3_nivel4;
                        sonido_de_respuesta_correcta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias2 = Respuesta_Incorrecta;
                        escenaActual = ejercicio3_nivel4;
                        sonido_de_respuesta_incorecta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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

                        Respuestas_Vacias3 = Respuesta_Incorrecta;
                        escenaActual = ejercicio4_nivel4;
                        sonido_de_respuesta_incorecta();
                    }
                    if (mousePosition.x >= click_nivel1_1_3_x_inicial && mousePosition.x <= click_nivel1_1_3_x_final &&
                        mousePosition.y >= click_nivel1_1_3_y_inicial && mousePosition.y <= click_nivel1_1_3_y_final)
                    {
                        Respuestas_Vacias3 = Respuesta_Correcta;
                        contador_4++;
                        escenaActual = ejercicio4_nivel4;
                        sonido_de_respuesta_correcta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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
                        Respuestas_Vacias4 = Respuesta_Incorrecta;
                        escenaActual = ejercicio5_nivel4;
                        sonido_de_respuesta_incorecta();
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
                        Respuestas_Vacias4 = Respuesta_Correcta;
                        contador_4++;
                        escenaActual = ejercicio5_nivel4;
                        sonido_de_respuesta_correcta();
                    }
                }
                musica_mutear_desmutear();
                finalizar_juego();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
                }
                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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

                DrawTexture(sonido, 1770, 10, BLACK);

                DrawTexture(Respuestas_Vacias1, (ancho_pantalla / 2) + 192, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias2, (ancho_pantalla / 2) + 270, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias3, (ancho_pantalla / 2) + 348, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias4, (ancho_pantalla / 2) + 426, (alto_pantalla / 2) - 435, WHITE);
                DrawTexture(Respuestas_Vacias5, (ancho_pantalla / 2) + 504, (alto_pantalla / 2) - 435, WHITE);

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
                if (contador_4 == 5)
                {
                    contador_4_skin = 1;
                }

                musica_mutear_desmutear();
                finalizar_juego();
                DrawText(TextFormat("%d/5", contador_4), (ancho_pantalla / 2) + 577, (alto_pantalla / 2) - 425, 50, BLACK);

                DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                EndDrawing();
                if (IsKeyPressed(KEY_J))
                {
                    escenaActual = MENU;
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

                    DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
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
                    }
                    else
                    {
                        break;
                    }
                    DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                    DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
                    EndDrawing();
                }
            }
            // Guardar el progreso actualizado
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

    DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
    EndDrawing();

    UnloadTexture(sonido);
    StopMusicStream(music);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
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
/*
void sonido_de_respuesta_correcta()
{
    double tiempoInicial = GetTime();
    PlayMusicStream(respuesta_correcta);
    SetMusicVolume(respuesta_correcta, 0.6);
    BeginDrawing();

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
        DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
    }
    EndDrawing();
}
*/
void sonido_de_respuesta_correcta()
{
    double tiempoInicial;
    tiempoInicial = GetTime();
    Texture2D fondo_bien = LoadTexture("resources/BIEN_MAL/fondo_bien.png");
    PlayMusicStream(respuesta_correcta);
    SetMusicVolume(respuesta_correcta, 0.3);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(respuesta_correcta);

        double tiempoActual = GetTime();

        BeginDrawing();

        if (tiempoActual - tiempoInicial <= 1.0)
        {
            DrawTexture(fondo_bien, 0, 0, WHITE);
        }
        else
        {
            StopMusicStream(respuesta_correcta);

            break;
        }

        EndDrawing();
    }
}
/*
void sonido_de_respuesta_incorecta()
{
    double tiempoInicial = GetTime();
    PlayMusicStream(respuesta_incorecta);
    SetMusicVolume(respuesta_incorecta, 0.3);
    BeginDrawing();

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
        DrawTexture(cursor, GetMouseX(), GetMouseY(), WHITE);
    }
    EndDrawing();
}
*/
void sonido_de_respuesta_incorecta()
{
    double tiempoInicial;
    tiempoInicial = GetTime();
    Texture2D fondo_mal = LoadTexture("resources/BIEN_MAL/fondo_mal.png");
    PlayMusicStream(respuesta_incorecta);
    SetMusicVolume(respuesta_incorecta, 0.3);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(respuesta_incorecta);

        double tiempoActual = GetTime();

        BeginDrawing();

        if (tiempoActual - tiempoInicial <= 1.0)
        {
            DrawTexture(fondo_mal, 0, 0, WHITE);
        }
        else
        {
            StopMusicStream(respuesta_incorecta);

            break;
        }

        EndDrawing();
    }
}
void Mostrarguardado()
{
    double tiempoInicial;

    tiempoInicial = GetTime();

    Texture2D guardado = LoadTexture("resources/guardando.png");

    while (!WindowShouldClose())
    {
        double tiempoActual = GetTime();

        BeginDrawing();
        ClearBackground(BLACK);

        if (tiempoActual - tiempoInicial <= 1.0)
        {
            DrawTexture(guardado, 0, 0, WHITE);
        }
        else
        {
            break;
        }

        EndDrawing();
    }
}
void MostrarCargandoProgreso()
{
    double tiempoInicial;

    tiempoInicial = GetTime();

    Texture2D progreso = LoadTexture("resources/CARGANDO_PROGRESO.png");

    while (!WindowShouldClose())
    {
        double tiempoActual = GetTime();

        BeginDrawing();
        ClearBackground(BLACK);

        if (tiempoActual - tiempoInicial <= 1.0)
        {
            DrawTexture(progreso, 0, 0, WHITE);
        }
        else
        {
            break;
        }

        EndDrawing();
    }
}