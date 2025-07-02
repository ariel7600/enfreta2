#include <iostream>
#include <ctime>
#include <vector>
#include "rlutil.h"
using namespace std;

//Defino variables
string ganador, perdedor;
vector<int> dadostockjugador1;
vector<int> dadostockjugador2;
vector <int> dadosElegidos={};
int cantDadosStock1=6;
int cantDadosStock2=6;
int mayor=0;
string record="Nadie";

//tirada de dados de 6 caras
int TirarDado6caras(){
    return rand() % 6 + 1;
}
//tirada de dados de 12 caras
int TirarDado12caras (){
    return rand() % 12 + 1;
}
//Asigno nombre a jugador 1
string PreguntoNombreJugador1 (){

  string jugador1;
  cout<< "Ingresar el nombre del jugador 1: "<<endl;
  cout << endl;
  cin>> jugador1;
  cout << "¡Bienvenido/a " << jugador1 << "!"<<endl;
  system("pause");
  system ("cls");

  return jugador1;
}
//Asigno nombre a jugador 2
string PreguntoNombreJugador2 (){

  string jugador2;
  cout<< "Ingresar el nombre del jugador 2: "<<endl;
  cout << endl;
  cin>> jugador2;
  cout << "¡Bienvenido/a " << jugador2 << "!"<<endl;
  system("pause");
  system ("cls");

  return jugador2;
}
// asignar dados stock
vector<int> asignarDadosStock(vector<int>& vector1, int b){
    for (int i=0; i<b; i++){
        vector1.push_back(TirarDado6caras());
        //vector1[i] = TirarDado6caras();
        }
        return vector1;
}
// se activa en caso de victoria automatica
void victoriaAutomatica(int &dados, int &puntaje, bool j){
    if(dados==0 && j){
        system ("cls");
        puntaje+=10000;
        cout<<"Victoria!!"<<endl;
        cout<<"Ganaste automaticamente tras quedarte sin dados stock!!"<<endl;
        cout<<endl;
        system("pause");
    }

}
//muestro en pantalla dados stock
void mostrarDadosStock(vector<int> vector){
    cout<<"[";
    for(int i=0; i<vector.size();i++){
        if(i==vector.size()-1){
            cout<<vector[i]<<"]";
            break;
        }else{
        cout << vector[i] << " - ";
        }
    }
    cout<<endl;
    cout<<"Dado nUM:     ";
    for(int i=0; i<vector.size();i++){
     cout << i+1<<"  ";
     if(i<vector.size()-1){
        cout<<" ";
     }
    }
}

