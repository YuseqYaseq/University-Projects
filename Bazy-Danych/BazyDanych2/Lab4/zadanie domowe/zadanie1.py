from pymongo import MongoClient
db = MongoClient().jeopardy
for question in db.question \
        .find({"category": "ORGANIZATIONS", "value":"$1000"}) \
        .sort([("show_number", 1)]):
    print(question)
