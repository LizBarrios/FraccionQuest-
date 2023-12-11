#include "raylib.h"
#include <stdio.h>

#define MAX_INPUT_CHARS 50

void guardarProceso(const char *nombreUsuario, const char *contrasena)
{
    FILE *archivo = fopen("progreso.txt", "w");

    if (archivo != NULL)
    {
        fprintf(archivo, "Nombre de usuario: %s\nContraseña: %s\n", nombreUsuario, contrasena);
        fclose(archivo);
        printf("Progreso guardado en progreso.txt.\n");
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}

int main()
{
    const int ancho_pantalla = 1920;
    const int alto_pantalla = 1080;

    InitWindow(ancho_pantalla, alto_pantalla, "Guardar Progreso");

    char nombreUsuario[MAX_INPUT_CHARS + 1] = {0};
    char contrasena[MAX_INPUT_CHARS + 1] = {0};

    SetTargetFPS(60);

    // Bucle principal
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Ingrese su nombre de usuario:", ancho_pantalla / 8, alto_pantalla / 4, 20, BLACK);
        DrawRectangle(ancho_pantalla / 8, alto_pantalla / 4 + 50, 220, 30, LIGHTGRAY);
        DrawText(nombreUsuario, ancho_pantalla / 8 + 10, alto_pantalla / 4 + 55, 20, MAROON);

        DrawText("Ingrese su contraseña:", ancho_pantalla / 8, alto_pantalla / 2, 20, BLACK);
        DrawRectangle(ancho_pantalla / 8, alto_pantalla / 2 + 50, 220, 30, LIGHTGRAY);
        DrawText(contrasena, ancho_pantalla / 8 + 10, alto_pantalla / 2 + 55, 20, MAROON);

        EndDrawing();

        // Capturar la entrada del usuario para el nombre de usuario y la contraseña
        int key = GetKeyPressed();
        if ((key >= 32) && (key <= 125))
        {
            int len;
            if (strlen(nombreUsuario) < MAX_INPUT_CHARS)
            {
                len = strlen(nombreUsuario);
                nombreUsuario[len] = (char)key;
                nombreUsuario[len + 1] = '\0';
            }
            if (strlen(contrasena) < MAX_INPUT_CHARS)
            {
                len = strlen(contrasena);
                contrasena[len] = (char)key;
                contrasena[len + 1] = '\0';
            }
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            guardarProceso(nombreUsuario, contrasena);
            printf("Progreso guardado.\n");
            break;
        }
    }

    CloseWindow();
    return 0;
}
