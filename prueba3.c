#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>

int check_date_duplicate();
void ingresar_paciente();
void lista_pacientes();
void eliminar_cita();
void fechacita();


struct patient{
    int cedula;
    char nombre_paciente[50];
    int enfermedad;
    char fecha_ingreso[12];
    char fecha_cita[13];
     char espe;
}p;


FILE *fp;

int main(){

    int ch;

    while(1){
        system("cls");
         printf("------FUNDACION SALUD PARA TODOS------\n");
        printf("<== Administracion de turnos Centro de Salud ==>\n");
        printf("1.Agendar Cita\n");
        printf("2.Lista de Citas\n");
        printf("3.ELiminar Citas\n");
        printf("0.Salir\n\n");
        printf("Ingrese su opcion ");
        scanf("%d", &ch);

        switch(ch){
        case 0:
            exit(0);

        case 1:
            ingresar_paciente();
            break;

        case 2:
            lista_pacientes();
            break;

        case 3:
            eliminar_cita();
            break;

        default:
            printf("Opcion invalida...\n\n");

        }
        printf("\n\nPresiona una tecla para continuar.");
        getch();
    }

    return 0;
}

void ingresar_paciente(){
    char mi_Fecha[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(mi_Fecha, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(p.fecha_ingreso, mi_Fecha);
    

    fp = fopen("patient.txt", "ab");

    printf("\nIngrese la cedula del paciente: ");
    fflush(stdin);
    scanf("%d", &p.cedula);

    printf("\nIngrese Nombre del paciente: ");
    fflush(stdin);
    gets(p.nombre_paciente);


    printf("\n------ESPECIALIDADES------\n");
        fflush(stdin);
    printf("\n0.Salir\n");
    printf("1.Medicina familiar\n");
    printf("2.Ginecologia\n");
    printf("3.Obstetricia\n");
    printf("4.Odontologia\n");
    printf("5.Pediatria\n");
    printf("6.Cuidados de enfermeria\n");
     printf("\nIngrese su opcion: ");
     scanf("%d", &p.enfermedad);
     
    switch(p.enfermedad){
        case 0:
            exit(0);

        case 1:
            fechacita();
            break;

        case 2:
            fechacita();
            break;

        case 3:
           fechacita();
            break;
        case 4:
           fechacita();
            break;
        case 5:
           fechacita();
            break;
        case 6:
           fechacita();
            break;

        default:
            printf("Opcion invalida...\n\n");
        }

     } 
    
    


void lista_pacientes(){
   
    if(p.enfermedad==1){
    p.espe='Medicina general';
    }else{
        if(p.enfermedad==2){
            p.espe='Ginecologia';
        }else{
            if(p.enfermedad==3){
        p.espe='Obstetricia';}
            else{
            if(p.enfermedad==4){
        p.espe='Odontologia';} 
        else{
            if(p.enfermedad==5){
        p.espe='Pediatria';} 
            else{
                if(p.enfermedad==6){
            p.espe='Cuidados de enfermeria';} 
            
            } 

         } 
         } 
        } 
    } 
    system("cls");
    printf("<== Lista de Citas ==>\n\n");
    printf("%-10s  %-25s %-20s %-20s %-20s %s\n", "Cedula", "Nombre Paciente", "Especialidad", "Fecha Cita", "Fecha Ingreso");
    printf("-----------------------------------------------------------------------------------------------------\n");
    
    fp = fopen("patient.txt", "rb");
    
    while(fread(&p, sizeof(p), 1, fp) == 1){
        printf("%-10d  %-25s %-20s %-20s %-20s %s\n", p.cedula, p.nombre_paciente,p.espe,p.fecha_cita,p.fecha_ingreso);
    }

    fclose(fp);
}


void eliminar_cita(){
    int id, f=0;
    system("cls");
    printf("<== Eliminar Citas ==>\n\n");
    printf("Ingrese la cedula del paciente: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("patient.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&p, sizeof(p), 1, fp) == 1){

        if(id == p.cedula){
            f=1;
        }else{
            fwrite(&p, sizeof(p), 1, ft);
        }
    }

    if(f==1){
        printf("\n\nCITA ELIMINADA");
    }else{
        printf("\n\nCita no existe el registro !");
    }

    fclose(fp);
    fclose(ft);

    remove("patient.txt");
    rename("temp.txt", "patient.txt");
  

}


int check_date_duplicate(const char* file_name) {
    struct patient buffer[100];
    int count = 0;
    FILE* file = fopen(file_name, "r");

    if (file == NULL) {
        printf("Error: no se pudo abrir el archivo %s\n", file_name);
        return -1;
    }
    while (fread(&buffer[count], sizeof(struct patient), 1, file)) {
        count++;
    }
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(buffer[i].fecha_cita, buffer[j].fecha_cita) == 0) {
                
                return 1;
            }
        }
    }

    printf("No se han encontrado fechas repetidas\n");
    return 0;
}

void fechacita(){
        printf("Ingrese la fecha para cita en formato dd/mm/aa:");
        fflush(stdin);
        gets(p.fecha_cita);
            if(check_date_duplicate("patient.txt") == 1){
                printf("\nFecha no disponible");

            fwrite(&p, sizeof(p), 1, fp);
            fclose(fp);
                
            }else{
                printf("\nCita Agendada");
                fwrite(&p, sizeof(p), 1, fp);
                fclose(fp);
                }  
 }