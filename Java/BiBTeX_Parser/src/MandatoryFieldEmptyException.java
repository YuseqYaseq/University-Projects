/**
 * @author Józef Jasek
 * Exception thrown by Entries when one of the mandatory fields is missing.
 */

public class MandatoryFieldEmptyException extends Exception{
	public MandatoryFieldEmptyException(String s)
	{
		super(s);
	}
	public MandatoryFieldEmptyException(String s, Throwable t)
	{
		super(s, t);
	}
}