#include "general.hpp"



extern pieza *fichas[32];
extern pieza *promo[16];
extern tablero tabla;
extern torre torre1b,torre2b,torre1n,torre2n;
extern caballo caballo1b,caballo2b,caballo1n,caballo2n;
extern alfil alfil1b, alfil2b, alfil1n, alfil2n;
extern dama dama1b, dama1n;
extern rey rey1b, rey1n;
extern class peon peon1b,peon2b,peon3b,peon4b,peon5b,peon6b,peon7b,peon8b,peon1n,peon2n,peon3n,peon4n,peon5n,peon6n,peon7n,peon8n;


//Constructor que inicializa la matriz del tablero
tablero :: tablero(){
    int i;  /*i es la fila*/
    int j;   /*j es la col*/    /*color blanco piezas fila 1,2  y color negro piezas filas 7,8*/
    
    for(j=0;j<8;j++)
        casilla[0][j].color=1;
    for(j=0;j<8;j++)
        casilla[1][j].color=1;
    for(j=0;j<8;j++)
        casilla[6][j].color=0;
    for(j=0;j<8;j++)
        casilla[7][j].color=0;
    
    /*piezas blancas   figuras y peones*/
    
    strcpy(casilla[0][0].pieza,"T1b");
    strcpy(casilla[0][1].pieza,"C1b");
    strcpy(casilla[0][2].pieza,"A1b");
    strcpy(casilla[0][3].pieza,"D_b");
    strcpy(casilla[0][4].pieza,"R_b");
    strcpy(casilla[0][7].pieza,"T2b");
    strcpy(casilla[0][6].pieza,"C2b");
    strcpy(casilla[0][5].pieza,"A2b");
    
    strcpy(casilla[1][0].pieza,"P1b");
    strcpy(casilla[1][1].pieza,"P2b");
    strcpy(casilla[1][2].pieza,"P3b");
    strcpy(casilla[1][3].pieza,"P4b");
    strcpy(casilla[1][4].pieza,"P5b");
    strcpy(casilla[1][7].pieza,"P6b");
    strcpy(casilla[1][6].pieza,"P7b");
    strcpy(casilla[1][5].pieza,"P8b");
    
    
    
    /*piezas negras  figuras y peones*/
    
    strcpy(casilla[7][0].pieza,"T1n");
    strcpy(casilla[7][1].pieza,"C1n");
    strcpy(casilla[7][2].pieza,"A1n");
    strcpy(casilla[7][3].pieza,"D_n");
    strcpy(casilla[7][4].pieza,"R_n");
    strcpy(casilla[7][7].pieza,"T2n");
    strcpy(casilla[7][6].pieza,"C2n");
    strcpy(casilla[7][5].pieza,"A2n");
    
    strcpy(casilla[6][0].pieza,"P1n");
    strcpy(casilla[6][1].pieza,"P2n");
    strcpy(casilla[6][2].pieza,"P3n");
    strcpy(casilla[6][3].pieza,"P4n");
    strcpy(casilla[6][4].pieza,"P5n");
    strcpy(casilla[6][7].pieza,"P6n");
    strcpy(casilla[6][6].pieza,"P7n");
    strcpy(casilla[6][5].pieza,"P8n");
    
    /*resto de casillas inicializo casilla vacía pieza='0'*/
    
    for(i=2;i<6;i++){
        for(j=0;j<8;j++){
            strcpy(casilla[i][j].pieza,"0");
        }
    }
    
}



//Función que devuelve que tipo de pieza hay en una determinada posición
char tablero :: leer(unsigned int filf,unsigned int colf){   /*turno=1(blancas) turno=0(negras)*/
    
    return casilla[filf][colf].pieza[0];
    /*si preguntan blancas casilla.color=0 para que se pueda comer si no no*/
    /*si preguntan las negras casilla.color=1 para poder comer idem con las blancas*/
    
}

//Función que devuelve el color de la ficha en una casilla determinada
int tablero:: leercolor(unsigned int filf,unsigned int colf){ /*te da el color de la casilla en la que estas*/
    
    return casilla[filf][colf].color;
    
}

