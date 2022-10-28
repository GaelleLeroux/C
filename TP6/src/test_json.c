#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str = "[{\"code\": \"message\", \"valeurs\": [\"Salut à tous c'est Fanta\"]},{\"code\" : \"couleurs\",\"valeurs\" : [\"sunflower.bmp\",\"29\"]}]";

int main()
{
  long value;
  char tempo[1024];
  char temp[1024];
  while (str){
    str = strstr(str, "\"code\"");
    if (str == NULL) {
            break;
        }
    str = strchr(str, ':');
        if (str == NULL) {
            break;
        }
    str++;
    //strcpy(temp,*str);
    memset(tempo, 0, sizeof(tempo));
    strcat(tempo, *str);
    printf("tempo : %s\n", tempo);
    if (*str == ',') {
            break;
        }
    printf("tempo : %s\n", tempo);
  }
  return 0;
}