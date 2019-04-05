import com.rabbitmq.client.AMQP;
import com.rabbitmq.client.Channel;
import com.rabbitmq.client.Consumer;
import com.rabbitmq.client.Envelope;

public class Technician {

    private Channel logChannel;
    private Channel resultChannel;

    private Consumer[] requestConsumer = new Consumer[2];

    private String id;

    private ConsumerBehaviour requestBehaviour = (String consumerTag, Envelope envelope,
                                                        AMQP.BasicProperties properties, byte[] body) -> {
        try {
            Thread.sleep(1000);
            System.out.println(id + " request: " + new String(body, "UTF-8"));
            resultChannel.basicPublish(properties.getReplyTo(), "", false, false,
                    null, body);
        } catch (Exception e) {
            e.printStackTrace();
        }
    };

    public Technician(String id, String possibleRequest1, String possibleRequest2) {
        this.id = id;
        logChannel = Factory.connectProducer(Factory.LOG_NAME);
        resultChannel = Factory.connectProducer(Factory.RESULT_NAME);

        requestConsumer[0] = Factory.connectConsumerToQueue(possibleRequest1, requestBehaviour);
        requestConsumer[1] = Factory.connectConsumerToQueue(possibleRequest2, requestBehaviour);
    }
}
