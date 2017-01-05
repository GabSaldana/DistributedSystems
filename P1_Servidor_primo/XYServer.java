import java.net.*;
import java.io.*;
import javax.swing.*; 
import java.awt.*; 

public class XYServer extends JFrame {
	
	static int x=0,y=0;

	public XYServer() {
        //Create and set up the window.
        setTitle("GRafica");
        setSize(900,900);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       
    }

	public static void main(String[] args){

		try{
			
			while(true){//siempre estamos escuchando
 
 				//RECEIVE
				DatagramSocket Servidor= new DatagramSocket(1500);//socket
				byte buffer[]= new byte[256];//donde vamos a recibir el mensaje
				DatagramPacket pack= new DatagramPacket(buffer, buffer.length);//datagrama
				Servidor.receive(pack);
				System.out.println("ip:" + pack.getAddress());
                System.out.println("puerto:" + pack.getPort());
                String msg = new String(pack.getData(),0,pack.getLength());
				//PAINT
				String[] tokens=msg.split(",");
				x= Integer.parseInt(x);
				y= Integer.parseInt(y);
				System.out.println(x + "," + y );
				XYServer s = new XYServer();
				//SEND
				String outstr = "pintado";
				byte outblock[] = outstr.getBytes();
				InetAddress address = InetAddress.getLocalHost();//elcliente es local
				DatagramPacket outpacket = new DatagramPacket(outblock, outblock.length, address,8765);
				socket.send(outpacket);

			}	

		}catch(Exception e){

			e.printStackTrace();
		}
	}

	public static void paint(Graphics g){

		g.setColor(Color.RED);
    	g.drawLine(x, y, x, y);		
	}

}