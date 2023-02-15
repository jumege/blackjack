/*
Nom: ___________________
S'ha d'optimitzar aquest codi tot el que pugueu.
Fer un document PDF on s'explica detalladament com estava el codi i quina millora heu fet.
Podeu modificar el codi tot el que vulgueu, però ha de mantenir les mateixes funcionalitats, no pot tenir noves ni tenir menys, el programa ha de fer el mateix.
*/

#include <iostream>
#include <cstdlib> //for rand and srand
#include <cstdio>
#include <string>
#include <ctime> // time function for seed value
#include <chrono>
#include <thread>
#include <unistd.h>

//unsigned int microseconds;

using namespace std;

struct carta

{
	int numero;
	string palo;
};


void mycout(string x,int n){

  if (n == 0)
        cout << x << endl;
  else if (n == 1)
        cout << "\033[1;31m"<< x <<"\033[0m" << endl;
  else if (n == 2)
        cout << "\033[1;32m"<< x <<"\033[0m" << endl;
  else if (n == 3)
        cout << "\033[1;33m"<< x <<"\033[0m" << endl;
  else if (n == 4)
        cout << "\033[1;34m"<< x <<"\033[0m" << endl;
  else if (n == 5)
        cout << "\033[1;35m"<< x <<"\033[0m" << endl;  
}
void mycout2(string x,struct carta manoH, int n){
  
  if (n == 0)
        cout << x << manoH.palo << endl;
  else if (n == 1)
        cout << "\033[1;31m"<< x << manoH.palo<<"\033[0m" << endl;
  else if (n == 2)
        cout << "\033[1;32m"<< x << manoH.palo <<"\033[0m" << endl;
  else if (n == 3)
        cout << "\033[1;33m"<< x << manoH.palo <<"\033[0m" << endl;
  else if (n == 4)
        cout << "\033[1;34m"<< x << manoH.palo <<"\033[0m" << endl;
  else if (n == 5)
        cout << "\033[1;35m"<< x << manoH.palo <<"\033[0m" << endl;

      
}
void status(int puntos, int *r, int *turno){
  if (puntos > 21){
    cout << "\033[1;31mTe has pasado... puntos: " << puntos << "\033[0m" << endl;
    cout << "\033[1;31mHas perdido\033[0m" << endl;
  *r = 0;
  *turno = 0;

  }       
  else if (puntos == 21){ 
    cout << "\033[1;33mFELICIDADES tienes " << puntos << "puntos! (Blackjack)\033[0m" << endl;
      *r = 0;
      *turno = 0;

  }
  else {
  cout << "\033[1;32mTienes " << puntos <<" puntos \033[0m" << endl;
  *r = 1;
  *turno= 1;

  }
}
void base_loader(struct carta baraja[]){
  time_t t;
  srand((unsigned) time(&t));
	//int numeros[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	const string palos[4] = { "Corazones", "Diamantes", "Picas", "Treboles" };
	
	int contador = 0; 

	for ( int i = 0; i < 13; i++){
		for ( int j = 0; j < 4; j++){
			baraja[contador].numero = i+1;
			baraja[contador].palo = palos[j];
			contador++;
		}
	}
}
void menu(){
          mycout ("Menu de opciones\n",1);
          mycout (" 1. Robar carta \n 2. Mostrar mano \n 3. Plantarse \n 4. Ver baraja \n 0. Salir",2);
}

void show_baraja(struct carta baraja[]){
  for (int contadorBaraja = 0; contadorBaraja < 52; contadorBaraja++){
                if( baraja[contadorBaraja].numero == 1){
                  cout <<  "A de " << baraja[contadorBaraja].palo << endl;
                } else if (baraja[contadorBaraja].numero == 11){
                  cout <<  "Sota de " << baraja[contadorBaraja].palo << endl;
                } else if (baraja[contadorBaraja].numero == 12){
                  cout <<  "Caballo de " << baraja[contadorBaraja].palo << endl;
                } else if (baraja[contadorBaraja].numero == 13){
                  cout <<  "Rey de " << baraja[contadorBaraja].palo << endl;
                } else {
                  cout << baraja[contadorBaraja].numero << " de " << baraja[contadorBaraja].palo << endl;
                }
              }
}

