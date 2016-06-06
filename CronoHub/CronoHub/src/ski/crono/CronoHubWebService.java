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
    
    @Override
    public void run(){
        String ksName = "/raid/Proiecte/Disertatie/crono.ski.prod/keystore.ks";
        char ksPass[] = "salam".toCharArray();
        char ctPass[] = "salam".toCharArray();
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
            BufferedWriter w=null;
            BufferedReader r=null;
            do{
                try{
                    System.out.println("Webservice listening...");
                    c=(SSLSocket)s.accept();
                    w=new BufferedWriter(new OutputStreamWriter(c.getOutputStream()));
                    r=new BufferedReader(new InputStreamReader(c.getInputStream()));
                    String m=r.readLine();
                    w.write("HTTP/1.0 200 OK");
                    w.newLine();
                    w.write("Content-Type: text/html");
                    w.newLine();
                    w.newLine();
                    w.write("Hello World!");
                    w.newLine();
                    w.flush();
                }catch(Exception ex){
                    System.out.println("WebService err: "+ex.getMessage());
                }finally{
                    if(w!=null) w.close();
                    if(r!=null) r.close();
                    if(c!=null) c.close();
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
