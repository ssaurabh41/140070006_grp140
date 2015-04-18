package UserInterface;
import java.awt.Container;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

import javax.swing.JOptionPane;
public class Cppcommunication {
	//class to communicate with imageproc.exe
	public void initComm(String address,String input,Container contentpane,String resx,String resy){
			Process p;
			
				try {
				
					
					 p= Runtime.getRuntime().exec(address);
					
					String line;
				    BufferedWriter out=new BufferedWriter(new OutputStreamWriter(p.getOutputStream()));
				    //send the address of the image to imageproc.exe
				    out.flush();
				 // 1 means that the user has uploaded an image and its path is also being sent
				    // the four parameters are sent as a string separated by commas 
				    out.write("1,");
				    
				    out.flush();
				    
				    
				    out.write(resx+",");
				    out.write(resy+",");
				    out.write(input);
				    System.out.println(resx);
				    System.out.println(resy);
				    
				    out.close();
				    System.out.println("input done");
				    
				    BufferedReader in =new BufferedReader(new InputStreamReader(p.getInputStream()));
				    
				    // gets error status from imageproc.exe
				    
				     line=in.readLine();
				    	 
				     JOptionPane.showInternalMessageDialog(contentpane , line);
				 
				     p.destroy();
				    
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				
				
			
		

		
	}
}

