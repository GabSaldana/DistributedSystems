import java.net.*;
import java.io.*;


public class serv2{
    
    public static boolean isPrimo(long num) {
			for(long i=num/2;i<num;i++)
        		if(num%i==0)
            		return false;
    		return true;
	}
   
    public static void main(String[] args) {
            try {
            int port=1501;
            DatagramSocket Servidor= new DatagramSocket(port);
            byte buffer[]= new byte[1500];
            while(true){
                DatagramPacket pack= new DatagramPacket(buffer, buffer.length);
                Servidor.receive(pack);
                System.out.println("ip:" + pack.getAddress());
                System.out.println("puerto:" + pack.getPort());
                String msg=new String(pack.getData(),0,pack.getLength());
                System.out.println("mensaje:" + msg);
                long NumP= Long.parseLong(msg);
                boolean n=isPrimo(NumP);
                System.out.println("El numero es primo:"+n);
                //puerto y dir del cliente
                envia(n,"127.0.0.1",1488);
                //envia(n,""+pack.getAddress(),pack.getPort());            
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void envia(boolean s,String m,int pto) throws UnknownHostException, SocketException, IOException {
                
                DatagramSocket Cliente= new DatagramSocket();
                String msg = "Servidor2:" +Boolean.toString(s);
                //System.out.println("Estoy aqui:3");
                byte[] mensaje= msg.getBytes();
                InetAddress host= InetAddress.getByName(m);
                DatagramPacket pack=new DatagramPacket(mensaje,msg.length(),host,pto);
                Cliente.send(pack);    
    }
}
