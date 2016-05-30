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
    byte[] secretKey=new byte[] {(byte)0xcb,(byte)0x07,(byte)0x1D,(byte)0x84,(byte)0x75,(byte)0xFA,(byte)0x8C,(byte)0x73,(byte)0xB7,(byte)0x30,(byte)0x81,(byte)0xAA,(byte)0x14,(byte)0xAF,(byte)0x78,(byte)0x83,(byte)0x07,(byte)0x68,(byte)0x2C,(byte)0x23,(byte)0x47,(byte)0xEB,(byte)0xB1,(byte)0x5D,(byte)0xAE,(byte)0xAE,(byte)0xE0,(byte)0x3D,(byte)0xF2,(byte)0x49,(byte)0x6B,(byte)0x1D};
    byte[] sharedKey=null;
    byte[] sessionKey=null;
    
    byte[] randomKey(){
        if(sharedKey==null){
            SecureRandom random = new SecureRandom();
            byte bytes[] = new byte[32];
            random.nextBytes(bytes);
            sharedKey=bytes;
            return bytes;
        } else {
            return sharedKey;
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
            SecretKey secret = new SecretKeySpec(secretKey, "AES");
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.ENCRYPT_MODE, secret);
            return cipher.doFinal(b);
        } catch (InvalidKeyException | NoSuchAlgorithmException | NoSuchPaddingException | IllegalBlockSizeException | BadPaddingException ex) {
            Logger.getLogger(CryptoTool.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }
    
    byte[] AESdecode(byte[] b){
        try {
            SecretKey secret = new SecretKeySpec(secretKey, "AES");
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.DECRYPT_MODE, secret);
            return cipher.doFinal(b);
        } catch (InvalidKeyException | NoSuchAlgorithmException | NoSuchPaddingException | IllegalBlockSizeException | BadPaddingException ex) {
            Logger.getLogger(CryptoTool.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }
    
    int getCrc8(byte[] data) {
        int tmp;
        int res = 0;
        for(int i = 0; i < data.length; i++) {
            tmp = res << 1;
            tmp += 0xff & data[i];
            res = ((tmp & 0xff) + (tmp >> 8)) & 0xff;
        }
        return res;
    }
}
