import com.rabbitmq.client.AMQP;
import com.rabbitmq.client.Channel;
import com.rabbitmq.client.Consumer;
import com.rabbitmq.client.Envelope;

public class Technician {

    private Channel logChannel;
    private Channel resultChannel;

    private Consumer[] requestConsumer = new Consumer[2];
    private Consumer infoConsumer;

    private String id;
    private AMQP.BasicProperties msgProperties;

    private ConsumerBehaviour requestBehaviour = (String consumerTag, Envelope envelope,
                                                        AMQP.BasicProperties properties, byte[] body) -> {
        try {
            Thread.sleep(1000);
            System.out.println(id + " request: " + new String(body, "UTF-8"));
            resultChannel.basicPublish(properties.getReplyTo(), "", false, false,
                    null, body);
            logChannel.basicPublish(Factory.LOG_NAME, "", msgProperties, "reply log".getBytes());
        } catch (Exception e) {
            e.printStackTrace();
        }
    };

    public Technician(String id, String possibleRequest1, String possibleRequest2) {
        this.id = id;

        msgProperties = new AMQP.BasicProperties
                .Builder()
                .correlationId(id)
                .replyTo(id)
                .build();

        logChannel = Factory.connectProducer(Factory.LOG_NAME);
        resultChannel = Factory.connectProducer(Factory.RESULT_NAME);

        requestConsumer[0] = Factory.connectConsumerToQueue(possibleRequest1, requestBehaviour);
        requestConsumer[1] = Factory.connectConsumerToQueue(possibleRequest2, requestBehaviour);
        infoConsumer = Factory.connectConsumerToExchange(Factory.INFO_NAME, CommonBehaviours.infoBehaviour);
    }
}
