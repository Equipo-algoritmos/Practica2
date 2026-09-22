#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

float calcularMediana(int arreglo[], int m){
	float mediana;
	int r = m/2;
	if ((m%2)==0) //el arreglo es par
	{
		mediana = ((float)arreglo[r]+(float)arreglo[r-1])/2.0;
	}
	else if((m%2)!=0){
		mediana = arreglo[r];
	}
	return mediana;
}

void printArr(int arreglo[], int m, char *msj){
	printf("%s|", msj);
	for (int i = 0; i < m; ++i)
	{
		printf(" %5d |", arreglo[i]);
		if(((i+1)%10==0)&&i!=(m-1))
			printf("\n|");
	}
}

int generarRandom(){
	return rand() % 201 - 100;
}

void llenarArreglo(int arreglo[], int m, char *select){
    if (select == "random"){
        for (int i = 0; i < m; i++){
            arreglo[i] = generarRandom();
        }
    }
    if (select == "cero"){
        for (int i = 0; i < m; i++){
            arreglo[i] = 0;
        }
    }
    if (select == "ordenado")
    {
        for (int i = 0; i < m; i++){
            arreglo[i] = i+1;
        }
    }
    if (select == "invertido")
    {
        for (int i = 0; i < m; i++){
            arreglo[i] = m-i;
        }
    }
}

void iniciarArr(int arreglo[], int m, int E){
        switch (E){
        case 1:
            llenarArreglo(arreglo, m, "ordenado");
            break;
        case 2:
            llenarArreglo(arreglo, m, "invertido");
            break;
        case 3:
            llenarArreglo(arreglo, m, "random");
            break;
    }
}

int pedirEntero(char msj[]){
	printf("%s", msj);
    int numero;
    while (1)
    {
        if (scanf("%d", &numero) == 1)
        {
            while (getchar()!='\n');
            return numero;
        }
        printf("\nEntrada invalida. Ingresa un numero entero: ");
        while (getchar() != '\n');
    }
}

    //INSERCION

void insercion(int arreglo[], int m){
    int i, j, key;
    for (j = 1; j < m; j++){
        key = arreglo[j];
        i = j - 1;
        while ((i > -1) && (arreglo[i] > key)){
            arreglo[i + 1] = arreglo[i];
            i = i - 1;
        }
        arreglo[i + 1] = key;
    }
}

void insercionPasos(int arreglo[], int m){
    int copia[m];
    llenarArreglo(copia, m, "cero");
    printf("\n\n%-84s%s\n", "Arreglo Ordenado", "Datos por Ordenar");
    for (int j = 0; j < m; j++){
        int key = arreglo[j];
        int i = j - 1;
        while (i >= 0 && copia[i] > key){
            copia[i + 1] = copia[i];
            i--;
        }
        copia[i + 1] = key;
        printArr(copia, j + 1, "");
        for (int e = 0; e < 84 - (1 + 8 * (j + 1)); e++){
            printf(" ");
        }
        if (j + 1 < m){
            printArr(arreglo + j + 1, m - j - 1, "");
        }
        printf("\n");
    }
    for (int i = 0; i < m; i++){
        arreglo[i] = copia[i];
    }
}

    //BURBUJA

void burbuja(int arreglo[], int m){
    int aux,b;
    for (int j = 0; j < m-1; j++)
    {
        b=0;
        for (int i = 0; i < m-1-j; i++)
        {
            if(arreglo[i]>arreglo[i+1]){
                aux=arreglo[i];
                arreglo[i]=arreglo[i+1];
                arreglo[i+1]=aux;
                b=1;
            }
        }
        if(b==0)
                return;
    }
}

void burbujaPasos(int arreglo[], int m){
    int b;
    printArr(arreglo, m, "\n\nInicial:  ");
    printf("\n");
    for (int j = 0; j < m - 1; j++){
        b=0;
        for (int i = 0; i < m - 1-j; i++){
            if (arreglo[i] > arreglo[i + 1]){
                int aux = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = aux;
                b=1;
            }
        }
        if(b==0)
            return;
        printf("Pasada %d: ", j + 1);
        printArr(arreglo, m, "");
        printf("\n");
    }
}


    //SELECCION

