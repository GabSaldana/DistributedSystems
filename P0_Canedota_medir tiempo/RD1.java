import java.util.*;

public class RD1{
 public static void main(String[] args) {
	//int n=4294967295;
	int n=1757600;
	//int n=500000;
	Random rd= new Random();
	int p=0;
	char A;
	char[] msg = new char[n];
	int i=0;
		while(i<n){
			for (int x = 0; x < 3; x++){
				A=(char)(65+rd.nextInt(26));
				msg[i]=A;
				i++;
				}
			msg[i]=' ';
			i++;
			}
	
	i=0;
	int cont=0;
	while(i<n){
		if(msg[i]=='I')
			if(msg[i+1]=='P')
				if(msg[i+2]=='N')
					cont++;
		i+=4;
		}
		//System.out.println(msg);
		System.out.println("Cont:"+cont);
		}
	}