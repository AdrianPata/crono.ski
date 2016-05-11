/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import java.io.IOException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author MPLAB
 */
public class CronoHubNetServerManager extends Thread {
    public boolean running=true;
    private int listenPort=4523;
    private ArrayList<CronoHubNetServer> servers=new ArrayList();
    
    @Override
    public void run(){
        while(running){
            //If there is no listening server, create a new server
            if(!existListeningServer()){
                createServer();
            }
            
            
            try { 
                Thread.sleep(1);
            } catch (InterruptedException ex) {
                Thread.currentThread().interrupt();
            }
        }
    }
    
    public void killAllServers(){
        for(int i=0;i<servers.size();i++){
            if(servers.get(i).isAlive()) {
                servers.get(i).interrupt();
                servers.remove(servers.get(i));
            }
        }
        running=false;
    }
    
    public void createServer(){
        Log.out("Creating server...");
        CronoHubNetServer s;
        try{
            s=new CronoHubNetServer(listenPort);
            s.start();
        } catch(IOException ex){
            Log.out("Error creating server: "+ex.getMessage());
            return;
        }
        servers.add(s);
    }
    
    //Test if there is any server listening for a connection
    public boolean existListeningServer(){
        boolean ret=false;
        
        for(int i=0;i<servers.size();i++){
            if(servers.get(i).listening) {
                ret=true;
                break;
            }
        }
        
        return ret;
    }
}
