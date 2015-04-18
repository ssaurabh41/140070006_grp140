package UserInterface;


import java.awt.Container;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

import javax.swing.JOptionPane;
// class to communicate with image generating tool
public class CppComm1 {
	//recieves path of the exe file from the GUI 
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