//chequeo si ya eligio mismo dado stock antes
bool mismoDado(vector<int> vector, int j){
    bool repetido=false;
    for(int i=0;i<vector.size();i++){
        if(vector[i]==j){
            repetido=true;
        }
    }
    return repetido;
}
//jugador elige dados stock a utilizar
void elegirDados ( vector <int> dadostockjugador1){
     int j, k=0;
     vector<int> numElegido(11);
     for (int i=0;i<70;i++){
        cout<<"Elija uno de sus dados stock (Para finalizar presione 0):"<<endl;
        cin>>j;

        if(j==0){
            break;
        }
        //no se puede elegir el mismo dado mas de una vez
        if(k>1){
            if(mismoDado(numElegido, j)){
            cout<<"Dado ya elegido, por favor elegir uno distinto";
            continue;
            }
        }
        //no se puede elegir un valor mayor a la cantidad de dados stock
        if(j > dadostockjugador1.size()){
            cout<<"Valor ingresado no válido"<<endl;
            continue;
        }
        numElegido[k]=j;
        dadosElegidos.push_back(dadostockjugador1[j-1]);
        k++;
    }
}
//sumo elementos de un vector
int sumaVector(vector<int> vector){
    int total=0;
    for(int i=0;i<vector.size();i++){
        total=total+vector[i];
    }
    return total;
}
//muestra los dados stock elegidos en patnalla
void mostrarElegidos(vector<int> vector){
    cout<<"Combinación elegida: ";

    for (int i=0;i<vector.size();i++){
        if(vector.size()==1){
        break;
        }
        if(i==vector.size()-1){
                cout<<vector[i]<<"=";
                break;
            }
        cout<<vector[i]<<"+";
    }
    cout<<sumaVector(vector)<<endl;
}
// chequeo si es tirada exitosa
bool tiradaExitosa(vector<int> vector, int k){
    int total=sumaVector(vector);
    bool exito=false;
    if(total == k){
        exito=true;
    }
    return exito;
}
//modifico las cantidades de dados stock luego de una jugada
void modDadosStock(int &cantDadosStock1,int &cantDadosStock2, int dadosElegidos, bool tiradaExitosa, vector<int> b) {
    if(b == dadostockjugador1){
        if (tiradaExitosa) {
            cantDadosStock1 = cantDadosStock1 - dadosElegidos;
            cantDadosStock2 = cantDadosStock2 + dadosElegidos;
        } else {
            cantDadosStock1 += 1;
            cantDadosStock2 -= 1;
        }
    } else {
        if (tiradaExitosa) {
            cantDadosStock2 = cantDadosStock2 - dadosElegidos;
            cantDadosStock1 = cantDadosStock1 + dadosElegidos;
        } else {
            cantDadosStock2 += 1;
            cantDadosStock1 -= 1;
        }
    }
}
//muestra titulo
void MostrarTitulo() {
    cout<<endl<<
"     _______   ____________  _______   ______  ___    ____  ____  _____"<<endl<<
"    /____ / |  // ____/ __ \/ ____/ | / / __ \/   |  / __ \/ __ \/ ___ "<<endl<<
"   / __/ /  |/ / /_  / /_/ / __/ /  |/ / / / / /| | / / / / / / /\__ \ "<<endl<<
"  / /___/ /|  / __/ / _  _/ /___/ /|  / /_/ / ___ |/ /_/ / /_/ /___/ /"<<endl<<
" /_____/_/ |_/_/   /_/ |_/_____/_/ |_/_____/_/  |_/_____/\____//____/"<<endl<<endl;

cout<<endl<<
system ("pause");
system ("cls");
}
//puntaje record
void mayorPuntaje(int &mayor, int puntaje, string jugador, string &record){
    if (puntaje > mayor){
        mayor = puntaje;
        record=jugador;
    }
}

