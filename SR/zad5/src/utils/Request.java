package utils;

import akka.actor.ActorRef;

import java.io.Serializable;

public class Request implements Serializable {
    //0 - find
    //1 - order
    //2 - stream
    private int type;
    private String bookName;
    private ActorRef client;

    public void setType(int type) {
        this.type = type;
    }

    public int getType() {
        return type;
    }

    public void setBookName(String bookName) {
        this.bookName = bookName;
    }

    public String getBookName() {
        return bookName;
    }

    public void setClient(ActorRef client) {
        this.client = client;
    }

    public ActorRef getClient() {
        return client;
    }

    public Request(int type, String bookName) {
        this.type = type;
        this.bookName = bookName;
    }
}