//Función que imprime el tablero por pantalla
void tablero::imprimir(){
    int i,j;
    //Bucles que recorren la matriz
    for(i=7;i>=0;i--){
        for(j=0;j<8;j++){
            //Si la pieza no esta vacia imprime el tipo de pieza y su color(b o n)
            if(casilla[i][j].pieza[0]!='0'){
                cout.width(3);
                cout<<casilla[i][j].pieza[0];
                cout<<casilla[i][j].pieza[2];
            }
            //Si la casilla esta vacia imprime el 0 con un ancho de 4 que es igual
            //al ancho resultante en las no vacias
            else{
                cout.width(4);
                cout<<casilla[i][j].pieza[0];
            }
            if(j==7)
                cout<<endl;
        }
    }
}

//Función que mueve la ficha en el tablero y cambia la posición de la pieza dentro del objeto
void tablero :: mover(pieza *ficha,unsigned int filf,unsigned int colf){
    //vaciamos casilla inicial
    strcpy(casilla[ficha->fila()][ficha->columna()].pieza,"0");
    //función que cambia los valores de la posición del objeto
    ficha->mover(filf,colf);
    //llenamos la casilla de destino con el nombre de nuestra pieza
    strcpy(casilla[filf][colf].pieza,ficha->devolvernombre());
}

//Deshacer mvto en caso de que al mover siga habiendo jaque impedir el movimiento. ira justo despues de mover en el tablero y la propia pieza.
void tablero :: deshacermov(pieza &ficha,unsigned int filf,unsigned int colf){
    
    strcpy(casilla[ficha.fila()][ficha.columna()].pieza,"0");
    ficha.mover(filf,colf);
    strcpy(casilla[filf][colf].pieza,ficha.devolvernombre());
    
    
}

//Constructor de clase base pieza
//El constructor esta sobrecargado, hay uno para las piezas normales y otro para las promocionadas

//Constructor para piezas normales
pieza::pieza(char caracter ){
    
    switch(caracter){
        case 'T':if(contador==0){
            filao=0;
            colo=0;
            color=1;
            strcpy(nombre,"T1b");
            vivo=1;
            contador++;
        }
        else if(contador==1){
            filao=0;
            colo=7;
            color=1;
            strcpy(nombre,"T2b");
            vivo=1;
            contador++;
        }
        else if(contador==2){
            filao=7;
            colo=0;
            color=0;
            strcpy(nombre,"T1n");
            contador++;
            vivo=1;
        }
        else if(contador==3){
            filao=7;
            colo=7;
            color=0;
            vivo=1;
            strcpy(nombre,"T2n");
            contador=0;
        }
            break;
            
        case 'P':strcpy(nombre,"P00");
            if(contador<8){
                nombre[1]=contador+1;
                nombre[2]='b';
                filao=1;
                colo=contador;
                color=1;
                contador++;
            }
            else {
                nombre[1]=contador-7;
                nombre[2]='n';
                filao=6;
                colo=contador-8;
                color=0;
                contador++;
            }
            vivo=1;
            if(contador==16)
                contador=0;
            
            break;
            
        case'C':if(contador==0){
            filao=0;
            colo=1;
            color=1;
            vivo=1;
            strcpy(nombre,"C1b");
            contador++;
        }
        else if(contador==1){
            filao=0;
            colo=6;
            color=1;
            vivo=1;
            strcpy(nombre,"C2b");
            contador++;
        }
        else if(contador==2){
            filao=7;
            colo=1;
            color=0;
            vivo=1;
            strcpy(nombre,"C1n");
            contador++;
        }
        else if(contador==3){
            filao=7;
            colo=6;
            contador=0;
            color=0;
            vivo=1;
            strcpy(nombre,"C2n");
            
        }
            break;
            
        case'A':if(contador==0){
            filao=0;
            colo=2;
            color=1;
            vivo=1;
            contador++;
            strcpy(nombre,"A1b");
            
        }
        else if(contador==1){
            filao=0;
            colo=5;
            color=1;
            vivo=1;
            strcpy(nombre,"A2b");
            contador++;
        }
        else if(contador==2){
            filao=7;
            colo=2;
            color=0;
            vivo=1;
            strcpy(nombre,"A1n");
            contador++;
        }
        else if(contador==3){
            filao=7;
            colo=5;
            contador=0;
            color=0;
            vivo=1;
            strcpy(nombre,"A2n");
            
        }
            break;
            
        case'D':if(contador==0){
            filao=0;
            colo=3;
            color=1;
            vivo=1;
            strcpy(nombre,"D1b");
            contador++;
        }
        else if(contador==1){
            filao=7;
            colo=3;
            color=0;
            vivo=1;
            contador=0;
            strcpy(nombre,"D1n");
        }
            break;
            
        case'R':if(contador==0){
            filao=0;
            colo=4;
            color=0;
            strcpy(nombre,"R1b");
            contador++;
        }
        else if (contador==1){
            filao=7;
            colo=4;
            color=1;
            contador=0;
            strcpy(nombre,"R1n");
            
        }
            break;
    }
    vivo=1;
}

