package utils;

import akka.actor.Actor;
import akka.actor.ActorRef;

import java.io.Serializable;

public class Response implements Serializable {
    private String content;
    private int value;
    private ActorRef client;

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public Response(String content, int value) {
        this.content = content;
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public void setClient(ActorRef client) {
        this.client = client;
    }

    public ActorRef getClient() {
        return client;
    }
}
