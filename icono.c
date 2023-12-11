#include "raylib.h"

int main(void) {
    // Inicializar Raylib y crear una ventana
    InitWindow(800, 450, "Ventana con Icono Personalizado");

    // Cargar una textura para el icono
    Image icono = LoadImage("resources/descarga.png");

    // Ajustar el formato de la imagen para que sea compatible con el icono de la ventana
    ImageResize(&icono, 32, 32); // Cambia el tamaño del icono si es necesario

    // Establecer el icono de la ventana con la textura cargada
    SetWindowIcon(icono);

    // Descargar la imagen de icono (ya no la necesitamos después de establecerla)
    UnloadImage(icono);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Aquí va el código de tu aplicación
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