//Constructor para piezas promocionadas
//Copiamos todos los datos del peon promocionado(color,fila,columna... menos el nombre)
pieza::pieza(char caracter ,pieza * peon){
    
    switch(caracter){
            
        case'T':
            if(peon->devolvercolor())
                strcpy(nombre,"T_b");
            else
                strcpy(nombre,"T_n");
            
            break;
            
        case'C':
            if(peon->devolvercolor())
                strcpy(nombre,"C_b");
            else
                strcpy(nombre,"C_n");
            
            break;
            
        case 'A':
            if(peon->devolvercolor())
                strcpy(nombre,"A_b");
            else
                strcpy(nombre,"A_n");
            
            break;
            
        case 'D':
            if(peon->devolvercolor())
                strcpy(nombre,"D_b");
            else
                strcpy(nombre,"D_n");
            
            break;
    }
    filao=peon->fila();
    colo=peon->columna();
    color=peon->devolvercolor();
    vivo=1;
    tabla.mover(this,filao,colo);
    //matamos al peon promocionado
    peon->vivo=0;
    peon->incrementarpromo();
    //Damos vida a la ficha promocionada
    vivo=1;
}

//Constructores de las piezas derivadas que llaman al constructor de la clase base pieza
//se llama al constructor de la base preparado para piezas NO promocionadas
torre::torre(char caracter ):pieza(caracter){}
peon::peon(char caracter ):pieza(caracter){}
caballo::caballo(char caracter ):pieza(caracter){}
alfil::alfil(char caracter ):pieza(caracter){}
dama::dama(char caracter ):pieza(caracter){}
rey::rey(char caracter ):pieza(caracter){}

//Constructores de las piezas derivadas que llaman al constructor de la clase base pieza
//Para piezas promocionadas
torre::torre(char caracter,pieza *peon ):pieza(caracter,peon){}
caballo::caballo(char caracter,pieza *peon):pieza(caracter,peon){}
alfil::alfil(char caracter,pieza *peon ):pieza(caracter,peon){}
dama::dama(char caracter,pieza *peon ):pieza(caracter,peon){}


//Función legalidad de la torre que comprueba que una ficha puede moverse a una posición determinada
//NO mueve la pieza, son comprobaciones
unsigned int torre:: legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer) {
    unsigned int i,aux;
    
    //Si nos han pasado posición inicial y no coincide con la pieza devolver 0
    if(posi){
        if((filao!=filai)&&(colo!=coli))
            return 0;
    }
    //si la pieza esta muerta no puede moverse
    if(vivo==0)
        return 0;
    //al ser una torre la columna o fila final tienen que coincidir con las de la propia pieza
    if(((filaf!=filao)&&(colf!=colo))||((filaf==filao)&&(colf==colo)))
        return 0;
    //recorre las columnas o filas que coincidan
    if(filaf==filao){
        if(colf>=colo){
            i=colf-1;
            aux=colo;
        }
        else {
            i=colo-1;
            aux=colf;
        }
        for(;i>aux;i--)
            if(tabla.leer(filaf,i)!='0')
                return 0;
    }
    if(colf==colo){
        if(filaf>=filao){
            i=filaf-1;
            aux=filao;
        }
        else {
            i=filao-1;
            aux=filaf;
        }
        for(;i>aux;i--)
            if(tabla.leer(i,colo)!='0')
                return 0;
        
    }
    
    return 1;
}

