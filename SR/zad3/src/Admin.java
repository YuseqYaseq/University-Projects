import com.rabbitmq.client.AMQP;
import com.rabbitmq.client.Channel;
import com.rabbitmq.client.Consumer;
import com.rabbitmq.client.Envelope;

import java.io.IOException;

public class Admin {
    private Channel infoChannel;

    private Consumer logConsumer;

    private String id;
    private AMQP.BasicProperties msgProperties;

    private ConsumerBehaviour logBehaviour = (String consumerTag, Envelope envelope,
                                                 AMQP.BasicProperties properties, byte[] body) -> {
        try {
            System.out.println(id + " log from " + properties.getReplyTo() + ": "
                    + new String(body, "UTF-8"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    };

    public Admin(String id) {
        this.id = id;

        msgProperties = new AMQP.BasicProperties
                .Builder()
                .correlationId(id)
                .replyTo(id)
                .build();

        infoChannel = Factory.connectProducer(Factory.INFO_NAME);

        logConsumer = Factory.connectConsumerToExchange(Factory.LOG_NAME, logBehaviour);
    }

    public void sendInfo(String info) throws IOException {
        infoChannel.basicPublish(Factory.INFO_NAME, "", msgProperties, info.getBytes());
    }

}
