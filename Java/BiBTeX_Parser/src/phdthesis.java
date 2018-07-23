import java.util.concurrent.*;
import java.util.Set;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * phd thesis entry type
 * Mandatory fields:	title
 * 						author
 * 						school
 * 						year
 */

public class phdthesis extends Entry {
	public void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException
	{
		mkey = key;
		Set<String> set = m.keySet();
		hm = m;
		
		//czy sa obowiazkowe pola
		Contains("author");
		Contains("title");
		Contains("school");
		Contains("year");
		
		//usun ignorowane
		for(String s : set)
		{
			switch(s)
			{
			case "author":
			case "opt":
			case "type":
			case "address":
			case "month":
			case "note":
			case "key": break;
			default:
				hm.remove(s);
			}
		}
	}
}
