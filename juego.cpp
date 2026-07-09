#include "juego.h"
#include <cstdlib>

// ==================== IMPLEMENTACIÓN DADO VISUAL ====================
DadoVisual::DadoVisual(int caras) : caras(caras), valor(0) {
    representacion.resize(5);
    generarRepresentacion(1);
}

int DadoVisual::tirar() {
    valor = rand() % caras + 1;
    generarRepresentacion(valor);
    return valor;
}

int DadoVisual::getValor() const {
    return valor;
}

void DadoVisual::setValor(int nuevoValor) {
    valor = nuevoValor;
    generarRepresentacion(valor);
}

vector<string> DadoVisual::getRepresentacion() const {
    return representacion;
}

void DadoVisual::generarRepresentacion(int valor) {
    vector<string> dado = {
        "┌─────┐",
        "│     │",
        "│  ●  │",
        "│     │",
        "└─────┘"
    };

    switch(valor) {
        case 1:
            dado = {
                "┌─────┐",
                "│     │",
                "│  ●  │",
                "│     │",
                "└─────┘"
            };
            break;
        case 2:
            dado = {
                "┌─────┐",
                "│ ●   │",
                "│     │",
                "│   ● │",
                "└─────┘"
            };
            break;
        case 3:
            dado = {
                "┌─────┐",
                "│ ●   │",
                "│  ●  │",
                "│   ● │",
                "└─────┘"
            };
            break;
        case 4:
            dado = {
                "┌─────┐",
                "│ ● ● │",
                "│     │",
                "│ ● ● │",
                "└─────┘"
            };
            break;
        case 5:
            dado = {
                "┌─────┐",
                "│ ● ● │",
                "│  ●  │",
                "│ ● ● │",
                "└─────┘"
            };
            break;
        case 6:
            dado = {
                "┌─────┐",
                "│ ● ● │",
                "│ ● ● │",
                "│ ● ● │",
                "└─────┘"
            };
            break;
        default:
            break;
    }

    representacion = dado;
}


static int anchoVisible(const string& s) {
    int columnas = 0;
    for (size_t i = 0; i < s.size(); ) {
        unsigned char c = s[i];
        if ((c & 0x80) == 0x00) i += 1;
        else if ((c & 0xE0) == 0xC0) i += 2;
        else if ((c & 0xF0) == 0xE0) i += 3;
        else if ((c & 0xF8) == 0xF0) i += 4;
        else i += 1;
        columnas++;
    }
    return columnas;
}

// ==================== IMPLEMENTACIÓN INTERFAZ RETRO ====================
InterfazRetro::InterfazRetro() {
    anchoPantalla = rlutil::tcols();
    altoPantalla = rlutil::trows();
    if (anchoPantalla < 80) anchoPantalla = 80;
    if (altoPantalla < 25) altoPantalla = 25;
}

void InterfazRetro::dibujarMarco(int x, int y, int ancho, int alto, const string& estilo) const {
    string supIzq, supDer, infIzq, infDer, hor, ver;

    if (estilo == "doble") {
        supIzq = "╔"; supDer = "╗"; infIzq = "╚"; infDer = "╝";
        hor = "═"; ver = "║";
    } else if (estilo == "simple") {
        supIzq = "+"; supDer = "+"; infIzq = "+"; infDer = "+";
        hor = "-"; ver = "|";
    } else if (estilo == "redondeado") {
        supIzq = "╭"; supDer = "╮"; infIzq = "╰"; infDer = "╯";
        hor = "─"; ver = "│";
    } else {
        supIzq = "┌"; supDer = "┐"; infIzq = "└"; infDer = "┘";
        hor = "─"; ver = "│";
    }

    rlutil::setColor(rlutil::LIGHTCYAN);

    // Línea superior
    rlutil::locate(x, y);
    cout << supIzq;
    for (int i = 0; i < ancho - 2; i++) cout << hor;
    cout << supDer;

    // Líneas laterales
    for (int i = 1; i < alto - 1; i++) {
        rlutil::locate(x, y + i);
        cout << ver;
        rlutil::locate(x + ancho - 1, y + i);
        cout << ver;
    }

    // Línea inferior
    rlutil::locate(x, y + alto - 1);
    cout << infIzq;
    for (int i = 0; i < ancho - 2; i++) cout << hor;
    cout << infDer;

    rlutil::resetColor();
}