//lanzamiento de dados de cada jugador por ronda
void Rondas(string& jugador1, string& jugador2, int n, int &puntaje1, int &puntaje2){
    int dadosobjetivostotal, dadosobjetivojugador1[2];
    system ("cls");
    cout << "RONDA " << n<< endl;
    cout << endl;
    cout << "Lanza sus dados " << ganador;
    cout << endl << endl;
    system ("pause");
    system ("cls");
    //asigno valores a los dados objetivos
    for (int i=0; i<2 ; i++){
      dadosobjetivojugador1[i] = TirarDado12caras();
    }
    //valor del numero objetivo
    dadosobjetivostotal =  dadosobjetivojugador1[0] + dadosobjetivojugador1[1];
    cout << "RONDA " << n<< endl;
    cout << endl;
    cout << "Turno de " << ganador;
    cout << endl;
    cout << "Dados objetivos: " << dadosobjetivojugador1[0] << " y " << dadosobjetivojugador1[1] << " = " << dadosobjetivostotal;
    cout << endl;
    cout<<endl;
    cout << "Dados stock: ";
    //asigno valores a los dados stock
    asignarDadosStock(dadostockjugador1, cantDadosStock1);
    //los muestro en pantalla
    mostrarDadosStock(dadostockjugador1);
    cout << endl;
    cout << endl;
    cout << "A continuación seleccionar los dados deseados";
    cout << endl;
    cout << endl;
    //jugador elige dados stock
    elegirDados(dadostockjugador1);
    system ("pause");
    system ("cls");
    cout << "RONDA " << n<< endl;
    cout << endl;
    cout << "Turno de " << ganador;
    cout << endl;
    cout << "Dados objetivos: " << dadosobjetivojugador1[0] << " y " << dadosobjetivojugador1[1] << " = " << dadosobjetivostotal;
    cout << endl;
    cout<<endl;
    cout << "Dados stock: ";
    mostrarDadosStock(dadostockjugador1);
    cout << endl;
    cout << endl;
    mostrarElegidos(dadosElegidos);
    //chequeo si fue tirada exitosa o no
    bool exito=tiradaExitosa(dadosElegidos, dadosobjetivostotal);
    if(exito){
        cout<<"Tirada exitosa!"<<endl;
        cout<<endl;
        cout<<"Dados elegidos: "<<dadosElegidos.size()<<" dados."<<endl;
        cout<<endl;
        cout<<"Puntos: "<<dadosobjetivostotal<<"x"<<dadosElegidos.size()<<"="<<dadosElegidos.size()*dadosobjetivostotal<<endl;
        cout<<endl;
        cout<<"Transfiere a "<<perdedor<<" "<<dadosElegidos.size()<<" dados."<<endl;
        cout<<endl;
        puntaje1=puntaje1+dadosElegidos.size()*dadosobjetivostotal;
        modDadosStock(cantDadosStock1,cantDadosStock2, dadosElegidos.size(), exito, dadostockjugador1);
        victoriaAutomatica(cantDadosStock1, puntaje1, exito);
        cout<<ganador<<" "<<cantDadosStock1<<" dados y "<< puntaje1<<"pts."<<endl;
        cout<<endl;
        cout<<perdedor<<" "<<cantDadosStock2<<" dados y "<< puntaje2<<"pts."<<endl;
    } else{
        modDadosStock(cantDadosStock1,cantDadosStock2, dadosElegidos.size(), exito, dadostockjugador1);
        victoriaAutomatica(cantDadosStock2, puntaje2, exito);
        cout<<"No fue una tirada exitosa"<<endl;
        cout<<endl;
        cout<<"Puntos obtenidos:0 "<<endl;
        cout<<endl;
        cout<<"Se te transfieren 1 dado extra de "<<perdedor<<"."<<endl;
        cout<<endl;
        cout<<ganador<<" "<<cantDadosStock1<<" dados y "<< puntaje1<<"pts."<<endl;
        cout<<endl;
        cout<<perdedor<<" "<<cantDadosStock2<<" dados y "<< puntaje2<<"pts."<<endl;
        cout<<endl;
    }
    system ("pause");
    system ("cls");
    //reseteo dados stock y elegidos
    dadostockjugador1.clear();
    dadosElegidos.clear();
    //si el jugador que arranca la ronda ya no tiene dados entonces el juego termina -VER me parece que con vitoria automatica alcanza
    if(cantDadosStock1==0 || puntaje1>9999){
        return;
        system("cls");
    } else{
        int dadosobjetivostotal2=0, dadosobjetivojugador2[2];
        cout << "RONDA " << n<< endl;
        cout << endl;
        cout << "Lanza sus dados " << perdedor;
        cout << endl << endl;
        system ("pause");
        system ("cls");
        for (int i=0; i<2; i++){
            dadosobjetivojugador2[i] = TirarDado12caras();
        }
        //valor del numero objetivo
        dadosobjetivostotal2 =  dadosobjetivojugador2[0] + dadosobjetivojugador2[1];
        cout << "RONDA " << n << endl;
        cout << endl;
        cout << "Turno de " << perdedor;
        cout << endl;
        cout << "Dados objetivos: " << dadosobjetivojugador2[0] << " y " << dadosobjetivojugador2[1] << " = " << dadosobjetivostotal2;
        cout << endl;
        cout<<endl;
        cout << "Dados stock: ";
        //asigno dados stock jugador 2
        asignarDadosStock(dadostockjugador2, cantDadosStock2);
        //muestro los dados stock
        mostrarDadosStock(dadostockjugador2);
        cout<< endl;
        cout << endl;
        cout << "A continuación seleccionar los dados deseados";
        cout << endl;
        cout << endl;
        //jugador 2 elije dados
        elegirDados(dadostockjugador2);
        system ("pause");
        system ("cls");
        cout << "RONDA " << n<< endl;
        cout << endl;
        cout << endl;
        cout << "Turno de " << perdedor;
        cout << endl;
        cout << endl;
        cout << "Dados objetivos: " << dadosobjetivojugador2[0] << " y " << dadosobjetivojugador2[1] << " = " << dadosobjetivostotal2;
        cout << endl;
        cout<<endl;
        cout << "Dados stock: ";
        mostrarDadosStock(dadostockjugador2);
        cout << endl;
        cout << endl;
        //muestro dados elegidos
        mostrarElegidos(dadosElegidos);
        exito=tiradaExitosa(dadosElegidos, dadosobjetivostotal2);

        if(exito){
            cout<<"Tirada exitosa!"<<endl;
            cout<<endl;
            cout<<"Dados elegidos: "<<dadosElegidos.size()<<" dados."<<endl;
            cout<<endl;
            cout<<"Puntos: "<<dadosobjetivostotal2<<"x"<<dadosElegidos.size()<<"="<<dadosElegidos.size()*dadosobjetivostotal2<<endl;
            cout<<endl;
            cout<<"Transfiere a "<<ganador<<" "<<dadosElegidos.size()<<" dados."<<endl;
            cout<<endl;
            puntaje2=puntaje2+dadosElegidos.size()*dadosobjetivostotal2;
            modDadosStock(cantDadosStock1,cantDadosStock2, dadosElegidos.size(), exito, dadostockjugador2);
            victoriaAutomatica(cantDadosStock2, puntaje2, exito);
            cout<<perdedor<<" "<<cantDadosStock2<<" dados y "<< puntaje2<<"pts."<<endl;
            cout<<endl;
            cout<<ganador<<" "<<cantDadosStock1<<" dados y "<< puntaje1<<"pts."<<endl;
        }else{
            modDadosStock(cantDadosStock1,cantDadosStock2, dadosElegidos.size(),  exito, dadostockjugador2);
            victoriaAutomatica(cantDadosStock1, puntaje1, exito);
            cout<<"No fue una tirada exitosa"<<endl;
            cout<<endl;
            cout<<"Puntos obtenidos:0 "<<endl;
            cout<<endl;
            cout<<"Se te transfieren 1 dado extra de "<<ganador<<"."<<endl;
            cout<<endl;
            cout<<perdedor<<" "<<cantDadosStock2<<" dados y "<< puntaje2<<"pts."<<endl;
            cout<<endl;
            cout<<ganador<<" "<<cantDadosStock1<<" dados y "<< puntaje1<<"pts."<<endl;
            cout<<endl;
        }
        system("pause");
        system ("cls");
        dadosElegidos.clear();
        dadostockjugador2.clear();
    }
        // si paso la tercer ronda o algun jugador se queda sin dados stock muestro resultados finales
        if(n==3 || cantDadosStock1==0 || cantDadosStock2==0){
        cout<<"RESULTADOS FINALES"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"Jugador";
        rlutil::locate(14, 4);
        cout<<"Puntos";
        rlutil::locate(28,4);
        cout<<"Dados stock"<<endl;
        cout<<endl;
        cout<<jugador1;
        rlutil::locate(16, 6);
        cout<<puntaje1;
        rlutil::locate(33,6);
        cout<<cantDadosStock1<<endl;
        cout<<endl;
        cout<<jugador2;
        rlutil::locate(16, 8);
        cout<<puntaje2;
        rlutil::locate(33,8);
        cout<<cantDadosStock2<<endl;
        cout<<endl;
        if(puntaje1>puntaje2){
            cout<<"El ganador es: "<<jugador1<<" felicitaciones!!"<<endl;
            cout<<endl;
            mayorPuntaje(mayor, puntaje1, jugador1, record);
        }
        if(puntaje2>puntaje1){
            cout<<"El ganador es: "<<jugador2<<" felicitaciones!!"<<endl;
            cout<<endl;
            mayorPuntaje(mayor, puntaje2, jugador2, record);
        }
        if(puntaje1==puntaje2){
        cout<<"Empate"<<endl;
        cout<<endl;
        //se dirime quien se postula al puntaje maximo
            if(cantDadosStock1<=cantDadosStock2){
                mayorPuntaje(mayor, puntaje1, jugador1, record);
            } else {
                mayorPuntaje(mayor, puntaje2, jugador2, record);
            }
        }
        //reseteo la cantidad de dados stock
        cantDadosStock1=cantDadosStock2=6;
        system("pause");
        system("cls");
        return;
        }
}

