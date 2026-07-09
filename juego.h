#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include "rlutil.h"

using namespace std;

// Constantes del juego
const int DADOS_INICIALES = 6;
const int MAX_RONDAS = 3;
const int PUNTOS_VICTORIA_AUTO = 10000;
const int CARAS_DADO = 6;
const int CARAS_DADO_OBJETIVO = 12;

// ==================== CLASE DADO VISUAL ====================
class DadoVisual {
private:
    int valor;
    int caras;
    vector<string> representacion;

public:
    DadoVisual(int caras = CARAS_DADO);
    int tirar();
    int getValor() const;
    void setValor(int nuevoValor);
    vector<string> getRepresentacion() const;
    void generarRepresentacion(int valor);
};

// ==================== CLASE INTERFAZ RETRO ====================
class InterfazRetro {
private:
    int anchoPantalla;
    int altoPantalla;

public:
    InterfazRetro();

    // Estilos de marco
    void dibujarMarco(int x, int y, int ancho, int alto, const string& estilo = "doble") const;
    void dibujarBanner(const string& texto, int y, int color = rlutil::LIGHTCYAN) const;
    void dibujarSeparador(int y, const string& caracter = "═") const;

    // Elementos de interfaz
    void mostrarTituloRetro(const string& titulo, int y = 2) const;
    void mostrarMenuRetro(const vector<string>& opciones, int seleccion = 0) const;
    void mostrarBotonRetro(const string& texto, int x, int y, bool seleccionado = false) const;
    void mostrarDadosEnFila(const vector<DadoVisual>& dados, int inicioX, int inicioY, bool mostrarIndices = false) const;
    void mostrarDadoUnico(const DadoVisual& dado, int x, int y) const;

    // Efectos visuales
    void efectoDestello(const string& texto, int x, int y, int repeticiones = 3) const;
    void efectoEscritura(const string& texto, int x, int y, int velocidad = 30) const;
    void transicionPantalla(int frames = 10) const;
    void efectoVictoria(const string& nombre) const;
    void efectoDerrota(const string& nombre) const;

    // Decoraciones
    void dibujarEsquinaDecorativa(int x, int y) const;
    void mostrarMarcoInfo(const string& info, int x, int y) const;
};

// ==================== CLASE JUGADOR ====================
class Jugador {
private:
    string nombre;
    int puntaje;
    vector<DadoVisual> dadosStock;
    vector<DadoVisual> dadosElegidos;
    vector<int> indicesElegidos;

public:
    Jugador(const string& nombre = "");

    // Getters
    string getNombre() const;
    int getPuntaje() const;
    int getCantidadDadosStock() const;
    int getCantidadDadosElegidos() const;
    vector<DadoVisual> getDadosElegidos() const;
    vector<int> getIndicesElegidos() const;
    DadoVisual getDadoStockAt(int index) const;

    // Setters y modificadores
    void setNombre(const string& nuevoNombre);
    void agregarPuntaje(int puntos);
    void generarDadosStock(int cantidad);
    void limpiarDadosStock();
    void limpiarDadosElegidos();
    void resetearJugador();

    // Métodos de juego
    void mostrarDadosStock(int posX = 0, int posY = 0) const;
    void mostrarDadosElegidos(int posX = 0, int posY = 0) const;
    void mostrarDadosObjetivo(int objetivo, int posX = 0, int posY = 0) const;
    bool elegirDados(InterfazRetro& interfaz);
    int sumarDadosElegidos() const;
    void transferirDados(Jugador& otro, int cantidad);
    void agregarDadoStock(const DadoVisual& dado);
    bool tieneDados() const;

    // Operadores
    bool operator<(const Jugador& otro) const;
};

// ==================== CLASE JUEGO RETRO ====================
class JuegoRetro {
private:
    InterfazRetro interfaz;
    Jugador jugador1;
    Jugador jugador2;
    Jugador* jugadorActivo;
    Jugador* jugadorRival;
    int rondaActual;
    int recordPuntaje;
    string nombreRecord;
    bool juegoTerminado;
    bool victoriaAutomatica;

    // Métodos privados
    void determinarQuienEmpieza();
    int generarObjetivo() const;
    void procesarTirada(int objetivo);
    void mostrarEstadoRonda(int objetivo) const;
    void mostrarResultadosFinales();
    bool verificarVictoriaAutomatica();
    void actualizarRecord();
    void mostrarCreditos();

public:
    JuegoRetro();

    // Métodos principales
    void iniciar();
    bool estaTerminado() const;

    // Estadísticas
    void mostrarEstadisticas() const;
    void mostrarTitulo();

    // Menú principal
    void mostrarMenu();
};

#endif // JUEGO_H_INCLUDED
