/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import javax.xml.bind.DatatypeConverter;

/**
 *
 * @author MPLAB
 */
public class NetProcess extends Thread {
    Socket client;
    boolean running=true;
    //256 bit secret
    byte[] secret=new byte[] {(byte)0xcb,(byte)0x07,(byte)0x1D,(byte)0x84,(byte)0x75,(byte)0xFA,(byte)0x8C,(byte)0x73,(byte)0xB7,(byte)0x30,(byte)0x81,(byte)0xAA,(byte)0x14,(byte)0xAF,(byte)0x78,(byte)0x83,(byte)0x07,(byte)0x68,(byte)0x2C,(byte)0x23,(byte)0x47,(byte)0xEB,(byte)0xB1,(byte)0x5D,(byte)0xAE,(byte)0xAE,(byte)0xE0,(byte)0x3D,(byte)0xF2,(byte)0x49,(byte)0x6B,(byte)0x1D};
    
    public NetProcess(Socket c){
        client=c;
    }
    
    @Override
    public void run(){
        byte[] b=new byte[1000];
        byte[] buf;
        int t;
        StringBuilder command;
        try{
            InputStream in=client.getInputStream();
            while(running){
                t=in.read(b,0,1000);
                if(t==-1) break;
                command=new StringBuilder();
                buf=new byte[t];
                for (int i=0;i<t;i++){ 
                    command.append((char)b[i]);
                    buf[i]=b[i];
                }
                System.out.println("Received: "+command.toString());
                System.out.println("Received: "+DatatypeConverter.printHexBinary(buf));
            }
        }catch(IOException e){
            System.out.println("Eroare: "+e.getMessage());
        }
        System.out.println("Connection closed.");
    }
}
