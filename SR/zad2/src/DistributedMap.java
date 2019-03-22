import org.jgroups.JChannel;
import org.jgroups.Message;
import org.jgroups.ReceiverAdapter;
import org.jgroups.View;
import org.jgroups.protocols.*;
import org.jgroups.protocols.pbcast.*;
import org.jgroups.stack.ProtocolStack;
import protos.HashMapProtos;

import java.io.*;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class DistributedMap implements SimpleStringMap {

    private JChannel channel;
    private Map<String, Integer> map;
    private final Boolean flag = false;

    @Override
    public boolean containsKey(String key) {
        return map.containsKey(key);
    }

    @Override
    public Integer get(String key) {
        return map.get(key);
    }

    @Override
    public void put(String key, Integer value) {
        HashMapProtos.HashMapOperation operation = HashMapProtos.HashMapOperation.newBuilder()
                .setType(HashMapProtos.HashMapOperation.OperationType.PUT)
                .setKey(key)
                .setValue(value)
                .build();
        send(operation);
        synchronized (flag) {
            map.put(key, value);
        }
    }

    @Override
    public Integer remove(String key) {
        HashMapProtos.HashMapOperation operation = HashMapProtos.HashMapOperation.newBuilder()
                .setType(HashMapProtos.HashMapOperation.OperationType.REMOVE)
                .setKey(key)
                .setValue(0.0)
                .build();
        synchronized (flag) {
            send(operation);
            return map.remove(key);
        }
    }

    private void send(HashMapProtos.HashMapOperation operation) {
        Message msg = new Message(null, null, operation.toByteArray());
        try {
            channel.send(msg);
        } catch (Exception e) {
            System.err.println(e.toString());
            e.printStackTrace();
        }
    }

    public DistributedMap(String groupName) throws Exception {
        channel = new JChannel(false);
        ProtocolStack stack = new ProtocolStack();
        channel.setProtocolStack(stack);

        stack.addProtocol(new UDP())
                .addProtocol(new PING())
                .addProtocol(new MERGE3())
                .addProtocol(new FD_SOCK())
                .addProtocol(new FD_ALL()
                        .setValue("timeout", 12000)
                        .setValue("interval", 3000))
                .addProtocol(new VERIFY_SUSPECT())
                .addProtocol(new BARRIER())
                .addProtocol(new NAKACK2())
                .addProtocol(new UNICAST3())
                .addProtocol(new STABLE())
                .addProtocol(new GMS())
                .addProtocol(new UFC())
                .addProtocol(new MFC())
                .addProtocol(new FRAG2())
                .addProtocol(new SEQUENCER())
                .addProtocol(new STATE_SOCK())
                .addProtocol(new FLUSH());

        stack.init();

        channel.connect(groupName);
        map = new ConcurrentHashMap<>();

        channel.setReceiver(new ReceiverAdapter(){
            @Override
            public void viewAccepted(View view) {
                super.viewAccepted(view);
                System.out.println(view.toString());
            }

            public void receive(Message msg) {
                if(msg.getSrc().equals(channel.getAddress()))
                    return;
                System.out.println("received msg from " + msg.getSrc());
                try {
                    HashMapProtos.HashMapOperation op = HashMapProtos.HashMapOperation.parseFrom(msg.getBuffer());
                    synchronized (flag) {
                        if(op.getType() == HashMapProtos.HashMapOperation.OperationType.PUT) {
                            map.put(op.getKey(), new Double(op.getValue()).intValue());
                        } else if(op.getType() == HashMapProtos.HashMapOperation.OperationType.REMOVE) {
                            map.remove(op.getKey());
                        }
                    }
                } catch(Exception e) {
                    System.err.println(e);
                    e.printStackTrace();
                }
            }

            @Override
            public void getState(OutputStream output) throws Exception {
                System.out.println("getState");
                //super.getState(output);
                ObjectOutputStream oos = new ObjectOutputStream(output);
                synchronized (flag) {
                    oos.writeObject(map);
                }
            }

            @Override
            public void setState(InputStream input) throws Exception {
                System.out.println("setState");
                //super.setState(input);
                ObjectInputStream ois = new ObjectInputStream(input);
                synchronized (flag) {
                    map = (ConcurrentHashMap<String, Integer>) ois.readObject();
                }
            }
        });

        channel.getState(null, 0);
    }

    public void print() {
        synchronized (flag) {
            System.out.println(channel);
            map.forEach((k,v) -> System.out.println(k + ": " + v));
        }
    }
}
