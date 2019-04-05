
public class Main {

    public static void main(String[] args) throws Exception {

        Doctor d1 = new Doctor("d1");
        Doctor d2 = new Doctor("d2");

        Technician t1 = new Technician("t1", Factory.REQUEST_KNEE_NAME, Factory.REQUEST_HIP_NAME);
        Technician t2 = new Technician("t2", Factory.REQUEST_ELBOW_NAME, Factory.REQUEST_HIP_NAME);

        d1.sendElbowRequest();
        d2.sendKneeRequest();
        d1.sendHipRequest();

        Thread.sleep(1000 * 30);
    }
}
