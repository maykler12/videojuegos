#include <iostream>
#include <winbgim.h>
#include <conio.h>
#include <chrono>
#include <iomanip>

int escala = 4;

int TAM_CUADRADO = 10*escala;
const int TAM_TABLERO_ANCHO = 20;
const int TAM_TABLERO_ALTO = 10;
const int ANCHO_PANTALLA = TAM_TABLERO_ANCHO*TAM_CUADRADO;
const int ALTO_PANTALLA = (TAM_TABLERO_ALTO+5)*TAM_CUADRADO;
int offsetX = (ANCHO_PANTALLA - TAM_TABLERO_ANCHO * TAM_CUADRADO) / 2;
int offsetY = (ALTO_PANTALLA - TAM_TABLERO_ALTO * TAM_CUADRADO) / 2;

int tablero[TAM_TABLERO_ALTO][TAM_TABLERO_ANCHO];
int jugadorX, jugadorY;
bool jugando = false;
bool cuysRecogidos[TAM_TABLERO_ALTO][TAM_TABLERO_ANCHO] = { false };
int direccionesCuy[TAM_TABLERO_ALTO] = { 0 };
int velocidadCuy = 100;
const int MAX_NIVELES = 5;
int nivelActual = 1;
int cuysRecogidosContador = 0;
int cuysRecogidosContadorNivelActual = 0;


