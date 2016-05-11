package ski.crono;

import java.io.*; 
import java.net.*;

public class CronoHub {
    static CronoHubNetServerManager netmgr=new CronoHubNetServerManager();

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input;
        CronoWebInt cw=new CronoWebInt();
        
        netmgr.start();
        
        do{
            input = br.readLine();
            if(input.equals("login")) cw.doLogin();
            if(input.equals("serv")) cw.doServ();
            
        } while (!input.equals("x"));
        
        netmgr.killAllServers();
        
        /*
        serverSocket = new ServerSocket(6789);
        serverSocket.setSoTimeout(10000);  
        
        System.out.println("Waiting for client on port " +
        serverSocket.getLocalPort() + "...");
        Socket server = serverSocket.accept();
        System.out.println("Just connected to " + server.getRemoteSocketAddress());
        
        //DataInputStream in =
        //      new DataInputStream(server.getInputStream());
        //System.out.println(in.readUTF());
        
        //DataOutputStream out =
        //     new DataOutputStream(server.getOutputStream());
        //out.writeUTF("Thank you for connecting to "
        //  + server.getLocalSocketAddress() + "\nGoodbye!");
        server.close();
        */
    }
    
}
