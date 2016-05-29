/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ski.crono;

import com.google.gson.Gson;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.List;
import java.util.Map;

/**
 *
 * @author MPLAB
 */
public class CronoWebInt {
    String cookie="";
    String targetURL="http://crono/service.php"; 
    
    public void doLogin(){
        System.out.println(getServiceData("com=login&usr=adi&pass=salam"));
    }
    
    public void doServ(){
        Gson gson = new Gson();
        
        String urlParameters="com=serv";
        
        TrackTime tt=new TrackTime();
        tt.code="OOPP";
        tt.totalTime=(float)27.54321;
        
        String t=gson.toJson(tt);
        urlParameters+="&time="+t;
        
        System.out.println(getServiceData(urlParameters));
    }
    
    public void doStart(){
        Gson gson = new Gson();
        
        String urlParameters="com=serv";
        
        TrackTime tt=new TrackTime();
        tt.code="AABBCC";
        tt.totalTime=(float)4.539;
        
        String t=gson.toJson(tt);
        urlParameters+="&time="+t;
        
        System.out.println(getServiceData(urlParameters));
    }
    
    public String getServiceData(String urlParameters){
        URL url;
        HttpURLConnection connection = null;
        
        try{
            url = new URL(targetURL);
            connection = (HttpURLConnection)url.openConnection();
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");

            connection.setRequestProperty("Content-Length", "" + Integer.toString(urlParameters.getBytes().length));
            connection.setRequestProperty("Content-Language", "en-US");  
            connection.setRequestProperty("Cookie",cookie);

            connection.setUseCaches (false);
            connection.setDoInput(true);
            connection.setDoOutput(true);

            //Send request
            DataOutputStream wr = new DataOutputStream (connection.getOutputStream());
            wr.writeBytes (urlParameters);
            wr.flush ();
            wr.close ();
            
            //Get cookie
            Map<String, List<String>> headerFields = connection.getHeaderFields();
            List<String> cookiesHeader = headerFields.get("Set-Cookie");
            
            if(cookiesHeader!=null && cookiesHeader.size()!=0) {
                for(int i=0;i<cookiesHeader.size();i++){
                    System.out.println("Cookie: "+cookiesHeader.get(i));
                }
                cookie=cookiesHeader.get(0);
            }

            //Get Response	
            InputStream is = connection.getInputStream();
            BufferedReader rd = new BufferedReader(new InputStreamReader(is));
            String line;
            StringBuffer response = new StringBuffer(); 
            while((line = rd.readLine()) != null) {
              response.append(line);
              response.append('\r');
            }
            rd.close();
            return response.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return "Err";
        } finally {
            if(connection != null) {
                connection.disconnect(); 
            }
        }
    }
}