//muestra menu
void MostrarMenu (string& jugador1, string& jugador2) {

   int op, primerlanzamiento1, primerlanzamiento2;

    do {
   cout << "MENÚ PRINCIPAL";
   cout << endl;
   cout << endl;
   cout << "1 - JUGAR";
   cout << endl;
   cout << endl;
   cout << "2 - ESTADÍSTICAS";
   cout << endl;
   cout << endl;
   cout << "3 - CRÉDITOS";
   cout << endl;
   cout << endl;
   cout << "-----------------";
   cout << endl;
   cout << endl;
   cout << "4 - SALIR";
   cout << endl;
   cout << endl;

   cin >> op;


    switch (op) {
        case 1:{
         int puntaje1=0;
         int puntaje2=0;
         system ("cls");
         jugador1 = PreguntoNombreJugador1();
         jugador2 = PreguntoNombreJugador2();
         cout << endl;
         cout << jugador1 << " lanzará su tiro de prueba." << endl;
         cout << endl;

         system ("pause");
         primerlanzamiento1 = TirarDado6caras();
         cout << endl;
         cout << jugador1 << ": " << primerlanzamiento1;
         cout << endl;
         cout << endl;
         cout << endl;
         cout << "Ahora " << jugador2 << " lanzará su tiro de prueba." << endl;
         cout << endl;
         system ("pause");

         primerlanzamiento2 = TirarDado6caras();
         cout << endl;
         cout << jugador2 << ": " << primerlanzamiento2;
         cout << endl;

          if (primerlanzamiento1 == primerlanzamiento2){
             cout << endl;
             cout << "¡EMPATE!" << endl;
             cout << endl;
             cout <<  "Se lanzarán otra vez los dados";
               do{
                cout << endl;
                cout << endl;
                cout << jugador1 << " lanzará nuevamente." << endl;
                cout << endl;
                system ("pause");
                cout << endl;
                primerlanzamiento1 = TirarDado6caras();
                cout << jugador1 << ": " << primerlanzamiento1;
                cout << endl;
                cout << endl;
                cout << "Ahora " << jugador2 << " lanzará nuevamente." << endl;
                cout << endl;
                system ("pause");
                primerlanzamiento2 = TirarDado6caras();
                cout << endl;
                cout << jugador2 << ": " << primerlanzamiento2;
                }
                while (primerlanzamiento1 == primerlanzamiento2);
                }

            if (primerlanzamiento1>primerlanzamiento2) {
                ganador=jugador1;
                perdedor=jugador2;
            }
            if (primerlanzamiento1<primerlanzamiento2) {
                ganador=jugador2;
                perdedor=jugador1;
            }
                cout << endl;
                cout << endl;
                cout << endl;
                cout << "¡"<<ganador << " DARÁ INICIO A LA PARTIDA!" << endl;
                cout << endl;
                system ("pause");
                for(int i=1; i<4;i++){
                    if(cantDadosStock1==0 || cantDadosStock2==0){
                        i=4;
                        break;
                    }
                    Rondas(jugador1, jugador2, i, puntaje1, puntaje2);
                }
                cout << endl;
                break;
                system("cls");
            }
        case 2:{
            system("cls");
                cout<<"        PUNTAJE RECORD"    <<endl;
                cout<<endl;
                cout<<"Jugador"<<"            "<<"Puntaje"<<endl;
                cout<<endl;
                cout<<record<<"               "<<mayor<<endl;
                system("pause");
                system("cls");
                break;
            }
        case 3:{
            cout<< "Todavia no esta configurado ";
            // Creditos();
            break;
            }
        case 4:{
            system ("cls");
            MostrarTitulo();
            system ("cls");
        // SalirDelJuego();
            break;
        }
        default:{
        cout<<"Opción no válida"<<endl;
         system("pause");
        system("cls");
        }
        }

 } while (op !=4);
}



