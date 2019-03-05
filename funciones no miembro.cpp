//
//  funciones miembro.cpp
//  ajedrez version 6
//
//  Created by Team Progra on 21/5/16.
//  Copyright © 2016 Team Progra. All rights reserved.
//

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


unsigned int compjaque(unsigned int filaf,unsigned int colf,bool posi,unsigned int filai,unsigned int coli,bool color,bool comer,bool jaque,unsigned int contadorpromo) {
   
    int i; int c;
    
     // int c me permite obtener el color de las piezas contrarias a partir de color
    c=(color==1)? 0:1;
    //compruebo que al mover, las piezas de mi color hacen jaque y lo ha indicado el jugador en sintaxis(jaque=1)
    for(i=color*16;i<(color*16+15);i++){
        if(fichas[i]->legalidad(fichas[c*16+15]->fila(),fichas[c*16+15]->columna(),tabla,posi,filai,coli,comer)&&(jaque==0)){return 0;}
    }
    //lo mismo para las promocionadas
    for(i=0;i<contadorpromo;i++){
        if((promo[i]!=NULL)&&(promo[i]->devolvercolor()==color))
            if(promo[i]->legalidad(fichas[c*16+15]->fila(),fichas[c*16+15]->columna(),tabla,posi,filai,coli,comer)&&(jaque==0)){return 0;}
    }
    //compruebo que al mover la pieza, no dejo a mi rey en jaque(le pregunto a las del otro bando si pueden llegar hasta mi rey
    // añado la comprobación de que ni la fila ni la columna sean iguales para aegurarme de que si he comido a una pieza esa no se comprueba
    //ya que en nuestro algoritmo solo se mata la pieza una vez aceptada la jugada, mientras tanto el objeto mantiene sus atributos
    for(i=c*16;i<(c*16+16);i++){
        if(fichas[i]->legalidad(fichas[color*16+15]->fila(),fichas[color*16+15]->columna(),tabla,posi,filai,coli,comer)&&(fichas[i]->fila()!=filaf)&&(fichas[i]->columna()!=colf)){return 0;}
        }
    for(i=0;i<contadorpromo;i++){
        if((promo[i]!=NULL)&&(promo[i]->devolvercolor()!=color))
            if(promo[i]->legalidad(fichas[color*16+15]->fila(),fichas[color*16+15]->columna(),tabla,posi,filai,coli,comer)&&(fichas[i]->fila()!=filaf)&&(fichas[i]->columna()!=colf)){return 0;}
    }
    return 1;
    
}



