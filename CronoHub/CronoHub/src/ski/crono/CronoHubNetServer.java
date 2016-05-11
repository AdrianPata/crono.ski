/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author MPLAB
 * http://www.tutorialspoint.com/java/java_networking.htm
 */
public class CronoHubNetServer extends Thread {
    
    public boolean listening=true;
    public boolean running=true; // While true the thread is running
    private ServerSocket serverSocket;
    private Socket server;
    
    CommandProcess comP=new CommandProcess(); //Process received bytes
    
    public CronoHubNetServer(int port) throws IOException
    {
       serverSocket = new ServerSocket(port);
       serverSocket.setSoTimeout(0);
    }
    
    @Override
    public void run(){
        try{
            Log.out("Waiting for client on port " + serverSocket.getLocalPort() + "...");
            server = serverSocket.accept();
            Log.out("Just connected to " + server.getRemoteSocketAddress());
            InputStream in=server.getInputStream();
            byte[] rBytes=new byte[1000];
            int t;
            while(running){
                if(in.available()>0){
                    t=in.read(rBytes,0, 1000);
                    if(t>0) Log.out("Received "+t+" bytes");
                    comP.addBytes(rBytes, t);
                }
                
                Thread.sleep(1);
            }
        }catch(SocketTimeoutException s)
        {
           Log.out("Socket timed out!"+s.getMessage());
        }catch(IOException e)
        {
            Log.out("CronoHubNetServer error: "+e.getMessage());
        }catch(InterruptedException ex) {
            Log.out("CronoHubNetServer thread interrupted: "+ex.getMessage());
        }
        finally {
            try {
                if(server!=null) server.close();
            } catch (IOException ex) {
                Log.out("CronoHubNetServer closing error: "+ex.getMessage());
            }
        }
    }
    
    
}
