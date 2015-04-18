package UserInterface;


import java.awt.Container;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

import javax.swing.JOptionPane;
/*
 * 	This class is brought into use to communicate with the image processing code written in C++ using OpenCV libraries
This class is used when the user wishes to draw the image.  


This class has only one function i. e. InitComm

 */
// class to communicate with image generating tool
public class CppComm1 {
	//recieves path of the exe file from the GUI 
	
	/*
	 * Function : InitComm(String, Container, String, String)
	This function accepts the path of the executable file of the image processing code and the resolution of the image. It also recieves the contentpane of the calling page to display a message box. 

 Of these resolution are sent to the c++ code by an output stream in the form of a single string separated by commas. A parity bit is also sent. this bit helps the C++ program determine whether the user chose to draw an image or upload an image
This function sends a  ‘0’ to denote that the user chose to draw the image. 



	 */
	public void initComm(String path,Container contentpane,String resx,String resy){
		Process p;
		String line;
	
			try {
					

				 p= Runtime.getRuntime().exec(path);
				
				//String line;
			    BufferedWriter out=new BufferedWriter(new OutputStreamWriter(p.getOutputStream()));
		
			    out.flush();
			    // 0 denotes that the user will be drawing the image
			    //three parameters are being sent to the cpp code in one string separated by commas
			    out.write("0,");
			    out.flush();
			    
			   
			    out.write(resx+",");
			    out.write(resy);
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
	public static void main(String[] args) {
		//new CppComm1().initComm();;
	}
	
}
