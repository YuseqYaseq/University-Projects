from pymongo import MongoClient
db = MongoClient().jeopardy
for res in db.question.aggregate([  \
                # wybierz te pytania, których air_date jest większy lub równy 2000-01-01
                # ponieważ data jest w formacie YYYY-MM-DD możemy sortować alfabetycznie 
                {"$match": {"air_date": {"$gte": "2000-01-01"}} }, \
                # pogrupuj pytania po kategoriach
                {"$group": {"_id": "$category", "total": {"$sum": 1}}}]):
    print(res)

