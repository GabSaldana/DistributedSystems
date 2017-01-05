import java.net.*;
import java.io.*;


public class serv1{
    public static void main(String[] args) {
            try {
            int port=1500;
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
                envia(n,"192.168.0.104",1488);
                //envia(n,""+pack.getAddress(),pack.getPort());            
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void envia(boolean s,String m,int pto) throws UnknownHostException, SocketException, IOException {
                
                DatagramSocket Cliente= new DatagramSocket();
                String msg = "Servidor1:" +Boolean.toString(s);
                //System.out.println("Estoy aqui:3");
                byte[] mensaje= msg.getBytes();
                InetAddress host= InetAddress.getByName(m);
                DatagramPacket pack=new DatagramPacket(mensaje,msg.length(),host,pto);
                Cliente.send(pack);    
    }

    public static boolean isPrimo(long num) {
            for(long i=2;i<(62*num)/100;i++)
                if(num%i==0)
                    return false;
            return true;
    }
    
}
