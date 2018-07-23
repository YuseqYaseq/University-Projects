import java.util.concurrent.*;
import java.util.Set;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * Master thesis entry type
 * Mandatory fields:	title
 * 						author
 * 						school
 * 						year
 */

public class mastersthesis extends Entry {
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
			case "title":
			case "school":
			case "year":
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
