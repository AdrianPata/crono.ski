/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketTimeoutException;

/**
 *
 * @author MPLAB
 * http://www.tutorialspoint.com/java/java_networking.htm
 */
public class CronoHubNetServer extends Thread {
    
    private boolean connected=true; // While true the thread is running
    private final Socket server;
    private final int id;
    CryptoTool crypto=new CryptoTool();
    String CronoStartID=""; //base64 encoded ID
    CronoWebInt webInt;
    Boolean validConn=false; //The CronoStart is validated

    CommandProcess comP; //Analyze and process received bytes (commands)
    
    public CronoHubNetServer(Socket s,int id,CronoWebInt w) throws IOException
    {
       server=s;
       this.id=id;
       this.webInt=w;
       comP=new CommandProcess(id,this);       
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
            
            System.out.println("HUB:"+com+":"+new String(b));
            
            out.write("\r\n".getBytes());
            out.write("HUB:".getBytes());
            com+=":";            
            out.write(com.getBytes());
            out.write(b);
            out.write("\r\n".getBytes());
        } catch (IOException ex) {
            Log.out(id+" send data error: "+ex.getMessage());
        }
    }
    
    public void sendOrder(byte[] b){
        byte[] b64;
        byte[] block;
        byte[] ord=new byte[b.length+1]; //We need to add 0x0D to the end
        int procBytes=0;
        int blockBytes=0;
        
        //Copy input array and add CR at the end
        for(int i=0;i<b.length;i++) ord[i]=b[i];
        ord[b.length]=0x0D;
        
        while(procBytes<ord.length){
            block=new byte[12];
            while(procBytes<ord.length && blockBytes<12){
                block[blockBytes]=ord[procBytes];
                blockBytes++;
                procBytes++;
            }
            
            b64=crypto.encryptBlock(block,blockBytes);
            sendData("DAT",b64);
            blockBytes=0;
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
        webInt.updateWebStatus("CronoStartDisconnected");
    }
    
    //Share public key
    private void initConnection(){
        sendData("KEY", crypto.base64encode(crypto.randomKey()));
    }
    
    public void shutDownGSM(){
        sendOrder("SHUT".getBytes());
    }
}