void InterfazRetro::dibujarBanner(const string& texto, int y, int color) const{
    int inicioX = (anchoPantalla - anchoVisible(texto) - 4) / 2;
    if (inicioX < 2) inicioX = 2;

    dibujarMarco(inicioX - 2, y - 1, anchoVisible(texto) + 4, 3, "doble");

    rlutil::setColor(color);
    rlutil::locate(inicioX + 2, y);
    cout << texto;
    rlutil::resetColor();
}

void InterfazRetro::dibujarSeparador(int y, const string& caracter) const {
    rlutil::setColor(rlutil::LIGHTCYAN);
    rlutil::locate(0, y);
    for (int i = 0; i < anchoPantalla; i++) {
        cout << caracter;
    }
    rlutil::resetColor();
}

void InterfazRetro::mostrarTituloRetro(const string& titulo, int y) const {
    int inicioX = (anchoPantalla - anchoVisible(titulo)) / 2;
    if (inicioX < 2) inicioX = 2;

    // Sombra
    rlutil::setColor(rlutil::DARKGREY);
    for (int i = 0; i < 2; i++) {
        rlutil::locate(inicioX + i + 1, y + i + 1);
        cout << titulo;
    }
    rlutil::resetColor();

    // Título principal con fondo
    rlutil::setColor(rlutil::YELLOW);
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::locate(inicioX, y);
    cout << titulo;
    rlutil::resetColor();
}

void InterfazRetro::mostrarMenuRetro(const vector<string>& opciones, int seleccion) const{
    int inicioX = 25;
    int inicioY = 8;

    dibujarMarco(inicioX - 3, inicioY - 2, 30, opciones.size() * 2 + 3, "doble");

    for (size_t i = 0; i < opciones.size(); i++) {
        int y = inicioY + i * 2;

        if ((int)i == seleccion) {
            rlutil::setColor(rlutil::YELLOW);
            rlutil::setBackgroundColor(rlutil::BLUE);
            rlutil::locate(inicioX, y);
            cout << "▶ " << opciones[i] << " ◀";
            rlutil::resetColor();
        } else {
            rlutil::setColor(rlutil::WHITE);
            rlutil::locate(inicioX + 2, y);
            cout << opciones[i];
            rlutil::resetColor();
        }
    }
}

void InterfazRetro::mostrarBotonRetro(const string& texto, int x, int y, bool seleccionado) const {
    int ancho = anchoVisible(texto) + 4;

    if (seleccionado) {
        rlutil::setColor(rlutil::YELLOW);
        rlutil::setBackgroundColor(rlutil::BLUE);
    } else {
        rlutil::setColor(rlutil::WHITE);
        rlutil::setBackgroundColor(rlutil::DARKGREY);
    }

    rlutil::locate(x, y);
    cout << "┌";
    for (int i = 0; i < ancho - 2; i++) cout << "─";
    cout << "┐";

    rlutil::locate(x, y + 1);
    cout << "│ " << texto << " │";

    rlutil::locate(x, y + 2);
    cout << "└";
    for (int i = 0; i < ancho - 2; i++) cout << "─";
    cout << "┘";

    rlutil::resetColor();
}

void InterfazRetro::mostrarDadosEnFila(const vector<DadoVisual>& dados, int inicioX, int inicioY, bool mostrarIndices) const {
    if (dados.empty()) {
        rlutil::locate(inicioX, inicioY + 2);
        cout << "Sin dados";
        return;
    }

    // Mostrar cada línea de todos los dados
    for (int fila = 0; fila < 5; fila++) {
        rlutil::locate(inicioX, inicioY + fila);

        for (size_t i = 0; i < dados.size(); i++) {
            rlutil::setColor(rlutil::WHITE);
            rlutil::setBackgroundColor(rlutil::LIGHTBLUE);
            cout << dados[i].getRepresentacion()[fila];
            rlutil::resetColor();

            if (i < dados.size() - 1) {
                cout << "  ";
            }
        }
        cout << endl;
    }

    // Mostrar índices debajo de los dados
    if (mostrarIndices) {
        rlutil::locate(inicioX, inicioY + 6);
        for (size_t i = 0; i < dados.size(); i++) {
            rlutil::setColor(rlutil::BLUE);
            cout << "[" << i + 1 << "]";
            rlutil::resetColor();
            if (i < dados.size() - 1) {
                cout << "   ";
            }
        }
        cout << endl;
    }
}