void mostrar_manoH(struct carta mano[],int *puntox,int *x){
 mycout("Tus cartas son:",3);       
 int puntos = 0 ;
 int contadorAs = 0;
 int num_cartas_mano = 0;
  for (int contadorMano = 0; contadorMano < 52; contadorMano++){
            if (mano[contadorMano].palo != ""){
              if( mano[contadorMano].numero == 1){
                mycout2 ("As de",mano[contadorMano],3);
                contadorAs++;
                if (contadorAs >= 1 && puntos+11 > 21){
                  puntos = puntos + 1;
                } else {
                  puntos = puntos + 11;
                }
                num_cartas_mano++;
              } else if (mano[contadorMano].numero == 11){
                mycout2 ("Sota de ",mano[contadorMano],3);
                puntos = puntos + 10;
                num_cartas_mano++;
              } else if (mano[contadorMano].numero == 12){
                mycout2 ("Caballo de ",mano[contadorMano],3);
                puntos = puntos + 10;
                num_cartas_mano++;
              } else if (mano[contadorMano].numero == 13){
                mycout2 ("Rey de ",mano[contadorMano],3);
                puntos = puntos + 10;
                num_cartas_mano++;
              } else {
                cout << "\033[1;33m "<< mano[contadorMano].numero << " de " << mano[contadorMano].palo << "\033[0m" << endl;
                puntos = puntos + mano[contadorMano].numero;
                num_cartas_mano++;
              }
            }
            }
  *x = num_cartas_mano;
  *puntox = puntos;
        
}
void jugada_maquina(struct carta manoMaquina[],struct carta baraja[], int puntos,int *r){
  int puntosMaquina = 0;
  int carta_mano_maquina =0;
cout << "\033[1;32mHas conseguido " << puntos << " puntos \033[0m" << endl;
                cout << "\033[1;36mAhora juega la maquina\033[0m" << endl;
                while(puntosMaquina < puntos){
                  cout << "\033[1;36mLa maquina roba carta\033[0m" << endl;
                  sleep(1);
                  manoMaquina[carta_mano_maquina] = baraja[rand()%52];
                  if( manoMaquina[carta_mano_maquina].numero == 1){
                    cout <<  "\033[1;33m A de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
                  } else if (manoMaquina[carta_mano_maquina].numero == 11){
                    cout <<  "\033[1;33m Sota de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
                  } else if (manoMaquina[carta_mano_maquina].numero == 12){
                    cout <<  "\033[1;33m Caballo de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
                  } else if (manoMaquina[carta_mano_maquina].numero == 13){
                    cout <<  "\033[1;33m Rey de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
                  } else {
                    cout << "\033[1;33m " << manoMaquina[carta_mano_maquina].numero << " de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
                  }
                  puntosMaquina = puntosMaquina + manoMaquina[carta_mano_maquina].numero;
                  cout << "\033[1;37m Puntos maquina: " << puntosMaquina << endl;
                  carta_mano_maquina++;
                }
                if (puntosMaquina > 21){
                  cout << "\033[1;31mLa máquina se ha pasado\033[0m" << endl;
                  cout << "\033[1;33mFELICIDADES, HAS GANADO!\033[0m" << endl;
                } else if (puntosMaquina == puntos){
                  cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
                  cout << "\033[1;33mEmpate\033[0m" << endl;
                } else {
                  cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
                  cout << "\033[1;31mHas perdido...\033[0m" << endl;
                }
                cout << "\033[1;35mTu has conseguido " << puntos << " puntos y la máquina " << puntosMaquina << " puntos\033[0m" << endl;
                *r = 0; 
}

int main(){

	struct carta baraja[52];
  int repetir;
  int opcion;
  struct carta mano[52], manoMaquina[52];
  int num_cartas_mano, carta_mano_maquina, puntos, contadorAs, puntosMaquina, turno = 0;
  base_loader(baraja);
  //Repartir cartas
  for (int contadorBaraja = 0; contadorBaraja < 2; contadorBaraja++){
    mano[contadorBaraja] = baraja[rand()%52];
  }
 
  do {
        menu();//muestra el menu
        if (turno == 0)
        {
          mostrar_manoH(mano,&puntos,&num_cartas_mano);//muestra la mano solo el primer turno
          
        };
        status(puntos, &repetir,&turno);//muestra los puntos que llevas y decide si continuas o no
        mycout("Ingrese una opcion: ",0);
        cin >> opcion;
       

        switch (opcion) {
            case 1:
            	  system("cls");
                mano[num_cartas_mano+1] = baraja[rand()%52];  //roba una carta
                cout << "\033[1;32mTu carta es: \033[0m" << endl;
                //abajo suma los puntos 
                if (mano[num_cartas_mano+1].numero >=10){
                puntos += 10; 
                }
                else {
                  puntos += mano[num_cartas_mano+1].numero;
                }
                //muestra la carta robada
                cout << mano[num_cartas_mano+1].numero << " de "<< mano[num_cartas_mano+1].palo << endl;
                status(puntos, &repetir,&turno);//muestra cuantos puntos tienes y decide si continuas
                system("pause");               

                break;
                
            case 2:
                system("cls");               
                cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
                mostrar_manoH(mano,&puntos,&num_cartas_mano);//muestra tu mano y devuelve los puntos robados, numero de cartas
                status(puntos, &repetir,&turno);//utiliza los puntos devueltos antes decide si repite
                system("pause");
                break;
                
                
            case 3:
            	system("cls");  
              jugada_maquina(manoMaquina,baraja,puntos,&repetir);          
          
                break;
            case 4:
              show_baraja(baraja);
            
              break;

            case 0:
            	repetir = false;
            	break;
        }        
    } while (repetir!=0);

		return 0;
}
