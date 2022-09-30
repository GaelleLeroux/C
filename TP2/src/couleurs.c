#include <stdio.h>
#include <string.h>

int main(){
    typedef struct details{
        short rouge;
        short vert;
        short bleu;
        short alpha;
    }details;

    details couleur[10];

    couleur[0].rouge = 0x31;
    couleur[0].vert = 0xd9;
    couleur[0].bleu = 0xdc;
    couleur[0].alpha = 0x7f;

    couleur[1].rouge = 0xeb;
    couleur[1].vert = 0x8e;
    couleur[1].bleu = 0x16;
    couleur[1].alpha = 0x7f;

    couleur[2].rouge = 0xed;
    couleur[2].vert = 0x96;
    couleur[2].bleu = 0xee;
    couleur[2].alpha = 0x7f;

    couleur[3].rouge = 0x86;
    couleur[3].vert = 0xe8;
    couleur[3].bleu = 0x6c;
    couleur[3].alpha = 0x7f;

    couleur[4].rouge = 0xb6;
    couleur[4].vert = 0x36;
    couleur[4].bleu = 0x1c;
    couleur[4].alpha = 0x7f;

    couleur[5].rouge = 0x5;
    couleur[5].vert = 0x5c;
    couleur[5].bleu = 0x85;
    couleur[5].alpha = 0x7f;

    couleur[6].rouge = 0x67;
    couleur[6].vert = 0x9;
    couleur[6].bleu = 0x95;
    couleur[6].alpha = 0x7f;

    couleur[7].rouge = 0xe5;
    couleur[7].vert = 0x12;
    couleur[7].bleu = 0x62;
    couleur[7].alpha = 0x7f;

    couleur[8].rouge = 0xe7;
    couleur[8].vert = 0xe3;
    couleur[8].bleu = 0xe5;
    couleur[8].alpha = 0x7f;

    couleur[9].rouge = 0xee;
    couleur[9].vert = 0xdc;
    couleur[9].bleu = 0x3;
    couleur[9].alpha = 0x7f;

    for (int i = 0; i < 10; i++){
        printf("r = 0x%x, v = 0x%x, b = 0x%x, a = 0x%x \n",couleur[i].rouge,couleur[i].vert,couleur[i].bleu,couleur[i].alpha);
    }
    return 0;
}