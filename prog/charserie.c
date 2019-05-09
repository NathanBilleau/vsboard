#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>


int main(int argc, char *argv[])
{

int vitesse;
char port[7];
char caractere;


if(argc < 4){
    printf("Usage: sudo ./charserie <port> <vitesse de transmission> <caractere>\n");
    printf("exemple : sudo ./charserie ttyAMA0 9600 1\n");
    printf("envoie sur le port ttyAMA0 le caractere 1 a une vitesse de 9600 bauds\n");
	printf("avec un adaptaeur usb rs232 utiliser le port ttyUSB0\n");
	printf("exemple : sudo ./charserie ttyUSB0 9600 1\n");
	
    return 1;
  }
 /* 
 //debug 
 printf("nb d'arguments %d",argc);   printf("\n");
  printf(argv[0]);   printf("\n");//argv[0] c'est le fichier executable
  printf(argv[1]);   printf("\n");//port
  printf(argv[2]);   printf("\n");//vitesse
  printf(argv[3]);   printf("\n\n");//car
 */ 
 
 //debug 
 
 sprintf(port,"/dev/%s",argv[1]);   //concatenation
//  printf(port);   printf("\n");
  vitesse = atoi (argv[2]);
//  printf("%d",vitesse);   printf("\n");
  caractere=argv[3][0];
//  printf("%c",caractere);   printf("\n");


if (wiringPiSetup()==-1) return 1;


//int hd=serialOpen("/dev/ttyAMA0",9600);
int hd=serialOpen(port,vitesse);
if (hd==-1) {
           printf("erreur ouverture port serie\n"); 
           return 1;
           }





//serialPutchar(hd,'A');
serialPutchar(hd,caractere);
//if (serialDataAvail(hd)>>1) printf("retour %d\n",serialGetchar(hd));
serialClose(hd);

return 0;
}
