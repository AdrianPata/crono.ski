/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ro.pata.sim800h;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.LinkedList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Adi
 */
public class Hub extends Thread {
    Socket client;
    boolean connected=false;
    boolean running=true;
    LinkedList<Byte> buffer=new LinkedList();
    OutputStream outToServer;
    ComTool com;
    
    public Hub(ComTool c){
        com=c;
    }
    
    public boolean connect(){
        //String host="192.168.157.1";
        String host="localhost";
        
        try {
            client = new Socket(host, 3895);            
            System.out.println("Just connected to "  + client.getRemoteSocketAddress());
            connected=true;
            return true;
        } catch (IOException ex) {
            Logger.getLogger(Hub.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
    }
    
    public void disconnect(){
        try {
            if(connected==true) client.close();
        } catch (IOException ex) {
            Logger.getLogger(Hub.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    @Override
    public void run(){
        byte[] b=new byte[1000];
        byte[] bo;
        int t;
        try {
            InputStream in=client.getInputStream();
            outToServer = client.getOutputStream();
            while(running){
                t=in.read(b,0,1000);
                if(t==-1) {
                    connected=false;
                    break;                    
                }
                bo=new byte[t];
                System.arraycopy(b, 0, bo, 0, t);
                com.SendRaw(bo);
            }
        } catch (IOException ex) {
            Logger.getLogger(Hub.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
