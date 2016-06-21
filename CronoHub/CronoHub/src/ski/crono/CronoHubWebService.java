/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.security.KeyStore;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.net.ssl.KeyManagerFactory;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLServerSocket;
import javax.net.ssl.SSLServerSocketFactory;
import javax.net.ssl.SSLSocket;

/**
 *
 * @author adi
 */
public class CronoHubWebService extends Thread {
    SSLServerSocket s;
    boolean listen=true;
    CronoHubNetServerManager netmgr;
    
    public CronoHubWebService(CronoHubNetServerManager n){
        netmgr=n;
    }
    
    @Override
    public void run(){
        String ksName = "keystore.ks";
        char ksPass[] = CryptoTool.globalKeystorePassword;
        char ctPass[] = CryptoTool.globalKeystorePassword;
        try{
            KeyStore ks=KeyStore.getInstance("JKS");
            ks.load(new FileInputStream(ksName),ksPass);
            
            KeyManagerFactory kmf=KeyManagerFactory.getInstance("SunX509");
            kmf.init(ks,ctPass);
            SSLContext sc=SSLContext.getInstance("TLS");
            sc.init(kmf.getKeyManagers(), null, null);
            SSLServerSocketFactory ssf=sc.getServerSocketFactory();
            s=(SSLServerSocket)ssf.createServerSocket(3898);
            System.out.println("WebService started.");
            SSLSocket c=null;
            do{
                try{
                    System.out.println("Webservice listening on 3898...");
                    c=(SSLSocket)s.accept();
                    CronoHubWebServiceClient cl=new CronoHubWebServiceClient(c,netmgr);
                    cl.start();
                    
                }catch(Exception ex){
                    System.out.println("WebService err: "+ex.getMessage());
                }                
            }while(listen);
        }catch(Exception ex){
            //ex.printStackTrace();
            System.out.println("WebService err: "+ex.getMessage());
        }       
    }
    
    public void close(){
        try {
            listen=false;
            s.close();
        } catch (IOException ex) {
            Logger.getLogger(CronoHubWebService.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
