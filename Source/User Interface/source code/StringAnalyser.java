package UserInterface;
//the class used to make data with spaces movable accross data streams

/*This class is used  while sending data to the C++ program from the GUI. 
Consists of two functions
analyse
revAnalyse

*/

public class StringAnalyser {
	
	String input;
	String output;
	//converts spaces to '!'
	/*
	 * Function : analyse(String)
Return type: String
This function receives a string as an argument. The string may contain spaces. This function replaces the space with ‘!’ (an exclamation mark). Then this modified string a returned. 

	 */
	public String analyse(String input)
	{		
		String substr=null;
			output="";
			int i =0;
			
			
			while(i<input.length())
			{	substr=input.substring(i,i+1);
				if(substr.equals(" ")){
					substr="!";
				}
				
				output=output.concat(substr);
				
				++i;
				
				
			}
			
				
		
		
		return output;
	}
	//convets spaces to '!'
	/*
	 * Function : revAnalyse(String)
Return Type :String
This function receives a string which contains spaces replaced by ‘!’ (exclamation marks). This string replaces the ‘!’ with spaces. It essentially reverses the effect of the function analyse. 


	 */
	public String revAnalyse(String input)
	{		
		String substr=null;
			output="";
			int i =0;
			
			
			while(i<input.length())
			{	substr=input.substring(i,i+1);
				if(substr.equals("!")){
					substr=" ";
				}
				
				output=output.concat(substr);
				
				++i;
				
				
			}
			
				
		
		
		return output;
	}
	
	
	public static void main(String[] args) {
			
			System.out.println(new StringAnalyser().analyse("this helps me solve the problem"));
	}
}
