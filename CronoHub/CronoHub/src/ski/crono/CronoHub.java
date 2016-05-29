package ski.crono;

import java.io.*; 
import java.net.*;

public class CronoHub {
    static CronoHubNetServerManager netmgr=new CronoHubNetServerManager();

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input;
        CronoWebInt cw=new CronoWebInt();
        
        netmgr.start();
        
        do{
            input = br.readLine();
            if(input.equals("login")) cw.doLogin();
            if(input.equals("serv")) cw.doServ();
            
        } while (!input.equals("x"));
        
        netmgr.killAllServers();
        
        
    }
    
}