void InterfazRetro::mostrarDadoUnico(const DadoVisual& dado, int x, int y) const {
    for (int fila = 0; fila < 5; fila++) {
        rlutil::locate(x, y + fila);
        rlutil::setColor(rlutil::WHITE);
        rlutil::setBackgroundColor(rlutil::LIGHTBLUE);
        cout << dado.getRepresentacion()[fila];
        rlutil::resetColor();
        cout << endl;
    }
}

void InterfazRetro::efectoDestello(const string& texto, int x, int y, int repeticiones)const {
    for (int i = 0; i < repeticiones; i++) {
        rlutil::locate(x, y);

        if (i % 2 == 0) {
            rlutil::setColor(rlutil::YELLOW);
            rlutil::setBackgroundColor(rlutil::RED);
        } else {
            rlutil::setColor(rlutil::WHITE);
            rlutil::setBackgroundColor(rlutil::BLUE);
        }

        cout << texto;
        rlutil::resetColor();
        rlutil::msleep(150);
    }
}

void InterfazRetro::efectoEscritura(const string& texto, int x, int y, int velocidad) const{
    rlutil::locate(x, y);
    for (char c : texto) {
        cout << c;
        cout.flush();
        rlutil::msleep(velocidad);
    }
}

void InterfazRetro::transicionPantalla(int frames) const {
    for (int i = 0; i < frames; i++) {
        rlutil::cls();

        // Efecto de "pantalla de carga" retro
        rlutil::setColor(rlutil::LIGHTCYAN);
        rlutil::locate(20, 12);
        cout << "CARGANDO";
        for (int j = 0; j < 3; j++) {
            cout << ".";
            cout.flush();
            rlutil::msleep(200);
        }
        rlutil::resetColor();
        rlutil::msleep(100);
    }
    rlutil::cls();
}

void InterfazRetro::efectoVictoria(const string& nombre) const {
    rlutil::cls();
    dibujarBanner("¡VICTORIA!", 5, rlutil::LIGHTGREEN);

    rlutil::setColor(rlutil::YELLOW);
    rlutil::locate(15, 10);
    efectoEscritura("🏆 " + nombre + " ES EL GANADOR! 🏆", 15, 10, 50);
    rlutil::resetColor();

    // Efecto de confeti
    for (int i = 0; i < 20; i++) {
        rlutil::locate(rand() % 70 + 5, rand() % 10 + 12);
        rlutil::setColor(rand() % 14 + 1);
        cout << "✦";
        rlutil::resetColor();
        rlutil::msleep(100);
    }

    rlutil::anykey("\nPresiona una tecla para continuar...\n");
}

void InterfazRetro::efectoDerrota(const string& nombre) const {
    rlutil::cls();
    dibujarBanner("FIN DE LA PARTIDA", 5, rlutil::LIGHTRED);

    rlutil::setColor(rlutil::RED);
    rlutil::locate(20, 10);
    efectoEscritura("💔 " + nombre + " fue derrotado!", 20, 10, 50);
    rlutil::resetColor();

    rlutil::anykey("\nPresiona una tecla para continuar...\n");
}

void InterfazRetro::dibujarEsquinaDecorativa(int x, int y) const {
    rlutil::setColor(rlutil::LIGHTCYAN);
    rlutil::locate(x, y);
    cout << "◈";
    rlutil::resetColor();
}

void InterfazRetro::mostrarMarcoInfo(const string& info, int x, int y) const {
    dibujarMarco(x, y, anchoVisible(info) + 4, 3, "redondeado");
    rlutil::locate(x + 2, y + 1);
    rlutil::setColor(rlutil::WHITE);
    cout << info;
    rlutil::resetColor();
}

// ==================== IMPLEMENTACIÓN JUGADOR ====================
Jugador::Jugador(const string& nombre) : nombre(nombre), puntaje(0) {}

string Jugador::getNombre() const {
    return nombre;
}

int Jugador::getPuntaje() const {
    return puntaje;
}

int Jugador::getCantidadDadosStock() const {
    return dadosStock.size();
}

int Jugador::getCantidadDadosElegidos() const {
    return dadosElegidos.size();
}

vector<DadoVisual> Jugador::getDadosElegidos() const {
    return dadosElegidos;
}

vector<int> Jugador::getIndicesElegidos() const {
    return indicesElegidos;
}

DadoVisual Jugador::getDadoStockAt(int index) const {
    if (index >= 0 && index < (int)dadosStock.size()) {
        return dadosStock[index];
    }
    return DadoVisual();
}