//Función legalidad del peon que comprueba que una ficha puede moverse a una posición determinada
//NO mueve la pieza, son comprobaciones
unsigned int peon:: legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer){
    
    //Si nos han pasado posición inicial y no coincide con la pieza devolver 0
    if(posi){
        if((filao!=filai)&&(colo!=coli))
            return 0;
    }
    //si la pieza esta muerta no puede moverse
    if(vivo==0)
        return 0;
    //comprobaciones propias del movimiento del peon
    if(color){
        if(colf==colo){
            if(((filaf-filao)==2)&&(filao==1)&&((tabla.leer(filaf-1,colf))=='0')&&(tabla.leer(filaf,colf))=='0'){
                return 1;
            }
            else if((filaf-filao==1)&&(tabla.leer(filaf,colf))=='0')
                return 1;
            else return 0;
        }
        else if(comer){
            if((filaf-filao==1)&&((colf-colo==1)||(colf-colo==-1)))
                return 1;
            else return 0;
        }
        else return 0;
        
    }
    else {
        if(colf==colo){
            if(((filao-filaf)==2)&&(filao==6)&&((tabla.leer(filaf+1,colf))=='0')&&(tabla.leer(filaf,colf))=='0'){
                return 1;
            }
            else if((filao-filaf==1)&&(tabla.leer(filaf,colf))=='0')
                return 1;
            else return 0;
        }
        else if(comer){
            if((filao-filaf==1)&&((colf-colo==1)||(colf-colo==-1)))
                return 1;
            else return 0;
        }
        else return 0;
    }
    
}

//Función legalidad del caballo que comprueba que una ficha puede moverse a una posición determinada
//NO mueve la pieza, son comprobaciones
unsigned int caballo:: legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer){
    /*(i,j)posiciónes posible*/
    
    unsigned int i=filao;
    unsigned int j=colo;
    
    //Si nos han pasado posición inicial y no coincide con la pieza devolver 0
    if(posi){
        if((filao!=filai)&&(colo!=coli))
            return 0;
    }
    //si la pieza esta muerta no puede moverse
    if(vivo==0)
        return 0;
    
    /*empiezo desde arriba a la derecha y me muevo en sentido anihorario*/
    //si hay una pieza del otro color en la casilla a la que vamos(se mira a través de la función leer()) devuelve un 1 y da permiso al tablero para mover y matar si no leer() devuelve un 0.
    
    
    i=filao+2; j=colo+1;
    if((i==filaf)&&(j==colf))
        return 1;
    
    i=filao+2; j=colo-1;
    if((i==filaf)&&(j==colf))
        return 1;
    
    i=filao-2; j=colo+1;
    if((i==filaf)&&(j==colf))
        return 1;
    
    i=filao-2; j=colo-1;
    if((i==filaf)&&(j==colf))
        return 1;
    
    i=filao+1; j=colo+2;
    if((i==filaf)&&(j==colf))
        return 1;
    
    i=filao-1; j=colo+2;
    if((i==filaf)&&(j==colf))
        return 1 ;
    
    i=filao+1; j=colo-2;
    if((i==filaf)&&(j==colf))
        return 1;
    
    i=filao-1; j=colo-2;
    if((i==filaf)&&(j==colf))
        return 1;
    
    
    return 0;
}

//Función legalidad del alfil que comprueba que una ficha puede moverse a una posición determinada
//NO mueve la pieza, son comprobaciones
unsigned int alfil::legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer){
    
    //compruebo que estan dentro del tablero:posicion e instruccion
    // PRUEBA ALFIL diag derecha sup
    
    //Si nos han pasado posición inicial y no coincide con la pieza devolver 0
    if(posi){
        if((filao!=filai)&&(colo!=coli))
            return 0;
    }
    //si la pieza esta muerta no puede moverse
    if(vivo==0)
        return 0;
    
    for(unsigned int i=filao,j=colo;i<8;i++,j++){    //diag sup derecha
        if(j>=8)break;
        if(i==filaf&&j==colf){
            for(unsigned int k=filao+1,l=colo+1;k<filaf;k++,l++){
                if(tabla.leer(k,l)=='0'){continue;}
                else return 0;
                
            }
            return 1;
        };
    };
    
    for(int i=filao,j=colo;i<8;i++,j--){    //diag sup izquierda
        if(j<0)break;
        if(i==filaf&&j==colf){
            for(unsigned int k=filao+1,l=colo-1;k<filaf;k++,l--){
                if(tabla.leer(k,l)=='0'){continue;}
                else return 0;
                
            }
            return 1;
        };
    };
    
    for(int i=filao,j=colo;i>=0;i--,j--){    //diag inf izq
        if(j<0)break;
        if(i==filaf&&j==colf){
            for(unsigned int k=filao-1,l=colo-1;k>filaf;k--,l--){
                if(tabla.leer(k,l)=='0'){continue;}
                else return 0;
                
            }
            return 1;
        };
        
    };
    
    
    for(int i=filao,j=colo;i>=0;i--,j++){    //diag inf derecha
        if(j>=8)break;
        if(i==filaf&&j==colf){
            for(unsigned int k=filao-1,l=colo+1;k>filaf;k--,l++){
                if(tabla.leer(k,l)=='0'){continue;}
                else return 0;
                
            }
            return 1;
        };
        
    };
    return 0;
}

