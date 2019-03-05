//
//  funciones general.hpp
//  version ajedrez5
//
//  Created by Team Progra on 20/5/16.
//
//Clases base pieza,clase independiente tablero,clases derivadas peon,torre,caballo,rey,alfil y dama
//También definido struct de la que esta hecha la matriz del tablero
//Prototipos de las funciones no miembro al final del fichero
#ifndef general_hpp
#define general_hpp

#include <iostream>
using namespace std;
class dama;
class caballo;
class peon;
class alfil;
class torre;
class pieza;
//STRUCT DE CADA CASILLA
struct posicion{
    
    char pieza[4]; /* si '0' significa qu eno hay pieza*/
    int color;
}; /*color=1 blanco     color=0 negro   */

//TABLERO
class tablero{
private:
    struct posicion casilla[8][8];
    
public:
    //las funciones estan explicadas en sus definiciones
    tablero();
    void inicializar();
    char leer(unsigned int filf,unsigned int colf);
    int leercolor(unsigned int filf,unsigned int colf);
    void moverpieza(char fila,char col,char pieza);
    void imprimir();
    void mover(pieza *ficha,unsigned int filf,unsigned int colf);
    void deshacermov(pieza &ficha,unsigned int filf,unsigned int colf);
    void insertarpromo(char nombre[4],unsigned int filf,unsigned int colf);
};
//CLASE BASE PIEZA

class pieza{
    
protected:
    static unsigned int contador;
    unsigned int filao,colo,vivo,color;
    char nombre[4];
    
public:
    //no hay que llamar ha esta función
    //solo para torre y rey
    //definida en clase torre y rey
    virtual void aumentarmov(){}
    
    //no hay que llamar ha esta función
    //solo para torre y rey
    //definida en clase torre y rey
    virtual unsigned int devolvermov(){
        return -1;
    }
    pieza(char );
    pieza(char caracter ,pieza *peon);
    //función virtual pura que esta definida en cada clase derivada(peon,torre,alfil,dama,rey,caballo)
    virtual unsigned int legalidad(unsigned int , unsigned int ,tablero &tabla,bool posi,unsigned int filai,unsigned int coli,bool comer)=0;
    //cambia la posicion del objeto a la final
    void  mover(unsigned int fila,unsigned int col){
        colo=col;
        filao=fila;
    }
    //mata a la pieza dandole el valor 0 a la variable vivo
    void muerte(unsigned int filaf,unsigned int colf,bool colorturno){
        if((color!=colorturno)&&(filao==filaf)&&(colo==colf))
            vivo=0;
    }
    
    unsigned int columna(){
        return colo;
    }
    unsigned int fila(){
        return filao;
    }
    char* devolvernombre(){
        return nombre;
    }
    //si esta muerta la imprime
    void imprimirmuerta(){
        if(vivo==0)
            cout<<nombre;
    }
    void vive(){
        vivo=1;
    }
    
    unsigned int devolvercolor(){
        return color;
    }
    virtual void  incrementarpromo(){}
    virtual bool devolverpromo(){return 0;}
    virtual ~pieza(){};
};


//CLASES FIGURAS

class torre :public pieza {
private:
    unsigned int mov;
    public :
    unsigned int devolvermov(){
        return mov;
    }
    //aumenta el numero de mov efectuados(solo para torre y rey)
    void aumentarmov(){
        mov++;
    }
    torre(char);
    torre(char, pieza *);
    unsigned int legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer);
    
    
};

class peon :public pieza{
private:
    bool promo;
    public :
    void incrementarpromo(){
        promo=1;
    }
    bool devolverpromo(){
        return promo;
    }
    peon(char);
    unsigned int legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer);
    
};

class caballo :public pieza {
    
    public :
    caballo(char ,pieza * peon);
    caballo(char );
    unsigned int legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer);
    
};



class alfil :public pieza {
    
    public :
    alfil(char,pieza *peon);
    alfil(char);
    unsigned int legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer);
    
};

class dama :public pieza {
    
    public :
    dama(char);
    dama(char,pieza *peon);
    unsigned int legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer);
    
    
};

class rey :public pieza {
private:
    unsigned int mov;
    
    public :
    //devuelve el numero de mov efectuados(solo para torre y rey)
    unsigned int devolvermov(){
        return mov;
    }
    //aumenta el numero de mov efectuados(solo para torre y rey)
    void aumentarmov(){
        mov++;
    }
    rey(char);
    unsigned int legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer);
    
};


//PROTOTIPOS

unsigned int sintaxis(char *instruccion,char &ficha,unsigned int &colf,unsigned int &filaf,unsigned int &coli,unsigned int &filai,bool &comer,bool &jaque,bool &peon,bool &color,bool &promocion,bool &enroqlargo,bool &enroqcorto);

unsigned int compjaque(unsigned int filaf,unsigned int colf,bool posi,unsigned int filai,unsigned int coli,bool color,bool comer,bool jaque,unsigned int contadorpromo);
void imprimirmuerta(unsigned int contadorpromo);
void fcomer(unsigned int filaf,unsigned int colf,bool color,unsigned int contadorpromo);
void fpromocionar(unsigned int &contadorpromo,pieza *peon);
void introavectores();
void primerascomp(char *instruccion,char &ficha,unsigned int &colf,unsigned int &filaf,unsigned int &coli,unsigned int &filai,bool &comer,bool &jaque,bool &peon,bool &color,bool &promocion,bool &enroqlargo,bool &enroqcorto,bool &comp,bool &error,unsigned int &turno,bool &posi);

bool comprob_enroques(bool &color,bool &enroqlargo,bool &enroqcorto, unsigned int &colu_i,unsigned int &colu_f, unsigned int &filu,unsigned int &auxi,const unsigned int IT, const unsigned int IR, short int &bandera);

bool tiempo_empleado(bool *color,time_t t1,time_t t2,time_t tiempo_partida[2],time_t minutos[2],time_t segundos[2],time_t *minutos_max,int *turno_pantalla, int *contador_turnos);
unsigned int multiplesmov(unsigned int filaf,unsigned int colf,unsigned int filai,unsigned int coli,unsigned int indice,unsigned int total,unsigned int contadorpromo,unsigned int &i,bool color,bool posi,bool comer,char ficha);
#endif /* general_hpp */
