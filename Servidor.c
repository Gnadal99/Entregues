#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <ctype.h>
#include <pthread.h>

int contador;
int i;
int sockets[100];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *AtenderCliente (void *socket)
{
	int sock_conn;
	int *s;
	s = (int *) socket;
	sock_conn = *s;
	
	int ret;
	
	char peticion[512];
	char respuesta[512];
	
	int terminar =0;
	while (terminar ==0)
	{
		// Ahora recibimos la petici?n
		ret=read(sock_conn,peticion, sizeof(peticion));
		printf ("Recibido\n");
		
		// Tenemos que a?adirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret]='\0';
		
		
		
		
		char *p = strtok( peticion, "/");
		printf ("Peticion: %s\n",peticion);
		
		int codigo =  atoi (p);
		// Ya tenemos el c?digo de petici?n
		char nombre[20];
		
		if ((codigo !=0) && (codigo != 6))
		{
			p = strtok( NULL, "/");
			
			strcpy (nombre, p);
			// Ya tenemos el nombre
			printf ("Codigo: %d, Nombre: %s\n", codigo, nombre);
		}
		
		if (codigo == 0)
		{
			terminar=1;
		}
		
		
		
		else if (codigo ==1) //piden la longitd del nombre
		{
			sprintf (respuesta,"1/%ld",strlen (nombre));
		}
		
		else if (codigo ==2)
		{
			// quieren saber si el nombre es bonito
			if((nombre[0]=='M') || (nombre[0]=='S'))
			{
				strcpy (respuesta,"2/SI");
			}
			else
			{
				strcpy (respuesta,"2/NO");
			}
		}
		else  if (codigo ==3)//quiere saber si es alto
		{
			p = strtok( NULL, "/");
			float altura =  atof (p);
			if (altura > 1.70)
				sprintf (respuesta, "3/%s: eres alto",nombre);
			else
				sprintf (respuesta, "3/%s: eres bajo",nombre);
		}
		
		else  if (codigo ==4)//palindromo
		{		
			
			int pal = 1;
			int lenn = strlen(nombre);
			for (int l = 0; nombre[l] != '\0'; l = l + 1)
			{
				nombre[l] = toupper(nombre[l]);
			}
			
			if (lenn % 2 == 0)
			{
				for (int i = 0 ; i <= (lenn-1) / 2 ; i++)
				{
					if (nombre[i] != nombre[lenn-1-i])
						pal = 0;
				}
			}
			if (lenn % 2 == 1)
			{
				for (int i = 0 ; i <= (lenn -2)/2 ; i++)
				{
					if (nombre[i] != nombre[lenn-1-i])
						pal = 0;
				}
				
			}
			if (pal == 1)
			{
				strcpy (respuesta,"4/SI");
			}
			else
				strcpy (respuesta,"4/NO");
			
			
		}				
		
		else  if (codigo ==5)//mayusculas
		{		
			
			int pal = 1;
			int lenn = strlen(nombre);
			for (int l = 0; nombre[l] != '\0'; l = l + 1)
			{
				nombre[l] = toupper(nombre[l]);
			}
			sprintf (respuesta,"5/%s", nombre);
			
		}
		
		if (codigo !=0)
		{
			
			printf ("Respuesta: %s\n", respuesta);
			// Enviamos respuesta
			write (sock_conn,respuesta, strlen(respuesta));
		}
		
		if ((codigo != 0) && (codigo != 6))
		{
			pthread_mutex_lock( &mutex );
			contador = contador +1;
			pthread_mutex_unlock( &mutex );
			//notificar a todos los conectados
			char notificacion[20];
			sprintf (notificacion, "6/%d",contador);
			int j;
			for (j=0; j<i; j++)
				write (sockets[j], notificacion, strlen(notificacion));
		}
		
	}
	close(sock_conn);
	
}

int main(int argc, char *argv[])
{
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	
	// INICIALITZACIONS
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	// Fem el bind al port
	
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// establecemos el puerto de escucha
	serv_adr.sin_port = htons(9600);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	
	
	pthread_t thread[100];
	i=0;

	for (;;){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexion\n");
		
		sockets[i] = sock_conn;
		//sock_conn es el socket que usaremos para este cliente
		
		//Crear thread y decirle lo que tiene que hacer
		pthread_create (&thread[i], NULL, AtenderCliente, &sockets[i]);
		i++;
	}
}