void Jugador::setNombre(const string& nuevoNombre) {
    nombre = nuevoNombre;
}

void Jugador::agregarPuntaje(int puntos) {
    puntaje += puntos;
}

void Jugador::generarDadosStock(int cantidad) {
    dadosStock.clear();
    for (int i = 0; i < cantidad; i++) {
        DadoVisual dado;
        dado.tirar();
        dadosStock.push_back(dado);
    }
}

void Jugador::limpiarDadosStock() {
    dadosStock.clear();
}

void Jugador::limpiarDadosElegidos() {
    dadosElegidos.clear();
    indicesElegidos.clear();
}

void Jugador::resetearJugador() {
    puntaje = 0;
    dadosStock.clear();
    dadosElegidos.clear();
    indicesElegidos.clear();
}

void Jugador::mostrarDadosStock(int posX, int posY) const {
    if (posX > 0 || posY > 0) {
        rlutil::locate(posX, posY);
    }

    if (dadosStock.empty()) {
        cout << "Sin dados";
        return;
    }

    // Usar la interfaz para mostrar dados visuales
    InterfazRetro tempInterfaz;
    tempInterfaz.mostrarDadosEnFila(dadosStock, posX, posY, true);
}

void Jugador::mostrarDadosElegidos(int posX, int posY) const {
    if (posX > 0 || posY > 0) {
        rlutil::locate(posX, posY);
    }

    if (dadosElegidos.empty()) {
        cout << "No has seleccionado dados";
        return;
    }

    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "Combinación: ";
    int total = sumarDadosElegidos();

    for (size_t i = 0; i < dadosElegidos.size(); i++) {
        rlutil::setColor(rlutil::LIGHTGREEN);
        cout << dadosElegidos[i].getValor();
        rlutil::resetColor();
        if (i < dadosElegidos.size() - 1) {
            cout << " + ";
        } else {
            cout << " = ";
        }
    }
    rlutil::setColor(rlutil::WHITE);
    cout << total;
    rlutil::resetColor();
}

void Jugador::mostrarDadosObjetivo(int objetivo, int posX, int posY) const {
    if (posX > 0 || posY > 0) {
        rlutil::locate(posX, posY);
    }

    rlutil::setColor(rlutil::LIGHTMAGENTA);
    cout << "🎯 OBJETIVO: ";
    rlutil::setColor(rlutil::YELLOW);
    cout << objetivo;
    rlutil::resetColor();
}

bool Jugador::elegirDados(InterfazRetro& interfaz) {
    dadosElegidos.clear();
    indicesElegidos.clear();
    vector<bool> indicesUsados(dadosStock.size(), false);

    while (true) {
        rlutil::cls();

        // Título
        interfaz.dibujarBanner("SELECCIÓN DE DADOS", 2, rlutil::LIGHTCYAN);

        // Mostrar dados stock visualmente
        cout << endl;
        cout << "TUS DADOS STOCK:" << endl;
        mostrarDadosStock(10, 6);
        cout << endl << endl;

        // Mostrar dados elegidos
        if (!dadosElegidos.empty()) {
            cout << "DADOS SELECCIONADOS:" << endl;
            mostrarDadosElegidos(10, 14);
            cout << endl;
        }

        // Opciones
        cout << endl;
        interfaz.dibujarSeparador(18, "─");
        rlutil::setColor(rlutil::YELLOW);
        cout << "Elige un dado (ingresa el número) o 0 para terminar: ";
        rlutil::resetColor();

        int opcion;
        cin >> opcion;

        if (opcion == 0) {
            break;
        }

        // Validar entrada
        if (opcion < 1 || opcion > (int)dadosStock.size()) {
            rlutil::setColor(rlutil::RED);
            cout << "❌ ¡Número inválido! Elige entre 1 y " << dadosStock.size() << endl;
            rlutil::resetColor();
            rlutil::anykey("\nPresiona una tecla para continuar...\n");
            continue;
        }

        // Verificar si ya fue usado
        if (indicesUsados[opcion - 1]) {
            rlutil::setColor(rlutil::RED);
            cout << "❌ ¡Este dado ya fue seleccionado! Elige otro." << endl;
            rlutil::resetColor();
            rlutil::anykey("\nPresiona una tecla para continuar...\n");
            continue;
        }

        // Seleccionar dado
        indicesUsados[opcion - 1] = true;
        dadosElegidos.push_back(dadosStock[opcion - 1]);
        indicesElegidos.push_back(opcion - 1);

        rlutil::setColor(rlutil::GREEN);
        cout << "✅ ¡Dado seleccionado correctamente!" << endl;
        rlutil::resetColor();
        rlutil::anykey("\nPresiona una tecla para continuar...\n");
    }

    return !dadosElegidos.empty();
}

