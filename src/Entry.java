import java.util.concurrent.*;
import java.util.Map;
import java.util.regex.*;
import java.util.*;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * Abstract Entry class representing all entries known by Parser/BiBData
 */

public abstract class Entry {
	
	/**
	 * Draws all Entry elements 
	 * @param f Character to use as frame
	 */
	public void Draw(char f)
	{
		int max = 17 + mkey.length();
		for(Map.Entry<String, String> entry : hm.entrySet())
		{
			if(entry.getKey().equals("author") || entry.getKey().equals("editor"))
			{
				Vector<String> names = toAuthor(entry.getValue());
				for(String s : names)
					if(17+s.length() > max)max = 17+s.length();
			}
			else if(17+entry.getValue().length() > max)max = 17+entry.getValue().length();
		}
		String classname = this.getClass().getSimpleName().toUpperCase();
		System.out.println(String.join("", Collections.nCopies(max, String.valueOf(f))));
		System.out.println(f + classname + String.join("", Collections.nCopies(14-classname.length(), " ")) + f + mkey + String.join("", Collections.nCopies(max-mkey.length()-17, " ")) + f);
		System.out.println(String.join("", Collections.nCopies(max, String.valueOf(f))));
		
		for(Map.Entry<String, String> entry : hm.entrySet()) {
		    String key = entry.getKey();
		    String value = entry.getValue();
		    
		    int n = 14 - key.length();
		    if(key.equals("author") || key.equals("editor"))
		    {
		    	Vector<String> names = toAuthor(value);
		    	boolean i = false;
		    	for(String s : names)
		    	{
		    		if(!i)
		    		{
		    			System.out.println(f + key + String.join("", Collections.nCopies(n, " ")) + f + s + String.join("", Collections.nCopies(max-s.length()-17, " ")) + f);
		    			i=true;
		    		}
		    		else
		    		{
		    			System.out.println(f + String.join("", Collections.nCopies(14, " ")) + f + s + String.join("", Collections.nCopies(max-s.length()-17, " ")) + f);
		    		}
		    	}
		    }
		    else System.out.println(f + key + String.join("", Collections.nCopies(n, " ")) + f + value + String.join("", Collections.nCopies(max-value.length()-17, " ")) + f);
		}
		System.out.println(String.join("", Collections.nCopies(max, String.valueOf(f))));
	}
	
	/**
	 * Checks if all mandatory fields have been placed. Removes misplaced fields.
	 * @param m Map of Key-Value (e.g. "author" - "Jozef Jasek")
	 * @param key Entry key
	 * @throws MandatoryFieldEmptyException Thrown when a manadatory field is missing.
	 */
	public abstract void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException;
	
	/**
	 * Used for checking if a field is in the HashMap
	 * @param s Key to find
	 * @throws MandatoryFieldEmptyException Thrown when the field is missing
	 */
	public void Contains(String s) throws MandatoryFieldEmptyException
	{
		if(!hm.containsKey(s))
			throw new MandatoryFieldEmptyException("brak pola obowiazkowego " + s);
	}
	
	/**
	 * Used for checking if either of fields is in the HashMap
	 * @param s1 One of the keys to find
	 * @param s2 One of the keys to find
	 * @throws MandatoryFieldEmptyException Thrown when the field is missing
	 */
	public void Contains(String s1, String s2) throws MandatoryFieldEmptyException
	{
		if(!hm.containsKey(s1) && !hm.containsKey(s2))
			throw new MandatoryFieldEmptyException("brak pola obowiazkowego " + s1 + " lub " + s2);
	}
	
	/**
	 * Used to get all different people from "author" and "editor" values (name1 and name2...)
	 * @param s "author" or "editor" value
	 * @return Vector or strings [name1] [name2] [name3]
	 */
	public Vector<String> toAuthor(String s)
	{
		Vector<String> names = new Vector<String>();
		Pattern pf = Pattern.compile("([^+]*) and ([^+]*)");
		Matcher mf = pf.matcher(s);
		String t = "";
		if(!mf.matches())
		{
			names.add(toName(s));
			return names;
		}
		while(mf.matches())
		{
			t = mf.group(1);
			names.add(toName(mf.group(2)));
			mf = pf.matcher(t);
		}
		names.add(toName(t));
		return names;
	}
	
	/**
	 * Used to convert "author" or "editor" string value to vector of strings [name] [von] [surname] [Jr]
	 * @param s "author" or "editor" value
	 * @return Vector of strings [name] [von] [surname] [Jr]
	 */
	private String toName(String s)
	{
		Pattern p1 = Pattern.compile("([A-z][a-z]*) ([a-z]*) ([A-Z][a-z]*)");
		Pattern p2 = Pattern.compile("([a-z]*) ([A-z][a-z]*), ([A-z][a-z]*)");
		Pattern p3 = Pattern.compile("([a-z]* [A-z][a-z]*), ([A-z][a-z]*), ([A-z][a-z]*)");
		
		Matcher m = p1.matcher(s);
		if(m.matches())
			return s;
		
		m = p2.matcher(s);
		if(m.matches())
			return m.group(3) + " " + m.group(1) + " " + m.group(2);
		
		m = p3.matcher(s);
		if(m.matches())
			return m.group(3) + " " + m.group(1) + " " + m.group(2);
		
		return s;
	}
	
	/**
	 * Entry key
	 */
	public String mkey;
	
	/**
	 * HashMap with all Eenry values
	 */
	public ConcurrentHashMap<String, String> hm;
}
