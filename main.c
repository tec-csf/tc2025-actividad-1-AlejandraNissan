//Alejandra Nissan 
//A01024682
//20/08/2020

#include <stdio.h>
#include <stdlib.h>

int cupoActual = 10;
int cont = 0;


typedef struct {
    char *nombre;
    char *apellidos;
    int edad;
    char *tel;
} paciente;

paciente *camas;
int primerEspacioLibre();
void incorporarPaciente();
void pacienteCorrespondeACama(int index);
void darDeAltaPaciente(int index);
void mostrarPacientesYCama();
void numCamasDisponiblesYOcupadas();
void imprimirOpciones();


typedef void (* menu_t)();

void opcion1();
void opcion2();
void opcion3();
void opcion4();
void opcion5();

int main(int argc, const char* argv[]){
    //Inician con 10 camas
    camas = (paciente*)malloc(cupoActual*sizeof(paciente));

    menu_t * opciones = (menu_t *) malloc(5 * sizeof(menu_t));
    
    *opciones = opcion1;
    *(opciones+1) = opcion2;
    *(opciones+2) = opcion3;
    *(opciones+3) = opcion4;
    *(opciones+4) = opcion5;

    for(int i=0; i<cupoActual; i++){
        (camas+i)->nombre= NULL;
        (camas+i)->apellidos= NULL;
        (camas+i)->tel= NULL;
    }

    int opcion;

    do{
        imprimirOpciones();
        scanf("%d", &opcion);
        if (opcion > 0 && opcion <= 6) {
            (*(opciones[opcion-1]))();
        }
    }while(opcion!=0);

    //Liberar la memoria
    for(int i=0; i<cupoActual; i++){
        free((camas+i)->nombre);
        free((camas+i)->apellidos);
        free((camas+i)->tel);
    }    
    free(camas);
    free(opciones);
}

//Funciones
int primerEspacioLibre(){
    int noEntre = 1;

    for(int i=0; i<cont; i++){
        if((camas+i)==NULL||(camas+i)->nombre==NULL||(camas+i)->apellidos==NULL||(camas+i)->tel==NULL){
            noEntre = 0;
            return i;
        }
    }

    if(noEntre!=0){
        return -1;
    }
}

void incorporarPaciente(){
    char *nombre;
    char *apellidos;
    int edad;
    char *tel;
    int espacioLibre = primerEspacioLibre();
    int index;

    if(espacioLibre==-1){
        index=cont;
        if(cont>=cupoActual){
            cupoActual+=5;
            camas = (paciente*)realloc(camas, cupoActual*sizeof(paciente));
            for(int i=cont; i<cupoActual; i++){
                (camas+i)->nombre= NULL;
                (camas+i)->apellidos= NULL;
                (camas+i)->tel= NULL;                
            }
        }
        cont++;
    }
    else{
        index=espacioLibre;
    }
    (camas+index)->nombre = (char * ) malloc(sizeof(char) * 30);
    printf("Dame el nombre: \n");
    scanf(" %[^\n]", (camas+index)->nombre);
    (camas+index)->apellidos = (char * ) malloc(sizeof(char) * 50);
    printf("Dame los apellidos: \n");
    scanf(" %[^\n]", (camas+index)->apellidos);
    printf("Dame la edad: \n");
    scanf("%d", &(camas+index)->edad);
    (camas+index)->tel = (char * ) malloc(sizeof(char)*10);
    printf("Dame el teléfono: \n");
    scanf("%s", (camas+index)->tel);

    printf("El paciente fue agregado exitosamente: nombre: %s %s, edad: %d, teléfono: %s en la cama %d\n", (camas+index)->nombre, (camas+index)->apellidos, (camas+index)->edad, (camas+index)->tel, index+1);
}

void pacienteCorrespondeACama(int index){
    index--;
    if(index < 0){
        printf("Ese número de cama no existe\n");
    }
    else if(index>cupoActual-1){
        printf("El cupo actual del hospital es de %d camas, por lo que no se cuenta con esa cama todavía\n", cupoActual);
    }
    else if((camas+index)->nombre!=NULL||(camas+index)->apellidos!=NULL||(camas+index)->tel!=NULL){
        printf("Paciente de cama %d es: nombre: %s %s, edad: %d, teléfono: %s\n", index+1, (camas+index)->nombre, (camas+index)->apellidos, (camas+index)->edad, (camas+index)->tel);
    }
    else{
        printf("Ese número de cama se encuentra disponible\n");
    }
}

void darDeAltaPaciente(int index){
    index--;
    if(index<0||index>=cupoActual){
        printf("Ese número de cama no existe\n");
    }
    else if((camas+index)->nombre!=NULL||(camas+index)->apellidos!=NULL||(camas+index)->tel!=NULL){
        free((camas+index)->nombre);
        free((camas+index)->apellidos);
        free((camas+index)->tel);
        (camas+index)->nombre=NULL;
        (camas+index)->apellidos = NULL;
        (camas+index)->tel= NULL;

        printf("El paciente fue dado de alta exitosamente\n");
    }
    else{
        printf("Ese número de cama no tiene asignado ningún paciente\n");
    }    

}

void mostrarPacientesYCama(){
    for(int i=0; i<cont; i++){
        if((camas+i)->nombre!=NULL||(camas+i)->apellidos!=NULL||(camas+i)->tel!=NULL){
            printf("Paciente: %s %s, edad: %d, teléfono: %s en la cama %d\n", (camas+i)->nombre, (camas+i)->apellidos, (camas+i)->edad, (camas+i)->tel, i+1);
        }
    }    
}

void numCamasDisponiblesYOcupadas(){
    int ocupadas=0;
    for(int i=0; i<cont; i++){
        if((camas+i)->nombre!=NULL||(camas+i)->apellidos!=NULL||(camas+i)->tel!=NULL){
            ocupadas+=1;
        }
    }    

    printf("El numero de camas actuales es %d\n", cupoActual);
    printf("Disponibles: %d Ocupadas: %d\n", cupoActual-ocupadas, ocupadas);
}

void imprimirOpciones(){
    printf("Elige la opción a ejecutrar: \n");
    printf("1. Incorporar un paciente \n");  
    printf("2. Información de cierta cama (se debe dar el número de cama)\n"); 
    printf("3. Dar de alta paciente (se debe dar el número de cama)\n");  
    printf("4. Mostrar todos los pacientes y su cama correspondiente\n");  
    printf("5. Conocer num de camas disponibles y num camas ocupadas\n");
    printf("0. Finalizar\n");
}

void opcion1()
{
    incorporarPaciente();
}

void opcion2()
{
    int pacienteCama;

    printf("Dame el número de cama\n");
    scanf("%d", &pacienteCama);  
    pacienteCorrespondeACama(pacienteCama);
}

void opcion3()
{
    int pacienteCama;

    printf("Dame el número de cama\n");
    scanf("%d", &pacienteCama); 
    darDeAltaPaciente(pacienteCama); 
}

void opcion4()
{
    mostrarPacientesYCama();
}

void opcion5()
{
    numCamasDisponiblesYOcupadas();
}