int Jugador::sumarDadosElegidos() const {
    int total = 0;
    for (const DadoVisual& dado : dadosElegidos) {
        total += dado.getValor();
    }
    return total;
}

void Jugador::transferirDados(Jugador& otro, int cantidad) {
    if (cantidad <= 0 || dadosStock.empty()) return;

    int transferir = min(cantidad, (int)dadosStock.size());
    for (int i = 0; i < transferir; i++) {
        if (!dadosStock.empty()) {
            DadoVisual dado = dadosStock.back();
            otro.dadosStock.push_back(dado);
            dadosStock.pop_back();
        }
    }
}

void Jugador::agregarDadoStock(const DadoVisual& dado) {
    dadosStock.push_back(dado);
}

bool Jugador::tieneDados() const {
    return !dadosStock.empty();
}

bool Jugador::operator<(const Jugador& otro) const {
    return puntaje < otro.puntaje;
}

// ==================== IMPLEMENTACIÓN JUEGO RETRO ====================
JuegoRetro::JuegoRetro() : rondaActual(0), recordPuntaje(0),
                           nombreRecord("Nadie"), juegoTerminado(false),
                           victoriaAutomatica(false) {
    srand(time(nullptr));
}

void JuegoRetro::mostrarTitulo(){
    rlutil::cls();

    interfaz.dibujarMarco(5, 2, 70, 10, "doble");
    interfaz.mostrarTituloRetro("DICE BATTLE RETRO", 5);

    // Dados decorativos
    DadoVisual d1, d2;
    d1.setValor(6);
    d2.setValor(6);

    interfaz.mostrarDadoUnico(d1, 10, 8);
    interfaz.mostrarDadoUnico(d2, 55, 8);

    rlutil::setColor(rlutil::LIGHTCYAN);
    rlutil::locate(20, 15);
    cout << "Presiona cualquier tecla para continuar...";
    rlutil::resetColor();

    rlutil::anykey("\nPresiona una tecla para continuar...\n");
    rlutil::cls();
}

void JuegoRetro::determinarQuienEmpieza() {
    rlutil::cls();

    interfaz.dibujarBanner("TIRO DE PRUEBA", 2, rlutil::YELLOW);

    rlutil::locate(15, 6);
    cout << jugador1.getNombre() << " lanza su dado...";
    rlutil::anykey("\nPresiona una tecla para continuar...\n");

    DadoVisual dado1;
    int tiro1 = dado1.tirar();

    rlutil::locate(15, 8);
    interfaz.mostrarDadoUnico(dado1, 15, 10);
    rlutil::locate(15, 16);
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "🎲 " << jugador1.getNombre() << " obtuvo: " << tiro1;
    rlutil::resetColor();
    rlutil::anykey("\nPresiona una tecla para continuar...\n");

    rlutil::cls();
    interfaz.dibujarBanner("TIRO DE PRUEBA", 2, rlutil::YELLOW);

    rlutil::locate(15, 6);
    cout << jugador2.getNombre() << " lanza su dado...";
    rlutil::anykey("\nPresiona una tecla para continuar...\n");

    DadoVisual dado2;
    int tiro2 = dado2.tirar();

    rlutil::locate(15, 8);
    interfaz.mostrarDadoUnico(dado2, 15, 10);
    rlutil::locate(15, 16);
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "🎲 " << jugador2.getNombre() << " obtuvo: " << tiro2;
    rlutil::resetColor();
    rlutil::anykey("\nPresiona una tecla para continuar...\n");

    if (tiro1 == tiro2) {
        rlutil::cls();
        interfaz.dibujarBanner("¡EMPATE!", 3, rlutil::YELLOW);
        rlutil::locate(20, 8);
        cout << "Se lanzarán de nuevo...";
        rlutil::anykey("\nPresiona una tecla para continuar...\n");
        determinarQuienEmpieza();
        return;
    }

    if (tiro1 > tiro2) {
        jugadorActivo = &jugador1;
        jugadorRival = &jugador2;
    } else {
        jugadorActivo = &jugador2;
        jugadorRival = &jugador1;
    }

    rlutil::cls();
    interfaz.efectoVictoria(jugadorActivo->getNombre());
    rlutil::locate(15, 18);
    rlutil::setColor(rlutil::LIGHTCYAN);
    cout << "🎯 " << jugadorActivo->getNombre() << " comenzará la partida!";
    rlutil::resetColor();
    rlutil::anykey("\nPresiona una tecla para continuar...\n");
}

