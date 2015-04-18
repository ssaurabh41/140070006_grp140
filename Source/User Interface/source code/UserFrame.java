package UserInterface;

//this frame is used for both
//1. uploading the image
//2. browsing the image creating tool



import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.SpringLayout;
import javax.swing.filechooser.FileNameExtensionFilter;

/*
 * This is by far the most extensive class. It generates the form which allows the user to upload the image and resolution in X and Y direction. 



It has four Buttons:
Browse
Enter
Clear
Back

Browse Button : It opens up the window which allows the user to browse  
                           and select the file. 

Enter Button :     It calls the function initComm of CppCommunication or 
                           CppComm1. 

Clear Button :     It clears the Text Fields

Back Button :      It closes this window and takes the user back to the 
main page. 
                          

 */
public class UserFrame  {
	final public JFrame frame;
	final public Container contentpane;
	final public JTextField resolutionx;
	final public JTextField resolutiony;
	
	
	public JTextField pathtext;

	//this function converts the address of the image browsed to address of 
	//imageproc.exe which is in same directory
	
	/*
	 * Function: getAddress(String)
	Return Type: String
	This function returns return the address of the executable file using the address of the image file. It uses the fact that the executable file and the image are in the same folder. 

	 */
	public String getAddress(String path){
		String newpath="";
		
		int i=0,l=0;
		
		while(i<path.length()){
			
			if((path.charAt(i)==('\\'))||(path.charAt(i)==('/'))){
				l=i;
			}
			i++;
		}
			path=path.substring(0, l+1);
			System.out.println(path);
			newpath=path.concat("imageproc.exe");
			File f=new File(newpath);
			if(f.exists()==true){
				return newpath;
			}
		
			else{
				return null;
			}
		
		
	}
	
	//the constructor
	//int optionNO helps decide the task for which it is being used
	//1 : uploading the image
	//2 : browsing the image creation tool
	/*
	 * Constructor : UserFrame(int)
		It generates the upload page by adding suitable GUI elements to the window. 
		It receives an integer as a parameter. this integer indicates whether the frame will be used for uploading the image or creating the image. The following values of the input parameter carry the specified meaning. 

1 : Image Upload
2 : Image Draw



	 */
	