unsigned int sintaxis(char *instruccion,char &ficha,unsigned int &colf,unsigned int &filaf,unsigned int &coli,unsigned int &filai,bool &comer,bool &jaque,bool &peon,bool &color,bool &promocion,bool &enroqlargo,bool &enroqcorto){
    
    //Cogemos el caracter de la pieza
    if(((instruccion[0]=='H')||(instruccion[0]=='A')||(instruccion[0]=='C')||(instruccion[0]=='T')||(instruccion[0]=='R'))||(instruccion[0]=='D')||(('a'<=instruccion[0])&&(instruccion[0]<='h'))||(instruccion[0]=='x')||(('1'<=instruccion[0])&&(instruccion[0]<='8'))){
        ficha=instruccion[0];
        
        //Si no tiene caracter comprobamos a ver si es un peón
        if((('a'<=instruccion[0])&&(instruccion[0]<='h'))||(instruccion[0]=='x')||(('1'<=instruccion[0])&&(instruccion[0]<='8'))){
            peon=1;
            ficha='P';
            if(instruccion[0]=='x')
                comer=1;
        }
        //A continuación recopilamos todas las diferentes variedades de instrucciones que hay
        //Para el peon es igual pero restandole una posición a la instrucción
        
        //PEON O SEGUNDA LETRA
        if(('a'<=instruccion[1-peon])&&(instruccion[1-peon]<='h')){
            //TERCERA NUMERO
            if(('1'<=instruccion[2-peon])&&(instruccion[2-peon]<='8')){
                colf=instruccion[1-peon]-'a';
                filaf=instruccion[2-peon]-'1';
                //jaque
                if(instruccion[3-peon]=='+'){
                    jaque=1;
                    if(instruccion[4-peon]==0)
                        return 1;
                }
                else if(instruccion[3-peon]==0)
                    return 1;
                
            }
            //TERCERA LETRA
            else if(('a'<=instruccion[2-peon])&&(instruccion[2-peon]<='h')){
                colf=instruccion[2-peon]-'a';
                coli=instruccion[1-peon]-'a';
                //CUARTA NUMERO
                if(('1'<=instruccion[3-peon])&&(instruccion[3-peon]<='8')){
                    filaf=instruccion[3-peon]-'1';
                    if(instruccion[4-peon]=='+'){
                        jaque=1;
                        if(instruccion[5-peon]==0)
                            return 1;
                    }
                    else if(instruccion[4-peon]==0)
                        return 1;
                    
                }
                
            }
            //TERCERA X
            else if(instruccion[2-peon]=='x'){
                comer=1;
                //CUARTA LETRA
                if(('a'<=instruccion[3-peon])&&(instruccion[3-peon]<='h')){
                    colf=instruccion[3-peon]-'a';
                    coli=instruccion[1-peon]-'a';
                    //QUINTA NUMERO
                    if(('1'<=instruccion[4-peon])&&(instruccion[4-peon]<='8')){
                        filaf=instruccion[4-peon]-'1';
                        if(instruccion[5-peon]=='+'){
                            jaque=1;
                            if(instruccion[6-peon]==0)
                                return 1;
                        }
                        else if(instruccion[5-peon]==0)
                            return 1;
                        
                    }
                    
                    
                }
                
            }
            
        }
        
        //SEGUNDA NUMERO
        else if(('1'<=instruccion[1-peon])&&(instruccion[1-peon]<='8')){
            filai=instruccion[1-peon]-'1';
            //TERCERA LETRA
            if(('a'<=instruccion[2-peon])&&(instruccion[2-peon]<='h')){
                colf=instruccion[2-peon]-'a';
                //CUARTA NUMERO
                if(('1'<=instruccion[3-peon])&&(instruccion[3-peon]<='8')){
                    filaf=instruccion[3-peon]-'1';
                    if(instruccion[4-peon]=='+'){
                        jaque=1;
                        if(instruccion[5-peon]==0)
                            return 1;
                    }
                    else if(instruccion[4-peon]==0)
                        return 1;
                    
                }
            }
            
            //TERCERA X
            else if(instruccion[2-peon]=='x'){
                comer=1;
                //CUARTA LETRA
                if(('a'<=instruccion[3-peon])&&(instruccion[3-peon]<='h')){
                    colf=instruccion[3-peon]-'a';
                    //QUINTA NUMERO
                    if(('1'<=instruccion[4-peon])&&(instruccion[4-peon]<='8')){
                        filaf=instruccion[4-peon]-'1';
                        if(instruccion[5-peon]=='+'){
                            jaque=1;
                            if(instruccion[6-peon]==0)
                                return 1;
                        }
                        else if(instruccion[5-peon]==0)
                            return 1;
                        
                    }
                }
            }
        }
        
        //SEGUNDA X
        else if(instruccion[1-peon]=='x'){
            comer=1;
            //TERCERA LETRA
            if(('a'<=instruccion[2-peon])&&(instruccion[2-peon]<='h')){
                colf=instruccion[2-peon]-'a';
                //CUARTA NUMERO
                if(('1'<=instruccion[3-peon])&&(instruccion[3-peon]<='8')){
                    filaf=instruccion[3-peon]-'1';
                    if(instruccion[4-peon]=='+'){
                        jaque=1;
                        if(instruccion[5-peon]==0)
                            return 1;
                    }
                    else if(instruccion[4-peon]==0)
                        return 1;
                    
                }
            }
        }
    }
    //enroque largo
    else if(strncmp(instruccion,"0-0-0",7)==0){
        enroqlargo=1;
        return 1;
    }
    //enroque corto
    else if(strncmp(instruccion,"0-0",7)==0){
        enroqcorto=1;
        return 1;
    }
    //fin de partida por abandono
    else if(strcmp(instruccion,"=")==0)
        return 1;
    
    
    return 0;
    
}

