package UserInterface;

import java.awt.Container;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

import javax.swing.JOptionPane;

public class Test {
	public void initComm(String path,Container contentpane,int resx,int resy){
		Process p;
		String line;
	
			try {
						//executes the .exe file
				 p= Runtime.getRuntime().exec(path);
				System.out.println("done");
				  BufferedWriter out=new BufferedWriter(new OutputStreamWriter(p.getOutputStream()));
				  				  out.write(1);
				  /*
				 // line=in.readLine();
				  out.write(resx);
				 // line=in.readLine();
				  out.write(resy);
				  System.out.println("output done");
				//gets error status from .exe file
				*/
				  BufferedReader in =new BufferedReader(new InputStreamReader(p.getInputStream()));
				  	line=in.readLine();
				  	while((line.equals(null))==false){
				     System.out.println(line);
				     line=in.readLine();
				  	}
				    	 System.out.println("input taken");
				    // JOptionPane.showInternalMessageDialog(contentpane , line);
				     System.out.println(line);
			    System.out.println("connection established");
			   p.destroy();
			    
			    
			    
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	}
	public static void main(String[] args) {
		
		
		
		new Test().initComm("C:\\Users\\Saurabh Pinjani\\Desktop\\javacpp2",new Container(),5,5);
		
	}
	
}
