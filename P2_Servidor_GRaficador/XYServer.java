import java.net.*;
import java.io.*;
import javax.swing.*; 
import java.awt.*; 

public class XYServer {
	
	static int w=900,h=900;
	static double x=0,y=0;
	static int X0=w/2,Y0=h/2;//origen del plano carteciano
	static double escalaY=100,escalaX=100;
	

	public static void main(String[] args){

		JFrame jf = new JFrame();
        jf.setTitle("Grafica");
        jf.setSize(w,h);
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       	jf.setVisible(true);
       	jf.setResizable(false);

       	JPanel panel = new JPanel() {
            
            @Override
            public void paintComponent(Graphics g) {

				super.paintComponent(g);
	    		g.setColor(Color.decode("#FFFFFF"));
				g.drawLine(0, h/2,w,h/2);
				g.drawLine(w/2, 0,w/2 ,h);
				setBackground(Color.decode("#009688"));
				//setBackground(Color.decode("#FFFFFF"));
			}
        };

        jf.add(panel);
        
		try{


			DatagramSocket socket= new DatagramSocket(8765);//socket
			
			while(true){//siempre estamos escuchando

 				//RECEIVE
				byte buffer[]= new byte[256];//donde vamos a recibir el mensaje
				DatagramPacket pack= new DatagramPacket(buffer, buffer.length);//datagrama
				socket.receive(pack);
				System.out.println("ip:" + pack.getAddress());
                System.out.println("puerto:" + pack.getPort());
                String msg = new String(pack.getData(),0,pack.getLength());
				
				//PAINT
                System.out.println("Mensaje: " + msg);
                String[] slit = msg.split(",");
                slit[2] =slit[2].substring(0,6 );
                System.out.println(Double.parseDouble(slit[1]) + "," + Double.parseDouble(slit[2]) );

                double id = Double.parseDouble(slit[0]);

				if(id == 1){
					
					x= Double.parseDouble(slit[1]);
					y= Double.parseDouble(slit[2]);
					System.out.println("PINTA");
					double a= escalaX*x;
					double b= escalaY*y;
					x= X0 +a;
					y= Y0 -b;
					pinta(panel.getGraphics(),(int)x,(int)y);			

				}

				if(id == 0){

					if(x >= -3.10 || x <= -3.1416){
						System.out.println("INICIO BORRA");	
					}
					if(x >= 3.10 || x <= 3.1416){
						System.out.println("FIN BORRA");	
					}

					x= Double.parseDouble(slit[1]);
					y= Double.parseDouble(slit[2]);
					System.out.println("BORRA");
					System.out.println(x + "," + y );
					double a= escalaX*x;
					double b= escalaY*y;
					x= X0 +a;
					y= Y0 -b;
					borra(panel.getGraphics(),(int)x,(int)y);			
				}
			}	

		}catch(Exception e){

			e.printStackTrace();

		}
	}

	public static void pinta(Graphics g, int x, int y){

		g.setColor(Color.WHITE);
		//g.setColor(Color.decode("#009688"));
		g.drawLine(x, y, x, y);			
		System.out.println("ok");
    	
	}

	public static void borra(Graphics g, int x, int y){

		//g.setColor(Color.WHITE);
		g.setColor(Color.decode("#009688"));
		g.drawLine(x, y, x, y);			
		System.out.println("ok");
    	
	}

}