//Función que solo imprime las fichas muertas
void imprimirmuerta(unsigned int contadorpromo){
    
    cout<<endl<<endl<<"Fichas muertas:";
    //Recorre todas las fichas no promocionadas
    for(int j=0;j<32;j++)
        if(*(fichas[j]->devolvernombre())!='P')
            fichas[j]->imprimirmuerta();
        else if(fichas[j]->devolverpromo()==0)
            fichas[j]->imprimirmuerta();
    
    //Recorre las fichas promocionadas
    for(int i=0;i<contadorpromo;i++)
        if(promo[i]!=NULL)
            promo[i]->imprimirmuerta();
    
    cout<<endl;
}

//Función que se encarga de matar a las piezas
void fcomer(unsigned int filaf,unsigned int colf,bool color,unsigned int contadorpromo){
    //Mata a las piezas que tengan la misma posición que la introducida en la instruccion
    //y que tengan color opuesto al del turno
    for(int j=0;j<32;j++)
        fichas[j]->muerte(filaf,colf,color);
    
    for(int i=0;i<contadorpromo;i++)
        if(promo[i]!=NULL)
            promo[i]->muerte(filaf,colf,color);
}

//Función que promociona las fichas
void fpromocionar(unsigned int &contadorpromo,pieza *peon){
    char fichapromocionada;
    cout<<"Introduce el caracter de la ficha a la que quieres promocionar tu peon:"<<endl;
    cin>>fichapromocionada;
    
    switch(fichapromocionada){
        case 'D': *(promo+contadorpromo)=new dama(fichapromocionada,peon);
            break;
            
        case 'C': *(promo+contadorpromo)=new caballo(fichapromocionada,peon);
            break;
            
        case 'A': *(promo+contadorpromo)=new alfil(fichapromocionada,peon);
            break;
            
        case 'T': *(promo+contadorpromo)=new torre(fichapromocionada,peon);
            break;
            
    }
    contadorpromo++;
}

//Función que introduce las direcciones de las piezas en el vector fichas
void introavectores(){
    
    //negras
    fichas[0]=&peon1n;
    fichas[1]=&peon2n;
    fichas[2]=&peon3n;
    fichas[3]=&peon4n;
    fichas[4]=&peon5n;
    fichas[5]=&peon6n;
    fichas[6]=&peon7n;
    fichas[7]=&peon8n;
    
    fichas[8]=&torre1n;
    fichas[9]=&torre2n;
    
    fichas[10]=&caballo1n;
    fichas[11]=&caballo2n;
    
    fichas[12]=&alfil1n;
    fichas[13]=&alfil2n;
    
    fichas[14]=&dama1n;
    
    fichas[15]=&rey1n;
    
    //blancas
    fichas[16]=&peon1b;
    fichas[17]=&peon2b;
    fichas[18]=&peon3b;
    fichas[19]=&peon4b;
    fichas[20]=&peon5b;
    fichas[21]=&peon6b;
    fichas[22]=&peon7b;
    fichas[23]=&peon8b;
    
    fichas[24]=&torre1b;
    fichas[25]=&torre2b;
    
    fichas[26]=&caballo1b;
    fichas[27]=&caballo2b;
    
    fichas[28]=&alfil1b;
    fichas[29]=&alfil2b;
    
    fichas[30]=&dama1b;
    
    fichas[31]=&rey1b;
    
}