int JuegoRetro::generarObjetivo() const {
    DadoVisual dadoObjetivo(CARAS_DADO_OBJETIVO);
    int dado1 = dadoObjetivo.tirar();
    int dado2 = dadoObjetivo.tirar();
    return dado1 + dado2;
}

void JuegoRetro::procesarTirada(int objetivo) {
    int sumaElegidos = jugadorActivo->sumarDadosElegidos();
    int cantidadElegidos = jugadorActivo->getCantidadDadosElegidos();

    rlutil::cls();

    interfaz.dibujarBanner("RESULTADO DE LA TIRADA", 2, rlutil::LIGHTCYAN);

    // Mostrar información
    rlutil::locate(15, 6);
    rlutil::setColor(rlutil::YELLOW);
    cout << "RONDA " << rondaActual << " - " << jugadorActivo->getNombre();
    rlutil::resetColor();

    jugadorActivo->mostrarDadosObjetivo(objetivo, 15, 8);
    cout << endl << endl;

    // Mostrar dados elegidos visualmente
    if (!jugadorActivo->getDadosElegidos().empty()) {
        rlutil::locate(15, 11);
        cout << "DADOS ELEGIDOS:" << endl;
        interfaz.mostrarDadosEnFila(jugadorActivo->getDadosElegidos(), 15, 13);
    }

    // Verificar tirada
    if (sumaElegidos == objetivo && cantidadElegidos > 0) {
        int puntos = objetivo * cantidadElegidos;
        jugadorActivo->agregarPuntaje(puntos);

        rlutil::locate(15, 20);
        interfaz.efectoDestello("✅ ¡TIRADA EXITOSA! +" + to_string(puntos) + " pts", 15, 20, 3);

        jugadorActivo->transferirDados(*jugadorRival, cantidadElegidos);
    } else {
        rlutil::locate(15, 20);
        interfaz.efectoDestello("❌ TIRADA FALLIDA - 0 pts", 15, 20, 2);

        if (jugadorRival->getCantidadDadosStock() > 0) {
            jugadorRival->transferirDados(*jugadorActivo, 1);
        }
    }

    // Mostrar estado actual
    rlutil::locate(2, 24);
    interfaz.dibujarSeparador(24, "─");
    rlutil::locate(2, 25);
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << jugadorActivo->getNombre() << ": " << jugadorActivo->getPuntaje() << " pts | "
         << jugadorActivo->getCantidadDadosStock() << " dados";
    rlutil::locate(45, 25);
    cout << jugadorRival->getNombre() << ": " << jugadorRival->getPuntaje() << " pts | "
         << jugadorRival->getCantidadDadosStock() << " dados";
    rlutil::resetColor();

    rlutil::anykey("\nPresiona una tecla para continuar...\n");
}

void JuegoRetro::mostrarEstadoRonda(int objetivo) const {
    rlutil::cls();

    interfaz.dibujarBanner("RONDA " + to_string(rondaActual), 2, rlutil::LIGHTCYAN);

    rlutil::locate(15, 6);
    rlutil::setColor(rlutil::YELLOW);
    cout << "Turno de " << jugadorActivo->getNombre();
    rlutil::resetColor();
    cout << endl << endl;

    jugadorActivo->mostrarDadosObjetivo(objetivo, 15, 9);
    cout << endl << endl;

    rlutil::locate(15, 12);
    cout << "TUS DADOS STOCK:" << endl;
    jugadorActivo->mostrarDadosStock(15, 14);
}

bool JuegoRetro::verificarVictoriaAutomatica() {
    if (jugador1.getCantidadDadosStock() == 0) {
        jugador1.agregarPuntaje(PUNTOS_VICTORIA_AUTO);
        rlutil::cls();
        interfaz.efectoVictoria(jugador1.getNombre());
        victoriaAutomatica = true;
        juegoTerminado = true;
        return true;
    }

    if (jugador2.getCantidadDadosStock() == 0) {
        jugador2.agregarPuntaje(PUNTOS_VICTORIA_AUTO);
        rlutil::cls();
        interfaz.efectoVictoria(jugador2.getNombre());
        victoriaAutomatica = true;
        juegoTerminado = true;
        return true;
    }

    return false;
}

