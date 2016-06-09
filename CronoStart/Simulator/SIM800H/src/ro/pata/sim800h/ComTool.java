/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ro.pata.sim800h;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.UnsupportedCommOperationException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.ListIterator;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.DefaultListModel;

public class ComTool {
    Hub hub;
    CommPort commPort;
    InputStream in;
    OutputStream out;
    
    DefaultListModel modelRX;
    
    //S-a primit AT+CIPSEND
    CipSend cipsend=new CipSend();
    
    public ComTool(DefaultListModel m){
        modelRX=m;
    }
    
    public void connect(){
        if(hub==null){
            hub=new Hub(this);
            if(hub.connect()) hub.start();
        }
    }
    
    public void disconnect(){
        if(hub!=null){
            hub.disconnect();
        }
    }
    
    public void processCommand(String c){
        try {
            if(c.indexOf("AT+CPIN=")==0){
                Send("+CPIN: READY".getBytes());
                Send("+CREG: 1,\"00AA\",\"54BB\"".getBytes());
            }
            if(c.indexOf("AT+CSTT=")==0){
                Send("OK".getBytes());                
            }
            if(c.indexOf("AT+CIICR")==0){
                Send("OK".getBytes());                
            }
            if(c.indexOf("AT+CIFSR")==0){
                Send("10.135.239.169".getBytes());                
            }
            if(c.indexOf("AT+CDNSGIP=")==0){
                Send("+CDNSGIP: 1,\"crono.ski\",\"192.168.157.1\"".getBytes());                
            }
            if(c.indexOf("AT+CIPSTART=")==0){
                if(hub==null){
                    hub=new Hub(this);
                    if(hub.connect()) {
                        hub.start();
                        Send("CONNECT OK".getBytes());
                    }
                }                
            }
            if(c.indexOf("AT+CIPCLOSE=0")==0){
                hub.disconnect();
                hub=null;
                Send("CLOSE OK".getBytes());
            }
            if(c.indexOf("AT+CPOWD=1")==0){
                Send("NORMAL POWER DOWN".getBytes());
            }
            if(c.indexOf("AT+CIPSEND")==0){
                cipsend.startSending(hub);
            }
        } catch (IOException ex) {
            Logger.getLogger(ComTool.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void SendRaw(byte[] b) throws IOException{
        try {
            Thread.sleep(200);
        } catch (InterruptedException ex) {
            Logger.getLogger(ComTool.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        modelRX.addElement("<-- "+javax.xml.bind.DatatypeConverter.printHexBinary(b)+" ("+new String(b)+")");
        for(int i=0;i<b.length;i++){
            out.write(b[i]);            
            try {
                Thread.sleep(1);
            } catch (InterruptedException ex) {
                Logger.getLogger(ComTool.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
    public void Send(byte[] b) throws IOException{
                
        modelRX.addElement("<-- "+new String(b));
        out.write(0x0D);
        out.write(0x0A);
        for(int i=0;i<b.length;i++){
            out.write(b[i]);            
            try {
                Thread.sleep(1);
            } catch (InterruptedException ex) {
                Logger.getLogger(ComTool.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        out.write(0x0D);
        out.write(0x0A);
    }
    
    void Connect() throws NoSuchPortException, PortInUseException, UnsupportedCommOperationException, IOException{
        CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier("COM2");
        if ( portIdentifier.isCurrentlyOwned() )
        {
            System.out.println("Error: Port is currently in use");
        }
        else
        {
            commPort = portIdentifier.open(this.getClass().getName(),2000);
            if ( commPort instanceof SerialPort )
            {
                SerialPort serialPort = (SerialPort) commPort;
                serialPort.setSerialPortParams(19200,SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
                
                in = serialPort.getInputStream();
                out = serialPort.getOutputStream();
                
                (new Thread(new SerialReader(in))).start();
                (new Thread(new SerialWriter(out))).start();
            }
        }
    }
    
   
    /** */
    public class SerialReader implements Runnable 
    {
        InputStream in;
        ArrayList<Byte> buffer=new ArrayList<>();
        
        public SerialReader ( InputStream in )
        {
            this.in = in;
        }
        
        int findCRLF(){
            int p=0;
            for(Byte b:buffer){
                if(b==0x0D) return p;
                p++;
            }
            return -1;
        }
        
        String getCommand(int p){
            String r="";
            ListIterator<Byte> lst=buffer.listIterator();
            for(int i=0;i<p;i++){
                r+=(char)(byte)lst.next();
                lst.remove();
            }
            lst.next(); //the last one is 0x0D. we don't want to add that.
            lst.remove();
            return r;
        }
        
        void processIn(byte[] bytes,int l){
            String com;
            boolean processed=false;
            
            for(int i=0;i<l;i++){
                if(ComTool.this.cipsend.needMore()){ //Daca trebuie sa transmitem octeti catre Hub, nu-i mai punem in buffer
                    ComTool.this.cipsend.sendByte(bytes[i]);
                }else{                
                    buffer.add(bytes[i]);
                }
            }
            
            do{
                int lc=findCRLF();
                if(lc>=0){
                    com=getCommand(lc);
                    System.out.println(com);
                    ComTool.this.modelRX.addElement("--> "+com);
                    ComTool.this.processCommand(com);
                    
                    if(ComTool.this.cipsend.needMore()){ //Daca exista octeti in buffer si trebuie sa transmitem date catre Hub, incepem sa-i luam din buffer
                        ListIterator<Byte> lst=buffer.listIterator();
                        while(lst.hasNext() && ComTool.this.cipsend.needMore()){
                            ComTool.this.cipsend.sendByte((byte)lst.next());
                            lst.remove();
                        }
                    }
                } else {
                    processed=true;
                }
            }while(!processed);
        }
        
        @Override
        public void run ()
        {
            byte[] b = new byte[1024];
            int len;
            try
            {
                while ( ( len = this.in.read(b)) > -1 )
                {
                    if(len>0){
                        processIn(b,len);
                    }
                }
            }
            catch ( IOException e )
            {
                e.printStackTrace();
            }            
        }
    }

    /** */
    public class SerialWriter implements Runnable 
    {
        OutputStream out;
        
        public SerialWriter ( OutputStream out )
        {
            this.out = out;
        }
        
        @Override
        public void run ()
        {
            try
            {                
                int c;
                while ( ( c = System.in.read()) > -1 )
                {
                    this.out.write(c);
                }                
            }
            catch ( IOException e )
            {
                e.printStackTrace();
            }            
        }
    }
}
