package UserInterface;
//the class used to make data with spaces movable accross data streams

public class StringAnalyser {
	
	String input;
	String output;
	//converts spaces to '!'
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
