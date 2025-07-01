#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <iostream>
#include <ctime>
#include <vector>
#include "rlutil.h"
using namespace std;
void mostrarDadosStock(vector<int> vector);
vector<int> asignarDadosStock(vector<int>& vector1, int n);
void MostrarTitulo();
void MostrarMenu(string& jugador1, string& jugador2);
string PreguntoNombreJugador1();
string PreguntoNombreJugador2();
int TirarDado6caras();
int TirarDado12caras();
void Rondas(string& jugador1, string& jugador2, int n, int &puntaje1, int &puntaje2);
bool mismoDado(vector<int> vector, int j);
void elegirDados ( vector <int> dadostockjugador1);
int sumaVector(vector<int> vector);
void mostrarElegidos(vector<int> vector);
bool tiradaExitosa(vector<int> vector, int k);
int cantDadoseElegidos(vector<int> vector);
void modDadosStock(int &cantDadosStock1,int &cantDadosStock2, int dadosElegidos, bool tiradaExitosa);
void victoriaAutomatica(int dados, int puntaje, bool j);

#endif // FUNCIONES_H_INCLUDED
