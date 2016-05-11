/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

/**
 *
 * @author MPLAB
 */
public class CommandProcess {
    byte[] buffer=new byte[1000];
    int bufferPos=0; //Buffer insert position. If it is 0, buffer is empty.
    
    public void addBytes(byte[] b,int length){
        for (int i=0;i<length;i++){
            buffer[bufferPos+i]=b[i];
        }
        bufferPos+=b.length;
    }
    
    
}