void mpj(int x,int y,double e,int color, int direccion){//Main Pj

    if(direccion == 1){
        setcolor(6);
        setfillstyle(9,color);
        fillellipse(x+11*e,y+11*e,7*e,7*e);//Cuerpo
        fillellipse(x+8*e,y+7*e,6*e,6*e);//Cara
        setcolor(15);
        setfillstyle(1,0);
        fillellipse(x+8*e,y+6*e,1*e,1*e);
        fillellipse(x+5*e,y+6*e,1*e,1*e);//Ojos
        setcolor(7);
        setfillstyle(9,7);
        fillellipse(x+7*e,y+10*e,3*e,2*e);//BOCA
        setcolor(0);
        setfillstyle(9,12);
        fillellipse(x+6*e,y+17*e,2*e,1*e);
        fillellipse(x+11*e,y+17*e,2*e,1*e);
        fillellipse(x+11*e,y+5*e,1*e,3*e);//oreja
        fillellipse(x+3*e,y+5*e,1*e,3*e);//oreja
        fillellipse(x+6*e,y+9*e,1*e,1*e);//nariz
    }else if(direccion == 0){
        setcolor(6);
        setfillstyle(9,color);
        fillellipse(x+9*e,y+11*e,7*e,7*e);
        fillellipse(x+12*e,y+7*e,6*e,6*e);//Cuerpo
        setcolor(15);
        setfillstyle(1,0);
        fillellipse(x+12*e,y+6*e,1*e,1*e);
        fillellipse(x+15*e,y+6*e,1*e,1*e);//Ojos
        setcolor(7);
        setfillstyle(9,7);
        fillellipse(x+13*e,y+10*e,3*e,2*e);//BOCA
        setcolor(0);
        setfillstyle(1,0);
        setcolor(0);
        setfillstyle(9,12);
        fillellipse(x+14*e,y+17*e,2*e,1*e);
        fillellipse(x+9*e,y+17*e,2*e,1*e);
        fillellipse(x+9*e,y+5*e,1*e,3*e);
        fillellipse(x+17.5*e,y+5*e,1*e,3*e);
        fillellipse(x+13.5*e,y+9*e,1*e,1*e);
    }else if(direccion == 2){
        setcolor(6);
        setfillstyle(9,color);
        fillellipse(x+10*e,y+11*e,7*e,7*e);//Cuerpo
        fillellipse(x+10*e,y+7*e,6*e,6*e);//Cara
        setcolor(15);
        setfillstyle(1,0);
        fillellipse(x+8*e,y+6*e,1*e,1*e);
        fillellipse(x+12*e,y+6*e,1*e,1*e);//Ojos
        setcolor(7);
        setfillstyle(9,7);
        fillellipse(x+10*e,y+10*e,3*e,2*e);//BOCA
        setcolor(0);
        setfillstyle(9,12);
        fillellipse(x+13*e,y+17*e,2*e,1*e);//pata
        fillellipse(x+7*e,y+17*e,2*e,1*e);//pata
        fillellipse(x+4.5*e,y+5*e,1*e,3*e);//oreja
        fillellipse(x+15.5*e,y+5*e,1*e,3*e);//oreja
        fillellipse(x+10*e,y+9*e,1*e,1*e);//nariz
    }else{
        setcolor(0);
        setfillstyle(9,color);
        fillellipse(x+13*e,y+18*e,2*e,1*e);//pata
        fillellipse(x+7*e,y+18*e,2*e,1*e);//pata
        fillellipse(x+4.5*e,y+5*e,1*e,3*e);//oreja
        fillellipse(x+15.5*e,y+5*e,1*e,3*e);//oreja
        setcolor(6);
        setfillstyle(9,color);
        fillellipse(x+10*e,y+7*e,6*e,6*e);//Cara
        fillellipse(x+10*e,y+11*e,7*e,7*e);//Cuerpo
        setcolor(7);
        setfillstyle(9,7);
        fillellipse(x+10*e,y+9*e,4*e,2*e);//Mancha de espalda
    }
}
void muro(int x,int y,int e,int color){
        e=e/6;
        rectangle(x+2,y+2,x+e-2,y+e-2);
        rectangle(x+e/4,y+e/4,x+3*e/4,y+3*e/4);
        setcolor(COLOR(255,81,28));
        setfillstyle(1,COLOR(255,81,28));
        bar(x,y,x+6*e,y+6*e);

        setcolor(COLOR(89,11,11));
        setfillstyle(1,COLOR(89,11,11));
        int g=1;
        for(int i=0;i<6;i++){
            bar(x,(y-g)+i*e,x+6*e,(y+g)+i*e);
            if(i==0 || i==2 || i==4){
                //0,2,4,6
                bar((x-g)+2*e,y+i*e,(x+g)+2*e,y+(i+1)*e);
                bar((x-g)+4*e,y+i*e,(x+g)+4*e,y+(i+1)*e);
            }else if(i==1 || i==3 || i==5){
                //1,3,5
                bar((x-g)+1*e,y+i*e,(x+g)+1*e,y+(i+1)*e);
                bar((x-g)+3*e,y+i*e,(x+g)+3*e,y+(i+1)*e);
                bar((x-g)+5*e,y+i*e,(x+g)+5*e,y+(i+1)*e);
            }
        }
}
void comida(int x,int y,int e,int color){
        setcolor(COLOR(226,6,44));
        setfillstyle(1,COLOR(226,6,44));
        e=e/6;
        int pX_1[]={x+1*e,y+2*e,x+2*e,y+1.5*e,x+3*e,y+2*e,x+4*e,y+1.5*e,x+5*e,y+2*e,x+5*e,y+4*e,x+4*e,y+5*e,x+3*e,y+4.5*e,x+2*e,y+5*e,x+1*e,y+4*e,x+1*e,y+2*e};
        fillpoly(11,pX_1);

        setcolor(COLOR(255,181,182));
        setfillstyle(1,COLOR(255,181,182));
        int pX_2[]={x+4*e,y+2*e,x+4.5*e,y+2.5*e,x+4*e,y+3*e,x+3.5*e,y+2.5*e,x+4*e,y+2*e};
        fillpoly(5,pX_2);

        setcolor(COLOR(140,95,69));
        setfillstyle(1,COLOR(140,95,69));
        int pX_3[]={x+3*e,y+0.5*e,x+3*e,y+2*e,x+2.5*e,y+0.5*e,x+3*e,y+0.5*e};
        fillpoly(4,pX_3);

        setcolor(COLOR(127,166,45));
        setfillstyle(1,COLOR(127,166,45));
        int pX_4[]={x+3*e,y+1.5*e,x+4*e,y+0.5*e,x+4*e,y+1.5*e,x+3*e,y+1.5*e};
        fillpoly(4,pX_4);
}
void dibujarCuys(int direccion, int x, int y, int color){
        int posX = offsetX+x*TAM_CUADRADO;
        int posY = offsetY+y*TAM_CUADRADO;

        mpj(posX,posY,0.5*escala,color,direccion);
}

