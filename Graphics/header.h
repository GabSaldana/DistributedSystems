#define GROUP_MULTICAST0 "238.0.0.1"
#define GROUP_MULTICAST1 "238.0.0.2"
#define GROUP_MULTICAST2 "238.0.0.3"
#define GROUP_MULTICAST3 "238.0.0.4"

#define HEIGHT "600"
#define WIDTH "800"

#define MAX_LAD 10

typedef struct _Point
{
	uint16_t x;
	uint16_t y;	
}Point;
typedef struct _Multicast_Point
{
	uint8_t lados;
	Point p[MAX_LAD];
}Multicast_Point;

