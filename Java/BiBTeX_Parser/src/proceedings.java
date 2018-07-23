import java.util.concurrent.*;
import java.util.Set;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * Proceedings entry type
 * Mandatory fields:	title
 * 						year
 */

public class proceedings extends Entry {

	@Override
	public void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException {
		mkey = key;
		Set<String> set = m.keySet();
		hm = m;
		
		//czy sa obowiazkowe pola
		Contains("title");
		Contains("year");
		
		//usun ignorowane
		for(String s : set)
		{
			switch(s)
			{
			case "editor":
			case "publisher":
			case "organization":
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
