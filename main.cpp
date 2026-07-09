#include "juego.h"
#include "rlutil.h"
#include <windows.h>

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // Configurar semilla aleatoria
    srand(time(nullptr));


    rlutil::saveDefaultColor();
    rlutil::hidecursor();

    // Crear y ejecutar el juego
    JuegoRetro juego;
    juego.mostrarMenu();

    rlutil::showcursor();
    return 0;
}
