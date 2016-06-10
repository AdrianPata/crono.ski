/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.Mac;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

/**
 *
 * @author MPLAB
 */
public class CryptoTool {
    byte[] secretSharedKey=null;
    byte[] publicSharedKey=null;
    byte[] sessionKey=null;
    int counter=0;
    
    byte[] randomKey(){
        if(publicSharedKey==null){
            SecureRandom random = new SecureRandom();
            byte bytes[] = new byte[32];
            random.nextBytes(bytes);
            publicSharedKey=bytes;
            
            //For testing, replace the generated key with fixed values
            //for(int i=0;i<32;i++) publicSharedKey[i]=(byte)0xBB;
            
            return bytes;
        } else {
            return publicSharedKey;
        }
    }
    
    byte[] hmac(byte[] key,byte[] message){
        try {
            Mac sha256_HMAC = Mac.getInstance("HmacSHA256");
            SecretKeySpec secret_key = new SecretKeySpec(key, "HmacSHA256");
            sha256_HMAC.init(secret_key);
            return sha256_HMAC.doFinal(message);
        } catch (NoSuchAlgorithmException | InvalidKeyException ex) {
            Logger.getLogger(CryptoTool.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return null;
    }
    
    byte[] base64encode(byte[] b){
        return Base64.getEncoder().encode(b);
    }
    
    byte[] base64decode(byte[] b){
        return Base64.getDecoder().decode(b);
    }
    
    byte[] AESencode(byte[] b){
        try {
            SecretKey secret = new SecretKeySpec(sessionKey, "AES");
            Cipher cipher = Cipher.getInstance("AES/ECB/NoPadding");
            cipher.init(Cipher.ENCRYPT_MODE, secret);
            return cipher.doFinal(b);
        } catch (InvalidKeyException | NoSuchAlgorithmException | NoSuchPaddingException | IllegalBlockSizeException | BadPaddingException ex) {
            Logger.getLogger(CryptoTool.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }
    
    byte[] AESdecode(byte[] b){
        try {
            SecretKey secret = new SecretKeySpec(sessionKey, "AES");
            Cipher cipher = Cipher.getInstance("AES/ECB/NoPadding");
            cipher.init(Cipher.DECRYPT_MODE, secret);
            byte[] r=cipher.doFinal(b);
            
            //Validate decrypted block (CRC and counter)
            byte crc=(byte)getCrc8(r);
            if(r[15]!=crc){
                System.out.println("CRC Failed");
                return null;
            }
            int rc; //received counter
            rc=r[0];
            rc=rc<<8;
            rc+=r[1];
            if(rc<counter){
                System.out.println("Counter failed on reception.");
                return null;
            }
            counter=rc+1; //Set the counter as the received counter and increment
            
            //Extract the payload and return
            byte[] d=new byte[r[2]]; //Byte 2 contains the payload length in block (max 12)
            for(int i=0;i<d.length;i++) d[i]=r[i+3];
            return d;
        } catch (InvalidKeyException | NoSuchAlgorithmException | NoSuchPaddingException | IllegalBlockSizeException | BadPaddingException ex) {
            Logger.getLogger(CryptoTool.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }
    
    int getCrc8(byte[] data) {
        int tmp;
        int res = 0;
        for(int i = 0; i < data.length-1; i++) { // length-1 because the last byte is the received CRC
            tmp = res << 1;
            tmp += 0xff & data[i];
            res = ((tmp & 0xff) + (tmp >> 8)) & 0xff;
        }
        return res;
    }
    
    public void setSecretSharedKey(String k){
        secretSharedKey=base64decode(k.getBytes());
        sessionKey=hmac(secretSharedKey,publicSharedKey);
        System.out.println("Session key: "+javax.xml.bind.DatatypeConverter.printHexBinary(sessionKey));
    }
}
