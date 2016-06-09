/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import javax.xml.bind.DatatypeConverter;

/**
 *
 * @author MPLAB
 */
public class CommandProcess {
    byte[] buffer=new byte[1000];
    int bufferPos=0; //Buffer insert position. If it is 0, buffer is empty.
    int id;
    CronoHubNetServer server;
    
    
    public CommandProcess(int id,CronoHubNetServer s){
        this.id=id;
        this.server=s;
    }
    
    //Add received to buffer
    public void addBytes(byte[] b,int length){
        for (int i=0;i<length;i++){
            buffer[bufferPos+i]=b[i];
            System.out.print((char)b[i]);
        }
        bufferPos+=length;
        
        //Search for a command in buffer. Get command end position if found and process command.
        int ce=identifyCommand();
        if(ce>=0)processCommand(ce);
    }
    
    //Search in buffer for a command terminator
    private int identifyCommand(){
        for (int i=0;i<bufferPos;i++){
            if(buffer[i]==0x0D){ //CR found
               return i; 
            }
        }
        
        return -1;
    }
    
    //Process command in buffer
    private void processCommand(int commandEndPos){
        StringBuilder command=new StringBuilder();
        for (int i=0;i<commandEndPos;i++){ //commandEndPos is the position of 0x0D
            command.append((char)buffer[i]);
        }
        
        Log.out(id+" received command: "+command.toString());
        discardCommand(commandEndPos);
        
        //CronoStart ID received. This will validate the connection.
        if(command.toString().startsWith("ID:")){
            String[] el=command.toString().split(":");
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
    }
    
    //Discard command from buffer
    private void discardCommand(int commandEndPos){
        int j=0;
        commandEndPos++; //Step over CR (0x0D)
        
        for(int i=commandEndPos;i<bufferPos;i++){
            buffer[j]=buffer[i]; //copy bytes from buffer to first position
            j++;
        }
        
        bufferPos=j;
    }
    
    
}
