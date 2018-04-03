#include <lib/pen.h>

//embua
void embua(Pen& p, int lado){
    if(lado < 20)
        return;
    p.setThickness(3);
    p.setColor(rand()%255, rand()%255, rand()%255);
    p.walk(lado);
    p.right(90);
    embua(p, lado - 10);

    p.setColor(rand()%255, rand()%255, rand()%255);
    p.left(90);
    p.walk(-lado);
}

//arvore
void arvore(Pen& p, int lado){
    float ang = 35;
    float dec = 0.75;
    lado -= (p.rand() % 5 - 2);
    if(lado < 10)
        return;
    p.setColor(0, 255, 0);
    p.setThickness(5);
    p.walk(lado);
    p.right(ang);
    arvore(p, lado * dec);
    p.left(ang);
    arvore(p, lado * dec);
    p.left(ang);
    arvore(p, lado * dec);
    p.right(ang);
    p.walk(-lado);
    p.setColor(160, 90, 20);
}

//triangulo
void triangulo(Pen& p, int lado){
    //cores aleatorias
    p.setColor(rand()%255, rand()%255, rand()%255);

    if(lado < 7)
        return;
    for(int i =0; i<3; i++){
        p.walk(lado);
        p.right(120);
        triangulo(p,lado / 2);
    }
}

//gelo
void floquinho(Pen& p, int lado){
    p.setColor(0, 0, 255);
    if(lado < 5)
        return;
    for(int i=0;i<5;i++){

        p.walk(lado);
        p.left(72);
        p.walk(-lado);
        floquinho(p, lado / 3);
    }
    p.setColor(255, 255, 255);
}

//trigo
void trigo(Pen& p, int lado){
    if(lado < 0.5)
        return;
    p.setColor(255, 255, 255);
    for(int i=0; i<4; i++){
        p.walk(lado);
        p.right(45);
        trigo(p, lado / 3);
        p.left(90);
        trigo(p, lado / 3);
        p.right(45);
    }
    p.setColor(255, 167, 80);
    p.walk(-lado*4);
}

//quadrados
void quadrado(Pen& p, int lado){
    if(lado < 4)
        return;
    for(int i=0; i<4; i++)
        p.walk(lado);
        p.right(90);
        quadrado(p, lado);
}


//circulos
void circulo(Pen& p, int lado){
    if(lado < 4)
        return;
    p.circle(lado);


    for(int i=0; i<6; i++)
        circulo(p,lado / 6);
        p.right(60);
}

//chamada para embua
void fractalEmbua(){
    Pen p(800, 600);
    //posicao do embua
    p.setXY(350, 100);
    //faz o pincel apontar pra direita
    p.setHeading(0);
    //velocidade
    p.setSpeed(30);
    //chamada da funcao embua
    embua(p, 400);
    //espera clicar no botao de fechar
    p.wait();

}

//chamada para arvore
void fractalArvore(){
    Pen p(800, 600);
    //posicao da arvore
    p.setXY(400, 590);
    //faz o pincel apontar pra cima
    p.setHeading(90);
    //velocidade
    p.setSpeed(0);
    //chamada da funcao arvore
    arvore(p,100);
    //espera clicar no botao fechar
    p.wait();
}

//chamada da funcao triangulo
void fractalTriangulo(){
    Pen p(800, 600);
    //posicao do triangulo
    p.setXY(350, 200);
    //faz o pincel apontar pra direita
    p.setHeading(0);
    //velocidade
    p.setSpeed(30);
    //chamada da funcao triangulo
    triangulo(p, 500);
    //espera clicar no botao fechar
    p.wait();
}

//chamada da funcao floquinho (gelo)
void fractalFloquinho(){
    Pen p(800, 600);
    //posicao do floquinho
    p.setXY(400, 300);
    //faz o pincel apontar pra direita
    p.setHeading(0);
    //velocidade
    p.setSpeed(30);
    //chamada da funcao floquinho
    floquinho(p, 250);
    //espera clicar no botao fechar
    p.wait();
}

//chamada da funcao trigo
void fractalTrigo(){
    Pen p(800, 600);
    //posicao do trigo
    p.setXY(400, 590);
    //faz o pincel apontar para cima
    p.setHeading(90);
    //velocidade
    p.setSpeed(30);
    //chamada da funcao
    trigo(p, 100);
    //espera clicar no botao fechar
    p.wait();
}

//chamada da funcao quadrado
void fractalQuadrado(){
    Pen p(800, 600);
    //posicao do quadrado
    p.setXY(250, 250);
    //faz o pincel apontar pra direita
    p.setHeading(0);
    //velocidade
    p.setSpeed(3);
    //chamada da funcao quadrado
    quadrado(p, 100);
    //espera clicar no botao fechar
    p.wait();
}

//chamada da funcao circulo
void fractalCirculo(){
    Pen p(800, 600);
    //posicao do circulo
    p.setXY(500,400);
    //faz o pincel apontar pra direita
    p.setHeading(0);
    //velocidade
    p.setSpeed(3);
    //chamada da funcao circulo
    circulo(p, 150);
    //espera clicar para sair
    p.wait();
}

//chamada de todas as funcoes
int main(){
    //fractalEmbua();
    //fractalArvore();
    //fractalTriangulo();
    //fractalFloquinho();
    //fractalTrigo();
    //fractalQuadrado();
    //fractalCirculo();
    return 0;
}
