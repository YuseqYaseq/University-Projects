from pymongo import MongoClient
from bson.code import Code
db = MongoClient().jeopardy

db.question.map_reduce(
    # map
    Code(" function() { \
        if(this.value != null) { \
            var newValue = parseInt(this.value.replace(\"$\", \"\").replace(\",\", \"\")); \
            emit(this.category, newValue); \
        } \
    }"),
    
    # reduce
    Code(" function(key, values) { \
        return Array.sum(values); \
    }"),
    
    # query output
    # Rezultat mapReduce będzie dostępny w kolekcji "results"
    "results"    
)
# Wyświetl zawartość "results"
for result in db.results.find({}):
    print(result)
