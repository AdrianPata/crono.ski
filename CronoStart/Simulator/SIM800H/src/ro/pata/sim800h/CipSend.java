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
    int total=0;
    Hub hub;
    
    public void startSending(int t,Hub h){
        hub=h;
        total=t;
        toSend=true;
    }
    
    public boolean needMore(){
        return toSend;
    }
    
    public void sendByte(byte b){
        buffer[l]=b;
        l++;
        if(l==total){
            hub.send(buffer,l);
            toSend=false;
            l=0;
            total=0;
        }
    }
}
