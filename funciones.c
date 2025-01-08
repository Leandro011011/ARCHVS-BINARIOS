#include <stdio.h>
#include <string.h>
#include "funciones.h"
float suma = 0;

void save(struct Factura *factura){
    FILE *file = fopen("facturas", "ab+");
    if (file == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }else{
        fwrite(factura, sizeof(struct Factura), 1, file);
        printf("Factura guardada\n");
    }
    fclose(file);
}
void eliminateSalto(char *cadena, int tam){
    fflush(stdin);
    fgets(cadena, tam, stdin);
    cadena[strlen(cadena)-1] = '\0';
}

int cedulaExiste(int cedula) {
    FILE *file = fopen("facturas", "rb");
    struct Factura factura;

    if (file == NULL) {
        printf("Error al abrir el archivo 'facturas'\n");
        return 0; 
    }

    while (fread(&factura, sizeof(struct Factura), 1, file)) {
        if (factura.cedula == cedula) {
            fclose(file);
            return 1; 
        }
    }

    fclose(file);
    return 0; 
}

void createFactura(){
    struct Factura factura;
    printf("\nIngreso de Datos de la Facturacion\n");
    printf("\nIngrese el Nombre del Cliente: ");
    eliminateSalto(factura.nombre, 50);

     do {
        printf("\nIngrese la Cedula del Cliente: ");
        scanf("%i", &factura.cedula);
        if (factura.cedula < 0) {
            printf("Error: La cedula no puede ser negativa. Vuelve a ingresar.\n");
        } else if (cedulaExiste(factura.cedula)) {
            printf("Error: La cedula ya existe. Vuelve a ingresar.\n");
        }
    } while (factura.cedula < 0 || cedulaExiste(factura.cedula));
    
    printf("\nIngrese el Numero de Productos: ");
    scanf("%i", &factura.numProductos);
  
      
    
    for (int i = 0; i < factura.numProductos; i++)
    {
        printf("\n");
        printf("\nProducto Numero %i: \n", i + 1);
        printf("\nNombre del Producto: ");
        eliminateSalto(factura.productos[i].nombreP, 50);
        printf("\nPrecio del Producto: ");
        scanf("%f", &factura.productos[i].precio);
        printf("\nCantidad del Producto: ");
        scanf("%i", &factura.productos[i].cantidad);
         
        suma = suma + (factura.productos[i].precio * factura.productos[i].cantidad);
    }
    factura.total = suma;
    save(&factura);
}
void readFactura(){
    int opc, cedulaLeer, validar = 0;
    FILE *file = fopen("facturas", "rb");
    struct Factura factura;
    if (file == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }else{
        printf("\nNombre\t\t\tCedula\t\tTotal\n");
        while( fread(&factura, sizeof(struct Factura), 1, file)){
            printf("%s\t\t%i\t\t%.2f$\n", factura.nombre, 
                                          factura.cedula, 
                                          factura.total);     
        }

        printf("\nDesea ver los detalles de alguna factura? 1.Si 2.No\n");
        scanf("%i", &opc);    
        if (opc == 1){
        printf("\nIngrese la cedula del cliente a ver: ");
        scanf("%i", &cedulaLeer);
        rewind(file);
        while (fread(&factura, sizeof(struct Factura), 1, file)){
        if (factura.cedula == cedulaLeer){
            validar = 1;
            printf("\nProducto\tPrecio\t\tCantidad\n");
            for (int i = 0; i < factura.numProductos; i++)
            {
                printf("\n%s\t\t%.2f$\t\t%i\n", factura.productos[i].nombreP, 
                                                factura.productos[i].precio, 
                                                factura.productos[i].cantidad);
            }
        printf("\nTotal: %.2f\n", factura.total);
        break;
        }
        }
        if (validar == 0)
        {
            printf("\nNo se encontro la factura\n");
        }    
    }
}
    fclose(file);
}

void eliminarFactura(){
    FILE *file = fopen("facturas", "rb+");
    FILE *file2 = fopen("facturas2", "wb"); 
    struct Factura factura;
    int cedula;

    if (file == NULL){
        printf("Error al abrir el archivo 'facturas'\n");
        return;
    }

    if (file2 == NULL){
        printf("Error al abrir el archivo 'facturas2'\n");
        fclose(file);
        return;
    }

    printf("\nIngrese la cedula del cliente a eliminar: ");
    scanf("%i", &cedula);

    while (fread(&factura, sizeof(struct Factura), 1, file)){
        if (factura.cedula != cedula){
            fwrite(&factura, sizeof(struct Factura), 1, file2);

        }
    }
    
    fclose(file);
    fclose(file2);
    
    if (remove("facturas") == 0) { 
        
    }else{
        printf("\nError no se pudo borrar los datos");
    }

    if (rename("facturas2", "facturas") == 0) {
        
    }else{
        printf("\nError no se pudo mover los datos");
    }

        printf("Factura eliminada\n");
    
    

}


void editFactura(){
    FILE *file = fopen("facturas", "rb+");
    struct Factura factura;
    int cedula;

    if (file == NULL){
        printf("Error al abrir el archivo 'facturas'\n");
        return;
    }


    printf("\nIngrese la cedula del cliente a editar: ");
    scanf("%i", &cedula);

    while (fread(&factura, sizeof(struct Factura), 1, file)){
        if (factura.cedula == cedula){
            printf("\nNombre\t\tCedula\t\tTotal\n");
            printf("\n%s\t%i\t\t%.2f\n", factura.nombre,
                                           factura.cedula,
                                           factura.total);
            printf("\nProducto\tPrecio\t\tCantidad\n");
            for (int i = 0; i < factura.numProductos; i++)
            {
                printf("\n%s\t\t%.2f\t\t%i\n", factura.productos[i].nombreP,
                                               factura.productos[i].precio,
                                               factura.productos[i].cantidad);
            }
            printf("\nIngrese el nuevo Nombre del Cliente: ");
            eliminateSalto(factura.nombre, 50);
           
  
             do {
                printf("\nIngrese la Cedula del Cliente: ");
                scanf("%i", &factura.cedula);
                if (factura.cedula < 0) {
                    printf("Error: La cedula no puede ser negativa. Vuelve a ingresar.\n");
                } else if (cedulaExiste(factura.cedula)) {
                    printf("Error: La cedula ya existe. Vuelve a ingresar.\n");
                }
             } while (factura.cedula < 0 || cedulaExiste(factura.cedula));
            
            printf("\nIngrese el Numero de Productos: ");
            scanf("%i", &factura.numProductos);
      
        
        for (int i = 0; i < factura.numProductos; i++)
        {
            printf("\n");
            printf("\nProducto Numero %i: \n", i + 1);
            printf("\nNombre del Producto: ");
            eliminateSalto(factura.productos[i].nombreP, 50);
            printf("\nPrecio del Producto: ");
            scanf("%f", &factura.productos[i].precio);
        
            printf("\nCantidad del Producto: ");
            scanf("%i", &factura.productos[i].cantidad);
                suma = suma + (factura.productos[i].precio * factura.productos[i].cantidad);
            }
            factura.total = suma;
            fseek(file, -(long)sizeof(struct Factura), SEEK_CUR);
            fwrite(&factura, sizeof(struct Factura), 1, file);
            break;
        }
    }

    fclose(file);

}

