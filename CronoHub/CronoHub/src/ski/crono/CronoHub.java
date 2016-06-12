package ski.crono;

import java.io.*; 
import java.net.*;

public class CronoHub {
    static CronoHubNetServerManager netmgr=new CronoHubNetServerManager();

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input;        
        
        //Start web service
        CronoHubWebService ws=new CronoHubWebService();
        ws.start();
        
        //Log in to the web service
        CronoWebInt cw=new CronoWebInt();
        if(!cw.doLogin()){ //Invalid login
            System.out.println("Can not log in to web service.");
            return;
        }
        cw.resetWebStatus();
        
        netmgr.setWebInterface(cw);
        netmgr.start();
        
        do{
            input = br.readLine();
            if(input.equals("login")) cw.doLogin();
            if(input.equals("serv")) cw.doServ();
        } while (!input.equals("x"));
        
        netmgr.killAllServers();
        ws.close();
    }
    
    public static void test(){
        CryptoTool c=new CryptoTool();
        byte[] b={(byte)0x00,(byte)0x01,(byte)0x06,(byte)0x41,(byte)0x64,(byte)0x72,(byte)0x69,(byte)0x61,(byte)0x6e,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0xb6};
        int r=c.getCrc8(b);
        System.out.println(r);
    }
}