void JuegoRetro::actualizarRecord() {
    string nombreGanador;
    int puntajeGanador;

    if (jugador1.getPuntaje() > jugador2.getPuntaje()) {
        nombreGanador = jugador1.getNombre();
        puntajeGanador = jugador1.getPuntaje();
    } else if (jugador2.getPuntaje() > jugador1.getPuntaje()) {
        nombreGanador = jugador2.getNombre();
        puntajeGanador = jugador2.getPuntaje();
    } else {
        if (jugador1.getCantidadDadosStock() <= jugador2.getCantidadDadosStock()) {
            nombreGanador = jugador1.getNombre();
            puntajeGanador = jugador1.getPuntaje();
        } else {
            nombreGanador = jugador2.getNombre();
            puntajeGanador = jugador2.getPuntaje();
        }
    }

    if (puntajeGanador > recordPuntaje) {
        recordPuntaje = puntajeGanador;
        nombreRecord = nombreGanador;
    }
}

void JuegoRetro::mostrarResultadosFinales() {
    rlutil::cls();

    if (victoriaAutomatica) {
        interfaz.dibujarBanner("¡VICTORIA AUTOMÁTICA!", 2, rlutil::LIGHTGREEN);
    } else {
        interfaz.dibujarBanner("RESULTADOS FINALES", 2, rlutil::LIGHTCYAN);
    }

    // Mostrar dados de cada jugador
    rlutil::locate(5, 6);
    rlutil::setColor(rlutil::YELLOW);
    cout << jugador1.getNombre();
    rlutil::resetColor();
    jugador1.mostrarDadosStock(5, 8);

    rlutil::locate(45, 6);
    rlutil::setColor(rlutil::YELLOW);
    cout << jugador2.getNombre();
    rlutil::resetColor();
    jugador2.mostrarDadosStock(45, 8);

    // Mostrar puntajes
    rlutil::locate(5, 16);
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "⭐ Puntos: " << jugador1.getPuntaje();
    rlutil::locate(45, 16);
    cout << "⭐ Puntos: " << jugador2.getPuntaje();
    rlutil::resetColor();

    // Ganador
    rlutil::locate(5, 18);
    if (jugador1.getPuntaje() > jugador2.getPuntaje()) {
        interfaz.efectoDestello("🏆 " + jugador1.getNombre() + " ES EL GANADOR!", 10, 20, 5);
    } else if (jugador2.getPuntaje() > jugador1.getPuntaje()) {
        interfaz.efectoDestello("🏆 " + jugador2.getNombre() + " ES EL GANADOR!", 10, 20, 5);
    } else {
        interfaz.efectoDestello("¡EMPATE!", 20, 20, 3);
    }

    actualizarRecord();

    rlutil::locate(10, 23);
    rlutil::setColor(rlutil::CYAN);
    cout << "RECORD: " << nombreRecord << " - " << recordPuntaje << " pts";
    rlutil::resetColor();

    rlutil::anykey("\nPresiona una tecla para continuar...\n");
}

void JuegoRetro::mostrarEstadisticas() const {
    rlutil::cls();
    interfaz.dibujarBanner("ESTADÍSTICAS", 2, rlutil::LIGHTCYAN);

    rlutil::locate(20, 8);
    rlutil::setColor(rlutil::YELLOW);
    cout << "🏆 RECORD DE PUNTAJE";
    rlutil::resetColor();

    rlutil::locate(20, 10);
    cout << "Jugador: " << nombreRecord;

    rlutil::locate(20, 11);
    cout << "Puntaje: " << recordPuntaje;

    rlutil::anykey("\nPresiona una tecla para continuar...\n");
}

void JuegoRetro::mostrarCreditos() {
    rlutil::cls();
    interfaz.dibujarBanner("CRÉDITOS", 2, rlutil::LIGHTCYAN);

    rlutil::locate(20, 8);
    rlutil::setColor(rlutil::YELLOW);
    cout << "DICE BATTLE RETRO v2.0";
    rlutil::resetColor();

    rlutil::locate(20, 10);
    cout << "🎲 Dados con Arte ASCII";

    rlutil::locate(20, 11);
    cout << "🎨 Interfaz Estilo SNES";

    rlutil::locate(20, 12);
    cout << "💻 Programación Orientada a Objetos";

    rlutil::locate(20, 14);
    rlutil::setColor(rlutil::CYAN);
    cout << "¡Diviértete jugando!";
    rlutil::resetColor();

    rlutil::anykey("\nPresiona una tecla para continuar...\n");
}

