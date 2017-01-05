import java.net.*;
import java.io.*;

public class UDPclient2{

/*enviamos un mensaje, obteniendolo de lo que recibe main*/
	public static void main(String args[]){

		String outstr;
		if(args.length >= 1)
			outstr = args[0];
		else
			outstr="count";//defaultmessage

		try{

			DatagramSocket socket =  new DatagramSocket();
			byte outblock[] = outstr.getBytes();
			InetAddress address = InetAddress.getLocalHost();//elcliente es local
			DatagramPacket outpacket = new DatagramPacket(outblock, outblock.length, address,8765);
			socket.send(outpacket);
			System.out.println("Client sent:" + outstr);

			//SErver's answer
			byte inblock[]= new byte[256];
			DatagramPacket inpacket =  new DatagramPacket(inblock, inblock.length);
			socket.receive(inpacket);

			String instr = new String(inpacket.getData(), 0, inpacket.getLength());
			System.out.println("Client got: " + instr);
			socket.close();

		}catch(SocketException e){
			System.out.println(e);
		}catch(UnknownHostException e){
			System.out.println(e);
		}catch(IOException e){
			System.out.println(e);
		}
	}

}
