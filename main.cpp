
//
//  main.cpp
//  version ajedrez5
//
//  Created by Team Progra on 20/5/16.
//
// Cuerpo del programa principal

#include "general.hpp"
using namespace std;

//Declaración de los vectores que engloban las piezas normales y las piezas promocionadas
pieza *fichas[32];
pieza *promo[16];
//Declaración de los objetos globales
tablero tabla, tabla_copia;
torre torre1b('T'),torre2b('T'),torre1n('T'),torre2n('T');
caballo caballo1b('C'),caballo2b('C'),caballo1n('C'),caballo2n('C');
alfil alfil1b('A'), alfil2b('A'), alfil1n('A'), alfil2n('A');
dama dama1b('D'), dama1n('D');
rey rey1b('R'), rey1n('R');
class peon peon1b('P'),peon2b('P'),peon3b('P'),peon4b('P'),peon5b('P'),peon6b('P'),peon7b('P'),peon8b('P'),peon1n('P'),peon2n('P'),peon3n('P'),peon4n('P'),peon5n('P'),peon6n('P'),peon7n('P'),peon8n('P');

const unsigned int IT=8,IC=10,IA=12,ID=14,IR=15,IP=0;

unsigned int pieza:: contador=0;

//Programa ppal
int main() {
    
    //Declaracion de variables para el tiempo de cada jugador
    time_t t1, t2,sec1,sec2,minutos_max=0;
    time_t tiempo_partida[2]={0,0}, minutos[2]={0,0};
    time_t segundos[2]={0,0};
    short int bandera=0;
    int turno_pantalla,contador_turnos=2;
    //cadena que guarda la instruccion y caracter ficha que guarda que ficha se mueve en dicho turno
    char instruccion[7],ficha='z';
    //variables que guardan info variada
    //colf filaf son la posicion final a la que se mueve la pieza
    //coli filai posicion inicial en caso de que nos la den
    //turno cuenta el numero de turnos que han pasado
    //contador promo indica hasta que posicion el vector promos esta lleno
    //variables "pasado" guardan la posicion en caso de que al mover produzcamos un jaque sobre nuestro propio rey
    //y haya que revertir el movimiento
    //en indice se guarda donde comienzan las piezas del tipo introducido(rey,dama...) en el vector fichas
    //total es el numero de piezas que hay por tipo.Por ej para rey 'R', total=1, para torre 'T' total =2...
    unsigned int colf=9,filaf=9,coli=9,filai=9,turno=0,contadorpromo=0,filapasado=0,colpasado=0,indice=0,total=0,i=0,colu_i=0, colu_f=0,filu=0,auxi=0;
    //variables que indican el estado de cada turno, si se come,si se mueve un peon,el color del bando que mueven,
    //si nos han introducido en la instruccion una posicion inicial (posi)...
    bool comer=0,jaque=0,peon=0,seguir=1,color=1,posi=0,error=0,enroqlargo=0,enroqcorto=0,comp=0,promocion=0,enroq=0,temp_empleado,saltarpromo=1;
    //Vector de promocionadas que apunten a null al estar vacias
    for(int i=0;i<16;i++)
        promo[i]=NULL;
    
    //Función que apunta cada puntero del vector de "fichas" a su objeto correspondiente
    introavectores();
    
    //Introducir tiempo del que dispondra cada jugador
    cout<<"Introduce el tiempo del que dispondra cada jugador. Maximo 1 hora";
    cout<<endl;
    cin>>minutos_max;
    cout<<endl;
    
    //Imprimir tablero
    tabla.imprimir();
    cout<<endl;
    
    //Bucle de los turnos
    while(seguir){
        //si la instruccion es erronea o ha ocurrido un error no avanzar en el turno
        turno=(error==1)?turno:++turno;
        //dependiendo de si el turno es par mueven las piezas de un color u otro
         color=(turno%2)?1:0;
        if(color)
            cout<<endl<<"Mueven blancas"<<endl;
        else
            cout<<endl<<"Mueven negras"<<endl;
        
        //Inicializo tiempo auxiliares a cero para evitar problemas
        t1=0;
        t2=0;
        
        //Empiezo a medir tiempo
        t1=time(&sec1);
        // tiempo en segundos
        
        //Comprueba que esta bien escrita la instrucción y comprobaciones inmediatas(si mueve que esté vacia la posición final,
        //y si come que este ocupada de una pieza de color opuesto
        primerascomp(instruccion,ficha,colf, filaf, coli, filai, comer, jaque,peon,color,promocion,enroqlargo,enroqcorto,comp,error,turno,posi);
        //si se rinde un jugador acabar partida
        if(strcmp(instruccion,"=")==0){
            seguir=0;
            continue;
        }
        cout<<ficha<<colf<<filaf<<coli<<filai<<comer<<jaque<<peon;
        cout<<endl;
        
        
        // Compruebo que el enroque es legal
        enroq=comprob_enroques(color,enroqlargo,enroqcorto, colu_i,colu_f, filu,auxi,IT,IR,bandera);
        if(enroq==true) {
            //Obtenemos el tiempo que ha pasado desde que empezo el turno
            t2=time(&sec2);
            // tiempo en segundos
            temp_empleado=tiempo_empleado(&color,t1,t2,tiempo_partida,minutos,segundos,&minutos_max, &turno_pantalla, &contador_turnos);
            //Impresion por pantalla del tablero
            tabla.imprimir();
            
            //funcion que imprime las fichas muertas
            imprimirmuerta(contadorpromo);
            continue;
        }
        if(enroq==false&&bandera==1){
            bandera=0;
            continue;
        }
        
        //Le damos el valor al indice dependiendo de que pieza queremos mover para recorrer el vector de piezas normales en donde nos interesa
        switch(ficha){
            case 'P':indice=IP;
                total=8;
                break;
                
            case 'T':indice=IT;
                total=2;
                break;
                
            case 'C':indice=IC;
                total=2;
                break;
                
            case 'A':indice=IA;
                total=2;
                break;
                
            case 'D':indice=ID;
                total=1;
                break;
                
            case 'R':indice=IR;
                total=1;
                break;
                
        }
            //multiplesmov devuelve cuantas piezas del tipo dado se pueden mover
            //a la posicion final
            //Si puede moverse más de una y no me han pasado la posición inicial error
        if(multiplesmov(filaf,colf,filai,coli,indice,total,contadorpromo,i,color,posi,comer,ficha)!=1){
            error=1;
            continue;
        }
        // a trvés de tabla copia guardamos la situación antes de mover la pieza por si el movimiento no fuera legal. para poder volver a trás
        tabla_copia=tabla;
        
        //Llegados aqui sabemos que solo una pieza con nuestras restricciones va a moverse
        saltarpromo=1;
        for(i=color*16+indice;i<(color*16+indice+total);i++){
            if(fichas[i]->legalidad(filaf,colf,tabla,posi,filai,coli,comer)){
                
                //datos que cogemos para poder deshacer el cambio en caso de que nuestro movimiento
                //provoque un jaque a nuestro propio rey
                filapasado=fichas[i]->fila();
                colpasado=fichas[i]->columna();
                
                //Función que mueve la ficha en el tablero y cambia su posición original dentro del objeto
                tabla.mover(fichas[i],filaf,colf);
            
                //Si las fichas que se mueven son torre o rey aumentar su numero de movimientos hechos para
                //tenerlo en cuenta y no dejar hacer los enroques
                if((*fichas[i]->devolvernombre()=='T')||(*fichas[i]->devolvernombre()=='R'))
                    fichas[i]->aumentarmov();
                //compjaque comprueba que habiendo movido, ninguna ficha nos hace jaque
                if(compjaque(filaf,colf,posi,filai, coli, color,comer,jaque,contadorpromo)==0){
                    //si alguna ficha nos hace jaque al mover deshacemos el cambio hecho
                    tabla=tabla_copia;
                    fichas[i]->mover(filapasado, colpasado);
                    error=1;
                    continue;
                }
                saltarpromo=0;
                break;
            }
        }
        //si ya se ha movido una ficha normal no comprobar si se puede mover una promocionada
        
        if(saltarpromo){
        //igual para las fichas promocionadas
        for(int i=0;i<contadorpromo;i++){
            if((promo[i]!=NULL)&&(promo[i]->devolvercolor()==color)&&(*promo[i]->devolvernombre()==ficha)){
                filapasado=promo[i]->fila();
                colpasado=promo[i]->columna();
                tabla.mover(promo[i],filaf,colf);
                if((*promo[i]->devolvernombre()=='T')||(*promo[i]->devolvernombre()=='R'))
                    promo[i]->aumentarmov();
                
                //en comparación de jaque se hacen dos cosas:
               
                //que al mover blancas, el rey blanco no quede en jaque(ninguna pieza pueda llegar hasta él.
                //y que al mover blancas, si hago jaque(alguna pieza blanca pueda llegar a donde esté el negro) , que el jugador lo halla indicado
                //por lo tanto le tendré que pasar la posición del rey de ambos bandos
                //la 3º y 4º son la fila y columna del rey del mismo color y la 5º y la 6º son la fila y columna del rey del otro color
                if(compjaque(filaf,colf,posi,filai, coli, color,comer,jaque,contadorpromo)==0){
                    tabla=tabla_copia;
                    promo[i]->mover(filapasado, colpasado);
                    error=1;
                    continue;
                }
                break;
            }
        }
        }
        //si el peon ha llegado a la fila final promocionarlo
        if(peon){
            if((color)&&(filaf==7)){
                fpromocionar(contadorpromo,fichas[i]);
            }
            else if((color==0)&&(filaf==0))
                fpromocionar(contadorpromo,fichas[i]);
            
        }
        
        //Si ha habido una pieza comida
        if(comer){
            //Función que mata a la pieza que tenga el color opuesto al del que mueve
            //y la misma posición final
            fcomer(filaf,colf,color,contadorpromo);
        }
        
        //Obtenemos el tiempo que ha pasado desde que empezo el turno
        t2=time(&sec2);
        // tiempo en segundos
        temp_empleado=tiempo_empleado(&color,t1,t2,tiempo_partida,minutos,segundos,&minutos_max, &turno_pantalla, &contador_turnos);
        
        //En caso de sobrepasar el tiempo, se acaba la partida
        if(temp_empleado==false){
            return 0;
        }
        //Impresion por pantalla del tablero
        tabla.imprimir();
        
        //funcion que imprime las piezas muertas
        imprimirmuerta( contadorpromo);
        
    }
    //Eliminar variables dinámicas(fichas promocionadas)
    for(int i=0;i<16;i++)
        delete promo[i];
    //Fin del juego
    cout<<"fin del juego"<<endl;
    return 0;
    
}
