#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct cita
{
int id;
char nom[50];
char cita[30];
}e;

FILE *fc;
int main(){

    int x;

    while(1){
        system("cls");
        printf("<== Sistema de admiciones ==>\n");
        printf("1.Agendar cita\n");
        printf("2.lista de citas\n");
        printf("3.Eliminar cita\n");
        printf("0.salir\n\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &x);

        switch(x){
        case 0:
            exit(0);

        case 1:
            admitPatient();
            break;

        case 2:
            patientList();
            break;

        case 3:
            dischargePatient();
            break;
        default:
            printf("Opcion no valida...\n\n");

        }
        printf("\n\nPrecione cualquier tecla para continuar...");
        getch();
    }

    return 0;
}

void admitPatient(){
    fc =fopen("citas.txt","ab");
    printf("Ingrece Id: \n");
   scanf("%d", &e.id);

    printf("Ingrese nombre del paciente: \n");
    fflush(stdin);
    gets(e.nom);
    system("cls");
    printf("\n");
    printf("\n");
    printf("ingresar con la siguiente estructura DD/MM/AA HH:MM \n");
    printf("Recuerde ingresar solo horas completas, ejemplo: 01:00 \n");
    printf("No ingresar horas no exactas, ejemplo 01:30,01:25,etc \n");
    printf("ya que el tiempo de consulta entre pacientes es de exactamente 1 hora \n");
    printf("Y las consultas empiezan a las 07:00 hasta las 21:00\n");
    printf("ingrese dia de la cita: \n");
    fflush(stdin);
    gets(e.cita);

    if(validacion("citas.txt") == 1){
    	printf("\nFecha no disponible");
    fclose(fc);
    	
	}else{
		printf("\nCita Agendada");
    	fwrite(&e, sizeof(e), 1, fc);
    	fclose(fc);
	}
}

void patientList(){

    printf("<== Lista de pacientes ==>\n\n");
    printf("%-10s %-30s %-30s \n", "ID", "Nombre","cita");
    printf("----------------------------------------------------------------------------------------------------------\n");
    fc = fopen("citas.txt", "rb");
    while(fread(&e, sizeof(e), 1, fc) == 1){
        printf("%-10d %-30s %-30s \n",e.id,e.nom,e.cita);
    }
    fclose(fc); 
}


void dischargePatient(){
    int id, f=0;
    system("cls");
    printf("<== Eliminar pacientes ==>\n\n");
    printf("Ingrese el ID del paciente que quiere eliminare: ");
    scanf("%d", &id);

    FILE *ft;

    fc = fopen("citas.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&e, sizeof(e), 1, fc) == 1){

        if(id == e.id){
            f=1;
        }else{
            fwrite(&e, sizeof(e), 1, ft);
        }
    }

    if(f==1){
        printf("\n\nPaciente eliminado exitosamente.");
    }else{
        printf("\n\nPaciente no encontrado !");
    }

    fclose(fc);
    fclose(ft);

    remove("citas.txt");
    rename("temp.txt", "citas.txt");

}

int validacion(const char* comprobacion) {
    struct cita vector [100];
    int cont = 0;
    FILE* file = fopen(comprobacion, "r");

    if (file == NULL) {
        printf("Error: no se pudo abrir el archivo %s\n", comprobacion);
        return -1;
    }
    while (fread(&vector[cont], sizeof(struct cita), 1, file)) {
        cont++;
    }
    for (int i = 0; i < cont; i++) {
        for (int j = i + 1; j < cont; j++) {
            if (strcmp(vector[i].cita, vector[j].cita) == 0) {
                
                return 1;
            }
        }
    }

    printf("No se han encontrado fechas repetidas\n");
return 0;
}