import java.util.concurrent.*;
import java.util.Set;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * Booklet entry type
 * Mandatory fields: title
 */

public class booklet extends Entry {
	public void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException
	{
		mkey = key;
		Set<String> set = m.keySet();
		hm = m;
		
		//czy sa obowiazkowe pola
		Contains("title");
		
		//usun ignorowane
		for(String s : set)
		{
			switch(s)
			{
			case "title":
			case "opt":
			case "author":
			case "howpublished":
			case "address":
			case "month":
			case "year":
			case "note":
			case "key": break;
			default:
				hm.remove(s);
			}
		}
	}
}