void seleccion(int arreglo[], int m){
    int min,k,j;
    for (j = 0; j < m-1; j++)
    {
        min=arreglo[j];
        k=j;
        for (int i = j+1; i < m; i++)
        {
            if(arreglo[i]<min)
            {
                min = arreglo[i];
                k=i;
            }
        }
    if (k!=j)
    {
        arreglo[k]=arreglo[j];
        arreglo[j]=min;
    }
    }
}

void seleccionPasos(int arreglo[], int m){
    int min, k;
    printArr(arreglo, m, "\n\nInicial:  ");
    printf("\n");
    for (int j = 0; j < m - 1; j++){
        min = arreglo[j];
        k = j;
        for (int i = j + 1; i < m; i++){
            if (arreglo[i] < min){
                min = arreglo[i];
                k = i;
            }
        }
        if (k != j){
            arreglo[k] = arreglo[j];
            arreglo[j] = min;
        }
        printf("Pasada %d: ", j + 1);
        printArr(arreglo, m, "");
        printf("\n");
    }
}

    //MEZCLA

void merge(int array[], int p, int q, int r)
{
    // Declaracion de variables
    int i, j, k;
    int n_1 = (q - p) + 1;
    int n_2 = (r - q);
    int *L, *R;

    // Asignacion de memoria
    L = malloc((size_t)n_1 * sizeof(int));
    R = malloc((size_t)n_2 * sizeof(int));
    if (L == NULL || R == NULL){
        free(L);
        free(R);
        fprintf(stderr, "No se pudo reservar memoria para la mezcla.\n");
        exit(EXIT_FAILURE);
    }

    // Copia de datos del arreglo A en los subarreglos L y R
    for (i = 0; i < n_1; i++)
    {
        L[i] = array[p + i];
    }

    for (j = 0; j < n_2; j++)
    {
        R[j] = array[q + j + 1];
    }

    i = 0;
    j = 0;

    // Fusion de datos respetando el valor minimos entre dos arreglos
    for (k = p; k <= r; k++)
    {
        if (i == n_1)
        {
            array[k] = R[j];
            j =  j+ 1;
        }
        else if(j == n_2)
        {
            array[k] = L[i];
            i = i + 1;
        }
        else
        {
            if (L[i] <= R[j])
            {
                array[k] = L[i];
                i = i + 1;
            }
            else
            {
                array[k] = R[j];
                j = j + 1;
            }
        }
    }
    free(L);
    free(R);
}

void mezcla(int array[], int p, int r){
    if (p < r){
        int q = p + (r - p) / 2;

        mezcla(array, p, q);
        mezcla(array, q + 1, r);

        merge(array, p, q, r);
    }
}

void mezclaPasos(int array[], int p, int r){
    if (p < r){
        int q = p + (r - p) / 2;

        mezclaPasos(array, p, q);
        mezclaPasos(array, q + 1, r);

        // Estas son las mitades que merge copiara en L y R.
        printArr(&array[p], q - p + 1, "\nL: ");
        printArr(&array[q + 1], r - q, "\nR: ");

        merge(array, p, q, r);

        printArr(&array[p], r - p + 1, "\nResultado: ");
        printf("\n");
    }
}



void mostrarTiempo(double diferencia){
    int milisegundos = (double)(diferencia) * 1000.0 / CLOCKS_PER_SEC;
    printf("\n\nTiempo de ordenamiento: %d ms", milisegundos);
}

void ordenPasos(int arreglo[], int m, int O){
    switch (O) {
        case 1:
            insercionPasos(arreglo, m);
        break;
        case 2:
            burbujaPasos(arreglo, m);
        break;        
        case 3:
            seleccionPasos(arreglo, m);
        break;        
        case 4:
            mezclaPasos(arreglo, 0, m - 1);
        break;
    }
}

double orden(int arreglo[], int m, int O){
    clock_t inicio,fin;
    printf("\nOrdenando...");
    switch (O) {
        case 1:
            inicio = clock();
            insercion(arreglo, m);
            fin = clock();
        break;
        case 2:
            inicio = clock();
            burbuja(arreglo, m);
            fin = clock();
        break;        
        case 3:
            inicio = clock();
            seleccion(arreglo, m);
            fin = clock();
        break;        
        case 4:
            inicio = clock();
            mezcla(arreglo, 0, m - 1);
            fin = clock();
        break;
    
    }
    double diferencia = (double)(fin - inicio);
    printf("\rAlgoritmo de ordenamiento ejecutado con exito");
    return diferencia;
}

