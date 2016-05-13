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
    private CryptoTool crypto;
    
    public CommandProcess(int id,CryptoTool c){
        this.id=id;
        this.crypto=c;
    }
    
    //Add received to buffer
    public void addBytes(byte[] b,int length){
        for (int i=0;i<length;i++){
            buffer[bufferPos+i]=b[i];
        }
        bufferPos+=length;
        
        //Search for a command in buffer. Get command end position if found and process command.
        int ce=identifyCommand();
        if(ce>=0)processCommand(ce);
    }
    
    //Search in buffer for a command terminator
    private int identifyCommand(){
        for (int i=0;i<bufferPos;i++){
            if(buffer[i]==0x0D && buffer[i+1]==0x0A){ //CRLF found
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
        
        if(command.toString().startsWith("SEND")){
            String cnt=command.toString().substring(4,command.toString().length());
            Log.out("Mesaj: "+new String(crypto.AESdecode(crypto.base64decode(cnt.getBytes()))));
        }
    }
    
    //Discard command from buffer
    private void discardCommand(int commandEndPos){
        int j=0;
        commandEndPos+=2; //Step over CRLF (0x0D and 0x0A)
        
        for(int i=commandEndPos;i<bufferPos;i++){
            buffer[j]=buffer[i]; //copy bytes from buffer to first position
            j++;
        }
        
        bufferPos=j;
    }
    
    
}
