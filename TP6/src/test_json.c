#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str = "[{\"code\": \"message\", \"valeurs\": [\"Salut à tous c'est Fanta\"]},{\"code\": \"couleurs\",\"valeurs\": [\"sunflower.bmp\",\"29\"]}]";

int main()
{
  long value;
  char check[1024];
  char temp[1024];
  char mess[11]="\"message\"";
  char coul[11]="\"couleurs\"";
  char data[1024];
  char contenu[1024];
  char arg1[1024];
  char arg2[1024];
  int ok =0;
  while (str){
    memset(data,0,sizeof(data));
    str = strstr(str, "\"code\"");
    if (str == NULL) {
            break;
        }
    str = strchr(str, ':');
        if (str == NULL) {
            break;
        }
    str++;
    str++;
    memset(check, 0, sizeof(check));
    while (*str != ',') {
            memset(temp,0,sizeof(temp));
            temp[0]=*str;
            strcat(check, temp);
            str++;
        }

    if (strcmp(&mess[0],&check[0])==0){
      strcpy(data, "message: ");
      str = strstr(str, "\"valeurs\"");
      str = strchr(str, ':');
      str++;
      str++;
      str++;
      memset(contenu, 0, sizeof(contenu));
      while (*str != ']') {
              memset(temp,0,sizeof(temp));
              temp[0]=*str;
              strcat(contenu, temp);
              str++;
          }
      strcat(data,contenu);

      printf("data : %s\n",data);
    }
    if (strcmp(&coul[0],&check[0])==0){
      memset(arg1,0,sizeof(arg1));
      memset(arg2,0,sizeof(arg2));
      str = strstr(str, "\"valeurs\"");
      str = strchr(str, ':');
      str++;
      str++;
      str++;
      
      while(*str!=']') {
        memset(contenu, 0, sizeof(contenu));
        while((*str!=',') && (*str != ']') ){
              memset(temp,0,sizeof(temp));
              temp[0]=*str;
              strcat(contenu, temp);
              //printf("contenu %s",contenu);
              printf("str : %c\n",*str);
              str++;
          }
        if (ok==0){
          strcat(arg1,contenu);
          printf("arg1 : %s\n",arg1);
          str++;
          ok+=1;
        }
        else{
          strcat(arg2,contenu);  
          printf("arg2 : %s\n",arg2);
        }
      }
    }
    
  }
  return 0;
}