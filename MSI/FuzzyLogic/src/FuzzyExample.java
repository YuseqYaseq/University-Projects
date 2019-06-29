
public class FuzzyExample {

    public static void main(String[] args) throws Exception {
        Game game = new Game(10, 8, 15, 2);
        Agent agent = new Agent(game);

        game.update(0);
        while(!game.isLost()) {
            game.draw();
            game.update(agent.getMove());
            Thread.sleep(500);
        }

    }

}