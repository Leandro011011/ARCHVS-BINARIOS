#include <stdio.h>
#include "funciones.h"
int main () {
    int opcion, opcion2;
    do
    {
        printf("\nMenu de Opciones: \n");
        printf("1. Crear Factura\n");
        printf("2. Leer Factura\n");
        printf("3. Editar Factura\n");
        printf("4. Eliminar Factura\n");
        printf("Seleccione una opcion: ");
        scanf("%i", &opcion);
        switch (opcion)
        {
        case 1:
            createFactura();
        break;
        case 2:
            readFactura();
        break;
        case 3:
            editFactura();
        break;
        case 4:
        eliminarFactura();
        break;
        default:
            printf("Opcion no valida.....N/A\n");
            break;
        }
        printf("\nDesea realizar otra operacion? 1.Si 2.No\n");
        scanf("%i", &opcion2);
    } while (opcion2 == 1);
    printf("\nGracias por utilizar el programa......\n");
    return 0;
}