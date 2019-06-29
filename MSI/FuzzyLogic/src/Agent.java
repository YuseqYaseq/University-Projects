import net.sourceforge.jFuzzyLogic.FIS;
import net.sourceforge.jFuzzyLogic.rule.FuzzyRuleSet;

import static java.lang.Double.isNaN;

public class Agent {

    private String fileName = "D:\\Code\\University-Projects\\MSI\\FuzzyLogic\\src\\declaration.FCL";
    private Game game;
    private FIS fis;
    private FuzzyRuleSet fuzzyRuleSet;

    public Agent(Game game) {
        this.game = game;
        fis = FIS.load(fileName,false);
        fuzzyRuleSet = fis.getFuzzyRuleSet();
    }

    public int getMove() {
        fuzzyRuleSet.setVariable("front_distance", game.getFrontDistance());
        fuzzyRuleSet.setVariable("close_left_distance", game.getLeftDistance());
        fuzzyRuleSet.setVariable("close_right_distance", game.getRightDistance());
        fuzzyRuleSet.setVariable("far_left_distance", game.getFarLeftDistance());
        fuzzyRuleSet.setVariable("far_right_distance", game.getFarRightDistance());
        fuzzyRuleSet.evaluate();

        double val = fuzzyRuleSet.getVariable("move").defuzzify();
        System.out.println(val);
        //fuzzyRuleSet.getVariable("move").chartDefuzzifier(true);
        if(isNaN(val)) {
            System.err.println("Val is NaN!");
            System.err.println(game.getFrontDistance());
            System.err.println(game.getLeftDistance());
            System.err.println(game.getRightDistance());
            System.err.println(game.getFarLeftDistance());
            System.err.println(game.getFarRightDistance());
        }
        //move left
        if(val < -0.05) return -1;

        //wait
        if(val < 0.05) return 0;

        //move right
        return 1;
    }

}
