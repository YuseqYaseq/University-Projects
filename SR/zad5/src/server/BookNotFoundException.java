package server;

public class BookNotFoundException extends Exception {
    public BookNotFoundException(String s) {
        super(s);
    }
}
