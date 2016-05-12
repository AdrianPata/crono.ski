/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
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
    
    private boolean connected=true; // While true the thread is running
    private final Socket server;
    private final int id;
    private CryptoTool crypto=new CryptoTool();
    
    CommandProcess comP; //Analyze and process received bytes (commands)
    
    public CronoHubNetServer(Socket s,int id) throws IOException
    {
       server=s;
       this.id=id;
       comP=new CommandProcess(id);
    }
    
    //Kill the connection and close the server
    public void close(){
        try {
            connected=false;
            server.close();
        } catch (IOException ex) {
            Log.out(id+" error on closing "+ex.getMessage());
        }
    }
    
    public void sendData(String com,byte[] b){
        try {
            OutputStream out=server.getOutputStream();
            out.write("SEND".getBytes());
            out.write(com.getBytes());
            out.write(b);
            out.write("\r\n".getBytes());
        } catch (IOException ex) {
            Log.out(id+" send data error: "+ex.getMessage());
        }
        
    }
    
    @Override
    public void run(){
        try{
            Log.out(id+ " just connected to " + server.getRemoteSocketAddress());
            InputStream in=server.getInputStream();
            byte[] rBytes=new byte[1000];
            int t;
            
            initConnection();
            
            while(connected){
                t=in.read(rBytes,0, 1000); //Read bytes from socket. Blocking.
                if(t>0) {
                    Log.out(id+ " received "+t+" bytes");
                    comP.addBytes(rBytes, t);
                }
                if(t==-1) break; //Connection closed
            }
        }catch(SocketTimeoutException s)
        {
           Log.out(id+" socket timed out!"+s.getMessage());
        }catch(IOException e)
        {
            Log.out(id+" CronoHubNetServer error: "+e.getMessage());
        } finally {
            try {
                server.close();
            } catch (IOException ex) {
                Log.out(id+" CronoHubNetServer closing error: "+ex.getMessage());
            }
        }
        Log.out(id+ " connection closed.");
    }
    
    //Share public key
    private void initConnection(){
        byte[] key=crypto.randomKey();
        sendData("KEY", key);
    }
}
