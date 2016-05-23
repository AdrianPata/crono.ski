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

public class ComTool {
    
    CommPort commPort;
    
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
                
                InputStream in = serialPort.getInputStream();
                OutputStream out = serialPort.getOutputStream();
                
                (new Thread(new SerialReader(in))).start();
                (new Thread(new SerialWriter(out))).start();
            }
        }
    }
    
    void Close(){
        commPort.close();
    }
    
    /** */
    public class SerialReader implements Runnable 
    {
        InputStream in;
        
        public SerialReader ( InputStream in )
        {
            this.in = in;
        }
        
        @Override
        public void run ()
        {
            byte[] buffer = new byte[1024];
            int len;
            try
            {
                while ( ( len = this.in.read(buffer)) > -1 )
                {
                    System.out.print(new String(buffer,0,len));
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
