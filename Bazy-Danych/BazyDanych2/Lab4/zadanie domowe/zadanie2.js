db.getCollection('question').aggregate([
    {$match : {"air_date": {"$gte": "2000-01-01"}}},
    {$group : {_id: "$category", total : {$sum : 1}}}
])