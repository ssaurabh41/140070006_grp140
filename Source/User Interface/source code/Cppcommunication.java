package UserInterface;
import java.awt.Container;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

import javax.swing.JOptionPane;
//class to communicate with imageproc.exe
	/*
	 * This class is brought into use to communicate with the image processing code written in C++ using OpenCV libraries.  
This class is used when the user chooses to upload an image file. 


This class has only one function i. e. InitComm

	 */
public class Cppcommunication {
	
	
	/*
	 * Function : InitComm(String, String, Container, String, String)
	This function accepts the path of the executable file of the image processing code , the path of the image that is uploaded and the resolution of the image. It also receives the contentpane of the calling page to display a message box. 

Of these the address of the image, the resolution and a parity bit are sent to the c++ code by an output stream in the form of a single string separated by commas. The single bit helped the executable determine that if the user chose to upload an image or draw an image. This function sends a ‘1’ to denote image upload. 


	 */
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

