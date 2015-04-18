package UserInterface;
/*
  this is class that has the main page that loads first .
 */
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JRadioButton;
import javax.swing.SpringLayout;
/*
 * The execution of the inteface starts with the execution of this class. 
Used to generate the main page or the opening window of the GUI. 
Consists of two Radio buttons and two command buttons. 

The two radio button direct to 
Upload Image
Create Image

The two buttons are 
Enter
Exit

Enter Button: Opens up the next window depending upon the selected                           
                       radio button. If none of the options are selected the user 
                       is prompted to select one and then press Enter. 
Exit Button : Closes the application

Constructor: MainPage()
		It generates the main page. 
		Also calls the constructor of class UserFrame. 

Main Function : Explicitely calls the constructor of this class


 */
public class MainPage {
	final JFrame frameMain;
	final Container contentpane;
	
	
	public MainPage() {
		
		//declaration of GUI object
		frameMain =new JFrame("Drawing Bot -User Interface-Main Page");
		 contentpane=frameMain.getContentPane();
		final JRadioButton op1=new JRadioButton("Upload image");
		final JRadioButton op2=new JRadioButton("Make an image");
		JButton enter= new JButton("Enter");
		JButton exit=new JButton("Exit");
		
		//addition of GUI Objects to the frame.
		// setting the layout
		SpringLayout layout= new SpringLayout();
		contentpane.setLayout(layout);
		
		contentpane.add(op1);
		layout.putConstraint(SpringLayout.WEST, op1,100, SpringLayout.WEST, contentpane);
		layout.putConstraint(SpringLayout.NORTH, op1,150, SpringLayout.NORTH, contentpane);
		
		contentpane.add(op2);
		layout.putConstraint(SpringLayout.WEST, op2,300, SpringLayout.WEST, contentpane);
		layout.putConstraint(SpringLayout.NORTH, op2,150, SpringLayout.NORTH, contentpane);
		
		contentpane.add(enter);
		layout.putConstraint(SpringLayout.WEST, enter,150, SpringLayout.WEST, contentpane);
		layout.putConstraint(SpringLayout.NORTH, enter,250, SpringLayout.NORTH, contentpane);
		
		contentpane.add(exit);
		layout.putConstraint(SpringLayout.WEST, exit,300, SpringLayout.WEST, contentpane);
		layout.putConstraint(SpringLayout.NORTH, exit,250, SpringLayout.NORTH, contentpane);
		//grouping the option buttons
		ButtonGroup group = new ButtonGroup();
	    group.add(op1);
	    group.add(op2);
	    
	    
		
		enter.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				if(op1.isSelected()==true){
					
					new UserFrame(1);
					//creating the frame to upload the picture
				}
				
				else if(op2.isSelected()==true){
					
					System.out.println("to be done");
					new UserFrame(2);
					//creating the frame to browse the image creating tool
					
				}
				else {
					JOptionPane.showInternalMessageDialog(contentpane, "First select an Option");
				}
				
			}
		});
		exit.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
				
			}
		});
		
		frameMain.setVisible(true);
		frameMain.setSize(600, 400);
		frameMain.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		
	}
	
	public static void main(String[] args) {
		new MainPage();
	}
}
