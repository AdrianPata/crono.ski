/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.Security;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.KeySpec;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.PBEKeySpec;
import org.bouncycastle.jce.provider.BouncyCastleProvider;

/**
 *
 * @author MPLAB
 */
public class CryptoTool {
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
    
    public CryptoTool(){
        Security.addProvider(new BouncyCastleProvider());
        
        if (Security.getProvider("BC") == null){
            System.out.println("Bouncy Castle provider is NOT available");
        }
        else{
            System.out.println("Bouncy Castle provider is available");
        }
    }
    
    byte[] base64encode(byte[] b){
        return Base64.getEncoder().encode(b);
    }
    
    byte[] base64decode(byte[] b){
        return Base64.getDecoder().decode(b);
    }
    
    byte[] AESencode(byte[] b,byte[] k) throws InvalidAlgorithmParameterException{
        try {
            SecretKey secret = new SecretKeySpec(k, "AES");
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding","BC");
            cipher.init(Cipher.ENCRYPT_MODE, secret);
            return cipher.doFinal(b);
        } catch (InvalidKeyException | NoSuchAlgorithmException | NoSuchPaddingException | IllegalBlockSizeException | BadPaddingException | NoSuchProviderException ex) {
            Logger.getLogger(CryptoTool.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }
    
    byte[] AESdecode(byte[] b,byte[] k){
        try {
            SecretKey secret = new SecretKeySpec(k, "AES");
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.DECRYPT_MODE, secret);
            return cipher.doFinal(b);
        } catch (InvalidKeyException | NoSuchAlgorithmException | NoSuchPaddingException | IllegalBlockSizeException | BadPaddingException ex) {
            Logger.getLogger(CryptoTool.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }
}
