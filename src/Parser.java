import java.util.*;
import java.util.concurrent.*;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * 
 * Singleton Parser class
 * 
 */


public class Parser {
	
	private Parser() {}
	
	/**
	 * <p>
	 * Singleton instance of class Parser
	 * <p>
	 */
	static public Parser P = new Parser();
	
	/**
	 * <p>
	 * Checks if the given character is whitespace
	 * <p>
	 * 
	 * @param c character to check
	 * @return true if c is whitespace; false otherwise
	 */
	boolean WhiteChar(char c)
	{
		switch(c)
		{
		case '\n':				//nowa linia
		case ' ': 				//spacja
		case '\r':				//powrót karetki
		case 9: return true;	//tab
		}
		return false;
	}
	
	/**
	 * <p>
	 * Checks if the given character is a letter
	 * <p>
	 * @param c character to check
	 * @return true if c is a letter; false otherwise
	 */
	boolean IsLetter(char c)
	{
		if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))return true;
		return false;
	}
	
	/**
	 * <p>
	 * Checks if the given character is a digit
	 * <p>
	 * @param c character to check
	 * @return true if c is a digit; false otherwise
	 */
	boolean IsDigit(char c)
	{
		if(c >= 48 && c <= 57) return true;
		return false;
	}
	
	/**
	 * <p>
	 * Checks if the given character is a letter or a digit
	 * <p>
	 * @param c character to check
	 * @return true if c is a letter or a digit; false otherwise
	 */
	boolean IsDigitLetter(char c)
	{
		return (IsDigit(c) || IsLetter(c));
	}
	
	/**
	 * <p>
	 * Converts String representation of a BiBTeX file to a collection of Entries
	 * <p>
	 * @param src BiBTeX file content
	 * @return Collection of Entries
	 */
	public Vector<Entry> Open(String src) {
		Map<String, String> spval = new ConcurrentHashMap<String, String>();
		Map<String, String> rmap = new ConcurrentHashMap<String, String>();
		
		rmap.put("jan", "January");
		rmap.put("feb", "February");
		rmap.put("mar", "March");
		rmap.put("apr", "April");
		rmap.put("may", "May");
		rmap.put("jun", "June");
		rmap.put("jul", "July");
		rmap.put("aug", "August");
		rmap.put("sep", "September");
		rmap.put("oct", "October");
		rmap.put("nov", "November");
		rmap.put("dec", "December");
		
		
		
		Vector<Entry> v = new Vector<Entry>();
		for(int i = 0; i < src.length();i++)
		{
			char c = src.charAt(i);
			if(c != '@') continue;
			i++;
			c = src.charAt(i);
			
			//data
			String type;
			String key;
			ConcurrentHashMap<String, String> Map = new ConcurrentHashMap<>();
			
			//get type
			int beg = i;
			while(IsLetter(c))
			{
				i++;
				c = src.charAt(i);
			}
			type = src.substring(beg, i);
			type = type.toLowerCase();
			if(type.equals("comment") || type.equals("preamble"))continue;
			if(type.equals("string"))
			{
				String s1,val="";
				while(!IsDigitLetter(c))
				{
					i++;
					c = src.charAt(i);
				}
				beg = i;
				while(IsDigitLetter(c) || c == '-' || c == ':')
				{
					i++;
					c = src.charAt(i);
				}
				s1 = src.substring(beg, i);
				while(c != '{' && c != '\"' && !IsDigitLetter(c))
				{
					i++;
					c = src.charAt(i);
				}
				beg = i;
				Stack<t> st = new Stack<t>();
				boolean text = false;
				while(true)
				{
					if(c == '{')
					{
						if(st.empty() && !text)
						{
							beg = i+1;
						}
						st.push(new t());
						
					}
					else if(c == '}')
					{
						if(st.empty())
						{
							break;
						}
						st.pop();
						if(st.empty() && !text)
						{
							val = val + src.substring(beg, i);
							while(WhiteChar(c))
							{
								i++;
								c = src.charAt(i);
							}
							beg = i;
							//continue;
						}
					}
					else if(c == '\"')
					{
						if(st.empty() && text == false)
						{
							text = true;
							beg = i+1;
						}
						else if(st.empty() && text == true)
						{
							text = false;
							val = val + src.substring(beg, i);
							while(WhiteChar(c))
							{
								i++;
								c = src.charAt(i);
							}
							beg = i;
						}
					}
					else if(c == ',')
					{
						if(text == false && st.empty())
						{
							
							break;
						}
					}
					else if(IsDigit(c) && st.empty() && !text)
					{
						beg = i;
						do
						{
							i++;
							c = src.charAt(i);
						}while(IsDigit(c));
						val = val + src.substring(beg, i);
						while(WhiteChar(c))
						{
							i++;
							c = src.charAt(i);
						}
						
						beg = i;
						continue;
					}
					else if(IsLetter(c) && st.empty() && !text)
					{
						beg = i;
						do
						{
							i++;
							c = src.charAt(i);
						}while(IsDigitLetter(c) || c == '-' || c == ':');
						val = val + rmap.get(src.substring(beg, i));
						while(WhiteChar(c))
						{
							i++;
							c = src.charAt(i);
						}
						beg = i;
						continue;
					}
					i++;
					c = src.charAt(i);
				}
				rmap.put(s1, val);
				beg = i;
				continue;
			}
			//System.out.println(type);
			
			
			//get key
			while(!IsDigitLetter(c))
			{
				i++;
				c = src.charAt(i);
			}
			beg = i;
			while(IsDigitLetter(c) || c == '-' || c ==':')
			{
				i++;
				c = src.charAt(i);
			}
			key = src.substring(beg, i);
			//System.out.println(key);
			
			boolean leave = false;
			
			Stack<t> st = new Stack<t>();
			String mkey = "";
			while(!leave)
			{
				String val = "";
				while(!IsLetter(c) && c != '}')
				{
					i++;
					c = src.charAt(i);
				}
				
				if(c == '}')
				{
					leave = true;
					break;
				}
				
				beg = i;
				while(IsLetter(c))
				{
					i++;
					c = src.charAt(i);
				}
				mkey = src.substring(beg, i);
				mkey = mkey.toLowerCase();
				//System.out.print(mkey);
				
				while(WhiteChar(c))
				{
					i++;
					c = src.charAt(i);
				}
				
				beg = i;
				boolean text = false;
				while(true)
				{
					if(c == '{')
					{
						if(st.empty() && !text)
						{
							/*if(!text)beg = i+1;
							else beg = i;*/
							beg = i+1;
						}
						st.push(new t());
						
					}
					else if(c == '}')
					{
						if(st.empty())
						{
							leave = true;
							break;
						}
						st.pop();
						if(st.empty() && !text)
						{
							val = val + src.substring(beg, i);
							while(WhiteChar(c))
							{
								i++;
								c = src.charAt(i);
							}
							beg = i;
							//continue;
						}
					}
					else if(c == '\"')
					{
						if(st.empty() && text == false)
						{
							text = true;
							beg = i+1;
						}
						else if(st.empty() && text == true)
						{
							text = false;
							val = val + src.substring(beg, i);
							while(WhiteChar(c))
							{
								i++;
								c = src.charAt(i);
							}
							beg = i;
						}
					}
					else if(c == ',')
					{
						if(text == false && st.empty())
						{
							
							break;
						}
					}
					else if(IsDigit(c) && st.empty() && !text)
					{
						beg = i;
						do
						{
							i++;
							c = src.charAt(i);
						}while(IsDigit(c));
						val = val + src.substring(beg, i);
						while(WhiteChar(c))
						{
							i++;
							c = src.charAt(i);
						}
						beg = i;
						continue;
					}
					else if(IsLetter(c) && st.empty() && !text)
					{
						beg = i;
						do
						{
							i++;
							c = src.charAt(i);
						}while(IsDigitLetter(c) || c == '-' || c == ':');
						val = val + rmap.get(src.substring(beg, i));
						while(WhiteChar(c))
						{
							i++;
							c = src.charAt(i);
						}
						beg = i;
						continue;
					}
					i++;
					c = src.charAt(i);
				}
				//val = val.replace("{", "");
				//val = val.replace("}", "");
				//System.out.println(" = " + val);
				Map.put(mkey, val);
			}
			try {
				Class<?> cl =  Class.forName(type);
				Entry e = (Entry)cl.newInstance();
				e.UpdateInfo(Map, key);
				v.add(e);
				
			}catch(ClassNotFoundException e){
				System.out.println("Unknown type: " + e.getMessage());
			}catch(MandatoryFieldEmptyException e){
				System.out.println(e.toString() + " w " + type + " - " + key);
			}catch(Exception e) {
				System.out.println("Some other exception!"+ e.toString() + e.getMessage());
			}
			
		}
		return v;
	}
}