//Función que engloba las primeras comprobaciones hechas a la instrucción
void primerascomp(char *instruccion,char &ficha,unsigned int &colf,unsigned int &filaf,unsigned int &coli,unsigned int &filai,bool &comer,bool &jaque,bool &peon,bool &color,bool &promocion,bool &enroqlargo,bool &enroqcorto,bool &comp,bool &error,unsigned int &turno,bool &posi){
    do {
        enroqcorto=0;
        enroqlargo=0;
        comp=1;
        comer=0;
        peon=0;
        promocion=0;
        error=0;
        posi=0;
        coli=9;
        filai=9;
        cout<<"Introduce una jugada valida:"<<endl;
        cin>> instruccion;
        //sintaxis coge la información de dentro de la instrucción y la introduce en las variables
        sintaxis(instruccion,ficha,colf, filaf, coli, filai, comer, jaque,peon,color,promocion,enroqlargo,enroqcorto);
        //si hay que comer que este llena la casilla con una pieza de color opuesto
        if(comer){
            if((tabla.leer(filaf,colf)=='0')||(tabla.leercolor(filaf,colf)==turno))
                comp=0;
        }
        //si no hay que comer que este vacia la casilla
        else if((tabla.leer(filaf,colf)!='0')&&((enroqcorto==0)&&(enroqlargo==0)))
            comp=0;
        //reconocer si me han pasado la pos inicial de la pieza
        if((coli!=9)||(filai!=9)){
            posi=1 ;
        }
        
    }while((comp==0)||sintaxis(instruccion,ficha,colf, filaf, coli, filai, comer, jaque,peon,color,promocion,enroqlargo,enroqcorto)==0);
    //no salir del bucle hasta que la instrucción este bien escrita
    
}
bool comprob_enroques(bool &color,bool &enroqlargo,bool &enroqcorto, unsigned int &colu_i,unsigned int &colu_f, unsigned int &filu,unsigned int &auxi,const unsigned int IT, const unsigned int IR, short int &bandera){
    unsigned int coluR=0;
    short int bandr=0;
    unsigned int colu_T=0;
    bandera=0;
    
    if(enroqlargo==1||enroqcorto==1){
        
        
        if((enroqlargo==1)&&(color==1)){
            colu_i=1; colu_T=2; coluR=1; filu=0; auxi=0; colu_f=4;
        }
        else if((enroqlargo==1)&&(color==0)){
            colu_i=1; colu_T=2; coluR=1; filu=7;auxi=0;colu_f=4;
        }
        else if((enroqcorto==1)&&(color==1)){
            colu_i=5; colu_T=5; coluR=6 ;filu=0;auxi=1;colu_f=7;
        }
        else if((enroqcorto==1)&&(color==0)){
            colu_i=5; colu_T=5; coluR=6; filu=7;auxi=1;colu_f=7;
        }
        
        if((fichas[color*16+IT+auxi]->devolvermov()==0)&&(fichas[color*16+IR]->devolvermov()==0)){
            for(short int j=colu_i; j<colu_f;j++)
                if(tabla.leer(filu,j)=='0') continue;
                else {
                    bandr=1;
                    break;
                }
            if(bandr==0){
                tabla.mover(fichas[color*16+IR],filu,coluR);
                tabla.mover(fichas[color*16+IT+auxi],filu,colu_T);
                return true;
            }
        }
        bandera=1;
    }
    
    return false;
}

bool tiempo_empleado(bool *color,time_t t1,time_t t2,time_t tiempo_partida[2],time_t minutos[2],time_t segundos[2],time_t *minutos_max,int *turno_pantalla, int *contador_turnos){
    time_t aux=(t2)-(t1);
    short int i;
    if(*color==1){
        i=0;
    }
    else if(*color==0){
        i=1;
    }
    
    tiempo_partida[i]=tiempo_partida[i]+aux;
    segundos[i]=(tiempo_partida[i]%60);
    minutos[i]=(tiempo_partida[i]/60);
    
    if(minutos[i]>=*minutos_max){
        cout<<"Has sobrepasado el tiempo máximo, la partida se ha terminado";
        cout<<endl;
        return false;
    }
    
    //Calculo turno cjugador blanco
    *turno_pantalla=*contador_turnos/2;
    *contador_turnos=*contador_turnos+1;
    
    cout<<endl;
    cout<<"Jugada numero:"<< *turno_pantalla;
    cout<<endl;
    cout<<endl;
    cout<<"Tiempo que llevas empleado";
    cout<<endl;
    cout<<minutos[i]<<"minuto/s"<<":"<<segundos[i]<<"segundos";
    cout<<endl;
    cout<<endl;
    return true;
}

unsigned int multiplesmov(unsigned int filaf,unsigned int colf,unsigned int filai,unsigned int coli,unsigned int indice,unsigned int total,unsigned int contadorpromo,unsigned int &i,bool color,bool posi,bool comer,char ficha){
    
    
    unsigned int numeromovs=0;
    
    //Bucle que suma las fichas originales que pueden moverse
    for(i=color*16+indice;i<(color*16+indice+total);i++)
        numeromovs+=fichas[i]->legalidad(filaf,colf,tabla,posi,filai,coli,comer);
    
    //Bucle que suma las fichas promocionadas que pueden moverse
    for(int i=0;i<contadorpromo;i++)
        if((promo[i]!=NULL)&&(promo[i]->devolvercolor()==color)&&(*promo[i]->devolvernombre()==ficha))
            numeromovs+=promo[i]->legalidad(filaf,colf,tabla,posi,filai,coli,comer);
    
    return numeromovs;
}