	public UserFrame(final int optionNo) {
		//declaration of GUI elements
		frame =new JFrame("Drawing Bot -User Interface-Upload");
		contentpane=frame.getContentPane();
		 pathtext =new JTextField(30);
		 resolutionx =new JTextField(10);
		 resolutiony=new JTextField(10);
		 resolutionx.setToolTipText("This is the magnification factor of the image that will be drawn by the bot");
		 
		 
		JButton pathbutton =new JButton("Browse");
		JLabel pathlabel=new JLabel("Path");
		JLabel resolLabel=new JLabel("Resolution");
		JLabel x=new JLabel(" X ");
		JButton submitButton=new JButton("Submit");
		JButton exitButton =new JButton("Back");
		JButton clearButton=new JButton("Clear");
		pathtext.setEnabled(false);
		pathlabel.setLabelFor(pathtext);
		
		
		SpringLayout layout= new SpringLayout();
		contentpane.setLayout(layout);
		
		//addtion of GUI elements to the frame
		
		contentpane.add(pathlabel);
		layout.putConstraint(SpringLayout.WEST, pathlabel,100, SpringLayout.WEST, contentpane);
		layout.putConstraint(SpringLayout.NORTH, pathlabel,50, SpringLayout.NORTH, contentpane);
		
		
		contentpane.add(pathtext);
		layout.putConstraint(SpringLayout.WEST, pathtext,50, SpringLayout.EAST, pathlabel);
		layout.putConstraint(SpringLayout.NORTH, pathtext,50, SpringLayout.NORTH, contentpane);
		
		contentpane.add(resolLabel);
		layout.putConstraint(SpringLayout.WEST, resolLabel,100, SpringLayout.WEST, contentpane);
		layout.putConstraint(SpringLayout.NORTH, resolLabel,100, SpringLayout.NORTH, contentpane);
		
		contentpane.add(resolutionx);
		layout.putConstraint(SpringLayout.WEST, resolutionx,20, SpringLayout.EAST, resolLabel);
		layout.putConstraint(SpringLayout.NORTH, resolutionx,100, SpringLayout.NORTH, contentpane);
		
		contentpane.add(x);
		layout.putConstraint(SpringLayout.WEST, x,20, SpringLayout.EAST, resolutionx);
		layout.putConstraint(SpringLayout.NORTH, x,100, SpringLayout.NORTH, contentpane);
		
		contentpane.add(resolutiony);
		layout.putConstraint(SpringLayout.WEST, resolutiony,20, SpringLayout.EAST, x);
		layout.putConstraint(SpringLayout.NORTH, resolutiony,100, SpringLayout.NORTH, contentpane);
		
		contentpane.add(pathbutton);
		layout.putConstraint(SpringLayout.WEST, pathbutton,150, SpringLayout.WEST, contentpane);
		layout.putConstraint(SpringLayout.NORTH, pathbutton,150, SpringLayout.NORTH, contentpane);
		
		contentpane.add(submitButton);
		layout.putConstraint(SpringLayout.WEST, submitButton,20, SpringLayout.EAST, pathbutton);
		layout.putConstraint(SpringLayout.NORTH, submitButton,0, SpringLayout.NORTH, pathbutton);
		
		contentpane.add(clearButton);
		layout.putConstraint(SpringLayout.WEST, clearButton,20, SpringLayout.EAST, submitButton);
		layout.putConstraint(SpringLayout.NORTH, clearButton,0, SpringLayout.NORTH,submitButton);
		
		contentpane.add(exitButton);
		
		layout.putConstraint(SpringLayout.WEST, exitButton,20, SpringLayout.EAST, clearButton);
		layout.putConstraint(SpringLayout.NORTH, exitButton,0, SpringLayout.NORTH,clearButton);
		
		
		pathbutton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				int a;
				//C drive is the default drive on which the file chooser opens up
				JFileChooser fileChooser=new JFileChooser("C:");
				FileNameExtensionFilter filter;
				if(optionNo==1){//uploading image
					//allows user to choose only image files
					filter=new FileNameExtensionFilter("jpeg","bmp","png","jpg");
				}
				else{//browsing the image creating tool
					//allows user to select only exe file
					filter=new FileNameExtensionFilter("exe files","exe");
				}
				
				fileChooser.setFileFilter(filter);
				a=fileChooser.showOpenDialog(fileChooser);
				File f=(fileChooser.getSelectedFile());
				if(a!=1){
					pathtext.setText(f.getPath());
				}
			}
		});
		
		submitButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				//System.out.println(pathtext.getText());
				if(pathtext.getText().equals("")){
					if(optionNo==1){
					JOptionPane.showInternalMessageDialog(contentpane, "first select an image to be processed");
					}
					else{
						JOptionPane.showInternalMessageDialog(contentpane, "first select the image generating tool executible file ");
					}
					
					
				}
				else if (resolutionx.getText().equals("")||resolutiony.getText().equals("")){
					JOptionPane.showInternalMessageDialog(contentpane, "enter the resolution data");
				}
				else{
					if(optionNo==1){
						
					
						JOptionPane.showInternalMessageDialog(contentpane, "the uploaded image is being processed");
						//class to communicate with imageproc.exe
						Cppcommunication a=new Cppcommunication();
						//string analyser converts the spaces in the address to '!'
						if(getAddress(pathtext.getText())==null){
							JOptionPane.showInternalMessageDialog(contentpane, "the file imageproc.exe is not present \n add it to the location of the image");
							return;
						}
						a.initComm(getAddress(pathtext.getText()),new StringAnalyser().analyse(pathtext.getText()),contentpane,resolutionx.getText(),resolutiony.getText());
					}
					else{
						//class to communicate with image creating tool
						CppComm1 a =new CppComm1();
						a.initComm(pathtext.getText(),contentpane,resolutionx.getText(),resolutiony.getText());
						
					}
					
				}
				
			}
		});
		
		clearButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
			pathtext.setText("");
			resolutionx.setText("");
			resolutiony.setText("");
				
			}
		});
		
		exitButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				frame.setVisible(false);
				
				
			}
		});
		frame.setVisible(true);
		frame.setSize(600, 400);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
	}
	
	public static void main(String args[]){
		
		//new UserFrame();
	}
}
