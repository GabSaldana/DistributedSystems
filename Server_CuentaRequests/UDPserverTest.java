import java.net.*;
import java.io.*;

public class UDPserverTest{


/*Esta escuchando siempre y Recibe un mensaje del cliente ve que mensaje es y 
responde conforme a lo recibido */

	public static void main(String args[]){

		DatagramSocket socket = null;//guarda la conexion al puerto
		int count = 0;//index to be sent

		try{//in the case the port is already bussy

			socket = new DatagramSocket(8765);
		}catch(IOException e){

			System.out.println(e);
		}

		boolean runServer = true;//
		while(runServer){//run forever

			try{

				byte block[] = new byte[256];//paquete
				DatagramPacket inpacket = new DatagramPacket(block, block.length);//solo pueden ser bytes
				socket.receive(inpacket);//lo recibimos y lo guardamos en inpacket

				int length = inpacket.getLength();
				System.out.println("DAta length: " + length);
				byte inblock[] = inpacket.getData();//obtenemos los datos del mensaje
				int port = inpacket.getPort();
				String inmsg =  new String(inblock, 0, length);//lo convertimos en cadena
				System.out.println("Server obtained: " + inmsg + " on the port: " + port);

				//ANSWERING
				String outmsg="";//answer to the user
				count++;//number of messaje

				if(inmsg.equals("count")){
					outmsg = "NUmber of messages: " + count;
				}else if(inmsg.equals("gabs")){
					outmsg = "Hi Admin: GABS";
				}else if(inmsg.equals("stop")){
					socket.close();//close the sesison
				}else{
					
					outmsg = "What you mean by " + inmsg + "?";
				}

				byte outblock[] = outmsg.getBytes();//convertimos a bytes

				InetAddress returnAddress = inpacket.getAddress();//contiene la direccion y el puerto
				int returnport = inpacket.getPort();
				DatagramPacket outpacket = new DatagramPacket(outblock,outblock.length,returnAddress,returnport);
				socket.send(outpacket);

			}catch(IOException e){

				e.printStackTrace();
			}
		}
	}
}