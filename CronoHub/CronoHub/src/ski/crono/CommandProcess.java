/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import java.util.ArrayList;
import java.util.LinkedList;

/**
 *
 * @author MPLAB
 */
public class CommandProcess {
    LinkedList<Byte> receivedBytes=new LinkedList<Byte>();
    ArrayList<Byte> command=null;
    int id;
    CronoHubNetServer server;
    
    
    public CommandProcess(int id,CronoHubNetServer s){
        this.id=id;
        this.server=s;
    }
    
    //Add received bytes to data buffer
    public void addBytes(byte[] recB,int length){
        for (int i=0;i<length;i++){
            receivedBytes.add(recB[i]);
        }
        
        //Try to ansamble a command
        while(!receivedBytes.isEmpty()){
            Byte b=receivedBytes.removeFirst();
            if(b!=0x0D){//It is not a command terminator.
                if(command==null) command=new ArrayList<>(); //If the command is null, create it
                command.add(b);
            } else {//We have a command terminator. Send command to processing.
                processCommand();
                command=null;
            }
        }
    }
    
    //Process command in buffer
    private void processCommand(){
        StringBuilder com=new StringBuilder();
        for(byte b:command) com.append((char)b);
        
        Log.out(id+" received command: "+com.toString());
        
        //CronoStart ID received. This will validate the connection.
        if(com.toString().startsWith("ID:")){
            String[] el=com.toString().split(":");
            server.CronoStartID=el[1];
            String ssk=server.webInt.getSecretSharedKey(server.CronoStartID);
            server.crypto.setSecretSharedKey(ssk);
            byte[] r=server.crypto.AESdecode(server.crypto.base64decode(el[2].getBytes()));
            if(r!=null && new String(r).equals("HALLO")){
                System.out.println(id+" valid connection.");
                server.validConn=true;
            }else{
                System.out.println(id+" invalid connection.");
                server.close();
            }
        }
        
        //Encrypted data received from CronoStart
        if(com.toString().startsWith("DAT:")){
            String[] el=com.toString().split(":");
            byte[] r=server.crypto.AESdecode(server.crypto.base64decode(el[1].getBytes()));
            System.out.println("Decoded data: "+new String(r));
        }
    }
}
