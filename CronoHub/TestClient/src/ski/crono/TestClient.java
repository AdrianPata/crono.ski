/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import java.net.*;
import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author MPLAB
 */
public class TestClient {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String serverName = "127.0.0.1";
        int port = 4523;
        byte[] b;
        boolean run=true;
        NetProcess net;
        
        try{
            System.out.println("Connecting to " + serverName + " on port " + port);
            Socket client = new Socket(serverName, port);
            net=new NetProcess(client);
            net.start();
            System.out.println("Just connected to "  + client.getRemoteSocketAddress());
            OutputStream outToServer = client.getOutputStream();
            
            
            String c;
            String r;
            while(run){
            
                r=br.readLine();
                if(r.equals("x")) run=false;
                if(r.equals("c1")){
                    c="salut\r\n";
                    b=c.getBytes();
                    outToServer.write(b);
                }
            }
            
            client.close();
        } catch (IOException ex) {
            Logger.getLogger(TestClient.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    
}
