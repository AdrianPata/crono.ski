package ski.crono;

import java.io.*; 
import java.net.*;

public class CronoHub {

    private static ServerSocket serverSocket;
    
    
    public static void main(String[] args) throws Exception {
        serverSocket = new ServerSocket(6789);
        serverSocket.setSoTimeout(10000);  
        
        System.out.println("Waiting for client on port " +
        serverSocket.getLocalPort() + "...");
        Socket server = serverSocket.accept();
        System.out.println("Just connected to " + server.getRemoteSocketAddress());
        //DataInputStream in =
        //      new DataInputStream(server.getInputStream());
        //System.out.println(in.readUTF());
        
        DataOutputStream out =
             new DataOutputStream(server.getOutputStream());
        out.writeUTF("Thank you for connecting to "
          + server.getLocalSocketAddress() + "\nGoodbye!");
        server.close();
    }
    
}