void iniciarTablero() {
    for (int y = 0; y < TAM_TABLERO_ALTO; y++) {
        for (int x = 0; x < TAM_TABLERO_ANCHO; x++) {
            tablero[y][x] = 0;
        }
        direccionesCuy[y] = 0;
    }
}

void dibujarMenu(int selectedItem) {
    setbkcolor(COLOR(255, 255, 255));
    cleardevice();

    settextstyle(DEFAULT_FONT, HORIZ_DIR, escala);
    setcolor(COLOR(0, 0, 0));
    outtextxy(TAM_CUADRADO*4, TAM_CUADRADO*3, "Juego de Cuys");

    settextstyle(DEFAULT_FONT, HORIZ_DIR, escala);
    setcolor(COLOR(0, 0, 0));

    if (selectedItem == 1) {
        setcolor(COLOR(219, 137, 4));
        outtextxy(TAM_CUADRADO*5, TAM_CUADRADO*5, "   Jugar");
        setcolor(COLOR(0, 0, 0));
        outtextxy(TAM_CUADRADO*5, TAM_CUADRADO*7, "   Salir");
        mpj(TAM_CUADRADO*6,TAM_CUADRADO*5,0.5*escala,12,2);
    } else if (selectedItem == 2) {
        outtextxy(TAM_CUADRADO*5, TAM_CUADRADO*5, "   Jugar");
        setcolor(COLOR(219, 137, 4));
        outtextxy(TAM_CUADRADO*5, TAM_CUADRADO*7, "   Salir");
        mpj(TAM_CUADRADO*6,TAM_CUADRADO*7,0.5*escala,12,3);
    }
    comida(offsetX+TAM_CUADRADO*15,offsetY,20*escala,6);
}

void dibujarTablero() {

    settextstyle(DEFAULT_FONT, HORIZ_DIR, escala);
    setcolor(COLOR(255, 255, 255));
    outtextxy(offsetX, offsetY - (TAM_CUADRADO*2), ("Nivel " + std::to_string(nivelActual)).c_str());

    int cuysRestantes = 0;
    for (int y = 0; y < TAM_TABLERO_ALTO; y++) {
        for (int x = 0; x < TAM_TABLERO_ANCHO; x++) {
            if (tablero[y][x] >= 1 && tablero[y][x] <= 4) {
                cuysRestantes++;
            }
        }
    }

    std::ostringstream ss;
    ss << "Cuys Hambrientos: " << cuysRestantes;
    outtextxy(offsetX, offsetY + TAM_CUADRADO*(TAM_TABLERO_ALTO+1), ss.str().c_str());

    for (int y = 0; y < TAM_TABLERO_ALTO; y++) {
        for (int x = 0; x < TAM_TABLERO_ANCHO; x++) {
            int posX = offsetX + x * TAM_CUADRADO;
            int posY = offsetY + y * TAM_CUADRADO;
            if(y==0){
                muro(offsetX+TAM_CUADRADO*x,offsetY-TAM_CUADRADO,10*escala,6);
                muro(offsetX+TAM_CUADRADO*x,offsetY+TAM_CUADRADO*TAM_TABLERO_ALTO,10*escala,6);
            }
            if (y % 2 == 0) {
                setfillstyle(SOLID_FILL, COLOR(23, 120, 14));
            } else {
                setfillstyle(SOLID_FILL, COLOR(61, 151, 6));
            }

            bar(posX, posY, posX + TAM_CUADRADO, posY + TAM_CUADRADO);

            if (tablero[y][x] != 0) {
                int colorCuy = y+1;
                if (tablero[y][x] == 5) {
                    setfillstyle(SOLID_FILL, COLOR(0, 0, 0)); // Cuy Negro
                    colorCuy = 0;
                }
                dibujarCuys(direccionesCuy[y],x,y,colorCuy);
            }
        }
    }
    int jugadorPosX = offsetX + jugadorX * TAM_CUADRADO;
    int jugadorPosY = offsetY + jugadorY * TAM_CUADRADO;
    comida(jugadorPosX,jugadorPosY,10*escala,6);
}

