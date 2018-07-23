import java.util.concurrent.*;
import java.util.Set;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * Technical report entry type
 * Mandatory fields:	title
 * 						author
 * 						institution
 * 						year
 */

public class techreport extends Entry {
	public void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException
	{
		mkey = key;
		Set<String> set = m.keySet();
		hm = m;
		
		//czy sa obowiazkowe pola
		Contains("author");
		Contains("title");
		Contains("institution");
		Contains("year");
		
		//usun ignorowane
		for(String s : set)
		{
			switch(s)
			{
			case "author":
			case "title":
			case "institution":
			case "year":
			case "opt":
			case "editor":
			case "volume":
			case "number":
			case "series":
			case "address":
			case "month":
			case "organization":
			case "publisher":
			case "note":
			case "key": break;
			default:
				hm.remove(s);
			}
		}
	}
}
