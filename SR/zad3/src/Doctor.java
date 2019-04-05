import com.rabbitmq.client.*;

import java.io.IOException;

public class Doctor {

    private Channel logChannel;
    private Channel requestElbowChannel;
    private Channel requestHipChannel;
    private Channel requestKneeChannel;

    private Consumer infoConsumer;
    private Consumer resultConsumer;

    private AMQP.BasicProperties msgProperties;

    private String id;

    private ConsumerBehaviour resultBehaviour = (String consumerTag, Envelope envelope,
                                                       AMQP.BasicProperties properties, byte[] body) -> {
        try {
            System.out.println(id + " result: " + new String(body, "UTF-8"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    };

    public Doctor(String id) {
        this.id = id;

        msgProperties = new AMQP.BasicProperties
                .Builder()
                .correlationId(id)
                .replyTo(id)
                .build();

        logChannel = Factory.connectProducer(Factory.LOG_NAME);
        requestElbowChannel = Factory.connectProducer(Factory.REQUEST_ELBOW_NAME);
        requestHipChannel = Factory.connectProducer(Factory.REQUEST_HIP_NAME);
        requestKneeChannel = Factory.connectProducer(Factory.REQUEST_KNEE_NAME);

        infoConsumer = Factory.connectConsumerToExchange(Factory.INFO_NAME, CommonBehaviours.infoBehaviour);
        resultConsumer = Factory.connectConsumerToExchange(id, resultBehaviour);
    }

    public void sendElbowRequest() throws IOException {
        requestElbowChannel.basicPublish(Factory.REQUEST_ELBOW_NAME, "", msgProperties, "elbow request".getBytes());
        logChannel.basicPublish(Factory.LOG_NAME, "", msgProperties, "elbow request log".getBytes());
    }

    public void sendHipRequest() throws IOException {
        requestHipChannel.basicPublish(Factory.REQUEST_HIP_NAME, "", msgProperties, "hip request".getBytes());
        logChannel.basicPublish(Factory.LOG_NAME, "", msgProperties, "hip request log".getBytes());
    }

    public void sendKneeRequest() throws IOException {
        requestKneeChannel.basicPublish(Factory.REQUEST_KNEE_NAME, "", msgProperties, "knee request".getBytes());
        logChannel.basicPublish(Factory.LOG_NAME, "", msgProperties, "knee request log".getBytes());
    }
}
