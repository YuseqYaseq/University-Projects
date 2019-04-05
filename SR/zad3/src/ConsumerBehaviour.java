import com.rabbitmq.client.AMQP;
import com.rabbitmq.client.Envelope;

public interface ConsumerBehaviour {
    public void handleDelivery(String consumerTag, Envelope envelope, AMQP.BasicProperties properties, byte[] body);
}
