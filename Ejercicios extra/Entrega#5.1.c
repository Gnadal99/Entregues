#include <stdio.h>
#include <string.h>


typedef struct {
	char nombre [20];
	int socket;
} Conectado;

typedef struct {
	Conectado conectados [100];
	int num;
} ListaConectados;

int Pon (ListaConectados *lista, char nombre[20], int socket) {
	// Añade nuevo conectado. Retorna 0 si todo ok.
	if (lista->num == 100)
		return -1;
	else {
		strcpy (lista->conectados[lista->num].nombre, nombre);
		lista->conectados[lista->num].socket = socket;
		lista->num++;
		return 0;
	}
}


int DamePosicion (ListaConectados *lista, char nombre[20]) {
	//Devuelve el socket relacionado con el nombre o -1 si no está en la lista
	int i = 0;
	int encontrado = 0;
	while ((i < lista->num) && !encontrado)
	{
		if (strcmp(lista->conectados[i].nombre,nombre) == 0)
			encontrado = 1;
		if(!encontrado)
			i= i + 1;
	}
	if (encontrado)
		return i;
	else
		return -1;	
}

int Eliminar (ListaConectados *lista, char nombre[20]){
	//retorna 0 si elimina o -1 si no esta en la lista
	int pos = DamePosicion (lista, nombre);
	if (pos == -1)
		return -1;
	else {
		int i;
		for (i=pos; i < lista->num-1; i++)
		{
			strcpy (lista->conectados[i].nombre, lista->conectados[i+1].nombre);
			lista->conectados[i].socket = lista->conectados[i+1].socket;
		}
		lista->num--;
		return 0;
	}
}

void DameConectados (ListaConectados *lista, char conectados[300]) {
	// Pone en conectados numconectados/nombres separados por /
	// "3/Juan/Maria/Pedro"
	sprintf (conectados, "%d", lista->num);
	int i;
	for (i=0; i < lista->num; i++)
		sprintf (conectados, "%s/%s", conectados, lista->conectados[i].nombre);
}
void DameSockets (ListaConectados *lista, char conectados[300], char sockets [300]) {
	// Pone en sockets numconectados/sockets seperados po /
	// "3/Juan/Maria/Pedro" --> "3/12/64/23"
	char *p = strtok (conectados, "/");
	int n = atoi (p);
	sprintf (sockets, p);

	int i;
	for (i=0; i<n; i++) {
		p = strtok (NULL, "/");
		char nombre [20];
		strcpy (nombre, p);	
		int pos;
		pos = DamePosicion(lista, nombre);
		
		sprintf (sockets, "%s/%d", sockets, lista->conectados[pos].socket);
	}
	

}

int main(int argc, char *argv[]) {
	ListaConectados miLista;
	miLista.num = 0;
	Pon (&miLista, "Pedro", 3);
	Pon (&miLista, "Maria", 322);
	Pon (&miLista, "Carlos", 23);
	Pon (&miLista, "Gerard", 223);
	int res = Pon (&miLista, "Juan", 5);
	if (res == -1)
		printf ("Lista llena. No se ha podido añadir\n");
	else
		printf("Añadido\n");
	
	int pos = DamePosicion (&miLista, "Juan");
	if (pos != -1)
		printf("Socket: %d\n", miLista.conectados[pos].socket);
	else 
		printf("El usuario no esta en la lista.\n");
	
	res = Eliminar (&miLista, "Juan");
	if (res == -1)
		printf ("No esta\n");
	else
		printf("Eliminado.\n");
	
	char misConectados [300];
	DameConectados (&miLista, misConectados);
	printf ("Resultado: %s\n", misConectados);
	
	char misSockets[300];
	DameSockets(&miLista, misConectados, misSockets);
	
	printf ("Sockets: %s\n",misSockets);
	
	return 0;
}

