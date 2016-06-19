/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

/**
 *
 * @author MPLAB
 */
public class CronoHubNetServerManager extends Thread {
    public boolean running=true;
    private int listenPort=3895;
    private ArrayList<CronoHubNetServer> servers=new ArrayList();
    private ServerSocket serverSocket;
    private int serverId=0;
    CronoWebInt webInterface;
    
    @Override
    public void run(){
        Socket server;
        
        try {
            serverSocket = new ServerSocket(listenPort);
            serverSocket.setSoTimeout(0);
        } catch (IOException ex) {
            Log.out("Error on server manager config: "+ex.getMessage());
            return;
        }
        
        
        while(running){
            try { 
                Log.out("Waiting for client on port " + serverSocket.getLocalPort() + "...");
                server = serverSocket.accept(); //Wait for connection. Blocking
                createServer(server);
            } catch (IOException ex) {
                Log.out("Error on listening: "+ex.getMessage());
            }
        }
    }
    
    public void setWebInterface(CronoWebInt w){
        this.webInterface=w;
    }
    
    public void killAllServers() throws IOException{
        serverSocket.close();
        running=false;
        for(int i=0;i<servers.size();i++){
            if(servers.get(i).isAlive()) {
                servers.get(i).close();
                servers.remove(servers.get(i));
            }
        }
        running=false;
    }
    
    public void createServer(Socket sock){
        serverId++;
        Log.out("Creating server "+serverId+"...");
        CronoHubNetServer s;
        try{
            s=new CronoHubNetServer(sock,serverId,webInterface);
            s.start();
            servers.add(s);
        } catch(IOException ex){
            Log.out("Error creating server: "+ex.getMessage());
        }
    }   
    
    public void shutDownCronoStart(){
        for(int i=0;i<servers.size();i++){
            if(servers.get(i).isAlive()) {
                servers.get(i).shutDownGSM();
            }
        }
    }
}
