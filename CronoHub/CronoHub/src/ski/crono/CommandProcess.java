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
    
    //If the command contains encrypted data, the data is decrypted and placed into orders
    LinkedList<Byte> orderBytes=new LinkedList<Byte>();
    ArrayList<Byte> order=null;
    
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
                server.webInt.updateWebStatus("CronoStartConnected");
            }else{
                System.out.println(id+" invalid connection.");
                server.close();
            }
        }
        
        //Encrypted data received from CronoStart
        if(com.toString().startsWith("DAT:")){
            String[] el=com.toString().split(":");
            byte[] r=server.crypto.AESdecode(server.crypto.base64decode(el[1].getBytes()));
            if(r!=null){
                System.out.println("Decoded data: "+new String(r));
                //Add bytes to orders
                for(byte b:r) orderBytes.add(b);
                //Try to ansamble an order
                while(!orderBytes.isEmpty()){
                    byte b=orderBytes.removeFirst();
                    if(b!=0x0D){
                        if(order==null) order=new ArrayList<>();
                        order.add(b);
                    }else{
                        processOrder();
                        order=null;
                    }
                }
            }
        }
    }
    
    private void processOrder(){
        //Card ID received
        if(indexOfArray(order,"RFID:".getBytes())==0){
            byte[] rfid=getByteArray(order,5); //Step over "RFID:"
            String rfidB64=new String(server.crypto.base64encode(rfid));
            System.out.println("RFID received: "+javax.xml.bind.DatatypeConverter.printHexBinary(rfid));
            if(server.webInt.validateRFID(rfidB64)){
                server.sendOrder("RFID OK".getBytes());
            }else {
                server.sendOrder("RFID ERR".getBytes());
            }
        }
        
        //Stopwatch started
        if(indexOfArray(order,"SW:START".getBytes())==0){
            System.out.println("Stopwatch started");
            server.webInt.updateWebStatus("CronoStartSTART");
        }

        //Stopwatch stopped
        if(indexOfArray(order,"SW:FINISH".getBytes())==0){
            byte[] time=getByteArray(order,9); //Step over "SW:FINISH"
            long t=0;
            double tRez=0;
            
            //Decode time. There are 6 bytes of time.
            for (int i = 0; i < 6; i++)
            {
                t +=((long) time[i] & 0xffL); //<< (8 * i);
                if(i<5) t=t<<8;
            }
            
            tRez=(double)t/(16000000/4/8); //FOSC=16Mhz.; one increment every 4 cycles; prescaler is 1:8
            
            System.out.println("Time received ["+tRez+" seconds]["+t+"]: "+javax.xml.bind.DatatypeConverter.printHexBinary(time));
            System.out.println("Stopwatch stopped");
            server.webInt.updateResult(t);
            server.webInt.updateWebStatus("CronoStartFINISH");
        }
    }
    
    //Find the possition of srch in the ArrayList
    private int indexOfArray(ArrayList<Byte> barr,byte[] srch){
        byte[] a=new byte[barr.size()];
        for(int i=0;i<barr.size();i++){
            a[i]=barr.get(i);
        }
        
        String s1=new String(a);
        String s2=new String(srch);
        
        return s1.indexOf(s2);
    }
    
    //Get byte array from ArrayList starting from position s
    private byte[] getByteArray(ArrayList<Byte> barr,int s){
        byte[] a=new byte[barr.size()-s];
        for(int i=s;i<barr.size();i++){
            a[i-s]=barr.get(i);
        }
        
        return a;
    }
}