//Función legalidad de la torre que comprueba que una ficha puede moverse a una posición determinada
//NO mueve la pieza, son comprobaciones
unsigned int dama::legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer){
    
    unsigned int h,aux;
    
    //Si nos han pasado posición inicial y no coincide con la pieza devolver 0
    if(posi){
        if((filao!=filai)&&(colo!=coli))
            return 0;
    }
    
    if(vivo==0)
        return 0;
    
    
    for(unsigned int i=filao,j=colo;i<8;i++,j++){    //diag sup derecha
        if(j>=8)break;
        if(i==filaf&&j==colf){
            for(unsigned int k=filao+1,l=colo+1;k<filaf;k++,l++){
                if(tabla.leer(k,l)=='0'){continue;}
                else return 0;
                
            }
            return 1;
        };
    };
    
    for(int i=filao,j=colo;i<8;i++,j--){    //diag sup izquierda
        if(j<0)break;
        if(i==filaf&&j==colf){
            for(unsigned int k=filao+1,l=colo-1;k<filaf;k++,l--){
                if(tabla.leer(k,l)=='0'){continue;}
                else return 0;
                
            }
            return 1;
        };
    };
    
    for(int i=filao,j=colo;i>=0;i--,j--){    //diag inf izq
        if(j<0)break;
        if(i==filaf&&j==colf){
            for(unsigned int k=filao-1,l=colo-1;k>filaf;k--,l--){
                if(tabla.leer(k,l)=='0'){continue;}
                else return 0;
                
            }
            return 1;
        };
        
    };
    
    
    for(int i=filao,j=colo;i>=0;i--,j++){    //diag inf derecha
        if(j>=8)break;
        if(i==filaf&&j==colf){
            for(unsigned int k=filao-1,l=colo+1;k>filaf;k--,l++){
                if(tabla.leer(k,l)=='0'){continue;}
                else return 0;
                
            }
            return 1;
        };
        
    };
    
    if(((filaf!=filao)&&(colf!=colo))||((filaf==filao)&&(colf==colo)))
        return 0;
    
    if(filaf==filao){
        if(colf>=colo){
            h=colf-1;
            aux=colo;
        }
        else {
            h=colo-1;
            aux=colf;
        }
        for(;h>aux;h--)
            if(tabla.leer(filaf,h)!='0')
                return 0;
    }
    if(colf==colo){
        if(filaf>=filao){
            h=filaf-1;
            aux=filao;
        }
        else {
            h=filao-1;
            aux=filaf;
        }
        for(;h>aux;h--)
            if(tabla.leer(h,colo)!='0')
                return 0;
        
    }
    
    
    return 1;
    
    
}



/*REY*/

//CONSTRUCTOR REY


//LEGALIDAD REY

unsigned int rey:: legalidad(unsigned int filaf , unsigned int colf,tablero &tabla,bool posi,unsigned int filai, unsigned int coli,bool comer){
    
    //no compruebo si me han pasado posicion inicial porque solo hay un rey
    //si la pieza esta muerta no puede moverse
    if(vivo==0)
        return 0;
    
    
    int i; int j;int encontrado=0;
    i=filao; j=colo;
    
    
    
    //compruebo los posibles movimientos del rey y si coincide alguno con el que me han pasado entonces encontrado=1
    i=filao+1;j=colo; if(i==filaf&&j==colf){ encontrado++;}
    
    i=filao+1; j=colo+1; if(i==filaf&&j==colf){ encontrado++;}
    
    i=filao+1; j=colo-1; if(i==filaf&&j==colf){ encontrado++;}
    
    i=filao; j=colo+1;if(i==filaf&&j==colf){ encontrado++;}
    
    i=filao; j=colo-1;if(i==filaf&&j==colf){ encontrado++;}
    
    i=filao-1; j=colo-1;if(i==filaf&&j==colf){ encontrado++;}
    
    i=filao-1; j=colo+1;if(i==filaf&&j==colf){ encontrado++;}
    
    i=filao-1;j=colo; if(i==filaf&&j==colf){ encontrado++;}
    
    //comprobacion de que al mover ninguna pieza del jugador enemigo me puede comer/llegar hasta esa posición
    
    if(encontrado){encontrado=0; return 1;}
    else return 0;
    
    
}




