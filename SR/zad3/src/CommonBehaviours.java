import com.rabbitmq.client.AMQP;
import com.rabbitmq.client.Envelope;

public class CommonBehaviours {
    public static ConsumerBehaviour infoBehaviour = (String consumerTag, Envelope envelope,
                                               AMQP.BasicProperties properties, byte[] body) -> {
        try {
            System.out.println("info: " + new String(body, "UTF-8"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    };
}
