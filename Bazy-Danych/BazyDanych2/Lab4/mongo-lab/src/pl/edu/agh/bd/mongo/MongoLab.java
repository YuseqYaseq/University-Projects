package pl.edu.agh.bd.mongo;

import java.net.UnknownHostException;
import java.util.*;

import com.mongodb.*;


public class MongoLab {
	private MongoClient mongoClient;
	private DB db;
	private DBCollection business;
	private DBCollection review;
	private DBCollection user;
	
	private MongoLab() throws UnknownHostException {
		mongoClient = new MongoClient();
		db = mongoClient.getDB("Jasek");
		business = db.getCollection("business");
		review = db.getCollection("review");
		user = db.getCollection("user");
	}
	
	private void showCollections(){
		for(String name : db.getCollectionNames()){
			System.out.println("colname: "+name);
		}
	}

	private long count5Stars() {
		DBObject fiveStars = new BasicDBObject("stars", 5.0);
		return business.count(fiveStars);
	}

	private Map<String, Integer> getRestaurantsInCities() {
		DBObject match = new BasicDBObject("$match", new BasicDBObject("categories", "Restaurants"));
		BasicDBObject sumOverCities = new BasicDBObject("_id", "$city");
		sumOverCities.append("total", new BasicDBObject("$sum", 1));
		DBObject group = new BasicDBObject("$group", sumOverCities);
		Cursor out;
		AggregationOptions aggregationOptions = AggregationOptions.builder()
				.batchSize(100)
				.outputMode(AggregationOptions.OutputMode.CURSOR).build();
		out = business.aggregate(Arrays.asList(match, group), aggregationOptions);

		Map<String, Integer> results = new HashMap<>();
		out.forEachRemaining(x -> results.put((String)x.get("_id"), (Integer)x.get("total")));
		return results;
	}

	private Map<String, Double> getNiceHotels() {
		DBObject key = new BasicDBObject("state", 1);

		List<DBObject> conditions = new ArrayList<>();
		conditions.add(new BasicDBObject("categories", "Hotels"));
		conditions.add(new BasicDBObject("attributes.Wi-Fi", "free"));
		conditions.add(new BasicDBObject("stars", new BasicDBObject("$gte", 4.5)));
		DBObject cond = new BasicDBObject("$and", conditions);

		DBObject initial = new BasicDBObject("count", 0);
		String reduce = "function(current, result){result.count += 1}";
		DBObject listOfStates = business.group(key, cond, initial, reduce);
		Set<String> keys = listOfStates.keySet();
		Map<String, Double> results = new HashMap<>();
		keys.forEach(x ->
				results.put((String)((DBObject)listOfStates.get(x)).get("state"),
						(Double)((DBObject)listOfStates.get(x)).get("count")));
		return results;
	}

	private Map<String, Double> getReviewsByType() {
		String map = "function() {" +
				"if(this.votes.funny > 0)" +
					"emit(\"funny\", 1);" +
				"if(this.votes.useful > 0)" +
					"emit(\"useful\", 1);" +
				"if(this.votes.cool > 0)" +
					"emit(\"cool\", 1);" +
				"}";
		String reduce = "function(key, values){return Array.sum(values);}";

		MapReduceCommand cmd = new MapReduceCommand(review, map, reduce, null,
				MapReduceCommand.OutputType.INLINE, null);
		MapReduceOutput out = review.mapReduce(cmd);

		Map<String, Double> results = new HashMap<>();
		out.results().forEach(x -> results.put((String)x.get("_id"), (Double)x.get("value")));
		return results;
	}

	private int countPositiveComments(List<DBObject> comments) {
		int current = 0;
		for(DBObject comment : (List<DBObject>)comments) {
			if(((Double)comment.get("$common.stars")) >= 4.5) current++;
		}
		return current;
	}

	private String getTopReviewer() {
		BasicDBObject usersFilter = new BasicDBObject("_id", 0);
		usersFilter.append("users_id", 1);

		BasicDBObject lookupFields = new BasicDBObject("from", "review");
		lookupFields.append("localField", "user_id");
		lookupFields.append("foreignField", "user_id");
		lookupFields.append("as", "common");

		BasicDBObject lookup = new BasicDBObject("$lookup", lookupFields);

		AggregationOptions aggregationOptions = AggregationOptions.builder()
				.batchSize(100)
				.outputMode(AggregationOptions.OutputMode.CURSOR).build();

		Cursor out = user.aggregate(Collections.singletonList(lookup), aggregationOptions);

		int max = 0;
		int mpos = 0;
		List<Integer> counts = new ArrayList<>();
		out.forEachRemaining(x -> counts.add(countPositiveComments((List<DBObject>)x)));
		for(int i = 0; i < counts.size(); ++i) {
			if(max <  counts.get(i)) {
				max = counts.get(i);
				mpos = i;
			}
		}
	}

	public static void main(String[] args) throws UnknownHostException {
		MongoLab mongoLab = new MongoLab();
		/*System.out.println(mongoLab.count5Stars());
		mongoLab.getRestaurantsInCities().forEach((k,v) ->
			System.out.println(k + ": " + v)
		);

		System.out.println("\n\n\n");
		mongoLab.getNiceHotels().forEach((k,v) ->
				System.out.println(k + ": " + v)
		);

		System.out.println("\n\n\n");
		mongoLab.getReviewsByType().forEach((k,v) ->
				System.out.println(k + ": " + v)
		);*/

		mongoLab.getTopReviewer();
	}

}
