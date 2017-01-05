#define OK 0 /*Mensaje de OK*/
#define E_BAD_OPCODE -1 /*Mensaje de Error*/
#define RESPONSE 1
#define REQUEST 0

typedef struct  _messageOrder
{
	uint32_t opcion;
	uint32_t numero;

}messageOrder; /*Mensaje de orden de las computadoras*/

typedef struct  _messageSynchronizeTrack
{
	uint32_t numero; /*Numero de computadora que lo envia*/
	uint32_t status; /*Status de la reprobuccion*/
	uint32_t posicion; /*Posición*/
}messageSynchronizeTrack;