void moverJugador(int dx, int dy) {
    int nuevaX = jugadorX + dx;
    int nuevaY = jugadorY + dy;

    if (nuevaX >= 0 && nuevaX < TAM_TABLERO_ANCHO && nuevaY >= 0 && nuevaY < TAM_TABLERO_ALTO) {
        jugadorX = nuevaX;
        jugadorY = nuevaY;
    }
}

void niveles(int num) {
    jugadorX = TAM_TABLERO_ANCHO / 2;
    jugadorY = 0;
    cuysRecogidosContador = 0;
    iniciarTablero();
    switch (num) {
    case 1:
        velocidadCuy = 100;
        tablero[1][0] = 1;
        tablero[3][0] = 1;
        tablero[5][0] = 1;
        tablero[7][0] = 1;
        break;
    case 2:
        velocidadCuy = 90;
        tablero[1][0] = 1;
        tablero[2][TAM_TABLERO_ANCHO-1] = 2;
        tablero[3][0] = 1;
        tablero[4][TAM_TABLERO_ANCHO-1] = 4;
        tablero[5][0] = 1;
        tablero[6][TAM_TABLERO_ANCHO-1] = 2;
        tablero[7][0] = 1;
        tablero[8][TAM_TABLERO_ANCHO-1] = 4;
        break;
    case 3:
        velocidadCuy = 80;
        tablero[1][0] = 1;
        tablero[2][10] = 1;
        tablero[3][19] = 1;
        tablero[4][0] = 1;
        tablero[5][10] = 1;
        tablero[6][19] = 1;
        tablero[7][0] = 1;
        tablero[8][10] = 1;
        tablero[9][19] = 1;
        break;
    case 4:
        velocidadCuy = 70;
        tablero[1][10] = 1;
        tablero[2][15] = 1;
        tablero[3][0] = 1;
        tablero[4][5] = 1;
        tablero[5][12] = 1;
        tablero[6][19] = 1;
        tablero[7][7] = 1;
        tablero[8][11] = 1;
        tablero[9][17] = 1;
        break;
    case 5:
        velocidadCuy = 60;
        tablero[0][19] = 1;
        tablero[1][10] = 1;
        tablero[2][15] = 1;
        tablero[3][0] = 1;
        tablero[4][5] = 1;
        tablero[5][12] = 1;
        tablero[6][19] = 1;
        tablero[7][7] = 1;
        tablero[8][11] = 1;
        tablero[9][17] = 1;
        break;
    default:
        iniciarTablero();
        nivelActual = 0;
        break;
    }
}

void recogerCuy() {
    if (tablero[jugadorY][jugadorX] >= 1 && tablero[jugadorY][jugadorX] <= 4) {
        cuysRecogidos[jugadorY][jugadorX] = true;
        cuysRecogidosContador++;

        int cuysRestantes = 0;
        for (int y = 0; y < TAM_TABLERO_ALTO; y++) {
            for (int x = 0; x < TAM_TABLERO_ANCHO; x++) {
                if (tablero[y][x] >= 1 && tablero[y][x] <= 4) {
                    cuysRestantes++;
                }
            }
        }
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        setcolor(COLOR(0, 0, 0));
        outtextxy(offsetX, offsetY + TAM_TABLERO_ALTO * TAM_CUADRADO + 10, ("Cuys restantes: " + std::to_string(cuysRestantes)).c_str());
    }
}