int printMenu(int b){
    int op;
    system("cls");
    printf("\tMENU\n");
    printf("1). Inicializar arreglo.\n");
    printf("2). Ver arreglo generado.\n");
    printf("3). Ordenar el arreglo generado.\n");
    printf("4). Salir del programa.\n");
    if (b==0)
        op=pedirEntero("Seleccione una opcion: ");
    else if (b==1)
        op=pedirEntero("Seleccione una opcion valida: ");
    else if(b==2)
        op=pedirEntero("Primero debes inicializar el arreglo: ");
    return op;
}

void iniciar(int data[]){
    data[0] = pedirEntero("De cuantos valores desea que sea el arreglo? (1 a 1,000,000)\nElige menos de diez para ver los pasos.\n");
    while (data[0] < 1 || data[0] > 1000000){
        data[0] = pedirEntero("Cantidad invalida. Ingresa un valor entre 1 y 1,000,000:\n");
    }
    //E=data[1]
    data[1] = pedirEntero("Elige el tipo de arreglo a ordenar:\n1) Arreglo ordenado\t2) Arreglo invertido\t3) Arreglo aleatorio\n");
    while (data[1] < 1 || data[1] > 3){
        data[1] = pedirEntero("Opcion invalida. Elige 1, 2 o 3:\n");
    }
}

void copiarArr(int destino[], int origen[], int m){
    memcpy(destino, origen, m * sizeof(int));
}

void programa1(){
    int *arreglo=NULL;
	srand(time(NULL));
    int data[3];
    llenarArreglo(data, 3, "cero");
    int op, b=0, imp;
    do{
        op = printMenu(b);
        switch (op) {
            case 1:
                system("cls");
                //m=data[0]
                b = 0;
                iniciar(data);
                arreglo = malloc((size_t)data[0] * sizeof *arreglo);
                if (arreglo == NULL){
                    printf("No se pudo reservar memoria.\n");
                    return;
                }
                int *original = malloc((size_t)data[0] * sizeof *original);
                if (original == NULL){
                    printf("No se pudo reservar memoria.\n");
                    return;
                }
                iniciarArr(arreglo, data[0], data[1]);
                copiarArr(original, arreglo, data[0]);
                imp = pedirEntero("\nDesea ver el Arreglo generado?\t1) Si\t2) No\n");
                while(0>imp && imp>3){
                    imp = pedirEntero("\nIngrese una opcion valida: ");
                }
                if(imp==1){
                    printArr(arreglo, data[0], "\nArreglo generado:\n");
                    printf("\nPresiona una tecla para continuar...\n");
                    getch();
                }
                break;
            case 2:
                if(data[0]==0 || data[1]==0){
                    b=2;
                    break;
                }
                system("cls");
                printArr(original, data[0], "\nArreglo desordenado:\n");
                printf("\nPresiona una tecla para continuar...\n");
                getch();
                break;
            case 3:
                system("cls");
                //O=data[2]
                copiarArr(arreglo, original, data[0]);
                b = 0;
                if(data[0]==0 || data[1]==0){
                    b=2;
                    break;
                }
                else{
                    data[2] = pedirEntero("Elige el algoritmo de ordenamiento:\n1) Insercion\t2) Burbuja\t3) Seleccion\t4) Mezcla\n");
                    if(data[0] > 10){
                        double tiempo;
                        tiempo = orden(arreglo, data[0], data[2]);
                        mostrarTiempo(tiempo);
                    }
                    else{
                        ordenPasos(arreglo, data[0], data[2]);
                    }
                    float mediana = calcularMediana(arreglo, data[0]);
                    printf("\n\nLa mediana en el arreglo de numero es: %.2f\n", mediana);
                    imp = pedirEntero("\nDesea ver el Arreglo ordenado?\t1) Si\t2) No\n");
                    while(0>imp && imp>3){
                        imp = pedirEntero("\nIngrese una opcion valida: ");
                    }
                    if(imp==1)
                        printArr(arreglo, data[0], "\n\nArreglo Ordenado:\n");
                    printf("\nPresiona una tecla para continuar...\n");
                    getch();
                }break;
            case 4:
                b = 0;
                free(arreglo);
                break;
            default:
                b=1;
                break;

        }
    }while(op!=4);
}

int main(int argc, char const *argv[]){
	programa1();
	return 0;
}
