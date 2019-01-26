package pl.edu.agh.ki.bd2;

public class Solution {

    private final GraphDatabase graphDatabase = GraphDatabase.createDatabase();

    public void databaseStatistics() {
        System.out.println(graphDatabase.runCypher("CALL db.labels()"));
        System.out.println(graphDatabase.runCypher("CALL db.relationshipTypes()"));
    }

    public void runAllTests() {
        System.out.println(findActorByName("Emma Watson"));
        System.out.println(findMovieByTitleLike("Star Wars"));
        System.out.println(findRatedMoviesForUser("maheshksp"));
        System.out.println(findCommonMoviesForActors("Emma Watson", "Daniel Radcliffe"));
        System.out.println(findMovieRecommendationForUser("emileifrem"));
        System.out.println(createFilmAndActor("Movie1", "Actor1"));
        System.out.println(addActorBio("Actor1", "Mexico", "640130400000"));
        System.out.println(findActorsInAtLeast6Movies());
        System.out.println(findAverageForActorsInAtLeast7Movies());
        System.out.println(findActorsAndDirectors());
        System.out.println(findUserFriendsRatedMovies("l", "Star Wars"));
    }

    private String findActorByName(final String actorName) {
        String query = "MATCH (actor: Person {name: \"" + actorName + "\"}) RETURN actor";
        return graphDatabase.runCypher(query);
    }

    private String findMovieByTitleLike(final String movieName) {
        String query = "MATCH (movie: Movie) WHERE movie.title =~ \".*" + movieName + ".*\" RETURN movie";
        return graphDatabase.runCypher(query);
    }

    private String findRatedMoviesForUser(final String userLogin) {
        String query = "MATCH (user: User {login: \"" + userLogin + "\"})-[:RATED]->(movie: Movie) return movie";
        return graphDatabase.runCypher(query);
    }

    private String findCommonMoviesForActors(String actorOne, String actorTwo) {
        String query = "MATCH (a1: Actor {name: \"" + actorOne +
                "\"})-[:ACTS_IN]->(movie: Movie)<-[:ACTS_IN]-(a2: Actor {name: \"" + actorTwo + "\"}) RETURN movie";
        return graphDatabase.runCypher(query);
    }

    private String findMovieRecommendationForUser(String userLogin) {
        String query = "MATCH (u: User)-[r:RATED]->(m: Movie)-[*]-(recommendation: Movie {genre: m.genre}) WHERE "
            + "recommendation.title <> m.title AND u.login = \"" + userLogin + "\" AND r.stars > 3.0 "
            + "RETURN DISTINCT recommendation LIMIT 10";
        return graphDatabase.runCypher(query);
    }

    ///////////Czesc 2/////////
    public String createFilmAndActor(String movieName, String actorName){
        String query = "CREATE (:Actor {name: \"" + actorName + "\"})-[:ACTS_IN]->(:Movie {title: \""
                + movieName + "\"})";
        return graphDatabase.runCypher(query);
    }

    public String addActorBio(String actorName, String birthplace, String birthdate){
        String query = "MATCH (a:Actor {name: \"" + actorName + "\"}) SET a.birthplace = \"" + birthplace
                + "\", a.birthdate = \"" + birthdate + "\"";
        return graphDatabase.runCypher(query);
    }

    public String findActorsInAtLeast6Movies(){
        String query = "MATCH (a:Actor)-[:ACTS_IN]->(m:Movie) WITH a, collect(DISTINCT m.title) as titles "
                + "WHERE length(titles) >= 6 RETURN a, length(titles) AS movie_count LIMIT 10";
        return graphDatabase.runCypher(query);
    }

    public String findAverageForActorsInAtLeast7Movies(){
        String query = "MATCH (a:Actor)-[:ACTS_IN]->(m:Movie) WITH a, collect(DISTINCT m.title) as titles "
                + "WHERE length(titles) >= 7 RETURN avg(length(titles)) AS average";
        return graphDatabase.runCypher(query);
    }

    public String findActorsAndDirectors(){
        String query = "MATCH (m1:Movie)<-[:DIRECTED]-(a:Actor)-[:ACTS_IN]->(m2:Movie) WITH a, "
                + "length(collect(DISTINCT m2.title)) as movies_acted_in, "
                + "length(collect(DISTINCT m1.title)) as movies_directed "
                + "WHERE movies_acted_in >= 5 AND movies_directed >= 1 "
                + "RETURN a, movies_acted_in, movies_directed ORDER BY movies_acted_in LIMIT 10";
        return graphDatabase.runCypher(query);
    }

    public String findUserFriendsRatedMovies(String userLogin, String movieName){
        String query = "MATCH (u1: User {login: \"" + userLogin
                + "\"})-[:FRIEND]-(u2: User)-[r:RATED]->(m: Movie {title: \"" + movieName + "\"}) "
                + "WHERE r.stars >= 3 RETURN u2.login, m.title, r.stars";
        return graphDatabase.runCypher(query);
    }

}
