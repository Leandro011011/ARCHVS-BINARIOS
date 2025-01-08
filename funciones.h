struct Producto
{
    char nombreP[50];
    int cantidad;
    float precio;
};
struct Factura
{
    char nombre[50];
    float total;
    int cedula;
    int numProductos;
    struct Producto productos[100];
};
void save(struct Factura *factura);
void eliminateSalto(char *cadena, int tam);
void createFactura();
void readFactura();
void eliminarFactura();
void editFactura();

