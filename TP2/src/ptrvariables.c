#include <stdio.h>

int main(){
    // Char

    char a[7]="Bonjour";
    char *ptr = &a[0];

    for (int i=1 ; i<sizeof(a)+1;i++){
        printf("ptr = %x\n",*ptr);
        ptr=ptr+1;
    }

    // Short

    short s = 30000;
    void *sptr = &s;

    printf("sptr = %x %x\n",*((char*)sptr+1),*((char*)sptr));

    // Float

    float f = 1;
    void *fptr = &f;

    printf("fptr = %x %x %x %x\n",*((unsigned char*)fptr+3),*((unsigned char*)fptr+2),*((unsigned char*)fptr+1),*((unsigned char*)fptr));

    // Int

    int entier = 30000;
    void *iptr = &entier;


    printf("iptr = %x %x %x %x\n",*(( char*)iptr+3),*((char*)iptr+2),*((char*)iptr+1),*((char*)iptr));
    

    // Double

    double dou = 3E-12;
    void *dptr = &dou;
    printf("dptr = %x %x %x %x %x %x %x %x\n",*((unsigned char*)dptr+7),*((unsigned char*)dptr+6),*((unsigned char*)dptr+5),*((unsigned char*)dptr+4),*((unsigned char*)dptr+3),*((unsigned char*)dptr+2),*((unsigned char*)dptr+1),*((unsigned char*)dptr));

}