void actualizarCuys() {
    static auto ultimoTiempo = std::chrono::high_resolution_clock::now();
    auto tiempoActual = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(tiempoActual - ultimoTiempo);
    int tiempoTranscurrido = duracion.count();

    if (tiempoTranscurrido >= velocidadCuy) {//EL tiempo que tarda en re dibujar el cuy
        ultimoTiempo = tiempoActual;

        for (int y = 0; y < TAM_TABLERO_ALTO; y++) {
            for (int x = 0; x < TAM_TABLERO_ANCHO; x++) {
                if (tablero[y][x] >= 1 && tablero[y][x] <= 5) {
                    if (x == jugadorX && y == jugadorY) {
                        jugadorX = TAM_TABLERO_ANCHO / 2;
                        jugadorY = 0;
                        if (tablero[y][x] == 5) {
                            jugando = false;
                            niveles(6);
                        } else {
                            tablero[y][x] = 5;
                        }
                    }
                    if (direccionesCuy[y] == 0) {
                        if (x == TAM_TABLERO_ANCHO - 1) {
                            direccionesCuy[y] = 1;
                        } else {
                            tablero[y][x + 1] = tablero[y][x];
                            tablero[y][x] = 0;
                            direccionesCuy[y] = 0;
                        }
                    } else {
                        if (x == 0) {
                            direccionesCuy[y] = 0;
                        } else {
                            tablero[y][x - 1] = tablero[y][x];
                            tablero[y][x] = 0;
                            direccionesCuy[y] = 1;
                        }
                    }

                    break;
                }
            }
        }
    }
}
int main() {
    initwindow(ANCHO_PANTALLA, ALTO_PANTALLA);

    bool salirDelJuego = false;
    int itemSeleccionado = 1;
    jugadorX = TAM_TABLERO_ANCHO / 2;
    jugadorY = 0;
    iniciarTablero();

    niveles(nivelActual);
    int cuysRecogidosContador = 0;

    while (!salirDelJuego) {
        if (!jugando) {
            dibujarMenu(itemSeleccionado);
        } else {
            dibujarTablero();
            actualizarCuys();
            int cuysTotales = 0;
            for (int y = 0; y < TAM_TABLERO_ALTO; y++) {
                for (int x = 0; x < TAM_TABLERO_ANCHO; x++) {
                    if (tablero[y][x] >= 1 && tablero[y][x] <= 4) {
                        cuysTotales++;
                    }
                }
            }
            if (cuysTotales == 0) {//Ganado (1)
                cuysRecogidosContadorNivelActual = 0;
                nivelActual++;

                if (nivelActual <= MAX_NIVELES) {
                    iniciarTablero();
                    niveles(nivelActual);
                } else {
                    jugando = false;
                    setbkcolor(COLOR(255, 255, 255));
                    cleardevice();

                    settextstyle(DEFAULT_FONT, HORIZ_DIR, escala);
                    setcolor(COLOR(0, 0, 0));
                    outtextxy(TAM_CUADRADO*5, TAM_CUADRADO*6, "¡Has ganado!");
                    delay(5000);
                }
            }
        }

        if (kbhit()) {
            char tecla = getch();
            if (!jugando) {
                if (tecla == 72 ||tecla == 'w' ||tecla == 'W') {
                    itemSeleccionado = (itemSeleccionado == 1) ? 2 : 1;
                } else if (tecla == 80 ||tecla == 's' ||tecla == 'S') {
                    itemSeleccionado = (itemSeleccionado == 1) ? 2 : 1;
                } else if (tecla == 13) {
                    if (itemSeleccionado == 1) {
                        jugando = true;
                        setbkcolor(COLOR(0, 0, 0));
                        cleardevice();
                    } else if (itemSeleccionado == 2) {
                        salirDelJuego = true;
                    }
                }
            } else {
                if (tecla == 27) {
                    jugando = false;
                    setbkcolor(COLOR(255, 255, 255));
                    cleardevice();
                } else if (tecla == 75 ||tecla == 'a' ||tecla == 'A') {
                    moverJugador(-1, 0);
                    recogerCuy();
                } else if (tecla == 77 ||tecla == 'd' ||tecla == 'D') {
                    moverJugador(1, 0);
                    recogerCuy();
                } else if (tecla == 72 ||tecla == 'w' ||tecla == 'W') {
                    moverJugador(0, -1);
                    recogerCuy();
                } else if (tecla == 80 ||tecla == 's' ||tecla == 'S') {
                    moverJugador(0, 1);
                    recogerCuy();
                }
            }
        }
        delay(50);
    }

    closegraph();
    return 0;
}