void JuegoRetro::iniciar() {
    rlutil::cls();
    mostrarTitulo();

    // Resetear estado
    jugador1.resetearJugador();
    jugador2.resetearJugador();
    juegoTerminado = false;
    victoriaAutomatica = false;
    rondaActual = 0;

    // Solicitar nombres
    interfaz.dibujarBanner("NUEVA PARTIDA", 2, rlutil::YELLOW);

    rlutil::locate(20, 6);
    cout << "Ingresa el nombre del Jugador 1: ";
    string nombre1;
    cin >> nombre1;
    jugador1.setNombre(nombre1);

    rlutil::locate(20, 7);
    cout << "Ingresa el nombre del Jugador 2: ";
    string nombre2;
    cin >> nombre2;
    jugador2.setNombre(nombre2);

    // Inicializar dados
    jugador1.generarDadosStock(DADOS_INICIALES);
    jugador2.generarDadosStock(DADOS_INICIALES);

    // Determinar quién empieza
    determinarQuienEmpieza();

    // Jugar rondas
    while (rondaActual < MAX_RONDAS && !juegoTerminado) {
        rondaActual++;
        int objetivo = generarObjetivo();

        jugadorActivo->limpiarDadosElegidos();
        mostrarEstadoRonda(objetivo);

        cout << endl << "Presiona cualquier tecla para elegir tus dados..." << endl;
        rlutil::anykey("\nPresiona una tecla para continuar...\n");

        if (!jugadorActivo->elegirDados(interfaz)) {
            rlutil::cls();
            interfaz.efectoDestello("⚠️ No seleccionaste dados. Turno perdido.", 15, 10, 2);
            rlutil::anykey("\nPresiona una tecla para continuar...\n");
        } else {
            procesarTirada(objetivo);
        }

        if (verificarVictoriaAutomatica()) {
            break;
        }

        // Intercambiar turnos
        swap(jugadorActivo, jugadorRival);

        // Regenerar dados
        jugadorActivo->limpiarDadosElegidos();
        jugadorRival->limpiarDadosElegidos();
        jugadorActivo->generarDadosStock(jugadorActivo->getCantidadDadosStock());
        jugadorRival->generarDadosStock(jugadorRival->getCantidadDadosStock());
    }

    mostrarResultadosFinales();
}

bool JuegoRetro::estaTerminado() const {
    return juegoTerminado;
}

void JuegoRetro::mostrarMenu() {
    vector<string> opciones = {
        "INICIAR PARTIDA",
        "ESTADÍSTICAS",
        "CRÉDITOS",
        "SALIR"
    };

    int seleccion = 0;
    bool salir = false;

    while (!salir) {
        rlutil::cls();

        // Título
        interfaz.dibujarMarco(15, 1, 60, 5, "doble");
        interfaz.mostrarTituloRetro("DICE BATTLE RETRO", 3);

        // Menú
        interfaz.mostrarMenuRetro(opciones, seleccion);

        // Controles
        interfaz.dibujarSeparador(22, "─");
        rlutil::locate(25, 23);
        rlutil::setColor(rlutil::DARKGREY);
        cout << "↑/↓: Navegar  Enter: Seleccionar  ESC: Salir";
        rlutil::resetColor();

        // Leer entrada
        int key = rlutil::getkey();

        switch(key) {
            case rlutil::KEY_UP:
                seleccion = (seleccion - 1 + opciones.size()) % opciones.size();
                break;
            case rlutil::KEY_DOWN:
                seleccion = (seleccion + 1) % opciones.size();
                break;
            case rlutil::KEY_ENTER:
                switch(seleccion) {
                    case 0:
                        interfaz.transicionPantalla(3);
                        iniciar();
                        break;
                    case 1:
                        mostrarEstadisticas();
                        break;
                    case 2:
                        mostrarCreditos();
                        break;
                    case 3:
                        salir = true;
                        break;
                }
                break;
            case 27: // ESC
                salir = true;
                break;
        }
    }
}
