import java.util.*;
import java.util.concurrent.*;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * Article entry type
 * Mandatory fields:	author
 * 						title
 * 						journal
 * 						year
 */


public class article extends Entry {
	public void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException
	{
		mkey = key;
		Set<String> set = m.keySet();
		hm = m;
		
		//czy sa obowiazkowe pola
		Contains("author");
		Contains("title");
		Contains("journal");
		Contains("year");
		//usun ignorowane
		for(String s : set)
		{
			switch(s)
			{
			case "author":
			case "title":
			case "journal":
			case "year":
			case "opt":
			case "volume":
			case "number":
			case "pages":
			case "month":
			case "note":
			case "key": break;
			default:
				hm.remove(s);
			}
		}
	}
}
