package ski.crono;

import java.io.*; 
import java.net.*;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.KeyPair;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.util.Base64;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;

public class CronoHub {
    static CronoHubNetServerManager netmgr=new CronoHubNetServerManager();

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input;   
        
        System.out.println("CronoHub v.1.2");
        
        Console console = System.console();
        if (console == null) {
            System.out.println("Couldn't get Console instance");
            System.exit(0);
        }

        CryptoTool.globalKeystorePassword= console.readPassword("Enter keystore password: ");        
        CryptoTool.loadRSAKeys();
        
        //Log in to the CronoWeb web service
        CronoWebInt cw=new CronoWebInt();
        if(!cw.doLogin()){ //Invalid login
            System.out.println("Can not log in to web service.");
            return;
        }
        cw.resetWebStatus();
        
        netmgr.setWebInterface(cw);
        netmgr.start();

        //Start local web service
        CronoHubWebService ws=new CronoHubWebService(netmgr);
        ws.start();
        
        do{
            input = br.readLine();
            if(input.equals("login")) cw.doLogin();
            if(input.equals("serv")) cw.doServ();
        } while (!input.equals("x"));
        
        netmgr.killAllServers();
        ws.close();
    }
    
    public static void test(){
        
        byte[] k=new byte[32];
        for(int i=0;i<32;i++){
            k[i]=(byte)0xAA;
        }
        
        byte[] e=CryptoTool.RSAencrypt(k);
        byte[] b=Base64.getEncoder().encode(e);        
        
        System.out.println(new String(b));
        
        //byte[] d=CryptoTool.RSAdecrypt(e);               
        //System.out.println(javax.xml.bind.DatatypeConverter.printHexBinary(d));
    }


}
