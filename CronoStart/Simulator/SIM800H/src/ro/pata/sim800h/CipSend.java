/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ro.pata.sim800h;

/**
 *
 * @author Adi
 */
public class CipSend {
    byte[] buffer=new byte[1000];
    int l=0;
    boolean toSend=false;
    boolean dataSend=false;
    Hub hub;
    
    public void startSending(Hub h){
        hub=h;
        toSend=true;
    }
    
    public boolean needMore(){
        return toSend;
    }
    
    public void sendByte(byte b){
        if(b!=0x1A){
            buffer[l]=b;
            l++;
        }else{ //Ctrl+Z received (0x1A) - send all data in buffer
            hub.send(buffer,l);
            toSend=false;
            dataSend=true;
            l=0;
        }
    }
}
