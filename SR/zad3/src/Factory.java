import com.rabbitmq.client.*;

import java.io.IOException;

public class Factory {

    public static String LOG_NAME = "log";
    public static String REQUEST_ELBOW_NAME = "elbow";
    public static String REQUEST_HIP_NAME = "hip";
    public static String REQUEST_KNEE_NAME = "knee";
    public static String RESULT_NAME = "result";//"amq.rabbitmq.reply-to";
    public static String INFO_NAME = "info";

    private static Connection connection;

    static {
        try {
            ConnectionFactory factory = new ConnectionFactory();
            factory.setHost("localhost");
            connection = factory.newConnection();
        } catch(Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        }
    }

    public static Consumer connectConsumerToExchange(String exchangeName, ConsumerBehaviour behaviour) {
        try {
            Channel channel = connection.createChannel();
            //channel.basicQos(1);
            channel.exchangeDeclare(exchangeName, BuiltinExchangeType.DIRECT);
            String queueName = channel.queueDeclare().getQueue();
            channel.queueBind(queueName, exchangeName, "");
            Consumer consumer = createConsumer(behaviour, channel);
            channel.basicConsume(queueName, false, consumer);
            return consumer;
        } catch(Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        }
        return null;
    }

    public static Consumer connectConsumerToQueue(String queueName, ConsumerBehaviour behaviour) {
        try {
            Channel channel = connection.createChannel();
            //channel.basicQos(1);
            channel.queueDeclare(queueName, false, false, false, null);
            channel.queueBind(queueName, queueName, "");
            Consumer consumer = createConsumer(behaviour, channel);
            channel.basicConsume(queueName, true, consumer);
            return consumer;
        } catch(Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        }
        return null;
    }

    private static Consumer createConsumer(ConsumerBehaviour behaviour, Channel channel) {
        return new DefaultConsumer(channel) {
            @Override
            public void handleDelivery(String consumerTag, Envelope envelope, AMQP.BasicProperties properties,
                                       byte[] body) throws IOException {
                behaviour.handleDelivery(consumerTag, envelope, properties, body);
            }
        };
    }

    /*public static Channel connectProducer(String exchangeName, DeliverCallback callback) {
        try {
            Channel producer = connection.createChannel();

            producer.exchangeDeclare(exchangeName, BuiltinExchangeType.DIRECT);
            return producer;
        } catch(Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        }
        return null;
    }*/

    public static Channel connectProducer(String exchangeName) {
        try {
            Channel producer = connection.createChannel();
            //producer.basicQos(1);
            producer.exchangeDeclare(exchangeName, BuiltinExchangeType.DIRECT);
            return producer;
        } catch(Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        }
        return null;
    }

    public void send(Channel producer, String name, byte[] data) {
        try {
            producer.basicPublish(name, "", null, data);
        } catch(Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        }
    }

}
