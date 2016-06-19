/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import com.google.gson.Gson;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.SocketException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.net.ssl.SSLSocket;
import ski.crono.servicePJO.WSReceivedCommand;

/**
 *
 * @author adi
 */
public class CronoHubWebServiceClient extends Thread {
    SSLSocket c=null;
    BufferedWriter w=null;
    BufferedReader r=null;
    CronoHubNetServerManager netmgr;
    
    public CronoHubWebServiceClient(SSLSocket sock,CronoHubNetServerManager n){
        this.c=sock;
        netmgr=n;
    }
    
    @Override
    public void run(){
        
        try {
            c.setSoTimeout(5000);
        
            w=new BufferedWriter(new OutputStreamWriter(c.getOutputStream()));
            r=new BufferedReader(new InputStreamReader(c.getInputStream()));

            //Parse header - search for content length
            int dataLen=0;
            String m;            
            while ((m = r.readLine()) !=null) {
                if(m.startsWith("Content-Length:")){
                    dataLen=Integer.parseInt(m.split(":")[1].trim());
                }
                if(m.length()==0) break;
            }
            
            //Get data
            StringBuffer recvData=null;
            if(dataLen>0){
                int d;
                recvData=new StringBuffer();
                while((d=r.read())>=0){                    
                    recvData.append((char)d);
                    dataLen--;
                    if(dataLen==0) break;
                }
            }
            
            WSReceivedCommand command=null;
            boolean commandOk=false;
            if(recvData!=null){
                Gson gson = new Gson();
                command=gson.fromJson(recvData.toString(), WSReceivedCommand.class);
                if(command.usr!=null && command.pass!=null && command.usr.equals("adi") && command.pass.equals("salam")){
                    commandOk=true;
                    System.out.println("Webservice command: "+command.com);
                } else {
                    System.out.println("Webservice command failed."+recvData.toString());
                }
                
            }

            if(commandOk){
                if(command!=null && command.com.equals("shut")){
                    System.out.println("Shutting down GSM module...");
                    netmgr.shutDownCronoStart();
                }
                w.write("HTTP/1.0 200 OK");
                w.newLine();
                w.write("Content-Type: text/html");
                w.newLine();
                w.newLine();
                w.write("Command OK");
                w.newLine();
            } else {
                w.write("HTTP/1.0 403 Forbidden");
                w.newLine();
                w.write("Content-Type: text/html");
                w.newLine();
                w.newLine();
                w.write("Access denied.");
                w.newLine();
            }
            w.flush();            
        } catch (SocketException ex) {
            Logger.getLogger(CronoHubWebServiceClient.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(CronoHubWebServiceClient.class.getName()).log(Level.SEVERE, null, ex);
        }finally{
            try{
                if(w!=null) w.close();
                if(r!=null) r.close();
                if(c!=null) c.close();
            }catch(Exception ex){
                ex.printStackTrace();
            }
        }
    }
}
