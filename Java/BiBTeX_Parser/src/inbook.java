import java.util.*;
import java.util.concurrent.*;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * Inbook entry type
 * Mandatory fields:	author or editor
 * 						title
 * 						pages or chapter
 * 						publisher
 * 						year
 */

public class inbook extends Entry {
	public void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException
	{
		mkey = key;
		hm = m;
		
		//czy sa obowiazkowe pola
		Contains("author", "editor");
		Contains("title");
		Contains("pages", "chapter");
		Contains("publisher");
		Contains("year");
		
		//usun ignorowane
		for(Iterator<Map.Entry<String, String>> it = hm.entrySet().iterator(); it.hasNext(); )
		{
			Map.Entry<String, String> entry = it.next();
			switch(entry.getKey())
			{
			case "author":
			case "editor":
			case "title":
			case "pages":
			case "chapter":
			case "publisher":
			case "year":
			case "opt":
			case "volume":
			case "number":
			case "series":
			case "type":
			case "address":
			case "edition":
			case "month":
			case "note":
			case "key": break;
			default:
				it.remove();
			}
		}
	}
}
