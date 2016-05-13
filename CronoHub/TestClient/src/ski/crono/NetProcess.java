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
    public byte[] secret=new byte[] {(byte)0xcb,(byte)0x07,(byte)0x1D,(byte)0x84,(byte)0x75,(byte)0xFA,(byte)0x8C,(byte)0x73,(byte)0xB7,(byte)0x30,(byte)0x81,(byte)0xAA,(byte)0x14,(byte)0xAF,(byte)0x78,(byte)0x83,(byte)0x07,(byte)0x68,(byte)0x2C,(byte)0x23,(byte)0x47,(byte)0xEB,(byte)0xB1,(byte)0x5D,(byte)0xAE,(byte)0xAE,(byte)0xE0,(byte)0x3D,(byte)0xF2,(byte)0x49,(byte)0x6B,(byte)0x1D};
    public byte[] sharedKey=new byte[32];
    public byte[] comBuffer=new byte[1000];
    int comBufferPos=0;
    
    public NetProcess(Socket c){
        client=c;
    }
    
    @Override
    public void run(){
        byte[] b=new byte[1000];
        int t,ce;
        try{
            InputStream in=client.getInputStream();
            while(running){
                t=in.read(b,0,1000);
                if(t==-1) break;
                for (int i=0;i<t;i++){ 
                    comBuffer[comBufferPos]=b[i];comBufferPos++;
                }
                
                ce=identifyCommand();
                if(ce>=0){
                    processCommand(ce);
                }
                
            }
        }catch(IOException e){
            System.out.println("Eroare: "+e.getMessage());
        }
        System.out.println("Connection closed.");
    }
    
    private int identifyCommand(){
        for (int i=0;i<comBufferPos;i++){
            if(comBuffer[i]==0x0D && comBuffer[i+1]==0x0A){ //CRLF found
               return i; 
            }
        }
        
        return -1;
    }
    
    private void processCommand(int commandEndPos){
        byte[] buf;
        StringBuilder command=new StringBuilder();
        buf=new byte[commandEndPos];
        for (int i=0;i<commandEndPos;i++){ //commandEndPos is the position of 0x0D
            command.append((char)comBuffer[i]);
            buf[i]=comBuffer[i];
        }
        
        System.out.println("Received: "+command.toString());
        System.out.println("Received: "+DatatypeConverter.printHexBinary(buf));
        discardCommand(commandEndPos);
        
        if(command.toString().startsWith("SENDKEY")){
            for(int i=7;i<39;i++) sharedKey[i-7]=buf[i]; //extract shared key
            System.out.println("Shared Key: "+DatatypeConverter.printHexBinary(sharedKey));
        }
    }
    
    private void discardCommand(int commandEndPos){
        int j=0;
        commandEndPos+=2; //Step over CRLF (0x0D and 0x0A)
        
        for(int i=commandEndPos;i<comBufferPos;i++){
            comBuffer[j]=comBuffer[i]; //copy bytes from buffer to first position
            j++;
        }
        
        comBufferPos=j;
    }
}
