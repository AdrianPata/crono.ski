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
    
    CommPort commPort;
    InputStream in;
    OutputStream out;
    
    DefaultListModel modelRX;
    
    public ComTool(DefaultListModel m){
        modelRX=m;
    }
    
    public void processCommand(String c){
        try {
            if(c.equals("AT+CPIN=0000")){
                Send("+CPIN: READY".getBytes());
                Send("+CREG: 1,\"00AA\",\"54BB\"".getBytes());
            }
        } catch (IOException ex) {
            Logger.getLogger(ComTool.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void Send(byte[] b) throws IOException{
        modelRX.addElement("<-- "+new String(b));
        out.write(0x0D);
        out.write(0x0A);
        out.write(b);
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
            for(int i=0;i<l;i++){
                buffer.add(bytes[i]);
            }
            int lc=findCRLF();
            if(lc>=0){
                com=getCommand(lc);
                ComTool.this.modelRX.addElement("--> "+com);
                ComTool.this.processCommand(com);
            } 
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
                        System.out.print(new String(b,0,len));
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
